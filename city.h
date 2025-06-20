#ifndef CITY_H
#define CITY_H

#include <iostream>
#include "string"
#include "vector"
#include "airport.h"


class Airport;

class City {
public:
    City(std::string name, std::string country);
    City(std::string name, std::string country, std::vector<Airport*> airports);

    void setName(std::string name) { name_ = name;}
    std::string getName() const { return name_;}

    void setCountry(std::string country) { country_ = country;}
    std::string getCountry() const { return country_;}

    void setAirports(std::vector<Airport*> airports) { airports_ = airports;}
    std::vector<Airport*> getAirports() const { return airports_;}

    /**
     * Adds an airport to the vector storing pointers to all the airports in the city.
     * @param airport A pointer to an airport.
     */
    void addAirport(Airport* airport);

    bool operator==(const City* city) const;
    bool operator==(const City& city) const;

    bool operator<(const City& city) const;

    /**
     * A method to print the information about a city.\n
     * It prints the corresponding city and country.\n
     * Time Complexity: O(1).
     */
    void show() const;

private:
    std::string name_;
    std::string country_;
    std::vector<Airport*> airports_;
};

/**
 * A functor to compare two pointers to cities.\n
 * Return true if city1 is lower than city2.
 */
struct CityPointerLower
{
    bool operator()(const City* city1, const City* city2) const { return *city1 < *city2; }
};

/**
 * A functor to compare two pointers to cities.\n
 * Return true if city1 is equal to city2.
 */
struct CityPointerComparison
{
    bool operator()(const City* city1, const City* city2) const { return *city1 == *city2; }
};

struct CityHashFunction
{
    std::size_t operator()(const City* city) const { return std::hash<std::string>()(city->getName()) + std::hash<std::string>()(city->getCountry());  }
};

/**
 * A functor to compare two pointers to cities.\n
 * Return true if city1 has less airports then city2. If the number of airports is the same, compares the cities' names and respective countries.
 */
struct CityPointerLowerNumAirports
{
    bool operator()(const City* city1, const City* city2) const {
        if(city1->getAirports().size() < city2->getAirports().size()) return true;
        if(city1->getAirports().size() == city2->getAirports().size() && city1->getName() > city2->getName()) return true;
        if(city1->getAirports().size() == city2->getAirports().size() && city1->getName() == city2->getName() && city1->getCountry() > city2->getCountry()) return true;
        return false;
    }
};

#endif
