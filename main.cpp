#include "wxWidgets-3.2.2.1/include/wx/wx.h"

//Name: main.cpp
//Purpose: wxwidgets learning
//Author: Ahmed Khan

//application class declaration
class MyApp : public wxApp
{
public:

	//virtual OnInit which overrides wx's internal implementation
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
	//constructor
	MyFrame(const wxString& title);

	//event handlers
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

private:
	//this class handles events
	DECLARE_EVENT_TABLE()
};


//implements MyApp& GetApp()
DECLARE_APP(MyApp)

//give wxwidgets the means to create myapp object
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	//create application window object
	MyFrame* frame = new MyFrame("Minimal wxWidgets App");
	//show window
	frame->Show(true);
	//start event loop
	return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
	EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
END_EVENT_TABLE()

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Printf("Hello and welcome to %s", wxVERSION_STRING);
	wxMessageBox(msg, "AboutMinimal", wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
	//destroy the frame
	Close();
}

//#include "picture.xpm"

MyFrame::MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
{
	//SetIcon(wxIcon(file_xpm));

	wxMenuBar* menuBar = new wxMenuBar();
	//file, edit, view, tools, help
			
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
	menuBar->Append(fileMenu, "&File");
	
	wxMenu* editMenu = new wxMenu;
	//add elements to edit dropdown
	menuBar->Append(editMenu, "&Edit");

	wxMenu* viewMenu = new wxMenu;
	//add elements to view dropdown
	menuBar->Append(viewMenu, "&View");

	wxMenu* toolsMenu = new wxMenu;
	//add elements to tool dropdown
	menuBar->Append(toolsMenu, "&Tools");

	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, "&About....\tF1", "Show about dialog");
	menuBar->Append(helpMenu, "&Help");
	
	SetMenuBar(menuBar);

	CreateStatusBar(2);
	SetStatusText("Welcome to wxWidgets!");
}
