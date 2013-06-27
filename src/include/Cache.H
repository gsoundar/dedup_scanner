/**
 * DEDUP - CACHE
 * -------------
 * by Gokul Soundararajan
 *
 *
 *
 **/

#ifndef __CACHE_H__
#define __CACHE_H__

#include <Dedup.H>
#include <vector>
#include <map>

using namespace std;

typedef struct entry_t {
  string key;
  bool refBit;
} CacheEntry;

class Cache {

private:
  unsigned int cacheSize;
  unsigned int clockHand;
  vector<CacheEntry> entries;
  map<string,CacheEntry> db;

  CacheEntry& placeInEmptySlot( string key );

public:

  Cache( unsigned int cacheSize );
  
  bool Access( string key );


};

#endif
