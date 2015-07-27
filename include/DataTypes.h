#pragma once
#include <string>

struct ToDoItem {
	std::string name;
	std::string description;
	int id; //currently unused
	int categoryID;
	bool completed;
};

struct ToDoCategory {
	std::string name;
	int id;
};