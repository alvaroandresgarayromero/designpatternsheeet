#include <iostream>
#include <cstring>
#include <unistd.h>

#include "Product.h"

/* This is a scratch board app for testing, debugging, and developing new
 * library features by linking directly to the static library
 * in the build tree. */
int main()
{
    Product product_1{"car", Color::Blue, Size::Medium};
    Product product_2{"tree", Color::Green, Size::Large};
    Product product_3{"ball", Color::Blue, Size::Small};

    std::vector<Product*> products{&product_1, &product_2, &product_3};

    ColorSpecification color_spec{Color::Blue};
    SizeSpecification size_spec{Size::Small};
    auto spec = color_spec && size_spec;

    ProductFilter pf;
    for( auto &items : pf.filter(products, spec) )
    {
        std::cout << items->m_name << std::endl;
    }
    return 0;
}