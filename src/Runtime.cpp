#include "Runtime.hpp"

Runtime::Runtime() : run_state(true){}

void Runtime::addCommand(const std::string& key, Command code)
{
	command_map.insert({key, code});
}

//function signature of void return time and string vector param

void Runtime::addLambdas()
{
	//the help lambda displays a list of all available commands when called
	auto helpLambda = [](const std::vector<std::string>& params)
	{
		std::cout <<
		std::endl << "help: lists available commands" <<
		std::endl << "exit: terminates the program" <<
		std::endl << "info: learn more about the program" <<
		std::endl;
	};
	addCommand("help", helpLambda);

	auto exitLambda = [this](const std::vector<std::string>& params)
	{
		this->run_state = false;
		std::cout <<
		std::endl << "Thank you for using Eagle Eye." <<
		std::endl;
	};
	addCommand("exit", exitLambda);

	auto infoLambda = [](const std::vector<std::string>& params)
	{
		std::cout << 
		std::endl << "Thank you for choosing our program." <<
		std::endl << "Eagle Eye is a command line based" <<
		std::endl << "waypoint mapper and  editor that lets" <<
		std::endl << "you keep track of points of interest in" <<
		std::endl << "a geographical space. Eagle Eye is" <<
		std::endl << "specialized towards forest management." << 
		std::endl <<
		std::endl << "Developed by Ahmed Khan, Gavin Silva," <<
		std::endl << "and Adam Freed from Ohlone College CS-124" <<
		std::endl;
	};
	addCommand("info", infoLambda);
}

void Runtime::greetMessage()
{
	std::cout <<
	std::endl << "Welcome to Eagle Eye." << 
	std::endl << 
	std::endl << "Type 'help' for list of commands" <<
	std::endl << "Type 'exit' to terminate program" <<
	std::endl;
}


void Runtime::invalidCommandMessage()
{
	std::cout <<
	std::endl << "invalid command, try again." <<
	std::endl;
}

void Runtime::run()
{
	addLambdas();
	greetMessage();
	while(run_state)
	{
		std::cout << std::endl << "> ";
		std::string input;
		std::getline(std::cin, input);
		std::istringstream iss(input);

		std::string command_token;
		iss >> command_token;
		
		std::vector<std::string> param_tokens;
		std::string parsed_param;
		
		while(iss >> parsed_param)
		{
			param_tokens.push_back(parsed_param);
		}
		
		if(!command_map.count(command_token))
		{
			invalidCommandMessage();
		}
		else
		{
			command_map[command_token](param_tokens);
		}
	}
}
