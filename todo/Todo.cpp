#include "Todo.h"
#include "DataTypes.h"
#include "FileIO.h"

#include <rapidjson\document.h>
#include <rapidjson\prettywriter.h>
#include <rapidjson\stringbuffer.h>

Todo::Todo() {
}

Todo::~Todo() {
}

int Todo::getTodoCount(){
	return m_todoCollection.size();
}

void Todo::init(){
	loadToDos();
	loadCategories();
}

ToDoCategory Todo::getCategory(int _categoryID){
	for (size_t i = 0; i < m_categories.size(); i++){
		if (m_categories[i].id == _categoryID){
			return m_categories[i];
		}
	}
	throw -1;
}

void Todo::loadToDos(){
	std::string fileContents = FileIO::readFile("todos.list");
	rapidjson::Document doc;
	doc.Parse(fileContents.c_str());
	if (doc.HasParseError()){
		writeEmptyConfig("todos.list");
#ifdef _DEBUG
		printf("ERROR: Error parsing todo database. New one has been generated!\n");
#endif
		return;
	}
	rapidjson::Value *currJsonObj = &doc;
	for (rapidjson::Value::MemberIterator memberItr = currJsonObj->MemberBegin(); memberItr != currJsonObj->MemberEnd(); ++memberItr) {
		if (strcmp(memberItr->name.GetString(), "todo") == 0){
			ToDoItem toDoItem;
			rapidjson::Value *todoVal = &memberItr->value;
			for (rapidjson::Value::MemberIterator todoItr = todoVal->MemberBegin(); todoItr != todoVal->MemberEnd(); ++todoItr) {
				if (strcmp(todoItr->name.GetString(), "name") == 0 && todoItr->value.IsString()){
					toDoItem.name = todoItr->value.GetString();
				} else if (strcmp(todoItr->name.GetString(), "description") == 0 && todoItr->value.IsString()){
					toDoItem.description = todoItr->value.GetString();
				} else if (strcmp(todoItr->name.GetString(), "id") == 0 && todoItr->value.IsInt()){
					toDoItem.id = todoItr->value.GetInt();
				} else if (strcmp(todoItr->name.GetString(), "category_id") == 0 && todoItr->value.IsInt()){
					toDoItem.categoryID = todoItr->value.GetInt();
				}
			}
			m_todoCollection.push_back(toDoItem);
		}
	}
}

void Todo::loadCategories(){
	std::string fileContents = FileIO::readFile("categories.list");
	rapidjson::Document doc;
	doc.Parse(fileContents.c_str());
	if (doc.HasParseError()){
		writeEmptyConfig("categories.list");
#ifdef _DEBUG
		printf("ERROR: Error parsing category database. New one has been generated!\n");
#endif
		return;
	}
	rapidjson::Value *currJsonObj = &doc;
	for (rapidjson::Value::MemberIterator memberItr = currJsonObj->MemberBegin(); memberItr != currJsonObj->MemberEnd(); ++memberItr) {
		if (strcmp(memberItr->name.GetString(), "category") == 0){
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
		}
	}
}

void Todo::saveToDos(){
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	for (size_t i = 0; i < m_todoCollection.size(); i++){
		writer.Key("todo");
		writer.StartObject();
		writer.Key("id");
		writer.Int(m_todoCollection[i].id);
		writer.Key("category_id");
		writer.Int(m_todoCollection[i].categoryID);
		writer.Key("name");
		writer.String(m_todoCollection[i].name.c_str());
		writer.Key("description");
		writer.String(m_todoCollection[i].description.c_str());
		writer.EndObject();
	}
	writer.EndObject();

	FileIO::writeFile("todos.list", sb.GetString(), FileIO::FileWriteType::WRITE);
}

void Todo::saveCategories(){
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	for (size_t i = 0; i < m_categories.size(); i++){
		writer.Key("category");
		writer.StartObject();
		writer.Key("name");
		writer.String(m_categories[i].name.c_str());
		writer.Key("id");
		writer.Int(m_categories[i].id);
		writer.EndObject();
	}
	writer.EndObject();

	FileIO::writeFile("categories.list", sb.GetString(), FileIO::FileWriteType::WRITE);
}

void Todo::printToDos(){
	size_t todoSize = m_todoCollection.size();
	printf("======= Things to Do ==========\n");
	for (size_t i = 0; i < todoSize; i++){
		if (i > 0 && i < todoSize) printf("---------------------------\n");
		printf("%i. Name: %s\n", i + 1, m_todoCollection[i].name.c_str());
		printf("Description: %s\n", m_todoCollection[i].description.c_str());
	}
	printf("===============================\n");
}

void Todo::printToDos(int _categoryID){
	size_t todoSize = m_todoCollection.size();
	ToDoCategory category;
	try{
		category = getCategory(_categoryID);
	} catch(int e) {
		if (e == -1){
			printf("ERROR: Could not get category of id %i\n", _categoryID);
		} else{
			printf("ERROR: Unknown error getting category.\n");
		}
		return;
	}
	printf("========== Things to Do in Category: %s ==========\n", category.name.c_str());
	int shownAmt = 0;
	for (size_t i = 0; i < todoSize; i++){
		if (m_todoCollection[i].categoryID == category.id){
			if (shownAmt > 0 && i < todoSize) printf("---------------------------\n");
			printf("%i. Name: %s\n", i + 1, m_todoCollection[i].name.c_str());
			printf("Description: %s\n", m_todoCollection[i].description.c_str());
			shownAmt++;
		}
	}
	printf("==================================================\n");
}

void Todo::printCategories(){
	size_t categoriesSize = m_categories.size();
	printf("======== Categories ===========\n");
	for (size_t i = 0; i < categoriesSize; i++){
		printf("[ID: %i] %s\n", m_categories[i].id, m_categories[i].name.c_str());
	}
	printf("===============================\n");
}

void Todo::addToDo(ToDoItem _toDoItem){
	m_todoCollection.push_back(_toDoItem);
	saveToDos();
}

void Todo::addCategory(std::string _name){
	ToDoCategory categoryToAdd;
	categoryToAdd.name = _name;
	categoryToAdd.id = m_categories.size();
	m_categories.push_back(categoryToAdd);
	saveCategories();
}

void Todo::removeToDoByIndex(int _index){
	if (_index < 0 || _index >= m_todoCollection.size()){
		throw -1;
	}
	m_todoCollection.erase(m_todoCollection.begin() + _index);
	saveToDos();
}

void Todo::removeAllToDos(){
	m_todoCollection.clear();
	saveToDos();
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
			saveCategories();
			return 0;
		}
	}
	return -1;
}

void Todo::writeEmptyConfig(std::string _fileName){
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	writer.EndObject();

	FileIO::writeFile(_fileName, sb.GetString(), FileIO::FileWriteType::WRITE);
}