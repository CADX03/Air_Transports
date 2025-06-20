#include "utils.h"


double calculateDistance(const double& lat1, const double& long1, const double& lat2, const double& long2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (long2 - long1) * M_PI / 180.0;

    double rLat1 = (lat1) * M_PI / 180.0;
    double rLat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(rLat1) * cos(rLat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}
