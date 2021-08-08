//
// Created by alvaro on 8/4/21.
//

#include <boost/lexical_cast.hpp>

#include "../include/Journal.h"

void Journal::add_entry(const std::string &new_entry)
{
    static int count = 1;
    entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + new_entry);

}

std::ostream &operator<<(std::ostream &os, const Journal &journal) {

    for( auto &entry : journal.entries)
    {
        os << "entry " << entry << std::endl;
    }
    return os;
}
