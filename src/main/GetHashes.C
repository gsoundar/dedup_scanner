/**
 * DEDUP - HASHER TEST
 * --------------------
 * by Gokul Soundararajan
 *
 * Tests the hashing code.
 *
 **/

#include <Dedup.H>
#include <Chunker.H>
#include <Hasher.H>

int main(int argc, char **argv ) {

  if( argc != 4 ) {
    cerr << "USAGE: " << argv[0] << " <filename> <chunker-type> <chunk-size>" << endl;
    cerr << "chunker-type: fixed or rabin" << endl;
    exit(-1);
  }

  string filename(argv[1]);
  string chunkerType = string(argv[2]);
  unsigned int chunkSize = atoi(argv[3]);
  unsigned int maxChunkSize = chunkSize * 5;
  unsigned int chunkInputSize = chunkSize;

  Chunker *c;
  if( chunkerType.compare("fixed") == 0 ) {
    c = new FixedWidthChunker( filename );
  } 
  else if( chunkerType.compare("rabin") == 0 ) {
    c = new RabinChunker( filename, chunkSize );
    chunkInputSize = maxChunkSize;
  }
  else {
    cerr << "ERROR: Not a valid hasher type!" << endl;
    exit(-1);
  }

  Hasher *h = new SHA1Hasher();
  byte *buffer = new byte[maxChunkSize]; int bufferSize = 0;
  byte *digest = new byte[h->digestSize()];
  unsigned int digestStringSize = 2 * h->digestSize() + 1;
  char *digestString = new char[digestStringSize];

  cout << "Filename: " << filename << endl;
  while( ( bufferSize = c->getChunk( buffer, chunkInputSize )) > 0 ) {
    h->update( buffer, bufferSize );
    h->digest( digest );

    Hasher::digestToString( digest, h->digestSize(), digestString, digestStringSize );
    cout << digestString << " " << bufferSize << endl;
  }
  

}
