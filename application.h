#ifndef APPLICATION_H
#define APPLICATION_H

#include "menu.h"


class Application {
public:
    Application(Application&) = delete;
    void operator=(const Application&) = delete;
    static Application* getInstance();

    /**
    * A run method responsible for setting up the reading of the files and the loading of its information to the respective data structures.
    */
    void run();

private:
    Application();
    static Application* instance_;
};


#endif
