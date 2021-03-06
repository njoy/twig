template< typename Xstack, typename Ystack >
class Callable {
  using Xdata = typename Xstack::value_type;
  using Ydata = typename Ystack::value_type;

  Xstack* xStack_;
  Ystack* yStack_;
  std::vector< Xdata > xBuffer{};
  std::vector< Ydata > yBuffer{};

  #include "twig/linearize/Callable/src/bin.hpp"
  #include "twig/linearize/Callable/src/grid.hpp"

public:
Callable( Xstack& xStack, Ystack& yStack ) : 
  xStack_( &xStack ),
  yStack_( &yStack )
{}

  template< typename... Args >
  void operator()( Args&&... args ){
    this->grid( std::forward<Args>(args)... );  
  }
};

template< typename Ystack, typename Xstack >
auto callable( Xstack& xStack, Ystack& yStack ){
  return Callable( xStack, yStack );
}
