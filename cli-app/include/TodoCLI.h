#pragma once
#include <vector>
#include <string>
#include "Todo.h"

class ToDoItem;
struct ToDoItemInfo;
struct ToDoCategory;
struct ToDoLabel;
enum LabelColor : unsigned int;

class TodoConfig;
class TodoPrinter;

class TodoCLI {
public:
	TodoCLI();
	virtual ~TodoCLI();

	void init();

	void loadToDoFile();
	void saveToDoFile();

	bool hasConfigFile();
	void loadConfigFile();
	void saveConfigFile();

	ToDoItem getToDoItemByIndex(int _index);
	size_t getToDoListSize();
	std::string getToDoFilePath() const;

	TodoPrinter* getToDoPrinter() const;

	void addToDo(ToDoItem _toDoItem);
	void addToDoAtIndex(ToDoItem _toDoItem, int _index);
	void addCategory(std::string _name);
	void addLabel(std::string _name, LabelColor _labelColor);
	void removeToDoByIndex(int _index);
	ToDoItem popToDo();
	void removeAllToDos();
	void removeAllToDosMarked();
	void removeCategoryByID(int _categoryID);
	void removeLabelByID(int _labelID);

	void setToDoInfo(int _toDoIndex, ToDoItemInfo _itemInfo);
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
