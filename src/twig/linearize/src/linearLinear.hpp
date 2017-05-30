template< typename InputIterator,
	  typename Sink >
void linearLinear( InputIterator& first,
		   InputIterator last,
		   Sink& sink ){
  std::copy( first, last, std::back_inserter(sink) );
  first = last;
}
