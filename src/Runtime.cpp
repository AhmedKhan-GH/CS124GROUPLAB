#include "Runtime.hpp"

Runtime::Runtime() : run_state(true), file_name("demo.txt"), clear_next_enter(false) {}

void Runtime::addCommand(const std::string& key, Command code)		//add new command lambda to map
{
	command_map.insert({key, code});
}

std::string Runtime::stringInput()
{
	std::string input;
	bool verified = false;
	do
	{
		std::getline(std::cin, input, '\n');
		if(input.length() == 0)
		{
			std::cout <<
		 	std::endl << "blank, try again: ";
		}
		else
		{
			verified = true;
		}
	}while(!verified);
	return input;
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


//function signature of void return time and string vector param

void Runtime::addLambdas()
{
	//displays a list of all available commands when called
	auto helpLambda = [](const std::vector<std::string>& params)
	{
		std::cout <<
		std::endl << "help: lists available commands" <<
		std::endl << "quit: terminates the program" <<
		std::endl << "info: credits and info about program" <<
		std::endl <<	
		std::endl << "makemap <name>: create new waypoint space" <<
		std::endl << "loadmap <filename.txt>: load from file" <<
		std::endl << "showmap: print waypoint space to console" <<
		std::endl << "savemap <filename.txt>: save to file" <<
		std::endl << "dletmap: delete current waypoint space" <<
		std::endl << "exitmap: exits waypoint space visualizer" <<		
		std::endl;
	};
	addCommand("help", helpLambda);

	//COMPLETE
	auto quitLambda = [this](const std::vector<std::string>& params)
	{
		this->run_state = false;
		std::cout <<
		std::endl << "Thank you for using Eagle Eye" <<
		std::endl;
	};
	addCommand("quit", quitLambda);

	auto infoLambda = [](const std::vector<std::string>& params)
	{
		std::cout << 
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

	auto loadMapLambda = [this](const std::vector<std::string>& params)
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
	addCommand("loadmap", loadMapLambda);

	auto saveMapLambda = [this](const std::vector<std::string>& params)
	{
		if(FileManager::doesFileExist(params[0]))
		{
			std::cout <<
			std::endl << "file already exists, overwrite? ";
			if(!this->booleanQuestion()) //user says no, if statement triggers and lambda returns
			{
				return;
			}
			//have file manager write to existing file
		}
		
		//savefile <filename.txt> will give filemanager class data
		//from wayspace class and print it to a file, savefile
		//should check if a file exists and ask if the user wants
		//to overrwrite the data
	};
	addCommand("savemap", saveMapLambda);

	auto exitMapLambda = [this](const std::vector<std::string>& params)
	{
		//throwaway command to allow user to exit map interface without any
		//unwanted functionality being invoked
	};
	addCommand("exitmap", exitMapLambda);

	auto showMapLambda = [this](const std::vector<std::string>& params)
	{
		if(!waypoint_space.getActive())
		{
			std::cout <<
			std::endl << "no map in system, use makemap <name>" <<
			std::endl << "or loadmap <filename.txt> to start" <<
			std::endl;
			return;
		}
		
		//this is test code
	
		this->clear_next_enter = true;
		Wayspace space; //there should be a wayspace pointer in runtime, and if showmap or savemap is called when it equals nullptr, then the user is informed they have not created a waypoint space yet
				
		space.fillSpace(char(45)); //rename to fillspace and printspace
		space.printSpace();
	};
	addCommand("showmap", showMapLambda);

	auto makeMapLambda = [this](const std::vector<std::string>& params)
	{
		if(params.empty())
		{	
			std::cout << 
			std::endl << "failed to provide map name" <<
			std::endl;
			return;
		}
		this->waypoint_space.activate();
		this->waypoint_space.setName(params[0]);
		std::cout <<
		std::endl << "'" << params[0] << "' successfully created" <<
		std::endl;
	};
	addCommand("makemap", makeMapLambda);


	auto deleteMapLambda = [this](const std::vector<std::string>& params)
	{
		if(!this->waypoint_space.getActive())
		{
			std::cout <<
			std::endl << "there is no map to delete" <<
			std::endl;
		}
		std::cout <<
		std::endl << "this is irreversible, proceed? "; 
		if(this->booleanQuestion())
		{
			std::cout <<
			std::endl << "'" << this->waypoint_space.getName() << "' successfully deleted" <<
			std::endl;
		
			this->waypoint_space.deactivate();
		}
	};
	addCommand("dletmap", deleteMapLambda);

	/*	
	//preferable to put this in a sort.cpp class and just call it from here
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
	*/
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
