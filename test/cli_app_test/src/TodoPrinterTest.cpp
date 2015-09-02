#include "TodoPrinterTest.h"
#include "TodoPrinter.h"
#include "Todo.h"
#include "DataTypes.h"

TodoPrinterTest::TodoPrinterTest(){
	m_testTodo = new Todo();
	m_testPrinter = new TodoPrinter(m_testTodo);
}

TodoPrinterTest::~TodoPrinterTest(){
	delete m_testPrinter;
	delete m_testTodo;
}

void TodoPrinterTest::runTests(){
	testIndividualPrint();
	testCollectionsPrint();
	displayResults();
}

void TodoPrinterTest::emptyTodoItems(){
	//Remove all items
	size_t listSize = m_testTodo->getTodoListSize();
	for (size_t i = 0; i < listSize; i++){
		m_testTodo->removeItemByIndex(0);
	}
}

void TodoPrinterTest::testIndividualPrint(){
	registerTest("Printing out an individual item");
	try {
		ToDoItem testItem;
		testItem.toDoItemInfo.name = "Test Print Item";
		testItem.toDoItemInfo.description = "This is a test item.";
		m_testPrinter->printToDoItem(testItem);
		registerPass();
		return;
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoPrinterTest::testCollectionsPrint(){
	registerTest("Printing out collections of items");
	try{
		emptyTodoItems();
		const size_t AMOUNT_OF_ITEMS = 5;
		ToDoItem testItems[AMOUNT_OF_ITEMS];
		for (size_t i = 0; i < AMOUNT_OF_ITEMS; i++){
			testItems[i].toDoItemInfo.name = "Test Print Item";
			testItems[i].toDoItemInfo.description = "This is a test item.";
			m_testTodo->addItem(testItems[i]);
		}
		m_testPrinter->printToDos();
	} catch (int e){
		registerError();
		registerFailure();
		return;
	}
	try{
		emptyTodoItems();
		m_testPrinter->printToDos();
	} catch (int e){
		registerError();
		registerFailure();
		return;
	}
	registerPass();
}
