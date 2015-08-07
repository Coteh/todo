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
	addLabel("Test Label", LabelColor::RED);
	addLabel("Test Label 2", LabelColor::MAGENTA);
	printItemWithLabel(0, 1, -1);
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
		toDoItem.toDoItemInfo.name = "Testing Add a Todo item to collection";
		m_toDoTestEngine.addToDo(toDoItem);
	} catch (int e){
		printf("Test failed!\n");
		return;
	}
	passes++;
	printf("Test succeeded!\n");
}

void TodoTest::printSingleItem(){
	testsRun++;
	printf("-----------------------\n");
	printf("Test: Printing out a single todo item\n");
	printf("-----------------------\n");
	try{
		ToDoItem toDoItem;
		toDoItem.toDoItemInfo.name = "Testing Print Single Todo item";
		m_toDoTestPrinter.printToDoItem(toDoItem);
	} catch (int e){
		printf("Test failed!\n");
		return;
	}
	passes++;
	printf("Test succeeded!\n");
}

void TodoTest::addAndPrint(){
	testsRun++;
	printf("-----------------------\n");
	printf("Test: Adding a todo item to the todo list, then printing the list out\n");
	printf("-----------------------\n");
	try{
		ToDoItem toDoItem;
		toDoItem.toDoItemInfo.name = "Testing Add n' Print";
		m_toDoTestEngine.addToDo(toDoItem);
		m_toDoTestPrinter.printToDos();
	} catch (int e){
		printf("Test failed!\n");
		return;
	}
	passes++;
	printf("Test succeeded!\n");
}

void TodoTest::addLabel(std::string _labelName, LabelColor _labelColor){
	testsRun++;
	printf("-----------------------\n");
	printf("Test: Adding a label\n");
	printf("-----------------------\n");
	try{
		m_toDoTestEngine.addLabel(_labelName, _labelColor);
		m_toDoTestPrinter.printLabels();
	} catch (int e){
		printf("Test failed!\n");
		return;
	}
	passes++;
	printf("Test succeeded!\n");
}

void TodoTest::printItemWithLabel(int _labelIDs, ...){
	testsRun++;
	printf("-----------------------\n");
	printf("Test: Printing an item with a label\n");
	printf("-----------------------\n");
	try{
		ToDoItem toDoItem;
		toDoItem.toDoItemInfo.name = "Testing Print Single Todo item with labels";
		va_list labelsArgList;
		for (va_start(labelsArgList, _labelIDs); _labelIDs != -1; _labelIDs = va_arg(labelsArgList, int)){
			toDoItem.addLabelID(_labelIDs);
		}
		va_end(labelsArgList);
		m_toDoTestPrinter.printToDoItem(toDoItem);
	} catch (int e){
		printf("Test failed!\n");
		return;
	}
	passes++;
	printf("Test succeeded!\n");
}
