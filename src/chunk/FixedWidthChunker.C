/**
 * DEDUP - FIXED WIDTH CHUNKER
 * ---------------------------
 * by Gokul Soundararajan
 *
 * Gets fixed-width chunks.
 *
 **/

#include <Dedup.H>
#include <Chunker.H>

using namespace std;

FixedWidthChunker::FixedWidthChunker( string filename ) {

  fd.open( filename.c_str(), ios::in | ios::binary );
  isStreamClosed = false;

  bufferSize = DEFAULT_SEG_SIZE;
  buffer = new byte[bufferSize];
  bufferConsumed = 0;
  bufferLimit = 0;

}

FixedWidthChunker::~FixedWidthChunker() {
  if( buffer ) { delete[] buffer; buffer = NULL; }
}

int FixedWidthChunker::getChunk( byte *chunkData, unsigned int chunkSize ) {

  unsigned int c = 0;
  unsigned int rc = 0;

  while( true ) {
    
    /* Copy until it hurts */
    while( bufferLimit > 0 && bufferConsumed <= bufferLimit && c < chunkSize ) {
      chunkData[c++] = buffer[bufferConsumed++];
    }

    /* User buffer is full or I have no more data */
    if( c == chunkSize || isStreamClosed ) { 
      return c; 
    }

    /* Read some more */
    fd.read( (char *) buffer, bufferSize );
    bufferConsumed = 0; 
    bufferLimit = ( (rc = fd.gcount()) > 0 ? rc - 1 : 0 );
    if( fd.eof() ) { isStreamClosed = true; }
    
    //cout << "while: " << c << " " << bufferLimit << " " << bufferConsumed << " " << isStreamClosed << " " << chunkSize << endl;

  }

  return 0;

}
