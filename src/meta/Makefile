# DEDUP
# -----
# by Gokul Soundararajan

include ../config.mk

all: build
clean:
	rm -rf *.o *.exe *.a *.so *.*~ *~

build: Metadata.o
	ar rcs libdedupmeta.a *.o

Metadata.o: Metadata.C
	${CCC} ${CFLAGS} ${INCLUDES} -c Metadata.C -o Metadata.o



