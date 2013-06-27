DEDUP SCANNER
=============

A simple filesystem scanner I wrote to identify duplicate blocks in my laptop.

Build
-----

1. Get and install the Crypto++ library within the "lib" directory
2. Edit src/config.mk and update path to CODE_BASE
   CODE_BASE=<PATH-TO-YOUR-CODE>/dedup_scanner/
3. Type make within the src/ directory

Run
---

src/main/GetHashes.exe
GetHashes.exe <filename> <chunker-type> <chunk-size>
<filename>: the name of the file you want to analyze
<chunker-type>: "fixed" or "rabin"
<chunk-size>: the block size you want to look at
