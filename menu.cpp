#include "menu.h"

Menu::Menu(FlightsManager& flightsManager, AirportsFileManager& airportsFileManager, AirlinesFileManager& airlinesFileManager, FlightsFileManager& flightsFileManager){
    flightsManager_ = &flightsManager;
    airportsFileManager_ = &airportsFileManager;
    airlinesFileManager_ = &airlinesFileManager;
    flightsFileManager_ = &flightsFileManager;
}

int Menu::checkValidInput() {
    int choice;
    std::cout << "Select an option: ";
    std::cin >> choice;

    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Invalid input. Please, enter a number: ";
        std::cin >> choice;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout << std::endl;
    return choice;
}

int Menu::checkInputGreaterThanZero() {
    int choice;
    std::cin >> choice;

    while(std::cin.fail() || choice <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Invalid input. Please, enter an integer greater than 0: ";
        std::cin >> choice;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout << std::endl;
    return choice;
}

bool Menu::checkYesOrNo() {
    while(true){
        std::string check;
        std::getline(std::cin, check);
        std::cout << std::endl;
        if(check == "No" || check == "no" || check == "NO") return false;
        else if (check == "Yes" || check == "yes" || check == "YES") return true;
        else std::cout << "ERROR: Invalid input. Please, answer 'Yes' or 'No'. ";
    }
}

Airport* Menu::checkValidInputAirport() const {
    std::string airportCode;
    std::cout << "Please, insert the airport code: ";
    std::getline(std::cin, airportCode);
    std::cout << std::endl;

    Airport* airport = flightsManager_->findAirport(airportCode);
    if(airport == nullptr) std::cout << "This airport couldn't be found in the system." << std::endl;
    return airport;
}

City* Menu::checkValidInputCity() const {
    std::string cityName;
    std::string country;
    std::cout << "Please, insert the city name: ";
    std::getline(std::cin, cityName);
    std::cout << std::endl;
    std::cout << "Please, insert the country: ";
    std::getline(std::cin, country);
    std::cout << std::endl;

    City* city = flightsManager_->findCity(cityName, country);
    if(city == nullptr) std::cout << "This city couldn't be found in the system." << std::endl;
    return city;
}

Airline* Menu::checkValidInputAirline() const {
    std::string airlineCode;
    std::cout << "Please, insert the airline code: ";
    std::getline(std::cin, airlineCode);
    std::cout << std::endl;

    Airline* airline = flightsManager_->findAirline(airlineCode);
    if(airline == nullptr) std::cout << "This airline couldn't be found in the system." << std::endl;
    return airline;
}

double Menu::checkValidInputLatitude() {
    double latitude;
    std::cout << "Please, insert the latitude [-90.0, 90.0]: ";
    std::cin >> latitude;

    while(std::cin.fail() || latitude < -90 || latitude > 90) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Invalid input. Please, enter a number between -90.0 and 90.0: ";
        std::cin >> latitude;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout << std::endl;
    return latitude;
}

double Menu::checkValidInputLongitude() {
    double longitude;
    std::cout << "Please, insert the longitude [-180.0, 180.0]: ";
    std::cin >> longitude;

    while(std::cin.fail() || longitude < -180 || longitude > 180) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Invalid input. Please, enter a number between -180.0 and 180.0: ";
        std::cin >> longitude;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout << std::endl;
    return longitude;
}

double Menu::checkValidInputRadius() {
    double radius;
    std::cout << "Please, insert the radius: ";
    std::cin >> radius;

    while(std::cin.fail() || radius < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Invalid input. Please, enter a positive number: ";
        std::cin >> radius;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout << std::endl;
    return radius;
}

void Menu::showHeader() const {
    std::cout << "---------- FLIGHTS MANAGER ----------" << std::endl;
}

void Menu::showFooter() const {
    std::cout << std::endl;
    std::cout << "9. Back" << std::endl;
    std::cout << "0. Start Menu" << std::endl;
    std::cout << std::endl;
}

void Menu::start() {
    state_ = State::LoadMenu;
    while(state_ != State::Exit){
        handleState();
    }
}

void Menu::askForAirports(std::vector<Airport*>& airports, bool& exit) {
    std::cout << "1. Airport" << std::endl;
    std::cout << "2. City" << std::endl;
    std::cout << "3. Coordinates" << std::endl;
    std::cout << std::endl;
    std::cout << "0. Quit" << std::endl;
    std::cout << std::endl;

    int choice = checkValidInput();

    switch (choice) {
        case 1:{
            while(true){
                Airport* airport = checkValidInputAirport();
                if(airport != nullptr) airports.push_back(airport);
                std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                if(!checkYesOrNo()) break;
            }
            if(airports.empty()){
                exit = true;
                std::cout << "No valid airports inserted. " << std::endl;
                std::cout << std::endl;
                return;
            }
            break;
        }
        case 2:{
            while(true){
                City* city = checkValidInputCity();
                if(city != nullptr) {
                    airports = city->getAirports();
                    break;
                }
                else {
                    std::cout << "Would you like to try another city ['Yes' or 'No']?" << std::endl;
                    if(!checkYesOrNo()) break;
                }
            }
            if(airports.empty()){
                exit = true;
                std::cout << "No valid airports inserted. " << std::endl;
                std::cout << std::endl;
                return;
            }
            break;
        }
        case 3:{
            double latitude = checkValidInputLatitude();
            double longitude = checkValidInputLongitude();
            double radius = checkValidInputRadius();
            airports = flightsManager_->airportsInRange(latitude, longitude, radius);
            break;
        }
        case 0:
            exit = true;
            return;
        default:
            return;
    }
}

void Menu::askForAirlines(std::unordered_set<std::string>& airlinesCodes) {
    while(true){
        Airline* airline = checkValidInputAirline();
        if(airline != nullptr) airlinesCodes.insert(airline->getCode());
        std::cout << "Would you like to insert another airline ['Yes' or 'No']?" << std::endl;
        if(!checkYesOrNo()) break;
    }
    if(airlinesCodes.empty()){
        std::cout << "No valid airlines inserted. " << std::endl;
        return;
    }
}

void Menu::handleState() {
    switch (state_) {
        case State::LoadMenu:
            showLoadMenu();
            break;
        case State::MainMenu:
            showMainMenu();
            break;
        case State::AirportMenu:
            showAirportMenu();
            break;
        case State::FlightsMenu:
            showFlightsMenu();
            break;
        case State::StatisticsMenu:
            showStatisticsMenu();
            break;
    }
}

void Menu::showLoadMenu() {
    showHeader();
    std::string airportsFile;
    std::string airlinesFile;
    std::string flightsFile;

    std::cout << std::endl;
    std::cout << "Choose the file from which you want to load the airports and cities information [airports.csv]: ";
    std::getline(std::cin, airportsFile);
    std::cout << "Choose the file from which you want to load the airlines information [airlines.csv]: ";
    std::getline(std::cin, airlinesFile);
    std::cout << "Choose the file from which you want to load the flights information [flights.csv]: ";
    std::getline(std::cin, flightsFile);
    std::cout << std::endl;

    if(airportsFile.empty()) airportsFileManager_->load(*flightsManager_);
    else airportsFileManager_->load(*flightsManager_, airportsFile);

    if(airlinesFile.empty())  airlinesFileManager_->load(*flightsManager_);
    airlinesFileManager_->load(*flightsManager_, airlinesFile);

    flightsManager_->resetFlights();
    if(flightsFile.empty()) flightsFileManager_->load(*flightsManager_);
    flightsFileManager_->load(*flightsManager_, flightsFile);

    state_ = State::MainMenu;
}

void Menu::showMainMenu() {
    showHeader();

    int choice;
    std::cout << "1. Check information about an airport" << std::endl;
    std::cout << "2. Check flights" << std::endl;
    std::cout << "3. Statistics about the network" << std::endl;
    std::cout << "9. Credits" << std::endl;
    std::cout << std::endl;
    std::cout << "0. Quit" << std::endl;
    std::cout << std::endl;

    choice = checkValidInput();

    switch (choice) {
        case 1 :
            state_ = AirportMenu;
            break;
        case 2:
            state_ = FlightsMenu;
            break;
        case 3:
            state_ = StatisticsMenu;
            break;
        case 9:
            std::cout << "Software developed by:" << std::endl;
            std::cout << "Joao Costa" << " - " << "Marco Costa" << " - " << "Tiago Viana" << std::endl;
            std::cout << "G40" << " - " << "2LEIC04" << " - " << "AED 2022/2023" << std::endl;
            std::cout << std::endl;
            return;
        case 0:
            state_ = State::Exit;
            return;
        default:
            return;
    }
}

void Menu::showAirportMenu() {
    showHeader();

    int choice;
    std::cout << "----- Information about an airport -----" << std::endl;
    std::cout << "1. Check number of flights" << std::endl;
    std::cout << "2. Check number of airlines" << std::endl;
    std::cout << "3. Check reachable airports" << std::endl;
    std::cout << "4. Check reachable cities" << std::endl;
    std::cout << "5. Check reachable countries" << std::endl;

    showFooter();

    choice = checkValidInput();

    switch (choice) {
        case 1: {
            while (true) {
                Airport* airport = checkValidInputAirport();
                if (airport == nullptr) {
                    std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                    if(!checkYesOrNo()) break;
                    else continue;
                }

                std::string airportCode = airport->getCode();
                size_t numFlights = flightsManager_->numFlightsAirport(airportCode);

                if (numFlights > 0) std::cout << "There were found " << numFlights << " flights departing from this airport." << std::endl;
                else if (numFlights == 0) std::cout << "No flights were found from this airport." << std::endl;

                std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                if(!checkYesOrNo()) break;
            }
            break;
        }
        case 2: {
            while (true) {
                Airport* airport = checkValidInputAirport();
                if (airport == nullptr) {
                    std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                    if(!checkYesOrNo()) break;
                    else continue;
                }

                std::string airportCode = airport->getCode();
                std::set<Airline *, AirlinePointerLower> airlines = flightsManager_->airlinesInAirport(airportCode);
                size_t numAirlines = airlines.size();

                if (numAirlines > 0) {
                    std::cout << "There were found " << numAirlines << " airlines in this airport." << std::endl;
                    std::cout << "Would you like to check more information about the airlines ['Yes' or 'No']?" << std::endl;
                    if(checkYesOrNo()) {
                        std::cout << "Information about the airlines:" << std::endl;
                        for (Airline* airline : airlines) {
                            airline->show();
                            std::cout << std::endl;
                        }
                        std::cout << std::endl;
                    }
                }

                else if (numAirlines == 0) std::cout << "No airlines were found in this airport." << std::endl;


                std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                if(!checkYesOrNo()) break;
            }
            break;
        }
        case 3: {
            while (true) {
                Airport *airport = checkValidInputAirport();
                if (airport == nullptr) {
                    std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                    if (!checkYesOrNo()) break;
                    else continue;
                }

                std::string airportCode = airport->getCode();
                std::cout << "Please, insert a maximum number of flights: ";
                int n = checkInputGreaterThanZero();
                std::set<Airport*, AirportPointerLower> airports = flightsManager_->reachableAirports(airportCode, n);
                size_t numAirports = airports.size();

                if (numAirports > 0) {
                    std::cout << "You can reach " << numAirports << " airports with a maximum of " << n << " flights departing from " << airportCode << "." << std::endl;
                    std::cout << "Would you like to check more information about those airports ['Yes' or 'No']?" << std::endl;
                    if(checkYesOrNo()) {
                        std::cout << "Information about the airports:" << std::endl;
                        for (Airport* airport1 : airports) {
                            airport1->show();
                            std::cout << std::endl;
                        }
                        std::cout << std::endl;
                    }
                }

                else if (numAirports == 0) std::cout << "You can't reach any airports with a maximum of " << n << " flights departing from " << airportCode << "." << std::endl;

                std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                if(!checkYesOrNo()) break;
            }
            break;
        }
        case 4: {
            while (true) {
                Airport *airport = checkValidInputAirport();
                if (airport == nullptr) {
                    std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                    if (!checkYesOrNo()) break;
                    else continue;
                }

                std::string airportCode = airport->getCode();
                std::cout << "Please, insert a maximum number of flights: ";
                int n = checkInputGreaterThanZero();
                std::set<City*, CityPointerLower> cities = flightsManager_->reachableCities(airportCode, n);
                size_t numCities = cities.size();

                if (numCities > 0) {
                    std::cout << "You can reach " << numCities << " cities with a maximum of " << n << " flights departing from " << airportCode << "." << std::endl;
                    std::cout << "Would you like to check more information about those cities ['Yes' or 'No']?" << std::endl;
                    if(checkYesOrNo()) {
                        std::cout << "Reachable cities:" << std::endl;
                        for (City* city : cities) {
                            city->show();
                            std::cout << std::endl;
                        }
                        std::cout << std::endl;
                    }
                }

                else if (numCities == 0) std::cout << "You can't reach any cities with a maximum of " << n << " flights departing from " << airportCode << "." << std::endl;

                std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                if(!checkYesOrNo()) break;
            }
            break;
        }
        case 5: {
            while (true) {
                Airport *airport = checkValidInputAirport();
                if (airport == nullptr) {
                    std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                    if (!checkYesOrNo()) break;
                    else continue;
                }

                std::string airportCode = airport->getCode();
                std::cout << "Please, insert a maximum number of flights: ";
                int n = checkInputGreaterThanZero();
                std::set<std::string> countries = flightsManager_->reachableCountries(airportCode, n);
                size_t numCountries = countries.size();

                if (numCountries > 0) {
                    std::cout << "You can reach " << numCountries << " countries with a maximum of " << n << " flights departing from " << airportCode << "." << std::endl;
                    std::cout << "Would you like to check more information about those countries ['Yes' or 'No']?" << std::endl;
                    if(checkYesOrNo()) {
                        std::cout << "Reachable countries:" << std::endl;
                        for (std::string country : countries) {
                            std::cout << country << std::endl;
                        }
                        std::cout << std::endl;
                    }
                }

                        else if (numCountries == 0) std::cout << "You can't reach any countriess with a maximum of " << n << " flights departing from " << airportCode << "." << std::endl;

                std::cout << "Would you like to insert another airport ['Yes' or 'No']?" << std::endl;
                if(!checkYesOrNo()) break;
            }
            break;
        }
        case 9: case 0:
            state_ = MainMenu;
        default:
            break;
    }
}

void Menu::showFlightsMenu() {
    showHeader();

    std::cout << "----- Check flights -----" << std::endl;
    std::cout << "How do you want to specify the departure point?" << std::endl;
    std::vector<Airport*> srcAirports;

    bool exit = false;
    askForAirports(srcAirports, exit);

    if (exit) {
        state_ = MainMenu;
        return;
    }

    std::cout << "How do you want to specify the arrival point?" << std::endl;
    std::vector<Airport*> destAirports;

    askForAirports(destAirports, exit);
    if (exit) {
        state_ = MainMenu;
        return;
    }

    std::unordered_set<std::string> airlinesCodes;
    std::cout << "Do you want to specify which airlines to use ['Yes' or 'No']?" << std::endl;
    if(checkYesOrNo()) askForAirlines(airlinesCodes);

    std::vector<route> routes = flightsManager_->findAllRoutes(srcAirports, destAirports, airlinesCodes);
    if(!routes.empty()){
        for(const route& r : routes){
            showRoute(r);
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    state_ = MainMenu;
}

void Menu::showStatisticsMenu() {
    showHeader();

    int choice;
    std::cout << "----- Statistics about the network -----" << std::endl;
    std::cout << "1. Articulation points" << std::endl;
    std::cout << "2. Top-k airlines with more flights" << std::endl;
    std::cout << "3. Top-k airports with more flights" << std::endl;
    std::cout << "4. Top-k airports with more airlines" << std::endl;
    std::cout << "5. Top-k cities with more airports" << std::endl;

    showFooter();

    choice = checkValidInput();

    switch (choice) {
        case 1:{
            std::set<Airport*, AirportPointerLower> airports = flightsManager_->articulationPoints();
            size_t numOfAirports = airports.size();

            std::cout << "The graph representing the flights between different airports has " << numOfAirports << " articulation points." << std::endl;

            std::cout << "Would you like to check which airports are the articulation points ['Yes' or 'No']?" << std::endl;
            if(checkYesOrNo()) {
                std::cout << "Information about the airlines:" << std::endl;
                for(Airport* a : airports){
                    a->show();
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
            break;
        }
        case 2: {
            std::cout << "Please insert k: ";
            int k = checkInputGreaterThanZero();
            auto airlines = flightsManager_->getAirlineByNumFlights();
            int rank = 1;
            while(k != 0 && !airlines.empty()){
                Airline* a = airlines.top();
                airlines.pop();
                std::cout << rank << ". ";
                a->show();
                std::cout << " with " << a->getFlights() << " flights.";
                std::cout << std::endl;
                k--;
                rank++;
            }
            std::cout << std::endl;
            break;
        }
        case 3: {
            std::cout << "Please insert k: ";
            int k = checkInputGreaterThanZero();
            auto airports = flightsManager_->getAirportsByNumFlights();
            int rank = 1;
            while(k != 0 && !airports.empty()){
                std::pair<Airport*, int> p = airports.top();
                airports.pop();
                std::cout << rank << ". ";
                p.first->show();
                std::cout << " with " << p.second << " flights.";
                std::cout << std::endl;
                k--;
                rank++;
            }
            std::cout << std::endl;
            break;
        }
        case 4: {
            std::cout << "Please insert k: ";
            int k = checkInputGreaterThanZero();
            auto airports = flightsManager_->getAirportsByNumAirlines();
            int rank = 1;
            while(k != 0 && !airports.empty()){
                std::pair<Airport*, int> p = airports.top();
                airports.pop();
                std::cout << rank << ". ";
                p.first->show();
                std::cout << " with " << p.second << " airlines.";
                std::cout << std::endl;
                k--;
                rank++;
            }
            std::cout << std::endl;
            break;
        }
        case 5: {
            std::cout << "Please insert k: ";
            int k = checkInputGreaterThanZero();
            std::priority_queue<City *, std::vector<City *>, CityPointerLowerNumAirports> cities = flightsManager_->getCitiesByNumAirports();
            int rank = 1;
            while(k != 0 && !cities.empty()){
                City* city = cities.top();
                cities.pop();
                std::cout << rank << ". ";
                city->show();
                std::cout << " with " << city->getAirports().size() << " airports.";
                std::cout << std::endl;
                k--;
                rank++;
            }
            std::cout << std::endl;
            break;
        }

        case 9: case 0:
            state_ = MainMenu;
        default:
            break;
    }
}

void Menu::showRoute(const route& route) {
    std::cout << route.first[0]->getCode() << ", ";
    route.first[0]->getCity()->show();
    for(int i = 1; i < route.first.size(); i++){
        std::cout << " [" << route.second[i-1]->getCode() << "] " << "-> " << route.first[i]->getCode() << ", ";
        route.first[i]->getCity()->show();
    }
}

