#ifndef AIRLINES_H
#define AIRLINES_H

#include <iostream>
#include "string"


class Airline {
public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);

    void setCode(std::string code) { code_ = code; }
    std::string getCode() const { return code_; }

    void setName(std::string name) { name_ = name; }
    std::string getName() const { return name_; }

    void setCallsign(std::string callsign) { callsign_ = callsign; }
    std::string getCallsign() const { return callsign_; }

    void setCountry(std::string country) { country_ = country; }
    std::string getCountry() const { return country_; }

    void setFlights(int flights) { flights_ = flights; }
    int getFlights() const { return flights_; }

    /**
     * Increments the private field flights_.\n
     * Time Complexity: O(1).
     */
    void increaseFlights();

    bool operator==(const Airline* airline) const;
    bool operator==(const Airline& airline) const;

    bool operator<(const Airline& airline) const;

    std::size_t operator()(const Airline* airline) const;
    std::size_t operator()(const Airline& airline) const;

    /**
     * A method to print the information about an airline.\n
     * It prints the corresponding code, name, call sign and country.\n
     * Time Complexity: O(1).
     */
    void show() const;

private:
    std::string code_;
    std::string name_;
    std::string callsign_;
    std::string country_;
    int flights_ = 0;
};

/**
 * A functor to compare two pointers to airlines.\n
 * Return true if airline1 is lower than airline2.
 */
struct AirlinePointerLower
{
    bool operator()(const Airline* airline1, const Airline* airline2) const { return *airline1 < *airline2; }
};

/**
 * A functor to compare two pointers to airlines.\n
 * Return true if airline1 is equal to airline2.
 */
struct AirlinePointerComparison
{
    bool operator()(const Airline* airline1, const Airline* airline2) const { return *airline1 == *airline2; }
};

struct AirlineHashFunction
{
    std::size_t operator()(const Airline* airline) const { return std::hash<std::string>()(airline->getCode()); }
};

/**
 * A functor to compare two pointers to airlines.\n
 * Return true if airline1 has less flights then airline2. If the number of flights is the same, compares the airlines' codes.
 */
struct AirlinePointerLowerNumFlights
{
    bool operator()(const Airline* airline1, const Airline* airline2) const {
        if(airline1->getFlights() < airline2->getFlights()) return true;
        if(airline1->getFlights() == airline2->getFlights() && airline1->getCode() > airline2->getCode()) return true;
        return false;
    }
};


#endif
