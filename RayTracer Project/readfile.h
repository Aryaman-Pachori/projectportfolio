#ifndef READFILE_H
#define READFILE_H

#include <stack>

// void matransform (stack<mat4> &transfstack, GLfloat * values) ;
void rightmultiply (const mat4 & M, std::stack<mat4> &transfstack) ;
bool readvals(std::stringstream &s, const int numvals, float* values) ;
void readfile (const char * filename) ;

#endif // READFILE_H