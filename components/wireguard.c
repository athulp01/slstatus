#include <string.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include "../util.h"
    

const char* wireguard(){
  struct ifaddrs *ifaddr, *ifa;

  if (getifaddrs(&ifaddr) == -1) {
    return bprintf("%s", "Error");
  }

  /* Walk through linked list, maintaining head pointer so we
     can free list later */
  int wireguard = 0;
  for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    if(!strcmp("wg0", ifa->ifa_name)) {
      wireguard = 1;
      break;
    }
  }

  freeifaddrs(ifaddr);
  if(wireguard) {
    return bprintf("%s", "Active");
  }
    return NULL;
}
