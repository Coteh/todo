#ifndef TODO_PRINTER_TEST_H
#define TODO_PRINTER_TEST_H

#include "BaseTest.h"

class TodoPrinter;
class Todo;

class TodoPrinterTest : public BaseTest {
public:
	TodoPrinterTest();
	~TodoPrinterTest();

	virtual void runTests();
private:
	TodoPrinter* m_testPrinter;
	Todo* m_testTodo;

	void emptyTodoItems();

	void testIndividualPrint();
	void testCollectionsPrint();
};

#endif /* end of include guard: TODO_PRINTER_TEST_H */
