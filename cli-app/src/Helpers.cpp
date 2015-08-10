#include "Helpers.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h> //minwindef.h, processenv.h, libloaderapi.h
#endif

int get_line(char *buffer, int bsize) {
	int ch, len;

	fgets(buffer, bsize, stdin);

	/* remove unwanted characters from the buffer */
	buffer[strcspn(buffer, "\r\n")] = '\0';

	len = strlen(buffer);

	/* clean input buffer if needed */
	if (len == bsize - 1)
	while ((ch = getchar()) != '\n' && ch != EOF);

	return len;
}

void clearInput(){
	fseek(stdin, 0, SEEK_END);
}

//Not needed right now
//but we'll probably need it later
//when the user saves their todo file.
std::string getCurrentDirectory(){
#ifdef _WIN32
	int num = GetCurrentDirectory(0, NULL);
	char buffer[MAX_PATH];
	GetCurrentDirectory(num, buffer);
	return buffer;
#endif
	return ".";
}

std::string getProjectDirectory(){
#ifdef _WIN32
	HMODULE hModule = GetModuleHandle(NULL);
	char buffer[MAX_PATH];
	GetModuleFileName(hModule, buffer, MAX_PATH);
	//break off the program .exe part from the filepath
	char* splitPath = buffer;
	char* context = NULL;
	std::string projectDirectory = "\0";
	splitPath = strtok_s(buffer, FOLDER_DELIM, &context);
	int currCount = 0;
	while (splitPath != NULL){
		if (strrchr(splitPath, '.')){
			break;
		}
		if (currCount){
			projectDirectory += FOLDER_DELIM;
		}
		projectDirectory += std::string(splitPath);
		splitPath = strtok_s(NULL, FOLDER_DELIM, &context);
		currCount++;
	}
	return projectDirectory;
#endif
	return ".";
}
