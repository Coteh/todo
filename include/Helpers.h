#ifndef HELPERS_H
#define HELPERS_H
#include <string>

#ifdef _WIN32
#define FOLDER_DELIM "\\"
#else
#define FOLDER_DELIM "/"
#endif

std::string getCurrentDirectory();
std::string getProjectDirectory();

#endif /* end of include guard: HELPERS_H */
