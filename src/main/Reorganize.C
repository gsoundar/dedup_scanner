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
static bool meta_compare( filemeta_t m1, filemeta_t m2 );
static int processFile( string filename, map<string,vector<filemeta_t> > &data );

/* Main */
/* ------------------------------------------------ */
int main( int argc, char **argv ) {
  
  if( argc != 2 ) {
    cerr << "USAGE: " << argv[0] << " <dedup-output-file> " << endl;
    return -1;
  }
  
  string filename = argv[1];
  map<string,vector<filemeta_t> > data;
  int ret = 0;

  /* Read data in file */
  ret = processFile( filename, data );
  /* Sort the data */
  map<string,vector<filemeta_t> >::iterator it;
  for( it=data.begin(); it != data.end(); it++ ) {
    //cout << "KEY: " << (*it).first << " has " << (*it).second.size() << " elements" << endl;
    vector<filemeta_t> v = (*it).second;
    stable_sort( v.begin(), v.end(), meta_compare );
    vector<filemeta_t>::iterator jt;
    for( jt=v.begin(); jt != v.end(); jt++ ) {
      cout << (*jt).order_id << endl;
    }
  }
  return ret;
  
}

/* Implementation */
/* ------------------------------------------------ */

static bool meta_compare( filemeta_t m1, filemeta_t m2 ) {

  if( m1.size < m2.size ) { return true; }
  else if(m1.size==m2.size && m1.name_length < m2.name_length ) { return true; }
  else if(m1.size==m2.size && m1.name_length == m2.name_length && m1.ctime < m2.ctime ) { return true; }
  else if(m1.size==m2.size && m1.name_length == m2.name_length && m1.ctime == m2.ctime && m1.mtime < m2.mtime) { return true; }
  else if(m1.size==m2.size && m1.name_length == m2.name_length && m1.ctime == m2.ctime && m1.mtime == m2.mtime && m1.atime < m2.atime) { return true; }
  return false;

}


static int processFile( string filename, map<string,vector<filemeta_t> > &data ) {
  
  string line;
  ifstream fd( filename.c_str() );
  
  /* partition the data by keys */
  filemeta_t value;
  
  if( fd.is_open() ) {
    while( !fd.eof() ) {
      
      getline(fd, line);
      
      if( line.find("File: ", 0, 6) != string::npos ) {
	int ntokens = 0;
	vector<string> tokens;
	ntokens = Tokenizer::split( tokens, line.substr(6), "," );
	assert( ntokens >= 3 && "ERROR: Number of tokens did not match!" );
	value.order_id = atoi( tokens[tokens.size()-1].c_str() );
      }
      else if( line.find("Meta:", 0, 5) != string::npos ) {
	int ntokens = 0;
	vector<string> tokens;
	ntokens = Tokenizer::split( tokens, line.substr(5),"," );
	assert( ntokens == 7 && "ERROR: Number of tokens did not match!" );
	
	string key = tokens[0].substr(1) + "-" + tokens[1];
	
	value.size = atoll( tokens[2].c_str() );
	value.name_length = atoll( tokens[3].c_str() );
	value.atime = atoll( tokens[4].c_str() );
	value.mtime = atoll( tokens[5].c_str() );
	value.ctime = atoll( tokens[6].c_str() );
	
	data[key].push_back( value );
	
	//cout << "KEY: |" << key << "|" << " Num keys: " << data.size() << endl;
      }
      
    } 
  }
  
  return 0;

}
