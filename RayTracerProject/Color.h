#ifndef COLOR_H
#define COLOR_H

class Color {
    private:
        float r;
        float g;
        float b;

    public:
        Color() {
            r = 0;
            g = 0;
            b = 0;
        }

        Color (float red, float green, float blue) {
            r = red;
            g = green;
            b = blue;
        }

        float getR() {
            return r;
        }

        float getG() {
            return g;
        }

        float getB() {
            return b;
        }

        Color operator+(const Color &c) {
            return Color(this->r + c.r, this->g + c.g, this->b + c.b);
        }

        Color operator*(const Color &c) {
            return Color(this->r * c.r, this->g * c.g, this->b * c.b);
        }

        Color operator*(const float &f) {
            return Color(this->r * f, this->g * f, this->b * f);
        }

        Color operator/(const float &f) {
            return Color(this->r / f, this->g / f, this->b / f);
        }
};

#endif // COLOR_H