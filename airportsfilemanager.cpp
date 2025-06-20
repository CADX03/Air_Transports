#include "airportsfilemanager.h"


AirportsFileManager::AirportsFileManager() { ; }

void AirportsFileManager::load(FlightsManager& flightsManager, const std::string& file) {
    std::ifstream ifs("../dataset/"+file);
    std::string header;
    std::getline(ifs, header);

    for(std::string line; std::getline(ifs, line);) {
        std::istringstream iss(line);
        std::string airportCode;
        std::string airportName;
        std::string cityName;
        std::string country;
        double airportLatitude;
        double airportLongitude;

        std::getline(iss, airportCode, ',');
        std::getline(iss, airportName, ',');
        std::getline(iss, cityName, ',');
        std::getline(iss, country, ',');
        iss >> airportLatitude;
        iss.ignore();
        iss >> airportLongitude;
        iss.ignore();

        flightsManager.addCity(cityName, country);
        City* cityPtr = flightsManager.findCity(cityName, country);

        flightsManager.addAirport(airportCode, airportName, cityPtr, airportLatitude, airportLongitude);
        Airport* airportPtr = flightsManager.findAirport(airportCode);
        cityPtr->addAirport(airportPtr);
    }
    ifs.close();
}
