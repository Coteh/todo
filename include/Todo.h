#pragma once
#include <vector>
#include <string>

struct ToDoItem;
struct ToDoCategory;
struct ToDoLabel;
enum LabelColor : unsigned int;

class TodoConfig;

class Todo {
public:
	Todo();
	~Todo();

	int getTodoCount();
	ToDoCategory getCategory(int _categoryID);
	ToDoLabel getLabel(int _labelID);

	void loadToDoFile();
	void saveToDoFile();
	void createNewToDoFile(std::string _filePath);

	void addToDo(ToDoItem _toDoItem);
	void addCategory(std::string _name);
	void addLabel(std::string _name, LabelColor _labelColor);
	void removeToDoByIndex(int _index);
	void removeAllToDos();
	int removeCategory(int _categoryID);
	int removeLabel(int _labelID);

	void setToDoToCategory(int _toDoIndex, int _categoryID);
	void markToDoCompleted(int _toDoIndex, bool _completed);

	std::pair<std::vector<ToDoItem>::iterator, std::vector<ToDoItem>::iterator> getItemIterator();
	std::pair<std::vector<ToDoCategory>::iterator, std::vector<ToDoCategory>::iterator> getCategoryIterator();
	std::pair<std::vector<ToDoLabel>::iterator, std::vector<ToDoLabel>::iterator> getLabelIterator();

	TodoConfig* todoConfig;
private:
	std::vector<ToDoItem> m_todoCollection;
	std::vector<ToDoCategory> m_categories;
	std::vector<ToDoLabel> m_labels;
};
