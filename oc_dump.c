#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void oc_dump(const uint8_t *buf, size_t len)
{
    int i;
    char *c;
  
    c = "0123456789abcdef";
    putchar('<');
    for(i = 0; i <len; i++) {
        if (i%4 == 0 && i != 0) {
            putchar(' ');
        }
        putchar(c[(buf[i]&0xf0)>>4]);
        putchar(c[buf[i]&0x0f]);
    }
    putchar('>');
}

int hex2int(char c) {
    if ((c >= '0' && c <= '9')) {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 0xa;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 0xa;
    }
    return -1;
}

// dp format '.*<fffffff ff ffff ffff>'
//           '.*{0xff,0xff,0xff}'
uint8_t *oc_read(const char *dp, size_t *outlen)
{
    int i, bit;
    uint8_t *rdp, *rdpp;
    int format = 0; 
    while (*dp && (format == 0)) {
        if (*dp == '{') format = 2;
        if (*dp == '<') format = 1;
        dp++;
    }
    i = 0;
    rdp = (uint8_t *)malloc(strlen(dp));
    rdpp = rdp;
    while(*dp) {
        if (format == 1) {
            if (*dp == '>') 
                break;
        } else if (format == 2) {
            if (*dp == '}') 
                break;
            if (memcmp(dp, "0x", 2) == 0 || memcmp(dp, "0X", 2) == 0) {
                dp += 2;
            }
        }

        bit = hex2int(*dp);
        if (bit >= 0) {
            if (i++ == 1) {
                *rdpp++ |= bit;
                i = 0;
            } else {
                *rdpp = bit << 4;
            }
        }
        dp++;
    }

    *outlen = rdpp - rdp;
    return rdp;
}