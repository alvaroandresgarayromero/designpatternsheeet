#include <iostream>
#include <cstring>
#include <unistd.h>

/* Liskov Substitution principle states that
 * a foo function that has a base class reference or pointer
 * as an argument, then any derived methods that gets called
 * must work.
 *
 * ex: Square is a rectangle. Is that true? See buggy example below
 * Note on the verify_area() function that it should work with
 * any derived classes from Rectangle_buggy, but it won't.
 */

class Rectangle_buggy
{
protected:
    int m_length;
    int m_width;
public:
    Rectangle_buggy(const int &a_length, const int &a_width) :
    m_length{a_length}, m_width{a_width} {}

    int getLength() const { return m_length; }
    int getWidth() const { return m_width; }
    virtual void setLength(int a_length) { m_length=a_length;}
    virtual void setWidth(int a_width) { m_width=a_width; }

    int area() { return m_width*m_length; }

    virtual void display() { std::cout << "Rectangle Base Class" << std::endl; }

};

class Square_buggy : public Rectangle_buggy
{
public:
    Square_buggy(const int &a_size) : Rectangle_buggy{a_size, a_size} {}

    void setLength(int a_size) override { m_length=m_width=a_size;}
    void setWidth(int a_size) override { m_length=m_width=a_size;}
    void display() override { std::cout << "Square Derived Class:" << std::endl; }

};

void verify_area(Rectangle_buggy & obj)
{
    // THIS FUNCTION SHOULD WORK WITH ANY DERIVED METHODS FROM THE BASE CLASS
    // HOWEVER, WE CAN SEE THAT SQUARE BREAKS THIS FUNCTION
    int width = obj.getWidth();
    int length = obj.getLength();

    obj.display();

    std::cout << "expected area is " << width*length << " calculated area is: "
              << obj.area() << std::endl;

    obj.setLength(10);
    length = obj.getLength();
    std::cout << "Now updating length to " << length << std::endl;

    std::cout << "expected area is " << width*length << " calculated area is: "
     << obj.area() << std::endl;
}

int main()
{
    /* rectangle works passes */
    Rectangle_buggy rect{5,5};
    verify_area(rect);
    std::cout << std::endl << std::endl;


    /* square fails */
    Square_buggy square{5};
    verify_area(square);

    return 0;
}