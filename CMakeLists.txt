cmake_minimum_required(VERSION 3.24)
project(aed2223_project2)

set(CMAKE_CXX_STANDARD 23)

add_executable(aed2223_project2 main.cpp graph.h graph.cpp airport.cpp airport.h city.cpp city.h airline.cpp airline.h flightsmanager.cpp flightsmanager.h filemanager.h airportsfilemanager.cpp airportsfilemanager.h airlinesfilemanager.cpp airlinesfilemanager.h flightsfilemanager.cpp flightsfilemanager.h application.cpp application.h menu.cpp menu.h utils.cpp utils.h)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)