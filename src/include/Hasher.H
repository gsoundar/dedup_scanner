/** 
 * DEDUP - Hasher 
 * --------------
 * by Gokul Soundararajan
 *
 * Hashing algorithm
 *
 **/

#ifndef __HASHER_H__
#define __HASHER_H__

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <md5.h>
#include <sha.h>

using namespace CryptoPP;

class Hasher {

public:
  virtual unsigned int digestSize() = 0;
  virtual int reset() = 0;
  virtual int update( byte *input, unsigned int input_length ) = 0;
  virtual int digest( byte *d, byte *input, unsigned int input_length ) = 0;
  virtual int digest( byte *d ) = 0;
  virtual ~Hasher() {};

  /* Common helpers */
  static int digestToString( const byte *digest, unsigned int digest_length,
			     char *str, unsigned int str_length );

};


class MD5Hasher : public Hasher {

private:
  Weak::MD5 md5;

public:
  static const unsigned int DIGEST_SIZE = 16;
  MD5Hasher();
  ~MD5Hasher();
  unsigned int digestSize() { return DIGEST_SIZE; }
  int reset();
  int update( byte *input, unsigned int input_length );
  int digest( byte *d, byte *input, unsigned int input_length );
  int digest( byte *d );
};

class SHA1Hasher : public Hasher {

private:
  SHA1 sha;

public:
  static const unsigned int DIGEST_SIZE = 20;
  SHA1Hasher();
  ~SHA1Hasher();
  unsigned int digestSize() { return DIGEST_SIZE; }
  int reset();
  int update( byte *input, unsigned int input_length );
  int digest( byte *d, byte *input, unsigned int input_length );
  int digest( byte *d );
};

#endif
