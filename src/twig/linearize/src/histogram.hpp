template< typename FineGridIterator,   /* models ForwardIterator concept */
	  typename CoarseGridIterator, /* models ForwardIterator concept */
	  typename Sink                /* requires vector-link interface */ >
void histogram( FineGridIterator& first,
		FineGridIterator last,
		CoarseGridIterator histogram,
		Sink& sink ){
  using Value = std::decay_t< decltype( *first ) >;
  const auto ninfinity = -std::numeric_limits< Value >::infinity();

  while ( first != last ){
    while ( *first != *histogram ){
      sink.push_back( *first );
      ++first;
    }
    const auto nudge = std::nextafter( *first, ninfinity );
    if ( sink.back() != nudge ){ sink.push_back( nudge ); }
    ++histogram;
  }
}
