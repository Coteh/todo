#pragma once

#ifdef _WIN32
#include <windows.h>
#endif
#include <string>

class Todo;
class ToDoItem;

enum PrintShowType {
	NONE = 0,
	ALL = 1,
	INCOMPLETE = 2,
	COMPLETE = 3
};

class TodoPrinter {
public:
	TodoPrinter(Todo* _todo);
	TodoPrinter();
	~TodoPrinter();

	void init();

	void printToDos();
	void printToDos(bool _verbose);
	void printToDos(int _categoryID);
	void printToDos(int _categoryID, bool _verbose);
	void printToDos(PrintShowType _showType, bool _verbose);
	void printToDos(int _categoryID, PrintShowType _showType, bool _verbose);
	void printToDoItem(const ToDoItem& _toDoItem);
	void printToDoItem(const ToDoItem& _toDoItem, bool _verbose);
	void printCategories();
	void printLabels();
	void printLabelColor(int _colorIndex, const char* _text);
private:
	Todo* m_todo;
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hstdout;
	static const WORD colors[];
#else
	static const int colors[];
#endif
	void beginPrintPaint(int _colorIndex);
	void endPrintPaint();

	std::string nameTag, descriptionTag;
};
