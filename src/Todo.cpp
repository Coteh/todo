#include "Todo.h"
#include "TodoConfig.h"
#include "DataTypes.h"
#include "FileIO.h"

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

Todo::Todo() {
	todoConfig = new TodoConfig();
}

Todo::~Todo() {
	delete todoConfig;
}

int Todo::getTodoCount(){
	return m_todoCollection.size();
}

ToDoCategory Todo::getCategory(int _categoryID){
	for (size_t i = 0; i < m_categories.size(); i++){
		if (m_categories[i].id == _categoryID){
			return m_categories[i];
		}
	}
	throw -1;
}

ToDoLabel Todo::getLabel(int _labelID){
	for (std::vector<ToDoLabel>::iterator labelItr = m_labels.begin(); labelItr != m_labels.end(); labelItr++){
		if (labelItr->id == _labelID){
			return *labelItr;
		}
	}
	throw -1;
}

void Todo::loadToDoFile(){
	if (todoConfig == nullptr){
		throw -2;
	}
	std::string fileContents = FileIO::readFile(todoConfig->getToDoFilePath());
	rapidjson::Document doc;
	doc.Parse(fileContents.c_str());
	if (doc.HasParseError()){
		throw -1;
	}
	rapidjson::Value *currJsonObj = &doc;
	for (rapidjson::Value::MemberIterator memberItr = currJsonObj->MemberBegin(); memberItr != currJsonObj->MemberEnd(); ++memberItr) {
		if (strcmp(memberItr->name.GetString(), "todo") == 0){
			ToDoItem toDoItem;
			rapidjson::Value *todoVal = &memberItr->value;
			for (rapidjson::Value::MemberIterator todoItr = todoVal->MemberBegin(); todoItr != todoVal->MemberEnd(); ++todoItr) {
				if (strcmp(todoItr->name.GetString(), "name") == 0 && todoItr->value.IsString()){
					toDoItem.toDoItemInfo.name = todoItr->value.GetString();
				} else if (strcmp(todoItr->name.GetString(), "description") == 0 && todoItr->value.IsString()){
					toDoItem.toDoItemInfo.description = todoItr->value.GetString();
				} else if (strcmp(todoItr->name.GetString(), "id") == 0 && todoItr->value.IsInt()){
					toDoItem.setID(todoItr->value.GetInt());
				} else if (strcmp(todoItr->name.GetString(), "category_id") == 0 && todoItr->value.IsInt()){
					toDoItem.setCategoryID(todoItr->value.GetInt());
				} else if (strcmp(todoItr->name.GetString(), "label_ids") == 0 && todoItr->value.IsArray()){
					rapidjson::Value *arrVal = &todoItr->value;
					for (rapidjson::Value::ConstValueIterator arrItr = arrVal->Begin(); arrItr != arrVal->End(); ++arrItr){
						toDoItem.addLabelID(arrItr->GetInt());
					}
				} else if (strcmp(todoItr->name.GetString(), "completed") == 0 && todoItr->value.IsBool()){
					toDoItem.completed = todoItr->value.GetBool();
				}
			}
			m_todoCollection.push_back(toDoItem);
		} else if (strcmp(memberItr->name.GetString(), "category") == 0){
			ToDoCategory category;
			rapidjson::Value *cateVal = &memberItr->value;
			for (rapidjson::Value::MemberIterator cateItr = cateVal->MemberBegin(); cateItr != cateVal->MemberEnd(); ++cateItr) {
				if (strcmp(cateItr->name.GetString(), "name") == 0 && cateItr->value.IsString()){
					category.name = cateItr->value.GetString();
				} else if (strcmp(cateItr->name.GetString(), "id") == 0 && cateItr->value.IsInt()){
					category.id = cateItr->value.GetInt();
				}
			}
			m_categories.push_back(category);
		} else if (strcmp(memberItr->name.GetString(), "label") == 0){
			ToDoLabel label;
			rapidjson::Value *labelVal = &memberItr->value;
			for (rapidjson::Value::MemberIterator labelItr = labelVal->MemberBegin(); labelItr != labelVal->MemberEnd(); ++labelItr) {
				if (strcmp(labelItr->name.GetString(), "name") == 0 && labelItr->value.IsString()){
					label.name = labelItr->value.GetString();
				} else if (strcmp(labelItr->name.GetString(), "id") == 0 && labelItr->value.IsInt()){
					label.id = labelItr->value.GetInt();
				} else if (strcmp(labelItr->name.GetString(), "color") == 0 && labelItr->value.IsInt()){
					label.color = labelItr->value.GetInt();
				}
			}
			m_labels.push_back(label);
		}
	}
}

