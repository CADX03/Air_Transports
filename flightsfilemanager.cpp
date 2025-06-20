#include "flightsfilemanager.h"

FlightsFileManager::FlightsFileManager() { ; }

void FlightsFileManager::load(FlightsManager &flightsManager, const std::string &file) {
    std::ifstream ifs("../dataset/"+file);
    std::string header;
    std::getline(ifs, header);

    for(std::string line; std::getline(ifs, line);){
        std::istringstream iss(line);
        std::string source;
        std::string target;
        std::string airline;
        std::getline(iss, source, ',');
        std::getline(iss, target, ',');
        std::getline(iss, airline, ',');

        if (!airline.empty() && airline[airline.size() - 1] == '\r')
            airline.erase(airline.size() - 1);

        flightsManager.addFlight(source, target, airline);
    }
    ifs.close();
}
