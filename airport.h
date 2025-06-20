#ifndef AIRPORT_H
#define AIRPORT_H

#include "city.h"


class City; // forward dependency of class city

class Airport {
public:
    Airport(std::string code, std::string name, double latitude, double longitude);
    Airport(std::string code, std::string name, City* city, double latitude, double longitude);

    void setCode(std::string code) { code_ = code; }
    std::string getCode() const { return code_; }

    void setName(std::string name) { name_ = name; }
    std::string getName() const { return name_; }

    void setCity(City* city) { city_ = city; }
    City* getCity() const { return city_; }

    void setLatitude(double latitude) { latitude_ = latitude; }
    double getLatitude() const { return latitude_; }

    void setLongitude(double longitude) { longitude_ = longitude; }
    double getLongitude() const { return longitude_; }

    bool operator==(const Airport* airport) const;
    bool operator==(const Airport& airport) const;

    bool operator<(const Airport& airport) const;

    /**
     * A method to print the information about an airport.\n
     * It prints the corresponding code, name, city and country.\n
     * Time Complexity: O(1).
     */
    void show() const;

private:
    std::string code_;
    std::string name_;
    City* city_;
    double latitude_;
    double longitude_;
};

template<> struct std::hash<Airport> {
    std::size_t operator()(Airport const& airport) const noexcept {
        return std::hash<std::string>()(airport.getCode());
    }
};

/**
 * A functor to compare two pointers to airports.\n
 * Return true if airport1 is lower than airport2.
 */
struct AirportPointerLower
{
    bool operator()(const Airport* airport1, const Airport* airport2) const { return *airport1 < *airport2; }
};

/**
 * A functor to compare two pointers to airports.\n
 * Return true if airport1 is equal to airport2.
 */
struct AirportPointerComparison
{
    bool operator()(const Airport* airport1, const Airport* airport2) const { return *airport1 == *airport2; }
};

struct AirportHashFunction
{
    std::size_t operator()(const Airport* airport) const { return std::hash<Airport>()(*airport); }
};


#endif
