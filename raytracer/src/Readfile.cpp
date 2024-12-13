/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix 
// transformations for a stack (matransform) and to rightmultiply the 
// top of a stack.  These functions are given to aid in setting up the 
// transformations properly, and to use glm functions in the right way.  
// Their use is optional in your program.  
  

// The functions readvals and readfile do basic parsing.  You can of course 
// rewrite the parser as you wish, but we think this basic form might be 
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE. 
// Read the other parts to get a context of what is going on. 
  
/*****************************************************************************/

// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
// #include <GL/glew.h>
// #include <GL/glut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;
#include "variables.h"
#include "readfile.h"
#include "Geometry.h"
#include "Transform.h" 
#include "Light.h"


// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
// void matransform(stack<mat4> &transfstack, GLfloat* values) 
// {
//     mat4 transform = transfstack.top(); 
//     vec4 valvec = vec4(values[0],values[1],values[2],values[3]); 
//     vec4 newval = transform * valvec; 
//     for (int i = 0; i < 4; i++) values[i] = newval[i]; 
// }

void rightmultiply(const mat4 & M, stack<mat4> &transfstack) 
{
    mat4 &T = transfstack.top(); 
    T = T * M; 
}

// // Function to read the input data values
// // Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, float* values) 
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i]; 
        if (s.fail()) {
            cout << "Failed reading value " << i << " will skip\n"; 
            return false;
        }
    }
    return true; 
}

