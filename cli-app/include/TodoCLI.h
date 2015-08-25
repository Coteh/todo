#pragma once
#include <vector>
#include <string>
#include "Todo.h"

class ToDoItem;
struct ToDoCategory;
struct ToDoLabel;
enum LabelColor : unsigned int;

class TodoConfig;
class TodoPrinter;

class TodoCLI {
public:
	TodoCLI();
	virtual ~TodoCLI();

	void loadToDoFile();
	void saveToDoFile();

	bool hasConfigFile();
	void loadConfigFile();
	void saveConfigFile();

	size_t getToDoListSize();
	std::string getToDoFilePath();

	TodoPrinter* getToDoPrinter() const;

	void addToDo(ToDoItem _toDoItem);
	void addCategory(std::string _name);
	void addLabel(std::string _name, LabelColor _labelColor);
	void removeToDoByIndex(int _index);
	void popToDo();
	void removeAllToDos();
	void removeCategoryByID(int _categoryID);
	void removeLabelByID(int _labelID);

	void setToDoToCategory(int _toDoIndex, int _categoryID);
	void markToDoCompleted(int _toDoIndex, bool _completed);
	void appendLabelToToDo(int _toDoIndex, int _labelID);
	void eraseLabelFromToDo(int _toDoIndex, int _labelID);

	void setToDoFilePath(std::string _filePath);
private:
	Todo m_todo;
	TodoConfig* m_todoConfig;
	TodoPrinter* m_todoPrinter;

	std::string m_programFilePath;
};
