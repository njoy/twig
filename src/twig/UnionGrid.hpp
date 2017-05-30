class UnionGrid {
protected:
  #include "twig/UnionGrid/src/unique.hpp"
  #include "twig/UnionGrid/src/merge.hpp"

public:
  template< typename Grids >
  auto operator()( Grids&& grids ) const {
    return merge( std::forward<Grids>(grids) );
  }
};

static constexpr UnionGrid unionGrid{};
