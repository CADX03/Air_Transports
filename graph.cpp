#include "graph.h"


Graph::Graph(std::unordered_set<Airport*, AirportHashFunction, AirportPointerComparison>& values, bool dir) {
    this->n = values.size();
    this->hasDir = dir;

    for(Airport* airport : values) {
        Node node = Node();
        node.value = airport;
        addNode(node);
    }
}

Graph::Node* Graph::findNode(const std::string& airportCode) {
    auto aux = nodes.find(airportCode);
    if(aux == nodes.end()) return nullptr;
    return &(aux->second);
}

void Graph::addNode(Graph::Node& node) {
    nodes.insert({node.value->getCode(), node});
}

void Graph::addEdge(Graph::Node* srcNode, Graph::Node* destNode, Airline* airline, double& distance) const {
    srcNode->adj.push_back({destNode->value->getCode(), airline, distance});
    if (!hasDir) destNode->adj.push_back({srcNode->value->getCode(), airline, distance});
}

void Graph::addEdge(Airport* src, Airport* dest, Airline* airline) {
    if(src == nullptr) return;
    if(dest == nullptr) return;
    if(airline == nullptr) return;

    double lat1 = src->getLatitude();
    double long1 = src->getLongitude();
    double lat2 = dest->getLatitude();
    double long2 = dest->getLongitude();

    double distance = calculateDistance(lat1, long1, lat2, long2);

    Node* srcNode = findNode(src->getCode());
    Node* destNode = findNode(dest->getCode());

    if(srcNode == nullptr) return;
    if(destNode == nullptr) return;

    addEdge(srcNode, destNode, airline, distance);
}

void Graph::findRoutes(Node* srcNode, Node* destNode, std::vector<Airport*>& path, std::vector<Airline*>& airlines, std::vector<route>& routes, std::unordered_set<std::string>& airlinesCodes) {
    if (srcNode == destNode) {
        path.push_back(destNode->value);
        routes.push_back({path, airlines});
        path.pop_back();
    }

    else {
        for (auto& e : srcNode->adj) {
            if(airlinesCodes.empty() || airlinesCodes.find(e.airline->getCode()) != airlinesCodes.end()){
                Node* w = findNode(e.destCode);
                if (w->distance == srcNode->distance+1) {
                    path.push_back(srcNode->value);
                    airlines.push_back(e.airline);
                    findRoutes(w, destNode, path, airlines, routes, airlinesCodes);
                    airlines.pop_back();
                    path.pop_back();
                }
            }
        }
    }
}

void Graph::dfsArticulationPoints(const std::string& airportCode, int& order, std::set<Airport*, AirportPointerLower>& airports) {
    Node* node = findNode(airportCode);
    node->visited = true;
    node->num = order;
    node->low = order;
    order++;

    int children = 0;
    bool articulation = false;

    for (auto& e : node->adj) {
        Node* w = findNode(e.destCode);
        if (!w->visited){
            children++;
            dfsArticulationPoints(w->value->getCode(), order, airports);
            node->low = std::min(node->low, w->low);
            if (w->low >= node->num) articulation = true;
        }
        else node->low = std::min(node->low, w->num);
    }
    if ((node->num == 1 && children > 1) || (node->num > 1 && articulation))
        airports.insert(node->value);
}

void Graph::bfs(const std::string& airportCode, const int& maxDistance) {
    Node* node = findNode(airportCode);

    for (auto& v : nodes) {
        v.second.visited = false;
        v.second.distance = -1;
        v.second.path = "";
    }

    std::queue<Node*> q;
    node->distance = 0;
    node->visited = true;
    q.push(node);
    while (!q.empty()) {
        Node* u = q.front(); q.pop();
        for (auto& e : u->adj) {
            Node* w = findNode(e.destCode);
            if (!w->visited) {
                w->visited = true;
                w->distance = u->distance+1;
                w->path = u->value->getCode();
                if(maxDistance == -1 || w->distance < maxDistance) q.push(w);
            }
        }
    }
}

