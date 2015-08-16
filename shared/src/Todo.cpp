#include "Todo.h"
#include "DataTypes.h"

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

Todo::Todo(void){

}

Todo::~Todo(void){
	m_itemCollection.clear();
	m_categoryCollection.clear();
	m_labelCollection.clear();
}

size_t Todo::todoListSize(){
	return m_itemCollection.size();
}

ToDoItem Todo::getItemByIndex(int _itemIndex){
	for (size_t i = 0; i < m_itemCollection.size(); i++){
		if (i == _itemIndex){
			return m_itemCollection[i];
		}
	}
	throw -1;
}

ToDoCategory Todo::getCategoryByID(int _categoryID){
	for (std::vector<ToDoCategory>::iterator cateItr = m_categoryCollection.begin(); cateItr != m_categoryCollection.end(); ++cateItr){
		if (cateItr->id == _categoryID){
			return *cateItr;
		}
	}
	throw -1;
}

ToDoLabel Todo::getLabelByID(int _labelID){
	for (std::vector<ToDoLabel>::iterator labelItr = m_labelCollection.begin(); labelItr != m_labelCollection.end(); ++labelItr){
		if (labelItr->id == _labelID){
			return *labelItr;
		}
	}
	throw -1;
}

void Todo::setItem(int _index, ToDoItem _toDoItem){
	if (_index < 0 || _index >= m_itemCollection.size()){
		throw -1;
	}
	m_itemCollection[_index] = _toDoItem;
}

void Todo::parseItems(std::string _contentsBuffer){
	rapidjson::Document doc;
	doc.Parse(_contentsBuffer.c_str());
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
					toDoItem.setCompleted(todoItr->value.GetBool());
				}
			}
			m_itemCollection.push_back(toDoItem);
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
			m_categoryCollection.push_back(category);
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
			m_labelCollection.push_back(label);
		}
	}
}

std::string Todo::writeItems(){
	rapidjson::StringBuffer sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();
	for (size_t i = 0; i < m_itemCollection.size(); i++){
		writer.Key("todo");
		writer.StartObject();
		writer.Key("id");
		writer.Int(m_itemCollection[i].getID());
		writer.Key("category_id");
		writer.Int(m_itemCollection[i].getCategoryID());
		if (m_itemCollection[i].hasLabels()){
			writer.Key("label_ids");
			writer.StartArray();
			for (std::forward_list<int>::iterator labelItr = m_itemCollection[i].labelsBegin(); labelItr != m_itemCollection[i].labelsEnd(); ++labelItr){
				writer.Int(*labelItr);
			}
			writer.EndArray();
		}
		writer.Key("name");
		writer.String(m_itemCollection[i].toDoItemInfo.name.c_str());
		writer.Key("description");
		writer.String(m_itemCollection[i].toDoItemInfo.description.c_str());
		writer.Key("completed");
		writer.Bool(m_itemCollection[i].getCompleted());
		writer.EndObject();
	}
	for (size_t i = 0; i < m_categoryCollection.size(); i++){
		writer.Key("category");
		writer.StartObject();
		writer.Key("name");
		writer.String(m_categoryCollection[i].name.c_str());
		writer.Key("id");
		writer.Int(m_categoryCollection[i].id);
		writer.EndObject();
	}
	for (size_t i = 0; i < m_labelCollection.size(); i++){
		writer.Key("label");
		writer.StartObject();
		writer.Key("name");
		writer.String(m_labelCollection[i].name.c_str());
		writer.Key("id");
		writer.Int(m_labelCollection[i].id);
		writer.Key("color");
		writer.Int(m_labelCollection[i].color);
		writer.EndObject();
	}
	writer.EndObject();

	return sb.GetString();
}

void Todo::addItem(ToDoItem _toDoItem){
	m_itemCollection.push_back(_toDoItem);
}

void Todo::addCategory(ToDoCategory _toDoCategory){
	//TODO
	//Assign ids in a better way
	_toDoCategory.id = m_categoryCollection.size();
	m_categoryCollection.push_back(_toDoCategory);
}

void Todo::addLabel(ToDoLabel _toDoLabel){
	//TODO
	//Assign ids in a better way
	_toDoLabel.id = m_labelCollection.size();
	m_labelCollection.push_back(_toDoLabel);
}

void Todo::removeItemByIndex(int _itemIndex){
	m_itemCollection.erase(m_itemCollection.begin() + _itemIndex);
}

void Todo::removeCategoryByID(int _categoryID){
	for (std::vector<ToDoCategory>::iterator cateItr = m_categoryCollection.begin(); cateItr != m_categoryCollection.end(); ++cateItr){
		if (cateItr->id == _categoryID){
			m_categoryCollection.erase(cateItr);
		}
	}
}

void Todo::removeLabelByID(int _labelID){
	for (std::vector<ToDoLabel>::iterator labelItr = m_labelCollection.begin(); labelItr != m_labelCollection.end(); ++labelItr){
		if (labelItr->id == _labelID){
			m_labelCollection.erase(labelItr);
		}
	}
}

std::vector<ToDoItem>::iterator Todo::itemsBegin(){
	return m_itemCollection.begin();
}

std::vector<ToDoItem>::iterator Todo::itemsEnd(){
	return m_itemCollection.end();
}

std::vector<ToDoCategory>::iterator Todo::categoriesBegin(){
	return m_categoryCollection.begin();
}

std::vector<ToDoCategory>::iterator Todo::categoriesEnd(){
	return m_categoryCollection.end();
}

std::vector<ToDoLabel>::iterator Todo::labelsBegin(){
	return m_labelCollection.begin();
}

std::vector<ToDoLabel>::iterator Todo::labelsEnd(){
	return m_labelCollection.end();
}