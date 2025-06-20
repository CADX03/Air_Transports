#include "application.h"


Application* Application::instance_ = nullptr;

Application::Application() {;}

Application *Application::getInstance() {
    if(instance_ == nullptr) instance_ = new Application();
    return instance_;
}

void Application::run() {
    FlightsManager flightsManager = FlightsManager();

    AirportsFileManager airportsFileManager = AirportsFileManager();
    AirlinesFileManager airlinesFileManager = AirlinesFileManager();
    FlightsFileManager flightsFileManager = FlightsFileManager();

    Menu menu = Menu(flightsManager, airportsFileManager, airlinesFileManager, flightsFileManager);
    menu.start();
}
