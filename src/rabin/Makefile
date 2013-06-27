# DEDUP
# -----
# by Gokul Soundararajan

include ../config.mk

all: build
clean:
	rm -rf *.o *.exe *.a *.so *.*~ *~

build: msb.o rabinpoly.o
	ar rcs libdeduprabin.a *.o

msb.o: msb.C
	${CCC} ${CFLAGS} ${INCLUDES} -c msb.C -o msb.o

rabinpoly.o: rabinpoly.C
	${CCC} ${CFLAGS} ${INCLUDES} -c rabinpoly.C -o rabinpoly.o



