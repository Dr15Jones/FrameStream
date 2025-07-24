
# Add the Class directory to the sources
file(GLOB CLASS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.c")

# Create the library or executable (choose one as needed)
add_library(Interpreter SHARED ${CLASS_SOURCES})

# If you want to build an executable instead, use:
# add_executable(SignalsSlots ${CLASS_SOURCES})

# Optionally, include the Class directory for headers
target_include_directories(Interpreter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Readline_INCLUDE_DIR})

#target_link_libraries(Interpreter PUBLIC CommandPattern ToolBox Utility Experiment TCL Readline)
target_link_libraries(Interpreter PUBLIC CommandPattern ToolBox Utility Experiment TCL ${Readline_LIBRARY} ${History_LIBRARY})