#include "Runtime.hpp"

//function signature of void return time and string vector param

void Runtime::addLambdas()
{

auto pathfindLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()){std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;}
	if(params.empty()){std::cout << std::endl << "no parameters provided, use 'help'" << std::endl; return;}
	if(params.size() < 2){std::cout << std::endl << "not all parameters provided, use 'help'" << std::endl; return;}
	if(!space.checkExistName(params[0])){std::cout << std::endl << "start point doesn't exist" << std::endl; return;}
	if(!space.checkExistName(params[1])){std::cout << std::endl << "end point doesn't exist" << std::endl; return;}
	if(params[0] == params[1]){std::cout << std::endl << "cannot find path to itself" << std::endl; return;}
	space.findPath(params[0], params[1]);
}; addCommand("pathfind", pathfindLambda);

auto distanceFindLamba = [this](const std::vector<std::string>& params)
{
	if(!space.getActive()){std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;}
	if(params.empty()){std::cout << std::endl << "no parameters provided, use 'help'" << std::endl; return;}
	if(params.size() < 2){std::cout << std::endl << "not all parameters provided, use 'help'" << std::endl; return;}
	if(!space.checkExistName(params[0])){std::cout << std::endl << "start point doesn't exist" << std::endl; return;}
	if(!space.checkExistName(params[1])){std::cout << std::endl << "end point doesn't exist" << std::endl; return;}
	if(params[0] == params[1]){std::cout << std::endl << "cannot find distance to itself" << std::endl; return;}

	std::cout << std::endl << "dist from '" << params[0] << "' to '" << params[1] << "': " <<
	space.findDist(params[0], params[1])*space.getScale() << " " << space.getUnit() << "(s)"  << std::endl;
}; addCommand("distfind", distanceFindLamba);


auto undoAddLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()){std::cout << std::endl << "no map in system, use 'makemap <name>'"<< std::endl; return;}
	space.undoAdd();
}; addCommand("undoadd", undoAddLambda);

auto removeFeatureLambda = [this](const std::vector<std::string>& params)
{
	if(!space.getActive()){std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;}
	if(params.empty()){std::cout << std::endl << "no parameters provided, use 'help'" << std::endl; return;}
	if(!space.checkExistName(params[0])){std::cout << std::endl << "given point doesn't exist" << std::endl; return;}
	if(params.size() < 2){std::cout << std::endl << "not all parameters provided, use 'help'" << std::endl; return;}
	space.pullFeature(params[0], params[1]);
	std::cout << std::endl << "removed '" << params[1] << "' from '" << params[0] << "'" << std::endl;
}; addCommand("rmvfeat", removeFeatureLambda);

auto listPointsLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()) {std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;}
	space.listPoints();
}; addCommand("listpoints", listPointsLambda);

auto viewPointLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()){std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;}
	if(params.empty()){std::cout << std::endl << "no parameters provided, use 'help'"<< std::endl; return;}
	if(!space.checkExistName(params[0])){std::cout << std::endl << "given point doesn't exist" << std::endl; return; }
	space.viewPoint(params[0]);
}; addCommand("viewpoint", viewPointLambda);

auto addFeatureLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()){std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;}
	if(params.empty()){std::cout << std::endl << "no parameters provided, use 'help'" << std::endl; return;}
	if(!space.checkExistName(params[0])){std::cout << std::endl << "given point doesn't exist" << std::endl; return;}
	if(params.size() < 3){std::cout << std::endl << "not all parameters provided, use 'help'" << std::endl; return;}
	if(params[2].find_first_not_of(".-0123456789") != std::string::npos)
	{std::cout << std::endl << "metric not numeric" << std::endl; return;}
	double temp = std::stod(params[2]);
	space.pushFeature(params[0], params[1], temp);
	std::cout << std::endl << "added '" << params[1] << ": " << temp << "' to '" << params[0] << "'" << std::endl;
}; addCommand("addfeat", addFeatureLambda);

