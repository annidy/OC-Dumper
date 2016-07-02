#pragma once

void oc_dump(const uint8_t *buf, size_t len);
// return value need free
uint8_t *oc_read(const char *dp, size_t *outlen);
