#pragma once
#include "Todo.h"
#include "TodoPrinter.h"

class TodoTest {
public:
	TodoTest();
	~TodoTest();

	void runTests();
	void displayResults();
private:
    Todo m_toDoTestEngine;
	TodoPrinter m_toDoTestPrinter;
	int testsRun, passes;

	void firstTest();
	void printSingleItem();
	void addAndPrint();
};
