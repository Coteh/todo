#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include "Todo.h"
#include "TodoConfig.h"
#include "DataTypes.h"
#include "Helpers.h"
#include "TodoPrinter.h"

Todo todoEngine;
TodoPrinter todoPrinter;
std::map<std::string, LabelColor> labelColorNames;

void addToDoDialog(){
	char thing[100];
	ToDoItem itemToAdd;
	itemToAdd.setID(0);
	printf("Provide a name for todo list item.\n");
	get_line(thing, 100);
	itemToAdd.toDoItemInfo.name = thing;
	printf("Provide a description for todo list item\n");
	get_line(thing, 100);
	itemToAdd.toDoItemInfo.description = thing;
	//The only way to assign a category to a todo item right now
	printf("Provide the category id this item will be categorized in:\n");
	int cateID = 0;
#ifdef _WIN32
	scanf_s("%i", &cateID);
#else
	scanf("%i", &cateID);
#endif
	itemToAdd.setCategoryID(cateID);
	itemToAdd.completed = false;
	todoEngine.addToDo(itemToAdd);
	todoPrinter.printToDos();
}

void addCategoryDialog(){
	char thing[100];
	printf("Provide a name for this category.\n");
	get_line(thing, 100);
	todoEngine.addCategory(thing);
	todoPrinter.printCategories();
}

void removeToDoDialog(){
	printf("Please enter number of what \"to do\" item you would like to remove.\n");
	int charRem = 0;
#ifdef _WIN32
	scanf_s("%i", &charRem);
#else
	scanf("%i", &charRem);
#endif
	if (charRem > 0 && charRem <= todoEngine.getTodoCount()){
		todoEngine.removeToDoByIndex(charRem - 1);
		todoPrinter.printToDos();
	}
}

void init(){
	TodoConfig* configObj = todoEngine.todoConfig;
	if (configObj != nullptr){
		try {
			configObj->loadConfigFile();
		} catch (int e) {
			if (e == -1){
				configObj->createNewConfigFile();
#ifdef _DEBUG
				printf("ERROR: Error parsing todo config file. New one has been generated!\n");
#endif
			} else {
				printf("ERROR: Unexpected error! Exiting program!\n");
				exit(-1);
			}
		}
	}
	try {
		todoEngine.loadToDoFile();
	} catch (int e) {
		if (e == -1){
			std::string todoFilePath = configObj->getToDoFilePath();
			if (strcmp(todoFilePath.c_str(), "\0") == 0){ //if no todo filepath currently exists in config...
				//Create a default one inside project directory
				std::string fullFileDirectory = getProjectDirectory();
				todoFilePath = fullFileDirectory + FOLDER_DELIM + "todo.jsondb";
				//printf("Full FilePath: %s\n", todoFilePath.c_str());
				configObj->setToDoFilePath(todoFilePath);
				configObj->saveConfigFile();
			}
			todoEngine.createNewToDoFile(todoFilePath);
#ifdef _DEBUG
			printf("ERROR: Error parsing todo database. New one has been generated!\n");
#endif
		} else {
			printf("ERROR: Unexpected error! Exiting program!\n");
			exit(-1);
		}
	}
	todoPrinter = TodoPrinter(&todoEngine);
	//Initializing color name map
	labelColorNames["white"] = LabelColor::WHITE;
	labelColorNames["green"] = LabelColor::GREEN;
	labelColorNames["magenta"] = LabelColor::MAGENTA;
	labelColorNames["yellow"] = LabelColor::YELLOW;
	labelColorNames["red"] = LabelColor::RED;
}

