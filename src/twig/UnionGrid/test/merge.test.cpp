#include <random>

#include "catch.hpp"
#include "twig.hpp"

using namespace njoy::twig;

namespace {
class TestUnionGrid : public UnionGrid {
public:
  using UnionGrid::merge;
};
}

SCENARIO("UnionGrid merge"){
  GIVEN( "three sorted lists" ){
    std::vector< std::vector< int > > grids;
    grids.emplace_back( std::vector< int >( { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ) );
    grids.emplace_back( std::vector< int >( { 1, 3, 5, 7, 9 } ) );
    grids.emplace_back( std::vector< int >( { 0, 2, 4, 6, 8, 10 } ) );

    WHEN( "merged into a single list" ){
      THEN("the output will match the reference"){
	  std::vector<int> reference =
	    {{0,1,2,3,4,5,6,7,8,9,10}};
	  auto trial = TestUnionGrid::merge( grids );
	  REQUIRE( reference == trial );
      }
    }
  }

  GIVEN( "a list with equal elements and nudge collision" ){
    auto d = 1.0;
    std::vector< std::vector<double> > grids =
      { { 0.0, std::nextafter(d, -10.0), d, d, 2.0 },
	{ 0.0, 2.0 } };
    auto trial = TestUnionGrid::merge( grids );
    auto reference = std::vector<double>{ 0.0, std::nextafter(d, -10.0), d, 2.0 };
    REQUIRE( reference == trial );
  }

  GIVEN("many random (but sorted) lists"){
    std::minstd_rand0 generator( 3091988 );
    std::uniform_int_distribution<int> distribution(0,1000);
    std::vector< std::vector< int > > grids;
    int i = 100;
    while( --i ){
      std::vector< int > instance; instance.reserve(100);
      int j = 100;
      while( --j ){
	instance.push_back( distribution( generator ) );
      }
      // introduce duplicates
      if ( i%2 ) {
	instance.reserve(250);
	std::copy_n( instance.begin(), 100, std::back_inserter(instance) );
      }
      std::sort( instance.begin(), instance.end() );
      grids.push_back( std::move(instance) );
    }
    WHEN( "merged into a single list" ){
      auto trial = TestUnionGrid::merge( grids );
      THEN("the output will be sorted"){
	REQUIRE( std::is_sorted( trial.begin(), trial.end() ) );
      }
      THEN("the values will be unique"){
	REQUIRE( trial.end() == std::adjacent_find( trial.begin(), trial.end() ) );
      }
    }
  }
}
