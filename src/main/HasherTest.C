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
    cerr << "USAGE: " << argv[0] << " <filename> <chunker-type> <hasher-type> " << endl;
    cerr << "chunker-type: fixed or rabin" << endl;
    cerr << "hasher-type: md5 or sha1" << endl;
    exit(-1);
  }

  string filename(argv[1]);
  string chunkerType = string(argv[2]);
  string hasherType = string(argv[3]);

  unsigned chunkSize = 16384;
  unsigned maxChunkSize = 5 * chunkSize;
  unsigned chunkInputSize = chunkSize;

  Chunker *c = NULL;
  if( chunkerType.compare("rabin") == 0 ) { c = new RabinChunker(filename, chunkSize); chunkInputSize = maxChunkSize; }
  else if( chunkerType.compare("fixed") == 0) { c = new FixedWidthChunker(filename); }
  else{ cerr << "ERROR: Invalid chunker type!!" << endl; return -1; }

  Hasher *h = NULL;
  if(hasherType.compare("md5") == 0) { h = new MD5Hasher(); }
  else if(hasherType.compare("sha1") == 0) { h = new SHA1Hasher(); }
  else{ cerr << "ERROR: Invalid hasher type!!" << endl; return -1; }

  byte *buffer = new byte[maxChunkSize]; int bufferSize;
  byte *digest = new byte[h->digestSize()];
  unsigned int digestStringSize = 2 * h->digestSize() + 1;
  char *digestString = new char[digestStringSize];

  while( ( bufferSize = c->getChunk( buffer, chunkInputSize )) > 0 ) {
    h->update( buffer, bufferSize );
  }
  h->digest( digest );

  Hasher::digestToString( digest, h->digestSize(), digestString, digestStringSize );
  cout << "MD5 (" << filename << ") = " <<  digestString << endl;

}
