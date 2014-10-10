#include <Base64.h>
#include <Base64CharMap.h>
#include <istream>
#include <ostream>
#include <iostream>

typedef unsigned char byte;
typedef enum {FST, SND, THD, FTH} Base64Group;

class Bits24 {
  
  public:
  byte byte0{0}, byte1{0}, byte2{0};

  int xtract_group(Base64Group group_id) 
  {
    unsigned int result = 0x0;
    switch (group_id) {
      case FST:
        result = (byte0 & 0xFC) >> 2;
        break;

      case SND:
        result = ((byte0 & 0x03) << 4) | ((byte1 & 0xF0) >> 4);
        break;

      case THD:
        result = ((byte1 & 0x0F) << 2) | ((byte2 & 0xC0) >> 6);
        break;

      case FTH:
        result = byte2 & 0x3F;
        break;

      default:
        throw std::runtime_error(std::string("Bits24::xtract_group: invalid group: ") + std::to_string(group_id));
    }
    return result;
  }

};

byte get_next_encodable_char(std::istream& is, std::ostream& os, bool& is_bad)
{
  byte next_byte{0};
  do {
    next_byte = is.get();
    is_bad = !is.good();
    if ('\r' == next_byte || '\n' == next_byte) {
      continue;
    } else {
      break;
    }
  } while(!is_bad);
  return is_bad ? 0 : next_byte;
}

bool Base64::Base64::encode(std::istream& is, std::ostream& os) 
{
  bool status{true}, stream_bad{false}, stop_now{false};
  do {
    Bits24 block;
    int padding = 0;
    byte next_byte = get_next_encodable_char(is, os, stream_bad); 
    block.byte0 = next_byte;
    if (stream_bad) {
      padding  = 2;
      block.byte1 = block.byte2 = 0;
      stop_now = true;
    } else {
      next_byte = get_next_encodable_char(is, os, stream_bad);
      block.byte1 = next_byte;
      if (stream_bad) {
        padding  = 1;
        block.byte2 = 0;
        stop_now = true;
      } else {
        next_byte = get_next_encodable_char(is, os, stream_bad);
        block.byte2 = next_byte;
        if (stream_bad) {
          stop_now = true;
        }
      }
    }
    os.put(CharMap.at(block.xtract_group(FST)));
    os.put(CharMap.at(block.xtract_group(SND)));
    os.put(CharMap.at(block.xtract_group(THD)));
    os.put(CharMap.at(block.xtract_group(FTH)));
    while (padding-- > 0) {
      os.put('=');
    }
  } while(!stop_now);

  return status;
}

bool Base64::Base64::decode(std::istream& is, std::ostream& os) 
{
  bool status = true;
  return status;
}
