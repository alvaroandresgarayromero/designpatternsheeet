/*
 * PART OF SINGLE RESPONSIBILITY PRINCIPLE EXAMPLE
 */

#include <string>
#include <vector>

#ifndef ENCRYPTION_EXAMPLE_ONE_H
#define ENCRYPTION_EXAMPLE_ONE_H

// Journal class does not take other responsibilities
class Journal {
    std::string title;
    std::vector<std::string> entries;

public:
    Journal(const std::string &title) : title(title) {}

    void add_entry(const std::string &new_entry);

    friend std::ostream &operator<<(std::ostream &os, const Journal &journal);
};


#endif //ENCRYPTION_EXAMPLE_ONE_H
