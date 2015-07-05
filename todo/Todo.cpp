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
}

void Todo::loadToDos(){
	std::string fileContents = FileIO::readFile("todos.list");
	rapidjson::Document doc;
	doc.Parse(fileContents.c_str());
	if (doc.HasParseError()){
		printf("ERROR: Parse Error!\n");
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
				}
			}
			m_todoCollection.push_back(toDoItem);
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
		writer.Key("name");
		writer.String(m_todoCollection[i].name.c_str());
		writer.Key("description");
		writer.String(m_todoCollection[i].description.c_str());
		writer.EndObject();
	}
	writer.EndObject();

	FileIO::writeFile("todos.list", sb.GetString(), FileIO::FileWriteType::WRITE);
}

void Todo::printToDos(){
	size_t todoSize = m_todoCollection.size();
	printf("======= Things to Do ==========\n");
	for (size_t i = 0; i < todoSize; i++){
		printf("%i. Name: %s\n", i + 1, m_todoCollection[i].name.c_str());
		printf("Description: %s\n", m_todoCollection[i].description.c_str());
		if (i != todoSize - 1) printf("---------------------------\n");
	}
	printf("===============================\n");
}

void Todo::addToDo(ToDoItem _toDoItem){
	m_todoCollection.push_back(_toDoItem);
	saveToDos();
}

void Todo::removeToDoByIndex(int _index){
	m_todoCollection.erase(m_todoCollection.begin() + _index);
	saveToDos();
}