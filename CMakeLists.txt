# Setup the project
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(neutron_beam)


#Find Geant4 package, activating all available UI and Vis drivers by default
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
find_package(Geant4 REQUIRED ui_all vis_all)

#Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

#Locate sources and headers for this project
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


# Add the executable, and link it to the Geant4 libraries
add_executable(neutron_beam neutron_beam.cc ${sources} ${headers})
target_link_libraries(neutron_beam ${Geant4_LIBRARIES} )


#Copy all scripts to the build directory,
#this is so that we canrun the executable directly because
#it relies on these scripts being in the current working directory
set(neutron_beam_SCRIPTS

       vis.mac run.mac
 )


foreach(_script ${neutron_beam_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX

install(TARGETS neutron_beam DESTINATION bin)
