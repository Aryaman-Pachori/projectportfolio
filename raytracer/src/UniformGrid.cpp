#include "UniformGrid.h"
#include "Geometry.h"
#include <iostream>
using namespace std;

UniformGrid::UniformGrid() {}

void UniformGrid::build(const std::vector<Geometry *> &objects)
{
    // calculate the bounding box of the scene.
    // initialize scene bounds
    glm::vec3 minBound(std::numeric_limits<float>::max());
    glm::vec3 maxBound(std::numeric_limits<float>::lowest());

    for (const auto &obj : objects)
    {
        glm::vec3 objMin, objMax;
        // sphere
        if (auto *sphere = dynamic_cast<Sphere *>(obj))
        {
            objMin = sphere->center - glm::vec3(sphere->radius);
            objMax = sphere->center + glm::vec3(sphere->radius);
        }
        // triangle
        else if (auto *triangle = dynamic_cast<Triangle *>(obj))
        {
            objMin = glm::min(triangle->v0, glm::min(triangle->v1, triangle->v2));
            objMax = glm::max(triangle->v0, glm::max(triangle->v1, triangle->v2));
        }

        minBound = glm::min(minBound, objMin);
        maxBound = glm::max(maxBound, objMax);
    }

    // debug statement
    std::cout << "Scene bounding box: Min(" << minBound.x << ", " << minBound.y << ", " << minBound.z
              << ") Max(" << maxBound.x << ", " << maxBound.y << ", " << maxBound.z << ")" << std::endl;

    sceneMin = minBound;
    sceneMax = maxBound;
    glm::vec3 sceneSize = sceneMax - sceneMin;

    // decide on grid dimension and cell size
    float cubeRoot = std::cbrt(static_cast<float>(objects.size()));
    dimensions = glm::ivec3(cubeRoot);
    cellSize = sceneSize / glm::vec3(dimensions);

    cells.resize(dimensions.x * dimensions.y * dimensions.z);

    std::cout << "Grid dimensions: (" << dimensions.x << ", " << dimensions.y << ", " << dimensions.z << ")"
              << " with cell size: (" << cellSize.x << ", " << cellSize.y << ", " << cellSize.z << ")" << std::endl;

    // loop through objects and add them to cells based on type
    for (auto *obj : objects)
    {
        glm::vec3 objMin(std::numeric_limits<float>::max()), objMax(std::numeric_limits<float>::lowest());

        // sphere calculation
        if (auto *sphere = dynamic_cast<Sphere *>(obj))
        {
            objMin = sphere->center - glm::vec3(sphere->radius);
            objMax = sphere->center + glm::vec3(sphere->radius);
        }
        // triangle calculation
        else if (auto *triangle = dynamic_cast<Triangle *>(obj))
        {
            objMin = glm::min(triangle->v0, glm::min(triangle->v1, triangle->v2));
            objMax = glm::max(triangle->v0, glm::max(triangle->v1, triangle->v2));
        }

        glm::ivec3 startCell = getCellIndex(objMin);
        glm::ivec3 endCell = getCellIndex(objMax);

        // check if cell indices are within grid bounds
        startCell = glm::clamp(startCell, glm::ivec3(0), dimensions - glm::ivec3(1));
        endCell = glm::clamp(endCell, glm::ivec3(0), dimensions - glm::ivec3(1));

        for (int x = startCell.x; x <= endCell.x; ++x)
        {
            for (int y = startCell.y; y <= endCell.y; ++y)
            {
                for (int z = startCell.z; z <= endCell.z; ++z)
                {
                    int cellIndex = x + dimensions.x * (y + dimensions.y * z);
                    cells[cellIndex].objects.push_back(obj);
                }
            }
        }
    }

    std::cout << "Objects added to grid." << std::endl;
}

bool UniformGrid::intersect(const Ray &ray, HitRecord &hitRecord) const
{
    std::cout << "Intersect called with Ray origin: (" << ray.origin().x << ", "
              << ray.origin().y << ", " << ray.origin().z << ") direction: ("
              << ray.direction().x << ", " << ray.direction().y << ", "
              << ray.direction().z << ")" << std::endl;

    glm::vec3 invDir = 1.0f / ray.direction();
    glm::vec3 sign = glm::sign(ray.direction());

    // intersection with the grid's bounding box
    glm::vec3 tMin = (sceneMin - ray.origin()) * invDir;
    glm::vec3 tMax = (sceneMax - ray.origin()) * invDir;

    // swapping
    if (sign.x < 0)
        std::swap(tMin.x, tMax.x);
    if (sign.y < 0)
        std::swap(tMin.y, tMax.y);
    if (sign.z < 0)
        std::swap(tMin.z, tMax.z);

    // max entry & min exit
    float tEntry = std::max(tMin.x, std::max(tMin.y, tMin.z));
    float tExit = std::min(tMax.x, std::min(tMax.y, tMax.z));

    // if there is no intersection with the grid's bounding box
    if (tEntry > tExit)
    {
        return false;
    }

    // grid traversal
    glm::ivec3 gridIndex = getCellIndex(ray.origin());
    glm::ivec3 step = glm::ivec3(sign);
    glm::vec3 tDelta = glm::vec3(abs(invDir));
    glm::vec3 nextCrossingT = tMin + tDelta * glm::vec3(step);

    // traverse the grid
    while (true)
    {
        // Check if the current cell is within the grid bounds
        if (gridIndex.x < 0 || gridIndex.x >= dimensions.x ||
            gridIndex.y < 0 || gridIndex.y >= dimensions.y ||
            gridIndex.z < 0 || gridIndex.z >= dimensions.z)
        {
            break;
        }

        // obtain the scalar t for the closest intersection within the current cell
        float tClosest = std::min(nextCrossingT.x, std::min(nextCrossingT.y, nextCrossingT.z));

        // test intersection with objects in the current cell
        int cellIndex = gridIndex.x + dimensions.x * (gridIndex.y + dimensions.y * gridIndex.z);
        for (auto *object : cells[cellIndex].objects)
        {
            if (object->intersect(ray, tEntry, tClosest, hitRecord))
            {
                return true; // intersection found
            }
        }

        // move to the next cell
        if (nextCrossingT.x < nextCrossingT.y && nextCrossingT.x < nextCrossingT.z)
        {
            gridIndex.x += step.x;
            nextCrossingT.x += tDelta.x;
        }
        else if (nextCrossingT.y < nextCrossingT.z)
        {
            gridIndex.y += step.y;
            nextCrossingT.y += tDelta.y;
        }
        else
        {
            gridIndex.z += step.z;
            nextCrossingT.z += tDelta.z;
        }

        // update the entry point for the next cell
        tEntry = tClosest;

        // if we've exited the grid, stop
        if (tEntry > tExit)
        {
            break;
        }
    }

    return false; // no intersection found
}

glm::ivec3 UniformGrid::getCellIndex(const glm::vec3 &point) const
{
    // convert a point to its cell index based on the grid's partitioning.
    glm::vec3 normalized = (point - sceneMin) / cellSize;
    glm::ivec3 cellIndex = glm::floor(normalized);
    cellIndex = glm::clamp(cellIndex, glm::ivec3(0), dimensions - glm::ivec3(1));
    return cellIndex;
}
