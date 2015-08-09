#pragma once
#include "TodoApp.h"
#include "TodoPrinter.h"

class TodoTest {
public:
	TodoTest();
	~TodoTest();

	void runTests();
	void displayResults();
private:
    TodoApp m_toDoTestEngine;
	TodoPrinter m_toDoTestPrinter;
	int testsRun, passes;

	void firstTest();
	void printSingleItem();
	void addAndPrint();
	void addLabel(std::string _labelName, LabelColor _labelColor);
	void printItemWithLabel(int _labelIDs, ...);
};
