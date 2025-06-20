#include "city.h"


City::City(std::string name, std::string country) {
    name_ = name;
    country_ = country;
}

City::City(std::string name, std::string country, std::vector<Airport*> airports) {
    name_ = name;
    country_ = country;
    airports_ = airports;
}

void City::addAirport(Airport* airport) { airports_.push_back(airport); }

bool City::operator==(const City* city) const { return this->name_ == city->getName() && this->country_ == city->getCountry(); }
bool City::operator==(const City& city) const { return name_ == city.getName() && country_ == city.getCountry(); }

bool City::operator<(const City& city) const {
    if(name_ < city.getName()) return true;
    if(name_ == city.getName() && country_ < city.getName()) return true;
    return false;
}

void City::show() const {
    std::cout << name_ << ", " << country_;
}
