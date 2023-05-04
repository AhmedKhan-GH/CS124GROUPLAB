#include "Runtime.hpp"
#include "Waypoint.hpp"

Runtime::Runtime() : run_state(true), file_name("demo.txt"){}

void Runtime::addCommand(const std::string& key, Command code)
{
	command_map.insert({key, code});
}

//COMPLETE
//this function uses string_input to return a bool based
//on user input
bool Runtime::booleanQuestion()
{
	bool verified = false; //determines if question
			       //loops based on invalid answer
	bool answer; //value of the answer input by the user

	std::string input; //single variable needed to store
			   //input even over repeated iterations
			   //of prompt
	std::cout << "[y/n]: "; //prompt for user for valid characters,

	do{
		input = string_input(); //getting string from
					//validated input function
		if(input == "y") //checking for yes and setting bools
		{
			verified = true;
			answer = true;
		}
		else if(input == "n") //checking for no and
				      //setting bools
		{
			verified = true;
			answer = false;
		}
		else //informing and reprompting user
		     //in case of invalid input
		{
			std::cout << std::endl << "invalid, try again: ";
			verified = false;
		}
	}while(!verified); //prompt loop until a desired answer
			   //has been given

	return answer;
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
			std::endl << "no filename provided" << 
			std::endl;
			return;
		}
		if(!FileManager::doesFileExist(params[0]))
		{
			std::cout << 
			std::endl << "file does not exist" << 
			std::endl;
			return;
		}
		if(params[0].substr(params[0].length() - 4) != ".txt")
		{
			std::cout <<
			std::endl << "file is not a '.txt'" <<
			std::endl;
			return;
		}
		if(!FileManager::doesFileHaveMetadata(params[0]))
		{
			std::cout <<
			std::endl << "file is not formatted" <<
			std::endl;
			return;	
		}

		this->file_name = params[0];
	};
	addCommand("loadfile", loadFileLambda);

	auto saveFileLambda = [](const std::vector<std::string>& params)
	{
		if(FileManager::doesFileExist(params[0]))
		{
		
			std::cout <<
			std::endl << "file already exists, overwrite?";
			booleanQuestion();
		
			
			
			//boolquestion asking about overwriting old file
			//
		}
		
		//savefile <filename.txt> will give filemanager class data
		//from wayspace class and print it to a file, savefile
		//should check if a file exists and ask if the user wants
		//to overrwrite the data
	};
	addCommand("savefile", saveFileLambda);

	auto newMapLambda = [](const std::vector<std::string>& params)
	{
		
	};
	addCommand("newmap", newMapLambda);


	auto openMapLambda = [](const std::vector<std::string>& params)
	{
	
		
	};
	addCommand("openmap", openMapLambda);
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
