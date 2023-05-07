#include "Runtime.hpp"

//runtime constructor intializing booleans
Runtime::Runtime() : run_state(true), clear_next_enter(false), file_name("") {}

//add new command lambda to map
void Runtime::addCommand(const std::string& key, Command code)
{
	command_map.insert({key, code});
}

//this function takes a string input and verifies input isnt empty
std::string Runtime::stringInput()
{
	std::string input;
	bool verified = false;
	do
	{
		//terminating at enter
		std::getline(std::cin, input, '\n');
		if(input.length() == 0) //if empty, reprompt
		{
			std::cout <<
		 	std::endl << "blank, try again: ";
		}
		else
		{
			verified = true; //exit if successful
		}
	}while(!verified);
	return input;
}

//this function uses string_input to return a bool based on user input
bool Runtime::booleanQuestion()
{
	bool verified = false; //determines if question
			       //loops based on invalid answer
	bool answer; //value of the answer input by the user

	std::string input; //single variable needed to store
			   //input even over repeated iterations
			   //of prompt
	std::cout << "[Y/n]: "; //prompt for user for valid characters,

	do{
		input = stringInput(); //getting string from
					//validated input function
		if(input == "y" || input == "Y") //checking for yes and setting bools
		{
			verified = true;
			answer = true;
		}
		else if(input == "n" || input == "N") //checking for no and
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

void Runtime::greetMessage()						//greeting user for first time
{
	std::cout <<
	std::endl << "Welcome to Eagle Eye." << 
	std::endl << 
	std::endl << "Type 'help' for list of commands" <<
	std::endl << "Type 'quit' to terminate program" <<
	std::endl;
}

void Runtime::invalidCommandMessage()					//informing user of invalid command
{
	std::cout <<
	std::endl << "invalid command, try again" <<
	std::endl;
}

void Runtime::run()
{
	addLambdas(); 							//initializing map of events
	greetMessage(); 						//greet user
	while(run_state)
	{
		std::cout << std::endl << "> "; 			//prompt for input
		std::string input;
		std::getline(std::cin, input);
		std::istringstream iss(input);

		std::string command_token;				//command token
		iss >> command_token;
		
		std::vector<std::string> param_tokens;			//parameter tokens
		std::string parsed_param;
		
		if(clear_next_enter) 					//clear condition (called by showmap)
		{
			system("clear");
			clear_next_enter = false;
		}

		while(iss >> parsed_param)				//parsing parameter tokens
		{
			param_tokens.push_back(parsed_param);
		}
		
		if(!command_map.count(command_token))			//invalid command token message
		{
			invalidCommandMessage();
		}
		else
		{
			command_map[command_token](param_tokens);	//execution of event lambda
		}
	}
}
