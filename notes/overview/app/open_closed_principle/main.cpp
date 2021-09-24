#include <iostream>
#include <cstring>
#include <unistd.h>

#include "overview/Product.h"

/* Task:
 * Create an app that filters some products.
 * A product has the following attributes:
 *  - name, color, size where color and size are defined in an enum
 *
 * Solution:
 * - Create a struct to maintain the product attributes
 * - Create a Specification abstract interface class that can be used
 * to create as many specification classes to meet our criteria, and then create
 * a filter class that takes a vector of products and the base class of the
 * specification in order to support any type of specification dynamically.
 */
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