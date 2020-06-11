#######################################################################
# Setup
#######################################################################

message( STATUS "Adding NJOY21 unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/twig/UnionGrid/test )
add_subdirectory( src/twig/linearize/test )
add_subdirectory( src/twig/linearize/Callable/test )
