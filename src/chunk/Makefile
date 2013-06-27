# DEDUP
# -----
# by Gokul Soundararajan

include ../config.mk

all: build
clean:
	rm -rf *.o *.exe *.a *.so *.*~ *~

build: FixedWidthChunker.o RabinChunker.o
	ar rcs libdedupchunker.a *.o

FixedWidthChunker.o: FixedWidthChunker.C
	${CCC} ${CFLAGS} ${INCLUDES} -c FixedWidthChunker.C -o FixedWidthChunker.o
RabinChunker.o: RabinChunker.C
	${CCC} ${CFLAGS} ${INCLUDES} -c RabinChunker.C -o RabinChunker.o


