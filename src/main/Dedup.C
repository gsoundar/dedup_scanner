/**
 * DEDUP - MAIN
 * ------------
 * by Gokul Soundararajan
 *
 * Main file to extract file metadata and hashes
 *
 **/

#include <Dedup.H>
#include <Chunker.H>
#include <Hasher.H>
#include <Metadata.H>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static int processFile( unsigned int id, string filename, string prefix, string chunkerType, unsigned int chunkSize, bool anonimize );


int main( int argc, char **argv ) {

  if( argc != 6 ) {
    cout << "USAGE: " << argv[0] << " <list-of-files> <prefix> <chunker-type> <chunk-size> <anonimize>" << endl;
    cout << "<chunker-type>: fixed or rabin" << endl;
    cout << "<anonimize>: true or false" << endl;
    exit(-1);
  }

  string listOfFiles = argv[1];
  string prefix = argv[2];
  string chunkerType = argv[3];
  unsigned int chunkSize = atoi(argv[4]);
  bool anonimize = ( string(argv[5]).compare("true") == 0 ? true : false );
  int ret = 0;
  unsigned int id = 0;

  /* Process each file */
  string line;
  ifstream fd( listOfFiles.c_str() );
  if( fd.is_open() ) {

    while( !fd.eof() ) {
      
      getline( fd, line );
      if( line.size() > 1 ) {
	ret = processFile( id, line, prefix, chunkerType, chunkSize, anonimize );
	if( ret != 0 ) { 
	  cerr << "ERROR: Something bad happened!" << endl;
	  cerr << "ERROR: Skipping file " << line << endl;
	}
	id++;
      }

    }

  }

  return 0;

}


static int processFile( unsigned int id, string filename, string prefix, string chunkerType, unsigned int chunkSize, bool anonimize ) {

  Chunker *c = NULL;
  SHA1Hasher h;

  unsigned int maxChunkSize = 5 * chunkSize;
  unsigned int chunkInputSize = chunkSize;

  int bufferSize = 0;
  byte *buffer = new byte[maxChunkSize];

  int digestSize = h.digestSize();
  byte *digest = new byte[digestSize];
  
  int digestStringSize = 2 * h.digestSize() + 1;
  char *digestString = new char[digestStringSize];

  filemeta_t meta;
  int ret = 0, erred = 0;

  /* Extract metadata */
  ret = MetaData::extractMetadata( filename.c_str(), &meta );
  if( ret ) {
    cerr << "ERROR: Could not extract metadata!" << endl;
    erred = 1; goto leave;
  } else {
    if(!anonimize)
      cout << "File: " << filename << "," << prefix << "," << id << endl;
    else
      cout << "File: " << "Hidden" << "," << prefix << "," << id << endl;
    cout << "Meta: " << meta.ext << "," << (unsigned) meta.mode << "," << meta.size << "," << meta.name_length << ",";
    cout << meta.atime << "," << meta.mtime << "," << meta.ctime << endl;
  }

  /* Create appropriate chunker */
  if( chunkerType.compare("fixed") == 0 ) {
    c = new FixedWidthChunker( filename );
    cout << "F-" << chunkSize << ":" ;
  } else if( chunkerType.compare("rabin") == 0 ) {
    c = new RabinChunker( filename, chunkSize );
    chunkInputSize = maxChunkSize;
    cout << "R-" << chunkSize << ": ";
  } else {
    cerr << "ERROR: Not a valid chunker type!" << endl;
    erred = 1; goto leave;
  }

  /* Get hashes */
  while( ( bufferSize = c->getChunk( buffer, chunkInputSize )) > 0 ) {
    h.update( buffer, bufferSize );
    h.digest( digest );
    Hasher::digestToString( digest, h.digestSize(), digestString, digestStringSize );
    cout << digestString << "-" << bufferSize << " ";
  }
  cout << endl << "END" << endl;

  /* Cleanup */
 leave:
  if( buffer ) { delete[] buffer; buffer = NULL; }
  if( digestString ) { delete[] digestString; digestString = NULL; }
  if( digest ) { delete[] digest; digest = NULL; }
  if( c ) { delete c; c = NULL; }

  return ( erred ? -1 : 0 );

}
