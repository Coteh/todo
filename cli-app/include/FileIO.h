#pragma once
#include <string>

namespace FileIO {
	enum FileWriteType {
		WRITE = 0,
		APPEND = 1
	};

	std::string readFile(std::string _filePath);
	void writeFile(std::string _filePath, std::string _fileContents, FileWriteType _fileWriteType);
}
