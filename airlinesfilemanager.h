#ifndef AIRLINESFILEMANAGER_H
#define AIRLINESFILEMANAGER_H

#include <fstream>
#include <sstream>
#include "filemanager.h"


class AirlinesFileManager : public FileManager{
public:
    AirlinesFileManager();

    /**
     * A method that loads and reads a file and stores the information about the airlines in the respective data structures of a Flights Manager.\n
     * Time Complexity: O(n).
     * @param file A string corresponding to the file's path in the system.
     * @param flightsManager A reference to a Flights Manager.
     */
    void load(FlightsManager& flightsManager, const std::string& file = "airlines.csv") override;
};


#endif
