
# Add the Class directory to the sources
file(GLOB CLASS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.cc")

# Create the library or executable (choose one as needed)
add_library(Signal SHARED ${CLASS_SOURCES})

# Optionally, include the Class directory for headers
target_include_directories(Signal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Signal
    PUBLIC
    Experiment)