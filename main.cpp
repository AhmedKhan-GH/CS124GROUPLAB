#include <wx/wx.h>
#include <wx/image.h>
#include <wx/statbmp.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);
};

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("Basic wxWidgets Window");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480)) {
    
    // Initialize the image handler for JPEG files
    wxInitAllImageHandlers();

    // Load the JPG image
    wxImage image;
    bool isLoaded = image.LoadFile("../jsc2016e090606.jpg", wxBITMAP_TYPE_JPEG);
    if (!isLoaded) {
        wxMessageBox("Failed to load the image", "Error", wxICON_ERROR);
        return;
    }

    // Create a static bitmap and set the image
    wxStaticBitmap* staticBitmap = new wxStaticBitmap(this, wxID_ANY, wxBitmap(image));

    // Center the window on the screen
    Centre();
}

IMPLEMENT_APP(MyApp);