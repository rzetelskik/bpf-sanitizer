TESTS=write pwrite writev pwritev pwritev2
HOST=$(addprefix capitalize_,$(TESTS)) \
     $(addprefix unload_,$(TESTS))

BPF=bpf_capitalize.o
TARGETS=$(HOST) $(BPF)

LIBBPF=libbpf/src/libbpf.a

# Override local libbpf
CFLAGS=-I libbpf/src -I libbpf/include -I libbpf/include/uapi -O2
LDFLAGS=-lelf -lz

all: $(TARGETS)


capitalize_%: do_%.c main_capitalize.c common.c $(LIBBPF)
	$(CC) -o $@ $< main_capitalize.c common.c $(LIBBPF) $(LDFLAGS) $(CFLAGS)

unload_%: do_%.c main_unload.c common.c $(LIBBPF)
	$(CC) -o $@ $< main_unload.c common.c $(LIBBPF) $(LDFLAGS) $(CFLAGS)


$(MISC): %: %.c common.c $(LIBBPF)
	cc -o $@ $< common.c $(LIBBPF) $(LDFLAGS) $(CFLAGS)

$(BPF): %.o: %.c
	clang-11 -target bpf $(CFLAGS) $< -c

$(LIBBPF):
	$(MAKE) -C libbpf/src

.PHONY: clean $(LIBBPF) $(LIBBPF32)
clean:
	$(MAKE) -C libbpf/src clean
	rm -f $(HOST) # leave ebpf
