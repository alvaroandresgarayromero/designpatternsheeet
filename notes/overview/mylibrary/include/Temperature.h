#ifndef OVERVIEW_TEMPERATURE_H
#define OVERVIEW_TEMPERATURE_H

#include <string>


// generic interface to support actual and virtual machine
// configurations
template <typename T>
class ITemp
{
public:
    virtual void setTemperature(const T &data) = 0;
    virtual int getTemperature() const = 0;
    virtual std::string display() const =0;
};

// low level module with details on the actual machine
class Machine : public ITemp<int>
{
private:
    int m_temp;
public:
    void setTemperature(const int &data) override
    {
        m_temp = data;
        // more operations on the actual machine go here
        std::cout << "Setting machine temperature to " << m_temp << std::endl;
    }
    int getTemperature() const override
    {
        return m_temp;
    }

    std::string  display() const override
    {
        return "actual machine";
    }
};

// low level module with details on the virtual machine
class VirtualMachine : public ITemp<int>
{
private:
    int m_temp;
public:
    void setTemperature(const int &data) override
    {
        m_temp = data;
        // more simulation operations go here
        std::cout << "Setting virtual machine temperature to " << m_temp << std::endl;

    }

    int getTemperature() const override
    {
        return m_temp;
    }

    std::string display() const override
    {
        return "virtual machine";
    }
};

#endif //OVERVIEW_TEMPERATURE_H
