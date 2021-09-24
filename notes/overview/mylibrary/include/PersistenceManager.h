#ifndef APP_PERSISTANCEMANAGER_H
#define APP_PERSISTANCEMANAGER_H

#include <string>
#include <fstream>
#include "Journal.h"

class PersistenceManager
{
public:
    PersistenceManager() = default;
    static void save(const Journal &a_journal, std::string a_filename)
    {
        std::ofstream outfile{a_filename};
        if( outfile.is_open())
        {
            for(auto &entry : a_journal.get_entries())
            {
                outfile << entry << std::endl;
            }

            outfile.close();

            std::cout << "saving to output file: " + a_filename << std::endl;
        }
        else
        {
            std::runtime_error("Output file is not open");
        }

    }
};


#endif //APP_PERSISTANCEMANAGER_H
