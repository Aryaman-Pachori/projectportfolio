// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.
    glm::vec3 axisNormalized = glm::normalize(axis);

    glm::mat3 matrix1 = glm::mat3(1);
    glm::mat3 matrix2 = glm::mat3(
        axisNormalized[0] * axisNormalized[0], axisNormalized[0] * axisNormalized[1], axisNormalized[0] * axisNormalized[2],
        axisNormalized[0] * axisNormalized[1], axisNormalized[1] * axisNormalized[1], axisNormalized[1] * axisNormalized[2],
        axisNormalized[0] * axisNormalized[2], axisNormalized[1] * axisNormalized[2], axisNormalized[2] * axisNormalized[2]);
    glm::mat3 matrix3 = glm::mat3(
        0, axisNormalized[2], -axisNormalized[1],
        -axisNormalized[2], 0, axisNormalized[0],
        axisNormalized[1], -axisNormalized[0], 0);

    float cosTheta = cos(degrees * pi / 180.0f);
    float sinTheta = sin(degrees * pi / 180.0f);

    return (cosTheta * matrix1) + ((1 - cosTheta) * matrix2) + (sinTheta * matrix3);
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    eye = rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.
    vec3 crossCopy = glm::normalize(glm::cross(eye, up));

    eye = rotate(degrees, crossCopy) * eye;
    up = rotate(degrees, crossCopy) * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1. 
    glm::vec3 w = glm::normalize(eye);

    glm::vec3 u = glm::normalize(glm::cross(up, w));

    glm::vec3 v = glm::cross(w, u);

    glm::mat4 rotationMatrix = glm::mat4(u[0], v[0], w[0], 0,
        u[1], v[1], w[1], 0,
        u[2], v[2], w[2], 0,
        0, 0, 0, 1);

    glm::mat4 otherMatrix = glm::mat4(1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -eye[0], -eye[1], -eye[2], 1);
    // You will change this return call
    return rotationMatrix * otherMatrix;
    //return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.
    //float theta = (fovy * pi / 180.0f) / 2;
    float theta = glm::radians(fovy) / 2;
    float xPerspective = 1 / (aspect * tan(theta));
    float yPerspective = 1 / tan(theta);

    float a = -(zNear + zFar) / (zFar - zNear);
    float b = -(2 * zNear * zFar) / (zFar - zNear);

    mat4 perspectiveMatrix = mat4(
        xPerspective, 0, 0, 0,
        0, yPerspective, 0, 0,
        0, 0, a, -1,
        0, 0, b, 0);

    return perspectiveMatrix;
    //mat4 ret;
    //return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    // YOUR CODE FOR HW2 HERE
    // Implement scaling
    mat4 scaleMatrix = mat4(
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    );

    return scaleMatrix;
    //mat4 ret;
    //return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    //mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement translation
    mat4 translationMatrix = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        tx, ty, tz, 1.0);

    return translationMatrix;
    //mat4 ret;
    //return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
