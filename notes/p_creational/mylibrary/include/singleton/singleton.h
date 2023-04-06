#ifndef OVERVIEW_SINGLETON_H
#define OVERVIEW_SINGLETON_H


/*
 * Singleton design pattern can be used to only allow one instance of a component.
 * A single component can be
 *  - a database
 * When the construction is really expensive, then we only want to do it once.
 * Therefore, with a singleton object, then we want to provide the same instance to every other object
 *
 * Note: the construction needs to be thread safe in order to avoid a race condition where the construction of
 * the instance occurs more than once.
 *
 *
 * SUMMARY: A singleton is a component that is instantiated only once
 */
#endif //OVERVIEW_SINGLETON_H
