
# Add the Class directory to the sources
file(GLOB CLASS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.cc")
file(GLOB CLASS_COMPRESSION_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/Compression/*.cc")

# Create the library or executable (choose one as needed)
add_library(StorageManagement SHARED ${CLASS_SOURCES} ${CLASS_COMPRESSION_SOURCES})

# If you want to build an executable instead, use:
# add_executable(SignalsSlots ${CLASS_SOURCES})

# Optionally, include the Class directory for headers
target_include_directories(StorageManagement PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(StorageManagement PUBLIC
    DataHandler Experiment)