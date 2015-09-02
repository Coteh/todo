#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include "TodoCLI.h"
#include "TodoConfig.h"
#include "DataTypes.h"
#include "Helpers.h"
#include "TodoPrinter.h"

TodoCLI todoEngine;
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
	itemToAdd.setCompleted(false);
	todoEngine.addToDo(itemToAdd);
	todoEngine.getToDoPrinter()->printToDos();
}

void addCategoryDialog(){
	char thing[100];
	printf("Provide a name for this category.\n");
	get_line(thing, 100);
	todoEngine.addCategory(thing);
	todoEngine.getToDoPrinter()->printCategories();
}

void removeToDoDialog(){
	printf("Please enter number of what \"to do\" item you would like to remove.\n");
	int charRem = 0;
#ifdef _WIN32
	scanf_s("%i", &charRem);
#else
	scanf("%i", &charRem);
#endif
	if (charRem > 0 && charRem <= todoEngine.getToDoListSize()){
		todoEngine.removeToDoByIndex(charRem - 1);
		todoEngine.getToDoPrinter()->printToDos();
	}
}

void init(){
	//Initializing color name map
	labelColorNames["white"] = LabelColor::WHITE;
	labelColorNames["green"] = LabelColor::GREEN;
	labelColorNames["magenta"] = LabelColor::MAGENTA;
	labelColorNames["yellow"] = LabelColor::YELLOW;
	labelColorNames["red"] = LabelColor::RED;
	labelColorNames["blue"] = LabelColor::BLUE;
	labelColorNames["cyan"] = LabelColor::CYAN;
	labelColorNames["teal"] = LabelColor::TEAL;
	labelColorNames["crimson"] = LabelColor::CRIMSON;
}

