#include <iostream>
#include <cstring>
#include <unistd.h>

#include <overview/Journal.h>
#include <overview/PersistenceManager.h>

/* Task:
 * Create a journal app where I can store my most intimate thoughts. I should
 * be able to add a title, and a number of entries. I also would like
 * the ability to save the entry into a filename.
 *
 * Solution:
 * - Journal should be its own class with inserting, deleting, and modifying entries.
 * - Save contents should be a separate class because it is a separate concern from Journal.
 *    - What if the journal class is already in production. We don't want to make new modifications on it.
 *    - Ex: currently we want to save into a file, but maybe in the future we can't to save in a database.
 *    -  Thus, create a PersistenceManager class that maintains all save or
 * load features from any classes. If we need to update the save mechanism (database, other file path, etc),
 * then all this can be done through the PersistenceManager.
 * */
int main()
{
    Journal obj{"Dear Diary"};
    obj.add_entry("I ate an apple");
    obj.add_entry("I went running today");

    PersistenceManager::save(obj, "text.txt");


    return 0;
}