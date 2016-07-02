#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "oc_dump.h"

void hexdump(const uint8_t *buffer, size_t index, size_t width)
{
    size_t i, spacer;
    for (i = 0; i < index; i++)
    {
        printf("%02x ", buffer[i]);
    }
    for (spacer = index; spacer < width; spacer++)
        printf("   ");
    printf("| ");
    for (i = 0; i < index; i++)
    {
        if (buffer[i] < 32)
            printf(".");
        else printf("%c", buffer[i]);
    }
    printf("\n");
}

void pprint(const char *dp)
{
    uint8_t *buf, *bufp;
    int     line;
    size_t  len;
    size_t  index;
    size_t  width;

    width = 16;
    len = 0;

    buf = (uint8_t *)oc_read(dp, &len);
    for (line = 0, bufp = buf; line * width < len; line++, bufp += width) {
        if (len > (line + 1) * width) {
            hexdump(bufp, width, width);
        } else {
            hexdump(bufp, len - line * width, width);
        }
    }
    printf("Length: %ld\n", len);
    free(buf);
}

char line[1024*100];
int main(int argc, char const *argv[])
{
    size_t len;
    FILE *fp;
    
    if (argc > 1) {
        fp = fopen(argv[1], "rb");
        while((len = fread(line, 1, sizeof(line), fp)) > 0) {
            oc_dump(line, len);
        }
        fclose(fp);
    } else {
        while(fgets(line, sizeof(line), stdin)) {
            pprint(line);
        }
    }
    return 0;
}