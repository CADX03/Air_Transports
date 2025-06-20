#include "airline.h"


Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) {
    code_ = code;
    name_ = name;
    callsign_ = callsign;
    country_ = country;
}

void Airline::increaseFlights() {
    flights_++;
}

bool Airline::operator==(const Airline* airline) const { return this->code_ == airline->getCode(); }
bool Airline::operator==(const Airline& airline) const { return getCode() == airline.getCode(); }

bool Airline::operator<(const Airline& airline) const { return code_ < airline.getCode(); }

std::size_t Airline::operator()(const Airline* airline) const { return std::hash<std::string>()(airline->getCode()); }
std::size_t Airline::operator()(const Airline& airline) const { return std::hash<std::string>()(airline.getCode()); }

void Airline::show() const {
    std::cout << code_ << ", " << name_ << ", " << callsign_ << ", " << country_;
}
