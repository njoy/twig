########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )
project( twig LANGUAGES CXX )


########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option( twig_unit_tests
    "Compile the twig unit tests and integrate with ctest" ON
    )


########################################################################
# Dependencies
########################################################################

include( cmake/twig_dependencies.cmake )


########################################################################
# Project targets
########################################################################

add_library( twig INTERFACE )
target_include_directories( twig INTERFACE src/ )
target_link_libraries( twig
    INTERFACE catch-adapter
    )


#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( twig_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
