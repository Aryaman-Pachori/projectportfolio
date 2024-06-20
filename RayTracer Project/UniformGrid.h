#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include <vector>
#include <glm/glm.hpp>
#include "Geometry.h"

class Geometry;
class Ray;
struct HitRecord;

class Cell
{
public:
    std::vector<Geometry *> objects;
};

class UniformGrid
{
private:
    std::vector<Cell> cells;
    glm::ivec3 dimensions;        // grid dimensions (number of cells in each axis)
    glm::vec3 cellSize;           // size of each cell
    glm::vec3 sceneMin, sceneMax; // bounding box of the whole scene

public:
    UniformGrid();
    void build(const std::vector<Geometry *> &objects);
    bool intersect(const Ray &ray, HitRecord &hitRecord) const;
    glm::ivec3 getCellIndex(const glm::vec3 &point) const;
};

#endif