void readfile(const char* filename) 
{
    // cout << "Readfile" << endl;
    string str, cmd; 
    ifstream in;
    in.open(filename); 
    if (in.is_open()) {
        int vertexIndex = 0;

        // I need to implement a matrix stack to store transforms.  
        // This is done using standard STL Templates 
        stack <mat4> transfstack; 
        transfstack.push(mat4(1.0));  // identity

        // getline (in, str); 
        while (getline (in, str)) {
            // cout << str << endl;
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines 

                stringstream s(str);
                s >> cmd; 
                int i; 
                float values[10]; // Position and color for light, colors for others
                //                     // Up to 10 params for cameras.  
                bool validinput; // Validity of input 
                // cout << "cmd: " << cmd << endl;
                // General Command
                if (cmd == "size") {
                    // cout << "Size Command" << endl;
                    validinput = readvals(s,2,values); 
                    if (validinput) { 
                        
                        width = (int) values[0];
                        height = (int) values[1]; 
                        cout << "size " << width << " " << height << endl;
                    }
                 
                } 
                else if (cmd == "maxdepth") {
                    validinput = readvals(s,1,values); 
                    if (validinput) { 
                        // cout << "MaxDepth Command" << endl;

                        maxDepth = (int) values[0];
                        cout << "Maxdepth " << maxDepth << endl;
                    }
                }
                // else if (cmd == "output") {
                //     //s >> output;
                // }
                
                
                // Camera Commands
                else if (cmd == "camera") {
                    validinput = readvals(s,10,values); // 10 values eye cen up fov
                    if (validinput) {
                        // cout << "camera" << endl;
                        
                        // Set eyeinit upinit center fovy in variables.h 
                        eyeinit = vec3(values[0], values[1], values[2]);
                        center = vec3(values[3], values[4], values[5]);
                        upinit = vec3(values[6], values[7], values[8]);
                        fovy = values[9];

                        cout << fovy << endl;

                        // for (i = 0; i < 10; i++) {
                        //     cout << values[i] << endl;
                        // }
                    
                    }
                } 

                // // Geometry Commands
                else if (cmd == "sphere") {
                    validinput = readvals(s,4,values); // 10 values eye cen up fov
                    if (validinput) {
                        // cout << "sphere" << endl;
                        
                        vec3 center = vec3(values[0], values[1], values[2]);

                        // Set eyeinit upinit center fovy in variables.h 
                        shapes.push_back(new Sphere(center, values[3], transfstack.top(), ambient, emission, diffuse, specular, shininess));
                    
                    }
                }
                else if (cmd == "maxverts") {
                    validinput = readvals(s,1,values);
                    if (validinput) {
                        vertices = vector<vec3>((int) values[0]);
                        cout << "maxverts " << vertices.size() << endl;
                    }
                } 
                // else if (cmd == "maxvertnorms")  {
                    
                else if (cmd == "vertex") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        // cout << "vertex" << endl;
                        // for (i = 0; i < 3; i++) {
                        //     cout << values[i] << endl;
                        // }
                        vec3 vertex = vec3(values[0], values[1], values[2]);
                        vertices[vertexIndex] = vertex;
                        vertexIndex++;
                        
                        // cout << "current vertices" << endl;
                        // for (auto v : vertices) {
                        //     cout << v.x << " " << v.y << " " << v.z << endl;
                        // }
                    }
                }
                // else if (cmd == "vertexnormal") {

                // }
                else if (cmd == "tri") {
                    validinput = readvals(s,3,values);
                    if (validinput) {

                        // cout << "tri" << endl;

                        vec4 tempVertex0 = vec4(vertices[(int) values[0]], 1);
                        vec4 tempVertex1 = vec4(vertices[(int) values[1]], 1);
                        vec4 tempVertex2 = vec4(vertices[(int) values[2]], 1);
                        vec3 vertex0 = vec3(transfstack.top() * tempVertex0);
                        vec3 vertex1 = vec3(transfstack.top() * tempVertex1);
                        vec3 vertex2 = vec3(transfstack.top() * tempVertex2);

                        // Triangle* testTri = new Triangle(vertex0, vertex1, vertex2, transfstack.top());
                        shapes.push_back(new Triangle(vertex0, vertex1, vertex2, transfstack.top(), ambient, emission, diffuse, specular, shininess));
                        
                        // Print size of shapes
                        // cout << "Shapes Size " << shapes.size() << endl; 

                    }
                } 
                // else if (cmd == "trinormal") {

                // }

                
                // // Transformations Command
                else if (cmd == "translate") {
                    validinput = readvals(s,3,values); 
                    if (validinput) {
                        // cout << "translate" << endl;
                        mat4 translateMatix = Transform::translate(values[0], values[1], values[2]);
                        rightmultiply(translateMatix, transfstack);
                    }
                }
                else if (cmd == "rotate") {
                    // cout << "rotate" << endl;
                    validinput = readvals(s,4,values); 
                    if (validinput) {
                        mat3 rotationMatrix = Transform::rotate(values[3], vec3(values[0], values[1], values[2]));
                        rightmultiply(mat4(rotationMatrix), transfstack);
                    }
                } 
                else if (cmd == "scale") {
                    validinput = readvals(s,3,values); 
                    if (validinput) {
                        // cout << "scale" << endl;
                        mat4 scaleMatrix = Transform::scale(values[0], values[1], values[2]);
                        rightmultiply(scaleMatrix, transfstack);
                    }
                } 
                else if (cmd == "pushTransform") {
                    // cout << "pushTransform" << endl;
                    transfstack.push(transfstack.top()); 
                } 
                else if (cmd == "popTransform") {
                    // cout << "popTransform" << endl;
                    if (transfstack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n"; 
                    } else {
                        transfstack.pop(); 
                    }
                }
                
                // // Lights Command
                else if (cmd == "directional") {
                    validinput = readvals(s, 6, values); // colors 
                    if (validinput) {
                        cout << "directional" << endl;
                        for (i = 0; i < 6; i++) {
                            cout << values[i] << endl;
                        }

                        vec3 position = vec3(values[0], values[1], values[2]);
                        position = vec3(transfstack.top() * vec4(position, 0));

                        Color color = Color(values[3], values[4], values[5]);
                        lights.push_back(new DirectionalLight(color, position));
                    }
                }
                else if (cmd == "point") {
                    validinput = readvals(s, 6, values); // colors 
                    if (validinput) {
                        cout << "point" << endl;
                        for (i = 0; i < 6; i++) {
                            cout << values[i] << endl;
                        }

                        vec3 position = vec3(values[0], values[1], values[2]);
                        position = vec3(transfstack.top() * vec4(position, 1));

                        Color color = Color(values[3], values[4], values[5]);
                        lights.push_back(new PointLight(color, position, attenuation));
                    }
                }
                // else if (cmd == "attenuation") {

                // } 
                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors 
                    if (validinput) {
                        // cout << "ambient" << endl;
                        ambient = Color(values[0], values[1], values[2]);
                        cout << "Ambient: " << ambient.getR() << " " << ambient.getG() << " " << ambient.getB() << endl;

                    }
                }
                
                // // Mateirals Command
                else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        cout << "diffuse" << endl;
                        diffuse = Color(values[0], values[1], values[2]);
                        cout << diffuse.getR() << " " << diffuse.getG() << " " << diffuse.getB() << endl;
                    }
                }
                else if (cmd == "specular") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        cout << "specualar" << endl;
                        specular = Color(values[0], values[1], values[2]);
                        cout << specular.getR() << " " << specular.getG() << " " << specular.getB() << endl;
                    }
                } 
                else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values); 
                    if (validinput) {
                        cout << "shininess" << endl;
                        shininess = values[0]; 
                    }
                } 
                else if (cmd == "emission") {
                    validinput = readvals(s, 3, values); 
                    if (validinput) {
                        // cout << "emission" << endl;
                        emission = Color(values[0], values[1], values[2]);
                        cout << "Emission: " << emission.getR() << " " << emission.getG() << " " << emission.getB() << endl;
                    }
                }
                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n"; 
                }
            }
            // getline (in, str); 
        }
    } else {
        cerr << "Unable to Open Input Data File " << filename << "\n"; 
        throw 2; 
    }
}
