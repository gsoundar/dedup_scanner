/**
 * DEDUP - SHA-1 Hasher
 * ------------------
 * by Gokul Soundararajan
 *
 * SHA-1 Hashing algorithm
 *
 **/

#include <Dedup.H>
#include <Hasher.H>

using namespace std;

SHA1Hasher::SHA1Hasher() {

  sha.Restart();

}

SHA1Hasher::~SHA1Hasher() { 

}

int SHA1Hasher::reset() {

  sha.Restart();
  return 0;

}

int SHA1Hasher::update( byte *input, unsigned int input_length ) {

  sha.Update( input, input_length );
  return 0;

}

int SHA1Hasher::digest( byte *d ) {
  
  sha.Final( d );
  return 0;
}

int SHA1Hasher::digest( byte *d, byte *input, unsigned int input_length ) {
  
  sha.Restart();
  sha.CalculateDigest( d, input, input_length );
  return 0;

}
