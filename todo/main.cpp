#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Todo.h"
#include "DataTypes.h"
#include "Helpers.h"

Todo todoEngine;

void addToDoDialog(){
	char thing[100];
	ToDoItem itemToAdd;
	itemToAdd.id = 0;
	printf("Provide a name for todo list item.\n");
	get_line(thing, 100);
	itemToAdd.name = thing;
	printf("Provide a description for todo list item\n");
	get_line(thing, 100);
	itemToAdd.description = thing;
	//The only way to assign a category to a todo item right now
	printf("Provide the category id this item will be categorized in:\n");
	int cateID = 0;
	scanf_s("%i", &cateID);
	itemToAdd.categoryID = cateID;
	todoEngine.addToDo(itemToAdd);
	todoEngine.printToDos();
}

void addCategoryDialog(){
	char thing[100];
	printf("Provide a name for this category.\n");
	get_line(thing, 100);
	todoEngine.addCategory(thing);
	todoEngine.printCategories();
}

void removeToDoDialog(){
	printf("Please enter number of what \"to do\" item you would like to remove.\n");
	int charRem = 0;
	scanf_s("%i", &charRem);
	if (charRem > 0 && charRem <= todoEngine.getTodoCount()){
		todoEngine.removeToDoByIndex(charRem - 1);
		todoEngine.printToDos();
	}
}

int main(int argc, char const *argv[]){
	todoEngine.init();
	if (argc > 1){
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--h") == 0){
			printf("usage: todo [--h] <command>\n\ntodo is a command-line app that organizes todo items.\n\nList of commands:\n");
			printf(" add            Add a todo item. Provide a name and description for second and third arguments.\n");
			printf(" remove         Remove a todo item by index number. Provide the todo's index number as the second argument.\n");
			printf(" clear          Clear all todo items.\n");
			printf(" show/print     Prints list of todo items that have been added.\n");
			return 0;
		} else if (strcmp(argv[1], "show") == 0 || strcmp(argv[1], "print") == 0){
			if (argc > 2){
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "--h") == 0){
					printf("usage: todo show/print [--h] <command>\n\nDefault action is to show all todo items.\n\nList of commands:\n");
					printf(" categories         Show all categories.\n");
					printf(" by-category        Show todo items by category of [category_id].\n");
					return 0;
				} else if (strcmp(argv[2], "categories") == 0){
					todoEngine.printCategories();
					return 0;
				} else if (strcmp(argv[2], "by-category") == 0){
					if (argc > 3){
						char* pEnd;
						int idNum = strtol(argv[3], &pEnd, 0);
						if (strcmp(pEnd, "\0") != 0){
							printf("ERROR: Could not process an id number for todo category.");
							return -1;
						}
						todoEngine.printToDos(idNum);
						return 0;
					} else{
						printf("ERROR: Please provide the index of the category to sort todos by.\n");
						return -1;
					}
				}
			} else{
				todoEngine.printToDos();
				return 0;
			}
		} else if (strcmp(argv[1], "add") == 0){
			if (argc > 3){
				//If we are adding a category rather than a todo item...
				if (strcmp(argv[2], "category") == 0){
					std::string cateNameStr = argv[3];
					todoEngine.addCategory(cateNameStr);
					printf("Category added!\n");
					return 0;
				}
				//Default add action is to add a todo item
				ToDoItem item;
				item.id = 0;
				item.name = argv[2];
				item.description = argv[3];
				item.categoryID = 0; //will be assigned to first category automatically for now
				todoEngine.addToDo(item);
				printf("Todo item added.\n");
				if (argc > 4){
					if (strcmp(argv[4], "-p") == 0){
						todoEngine.printToDos();
					}
				}
				return 0;
			} else if (argc == 3){
				//If we are calling for help
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "--h") == 0){
					printf("usage: todo add [--h] <command>\n\nList of commands:\n");
					printf(" [name] [description]      Todo item's name and description respectively.\n");
					printf(" category                  Add category dialog. Provide a subsequent argument for category name.\n");
					return 0;
				//If we are adding a category rather than a todo item...
				} else if (strcmp(argv[2], "category") == 0){
					addCategoryDialog();
					return 0;
				}
				printf("ERROR: Please provide a description for the todo item to add.\n");
				return -1;
			} else {
				addToDoDialog();
				return 0;
			}
		} else if (strcmp(argv[1], "remove") == 0){
			if (argc > 2){
				//If we are calling for help
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "--h") == 0){
					printf("usage: todo remove [--h] <command>\n\nList of commands:\n");
					printf(" [index]         Index number of todo item to delete.\n");
					printf(" category        Remove a category specified by [category_id].\n");
					printf(" all             Clear all todo items.\n");
					return 0;
				//If we are going to remove all todos...
				} else if (strcmp(argv[2], "all") == 0){
					todoEngine.removeAllToDos(); //remove 'em all!
					printf("All ToDos cleared!\n");
					return 0;
				} else if (strcmp(argv[2], "category") == 0){
					if (argc > 3){
						char* pEnd;
						int cateIDNum = strtol(argv[3], &pEnd, 0);
						if (strcmp(pEnd, "\0") != 0){
							printf("ERROR: Could not process ID number of the category to remove.");
							return -1;
						}
						if (todoEngine.removeCategory(cateIDNum) == -1){
							printf("ERROR: No category exists with ID of %i\n", cateIDNum);
						} else{
							printf("Category removed!\n");
						}
						return 0;
					}
					printf("ERROR: Please provide the ID number of the category to remove.\n");
					return -1;
				}
				char* pEnd;
				int indexNum = strtol(argv[2], &pEnd, 0);
				if (strcmp(pEnd, "\0") != 0){
					printf("ERROR: Could not process an index number for todo item to remove.");
					return -1;
				}
				try{
					todoEngine.removeToDoByIndex(indexNum - 1);
				} catch (int e){
					if (e == -1){
						printf("ERROR: Index number %i out of todo list range.\n", indexNum);
						return -1;
					}
				}
				printf("ToDo item removed.\n");
				if (argc > 3){
					if (strcmp(argv[3], "-p") == 0){
						todoEngine.printToDos();
					}
				}
				return 0;
			} else{
				removeToDoDialog();
				return 0;
			}
		} else if (strcmp(argv[1], "clear") == 0){
			//Duplicate function of "remove all"
			todoEngine.removeAllToDos(); //remove 'em all!
			printf("All ToDos cleared!\n");
			return 0;
		}
		printf("ERROR: Invalid command.\n");
		return -1;
	}
	todoEngine.printToDos();
#ifdef _DEBUG
	getchar();
#endif
}