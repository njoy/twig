template< typename ForwardIterator, typename Buffer >
static ForwardIterator
unique( ForwardIterator begin,
	ForwardIterator end,
	Buffer& buffer ){

  using Value = typename ForwardIterator::value_type;
  const auto ninfinity = -std::numeric_limits< Value >::infinity();
    
  const auto cached = [&]( auto& left, auto& right){
    if (left == right){
      buffer.push_back( std::nextafter( right, ninfinity ) );
      return true;
    }
    return false;
  };

  buffer.clear();
  const auto pivot = std::unique( begin, end, cached );
  const auto sentinel = 
    std::copy( buffer.begin(),
	       std::unique( buffer.begin(), buffer.end() ), pivot );
 
  std::inplace_merge( begin, pivot, sentinel );
  return std::unique( begin, sentinel );
}
