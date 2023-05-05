#include "Runtime.hpp"

Runtime::Runtime() : run_state(true), file_name("demo.txt"){}

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
		std::endl << "loadfile <filename.txt>: loads file to program" << 
		std::endl;
	};
	addCommand("help", helpLambda);

	auto exitLambda = [this](const std::vector<std::string>& params)
	{
		this->run_state = false;
		std::cout <<
		std::endl << "Thank you for using Eagle Eye" <<
		std::endl;
	};
	addCommand("exit", exitLambda);

	auto infoLambda = [](const std::vector<std::string>& params)
	{
		std::cout << 
		std::endl << "Thank you for choosing Eagle Eye!" <<
		std::endl << "Eagle Eye is a command line based" <<
		std::endl << "waypoint mapper and editor that lets" <<
		std::endl << "you keep track of points of interest" <<
		std::endl << "in geographical space. Eagle Eye is" <<
		std::endl << "specialized for forest management" << 
		std::endl <<
		std::endl << "Developed by Ahmed Khan, Adam Freed," <<
		std::endl << "and Gavin Silva. Ohlone College CS-124" <<
		std::endl;
	};
	addCommand("info", infoLambda);

	auto loadFileLambda = [this](const std::vector<std::string>& params)
	{
		if(params.empty())
		{
			std::cout << 
			std::endl << "No filename provided" << 
			std::endl;
			return;
		}
		if(!FileManager::doesFileExist(params[0]))
		{
			std::cout << 
			std::endl << "File does not exist" << 
			std::endl;
			return;
		}
		if(params[0].substr(params[0].length() - 4) != ".txt")
		{
			std::cout <<
			std::endl << "File is not a '.txt'" <<
			std::endl;
			return;
		}
		if(!FileManager::doesFileHaveMetadata(params[0]))
		{
			std::cout <<
			std::endl << "Invalid file format" <<
			std::endl;
			return;	
		}

		this->file_name = params[0];
	};
	addCommand("loadfile", loadFileLambda);

	auto saveFileLambda = [](const std::vector<std::string>& params)
	{

	};
	addCommand("savefile", saveFileLambda);

	auto newMapLambda = [](const std::vector<std::string>& params)
	{
		
	};
	addCommand("newmap", newMapLambda);


	auto openMapLambda = [](const std::vector<std::string>& params)
	{
	
		if(Geospace == nullptr)
	};
	addCommand("openmap", openMapLambda);
	
	//test this
	auto sortWaypointsLambda = [](const std::vector<std::string>& params)
	{
		if (Waypoint.empty()) return;

    		std::function<void(int, int)> quicksort;
    		quicksort = [&](int start, int end) 
    		{
        		if (start >= end) return;
        		int pivot = Waypoint[(start + end) / 2].get_feature(params[0]);
        		int i = start, j = end;
        		while (i <= j) 
			{
            			while (Waypoint[i].get_feature(params[0]) < pivot) i++;
            			while (Waypoint[j].get_feature(params[0]) > pivot) j--;
            			if (i <= j) 
				{
                			std::swap(Waypoint[i], Waypoint[j]);
                			i++; j--;
            			}
        		}
       		quicksort(start, j);
        	quicksort(i, end);
   	 	};
    	quicksort(0, Waypoint.size() - 1);
	};
	addCommand("sortwaypoints", sortWaypointsLambda);
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
	std::endl << "invalid command, try again" <<
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
