# DEDUP
# -----
# by Gokul Soundararajan

include ../config.mk

all: clean build
build: ChunkerTest.exe HasherTest.exe GetHashes.exe Dedup.exe Reorganize.exe PrintNewOrder.exe
clean:
	rm -rf *.o *.exe *.a *.so *.*~ *~

ChunkerTest.o: ChunkerTest.C
	${CCC} ${CFLAGS} ${INCLUDES} -c ChunkerTest.C -o ChunkerTest.o
ChunkerTest.exe: ChunkerTest.o
	${CCC} ${CFLAGS} ${INCLUDES} ChunkerTest.o -o ChunkerTest.exe ${LIBDIRS} ${LIBS}

HasherTest.o: HasherTest.C
	${CCC} ${CFLAGS} ${INCLUDES} -c HasherTest.C -o HasherTest.o
HasherTest.exe: HasherTest.o
	${CCC} ${CFLAGS} ${INCLUDES} HasherTest.o -o HasherTest.exe ${LIBDIRS} ${LIBS}

GetHashes.o: GetHashes.C
	${CCC} ${CFLAGS} ${INCLUDES} -c GetHashes.C -o GetHashes.o
GetHashes.exe: GetHashes.o
	${CCC} ${CFLAGS} ${INCLUDES} GetHashes.o -o GetHashes.exe ${LIBDIRS} ${LIBS}

Dedup.o: Dedup.C
	${CCC} ${CFLAGS} ${INCLUDES} -c Dedup.C -o Dedup.o
Dedup.exe: Dedup.o
	${CCC} ${CFLAGS} ${INCLUDES} Dedup.o -o Dedup.exe ${LIBDIRS} ${LIBS}

Reorganize.o: Reorganize.C
	${CCC} ${CFLAGS} ${INCLUDES} -c Reorganize.C -o Reorganize.o
Reorganize.exe: Reorganize.o
	${CCC} ${CFLAGS} ${INCLUDES} Reorganize.o -o Reorganize.exe ${LIBDIRS} ${LIBS}

PrintNewOrder.o: PrintNewOrder.C
	${CCC} ${CFLAGS} ${INCLUDES} -c PrintNewOrder.C -o PrintNewOrder.o
PrintNewOrder.exe: PrintNewOrder.o
	${CCC} ${CFLAGS} ${INCLUDES} PrintNewOrder.o -o PrintNewOrder.exe ${LIBDIRS} ${LIBS}

