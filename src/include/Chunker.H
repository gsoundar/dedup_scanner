/**
 * DEDUP - CHUNKER
 * ---------------
 * by Gokul Soundararajan
 *
 * The chunker interface.
 *
 **/

#ifndef __CHUNKER_H__
#define __CHUNKER_H__

#include <Dedup.H>
#include <math.h>
#include <rabinpoly.H>

using namespace std;

class Chunker {

public:
  static const unsigned int DEFAULT_SEG_SIZE = 4*1024*1024;

  virtual int getChunk( byte *chunkData, unsigned int chunkSize ) = 0;
  virtual ~Chunker() {};
};


class FixedWidthChunker : public Chunker {

private:
  fstream fd;
  bool isStreamClosed;

  byte *buffer;
  unsigned int bufferSize;
  unsigned int bufferConsumed, bufferLimit;

public:
  FixedWidthChunker( string filename );
  int getChunk( byte *chunkData, unsigned int chunkSize );
  ~FixedWidthChunker();
};

class RabinChunker : public Chunker {

private:
  fstream fd;
  bool isStreamClosed;

  unsigned int averageChunkSize;
  unsigned int minChunkSize, maxChunkSize;
  unsigned long long breakMark;

  byte *buffer;
  unsigned int bufferSize;
  unsigned int bufferConsumed, bufferLimit;

public:

  static const unsigned int DEFAULT_MIN_SIZE = 1024;
  static const unsigned int DEFAULT_RABIN_WINDOW_SIZE = 48;
  static const unsigned long long FINGERPRINT_PT = 0xbfe6b8a5bf378d83LL;

  RabinChunker( string filename, unsigned int averageChunkSize );
  int getChunk( byte *chunkData, unsigned int chunkSize );
  ~RabinChunker();

};

#endif
