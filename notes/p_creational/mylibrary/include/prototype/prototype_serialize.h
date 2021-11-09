#ifndef CREATIONAL_PROTOTYPE_SERIALIZE_H
#define CREATIONAL_PROTOTYPE_SERIALIZE_H

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <ostream>

/* From Boost documentation: https://www.boost.org/doc/libs/1_55_0/libs/serialization/doc/special.html
 * By default, data types designated primitive by Implementation Level class serialization trait are never tracked.
 * If it is desired to track a shared primitive object through a pointer, (ex int*), then
 * it should be wrapped in a class/struct so that it is an identifiable type. */
struct Wrapped {
    int value;
    Wrapped() = default;
    Wrapped(int a_value) : value{a_value} {}

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar,const unsigned int file_version)
    {
        ar & value;
    }
};

class Test
{
private:
    std::string _name;
    Wrapped * _data;

    /* boost serialize support */
    /* make serialize function accessible to the serialization library*/
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int file_version)
    {
        ar & _name;
        ar & _data; // boost knows that this is a pointer thus it will dereference
     }
public:
    Test() = default;
    Test(const std::string &name, int value)
    {
        _name = name;
        _data = new Wrapped(value);
    }
    ~Test()
    {
        delete _data;
    }

    // by default, C++ will do shallow copy implicitly,
    // but let's make it explicit for visual purposes.
    Test(const Test& other)
    {
        _name = other._name;
        _data = other._data; // <--- shallow copy
    }

    void update_data(int value)
    {
        _data->value = value;
    }

    friend std::ostream &operator<<(std::ostream &os, const Test &test) {
        os << "_name: " << test._name << " _data: " << test._data->value;
        return os;
    }

};

Test clone(const Test &c)
{
    // save
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << c;
    //std::cout << oss.str() << std::endl;


    // load
    std::istringstream iss{oss.str()};
    boost::archive::text_iarchive ia(iss);

    Test result;
    ia >> result;
    return result;
}


#endif //CREATIONAL_PROTOTYPE_SERIALIZE_H
