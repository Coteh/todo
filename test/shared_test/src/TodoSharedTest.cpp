#include "TodoSharedTest.h"
#include "DataTypes.h"
#include <climits>

TodoSharedTest::TodoSharedTest(){

}

TodoSharedTest::~TodoSharedTest(){

}

void TodoSharedTest::runTests(){
	todoReadTest();
	todoWriteTest();
	addItemTest();
	addItemAtIndexTest();
	addCategoryTest();
	addLabelTest();
	itemModificationTest();
	testGetters();
	removeItemTest();
	removeCategoryTest();
	removeLabelTest();
	displayResults();
}

void TodoSharedTest::refreshTodo(){
	m_testTodo = Todo();
}

void TodoSharedTest::todoReadTest(){
	registerTest("Reading todo items from JSON");
	try {
		m_testTodo.parseItems("\{\"todo\":\{\"id\":0,\"category_id\":0,\"name\":\"Test Item\",\"description\":\"This is a test item to see if reading is okay.\",\"completed\":false\}\}");
	} catch (int e) {
		registerFailure();
		return;
	}
	registerPass();
}

void TodoSharedTest::todoWriteTest(){
	registerTest("Writing todo items to JSON");
	try {
		std::string todoResult = m_testTodo.writeItems();
		printf("%s\n", todoResult.c_str());
	} catch (int e) {
		registerFailure();
		return;
	}
	registerPass();
}

void TodoSharedTest::addItemTest(){
	registerTest("Adding an item to the todo list");
	refreshTodo();
	ToDoItem testItem;
	m_testTodo.addItem(testItem);
	//There should be exactly one item in the todo list in order to pass the test
	if (m_testTodo.getTodoListSize() == 1){
		registerPass();
		return;
	}
	registerFailure();
}

