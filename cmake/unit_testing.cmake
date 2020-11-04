#######################################################################
# Setup
#######################################################################

message( STATUS "Adding twig unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/twig/UnionGrid/test )
add_subdirectory( src/twig/linearize/Callable/test )
add_subdirectory( src/twig/linearize/test )
