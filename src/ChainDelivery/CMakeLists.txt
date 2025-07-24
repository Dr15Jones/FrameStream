
# Create the library or executable (choose one as needed)
add_library(ChainDelivery INTERFACE)

target_include_directories(
  ChainDelivery
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(ChainDelivery INTERFACE DataDelivery Experiment)