template< typename Grids >
static auto merge( Grids&& grids ){
  using Value = typename std::decay_t<Grids>::value_type::value_type;
    
  std::sort( grids.begin(), grids.end(),
	     []( const auto& left, const auto& right ){
	       return left.size() < right.size(); } );

  std::vector< int > nodeCount( grids.size() + 1 );
  nodeCount.front() = 0;
    
  std::transform( grids.begin(), grids.end(),
		  std::next( nodeCount.begin() ),
		  []( auto& grid ){ return grid.size(); } );

  std::partial_sum( nodeCount.begin(), nodeCount.end(), nodeCount.begin() );

  std::vector<Value> grid( nodeCount.back() );
  std::vector<Value> buffer; buffer.reserve( grid.size() );
    
  auto divide_and_conquer =
    [&]( const auto& self, std::size_t left, std::size_t right, auto base ){
    switch ( right - left ){
    case 0: {
      return base;
    }
    case 1: {
      const auto end = std::copy( grids[left].begin(), grids[left].end(), base );
      return unique( base, end, buffer );
    }
    default: {
      const auto split = ( nodeCount[left] + nodeCount[right - 1] ) / 2;
      const auto offset = std::lower_bound( nodeCount.begin() + left,
					    nodeCount.begin() + right,
					    split ) - nodeCount.begin();
      const auto mid = self( self, left, offset, base );
      const auto end = self( self, offset, right, mid );
      buffer.clear();
      std::merge( base, mid, mid, end, std::back_inserter(buffer) );
      std::copy( buffer.begin(), buffer.end(), base );
      return end;
    }
    }
  };

  const auto end =
    divide_and_conquer( divide_and_conquer, 0, grids.size(), grid.begin() );
  
  grid.erase( std::unique( grid.begin(), end ), grid.end() );
  return grid;
}
