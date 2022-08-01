#include "common.h"


void do_write(int fd, char *buf, int size, int pos) {
    const int split = size / 3;
	if (pwrite(fd, buf, split, pos) != split)
		syserr("Write error");

if (pwrite(fd, buf + split, size - split, pos + split) != size -split)
		syserr("Write error");


}

