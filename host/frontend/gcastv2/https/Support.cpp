#include <https/Support.h>

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <ctype.h>
#include <fcntl.h>
#include <sys/errno.h>

void makeFdNonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) { flags = 0; }
    DEBUG_ONLY(int res = )fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    assert(res >= 0);
}

void hexdump(const void *_data, size_t size) {
  const uint8_t *data = static_cast<const uint8_t *>(_data);

  size_t offset = 0;
  while (offset < size) {
    printf("%08zx: ", offset);

    for (size_t col = 0; col < 16; ++col) {
      if (offset + col < size) {
        printf("%02x ", data[offset + col]);
      } else {
        printf("   ");
      }

      if (col == 7) {
        printf(" ");
      }
    }

    printf(" ");

    for (size_t col = 0; col < 16; ++col) {
      if (offset + col < size && isprint(data[offset + col])) {
        printf("%c", data[offset + col]);
      } else if (offset + col < size) {
        printf(".");
      }
    }

    printf("\n");

    offset += 16;
  }
}

static char encode6Bit(unsigned x) {
  static char base64[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  return base64[x & 63];
}

void encodeBase64(const void *_data, size_t size, std::string *out) {
    out->clear();
    out->reserve(((size+2)/3)*4);

    const uint8_t *data = (const uint8_t *)_data;

    size_t i;
    for (i = 0; i < (size / 3) * 3; i += 3) {
        uint8_t x1 = data[i];
        uint8_t x2 = data[i + 1];
        uint8_t x3 = data[i + 2];

        out->append(1, encode6Bit(x1 >> 2));
        out->append(1, encode6Bit((x1 << 4 | x2 >> 4) & 0x3f));
        out->append(1, encode6Bit((x2 << 2 | x3 >> 6) & 0x3f));
        out->append(1, encode6Bit(x3 & 0x3f));
    }
    switch (size % 3) {
        case 0:
            break;
        case 2:
        {
            uint8_t x1 = data[i];
            uint8_t x2 = data[i + 1];
            out->append(1, encode6Bit(x1 >> 2));
            out->append(1, encode6Bit((x1 << 4 | x2 >> 4) & 0x3f));
            out->append(1, encode6Bit((x2 << 2) & 0x3f));
            out->append(1, '=');
            break;
        }
        default:
        {
            uint8_t x1 = data[i];
            out->append(1, encode6Bit(x1 >> 2));
            out->append(1, encode6Bit((x1 << 4) & 0x3f));
            out->append("==");
            break;
        }
    }
}
