﻿cmake_minimum_required(VERSION 3.27)

project($(name))

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

################# create target #######################################################

file(GLOB_RECURSE Headers CONFIGURE_DEPENDS src/*.h src/*.hpp src/*.hxx)
file(GLOB_RECURSE PublicHeaders CONFIGURE_DEPENDS include/*.h include/*.hpp include/*.hxx)
file(GLOB_RECURSE Sources CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${Headers} ${PublicHeaders} ${Sources})

#######################################################################################

################# set install directories #############################################

string(REGEX REPLACE "^.*\\(([0-9]+\.[0-9]+\.[0-9]+\.[0-9]+).*$" "\\1" _ARP_SHORT_DEVICE_VERSION ${ARP_DEVICE_VERSION})
set(INCLUDE_INSTALL_DIR ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/include)
set(LIB_INSTALL_DIR ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/lib/${PROJECT_NAME})

#######################################################################################

################# project include-paths ###############################################

target_include_directories(${PROJECT_NAME}
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>)

#######################################################################################

################# include arp cmake module path #######################################

list(INSERT CMAKE_MODULE_PATH 0 "${ARP_TOOLCHAIN_CMAKE_MODULE_PATH}")

#######################################################################################

################# set RPATH to ORIGIN for thrid party libraries #######################
# Only by setting this is it possible to use libraries which are not already          #
# installed in the default install locations on the target.                           #
#######################################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH $ORIGIN)

#######################################################################################

################# set link options ####################################################
# WARNING: Without --no-undefined the linker will not check, whether all necessary    #
#          libraries are linked. When a library which is necessary is not linked,     #
#          the firmware will crash and there will be NO indication why it crashed.    #
#######################################################################################

target_link_options(${PROJECT_NAME} PRIVATE LINKER:--no-undefined)  
target_link_options(${PROJECT_NAME} PRIVATE LINKER:--as-needed)

#######################################################################################

################# add link targets ####################################################

find_package(ArpDevice REQUIRED)

if(${ARP_VERSION_MAJOR} GREATER_EQUAL "25")
    find_package(Arp REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Arp::ALL)
else()
    find_package(ArpProgramming REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ArpDevice ArpProgramming)
endif()

#######################################################################################

################# configure cmake package config files ################################
# IMPORTANT: The library version is set here.									      #
#######################################################################################

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  "Config.cmake.in" 
  "${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/cmake
  PATH_VARS
    INCLUDE_INSTALL_DIR
	LIB_INSTALL_DIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )

#######################################################################################

########## install public headers while retaining the directory structure #############

file(GLOB _DEPLOY_HEADERS_AND_DIRS include/*)
set(_DIRS_TO_DEPLOY "")
set(_FILES_TO_DEPLOY "")
foreach(ITEM ${_DEPLOY_HEADERS_AND_DIRS})
   if( IS_DIRECTORY "${ITEM}" )
      list( APPEND _DIRS_TO_DEPLOY "${ITEM}" )
   elseif(NOT ITEM MATCHES ".*ADD_PUBLIC_HEADERS_HERE")
      list( APPEND _FILES_TO_DEPLOY "${ITEM}" )
   endif()
endforeach()
install( FILES ${_FILES_TO_DEPLOY} DESTINATION ${INCLUDE_INSTALL_DIR} )
install( DIRECTORY ${_DIRS_TO_DEPLOY} DESTINATION ${INCLUDE_INSTALL_DIR} )
unset(_FILES_TO_DEPLOY)
unset(_DIRS_TO_DEPLOY)
unset(_DEPLOY_HEADERS_AND_DIRS)

#######################################################################################

################# install CMake package and library ###################################

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets DESTINATION ${LIB_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets DESTINATION ${LIB_INSTALL_DIR})
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${ARP_DEVICE}_${_ARP_SHORT_DEVICE_VERSION}/${CMAKE_BUILD_TYPE}/cmake"
  )
unset(_ARP_SHORT_DEVICE_VERSION)

#######################################################################################