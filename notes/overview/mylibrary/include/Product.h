#ifndef OVERVIEW_PRODUCT_H
#define OVERVIEW_PRODUCT_H

#include <string>
#include <vector>

enum class Color{ Green, Blue,  Red };
enum class Size{ Large, Medium, Small };

struct Product
{
    std::string m_name;
    Color m_color;
    Size m_size;
    Product(const std::string &a_name, const Color &a_color, const Size &a_size) :
            m_name{a_name}, m_color{a_color}, m_size{a_size} {};

};


template <typename T>
class Specification
{
public:
    virtual bool is_satisfied(T * item) = 0;
};

class ColorSpecification : public Specification<Product>
{
private:
    Color m_color;
public:
    ColorSpecification(const Color & a_color) : m_color{a_color} {}

    bool is_satisfied(Product *item) override
    {
        return item->m_color == m_color;
    }
};

class SizeSpecification : public Specification<Product>
{
private:
    Size m_size;
public:
    SizeSpecification(const Size & a_size) : m_size{a_size} {}

    bool is_satisfied(Product *item) override
    {
        return item->m_size == m_size;
    }
};

template<typename T>
class AndSpecification : public Specification<T>
{
private:
    Specification<T> &m_first;
    Specification<T> &m_second;
public:
    AndSpecification(Specification<T> &a_first, Specification<T> &a_second) :
            m_first{a_first}, m_second{a_second} {}

    bool is_satisfied(T *item) override
    {
        return m_first.is_satisfied(item) && m_second.is_satisfied(item);
    }
};

template<typename T>
AndSpecification<T> operator&&(Specification<T> &first, Specification<T> &second)
{
    // implicit construction
    return { first, second };
}



template <typename T>
class Filter
{
public:
    virtual std::vector<T*> filter(std::vector<T*> items, Specification<T> &spec) = 0;
};

class ProductFilter : public Filter<Product>
{
public:
    std::vector<Product*> filter(std::vector<Product*> items, Specification<Product> &spec) override
    {
        std::vector<Product*> result;
        for( auto &item : items)
        {
            if(spec.is_satisfied(item))
            {
                result.push_back(item);
            }
        }
        return result;
    }
};

#endif //OVERVIEW_PRODUCT_H
