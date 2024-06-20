/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  
#include <vector>
#include <glm/glm.hpp>

#include "Color.h"
#include "Geometry.h"
#include "Light.h"

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

// EXTERN int amount; // The amount of rotation for each arrow press
// EXTERN glm::vec3 eye; // The (regularly updated) vector coordinates of the eye 
// EXTERN glm::vec3 up;  // The (regularly updated) vector coordinates of the up /

#ifdef MAINPROGRAM 
glm::vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
glm::vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
glm::vec3 center(0.0,0.0,0.0) ; // Center look at point 
int width = 500;
int height = 500 ; // width and height 
float fovy = 90.0 ; // For field of view
int maxDepth = 5;
Color ambient = Color(0.2, 0.2, 0.2); //default ambient
Color diffuse = Color(0, 0, 0);
Color emission = Color(0, 0, 0);
Color specular = Color(0, 0, 0);
float shininess = 0; 
float attenuation[3] = {1, 0, 0}; // default attenuation
std::vector<glm::vec3> vertices = {};
std::vector<Geometry> shapes = {};
std::vector<Light> lights = {};

#else 
EXTERN glm::vec3 eyeinit ; 
EXTERN glm::vec3 upinit ; 
EXTERN glm::vec3 center ; 
EXTERN int width;
EXTERN int height;
EXTERN int fovy ;
EXTERN int maxDepth;
EXTERN Color ambient;
EXTERN Color diffuse;
EXTERN Color emission;
EXTERN Color specular;
EXTERN float shininess;
EXTERN float attenuation[3];
EXTERN std::vector<glm::vec3> vertices;
EXTERN std::vector<Geometry*> shapes;
EXTERN std::vector<Light*> lights;

#endif