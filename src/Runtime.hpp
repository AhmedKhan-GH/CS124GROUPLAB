#ifndef RUNTIME_HPP
#define RUNTIME_HPP
#include "FileManager.hpp"
#include "Wayspace.hpp"
#include "Waypoint.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <sstream>
using Command = std::function<void(const std::vector<std::string>&)>;

class Runtime
{
public:

	Runtime();
	void greetMessage();
	void invalidCommandMessage();
	
	void run();
	void addCommand(const std::string& key, Command code);
	void addLambdas();
private:
	FileManager* file_manager;
	Wayspace* way_space;

	std::string file_name;	
	bool run_state;
	std::unordered_map<std::string, Command> command_map;
};

#endif //RUNTIME_HPP
