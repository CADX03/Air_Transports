#include "flightsmanager.h"


FlightsManager::FlightsManager() {
    airports_ = std::unordered_set<Airport*, AirportHashFunction, AirportPointerComparison>();
    cities_ = std::unordered_set<City*, CityHashFunction, CityPointerComparison>();
    airlines_ = std::unordered_set<Airline*, AirlineHashFunction, AirlinePointerComparison> ();
}

void FlightsManager::addAirport(Airport* airport){ airports_.insert(airport); }

void FlightsManager::addAirport(std::string& airportCode, std::string& airportName, City* cityPtr, double& airportLatitude, double& airportLongitude) {
    Airport* airportPtr = findAirport(airportCode);

    if (airportPtr == nullptr) {
        airportPtr = new Airport(airportCode, airportName, cityPtr, airportLatitude, airportLongitude);
        addAirport(airportPtr);
    }
}

void FlightsManager::addCity(City* city) { cities_.insert(city); }

void FlightsManager::addCity(std::string& cityName, std::string& country) {
    City* cityPtr = findCity(cityName, country);

    if (cityPtr == nullptr){
        cityPtr = new City(cityName, country);
        addCity(cityPtr);
    }
}

void FlightsManager::addAirline(Airline* airline) { airlines_.insert(airline); }

void FlightsManager::addAirline(std::string& airlineCode, std::string& airlineName, std::string& callsign, std::string& country) {
    Airline* airlinePtr = findAirline(airlineCode);

    if (airlinePtr == nullptr){
        airlinePtr = new Airline(airlineCode, airlineName, callsign, country);
        addAirline(airlinePtr);
    }
}

void FlightsManager::addFlight(std::string& srcCode, std::string& destCode, std::string& airlineCode) {
    Airport* srcAirport = findAirport(srcCode);
    Airport* destAirport = findAirport(destCode);
    Airline* airline = findAirline(airlineCode);
    airline->increaseFlights();
    flights_.addEdge(srcAirport, destAirport, airline);
}

Airport* FlightsManager::findAirport(const std::string& airportCode) const {
    Airport airport = Airport(airportCode, "", 0.0, 0.0);
    auto airportPtr = airports_.find(&airport);

    if (airportPtr == airports_.end()) { return nullptr; }
    return *airportPtr;
}

City* FlightsManager::findCity(const std::string& cityName, const std::string& country) const {
    City city = City(cityName, country);
    auto cityPtr = cities_.find(&city);

    if (cityPtr == cities_.end()) { return nullptr; }
    return *cityPtr;
}

Airline* FlightsManager::findAirline(const std::string& airlineCode) const {
    Airline airline = Airline(airlineCode, "", "", "");
    auto airlinePtr = airlines_.find(&airline);

    if (airlinePtr == airlines_.end()) { return nullptr; }
    return *airlinePtr;
}

std::vector<Airport*> FlightsManager::airportsInCity(const std::string& cityName, const std::string& country) const {
    City* city = findCity(cityName, country);
    if(city == nullptr) throw std::invalid_argument("This city couldn't be found in the system.");
    return city->getAirports();
}

void FlightsManager::resetFlights(bool dir) {
    flights_ = Graph(airports_, dir);
}

size_t FlightsManager::numFlightsAirport(std::string& airportCode) {
    size_t numFlights = flights_.numFlightsAirport(airportCode);
    return numFlights;
}

std::set<Airline*, AirlinePointerLower> FlightsManager::airlinesInAirport(std::string& airportCode) {
    std::set<Airline*, AirlinePointerLower> airlines = flights_.airlinesInAirport(airportCode);
    return airlines;
}

std::set<Airport*, AirportPointerLower> FlightsManager::destAirports(std::string& airportCode) {
    std::set<Airport*, AirportPointerLower> airports = flights_.destAirports(airportCode);
    return airports;
}

std::set<std::string> FlightsManager::destCountries(std::string& airportCode) {
    std::set<std::string> countries = flights_.destCountries(airportCode);
    return countries;
}

std::set<Airport*, AirportPointerLower> FlightsManager::reachableAirports(std::string& airportCode, int n) {
    std::set<Airport*, AirportPointerLower> airports = flights_.reachableAirports(airportCode, n);
    return airports;
}

std::set<City*, CityPointerLower> FlightsManager::reachableCities(std::string& airportCode, int n) {
    std::set<City*, CityPointerLower> cities = flights_.reachableCities(airportCode, n);
    return cities;
}

std::set<std::string> FlightsManager::reachableCountries(std::string& airportCode, int n) {
    std::set<City*, CityPointerLower> cities = flights_.reachableCities(airportCode, n);
    std::set<std::string> countries;
    for (City* city : cities) {
        std::string country = city->getCountry();
        countries.insert(country);
    }
    return countries;
}

std::vector<Airport*> FlightsManager::airportsInRange(const double& latitude, const double& longitude, const double& radius) const{
    std::vector<Airport*> airports;

    for (Airport* airport : airports_) {
        double airportLatitude = airport->getLatitude();
        double airportLongitude = airport->getLongitude();
        double d = calculateDistance(airportLatitude, airportLongitude, latitude, longitude);
        if (d <= radius) airports.push_back(airport);
    }

    return airports;
}

std::vector<route> FlightsManager::findAllRoutes(std::vector<Airport*>& srcAirports, std::vector<Airport*>& destAirports, std::unordered_set<std::string>& airlinesCodes) {
    std::vector<route> routes = flights_.findAllRoutes(srcAirports, destAirports, airlinesCodes);
    return routes;
}

std::priority_queue<City*, std::vector<City *>, CityPointerLowerNumAirports> FlightsManager::getCitiesByNumAirports() const {
    std::priority_queue<City*, std::vector<City *>, CityPointerLowerNumAirports> cities = std::priority_queue<City*, std::vector<City*>, CityPointerLowerNumAirports>();
    for(City* c: cities_) cities.push(c);
    return cities;
}

std::priority_queue<std::pair<Airport*, int>, std::vector<std::pair<Airport*, int>>, PairAirportIntLower> FlightsManager::getAirportsByNumAirlines() {
    auto airports = std::priority_queue<std::pair<Airport*, int>, std::vector<std::pair<Airport*, int>>, PairAirportIntLower>();
    for(Airport* a : airports_){
        std::string airportCode = a->getCode();
        auto s = airlinesInAirport(airportCode);
        std::pair<Airport*, int> p = {a, s.size()};
        airports.push(p);
    }
    return airports;
}

std::priority_queue<std::pair<Airport*, int>, std::vector<std::pair<Airport *, int>>, PairAirportIntLower> FlightsManager::getAirportsByNumFlights() {
    auto airports = std::priority_queue<std::pair<Airport*, int>, std::vector<std::pair<Airport*, int>>, PairAirportIntLower>();
    for(Airport* a : airports_){
        std::string airportCode = a->getCode();
        int n = numFlightsAirport(airportCode);
        std::pair<Airport*, int> p = {a, n};
        airports.push(p);
    }
    return airports;
}

std::priority_queue<Airline*, std::vector<Airline*>, AirlinePointerLowerNumFlights> FlightsManager::getAirlineByNumFlights() {
    auto airlines = std::priority_queue<Airline*, std::vector<Airline*>, AirlinePointerLowerNumFlights>();
    for(Airline* a : airlines_) airlines.push(a);
    return airlines;
}

std::set<Airport*, AirportPointerLower>FlightsManager::articulationPoints() {
    std::set<Airport*, AirportPointerLower> airports = flights_.articulationPoints();
    return airports;
}
