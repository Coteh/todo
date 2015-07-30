#pragma once
#include <vector>
#include <string>

struct ToDoItem;
struct ToDoCategory;

class TodoConfig;

class Todo {
public:
	Todo();
	~Todo();

	int getTodoCount();
	ToDoCategory getCategory(int _categoryID);

	void loadToDoFile();
	void saveToDoFile();
	void createNewToDoFile(std::string _filePath);

	void addToDo(ToDoItem _toDoItem);
	void addCategory(std::string _name);
	void removeToDoByIndex(int _index);
	void removeAllToDos();
	int removeCategory(int _categoryID);

	void setToDoToCategory(int _toDoIndex, int _categoryID);
	void markToDoCompleted(int _toDoIndex, bool _completed);

	std::pair<std::vector<ToDoItem>::iterator, std::vector<ToDoItem>::iterator> getToDoItemIterator();
	std::pair<std::vector<ToDoCategory>::iterator, std::vector<ToDoCategory>::iterator> getToDoCategoryIterator();

	TodoConfig* todoConfig;
private:
	std::vector<ToDoItem> m_todoCollection;
	std::vector<ToDoCategory> m_categories;
};
