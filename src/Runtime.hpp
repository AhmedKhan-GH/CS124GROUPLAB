#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <cstdlib> //for console clear commands
#include <sstream> //for command parsing

#include "FileManager.hpp"
#include "Wayspace.hpp"
#include <iostream>
#include <unordered_map>
#include <functional>

using Command = std::function<void(const std::vector<std::string>&)>;

class Runtime
{
public:
	bool booleanQuestion();
	std::string stringInput();
	Runtime();
	void greetMessage();
	void invalidCommandMessage();
	
	void run();
	void addCommand(const std::string& key, Command code);
	void addLambdas();
private:
	FileManager file_manager;
	Wayspace space;

	std::string file_name;	
	bool clear_next_enter;
	bool run_state;
	std::unordered_map<std::string, Command> command_map;
};

#endif //RUNTIME_HPP
