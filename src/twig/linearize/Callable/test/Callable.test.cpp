#include <cmath>
#include <limits>

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "twig.hpp"

using namespace njoy::twig;

SCENARIO("Broken stick implementation"){
  std::vector< double > instance;
  instance.reserve(100);

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

  auto linearization = linearize::callable< double >( instance );
  auto first = xgrid.begin();
  auto last = xgrid.end() - 1;
  linearization( first, last, functor, criterion, midpoint );
  CHECK( first == last );


  auto iterator = instance.begin();

  auto left = [&iterator](){ return iterator[0]; };
  auto right = [&iterator](){ return iterator[1]; };

  auto x = []( auto value ){ return value; };
  auto y = [&]( auto value ){ return functor( value ); };

  while ( iterator != std::prev( instance.end() ) ){
    const auto midpoint = 0.5 * ( x( left() ) + x( right() ) );
    const auto trial = 0.5 * ( y( left() ) + y( right() ) );
    const auto reference = y( midpoint );
    CHECK( criterion( trial, reference,
                       x( left() ), x( right() ),
                       y( left() ), y( right() ) ) );
    ++iterator;
  }
}  
