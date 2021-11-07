#ifndef CREATIONAL_ABSTRACT_FACTORY_H
#define CREATIONAL_ABSTRACT_FACTORY_H

class HotDrink
{
public:
    HotDrink() = default;
    virtual ~HotDrink() = default;
    virtual void prepare(int i) = 0;
};

class Tea : public HotDrink
{
public:
    Tea() = default;
    void prepare(int i) override
    {
        std::cout << "Preparing " << i << " tea" << std::endl;
    }
};

class Coffee : public HotDrink
{
public:
    Coffee() = default;
    void prepare(int i) override
    {
        std::cout << "Preparing " << i << " coffee" << std::endl;

    }
};

/* Create abstract factory to construct an instance of Tea and Coffee */
class FactoryHotDrink
{
public:
    FactoryHotDrink() = default;
    virtual ~FactoryHotDrink() = default;
    virtual std::unique_ptr<HotDrink> make() = 0;
};

class FactoryTea : public FactoryHotDrink
{
public:
    FactoryTea() = default;
    std::unique_ptr<HotDrink> make() override
    {
        return std::make_unique<Tea>();
    }
};

class FactoryCoffee : public FactoryHotDrink
{
public:
    FactoryCoffee() = default;
    std::unique_ptr<HotDrink> make() override
    {
        return std::make_unique<Coffee>();
    }
};


#endif //CREATIONAL_ABSTRACT_FACTORY_H
