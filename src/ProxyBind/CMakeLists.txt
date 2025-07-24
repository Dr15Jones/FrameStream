
# Add the Class directory to the sources
file(GLOB CLASS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.cc")

# Create the library or executable (choose one as needed)
add_library(ProxyBind SHARED ${CLASS_SOURCES})

# Optionally, include the Class directory for headers
target_include_directories(ProxyBind PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ProxyBind PUBLIC DataHandler ToolBox Utility Experiment)