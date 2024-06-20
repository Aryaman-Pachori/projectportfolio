#include <iostream>
#include <string>
#include "FreeImage.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#define MAINPROGRAM

#include "variables.h"
#include "Scene.h"
#include "readfile.h"

using namespace std;
using namespace glm;

Scene* scene;

int main(int argc, char* argv[]) {

    cout << "Number of Arguments " << argc << endl;

    // Loads the global variables
    scene = new Scene();
    
    readfile(argv[1]);

    cout << "Done Reading File" << endl;
    cout << "=============================" << endl;
    
    scene->init();
    
    scene->renderImage();

}