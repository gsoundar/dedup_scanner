# DEDUP
# -----
# by Gokul Soundararajan

include ../config.mk

all: build
clean:
	rm -rf *.o *.exe *.a *.so *.*~ *~

build: Hasher.o MD5Hasher.o SHA1Hasher.o
	ar rcs libdeduphasher.a *.o

Hasher.o: Hasher.C
	${CCC} ${CFLAGS} ${INCLUDES} -c Hasher.C -o Hasher.o

MD5Hasher.o: MD5Hasher.C
	${CCC} ${CFLAGS} ${INCLUDES} -c MD5Hasher.C -o MD5Hasher.o

SHA1Hasher.o: SHA1Hasher.C
	${CCC} ${CFLAGS} ${INCLUDES} -c SHA1Hasher.C -o SHA1Hasher.o


