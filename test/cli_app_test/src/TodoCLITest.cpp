#include "TodoCLITest.h"
#include "TodoCLI.h"
#include "DataTypes.h"

TodoCLITest::TodoCLITest(){

}

TodoCLITest::~TodoCLITest(){

}

void TodoCLITest::runTests(){
	testAddingItem();
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
		if (m_toDoTestEngine->getToDoListCount() == 1){
			registerPass();
			return;
		}
	} catch (int e){
		registerError();
		registerFailure();
	}
	registerFailure();
}

void TodoCLITest::testAddingCategory(){
	
}

void TodoCLITest::testAddingLabel(){

}

void TodoCLITest::testRemovingItemByIndex(){

}

void TodoCLITest::testRemovingAllItems(){

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
