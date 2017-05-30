template< typename Xstack, typename Ydata >
class Callable {
  using Xdata = typename Xstack::value_type;

  Xstack* stack;
  std::vector< Xdata > xBuffer{};
  std::vector< Ydata > yBuffer{};

  #include "twig/linearize/Callable/src/bin.hpp"
  #include "twig/linearize/Callable/src/grid.hpp"

public:
  Callable( Xstack& xStack ) : stack( &xStack ){}
  void xStack( Xstack& stack ){ this->stack = &stack; }

  template< typename... Args >
  void operator()( Args&&... args ){
    this->grid( std::forward<Args>(args)... );  
  }
};

template< typename Ydata, typename Xstack >
auto callable( Xstack& stack ){
  return Callable< Xstack, Ydata >( stack );
}
