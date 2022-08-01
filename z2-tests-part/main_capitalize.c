#include "common.h"

char msg[] = "xyzzy xyzzy xyzzy\n";
int main(int argc, char **argv)
{
	int fd;
	int res = 0;
	struct bpf_test test;
    if (bpf_test_load("bpf_capitalize.o", &test) != 0)
        return -1;

	if ((fd = open("tst", O_RDWR | O_CREAT, 0644)) < 0) {
        fprintf(stderr, "Unable to open\n");
        res = -1;
        goto cleanup;
    }

	do_write(fd, msg, strlen(msg), 0);

	close(fd);


cleanup:
    bpf_test_cleanup(&test);
	return res;
}
