#ifndef AIRPORTSFILEMANAGER_H
#define AIRPORTSFILEMANAGER_H

#include "filemanager.h"
#include <fstream>
#include <sstream>


class AirportsFileManager : public FileManager {
public:
    AirportsFileManager();

    /**
     * A method that loads and reads a file and stores the information about the airports and the cities in the respective data structures of a Flights Manager.\n
     * Time Complexity: O(n).
     * @param file A string corresponding to the file's path in the system.
     * @param flightsManager A reference to a Flights Manager.
     */
    void load(FlightsManager& flightsManager, const std::string& file = "airports.csv") override;
};


#endif
