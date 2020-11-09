#pragma once
#ifndef _3_2_3_2_COMMON_H
#define _3_2_3_2_COMMON_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int set_nonblock(int fd)
{
  int flags;
  #ifdef O_NONBLOCK
  if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
    flags = 0;
  return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  #else
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
  #endif
}

#endif //_3_2_3_2_COMMON_H
