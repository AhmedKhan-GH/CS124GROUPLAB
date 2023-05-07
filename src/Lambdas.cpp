#include "Runtime.hpp"

//function signature of void return time and string vector param

void Runtime::addLambdas()
{

auto listPointsLambda = [this](const std::vector<std::string>& params)
{
	if(!space.getActive()) {std::cout << std::endl << "there is no map in system" << std::endl; return;}
	space.listWaypoints();
};
addCommand("listpoints", listPointsLambda);

auto viewPointLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()){std::cout << std::endl << "there is no map in system" << std::endl; return;}
	if(params.empty()){std::cout << std::endl << "no parameters provided" << std::endl; return;}
	if(!space.checkExistName(params[0])){std::cout << std::endl << "given point doesn't exist" << std::endl;}
	
	space.viewPoint(params[0]);
}; addCommand("viewpoint", viewPointLambda);

auto setScaleLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()){std::cout << std::endl << "there is no map in system" << std::endl; return;} //checking if map is active
	if(space.getScaleSet()){std::cout << std::endl << "scale has already been set" << std::endl; return;} //checking if scale has already been set
	if(params.empty()){std::cout << std::endl << "no parameters provided" << std::endl; return;} //checking if parameters have been provided
	if(params[0].find_first_not_of("-0123456789") != std::string::npos) //checking if numerial parameter is non numeric
	{std::cout <<std::endl << "scale factor not numeric" << std::endl; return;} 
	if(stoi(params[0]) <= 0){std::cout << std::endl << "scale factor zero or negative " << std::endl; return;} //checking if scale factor is negative
	if(params.size() < 2) {std::cout << std::endl << "not all parameters provided" << std::endl; return;} //checking if parameters are missing
	this->space.setScale(stoi(params[0])); //setting scale
	this->space.setUnit(params[1]);	//setting scale unit
	std::cout << std::endl << "grid set to " << params[0] << " " << params[1] << "(s) scale" << std::endl; //indication of success to user
}; addCommand("setscale", setScaleLambda);

//displays a list of all available commands when called
auto helpLambda = [](const std::vector<std::string>& params){
	std::cout <<
	std::endl << "help: lists available commands" <<
	std::endl << "quit: terminates the program" <<
	std::endl << "info: credits and info about program" <<
	std::endl << "clear: removes history from terminal" <<
	std::endl <<
	std::endl << "makemap <name>: create new waypoint space" <<
	std::endl << "loadmap <filename.txt>: load from file" <<
	std::endl << "showmap: print waypoint space to console" <<
	std::endl << "savemap <filename.txt>: save to file" <<
	std::endl << "dletmap: delete current waypoint space" <<
	std::endl << "exitmap: exit waypoint space visualizer" <<
	std::endl << "setscale <number> <name>: set distance scale" <<
	std::endl <<
	std::endl << "addpoint <name> <y> <x>: add waypoint to map" <<

	std::endl;
}; addCommand("help", helpLambda);

//sets run state to false causing event handler loop to terminate on next cycle
auto quitLambda = [this](const std::vector<std::string>& params){
	this->run_state = false;
	std::cout << std::endl << "Thank you for using Eagle Eye!" << std::endl;
}; addCommand("quit", quitLambda);

auto infoLambda = [](const std::vector<std::string>& params){
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
}; addCommand("info", infoLambda);

//calls cstdlib clear to empty the console
auto clearLambda = [this](const std::vector<std::string>& params) {
	system("clear");
}; addCommand("clear", clearLambda);

auto loadMapLambda = [this](const std::vector<std::string>& params)
{
	if(params.empty()){std::cout << std::endl << "no filename provided" << std::endl; return;}
	if(!FileManager::doesFileExist(params[0])){std::cout << std::endl << "file does not exist" << std::endl; return;}
	if(params[0].substr(params[0].length() - 4) != ".txt"){std::cout << std::endl << "file is not a '.txt'" << std::endl;return;}
	if(!FileManager::doesFileHaveMetadata(params[0])){std::cout << std::endl << "file is not formatted" << std::endl; return;}
	this->file_name = params[0];
}; addCommand("loadmap", loadMapLambda);

