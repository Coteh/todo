#include <stdio.h>
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
	todoEngine.addToDo(itemToAdd);
	todoEngine.printToDos();
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
			printf("usage: todo [-h] <command>\n\nList of commands:\n");
			printf(" add            Add a todo item. Provide a name and description for second and third arguments.\n");
			printf(" show/print     Prints list of todo items that have been added.\n");
		} else if (strcmp(argv[1], "show") == 0 || strcmp(argv[1], "print") == 0){
			todoEngine.printToDos();
		} else if (strcmp(argv[1], "add") == 0){
			if (argc > 3){
				ToDoItem item;
				item.id = 0;
				item.name = argv[2];
				item.description = argv[3];
				todoEngine.addToDo(item);
				printf("Todo item added.\n");
				if (argc > 4){
					if (strcmp(argv[4], "-p") == 0){
						todoEngine.printToDos();
					}
				}
				return 0;
			} else {
				printf("ERROR: Please provide a todo item to add.\n");
				return -1;
			}
		}
		return 0;
	}
	bool flag = false;
	while (!flag){
		char thing[100];
		printf("Please enter a todo command. (or say \"/exit\" to quit)\n");
		get_line(thing, 100);
		if (strcmp(thing, "/exit") == 0){
			flag = true;
			break;
		} else if (strcmp(thing, "/add") == 0){
			addToDoDialog();
		} else if (strcmp(thing, "/remove") == 0){
			removeToDoDialog();
		} else if (strcmp(thing, "/print") == 0 || strcmp(thing, "/show") == 0){
			todoEngine.printToDos();
		} else {
			printf("Invalid command.\n");
		}
		clearInput();
	}
}