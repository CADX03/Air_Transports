#ifndef MENU_H
#define MENU_H

#include "airportsfilemanager.h"
#include "airlinesfilemanager.h"
#include "flightsfilemanager.h"


class Menu {
public:
    Menu(FlightsManager& flightsManager, AirportsFileManager& airportsFileManager, AirlinesFileManager& airlinesFileManager, FlightsFileManager& flightsFileManager);

    /**
     * A start method responsible for setting up the Menu.
     */
    void start();

private:
    /**
    * An enum.\n
    * Each State represents a different menu of the global Menu.
    */
    enum State {LoadMenu, MainMenu, AirportMenu, FlightsMenu, StatisticsMenu, Exit};
    State state_;

    /**
     * Checks if the user input is a number of type integer.
     * @return An integer corresponding to the user's choice.
     */
    static int checkValidInput();

    /**
    * Checks if the user input is a natural number.
    * @return An integer corresponding to the user's choice.
    */
    static int checkInputGreaterThanZero();

    /**
    * Checks if the user input is either Yes or No.
    * @return Returns true if the user's answer is yes and false if it is no.
    */
    static bool checkYesOrNo();

    /**
    * Checks if the user input is a valid airport code.
    * @return A pointer to an airport.
    */
    Airport* checkValidInputAirport() const;

    /**
    * Checks if the user input is a valid city name and country.
    * @return A pointer to a city.
    */
    City* checkValidInputCity() const;

    /**
    * Checks if the user input is a valid airline code.
    * @return A pointer to an airline.
    */
    Airline* checkValidInputAirline() const;

    /**
    * Checks if the user input is a valid latitude value.
    * @return A double corresponding to the latitude (between -90 and 90).
    */
    static double checkValidInputLatitude();

    /**
    * Checks if the user input is a valid longitude value.
    * @return A double corresponding to the longitude (between -180 and 180).
    */
    static double checkValidInputLongitude();

    /**
    * Checks if the user input is a valid radius value.
    * @return A positive integer corresponding to the user's choice.
    */
    static double checkValidInputRadius();

    /**
    * Ask how does the user want to input each airport.
    */
    void askForAirports(std::vector<Airport*>& airports, bool& exit);

    /**
    * Ask the user for each airline input.
    */
    void askForAirlines(std::unordered_set<std::string>& airlinesCodes);

    /**
     * A method responsible for handling the different states of the Menu.
     */
    void handleState();

    /**
     * Prints the header of the Menu.\n
     * Time Complexity: O(1).
     */
    void showHeader() const;

    /**
     * Prints the footer of the Menu.\n
     * Time Complexity: O(1).
     */
    void showFooter() const;

    /**
     * Prints all the different options in the Load Menu and manages the user inputs.
     */
    void showLoadMenu();

    /**
     * Prints all the different options in the Main Menu and manages the user inputs.
     */
    void showMainMenu();

    /**
    * Prints all the different options in the Airport Menu and manages the user inputs.
    */
    void showAirportMenu();

    /**
    * Prints all the different options in the Flights Menu and manages the user inputs.
    */
    void showFlightsMenu();

    /**
    * Prints all the different options in the Statistics Menu and manages the user inputs.
    */
    void showStatisticsMenu();

    /**
    * Prints route.
    */
    void showRoute(const route& route);

    FlightsManager* flightsManager_;
    AirportsFileManager* airportsFileManager_;
    AirlinesFileManager* airlinesFileManager_;
    FlightsFileManager* flightsFileManager_;
};


#endif
