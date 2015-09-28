#include "TodoCLITestWrapper.h"
#include "DataTypes.h"
#include <cassert>

TodoCLITestWrapper::TodoCLITestWrapper(){

}

TodoCLITestWrapper::~TodoCLITestWrapper(){

}

void TodoCLITestWrapper::setAmountOfTestItems(int _amtOfItems){
	assert(_amtOfItems >= 0);
	assert(getToDoListSize() == 0);
	for (int i = 0; i < _amtOfItems; i++){
		ToDoItem itemToAdd;
		itemToAdd.toDoItemInfo.name = "Test item";
		itemToAdd.toDoItemInfo.description = "Test item description";
		addToDo(itemToAdd);
	}
	assert(getToDoListSize() == (unsigned int)_amtOfItems);
}
