# DEDUP
# -----
# by Gokul Soundararajan

include config.mk

all: buildlib buildexe

buildlib:
	cd include; make
	cd rabin; make
	cd meta; make
	cd chunk; make
	cd hash; make

buildexe: buildlib
	cd main; make

clean:
	cd include; make clean
	cd rabin; make clean
	cd meta; make clean
	cd chunk; make clean
	cd hash; make clean
	cd main; make clean
	rm -rf *.o *.exe *.a *.so *.*~ *~
