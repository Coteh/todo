#include "FileIO.h"

std::string FileIO::readFile(std::string _filePath){
	FILE* todoFile;
#ifdef _WIN32
	errno_t err;
	if (err = fopen_s(&todoFile, _filePath.c_str(), "r") != 0){
		printf("File could not be opened!\n");
		return "";
	}
#else
	todoFile = fopen(_filePath.c_str(), "r");
	if (todoFile == nullptr){
		printf("File could not be opened!\n");
		return "";
	}
#endif
	std::string todoContents;
	bool fileRead = false;
	while (!fileRead){
		char chunk[100] = "";
		if (fgets(chunk, 100, todoFile) == NULL){
			//end of file
			fileRead = true;
		}
		todoContents += chunk;
	}
	fclose(todoFile);
	return todoContents;
}

void FileIO::writeFile(std::string _filePath, std::string _fileContents, FileWriteType _fileWriteType){
	FILE* todoFile;
	const char* writeCode = (_fileWriteType == FileWriteType::APPEND) ? "a" : "w";
#ifdef _WIN32
	errno_t err;
	if (err = fopen_s(&todoFile, _filePath.c_str(), writeCode) != 0){
		printf("File could not be opened!\n");
		return;
	}
#else
	todoFile = fopen(_filePath.c_str(), writeCode);
	if (todoFile == nullptr){
		printf("File could not be opened!\n");
		return;
	}
#endif
	fputs(_fileContents.c_str(), todoFile);
	fclose(todoFile);
}
