
# Add the Class directory to the sources
file(GLOB CLASS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.cc")

# Create the library or executable (choose one as needed)
add_library(DBEventHeaderProd SHARED ${CLASS_SOURCES})

# If you want to build an executable instead, use:
# add_executable(SignalsSlots ${CLASS_SOURCES})

# Optionally, include the Class directory for headers
target_include_directories(DBEventHeaderProd PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(DBEventHeaderProd PRIVATE Processor CleoDB Experiment)
set_target_properties(DBEventHeaderProd PROPERTIES PREFIX "")
set_target_properties(DBEventHeaderProd PROPERTIES SUFFIX ".so")