int main(int argc, char const *argv[]){
	init();
	if (argc > 1){
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
			printf("usage: todo [-h/--help] <command>\n\ntodo is a command-line app that organizes todo items.\n\nList of commands:\n");
			printf(" add\t\tAdd a todo item. Provide a name and description for second and third arguments.\n");
			printf(" remove\t\tRemove a todo item by index number. Provide the todo's index number as the second argument.\n");
			printf(" show/print\tPrints list of todo items that have been added.\n");
			printf(" set\t\tModify existing todo items.\n");
			printf(" clear\t\tClear all todo items.\n");
			printf(" pop\t\tRemoves the first todo item from the list.\n");
			printf(" count\t\tReturns the amount of todo items currently in the list.\n");
			printf(" config\t\tRetrieve/modify config information.\n");
			printf(" -v --version\tDisplay version number.\n");
			return 0;
		} else if (strcmp(argv[1], "show") == 0 || strcmp(argv[1], "print") == 0){
			if (argc > 2){
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "-h") == 0){
					printf("usage: todo show/print [-h/--help] <command> [-v]\n\nDefault action is to show all todo items.\n\nList of commands:\n");
					printf(" categories\t\tShow all categories.\n");
					printf(" labels\t\t\tShow all labels.\n");
					printf(" label-colors\t\tShow all colors that a label can have.\n");
					printf(" by-category\t\tShow todo items by category of [category_id].\n");
					return 0;
				} else if (strcmp(argv[2], "-v") == 0){
					todoEngine.getToDoPrinter()->printToDos(true);
					return 0;
				} else if (strcmp(argv[2], "categories") == 0){
					todoEngine.getToDoPrinter()->printCategories();
					return 0;
				} else if (strcmp(argv[2], "labels") == 0){
					todoEngine.getToDoPrinter()->printLabels();
					return 0;
				} else if (strcmp(argv[2], "label-colors") == 0){
					printf("These are the colors that can be added to a label: \n");
					for (std::map<std::string, LabelColor>::iterator labelColorItr = labelColorNames.begin(); labelColorItr != labelColorNames.end(); labelColorItr++){
						if (labelColorItr != labelColorNames.begin()) printf(", ");
						todoEngine.getToDoPrinter()->printLabelColor(labelColorItr->second, labelColorItr->first.c_str());
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
								todoEngine.getToDoPrinter()->printToDos(idNum, true);
								return 0;
							}
						}
						todoEngine.getToDoPrinter()->printToDos(idNum);
						return 0;
					} else{
						printf("ERROR: Please provide the index of the category to sort todos by.\n");
						return -1;
					}
				} else if (strcmp(argv[2], "completed") == 0){
					todoEngine.getToDoPrinter()->printToDos(PrintShowType::COMPLETE, (argc > 3 && (strcmp(argv[3], "-v") == 0)));
					return 0;
				} else if (strcmp(argv[2], "incompleted") == 0){
					todoEngine.getToDoPrinter()->printToDos(PrintShowType::INCOMPLETE, (argc > 3 && (strcmp(argv[3], "-v") == 0)));
					return 0;
				}
			} else{
				todoEngine.getToDoPrinter()->printToDos();
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
				item.setCompleted(false);
				bool isSettingIndex = false, isSettingCategory = false, isPrinting = false;
				int indexToSet = -1, categoryIDToSet = -1;
				if (argc > 4){
					for (int i = 4; i < argc; i++){
						if (strcmp(argv[i], "-i") == 0){
							if (i >= argc - 1){
								printf("ERROR: Index number not provided.\n");
								return -1;
							}
							char* pEnd;
							indexToSet = strtol(argv[i + 1], &pEnd, 0);
							if (strcmp(pEnd, "\0") != 0){
								printf("ERROR: Could not process index number to place todo item at.\n");
								return -1;
							} else{
								isSettingIndex = true;
							}
							i++;
						} else if (strcmp(argv[i], "-c") == 0){
							if (i >= argc - 1){
								printf("ERROR: Category ID not provided.\n");
								return -1;
							}
							char* pEnd;
							categoryIDToSet = strtol(argv[i + 1], &pEnd, 0);
							if (strcmp(pEnd, "\0") != 0){
								printf("ERROR: Could not process category ID for the todo item to be categorized in.\n");
								return -1;
							} else{
								isSettingCategory = true;
							}
							i++;
						} else if (strcmp(argv[i], "-p") == 0){
							isPrinting = true;
						}
					}
				}
				if (isSettingCategory){
					item.setCategoryID(categoryIDToSet);
				}
				if (isSettingIndex){
					try{
						todoEngine.addToDoAtIndex(item, indexToSet - 1);
					} catch (int e){
						if (e == -1){
							printf("ERROR: Index number %i out of todo list range.\n", indexToSet);
							return -1;
						}
					}
				} else{
					todoEngine.addToDo(item);
				}
				printf("Todo item added.\n");
				if (isPrinting){
					todoEngine.getToDoPrinter()->printToDos();
				}
				return 0;
			} else if (argc == 3){
				//If we are calling for help
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "-h") == 0){
					printf("usage: todo add [-h/--help] <command>\n\nList of commands:\n");
					printf(" [name] [description] \t\tTodo item's name and description respectively.\n");
					printf(" \t-i <index>\t\tSpecify position/index on the list to add the item at.\n");
					printf(" \t-c <category_id>\tSpecify the category ID the item will be assigned to upon add.\n");
					printf(" \t-p\t\t\tPrints results after successful add.\n");
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
		} else if ((strcmp(argv[1], "remove") == 0) || (strcmp(argv[1], "rm") == 0)){
			if (argc > 2){
				//If we are calling for help
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "-h") == 0){
					printf("usage: todo remove [-h/--help] <command>\n\nList of commands:\n");
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
						try {
							todoEngine.removeCategoryByID(cateIDNum);
							printf("Category removed!\n");
						} catch (int e){
							if (e == -1){
								printf("ERROR: No category exists with ID of %i\n", cateIDNum);
							}
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
						try {
							todoEngine.removeLabelByID(labelNum);
							printf("Label removed!\n");
						} catch (int e) {
							printf("ERROR: No label exists with ID of %i\n", labelNum);
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
						todoEngine.getToDoPrinter()->printToDos();
					}
				}
				return 0;
			} else{
				removeToDoDialog();
				return 0;
			}
		} else if (strcmp(argv[1], "set") == 0){
			if (argc > 2){
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "-h") == 0){
					printf("usage: todo set [-h/--help] <command>\n\nList of commands:\n");
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
						if (strcmp(argv[4], "--help") == 0 || strcmp(argv[4], "-h") == 0){
							printf("usage: todo set todo %i [-h/--help] <command>\n\nList of commands:\n", indexNum);
							printf(" info\t\t\t\t\tModify todo item's name and/or description.\n");
							printf("\t-name <name>\t\t\tSet the name of the item.\n");
							printf("\t-description <description>\tSet the description of the item.\n");
							printf(" category [category_id]\t\t\tSwitch todo item's category to a category of [category_id].\n");
							printf(" label add [label_id]\t\t\tAdd a label of ID [label_id] to todo item.\n");
							printf(" label remove [label_id]\t\tRemove a label of ID [label_id] from todo item.\n");
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
						} else if (strcmp(argv[4], "info") == 0){
							if (argc > 5){
								ToDoItem todoItem;
								try{
									todoItem = todoEngine.getToDoItemByIndex(indexNum - 1);
								} catch (int e){
									printf("ERROR: Can't edit an item of index out of range.\n");
									return -1;
								}
								ToDoItemInfo infoToSet;
								infoToSet.name = "";
								infoToSet.description = "";
								for (int i = 5; i < argc - 1; i++){
									if (strcmp(argv[i], "-name") == 0 && infoToSet.name == ""){
										infoToSet.name = argv[i + 1];
										i++;
									} else if (strcmp(argv[i], "-description") == 0 && infoToSet.description == ""){
										infoToSet.description = argv[i + 1];
										i++;
									}
								}
								if (infoToSet.name == ""){
									infoToSet.name = todoItem.toDoItemInfo.name;
								}
								if (infoToSet.description == ""){
									infoToSet.description = todoItem.toDoItemInfo.description;
								}
								todoEngine.setToDoInfo(indexNum - 1, infoToSet);
								printf("Todo info set!\n");
								return 0;
							}
							printf("Please provide a -name and/or -description flag to change the respective item information.\n");
							return -1;
						} else if (strcmp(argv[4], "label") == 0){
							if (argc > 5){
								if (strcmp(argv[5], "add") == 0){
									if (argc <= 6){
										printf("ERROR: Please provide a label ID to add to this item.\n");
										return -1;
									}
									char* pEnd;
									int labelNum = strtol(argv[6], &pEnd, 0);
									if (strcmp(pEnd, "\0") != 0){
										printf("ERROR: Could not process ID number of the label to add.");
										return -1;
									}
									try{
										todoEngine.appendLabelToToDo(indexNum - 1, labelNum);
									} catch (int e){
										printf("ERROR: Index number %i out of todo list range.\n", indexNum);
										return -1;
									}
									printf("Label added to ToDo item!\n");
									return 0;
								} else if (strcmp(argv[5], "remove") == 0){
									if (argc <= 6){
										printf("ERROR: Please provide a label ID to remove from this item.\n");
										return -1;
									}
									char* pEnd;
									int labelNum = strtol(argv[6], &pEnd, 0);
									if (strcmp(pEnd, "\0") != 0){
										printf("ERROR: Could not process ID number of the label to remove.");
										return -1;
									}
									try{
										todoEngine.eraseLabelFromToDo(indexNum - 1, labelNum);
									} catch (int e){
										printf("ERROR: Index number %i out of todo list range.\n", indexNum);
										return -1;
									}
									printf("Label removed from ToDo item!\n");
									return 0;
								}
							}
						}
					}
				}
			}
		} else if (strcmp(argv[1], "config") == 0){
			if (todoEngine.hasConfigFile()){
				if (argc > 2){
					if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "-h") == 0){
						printf("usage: todo config [-h/--help] <command>\n\nList of commands:\n");
						printf(" filepath [filepath]	Get the filepath of todo database. (or set the filepath if [filepath] is provided)\n");
						return 0;
					} else if (strcmp(argv[2], "filepath") == 0){
						if (argc > 3){
							std::string filePathToUse = argv[3];
							todoEngine.setToDoFilePath(filePathToUse);
							printf("New todo filepath set!\n");
							return 0;
						} else {
							printf("%s\n", todoEngine.getToDoFilePath().c_str());
							return 0;
						}
					}
				}
			} else{
				printf("ERROR: Config file could not be found!\n");
			}
		} else if (strcmp(argv[1], "clear") == 0){
			if (argc > 2){
				if (strcmp(argv[2], "--help") == 0 || strcmp(argv[2], "-h") == 0){
					printf("usage: todo clear [-h/--help] <command>\n\nDefault clear action deletes all todo items from list.\n\nList of commands:\n");
					printf(" completed\tClear all completed items from list.\n");
					return 0;
				} else if (strcmp(argv[2], "completed") == 0){
					todoEngine.removeAllToDosMarked();
					printf("All completed ToDos have been cleared!\n");
					return 0;
				}
			} else {
				//Duplicate function of "remove all"
				todoEngine.removeAllToDos(); //remove 'em all!
				printf("All ToDos cleared!\n");
				return 0;
			}
		} else if (strcmp(argv[1], "pop") == 0){
			todoEngine.popToDo();
			printf("First todo item on list has been cleared.\n");
			return 0;
		} else if (strcmp(argv[1], "count") == 0){
			size_t todoListSize = todoEngine.getToDoListSize();
			printf("%i\n", todoListSize);
			return 0;
		} else if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0){
			printf("v1.0\n");
			return 0;
		}
		printf("ERROR: Invalid command.\n");
		return -1;
	}
	todoEngine.getToDoPrinter()->printToDos();
#ifdef _DEBUG
	getchar();
#endif
}