auto setScaleLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()){std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;} //checking if map is active
	if(space.getScaleSet()){std::cout << std::endl << "scale has already been set" << std::endl; return;} //checking if scale has already been set
	if(params.empty()){std::cout << std::endl << "no parameters provided, use 'help'" << std::endl; return;} //checking if parameters have been provided
	if(params[0].find_first_not_of("-0123456789") != std::string::npos) //checking if numerial parameter is non numeric
	{std::cout << std::endl << "scale factor not numeric" << std::endl; return;} 
	if(stoi(params[0]) <= 0){std::cout << std::endl << "scale factor zero or negative " << std::endl; return;} //checking if scale factor is negative
	if(params.size() < 2) {std::cout << std::endl << "not all parameters provided, use 'help'" << std::endl; return;} //checking if parameters are missing
	this->space.setScale(stoi(params[0])); //setting scale
	this->space.setUnit(params[1]);	//setting scale unit
	std::cout << std::endl << "grid unit set to " << params[0] << " " << params[1] << "(s)" << std::endl; //indication of success to user
}; addCommand("setscale", setScaleLambda);

//displays a list of all available commands when called
auto helpLambda = [](const std::vector<std::string>& params){
	std::cout <<
	std::endl << "help: lists all available commands and their params" <<
	std::endl << "quit: terminates the program at any point of running" <<
	std::endl << "info: information about program and developer credits" <<
	std::endl << "clear: clears all command history from the terminal" <<
	std::endl <<
	std::endl << "makemap <name>: create a new waypoint map" <<
	std::endl << "showmap: print waypoint map to console" <<
	std::endl << "exitmap: exit waypoint map visualizer" <<
	std::endl << "setscale <number> <name>: set map distance scale" <<
	std::endl <<
	std::endl << "addpoint <name> <y> <x>: add given waypoint to map" <<
	std::endl << "undoadd: remove instance of add back to last filesave" <<
	std::endl << "addfeat <name> <feature> <number>: add metric to waypoint" <<
	std::endl << "rmvfeat <name> <feature>: remove metric to waypoint" <<
	std::endl << "rankfeat <feature>: rank all waypoints with given feature" <<
	std::endl << "viewpoint <name>: list coord and all metrics of a point" <<

	std::endl << "pathfind <name1> <name2>: potential (not optimal) path" <<
	std::endl << "distfind <name1> <name2>: direct distance between points" <<

	std::endl;
}; addCommand("help", helpLambda);

auto rankFeatureLambda = [this](const std::vector<std::string>& params){
	if(!space.getActive()){std::cout << std::endl << "no map in system" << std::endl;}
	if(params.empty()){std::cout << std::endl <<  "no parameters provided, use 'help'" << std::endl;}
	space.rankFeatures(params[0]);
}; addCommand("rankfeat", rankFeatureLambda);

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
	std::endl << "intended for forest management orgs" <<
	std::endl <<
	std::endl << "Developed by Ahmed Khan, Adam Freed," <<
	std::endl << "and Gavin Silva. Ohlone College CS-124" <<
	std::endl;
}; addCommand("info", infoLambda);

//calls cstdlib clear to empty the console
auto clearLambda = [this](const std::vector<std::string>& params) {
	system("clear");
}; addCommand("clear", clearLambda);

/*
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
	if(FileManager::doesFileExist(params[0])) {std::cout << std::endl << "are you sure you want to overwrite '" << params[0] << "'? ";
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
*/

auto exitMapLambda = [this](const std::vector<std::string>& params) {
	this->show_map = false;
	system("clear");
	 /* throwaway command to allow user to exit map interface without any other action */ 
}; addCommand("exitmap", exitMapLambda);

auto showMapLambda = [this](const std::vector<std::string>& params)
{
	if(!space.getActive()) {std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;}

	if(!space.getScaleSet()) 
	{	std::cout << std::endl << "scale has not been set" <<
		std::endl << "use 'setscale <number> <name>' to set" << std::endl; return;}

	this->show_map = true;
	space.fillSpace(char(46));

	//plot waypoints and legend
	space.plotPoints();

	space.plotElements();
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
	std::endl << "use 'setscale <number> <unit>' next" << std::endl;
}; addCommand("makemap", makeMapLambda);


auto addWaypointLambda = [this](const std::vector<std::string>& params)
{
	if(!space.getActive()){std::cout << std::endl << "no map in system, use 'makemap <name>'" << std::endl; return;}
	if(params.empty())
	{	std::cout << std::endl << "no parameters provided, use 'help'" <<
		std::endl << "addpoint <name> <ypos> <xpos>" << std::endl; return;}
	if(params.size() < 3)
	{	std::cout << std::endl << "not all parameters provided, use 'help'"<<
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
	space.addPoint(tempy, tempx, params[0]);
	std::cout << std::endl << "added waypoint '" << params[0] << "' to <" << tempy << "," << tempx << ">" << std::endl;
};
addCommand("addpoint", addWaypointLambda);

}

