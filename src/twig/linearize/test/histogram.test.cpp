#include <vector>

#include "catch.hpp"
#include "twig.hpp"
#include <iostream>
using namespace njoy::twig;

const auto ninfinity = -std::numeric_limits< double >::infinity();

SCENARIO("linearizing a histogram region"){
  std::vector< double > fine{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
  std::vector< double > histogram{ 1.0, 3.0, 6.0 };
  std::vector< double > sink;

  auto first = fine.begin();
  linearize::histogram( first, fine.end() - 1,  histogram.begin(), sink );
  REQUIRE( first == (fine.end() - 1) );
  
  std::vector< double > reference{ 1.0, 2.0,
                                   std::nextafter( 3.0, ninfinity ),
                                   3.0, 4.0, 5.0,
                                   std::nextafter( 6.0, ninfinity ) };
  REQUIRE( sink == reference );
}

SCENARIO("linearizing a histogram region with sink with nudge collision"){
  std::vector< double > fine{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
  std::vector< double > histogram{ 1.0, 3.0, 6.0 };
  std::vector< double > sink{ std::nextafter( 1.0, ninfinity ) };

  auto first = fine.begin();
  linearize::histogram( first, fine.end() - 1,  histogram.begin(), sink );
  REQUIRE( first == (fine.end() - 1) );
  
  std::vector< double > reference{ std::nextafter( 1.0, ninfinity ),
                                   1.0, 2.0,
                                   std::nextafter( 3.0, ninfinity ),
                                   3.0, 4.0, 5.0,
                                   std::nextafter( 6.0, ninfinity ) };
  REQUIRE( sink == reference );
}
