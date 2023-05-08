#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#include <fstream>
#include <iostream>
class FileManager
{
public:
	static bool doesFileExist(std::string file_name);
	static bool doesFileHaveMetadata(std::string file_name);
private:
};

#endif //FILEMANAGER_HPP
