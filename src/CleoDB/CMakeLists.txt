
# Add the Class directory to the sources
file(GLOB CLASS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.cc")
file(GLOB INSTANTIATE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Instantiate/*.cc")

# Create the library or executable (choose one as needed)
add_library(CleoDB SHARED ${CLASS_SOURCES} ${INSTANTIATE_SOURCES})

# If you want to build an executable instead, use:
# add_executable(SignalsSlots ${CLASS_SOURCES})

# Optionally, include the Class directory for headers
target_include_directories(CleoDB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CleoDB PUBLIC FrameAccess DataDelivery StorageManagement DataHandler Experiment)