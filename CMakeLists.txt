#------------------------------------------------------------------------------------------------------------------------------
# $Id: CMakeLists.txt
# Code for induced fission
# Abhijit Bhattacharyya
#-------------------------------------------------------------------------------------------------------------------------------
#Setup
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(inducedFission)

option(WITH_GEANT4_UIVIS " Build with UI and Vis driver " ON)
if (WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/inc ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)

add_executable(inducedFission inducedFission.cc ${sources} ${headers})
target_link_libraries(inducedFission ${Geant4_LIBRARIES})

#-------------------------------------------------------------------------------------------------------------------------
# copy scripts to build directory
#--------------------------------------------------------------------------------------------------------------------------
set(inducedFission_SCRIPTS
  run.mac
  vis.mac
)
foreach(_script ${inducedFission_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )
  endforeach()


install(TARGETS inducedFission DESTINATION bin)
