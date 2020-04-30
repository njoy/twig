#include <cmath>
#include <limits>

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "twig.hpp"

using namespace njoy::twig;

SCENARIO("Broken stick implementation"){
  std::vector< double > xInstance;
  std::vector< double > yInstance;
  xInstance.reserve(100);
  yInstance.reserve(100);

  std::vector< double > xgrid{ 1.0, 5.0, 13.0, 29.0 };

  auto functor = []( auto&& x ){ return std::exp(x); };
  auto criterion = []( auto&& trial, auto&& reference,
                       auto&& xLeft, auto&& xRight,
                       auto&&,       auto&& ){
    const auto infinity = std::numeric_limits<double>::infinity();
    if ( xRight == std::nextafter( xLeft, infinity ) ){ return true; }
    auto difference = std::abs( trial - reference );
    return ( difference < 1E-10 ) || ( (difference / reference) < 1E-4 );
  };

  auto midpoint = []( auto&& x, auto&& ){
    return 0.5 * ( std::get<0>(x) + std::get<1>(x) );
  };

  auto linearization = linearize::callable( xInstance, yInstance );
  auto first = xgrid.begin();
  auto last = xgrid.end();
  linearization( first, last, functor, criterion, midpoint );
  CHECK( first == last );

  // Make sure all the original x values are in the linearized x
  for( double& x : xgrid ){
    CHECK( std::any_of( xInstance.begin(), xInstance.end(), 
                        [&]( auto& arg ){ return arg == x; } ) );
  }
  
  auto length = xInstance.size();
  CHECK( 1793 == length );
  for (size_t i{ 0 }; i < length; ++i) {
    CHECK( yInstance[ i ] == functor( xInstance[ i ] ) );
  }
}  
