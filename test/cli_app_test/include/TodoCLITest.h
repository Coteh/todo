#ifndef TODO_CLI_TEST_H
#define TODO_CLI_TEST_H

#include "BaseTest.h"

class TodoCLITestWrapper;

class TodoCLITest : public BaseTest {
public:
	TodoCLITest();
	~TodoCLITest();

	virtual void runTests();
private:
	TodoCLITestWrapper* m_toDoTestEngine;

	void refreshEngine();

	void testAddingItem();
	void testAddingItemAtIndex();
	void testAddingCategory();
	void testAddingLabel();
	void testRemovingItemByIndex();
	void testRemovingItemByPop();
	void testRemovingAllItems();
	void testRemovingAllCompletedItems();
	void testRemovingCategoryByID();
	void testRemovingLabelByID();

	void testSettingItemInfo();
	void testSettingItemCategory();
	void testMarkingItemAsCompleted();
	void testAppendingLabelToItem();
	void testRemovingLabelFromItem();
};

#endif /* end of include guard: TODO_CLI_TEST_H */