auto saveMapLambda = [this](const std::vector<std::string>& params)
{
	if(FileManager::doesFileExist(params[0])) {std::cout << std::endl << "are you sure you want to overwrite " << params[0] << "? ";
		if(!this->booleanQuestion()) //user says no, if statement triggers and lambda returns
		{
			std::cout << std::endl << "file saving cancelled" << std::endl;
			return;
		}
	}

	//savefile <filename.txt> will give filemanager class data
	//from wayspace class and print it to a file, savefile
	//should check if a file exists and ask if the user wants
	//to overrwrite the data
}; addCommand("savemap", saveMapLambda);

auto exitMapLambda = [this](const std::vector<std::string>& params) { /* throwaway command to allow user to exit map interface without any other action */ 
}; addCommand("exitmap", exitMapLambda);

auto showMapLambda = [this](const std::vector<std::string>& params)
{
	if(!space.getActive()) 
	{	std::cout << std::endl << "no map in system, use 'makemap <name>'" << 
		std::endl << "or 'loadmap <filename.txt>' to start" << std::endl; return;}

	if(!space.getScaleSet()) 
	{	std::cout << std::endl << "scale has not been set" <<
		std::endl << "use 'setscale <number> <name>' to set" << std::endl; return;}

	this->clear_next_enter = true;
	space.fillSpace(char(46));

	//plot waypoints and legend
	space.plotPoints();

	space.plotCompass(); space.plotHeaders(); space.plotScale(); 
	//this is plotted last as it overrwrites anything under it

	space.printSpace();
};
addCommand("showmap", showMapLambda);

auto makeMapLambda = [this](const std::vector<std::string>& params)
{
	if(params.empty()){std::cout << std::endl << "map name not provided" << std::endl; return;}
	this->space.activate();
	this->space.setName(params[0]);
	std::cout << std::endl << "'" << params[0] << "' successfully created" <<
	std::endl << "use 'setscale <number> <name>' next" << std::endl;
}; addCommand("makemap", makeMapLambda);

auto deleteMapLambda = [this](const std::vector<std::string>& params)
{
	if(!this->space.getActive()){std::cout << std::endl << "there is no map in the system" << std::endl; return;}
	std::cout << std::endl << "are you sure you want to delete " << space.getName() << "? ";
	if(this->booleanQuestion())
	{	std::cout << std::endl << "'" << this->space.getName() << "' successfully deleted" << std::endl;
		this->space.deactivate();}
}; addCommand("dletmap", deleteMapLambda);

auto addWaypointLambda = [this](const std::vector<std::string>& params)
{
	if(!space.getActive()){std::cout << std::endl << "there is no map in system" << std::endl; return;}
	if(params.empty())
	{	std::cout << std::endl << "no parameters provided" <<
		std::endl << "addpoint <name> <ypos> <xpos>" << std::endl; return;}
	if(params.size() < 3)
	{	std::cout << std::endl << "not all parameters provided" <<
		std::endl << "addpoint <name> <ypos> <xpos>" << std::endl; return;}
	if(params[1].find_first_not_of("-0123456789") != std::string::npos)
	{std::cout << std::endl << "y coordinate not numeric" << std::endl; return;}
	if(params[2].find_first_not_of("-0123456789") != std::string::npos)
	{std::cout << std::endl << "x coordinate not numeric" << std::endl;return;}
	int tempy = std::stoi(params[1]);
	int tempx = std::stoi(params[2]);
	if(tempy > 21 || tempy < 0){std::cout << std::endl << "y coordinate out of bounds" << std::endl; return;}
	if(tempx > 79 || tempx < 0){std::cout << std::endl << "x coordinate out of bounds" << std::endl; return;}
	if(space.checkExistName(params[0])) {std::cout << std::endl << "'" << params[0] << "' already exists in map" << std::endl; return;}
	space.addWaypoint(tempy, tempx, params[0]);
	std::cout << std::endl << "added waypoint '" << params[0] << "' to <" << tempy << "," << tempx << ">" << std::endl;
};
addCommand("addpoint", addWaypointLambda);

/*
	preferable to put this in a sort.cpp class and just call it from here
	test this
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

