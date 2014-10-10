#include <iostream>
#include <Base64.h>

int main()
{
  Base64::Base64 b64;
  b64.encode(std::cin, std::cout);
  std::cout << std::endl;
  return 0;
}
