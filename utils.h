#ifndef UTILS_H
#define UTILS_H

#include <cmath>

/**
 * A method that calculates the distance between two points in kilometers using the Haversine formula.\n
 * @param lat1 A double corresponding to the latitude of the first point.
 * @param long1 A double corresponding to the longitude of the first point.
 * @param lat2 A double corresponding to the latitude of the second point.
 * @param long2 A double corresponding to the longitude of the second point.
 * @return A double corresponding to the distance between the two points in kilometers.
 */
double calculateDistance(const double& lat1, const double& long1, const double& lat2, const double& long2);


#endif
