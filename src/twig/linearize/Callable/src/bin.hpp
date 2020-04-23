template< typename Functor, typename Criterion, typename Midpoint >
void bin( Xdata xLeft, Xdata xRight,
          Ydata yLeft, Ydata yRight,
          Functor&& functor,
          Criterion&& criterion,
          Midpoint&& midpoint ){
  auto left = 0; auto right = 1;
  std::array< Xdata, 2 > x{{ xLeft, xRight }};
  std::array< Ydata, 2 > y{{ yLeft, yRight }};
  while (true) {
    const auto midpoint_ = midpoint( x, y );
    const auto trial = 0.5 * ( y[left] + y[right] );
    const auto reference = functor( midpoint_ );
    if ( criterion( trial, reference,
        x[left], x[right],
        y[left], y[right] ) ){

      this->xStack_->push_back( x[left] );
      this->yStack_->push_back( y[left] );
      if ( not this->xBuffer.size() ){ 
        // this->xStack_->push_back( x[right] );
        // this->yStack_->push_back( y[right] );
        break; 
      }

      std::swap( left, right );
      x[right] = this->xBuffer.back(); this->xBuffer.pop_back();
      y[right] = this->yBuffer.back(); this->yBuffer.pop_back();
    } else {
      this->xBuffer.push_back( x[right] );
      this->yBuffer.push_back( y[right] );
      x[right] = midpoint_;
      y[right] = reference;
    }
  }
}
