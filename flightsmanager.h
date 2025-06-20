#ifndef FLIGHTSMANAGER_H
#define FLIGHTSMANAGER_H

#include "graph.h"

/**
 * A functor to compare two pairs of pointers to airports and integers.\n
 * Returns true if airport1 has fewer airlines or flights than airport2. If the number of airlines or flights is the same, compares the airports' code.
 */
struct PairAirportIntLower
{
    bool operator()(const std::pair<Airport*, int> p1, const std::pair<Airport*, int> p2) const {
        if(p1.second < p2.second) return true;
        if(p1.second == p2.second && p1.first->getCode() < p2.first->getCode()) return true;
        return false;
    }
};

class FlightsManager {
public:
    FlightsManager();
    void setAirports(std::unordered_set<Airport*, AirportHashFunction, AirportPointerComparison> airports) { airports_ = airports; }
    std::unordered_set<Airport*, AirportHashFunction, AirportPointerComparison> getAirports() const { return airports_; }

    void setCities(std::unordered_set<City*, CityHashFunction, CityPointerComparison> cities) { cities_ = cities; }
    std::unordered_set<City*, CityHashFunction, CityPointerComparison> getCities() const { return cities_; }

    void setAirlines(std::unordered_set<Airline*, AirlineHashFunction, AirlinePointerComparison>  airlines) { airlines_ = airlines; }
    std::unordered_set<Airline*, AirlineHashFunction, AirlinePointerComparison>  getAirlines() const { return airlines_; }

    void setFlights(Graph flights) { flights_ = flights; }
    Graph getFlights() const { return flights_; }

    /**
     * A method to insert a pointer to an airport in the private field airports_.\n
     * Time Complexity: O(1).
     * @param airport A pointer to an airport.
     */
    void addAirport(Airport* airport);

    /**
     * A method that creates an airport with the given information and calls another method with a pointer to that airport.\n
     * Time Complexity: O(1).
     * @param airportCode A string corresponding to the airport's code.
     * @param airportName A string corresponding to the airport's name.
     * @param cityPtr A pointer to a city.
     * @param airportLatitude A double corresponding to the airport's latitude.
     * @param airportLongitude A double corresponding to the airport's longitude.
     */
    void addAirport(std::string& airportCode, std::string& airportName, City* cityPtr, double& airportLatitude, double& airportLongitude);

    /**
     * A method to insert a pointer to a city in the private field cities_.\n
     * Time Complexity: O(1).
     * @param city A pointer to a city.
     */
    void addCity(City* city);

    /**
     * A method that creates a city with the given information and calls another method with a pointer to that city.\n
     * Time Complexity: O(1).
     * @param cityName A string corresponding to the city's name.
     * @param country  A string corresponding to the city's country.
     */
    void addCity(std::string& cityName, std::string& country);

    /**
     * A method to insert a pointer to an airline in the private field airlines_.\n
     * Time Complexity: O(1).
     * @param airline A pointer to an airline.
     */
    void addAirline(Airline* airline);

    /**
     * A method that creates an airline with the given information and calls another method with a pointer to that airline.\n
     * Time Complexity: O(1).
     * @param airlineCode A string corresponding to the airline's code.
     * @param airlineName A string corresponding to the airline's name.
     * @param callsign A string corresponding to the airline's call sign.
     * @param country A string corresponding to the airline's country.
     */
    void addAirline(std::string& airlineCode, std::string& airlineName, std::string& callsign, std::string& country);

    /**
     * A method that stores a flight in the respective data structure.\n
     * Time Complexity: O(1).
     * @param srcCode A string corresponding to the source airport's code.
     * @param destCode A string corresponding to the destination airport's code.
     * @param airlineCode A string corresponding to the airline's code.
     */
    void addFlight(std::string& srcCode, std::string& destCode, std::string& airlineCode);

    /**
     * A method to find the pointer to an airport given an airport code.\n
     * Time Complexity: O(1).
     * @param airportCode A string corresponding to an airport code.
     * @return A pointer to an airport.
     */
    Airport* findAirport(const std::string& airportCode) const;

    /**
     * A method to find the pointer to a city given a city name and a country.\n
     * Time Complexity: O(1).
     * @param cityName A string corresponding to the city's name.
     * @param country A string corresponding to the city's country.
     * @return A pointer to a city.
     */
    City* findCity(const std::string& cityName, const std::string& country) const;

    /**
     * A method to find the pointer to an airline given an airline code.\n
     * Time Complexity: O(1).
     * @param airlineCode A string corresponding to an airline code.
     * @return A pointer to an airline.
     */
    Airline* findAirline(const std::string& airlineCode) const;

    /**
     * A method to get a vector that stores pointers to the airports in the city.\n
     * Time Complexity: O(1).
     * @param cityName A string corresponding to the city's name.
     * @param country A string corresponding to the city's country.
     * @return A vector of pointers to airports.
     */
    std::vector<Airport*> airportsInCity(const std::string& cityName, const std::string& country) const;

    /**
     * A method reset the graph flights_.\n
     * Time Complexity: O(|V|), where V stands for the number of nodes in the graph.
     * @param dir A bool that determines if the graph is directed or not.
     */
    void resetFlights(bool dir = true);

    /**
    * A method to determine the number of flights in an airport.\n
    * Time Complexity: O(1).
    * @param airportCode A string corresponding to the airport's code.
    * @return An unsigned long representing the number of flights in the airport.
    */
    size_t numFlightsAirport(std::string& airportCode);

