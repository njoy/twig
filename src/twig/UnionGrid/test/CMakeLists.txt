
add_executable( twig.UnionGrid.test
                merge.test.cpp
                unique.test.cpp
                UnionGrid.test.cpp )
target_compile_options( twig.UnionGrid.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${twig_appended_flags} )
target_link_libraries( twig.UnionGrid.test PUBLIC twig ) 
add_test( NAME twig.UnionGrid COMMAND twig.UnionGrid.test )
