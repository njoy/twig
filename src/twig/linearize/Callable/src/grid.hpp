/**
 * @details
 * In order to globally satisfy the user-specified error criterion,
 * the broken stick algorithm used here requires that any zeros
 * of the functor's first or second derivative are nodes in the 
 * x-range argument.
 **/
template< typename ForwardIterator,
          typename Functor,
          typename Convergence,
          typename Midpoint >
void grid( ForwardIterator& first,
           ForwardIterator last,
           Functor&& functor,
           Convergence&& criterion,
           Midpoint&& midpoint ){
  auto xLeft = *first; ++first;
  auto yLeft = functor( xLeft );

  decltype( xLeft ) xRight;
  decltype( yLeft ) yRight;
  while ( first != last ){
    xRight = *first; ++first;
    yRight = functor( xRight );
    this->bin( xLeft, xRight, yLeft, yRight,
               std::forward<Functor>(functor),
               std::forward<Convergence>(criterion),
               std::forward<Midpoint>(midpoint) );
    xLeft = xRight;
    yLeft = yRight;
  }
  this->xStack_->push_back( xRight );
  this->yStack_->push_back( yRight );
}