    /**
     * A method to determine the airlines in an airport.\n
     * Time Complexity: O(|E|), where E stands for the number of the edges of the node.
     * @param airportCode A string corresponding to the airport's code.
     * @return A set of pointers to airlines.
     */
    std::set<Airline*, AirlinePointerLower> airlinesInAirport(std::string& airportCode);

    /**
     * A method to determine the destination airports of an airport.\n
     * Time Complexity: O(|E|), where E stands for the number of the edges of the node.
     * @param airportCode A string corresponding to the airport's code.
     * @return A set of pointers to airports.
     */
    std::set<Airport*, AirportPointerLower> destAirports(std::string& airportCode);

    /**
     * A method to determine the destination countries of an airport.\n
     * Time Complexity: O(|E|), where E stands for the number of the edges of the node.
     * @param airportCode A string corresponding to the airport's code.
     * @return A set of strings that represent countries.
     */
    std::set<std::string> destCountries(std::string& airportCode);

    /**
     * A method to determine the reachable airports of an airport with a given n number of flights.\n
     * Time Complexity: O(|V| + |E|), where V stands for the number of nodes and E stands for the number of edges.
     * @param airportCode A string corresponding to the airport's code.
     * @param n An integer representing the maximum number of flights.
     * @return A set of pointers to airports.
     */
    std::set<Airport*, AirportPointerLower> reachableAirports(std::string& airportCode, int n);

    /**
     * A method to determine the reachable cities of an airport with a given n number of flights.\n
     * Time Complexity: O(|V| + |E|), where V stands for the number of nodes and E stands for the number of edges.
     * @param airportCode A string corresponding to the airport's code.
     * @param n An integer representing the maximum number of flights.
     * @return A set of pointers to cities.
     */
    std::set<City*, CityPointerLower> reachableCities(std::string& airportCode, int n);

    /**
     * A method to determine the reachable countries of an airport with a given n number of flights.\n
     * Time Complexity: O(|V| + |E|), where V stands for the number of nodes and E stands for the number of edges.
     * @param airportCode A string corresponding to the airport's code.
     * @param n An integer representing the maximum number of flights.
     * @return A set of string that represent countries.
     */
    std::set<std::string> reachableCountries(std::string& airportCode, int n);

    /**
     * A method that returns a vector storing pointers to all airports in a given range of a given position.\n
     * Time Complexity: O(n).
     * @param latitude A double representing the latitude of the given position.
     * @param longitude A double representing the longitude of the given position.
     * @param radius A double representing the radius of the range.
     * @return A vector of pointers to airports.
     */
    std::vector<Airport*> airportsInRange(const double& latitude, const double& longitude, const double& radius) const;

    /**
     * A method that returns a vector storing all the routes from a given airport to another given airport flying with the given airlines.\n
     * Time Complexity: O(S * D * (|V| + |E|)) where S stands for the number of source airports, D stands for the number of destination airports, V stands for the number of nodes and E stands for the number of edges..
     * @param srcAirports A vector of pointers to the source airports.
     * @param destAirports A vector of pointers to the destination airports.
     * @param airlinesCodes An unordered set of strings representing airline codes.
     * @return A vector of routes.
     */
    std::vector<route> findAllRoutes(std::vector<Airport*>& srcAirports, std::vector<Airport*>& destAirports, std::unordered_set<std::string>& airlinesCodes);

    /**
     * A method that returns a priority queue that stores all the cities and the corresponding number of airports.\n
     * Time Complexity: O(n*log(n)).
     * @return A priority queue (heap_max) of pointers to cities, ordered by the number of airports of each city.
     */
    std::priority_queue<City*, std::vector<City*>, CityPointerLowerNumAirports> getCitiesByNumAirports() const;

    /**
    * A method that returns a priority queue that stores all the airports and the corresponding number of airlines.\n
    * Time Complexity: O(n*log(n) + |E|) where n stands for the number of airports and E stands for the number of edges.
    * @return A priority queue (heap_max) of pointers to airports, ordered by the number of airlines of each airport.
    */
    std::priority_queue<std::pair<Airport*, int>, std::vector<std::pair<Airport*, int>>, PairAirportIntLower> getAirportsByNumAirlines();

    /**
    * A method that returns a priority queue that stores all the airports and the corresponding number of flights.
    * Time Complexity: O(n*log(n)).
    * @return A priority queue (heap_max) of pointers to airports, ordered by the number of flights of each airport.
    */
    std::priority_queue<std::pair<Airport*, int>, std::vector<std::pair<Airport*, int>>, PairAirportIntLower> getAirportsByNumFlights();

    /**
    * A method that returns a priority queue that stores all the airlines and the corresponding number of flights.
    * Time Complexity: O(n*log(n)).
    * @return A priority queue (heap_max) of pointers to airlines, ordered by the number of flights of each airline.
    */
    std::priority_queue<Airline*, std::vector<Airline*>, AirlinePointerLowerNumFlights> getAirlineByNumFlights();

    /**
    * A method that returns a set of pointers the airports that are articulation points of the graph.
    * Time Complexity: O(|V| + |E|), where V stands for the number of vertices and E stands for the number of edges.
    * @return A set of pointers to airports.
    */
    std::set<Airport*, AirportPointerLower> articulationPoints();

private:
    std::unordered_set<Airport*, AirportHashFunction, AirportPointerComparison> airports_;
    std::unordered_set<City*, CityHashFunction, CityPointerComparison> cities_;
    std::unordered_set<Airline*, AirlineHashFunction, AirlinePointerComparison> airlines_;
    Graph flights_ = Graph(airports_, true);
};


#endif
