#ifndef CREATIONAL_INNER_FACTORY_H
#define CREATIONAL_INNER_FACTORY_H

#include <cmath>

/* factory are whole-wise constructions by hidden the constructor */
class Point {
private:
    Point(float a_x, float a_y) : x{a_x}, y{a_y} {}

    float x;
    float y;
private:
    class PointFactory
    {
    public:
        static Point newCatersian(float a_x, float a_y)
        {
            return {a_x,a_y};
        }
        static Point newPolar(float r, float theta)
        {
            return{r*std::cos(theta), r*std::sin(theta)};
        }
    };
public:
    static PointFactory factory;
};


#endif //CREATIONAL_INNER_FACTORY_H
