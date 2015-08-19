#include "TodoCLITest.h"
#include "TodoCLI.h"
#include "DataTypes.h"

TodoCLITest::TodoCLITest(){

}

TodoCLITest::~TodoCLITest(){

}

void TodoCLITest::runTests(){
	testAddingItem();
	testRemovingItemByPop();
	testRemovingAllItems();
	displayResults();
}

void TodoCLITest::refreshEngine(){
	if (m_toDoTestEngine != nullptr){
		delete m_toDoTestEngine;
		m_toDoTestEngine = nullptr;
	}
	m_toDoTestEngine = new TodoCLI();
}

void TodoCLITest::testAddingItem(){
	registerTest("Adding an item to the Todo list");
	try {
		refreshEngine();
		ToDoItem testItem;
		testItem.toDoItemInfo.name = "Test Item";
		testItem.toDoItemInfo.description = "This is a test item.";
		m_toDoTestEngine->addToDo(testItem);
		//We pass the test if there's one item in the list now
		if (m_toDoTestEngine->getToDoListSize() == 1){
			registerPass();
			return;
		}
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoCLITest::testAddingCategory(){
	
}

void TodoCLITest::testAddingLabel(){

}

void TodoCLITest::testRemovingItemByIndex(){

}

void TodoCLITest::testRemovingItemByPop(){
	registerTest("Popping the top item out of the Todo list");
	try {
		refreshEngine();
		//Loop of popping items (list size) times
		size_t listSize = m_toDoTestEngine->getToDoListSize();
		for (size_t i = 0; i <= listSize; i++){
			m_toDoTestEngine->popToDo();
		}
		//We pass the test if we don't get any errors at all during this process
		registerPass();
		return;
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoCLITest::testRemovingAllItems(){
	registerTest("Removing all todo items from list");
	try {
		refreshEngine();
		//Remove all items
		m_toDoTestEngine->removeAllToDos();
		//We pass the test if we don't get any errors at all during this process
		registerPass();
		return;
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoCLITest::testRemovingCategoryByID(){

}

void TodoCLITest::testRemovingLabelByID(){

}

void TodoCLITest::testSettingItemCategory(){
	
}

void TodoCLITest::testMarkingItemAsCompleted(){
	
}

void TodoCLITest::testAppendingLabelToItem(){

}

void TodoCLITest::testRemovingLabelFromItem(){

}
