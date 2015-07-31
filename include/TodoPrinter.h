#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

class Todo;
struct ToDoItem;

enum PrintShowType {
	NONE = 0,
	ALL = 1,
	INCOMPLETE = 2,
	COMPLETE = 3
};

class TodoPrinter {
public:
	TodoPrinter(Todo* _todoEngine);
	TodoPrinter();
	~TodoPrinter();

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
	Todo* m_toDoEngine;
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hstdout;
	static const WORD colors[];

	void beginPrintPaint(int _colorIndex);
	void endPrintPaint();
#endif
};

