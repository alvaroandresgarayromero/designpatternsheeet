#ifndef CREATIONAL_INNER_FACTORY_H
#define CREATIONAL_INNER_FACTORY_H


#include <cmath>

class Point
{
private:
    Point(float a_x, float a_y) : x{a_x}, y{a_y} {}
    float x;
    float y;

private:
    class Point_factory
    {
    public:
        static Point newCatersian(float a_x, float a_y)
        {
            return {a_x, a_y};
        }

        static Point newPolar(float r, float theta)
        {
            return {r*std::cos(theta), r*std::sin(theta)};
        }
    };
public:
    static Point_factory factory; // instance of factory
};


#endif //CREATIONAL_INNER_FACTORY_H
