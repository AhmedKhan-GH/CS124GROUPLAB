#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <cstdlib> //for console clear commands
#include <sstream> //for command parsing


#include "Wayspace.hpp"
#include <iostream>
#include <unordered_map>
#include <functional>

using Command = std::function<void(const std::vector<std::string>&)>;

class Runtime
{
public:
	Runtime();
	void run();
	
	void invalidCommandMessage();
	void illegalCharacterMessage();
	void greetMessage();
	
	std::string stringInput();
	bool booleanQuestion();
	
	void addCommand(const std::string& key, Command code);
	void addLambdas();
private:
	Wayspace space;

	std::string file_name;	
	bool run_state;
	bool show_map;
	
	std::unordered_map<std::string, Command> command_map;
};

#endif //RUNTIME_HPP
