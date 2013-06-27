/**
 * DEDUP - MD5 Hasher
 * ------------------
 * by Gokul Soundararajan
 *
 * MD5 Hashing algorithm
 *
 **/

#include <Dedup.H>
#include <Hasher.H>

using namespace std;

MD5Hasher::MD5Hasher() {

  md5.Restart();

}

MD5Hasher::~MD5Hasher() {

}

int MD5Hasher::reset() {

  md5.Restart();
  return 0;

}

int MD5Hasher::update( byte *input, unsigned int input_length ) {

  md5.Update( input, input_length );
  return 0;

}

int MD5Hasher::digest( byte *d ) {
  
  md5.Final( d );
  return 0;
}

int MD5Hasher::digest( byte *d, byte *input, unsigned int input_length ) {
  
  md5.Restart();
  md5.CalculateDigest( d, input, input_length );
  return 0;

}
