APP = qemu-riscv64

OSDIR = ../../

export CFLAGS = -march=rv64gc -mabi=lp64 -mcmodel=medany		\
	-nostdinc -fno-builtin-printf -ffreestanding -Wall		\
	-Wredundant-decls -Wnested-externs -Wstrict-prototypes		\
	-Wmissing-prototypes -Wpointer-arith -Winline -Wcast-qual	\
	-Wundef -Wmissing-include-dirs -Werror

export AFLAGS = ${CFLAGS}

CMD = python3 -B ${OSDIR}/tools/emitter.py

# Multi-threaded, multi-processor
all:
	@${CMD} -j mdepx.conf

# Single-threaded, uni-processor
st:
	@${CMD} -j mdepx-st.conf

# Multi-threaded, uni-processor
up:
	@${CMD} -j mdepx-up.conf

clean:
	@rm -rf obj/*

include ${OSDIR}/mk/user.mk