int main(int argc, char const *argv[]){
	init();
	if (argc > 1){
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--h") == 0){
			printf("usage: todo [--h] <command>\n\ntodo is a command-line app that organizes todo items.\n\nList of commands:\n");
			printf(" add\t\tAdd a todo item. Provide a name and description for second and third arguments.\n");
			printf(" remove\t\tRemove a todo item by index number. Provide the todo's index number as the second argument.\n");
			printf(" show/print\tPrints list of todo items that have been added.\n");
			printf(" set\t\tModify existing todo items.\n");
			printf(" config\t\tRetrieve/modify config information.\n");
			printf(" clear\t\tClear all todo items.\n");
			return 0;
		} else if (strcmp(argv[1], "show") == 0 || strcmp(argv[1], "print") == 0){
			if (argc > 2){
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "--h") == 0){
					printf("usage: todo show/print [--h] <command> [-v]\n\nDefault action is to show all todo items.\n\nList of commands:\n");
					printf(" categories\t\tShow all categories.\n");
					printf(" labels\t\t\tShow all labels.\n");
					printf(" label-colors\t\tShow all colors that a label can have.\n");
					printf(" by-category\t\tShow todo items by category of [category_id].\n");
					return 0;
				} else if (strcmp(argv[2], "-v") == 0){
					todoPrinter.printToDos(true);
					return 0;
				} else if (strcmp(argv[2], "categories") == 0){
					todoPrinter.printCategories();
					return 0;
				} else if (strcmp(argv[2], "labels") == 0){
					todoPrinter.printLabels();
					return 0;
				} else if (strcmp(argv[2], "label-colors") == 0){
					printf("These are the colors that can be added to a label: \n");
					for (std::map<std::string, LabelColor>::iterator labelColorItr = labelColorNames.begin(); labelColorItr != labelColorNames.end(); labelColorItr++){
						if (labelColorItr != labelColorNames.begin()) printf(", ");
						todoPrinter.printLabelColor(labelColorItr->second, labelColorItr->first.c_str());
					}
					printf("\n");
					return 0;
				} else if (strcmp(argv[2], "by-category") == 0){
					if (argc > 3){
						char* pEnd;
						int idNum = strtol(argv[3], &pEnd, 0);
						if (strcmp(pEnd, "\0") != 0){
							printf("ERROR: Could not process an id number for todo category.");
							return -1;
						}
						if (argc > 4){
							if (strcmp(argv[4], "-v") == 0){
								todoPrinter.printToDos(idNum, true);
								return 0;
							}
						}
						todoPrinter.printToDos(idNum);
						return 0;
					} else{
						printf("ERROR: Please provide the index of the category to sort todos by.\n");
						return -1;
					}
				} else if (strcmp(argv[2], "completed") == 0){
					todoPrinter.printToDos(PrintShowType::COMPLETE, (argc > 3 && (strcmp(argv[3], "-v") == 0)));
					return 0;
				} else if (strcmp(argv[2], "incompleted") == 0){
					todoPrinter.printToDos(PrintShowType::INCOMPLETE, (argc > 3 && (strcmp(argv[3], "-v") == 0)));
					return 0;
				}
			} else{
				todoPrinter.printToDos();
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
				} else if (strcmp(argv[2], "label") == 0){
					if (argc <= 4) {
						printf("ERROR: Please specify the color of the label.\n");
						return -1;
					}
					LabelColor colorToAdd;
					const char* colorArg = argv[4];
					if (labelColorNames.count(colorArg)){ //if it returns at least one element, then it's a valid color
						colorToAdd = labelColorNames[colorArg];
					} else{
						printf("ERROR: Not a valid color.\n");
						return -1;
					}
					std::string labelNameStr = argv[3];
					todoEngine.addLabel(labelNameStr, colorToAdd);
					printf("Label added!\n");
					return 0;
				}
				//Default add action is to add a todo item
				ToDoItem item;
				item.setID(0);
				item.toDoItemInfo.name = argv[2];
				item.toDoItemInfo.description = argv[3];
				item.setCategoryID(0); //will be assigned to first category automatically for now
				item.completed = false;
				todoEngine.addToDo(item);
				printf("Todo item added.\n");
				if (argc > 4){
					if (strcmp(argv[4], "-p") == 0){
						todoPrinter.printToDos();
					}
				}
				return 0;
			} else if (argc == 3){
				//If we are calling for help
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "--h") == 0){
					printf("usage: todo add [--h] <command>\n\nList of commands:\n");
					printf(" [name] [description]\tTodo item's name and description respectively.\n");
					printf(" category [name]\t\tAdd category dialog. (Optional) Provide a subsequent argument for category name.\n");
					printf(" label [name] [color]\t\tAdd a label by providing its [name] and [color] as arguments.\n");
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
					printf(" [index]\t\t\t\tIndex number of todo item to delete.\n");
					printf(" category [category_id]\t\t\tRemove a category specified by [category_id].\n");
					printf(" label [label_id]\t\t\tRemove a label specified by [label_id].\n");
					printf(" all					Clear all todo items.\n");
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
				} else if (strcmp(argv[2], "label") == 0){
					if (argc > 3){
						char* pEnd;
						int labelNum = strtol(argv[3], &pEnd, 0);
						if (strcmp(pEnd, "\0") != 0){
							printf("ERROR: Could not process ID number of the label to remove.");
							return -1;
						}
						if (todoEngine.removeLabel(labelNum) == -1){
							printf("ERROR: No label exists with ID of %i\n", labelNum);
						} else{
							printf("Label removed!\n");
						}
						return 0;
					}
					printf("ERROR: Please provide the ID number of the label to remove.\n");
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
						todoPrinter.printToDos();
					}
				}
				return 0;
			} else{
				removeToDoDialog();
				return 0;
			}
		} else if (strcmp(argv[1], "set") == 0){
			if (argc > 2){
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "--h") == 0){
					printf("usage: todo set [--h] <command>\n\nList of commands:\n");
					printf(" todo [index] <command>         Perform set operations on todo item of [index].\n");
					return 0;
				} else if (strcmp(argv[2], "todo") == 0){
					if (argc > 4){
						char* pEnd;
						int indexNum = strtol(argv[3], &pEnd, 0);
						if (strcmp(pEnd, "\0") != 0){
							printf("ERROR: Could not process an index number for todo item to retrieve.\n");
							return -1;
						}
						if (strcmp(argv[4], "--help") == 0 || strcmp(argv[4], "--h") == 0){
							printf("usage: todo set todo %i [--h] <command>\n\nList of commands:\n", indexNum);
							printf(" category [category_id]\t\t\tSwitch todo item's category to a category of [category_id].\n");
							printf(" mark/unmark\t\t\t\tCheck/uncheck todo item.\n");
							return 0;
						} else if (strcmp(argv[4], "category") == 0){
							if (argc <= 5){
								printf("ERROR: Enter the ID of the category to switch to.\n");
								return -1;
							}
							int cateID = strtol(argv[5], &pEnd, 0);
							if (strcmp(pEnd, "\0") != 0){
								printf("ERROR: Could not process an ID number for category.\n");
								return -1;
							}
							try{
								todoEngine.setToDoToCategory(indexNum - 1, cateID);
							} catch (int e){
								if (e == -1){
									printf("ERROR: Index number %i out of todo list range.\n", indexNum);
									return -1;
								}
							}
							printf("ToDo item's category has been changed to category of id %i.\n", cateID);
							return 0;
						} else if (strcmp(argv[4], "mark") == 0){
							try{
								todoEngine.markToDoCompleted(indexNum - 1, true);
							} catch (int e){
								if (e == -1){
									printf("ERROR: Can't mark an item of index out of range.\n");
									return -1;
								}
							}
							printf("ToDo item has been marked as completed.\n");
							return 0;
						} else if (strcmp(argv[4], "unmark") == 0){
							try{
								todoEngine.markToDoCompleted(indexNum - 1, false);
							} catch (int e){
								if (e == -1){
									printf("ERROR: Can't unmark an item of index out of range.\n");
									return -1;
								}
							}
							printf("ToDo item has been unmarked.\n");
							return 0;
						}
					}
				}
			}
		} else if (strcmp(argv[1], "config") == 0){
			TodoConfig* configFile = todoEngine.todoConfig;
			if (configFile != nullptr){
				if (argc > 2){
					if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "--h") == 0){
						printf("usage: todo config [--h] <command>\n\nList of commands:\n");
						printf(" filepath [filepath]	Get the filepath of todo database. (or set the filepath if [filepath] is provided)\n");
						return 0;
					} else if (strcmp(argv[2], "filepath") == 0){
						if (argc > 3){
							if (strcmp(argv[3], "set") == 0){
								if (argc <= 4){
									printf("ERROR: Enter a filepath for the new todo file.\n");
									return -1;
								} else {
									std::string filePathToUse = argv[4];
									configFile->setToDoFilePath(filePathToUse);
									configFile->saveConfigFile();
									printf("New todo filepath set!\n");
									return 0;
								}
							}
						} else{
							printf("%s\n", configFile->getToDoFilePath().c_str());
							return 0;
						}
					}
				}
			} else{
				printf("ERROR: Config object NOT initialized!\n");
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
	todoPrinter.printToDos();
#ifdef _DEBUG
	getchar();
#endif
}
