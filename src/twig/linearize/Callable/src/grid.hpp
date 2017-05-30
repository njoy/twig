/**
 * @details
 * In order to globally satisfy the user-specified error criterion,
 * the broken stick algorithm used here requires that any zeros
 * of the functor's first or second derivative are nodes in the 
 * x-range argument.
 **/
template< typename ForwardIterator,
	  typename Functor,
	  typename Convergence >
void grid( ForwardIterator& first,
	   ForwardIterator last,
	   Functor&& functor,
	   Convergence&& criterion ){
  auto xLeft = *first; ++first;
  auto yLeft = functor( xLeft );
  while ( first != last ){
    auto xRight = *first; ++first;
    auto yRight = functor( xRight );
    this->bin( xLeft, xRight, yLeft, yRight,
	       std::forward<Functor>(functor),
	       std::forward<Convergence>(criterion) );
    xLeft = xRight;
    yLeft = yRight;
  }
}
