/*
 * PART OF SINGLE RESPONSIBILITY PRINCIPLE EXAMPLE
 */

#include <string>
#include <vector>

#ifndef ENCRYPTION_EXAMPLE_ONE_H
#define ENCRYPTION_EXAMPLE_ONE_H

// Journal class does not take other responsibilities
class Journal {
private:
    std::string m_title;
    std::vector<std::string> m_entries;

public:
    Journal(const std::string &title) : m_title(title) {}

    void add_entry(const std::string &new_entry);

    std::vector<std::string> get_entries() const;

};


#endif //ENCRYPTION_EXAMPLE_ONE_H
