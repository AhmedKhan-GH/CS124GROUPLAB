#include <iostream>
#include <fstream>
#include <sstream>
#include <X11/Xlib.h>

struct PPM {
    int width;
    int height;
    int maxColor;
    unsigned char* data;
};

bool readPPM(const std::string& filename, PPM& ppm) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string magic;
    file >> magic;
    if (magic != "P6") {
        std::cerr << "Invalid PPM format" << std::endl;
        return false;
    }

    file >> ppm.width >> ppm.height >> ppm.maxColor;
    file.ignore();

    int dataSize = ppm.width * ppm.height * 3;
    ppm.data = new unsigned char[dataSize];
    file.read(reinterpret_cast<char*>(ppm.data), dataSize);
    return true;
}

int main() {
    std::string ppmFile = "jsc2016e090606.ppm";
    PPM ppm;
    if (!readPPM(ppmFile, ppm)) {
        return 1;
    }

    Display* display = XOpenDisplay(nullptr);
    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);

    XSetWindowAttributes attributes;
    attributes.background_pixel = WhitePixel(display, screen);

    Window window = XCreateWindow(display, root, 0, 0, 640, 480, 0,
                                  CopyFromParent, InputOutput, CopyFromParent,
                                  CWBackPixel, &attributes);
    XStoreName(display, window, "PPM Viewer");
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    GC gc = XCreateGC(display, window, 0, nullptr);

    XImage* image = XCreateImage(display, CopyFromParent, 24, ZPixmap, 0,
                                 reinterpret_cast<char*>(ppm.data), ppm.width,
                                 ppm.height, 32, 0);

    bool done = false;
    while (!done) {
        XEvent event;
        XNextEvent(display, &event);

        switch (event.type) {
            case Expose:
                XPutImage(display, window, gc, image, 0, 0, 0, 0, ppm.width, ppm.height);
                break;
            case KeyPress:
                done = true;
                break;
        }
    }

    XFree(image);
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    delete[] ppm.data;

    return 0;
}
