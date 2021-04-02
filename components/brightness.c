#include <stdio.h>
#if defined(__linux__)
#include "../util.h"
#include <stdint.h>

const char *brightness(void) {
  uintmax_t max_brightness, cur_brightness;
  if (pscanf("/sys/class/backlight/intel_backlight/max_brightness", "%ju",
             &max_brightness) != 1) {
    return NULL;
  }

  if (pscanf("/sys/class/backlight/intel_backlight/brightness", "%ju",
             &cur_brightness) != 1) {
    return NULL;
  }
  int percentage = ((float)cur_brightness / max_brightness) * 100;
  return bprintf("%d", percentage);
}
#endif
