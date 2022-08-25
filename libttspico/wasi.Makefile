##CC = gcc
CFLAGS = -O2 -s
TARGET_BIN = example.wasm
LIBS = -lm

SRCS := picoacph.c \
	picoapi.c \
	picobase.c \
	picocep.c \
	picoctrl.c \
	picodata.c \
	picodbg.c \
	picoextapi.c \
	picofftsg.c \
	picokdbg.c \
	picokdt.c \
	picokfst.c \
	picoklex.c \
	picoknow.c \
	picokpdf.c \
	picokpr.c \
	picoktab.c \
	picoos.c \
	picopal.c \
	picopam.c \
	picopr.c \
	picorsrc.c \
	picosa.c \
	picosig.c \
	picosig2.c \
	picospho.c \
	picotok.c \
	picotrns.c \
	picowa.c

 
.PHONY: all
all: ${TARGET_BIN}
 
$(TARGET_BIN): 
	$(CC) --target=wasm32-unknown-wasi --sysroot /opt/wasi-sysroot \
	 $(CFLAGS) bin/example.c $(SRCS) $(LIBS) -I./ -o bin/$@ 
 
 

