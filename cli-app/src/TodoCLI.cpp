#include "TodoCLI.h"
#include "TodoConfig.h"
#include "TodoPrinter.h"
#include "DataTypes.h"
#include "FileIO.h"
#include "Helpers.h"
#include <string.h>

#define CONFIG_FILENAME "config.json"

TodoCLI::TodoCLI() {
	m_todoConfig = new TodoConfig();
	m_programFilePath = getProjectDirectory();

	init();
}

TodoCLI::~TodoCLI() {
	delete m_todoConfig;
	delete m_todoPrinter;
}

void TodoCLI::init(){
	loadConfigFile();
	try{
		loadToDoFile();
	} catch (int e){
		std::string todoFilePath = m_todoConfig->getToDoFilePath();
		if (strcmp(todoFilePath.c_str(), "\0") == 0){ //if no todo filepath currently exists in config...
			//Create a default one inside project directory
			std::string fullFileDirectory = getProjectDirectory();
			todoFilePath = fullFileDirectory + FOLDER_DELIM + "todo.jsondb";
			//printf("Full FilePath: %s\n", todoFilePath.c_str());
			m_todoConfig->setToDoFilePath(todoFilePath);
		}
		saveConfigFile();
		printf("ERROR: Error parsing todo database. New one has been generated!\n");
	}

	m_todoPrinter = new TodoPrinter(&m_todo);
}

void TodoCLI::loadToDoFile(){
	if (m_todoConfig == nullptr){
		throw -2;
	}
	std::string fileContents = FileIO::readFile(m_todoConfig->getToDoFilePath());
	m_todo.parseItems(fileContents);
}

void TodoCLI::saveToDoFile(){
	if (m_todoConfig == nullptr){
		throw -2;
	}

	std::string todoJSONBuffer = m_todo.writeItems();

	FileIO::writeFile(m_todoConfig->getToDoFilePath(), todoJSONBuffer, FileIO::FileWriteType::WRITE);
}

bool TodoCLI::hasConfigFile(){
	return (m_todoConfig != nullptr && m_todoConfig->getToDoFilePath() != "");
}

size_t TodoCLI::getToDoListSize(){
	return m_todo.getTodoListSize();
}

std::string TodoCLI::getToDoFilePath(){
	return m_todoConfig->getToDoFilePath();
}

TodoPrinter* TodoCLI::getToDoPrinter() const{
	return m_todoPrinter;
}

void TodoCLI::addToDo(ToDoItem _toDoItem){
	m_todo.addItem(_toDoItem);
	saveToDoFile();
}

void TodoCLI::addCategory(std::string _name){
	ToDoCategory categoryToAdd;
	categoryToAdd.name = _name;
	m_todo.addCategory(categoryToAdd);
	saveToDoFile();
}

void TodoCLI::addLabel(std::string _name, LabelColor _labelColor){
	ToDoLabel labelToAdd;
	labelToAdd.name = _name;
	labelToAdd.color = _labelColor;
	m_todo.addLabel(labelToAdd);
	saveToDoFile();
}

void TodoCLI::removeToDoByIndex(int _index){
	if (_index < 0 || _index >= m_todo.getTodoListSize()){
		throw -1;
	}
	m_todo.removeItemByIndex(_index);
	saveToDoFile();
}

void TodoCLI::popToDo(){
	if (m_todo.getTodoListSize() <= 0){
		throw -1;
	}
	m_todo.removeItemByIndex(0);
	saveToDoFile();
}

void TodoCLI::removeAllToDos(){
	size_t listSize = m_todo.getTodoListSize();
	for (size_t i = 0; i < listSize; i++){
		m_todo.removeItemByIndex(0);
	}
	saveToDoFile();
}

void TodoCLI::removeAllToDosMarked(){
	size_t listSize = m_todo.getTodoListSize();
	if (listSize <= 0) return;
	for (size_t i = listSize - 1; i <= listSize; i--){
		ToDoItem item = m_todo.getItemByIndex(i);
		if (item.getCompleted()) m_todo.removeItemByIndex(i);
	}
	saveToDoFile();
}

void TodoCLI::removeCategoryByID(int _categoryID){
	m_todo.removeCategoryByID(_categoryID);
	saveToDoFile();
}

void TodoCLI::removeLabelByID(int _labelID){
	m_todo.removeLabelByID(_labelID);
	saveToDoFile();
}

void TodoCLI::setToDoToCategory(int _toDoIndex, int _categoryID){
	if (_toDoIndex < 0 || _toDoIndex >= m_todo.getTodoListSize()){
		throw -1;
	}
	ToDoItem todoItem = m_todo.getItemByIndex(_toDoIndex);
	todoItem.setCategoryID(_categoryID);
	m_todo.setItem(_toDoIndex, todoItem);
	saveToDoFile();
}

void TodoCLI::markToDoCompleted(int _toDoIndex, bool _completed){
	if (_toDoIndex < 0 || _toDoIndex >= m_todo.getTodoListSize()){
		throw -1;
	}
	ToDoItem todoItem = m_todo.getItemByIndex(_toDoIndex);
	todoItem.setCompleted(_completed);
	m_todo.setItem(_toDoIndex, todoItem);
	saveToDoFile();
}

void TodoCLI::appendLabelToToDo(int _toDoIndex, int _labelID){
	if (_toDoIndex < 0 || _toDoIndex >= m_todo.getTodoListSize()){
		throw - 1;
	}
	ToDoItem todoItem = m_todo.getItemByIndex(_toDoIndex);
	todoItem.addLabelID(_labelID);
	m_todo.setItem(_toDoIndex, todoItem);
	saveToDoFile();
}

void TodoCLI::eraseLabelFromToDo(int _toDoIndex, int _labelID){
	if (_toDoIndex < 0 || _toDoIndex >= m_todo.getTodoListSize()){
		throw - 1;
	}
	ToDoItem todoItem = m_todo.getItemByIndex(_toDoIndex);
	todoItem.removeLabelID(_labelID);
	m_todo.setItem(_toDoIndex, todoItem);
	saveToDoFile();
}

void TodoCLI::loadConfigFile(){
	std::string fileContents = FileIO::readFile(m_programFilePath + FOLDER_DELIM + CONFIG_FILENAME);
	try{
		m_todoConfig->processConfig(fileContents);
	} catch (int e){
		saveConfigFile();
		printf("ERROR: Error parsing todo config file. New one has been generated!\n");
	}
}

void TodoCLI::saveConfigFile(){
	std::string configSerialized = m_todoConfig->writeConfig();
	FileIO::writeFile(m_programFilePath + FOLDER_DELIM + CONFIG_FILENAME, configSerialized, FileIO::FileWriteType::WRITE);
}

void TodoCLI::setToDoFilePath(std::string _filePath){
	m_todoConfig->setToDoFilePath(_filePath);
	saveConfigFile();
}
