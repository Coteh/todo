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
	void printToDos(int _categoryID);
	void printCategories();

	void addToDo(ToDoItem _toDoItem);
	void addCategory(std::string _name);
	void removeToDoByIndex(int _index);
	void removeAllToDos();
private:
	std::vector<ToDoItem> m_todoCollection;
	std::vector<ToDoCategory> m_categories;

	ToDoCategory getCategory(int _categoryID);

	void writeEmptyConfig(std::string _fileName);
};

