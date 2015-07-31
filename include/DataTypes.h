#pragma once
#include <string>

struct ToDoItem {
	std::string name;
	std::string description;
	int id; //currently unused
	int categoryID;
	int labelID;
	bool completed;
};

struct ToDoCategory {
	std::string name;
	int id;
};

struct ToDoLabel {
	std::string name;
	int color;
	int id;
};

enum LabelColor {
	WHITE = 0,
	GREEN = 1,
	MAGENTA = 2,
	YELLOW = 3,
	RED = 4
};