void Todo::saveToDoFile(){
	if (todoConfig == nullptr){
		throw -2;
	}
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	for (size_t i = 0; i < m_todoCollection.size(); i++){
		writer.Key("todo");
		writer.StartObject();
		writer.Key("id");
		writer.Int(m_todoCollection[i].getID());
		writer.Key("category_id");
		writer.Int(m_todoCollection[i].getCategoryID());
		if (m_todoCollection[i].hasLabels()){
			writer.Key("label_ids");
			writer.StartArray();
			for (std::forward_list<int>::iterator labelItr = m_todoCollection[i].labelsBegin(); labelItr != m_todoCollection[i].labelsEnd(); ++labelItr){
				writer.Int(*labelItr);
			}
			writer.EndArray();
		}
		writer.Key("name");
		writer.String(m_todoCollection[i].toDoItemInfo.name.c_str());
		writer.Key("description");
		writer.String(m_todoCollection[i].toDoItemInfo.description.c_str());
		writer.Key("completed");
		writer.Bool(m_todoCollection[i].completed);
		writer.EndObject();
	}
	for (size_t i = 0; i < m_categories.size(); i++){
		writer.Key("category");
		writer.StartObject();
		writer.Key("name");
		writer.String(m_categories[i].name.c_str());
		writer.Key("id");
		writer.Int(m_categories[i].id);
		writer.EndObject();
	}
	for (size_t i = 0; i < m_labels.size(); i++){
		writer.Key("label");
		writer.StartObject();
		writer.Key("name");
		writer.String(m_labels[i].name.c_str());
		writer.Key("id");
		writer.Int(m_labels[i].id);
		writer.Key("color");
		writer.Int(m_labels[i].color);
		writer.EndObject();
	}
	writer.EndObject();

	FileIO::writeFile(todoConfig->getToDoFilePath(), sb.GetString(), FileIO::FileWriteType::WRITE);
}

void Todo::createNewToDoFile(std::string _filePath){
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	writer.EndObject();

	FileIO::writeFile(_filePath, sb.GetString(), FileIO::FileWriteType::WRITE);
}

void Todo::addToDo(ToDoItem _toDoItem){
	m_todoCollection.push_back(_toDoItem);
	saveToDoFile();
}

void Todo::addCategory(std::string _name){
	ToDoCategory categoryToAdd;
	categoryToAdd.name = _name;
	//TODO
	//Assign ids in a better way
	categoryToAdd.id = m_categories.size();
	m_categories.push_back(categoryToAdd);
	saveToDoFile();
}

void Todo::addLabel(std::string _name, LabelColor _labelColor){
	ToDoLabel labelToAdd;
	labelToAdd.name = _name;
	labelToAdd.color = _labelColor;
	//TODO
	//Assign ids in a better way
	labelToAdd.id = m_labels.size();
	m_labels.push_back(labelToAdd);
	saveToDoFile();
}

void Todo::removeToDoByIndex(int _index){
	if (_index < 0 || _index >= m_todoCollection.size()){
		throw -1;
	}
	m_todoCollection.erase(m_todoCollection.begin() + _index);
	saveToDoFile();
}

void Todo::removeAllToDos(){
	m_todoCollection.clear();
	saveToDoFile();
}

int Todo::removeCategory(int _categoryID){
	ToDoCategory category;
	try{
		category = getCategory(_categoryID);
	} catch (int e) {
		if (e == -1){
			printf("ERROR: Could not get category of id %i\n", _categoryID);
		} else{
			printf("ERROR: Unknown error getting category.\n");
		}
		return - 1;
	}
	for (std::vector<ToDoCategory>::iterator cateItr = m_categories.begin(); cateItr != m_categories.end(); cateItr++){
		if (cateItr->id == _categoryID){
			m_categories.erase(cateItr);
			saveToDoFile();
			return 0;
		}
	}
	return -1;
}

int Todo::removeLabel(int _labelID){
	for (std::vector<ToDoLabel>::iterator labelItr = m_labels.begin(); labelItr != m_labels.end(); labelItr++){
		if (labelItr->id == _labelID){
			m_labels.erase(labelItr);
			saveToDoFile();
			return 0;
		}
	}
	return -1;
}

void Todo::setToDoToCategory(int _toDoIndex, int _categoryID){
	if (_toDoIndex < 0 || _toDoIndex >= m_todoCollection.size()){
		throw -1;
	}
	m_todoCollection[_toDoIndex].setCategoryID(_categoryID);
	saveToDoFile();
}

void Todo::markToDoCompleted(int _toDoIndex, bool _completed){
	if (_toDoIndex < 0 || _toDoIndex >= m_todoCollection.size()){
		throw -1;
	}
	m_todoCollection[_toDoIndex].completed = _completed;
	saveToDoFile();
}

std::pair<std::vector<ToDoItem>::iterator, std::vector<ToDoItem>::iterator> Todo::getItemIterator(){
	return std::make_pair(m_todoCollection.begin(), m_todoCollection.end());
}

std::pair<std::vector<ToDoCategory>::iterator, std::vector<ToDoCategory>::iterator> Todo::getCategoryIterator(){
	return std::make_pair(m_categories.begin(), m_categories.end());
}

std::pair<std::vector<ToDoLabel>::iterator, std::vector<ToDoLabel>::iterator> Todo::getLabelIterator(){
	return std::make_pair(m_labels.begin(), m_labels.end());
}
