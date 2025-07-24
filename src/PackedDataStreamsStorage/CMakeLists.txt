
# Add the Class directory to the sources
file(GLOB CLASS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Class/*.cc")

# Create the library or executable (choose one as needed)
add_library(PackedDataStreamsStorage SHARED ${CLASS_SOURCES})

# If you want to build an executable instead, use:
# add_executable(SignalsSlots ${CLASS_SOURCES})

# Optionally, include the Class directory for headers
target_include_directories(PackedDataStreamsStorage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PackedDataStreamsStorage PRIVATE DataStorage PackedDataStreamsFormat Experiment)
set_target_properties(PackedDataStreamsStorage PROPERTIES PREFIX "")
set_target_properties(PackedDataStreamsStorage PROPERTIES OUTPUT_NAME "PDSSinkFormat")
set_target_properties(PackedDataStreamsStorage PROPERTIES SUFFIX ".so")
