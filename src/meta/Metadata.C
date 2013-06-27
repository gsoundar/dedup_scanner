/**
 * DEDUP - METADATA
 * ----------------
 * by Gokul Soundararajan
 *
 * Extract metadata from file
 *
 **/

#include <Dedup.H>
#include <Tokenizer.H>
#include <Metadata.H>

int MetaData::extractMetadata( const char *filename, filemeta_t *data ) {

  struct stat s;
  
  /* Check input */
  assert( filename && "ERROR: filename is NULL!" );
  assert( data && "ERROR: data is NULL!" );

  /* Get stats */
  if( lstat( filename, &s ) == 0 ) {

    data->size = s.st_size;
    data->mode = s.st_mode;
    data->atime = s.st_atime;
    data->mtime = s.st_mtime;
    data->ctime = s.st_ctime;

    /* Extract name length */
    {
      vector<string> tokens;
      Tokenizer::split( tokens, string(filename), "/" );
      if( tokens.size() > 1 ) { data->name_length = tokens[tokens.size()-1].size();} 
      else { data->name_length = 0; }
    }

    /* Extract extension */
    {
      vector<string> tokens;
      Tokenizer::split( tokens, string(filename), "." );
      if( tokens.size() > 1 ) { 
	memset( data->ext, 0, META_MAX_FILEEXT_LENGTH );
	strncpy( data->ext, tokens[tokens.size()-1].c_str(), META_MAX_FILEEXT_LENGTH-1); 
      }
      else { strncpy( data->ext, "None", META_MAX_FILEEXT_LENGTH-1); }
    }

    return 0;
    
  }
  return -1;
}
