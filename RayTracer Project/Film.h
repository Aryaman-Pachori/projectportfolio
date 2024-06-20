
#include <string>
#include <vector>
#include "Color.h"


class Film {
    private:
        std::vector<std::vector<Color>> pixels;

    public:
        Film();

        void addPixelColor(int x, int y, Color color);

        void saveImage(std::string fname);
};