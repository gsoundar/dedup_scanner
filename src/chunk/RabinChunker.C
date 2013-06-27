/**
 * DEDUP - RABIN CHUNKER
 * ---------------------------
 * by Gokul Soundararajan
 *
 * Gets variable-width chunks using 
 * Rabin fingerprints
 *
 **/

#include <Dedup.H>
#include <Chunker.H>

using namespace std;

RabinChunker::RabinChunker( string filename, unsigned int chunkSize ) {

  fd.open( filename.c_str(), ios::in | ios::binary );
  isStreamClosed = false;
  averageChunkSize = chunkSize;
  if( chunkSize / 2 > 0 )
    minChunkSize = ( DEFAULT_MIN_SIZE > chunkSize/2 ? DEFAULT_MIN_SIZE : chunkSize/2 );
  else
    minChunkSize = DEFAULT_MIN_SIZE;
  breakMark = pow(2,ceil(log2(averageChunkSize))-1)-1;

  bufferSize = DEFAULT_SEG_SIZE;
  buffer = new byte[bufferSize];
  bufferConsumed = 0;
  bufferLimit = 0;

}

RabinChunker::~RabinChunker() {
  if( buffer ) { delete[] buffer; buffer = NULL; }
}

int RabinChunker::getChunk( byte *chunkData, unsigned int chunkSize ) {

  unsigned int c = 0;
  unsigned long long rabinf = 0;
  window rabin(FINGERPRINT_PT, DEFAULT_RABIN_WINDOW_SIZE );

  while( true ) {
    
    /* Copy until it hurts */
    bool rabinMatched = false;
    while( bufferLimit > 0 && bufferConsumed <= bufferLimit && c < chunkSize ) {
      byte b = buffer[bufferConsumed++];
      chunkData[c++] = b; 
      rabinf = rabin.slide8( b );
      if( (rabinf & breakMark) == breakMark ) { 
	if( c > minChunkSize ) { rabinMatched = true; break; }
	else { rabin.reset(); }
      }
    }
    
    /* User buffer is full or I have no more data */
    if( rabinMatched || c == chunkSize || isStreamClosed ) { 
      return c; 
    }
    
    /* Read some more */
    fd.read( (char *) buffer, bufferSize );
    bufferConsumed = 0; 
    bufferLimit = ( fd.gcount() > 0 ? fd.gcount() - 1 : 0 );
    if( fd.eof() ) { isStreamClosed = true; }

  }

}
