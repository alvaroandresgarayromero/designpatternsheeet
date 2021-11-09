#ifndef OVERVIEW_PROTOTYPE_H
#define OVERVIEW_PROTOTYPE_H

#include <ostream>

/* - prototype design pattern is a partially or fully constructed object that
 *   can be cloned in order to further customize it.
 * - This requires deep copy support in order to facilitate the cloning */

/* Address and Contact: Naive implementation of a deep copy constructor without using modern pointer */
class Address
{
public:

    std::string street;
    std::string city;
    int suite;
     Address(std::string a_street, std::string a_city, int a_suite) :
            street{a_street}, city{a_city}, suite{a_suite} {}

    friend std::ostream &operator<<(std::ostream &os, const Address &address) {
        os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite;
        return os;
    }

    friend class Contact;
};

class Contact
{
public:

    std::string name;
    Address *address;
public:
    Contact(std::string a_name, Address a_address)
    {
        name = a_name;
        address = new Address{a_address.street, a_address.city, a_address.suite};
    }

    ~Contact()
    {
        delete address;
    }

    Contact(const Contact &other) : Contact(other.name, *other.address) {}

    friend std::ostream &operator<<(std::ostream &os, const Contact &contact) {
        os << "name: " << contact.name << " address: " << *contact.address;
        return os;
    }


};

/* Say, our tasks is to create an interface that allow us to re-use the main address of an office building,
 * such that HR just needs to add new employee names.
 * - We can use a factory to do whole-wise construction, such that we can specialize the construction
 * @todo: we need to make our other class constructor private so user knows not to use them for factory design*/
class EmployeeFactory
{
public:
    static std::unique_ptr<Contact> newEmployee(const std::string name)
    {
        // create static office contact object so that we can re-use as our main template
        static Contact look_up_contact{"", {"22011 30th Dr SE",
                                                "Bothell,WA",
                                                1}};
        // triggers copy constructor
        std::unique_ptr<Contact> result = std::make_unique<Contact>(look_up_contact);
        result->name = name;
        return std::move(result);
    }
};

#endif //OVERVIEW_PROTOTYPE_H
