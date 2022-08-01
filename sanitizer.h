struct sanitizer_ctx {
    union {
        /* bpf_sanitizer_process */
        struct {
            loff_t offset;
            size_t size;
        };
        /* bpf_sanitizer_check */
        struct {
            u64 flags; /* open flags */
            umode_t mode; /* inode mode */
            kuid_t uid; /* owner */
            kgid_t gid; /* group */
        };
    };
};


