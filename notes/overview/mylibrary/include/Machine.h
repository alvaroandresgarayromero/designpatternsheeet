#ifndef OVERVIEW_MACHINE_H
#define OVERVIEW_MACHINE_H

#include <string>

struct Document
{
    std::string m_title;
};

class IPrinter
{
public:
    virtual void print(const Document &doc) = 0;
};

class IScanner
{
public:
    virtual void scan(const Document &doc) = 0;
};

class IFax
{
public:
    virtual void fax(const Document &doc) = 0;
};

class IMachine : public IPrinter, IScanner {};

// concrete class
class Machine : public IMachine
{
public:
    void print(const Document &doc) override
    {
        std::cout << "printing document: " << doc.m_title << std::endl;
    }

    void scan(const Document &doc) override
    {
        std::cout << "scanning document: " << doc.m_title << std::endl;
    }
};

class Fax : public IFax
{
public:
    void fax(const Document &doc) override
    {
        std::cout << "faxing document: " << doc.m_title << std::endl;
    }
};


#endif //OVERVIEW_MACHINE_H
