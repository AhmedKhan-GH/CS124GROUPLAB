#include "FileManager.hpp"

bool FileManager::doesFileExist(std::string file_name)
{
	bool exists;
	std::ifstream file;
	file.open(file_name);
	exists = file.good();
	file.close();
	return exists;
}

bool FileManager::doesFileHaveMetadata(std::string file_name)
{
	return false;
	//TODO
}
