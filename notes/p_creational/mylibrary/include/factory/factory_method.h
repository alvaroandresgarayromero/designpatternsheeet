#ifndef CREATIONAL_FACTORY_METHOD_H
#define CREATIONAL_FACTORY_METHOD_H

#include <cmath>

class Point
{
private:
    Point(float a_x, float a_y) : x{a_x}, y{a_y} {}
public:
    float x;
    float y;

    static Point newCatersian(float a_x, float a_y)
    {
        return {a_x, a_y};
    }

    static Point newPolar(float r, float theta)
    {
        return {r*std::cos(theta), r*std::sin(theta)};
    }
};

class Temp
{
private:
    Temp(float a_x, float a_y) : x{a_x}, y{a_y} {}


    float x;
    float y;

public:
    static Temp * new_instance(float a_x, float a_y)
    {
        Temp *ptr = new Temp{a_x, a_y};
        return ptr;
    }

};

#endif //CREATIONAL_FACTORY_METHOD_H
