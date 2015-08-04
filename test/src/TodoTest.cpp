#include "TodoTest.h"
#include "DataTypes.h"

TodoTest::TodoTest(){
	m_toDoTestPrinter = TodoPrinter(&m_toDoTestEngine);
}

TodoTest::~TodoTest(){

}

void TodoTest::runTests(){
	firstTest();
	printSingleItem();
	addAndPrint();
	displayResults();
}

void TodoTest::displayResults(){
	printf("Passed %i/%i tests!\n", passes, testsRun);
}

void TodoTest::firstTest(){
	testsRun++;
	printf("-----------------------\n");
	printf("Test: Adding a todo item to the todo list\n");
	printf("-----------------------\n");
	try{
		ToDoItem toDoItem;
		toDoItem.name = "Testing Add a Todo item to collection";
		m_toDoTestEngine.addToDo(toDoItem);
	} catch (int e){
		printf("Test failed!\n");
		return;
	}
	passes++;
	printf("Test succeeded!\n");
	return;
}

void TodoTest::printSingleItem(){
	testsRun++;
	printf("-----------------------\n");
	printf("Test: Printing out a single todo item\n");
	printf("-----------------------\n");
	try{
		ToDoItem toDoItem;
		toDoItem.name = "Testing Print Single Todo item";
		m_toDoTestPrinter.printToDoItem(toDoItem);
	} catch (int e){
		printf("Test failed!\n");
		return;
	}
	passes++;
	printf("Test succeeded!\n");
	return;
}

void TodoTest::addAndPrint(){
	testsRun++;
	printf("-----------------------\n");
	printf("Test: Adding a todo item to the todo list, then printing the list out\n");
	printf("-----------------------\n");
	try{
		ToDoItem toDoItem;
		toDoItem.name = "Testing Add n' Print";
		m_toDoTestEngine.addToDo(toDoItem);
		m_toDoTestPrinter.printToDos();
	} catch (int e){
		printf("Test failed!\n");
		return;
	}
	passes++;
	printf("Test succeeded!\n");
	return;
}
