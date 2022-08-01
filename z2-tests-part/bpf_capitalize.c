#include "vmlinux.h"
#include <bpf_helpers.h>

SEC("sanitizer/check")
int check(struct sanitizer_ctx *ctx)
{
    return 1;
}


SEC("sanitizer/sanitize")
int sanitize(struct sanitizer_ctx *ctx)
{
    const char repl[] = "XYZZY";
    const char pattern[] = "xyzzy";
    char buf[16];

    if (bpf_copy_from_buffer(ctx, 0, buf, sizeof(pattern) - 1))
        return 0;

    for (int i = 0; i < sizeof(pattern) - 1; i++)
        if (buf[i] != pattern[i])
            return 0;

    bpf_copy_to_buffer(ctx, 0, repl, sizeof(repl) - 1);

    return 0;
}

char _license[] SEC("license") = "GPL";
