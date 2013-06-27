/**
 * DEDUP - METADATA
 * ----------------
 * by Gokul Soundararajan
 *
 **/

#ifndef __METADATA_H__
#define __METADATA_H__

#include <Dedup.H>

#define _POSIX_C_SOURCE
#undef _DARWIN_FEATURE_64_BIT_INODE
#include <sys/stat.h>
#include <assert.h>


#define META_MAX_FILEEXT_LENGTH 8
#define META_NOEXT_STRING "None"

typedef struct filemeta_t {

  /* Distance metrics */
  uint64_t size;
  uint64_t atime, mtime, ctime;
  unsigned int name_length;
  unsigned int order_id;

  /* Partition keys */
  char ext[META_MAX_FILEEXT_LENGTH];
  byte mode; /* st_mode from stat() */

} filemeta_t;


class MetaData {

public:
  static int extractMetadata( const char *filename, filemeta_t *data );
};

#endif
