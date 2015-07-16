#pragma once
#include <vector>

struct ToDoItem;
struct ToDoCategory;

class Todo {
public:
	Todo();
	~Todo();

	int getTodoCount();

	void init();
	void loadToDos();
	void loadCategories();
	void saveToDos();
	void saveCategories();
	void printToDos();
	void printToDos(bool _verbose);
	void printToDos(int _categoryID);
	void printToDos(int _categoryID, bool _verbose);
	void printToDoItem(const ToDoItem& _toDoItem);
	void printToDoItem(const ToDoItem& _toDoItem, bool _verbose);
	void printCategories();

	void addToDo(ToDoItem _toDoItem);
	void addCategory(std::string _name);
	void removeToDoByIndex(int _index);
	void removeAllToDos();
	int removeCategory(int _categoryID);

	void setToDoToCategory(int _toDoIndex, int _categoryID);
	void markToDoCompleted(int _toDoIndex, bool _completed);
private:
	std::vector<ToDoItem> m_todoCollection;
	std::vector<ToDoCategory> m_categories;

	ToDoCategory getCategory(int _categoryID);

	void writeEmptyConfig(std::string _fileName);
};

