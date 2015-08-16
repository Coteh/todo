#ifndef TODO_H
#define TODO_H
#include <string>
#include <vector>

struct ToDoItem;
struct ToDoCategory;
struct ToDoLabel;

class Todo {
public:
	Todo(void);
	~Todo(void);
	void parseItems(std::string _contentsBuffer);
	std::string writeItems();

	size_t todoListSize();

	ToDoItem getItemByIndex(int _itemIndex);
	ToDoCategory getCategoryByID(int _categoryID);
	ToDoLabel getLabelByID(int _labelID);

	void addItem(ToDoItem _toDoItem);
	void addCategory(ToDoCategory _toDoCategory);
	void addLabel(ToDoLabel _toDoLabel);
	void removeItemByIndex(int _itemIndex);
	void removeCategoryByID(int _categoryID);
	void removeLabelByID(int _labelID);

	void setItem(int _index, ToDoItem _toDoItem);

	std::vector<ToDoItem>::iterator itemsBegin();
	std::vector<ToDoItem>::iterator itemsEnd();
	std::vector<ToDoCategory>::iterator categoriesBegin();
	std::vector<ToDoCategory>::iterator categoriesEnd();
	std::vector<ToDoLabel>::iterator labelsBegin();
	std::vector<ToDoLabel>::iterator labelsEnd();
private:
	std::vector<ToDoItem> m_itemCollection;
	std::vector<ToDoCategory> m_categoryCollection;
	std::vector<ToDoLabel> m_labelCollection;
};

#endif /* end of include guard: TODO_H */
