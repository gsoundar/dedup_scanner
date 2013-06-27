/**
 * DEDUP - CHUNKER TEST
 * --------------------
 * by Gokul Soundararajan
 *
 * Tests the chunking code.
 *
 **/

#include <Dedup.H>
#include <Chunker.H>

int main(int argc, char **argv ) {

  if( argc != 4 ) {
    cerr << "USAGE: " << argv[0] << " <filename> <chunk-size> <chunker-type> " << endl;
    cerr << "chunker-type: fixed or rabin" << endl;
    exit(-1);
  }

  string filename(argv[1]);
  int chunkSize = atoi(argv[2]);
  string chunkerType = string(argv[3]);

  /* fixed width chunker */
  if( chunkerType.compare("fixed") == 0 ) {
    Chunker *c = new FixedWidthChunker( filename );
    byte *buffer = new byte[chunkSize];
    int bufferSize = 0;
    while( ( bufferSize = c->getChunk( buffer, chunkSize )) > 0 ) {
      cout << "Buffer size: " << bufferSize << endl;
    }
    delete buffer;
  } 
  /* rabin chunker */
  else if( chunkerType.compare("rabin") == 0 ) {
    Chunker *c = new RabinChunker( filename, chunkSize );
    unsigned int maxChunkSize = 5*chunkSize;
    byte *buffer = new byte[maxChunkSize]; 
    int bufferSize = 0;
    while( ( bufferSize = c->getChunk( buffer, maxChunkSize )) > 0 ) {
      cout << "Buffer size: " << bufferSize << endl;
    }
    delete buffer;
  } 
  /* not a valid chunker type */
  else {
    cerr << "ERROR: Not a valid chunker type!" << endl;
    exit(-1);
  }

}
