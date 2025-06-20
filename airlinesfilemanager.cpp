#include "airlinesfilemanager.h"


AirlinesFileManager::AirlinesFileManager() { ; }

void AirlinesFileManager::load(FlightsManager &flightsManager, const std::string &file) {
    std::ifstream ifs("../dataset/"+file);
    std::string header;
    std::getline(ifs, header);

    for(std::string line; std::getline(ifs, line);){
        std::istringstream iss(line);
        std::string airlineCode;
        std::string airlineName;
        std::string callsign;
        std::string country;
        std::getline(iss, airlineCode, ',');
        std::getline(iss, airlineName, ',');
        std::getline(iss, callsign, ',');
        std::getline(iss, country, ',');

        if (!country.empty() && country[country.size() - 1] == '\r')
            country.erase(country.size() - 1);

        flightsManager.addAirline(airlineCode, airlineName, callsign, country);
    }
    ifs.close();
}
