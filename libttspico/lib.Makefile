##CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g 
LDFLAGS = -shared
TARGET_LIB = libsvoxpico.so 
TARGET_BIN = testtts
LIBS = -lsvoxpico -lpopt -lm

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

OBJS = $(SRCS:.c=.o)
 
.PHONY: all
all: ${TARGET_BIN}
 
$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(TARGET_BIN): $(TARGET_LIB)
	$(CC) -L./ bin/pico2wave.c $(LIBS) -I./ -o bin/$@ 
 
$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@
 
include $(SRCS:.c=.d)
 



