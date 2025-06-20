#include "application.h"


int main() {
    Application* application = Application::getInstance();
    application->run();
    return 0;
}
