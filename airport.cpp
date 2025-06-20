#include "airport.h"


Airport::Airport(std::string code, std::string name, City *city, double latitude, double longitude) {
    code_ = code;
    name_ = name;
    city_ = city;
    latitude_ = latitude;
    longitude_ = longitude;
}

Airport::Airport(std::string code, std::string name, double latitude, double longitude) {
    code_ = code;
    name_ = name;
    city_ = nullptr;
    latitude_ = latitude;
    longitude_ = longitude;
}

bool Airport::operator==(const Airport* airport) const { return this->code_ == airport->getCode(); }
bool Airport::operator==(const Airport& airport) const { return code_ == airport.getCode(); }

bool Airport::operator<(const Airport& airport) const { return code_ < airport.getCode(); }

void Airport::show() const {
    std::cout << code_ << ", " << name_ << ", ";
    city_->show();
}