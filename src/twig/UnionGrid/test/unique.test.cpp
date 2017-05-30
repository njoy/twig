#include "catch.hpp"
#include "twig.hpp"

using namespace njoy::twig;

namespace {
class TestUnion : public UnionGrid {
public:
  using UnionGrid::unique;
};
}

SCENARIO("UnionGrid unique"){
  std::vector<double> input{ std::nextafter(1.0, -10.0),
                             std::nextafter(1.0, -10.0),
                             1.0, 1.0, 1.0,
                             std::nextafter(1.0, 10.0),
                             std::nextafter(1.0, 10.0),
                             1.5, 1.5, 2.0 };
  std::vector<double> buffer;
  std::vector<double> result( input.begin(),
			      TestUnion::unique( input.begin(),
						 input.end(),
						 buffer ) );

  std::vector<double> reference{ std::nextafter(std::nextafter(1.0, -10.0), -10.0),
                                 std::nextafter(1.0, -10.0),
                                 1.0,
                                 std::nextafter(1.0, 10.0),
                                 std::nextafter(1.5, -10.0),
                                 1.5, 2.0 };
  
  REQUIRE( reference == result );
}
