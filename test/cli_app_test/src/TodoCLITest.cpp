#include "TodoCLITest.h"
#include "TodoCLI.h"
#include "DataTypes.h"
#include "TodoCLITestWrapper.h"

TodoCLITest::TodoCLITest(){
	m_toDoTestEngine = new TodoCLITestWrapper();
}

TodoCLITest::~TodoCLITest(){
	delete m_toDoTestEngine;
}

void TodoCLITest::runTests(){
	testAddingItem();
	testRemovingItemByIndex();
	testRemovingItemByPop();
	testRemovingAllItems();
	testRemovingAllCompletedItems();
	displayResults();
}

void TodoCLITest::refreshEngine(){
	m_toDoTestEngine->removeAllToDos();
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
	registerTest("Removing items from the todo list by index");
	try {
		refreshEngine();
		m_toDoTestEngine->setAmountOfTestItems(3);
		try {
			m_toDoTestEngine->removeToDoByIndex(0);
		} catch (int e){
			registerError("Could not remove entry of index 0");
			registerFailure();
		}
	} catch (int e){
		registerError();
		registerFailure();
	}
	registerPass();
}

void TodoCLITest::testRemovingItemByPop(){
	registerTest("Popping the top item out of the Todo list");
	try {
		refreshEngine();
		m_toDoTestEngine->setAmountOfTestItems(1);
		//Loop of popping items (list size + 1) times
		size_t listSize = m_toDoTestEngine->getToDoListSize();
		for (size_t i = 0; i <= listSize; i++){
			m_toDoTestEngine->popToDo();
		}
		//We pass the test if we don't get any errors at all during this process
		registerPass();
		return;
	} catch (int e){
		//Expecting an error of pop being performed when list size is 0
		if (m_toDoTestEngine->getToDoListSize() == 0){
			registerError("Todo list count is 0.");
			registerPass();
			return;
		} else{
			registerError();
		}
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

void TodoCLITest::testRemovingAllCompletedItems(){
	registerTest("Removing all todo items that have been completed");
	try {
		refreshEngine();
		//Adding some items
		ToDoItem item1, item2;
		item1.setCompleted(true);
		item2.setCompleted(false);
		m_toDoTestEngine->addToDo(item1);
		m_toDoTestEngine->addToDo(item2);
		//Remove all marked items
		m_toDoTestEngine->removeAllToDosMarked();
		//We pass the test if there's one item left
		if (m_toDoTestEngine->getToDoListSize() == 1){
			registerPass();
		}
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
