#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include "airport.h"
#include "airline.h"
#include "utils.h"

typedef std::pair<std::vector<Airport*>, std::vector<Airline*>> route;


class Graph {
private:
    struct Node;
    struct Edge;

    struct Edge {
        std::string destCode; // Code of the destination node
        Airline* airline;
        double weight; // Distance between two airports in km
    };

    struct Node {
        Airport* value;
        std::list<Edge> adj;
        bool visited;
        int distance; // Number of connections from root to the node
        std::string path;
        bool isDest; // Is this node a destination airport?
        int low;
        int num;
    };

    void addNode(Node& node);
    void addEdge(Node* srcNode, Node* destNode, Airline* airline, double& distance) const;

    /**
     * A method that find all the shortest routes from the source node to the destination node and stores them in the vector routes, using the specified airlines.\n
     * Time Complexity: O(K * (|V| + |E|)), where K stands for the number of possible routes between the source node and the destination node.
     */
    void findRoutes(Node* srcNode, Node* destNode, std::vector<Airport*>& path, std::vector<Airline*>& airlines, std::vector<route>& routes, std::unordered_set<std::string>& airlinesCodes);

    size_t n;
    bool hasDir;

    std::unordered_map<std::string, Node> nodes;

public:
    Graph(std::unordered_set<Airport*, AirportHashFunction, AirportPointerComparison>& values, bool dir = false);

    Node* findNode(const std::string& airportCode);

    void addEdge(Airport* src, Airport* dest, Airline* airline);

    /**
     * A depth-first search to find the articulation points.\n
     * Time Complexity: O(|V| + |E|).
     * @param airportCode A string that represents an airport code.
     * @param order An integer representing the order by which each node is visited.
     * @param airports A set of pointers to airports.
     */
    void dfsArticulationPoints(const std::string& airportCode, int& order, std::set<Airport*, AirportPointerLower>& airports);

    void bfs(const std::string& airportCode, const int& maxDistance = -1);

    /**
     * A breadth-first search to find the shortest path between any airport in the given vector of source airports to any airport in the given vector of destination airports using only the given airlines.
     * @param srcAirports A vector of pointers to the source airports.
     * @param destAirports A vector of pointers to the destination airports.
     * @param airlinesCodes An unordered set of strings representing airline codes.
     * @return An integer representing the minimum number of flights to reach any destination airport from any source airport.
     */
    int bfsShortestPath(std::vector<Airport*>& srcAirports, std::vector<Airport*>& destAirports, std::unordered_set<std::string>& airlinesCodes);


    /**
     * A method to determine the number of flights in an airport.\n
     * Time Complexity: O(1).
     * @param airportCode A string corresponding to the airport's code.
     * @return An unsigned long representing the number of flights in the airport.
     */
    size_t numFlightsAirport(std::string& airportCode);

    /**
     * A method to give the airlines in an airport.\n
     * Time Complexity: O(n).
     * @param airportCode A string corresponding to the airport's code.
     * @return A set of airlines pointers.
     */
    std::set<Airline*, AirlinePointerLower> airlinesInAirport(std::string& airportCode);

    /**
    * A method to determine the airlines in an airport.\n
    * Time Complexity: O(|E|), where E stands for the number of the edges of the node.
    * @param airportCode A string corresponding to the airport's code.
    * @return A set of pointers to airlines.
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
     * A method to give the reachable airports of an airport.\n
     * Time Complexity: O(n).
     * @param airportCode A string corresponding to the airport's code.
     * @param n An integer.
     * @return A set of airports pointers.
     */


    std::set<Airport*, AirportPointerLower> reachableAirports(std::string& airportCode, const int& n = -1);

    /**
    * A method to determine the reachable airports of an airport with a given n number of flights.\n
    * Time Complexity: O(|V| + |E|), where V stands for the number of nodes and E stands for the number of edges.
    * @param airportCode A string corresponding to the airport's code.
    * @param n An integer representing the maximum number of flights.
    * @return A set of pointers to airports.
    */
    std::set<City*, CityPointerLower> reachableCities(std::string& airportCode, const int& n = -1);

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
    * A method that returns a set of pointers the airports that are articulation points of the graph.
    * Time Complexity: O(|V| + |E|), where V stands for the number of vertices and E stands for the number of edges.
    * @return A set of pointers to airports.
    */
    std::set<Airport*, AirportPointerLower> articulationPoints();

};

#endif