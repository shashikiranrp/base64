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

  unsigned int xtract_group(Base64Group group_id) 
  {
    unsigned int result = 0x0;
    switch (group_id) {
      case FST:
        result = (byte0 & 0xFCu) >> 2u;
        break;

      case SND:
        result = ((byte0 & 0x03u) << 4u) | ((byte1 & 0xF0u) >> 4u);
        break;

      case THD:
        result = ((byte1 & 0x0Fu) << 2u) | ((byte2 & 0xC0u) >> 6u);
        break;

      case FTH:
        result = byte2 & 0x3Fu;
        break;
    }
    return result;
  }

};

static byte get_next_encodable_char(std::istream& is, bool& is_bad)
{
  static int count{0};
  byte next_byte{0};
  next_byte = static_cast<byte>(is.get());

  if (is.eof()) {
    is_bad = true;
    next_byte = 0;
  } else {
    ++count;
    is_bad = false;
  }

  return next_byte;
}

bool Base64::Base64::encode(std::istream& is, std::ostream& os) 
{
  bool status{true}, stream_bad{false}, stop_now{false};
  do {
    Bits24 block;
    int bytes_read{0};
    byte next_byte = get_next_encodable_char(is, stream_bad); 
    if (stream_bad) {
      stop_now = true;
    } else {
      block.byte0 = next_byte;
      bytes_read++;
      next_byte = get_next_encodable_char(is, stream_bad);
      if (stream_bad) {
        block.byte1 = block.byte2 = 0;
        stop_now = true;
      } else {
        block.byte1 = next_byte;
        bytes_read++;
        next_byte = get_next_encodable_char(is, stream_bad);
        if (stream_bad) {
          block.byte2 = 0;
          stop_now = true;
        } else {
          block.byte2 = next_byte;
          bytes_read++;
        }
      }
    }
    
    if (bytes_read > 0) {
      os.put(CharMapA[block.xtract_group(FST)]);
      os.put(CharMapA[block.xtract_group(SND)]);
      --bytes_read;
      if (bytes_read > 0) {
        os.put(CharMapA[block.xtract_group(THD)]);
      } else {
        os.put('=');
        os.put('=');
        break;
      }
      --bytes_read;
      if (bytes_read > 0) {
        os.put(CharMapA[block.xtract_group(FTH)]);
      } else {
        os.put('=');
        break;
      }
    }
  } while(!stop_now);

  return status;
}

