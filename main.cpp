#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <string>

struct PPMImage {
    unsigned int width;
    unsigned int height;
    unsigned int max_color;
    std::vector<unsigned char> data;
};

std::unique_ptr<PPMImage> load_ppm(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return nullptr;
    }

    std::unique_ptr<PPMImage> image = std::make_unique<PPMImage>();
    std::string line;

    // Read magic number and ensure it is P6
    std::getline(file, line);
    if (line != "P6") {
        std::cerr << "Invalid PPM format. Expected P6." << std::endl;
        return nullptr;
    }

    // Read width, height, and max color
    while (std::getline(file, line)) {
        if (line[0] == '#') continue;  // Skip comments
        std::stringstream ss(line);
        ss >> image->width >> image->height >> image->max_color;
        break;
    }

    // Ignore single whitespace character
    file.ignore(1);

    // Read pixel data
    size_t size = image->width * image->height * 3;
    image->data.resize(size);
    file.read(reinterpret_cast<char *>(image->data.data()), size);

    return image;
}

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;

    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        std::cerr << "Cannot open display" << std::endl;
        return 1;
    }

    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 640, 480, 1,
                                  BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    auto image = load_ppm("jsc2016e090606.ppm");
    if (!image) {
        std::cerr << "Error loading image" << std::endl;
        XCloseDisplay(display);
        return 1;
    }

    XImage *ximage = XCreateImage(display, DefaultVisual(display, screen), 24, ZPixmap, 0,
                                  reinterpret_cast<char *>(image->data.data()), image->width, image->height, 32, 0);

    bool running = true;
    while (running) {
        XNextEvent(display, &event);

        if (event.type == Expose) {
            XPutImage(display, window, DefaultGC(display, screen), ximage, 0, 0, 0, 0,
                      image->width, image->height);
	        } else if (event.type == KeyPress) {
            running = false;
        }
    }

    XDestroyImage(ximage);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}

