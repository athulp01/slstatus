#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util.h"

const char* netstat(const char *interface) {
  FILE *vnstat = popen("/usr/bin/vnstat -i wlp3s0 -d --oneline", "r");
  char buff[1024];
  fgets(buff, sizeof(buff), vnstat);
  char *tok = strtok(buff, ";");
  int tokno = 5;
  while(tokno--) tok = strtok(NULL, ";");
  pclose(vnstat);
  return bprintf("%s", tok);
}