int Graph::bfsShortestPath(std::vector<Airport*>& srcAirports, std::vector<Airport*>& destAirports, std::unordered_set<std::string>& airlinesCodes) {
    int minDist = INT32_MAX;

    for (auto &v: nodes) {
        v.second.visited = false;
        v.second.distance = -1;
        v.second.path = "";
        v.second.isDest = false;
    }

    std::queue<std::string> q;

    for (Airport* aux: srcAirports) {
        std::string temp = aux->getCode();
        Node* node = findNode(temp);
        node->visited = true;
        node->distance = 0;
        node->path = temp;
        q.push(temp);
    }

    for (Airport* aux: destAirports) findNode(aux->getCode())->isDest = true;

    while (!q.empty()) {
        std::string uKey = q.front();
        Node* u = findNode(uKey);
        q.pop();
        if(minDist == INT32_MAX && u->isDest) minDist = u->distance;
        if(u->distance == minDist) continue;
        for (auto& e: u->adj) {
            if(airlinesCodes.empty() || airlinesCodes.find(e.airline->getCode()) != airlinesCodes.end()){
                Node* w = findNode(e.destCode);
                if (!w->visited) {
                    w->visited = true;
                    w->distance = u->distance+1;
                    w->path = u->value->getCode();
                    if(w->distance < minDist) q.push(e.destCode);
                }
            }
        }
    }

    if(minDist == INT32_MAX) return -1;
    return minDist;
}

size_t Graph::numFlightsAirport(std::string& airportCode) {
    Node* node = findNode(airportCode);
    if(node == nullptr) throw std::invalid_argument("This airport couldn't be found in the system.");
    return node->adj.size();
}

std::set<Airline*, AirlinePointerLower> Graph::airlinesInAirport(std::string& airportCode) {
    std::set<Airline*, AirlinePointerLower> airlines;

    Node* node = findNode(airportCode);
    if(node == nullptr) throw std::invalid_argument("This airport couldn't be found in the system.");

    for (const auto& e : node->adj) {
        airlines.insert(e.airline);
    }

    return airlines;
}

std::set<Airport*, AirportPointerLower> Graph::destAirports(std::string& airportCode) {
    std::set<Airport*, AirportPointerLower> airports;

    Node* node = findNode(airportCode);
    if(node == nullptr) throw std::invalid_argument("This airport couldn't be found in the system.");

    for (const auto& e : node->adj) {
        std::string destAirportCode = e.destCode;
        Node* destAirport = findNode(destAirportCode);
        airports.insert(destAirport->value);
    }

    return airports;
}

std::set<std::string> Graph::destCountries(std::string& airportCode) {
    std::set<std::string> countries;

    Node* node = findNode(airportCode);
    if(node == nullptr) throw std::invalid_argument("This airport couldn't be found in the system.");

    for (const auto& e : node->adj) {
        std::string destAirportCode = e.destCode;
        Node* destAirport = findNode(destAirportCode);
        countries.insert(destAirport->value->getCity()->getCountry());
    }

    return countries;
}

std::set<Airport *, AirportPointerLower> Graph::reachableAirports(std::string& airportCode, const int& n) {
    std::set<Airport*, AirportPointerLower> airports;

    Node* node = findNode(airportCode);
    if(node == nullptr) throw std::invalid_argument("This airport couldn't be found in the system.");

    bfs(airportCode, n);
    for (const auto& v : nodes) if(v.second.distance <= n && v.second.distance >= 0) airports.insert(v.second.value);

    return airports;
}

std::set<City *, CityPointerLower> Graph::reachableCities(std::string& airportCode, const int& n) {
    std::set<City *, CityPointerLower> cities;

    Node* node = findNode(airportCode);
    if(node == nullptr) throw std::invalid_argument("This airport couldn't be found in the system.");

    bfs(airportCode, n);
    for (const auto& v : nodes) if(v.second.distance <= n && v.second.distance >= 0) cities.insert(v.second.value->getCity());

    return cities;
}

std::vector<route> Graph::findAllRoutes(std::vector<Airport*>& srcAirports, std::vector<Airport*>& destAirports, std::unordered_set<std::string>& airlinesCodes) {
    std::vector<route> routes;
    std::vector<Airport*> path;
    std::vector<Airline*> airlines;

    int dist = bfsShortestPath(srcAirports, destAirports, airlinesCodes);

    for(Airport* src : srcAirports) {
        Node* srcNode = findNode(src->getCode());
        if (srcNode == nullptr) throw std::invalid_argument("This airport couldn't be found in the system.");
        for (Airport* dest: destAirports) {
            Node* destNode = findNode(dest->getCode());
            if (destNode == nullptr) throw std::invalid_argument("This airport couldn't be found in the system.");
            if (destNode->distance == dist) findRoutes(srcNode, destNode, path, airlines, routes, airlinesCodes);
        }
    }

    return routes;
}

std::set<Airport*, AirportPointerLower> Graph::articulationPoints() {
    std::set<Airport*, AirportPointerLower> airports;
    for (auto& node : nodes) {
        node.second.visited = false;
        node.second.low = 0;
        node.second.num = 0;
    }

    int order = 1;

    for (auto& node : nodes) {
        if (!node.second.visited) dfsArticulationPoints(node.second.value->getCode(), order, airports);
    }

    return airports;
}
