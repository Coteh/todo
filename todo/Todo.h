#pragma once
#include <vector>

struct ToDoItem;

class Todo {
public:
	Todo();
	~Todo();

	int getTodoCount();

	void init();
	void loadToDos();
	void saveToDos();
	void printToDos();

	void addToDo(ToDoItem _toDoItem);
	void removeToDoByIndex(int _index);
private:
	std::vector<ToDoItem> m_todoCollection;
};

