
# Add the Class directory to the sources
file(GLOB CLASS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.cc")

file(GLOB INSTANTIATE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Instantiate/*.cc")

# Create the library or executable (choose one as needed)
add_library(BlankRecordDelivery SHARED ${CLASS_SOURCES} ${INSTANTIATE_SOURCES})

# Optionally, include the Class directory for headers
target_include_directories(BlankRecordDelivery PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(BlankRecordDelivery PUBLIC ChainDelivery DataDelivery Experiment)