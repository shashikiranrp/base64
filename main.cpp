#include <iostream>
#include <fstream>
#include <getopt.h>

#include <Base64.h>

typedef enum {ENCODE, DECODE} MODE; 
int main(int argc, char *argv[])
{
    int option_char;
    MODE mode = ENCODE;
    std::string inFileName("");
    std::string outFileName("");

    while ((option_char = getopt(argc, argv, "hvdei:o:")) != EOF) {
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

            case 'i':
                inFileName.assign(optarg);
                break;

            case 'o':
                outFileName.assign(optarg);
                break;

            case 'h':
            default:
                std::cerr << "usage: " << argv[0] << " [-h] [-v] [-e] [-d] [-i input_file] [-o output_file]" << std::endl;
                std::cerr << "\t-v " << "verbose (default: false)." << std::endl;
                std::cerr << "\t-e " << "encode to base64 (default action)." << std::endl;
                std::cerr << "\t-d " << "decode from base64." << std::endl;
                std::cerr << "\t-i " << "read input from file (default: stdin)." << std::endl;
                std::cerr << "\t-o " << "write output to file. (default: stdout)" << std::endl;
                std::cerr << "\t-h " << "show this help and exit." << std::endl;
                exit(1);
        }
  }
  Base64::Base64 b64;
  std::unique_ptr<std::ifstream> is(!inFileName.empty() ? new std::ifstream(inFileName.c_str(), std::ifstream::in) : nullptr);
  std::unique_ptr<std::ofstream> os(!outFileName.empty() ? new std::ofstream(outFileName.c_str(), std::ofstream::out) : nullptr);
  return mode == ENCODE ? b64.encode(nullptr == is ? std::cin : *is, nullptr == os ? std::cout : *os) 
                        : b64.decode(nullptr == is ? std::cin : *is, nullptr == os ? std::cout : *os);
}

