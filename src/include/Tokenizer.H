/**
 * DEDUP - Tokenizer
 * -----------------
 * by Gokul Soundararajan
 *
 * This code is copied from:
 * http://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
 * solution by mrree
 *
 **/

#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <string>
#include <vector>
#include <assert.h>

using namespace std;

class Tokenizer {

public:
  static unsigned int split( vector<string> & theStringVector,  /* Altered/returned value */
			     const  string  & theString,
			     const  string  & theDelimiter )
  {
    assert( theDelimiter.size() > 0 && "ERROR: The delimiter is empty");    
    size_t  start = 0, end = 0;
    while ( end != string::npos ) {
      end = theString.find( theDelimiter, start );	
      // If at end, use length=maxLength.  Else use length=end-start.
      theStringVector.push_back( 
				theString.substr( start,(end == string::npos) ? string::npos : end - start ) 
				 );
	// If at end, use start=maxSize.  Else use start=end+delimiter.
      start = (   ( end > (string::npos - theDelimiter.size()) )
		  ?  string::npos  :  end + theDelimiter.size()    );
    }

    return theStringVector.size();

  }
  
};

#endif
