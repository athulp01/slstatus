#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *netstat(const char *interface) {
  char cmd[1024];
  sprintf(cmd, "/usr/bin/vnstat -i %s -d --oneline", interface);
  FILE *vnstat = popen(cmd, "r");
  char buff[1024];
  fgets(buff, sizeof(buff), vnstat);
  char *tok = strtok(buff, ";");
  int tokno = 5;
  while (tokno--)
    tok = strtok(NULL, ";");
  pclose(vnstat);
  return bprintf("%s", tok);
}
