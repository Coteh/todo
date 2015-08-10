#pragma once
#include <string>

#ifdef _WIN32
#define FOLDER_DELIM "\\"
#else
#define FOLDER_DELIM "/"
#endif

int get_line(char *buffer, int bsize);
void clearInput();

std::string getCurrentDirectory();
std::string getProjectDirectory();
