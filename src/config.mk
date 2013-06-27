# Build Configuration
CC=gcc
CCC=g++
CFLAGS=-g -Wall -O4
CODE_BASE=/Users/gokuls/Dropbox/Code/dedup_scanner/
DEDUP_INCLUDES=-I${CODE_BASE}/src/include
DEDUP_LIBDIRS=-L${CODE_BASE}/src/chunk -L${CODE_BASE}/src/hash -L${CODE_BASE}/src/rabin -L${CODE_BASE}/src/meta
DEDUP_LIBS=-ldedupchunker -ldeduphasher -ldeduprabin -ldedupmeta

# Crypto
CRYPTO_BASE=${CODE_BASE}/lib/cryptopp
CRYPTO_INCLUDES=-I${CRYPTO_BASE}/
CRYPTO_LIBDIRS=-L${CRYPTO_BASE}/
CRYPTO_LIBS=-lcryptopp

INCLUDES=${DEDUP_INCLUDES} ${CRYPTO_INCLUDES}
LIBDIRS=${DEDUP_LIBDIRS} ${CRYPTO_LIBDIRS}
LIBS=${DEDUP_LIBS} ${CRYPTO_LIBS}

