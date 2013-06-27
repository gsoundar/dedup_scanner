/**
 * DEDUP - REORGANIZE
 * ------------------
 * by Gokul Soundararaajan
 *
 * The smarts (hopefully) of the whole thing!
 *
 **/

#include <Dedup.H>
#include <Metadata.H>
#include <Tokenizer.H>

#include <map>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

/* Headers */
/* ------------------------------------------------ */
static int loadHashes( string filename, string hashString, map<unsigned int,vector<string> > &hashes );

/* Main */
/* ------------------------------------------------ */
int main( int argc, char **argv ) {
  
  if( argc != 4 ) {
    cerr << "USAGE: " << argv[0] << " <hash-string> <dedup-output-file> <reorg-output-file>" << endl;
    cerr << "<reorg-output-file>: actual file or None" << endl;
    return -1;
  }
  
  string hashString = argv[1];
  string dedupOutputFile = argv[2];
  string reorgOutputFile = argv[3];
  map<unsigned int,vector<string> > data;
  int ret = 0;

  /* Load hashes */
  ret = loadHashes( dedupOutputFile, hashString, data ); 

  /* Print in old order */
  if( reorgOutputFile.compare("None") == 0 ) {
    map<unsigned int, vector<string> >::iterator it;
    for( it=data.begin(); it != data.end(); it++ ) {
      vector<string> v = (*it).second;
      vector<string>::iterator jt;
      for( jt=v.begin(); jt!=v.end(); jt++ ) {
	cout << (*jt) << endl;
      }
    }
  } else {
    ifstream fd( reorgOutputFile.c_str() );
    string line;
    if( fd.is_open() ) {
      while( !fd.eof() ) {
	getline(fd,line);
	unsigned int order_id = atoi( line.c_str() );
	if( data.find(order_id) != data.end() ) {
	  vector<string> v = data[order_id];
	  vector<string>::iterator jt;
	  for( jt=v.begin(); jt!=v.end(); jt++ ) {
	    cout << (*jt) << endl;
	  }
	}
      }
    }
  }

  return ret;
  
}

/* Implementation */
/* ------------------------------------------------ */

static int loadHashes( string filename, string hashString, map<unsigned int,vector<string> > &hashdb ) {

  string line;
  ifstream fd( filename.c_str() );

  unsigned int order_id = 0;
  vector<string> hashes;

  if(fd.is_open()) {
    while( !fd.eof() ) {

      /* Read line from file */
      getline(fd,line);

      //cout << line << endl;

      /* Process line */
      if( line.find("File: ", 0, 6) != string::npos ) {
	int ntokens = 0;
	vector<string> tokens;
	ntokens = Tokenizer::split( tokens, line.substr(6), "," );
	assert( ntokens >= 2 && "ERROR: Number of tokens did not match!" );
	order_id = atoi( tokens[tokens.size()-1].c_str() );
      }
      else if( line.find(hashString) != string::npos ) {
	int ntokens = 0;
	vector<string> tokens;
	ntokens = Tokenizer::split( tokens, line.substr(hashString.size()), " " );
	if( ntokens > 0 ) {
	  vector<string>::iterator i;
	  for( i=tokens.begin(); i != tokens.end(); i++ ) {
	    int nt = 0;
	    vector<string> t2;
	    nt = Tokenizer::split( t2, (*i), "-" );
	    //cout << "NT: " << nt << " TOK: " << (*i) << endl;
	    if( nt == 2 ) { hashes.push_back( t2[0] ); }
	  }
	}
      }
      else if( line.find("END", 0, 3 ) != string::npos ) {
	hashdb[order_id] = hashes;
	order_id = 0;
	hashes.clear();
	//cout << "DB size: " << hashdb.size() << endl;
      }
    }
  }

  return 0;

}
