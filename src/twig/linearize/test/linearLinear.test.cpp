#define CATCH_CONFIG_MAIN

#include <vector>

#include "catch.hpp"
#include "twig.hpp"

using namespace njoy::twig;

SCENARIO("linearizing an existing linear-linear region"){
  std::vector< double > input{ 1.0, 2.0, 3.0 };
  std::vector< double > sink;

  auto first = input.begin();
  linearize::linearLinear( first, input.end() - 1, sink );
  CHECK( first == (input.end() - 1) );

  std::vector< double > reference{ 1.0, 2.0 };
  CHECK( sink == reference );
}
