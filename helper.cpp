#include <err.h>
#include <stdio.h>
#include <string.h>

#include <hidapi/hidapi.h>

int main() {
  if (hid_init() != 0) {
    errx(1, "hid_init failed");
  }

  hid_device* handle = hid_open(0x2fe3, 0x0006, nullptr);
  if (!handle) {
    errx(1, "failed to open device");
  }

  unsigned char buf[65] = {};
  buf[0] = 0xf0;
  strncpy((char*)buf + 1, "the quick brown fox jumped over the lazy dog", 64);
  buf[64] = 0xff;


  int rc = hid_send_feature_report(handle, buf, 65);
  if (rc < 0) {
    errx(1, "write failed");
  }
  printf("write returned %d\n", rc);

  memset(buf, 0, 65);

  buf[0] = 0xf1;
  rc = hid_get_feature_report(handle, buf, 65);
  if (rc < 0) {
    errx(1, "read failed");
  }

  printf("read returned %d (%s)\n", rc, buf + 1);
  if (buf[64] != 0xff) {
    errx(1, "failed to read last byte (value = %#02x)", buf[64]);
  }
}
