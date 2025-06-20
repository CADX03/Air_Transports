#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "flightsmanager.h"


class FileManager {
public:
    virtual void load(FlightsManager &flightsManager, const std::string &file) = 0;
};


#endif
