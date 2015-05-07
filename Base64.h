#ifndef BASE_64_H
#define BASE_64_H

#include <istream>
#include <ostream>

namespace Base64 {

  extern bool VERBOSE_FLAG;
  
  class Base64 {
    
    public:
      bool encode(std::istream&, std::ostream&);
      bool decode(std::istream&, std::ostream&);
  };

}



#endif