void TodoSharedTest::addItemAtIndexTest(){
	registerTest("Adding an item to the todo list at index");
	try{
		refreshTodo();
		for (int i = 0; i < 5; i++){
			ToDoItem testItem;
			m_testTodo.addItem(testItem);
		}
		ToDoItem testItemAtIndex;
		int indexOfIndexItem = 3;
		int categoryOfIndexItem = 5;
		testItemAtIndex.toDoItemInfo.name = "Test Adding to Index";
		testItemAtIndex.toDoItemInfo.description = "Item is in the middle.";
		testItemAtIndex.setCategoryID(categoryOfIndexItem);
		m_testTodo.addItemAtIndex(testItemAtIndex, indexOfIndexItem);
		//Test is passed if the item we just added is at that index
		if (m_testTodo.getItemByIndex(indexOfIndexItem).getCategoryID() == categoryOfIndexItem){
			registerPass();
			return;
		}
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoSharedTest::addCategoryTest(){
	registerTest("Adding a category to the category list");
	refreshTodo();
	ToDoCategory testCategory;
	m_testTodo.addCategory(testCategory);
	//There should be exactly one category in the category list in order to pass the test
	int i = 0;
	for (std::vector<ToDoCategory>::iterator cateItr = m_testTodo.categoriesBegin(); cateItr != m_testTodo.categoriesEnd(); ++cateItr){
		i++;
	}
	if (i == 1){
		registerPass();
		return;
	}
	registerFailure();
}

void TodoSharedTest::addLabelTest(){
	registerTest("Adding a label to the label list");
	refreshTodo();
	ToDoLabel testLabel;
	m_testTodo.addLabel(testLabel);
	//There should be exactly one label in the label list in order to pass the test
	int i = 0;
	for (std::vector<ToDoLabel>::iterator labelItr = m_testTodo.labelsBegin(); labelItr != m_testTodo.labelsEnd(); ++labelItr){
		i++;
	}
	if (i == 1){
		registerPass();
		return;
	}
	registerFailure();
}

void TodoSharedTest::itemModificationTest(){
	registerTest("Modifying an item on the todo list");
	refreshTodo();
	ToDoItem testItem;
	testItem.toDoItemInfo.name = "This Item needs to be modified";
	m_testTodo.addItem(testItem);
	//Since we refreshed the todo list, this item should be at index 0.
	//If it isn't, the test isn't necessarily a failure, just as long as the item has the new title, we should be fine...
	std::string titleToBeApplied = "This item is modifed!";
	testItem.toDoItemInfo.name = titleToBeApplied;
	try{
		m_testTodo.setItem(0, testItem);
		ToDoItem modifiedItem = m_testTodo.getItemByIndex(0);
		//The new title should be the one we set it
		if (modifiedItem.toDoItemInfo.name == titleToBeApplied){
			registerPass();
			return;
		}
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoSharedTest::testGetters(){
	registerTest("Getting Todo contents");
	refreshTodo();
	std::string testItemStr = "Test Get Item";
	std::string testCateStr = "Test Get Category";
	std::string testLabelStr = "Test Get Label";
	ToDoItem testItem;
	testItem.toDoItemInfo.name = testItemStr;
	m_testTodo.addItem(testItem);
	ToDoCategory testCategory;
	testCategory.name = testCateStr;
	m_testTodo.addCategory(testCategory);
	ToDoLabel testLabel;
	testLabel.name = testLabelStr;
	m_testTodo.addLabel(testLabel);
	try{
		//Try to get our items
		if (m_testTodo.getItemByIndex(0).toDoItemInfo.name != testItemStr){
			printf("Item is not there!");
			registerFailure();
			return;
		}
		if (m_testTodo.getCategoryByID(0).name != testCateStr){
			printf("Category is not there!");
			registerFailure();
			return;
		}
		if (m_testTodo.getLabelByID(0).name != testLabelStr){
			printf("Label is not there!");
			registerFailure();
			return;
		}
		//Now try out the edge cases
		try{
			m_testTodo.getItemByIndex(-1);
			m_testTodo.getItemByIndex(INT_MAX);
			m_testTodo.getItemByIndex(INT_MIN);
		} catch (int e){
			if (e != -1){ //if it isn't our error, then fail the test
				registerFailure();
			}
		}
		registerPass();
		return;
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoSharedTest::removeItemTest(){
	registerTest("Removing a todo item");
	refreshTodo();
	ToDoItem testItem;
	m_testTodo.addItem(testItem);
	try{
		m_testTodo.removeItemByIndex(0);
		//There should be exactly zero items in the todo list in order to pass the test
		if (m_testTodo.getTodoListSize() == 0){
			registerPass();
			return;
		}
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoSharedTest::removeCategoryTest(){
	registerTest("Removing a category");
	refreshTodo();
	ToDoCategory testCategory;
	m_testTodo.addCategory(testCategory);
	try{
		m_testTodo.removeCategoryByID(0);
		//There should be exactly zero categories in the category list in order to pass the test
		bool thereIsOne = false;
		for (std::vector<ToDoCategory>::iterator cateItr = m_testTodo.categoriesBegin(); cateItr != m_testTodo.categoriesEnd(); ++cateItr){
			thereIsOne = true;
		}
		if (!thereIsOne){
			registerPass();
			return;
		}
	} catch (int e){
		registerError();
	}
	registerFailure();
}

void TodoSharedTest::removeLabelTest(){
	registerTest("Removing a label");
	refreshTodo();
	ToDoLabel testLabel;
	m_testTodo.addLabel(testLabel);
	try{
		m_testTodo.removeLabelByID(0);
		//There should be exactly zero labels in the label list in order to pass the test
		bool thereIsOne = false;
		for (std::vector<ToDoLabel>::iterator labelItr = m_testTodo.labelsBegin(); labelItr != m_testTodo.labelsEnd(); ++labelItr){
			thereIsOne = true;
		}
		if (!thereIsOne){
			registerPass();
			return;
		}
	} catch (int e){
		registerError();
	}
	registerFailure();
}