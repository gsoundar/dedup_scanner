/**
 * DEDUP - Hasher
 * ------------------
 * by Gokul Soundararajan
 *
 * Hashing algorithm
 *
 **/

#include <Dedup.H>
#include <Hasher.H>

using namespace std;

int Hasher::digestToString( const byte *digest, unsigned int digest_length, 
			    char *str, unsigned int string_length ) {

  int c = 0;

  memset( str, 0, string_length );

  for (unsigned int i = 0; i < digest_length; i++) {
    int halfbyte = ( (unsigned char) digest[i] >> 4) & 0x0F;
    int two_halfs = 0;
    do {
      if ((0 <= halfbyte) && (halfbyte <= 9))
	str[c++] = ((char) ('0' + halfbyte));
      else
	str[c++] = ((char) ('a' + (halfbyte - 10)));
      halfbyte = digest[i] & 0x0F;
    } while (two_halfs++ < 1);
  }

  return c;
  
}
