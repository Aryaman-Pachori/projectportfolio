// This class is done.

#include <string>
#include <glm/glm.hpp>
#include <iostream>
#include "FreeImage.h"

#include "Film.h"
#include "variables.h"
#include "Color.h"

using namespace std;
using namespace glm;

Film::Film() {
    // Constructor
    pixels = vector<vector<Color>>(width, vector<Color>(height, Color(0,0,0)));

}

void Film::addPixelColor(int x, int y, Color color) {
    // Be careful with how the format is saved and pixel coordinates input to avoid Segmentation Fault
    pixels[y][x] = color;
}

void Film::saveImage(string fname) {

    FreeImage_Initialise();
    RGBQUAD color;

    FIBITMAP * bitmap  = FreeImage_Allocate(width, height, 24);
    if (!bitmap) {
        exit(1);
    }

    for (int i = 0; i < width; i++) {
        // cout << "Percent Done: " << (i / (float)width) * 100 << "%\r" << endl;

        for (int j = 0; j < height; j++) {
            // Multiply by 255 to convert from 0-1 to 0-255
            color.rgbRed = pixels[i][j].getR() * 255;
            color.rgbGreen = pixels[i][j].getG() * 255;
            color.rgbBlue = pixels[i][j].getB() * 255;

            FreeImage_SetPixelColor(bitmap, i, j, &color);
        }
    }

    cout << "Done Rendering Image" << endl;

    FreeImage_Save(FIF_PNG, bitmap, fname.c_str(), 0);

    cout << "Image saved at " << fname << endl;


    FreeImage_DeInitialise();    

}
    