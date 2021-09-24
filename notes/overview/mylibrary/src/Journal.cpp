#include <boost/lexical_cast.hpp>

#include "../include/Journal.h"

void Journal::add_entry(const std::string &new_entry)
{
    static int count = 1;
    m_entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + new_entry);
}

std::vector<std::string> Journal::get_entries() const
{
    return m_entries;
}
