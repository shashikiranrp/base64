#include <iostream>
#include <getopt.h>

#include <Base64.h>

typedef enum {ENCODE, DECODE} MODE; 
int main(int argc, char *argv[])
{
    int option_char;
    MODE mode = ENCODE;

    while ((option_char = getopt(argc, argv, "hvde")) != EOF) {
        switch (option_char) {
            case 'v':
                Base64::VERBOSE_FLAG = true;
                break;

            case 'd':
                mode = DECODE;            
                break;
                
            case 'e':
                mode = ENCODE;            
                break;

            case 'h':
            default:
                std::cerr << "usage: " << argv[0] << " [-h] [-v] [-e] [-d]" << std::endl;
                std::cerr << "\t-v " << "verbose (default: false)." << std::endl;
                std::cerr << "\t-e " << "encode to base64 (default)." << std::endl;
                std::cerr << "\t-d " << "decode from base64.." << std::endl;
                std::cerr << "\t-h " << "show this help and exit." << std::endl;
                exit(1);
        }
  }
  Base64::Base64 b64;
  return mode == ENCODE ? b64.encode(std::cin, std::cout) : b64.decode(std::cin, std::cout);
}

