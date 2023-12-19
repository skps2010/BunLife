


// adds an object to the currrent export bundle
void addExportObject( int inObjectID );

// remove an already-added object from the current export bundle
void removeExportObject( int inObjectID );


char doesExportContain( int inObjectID );


// clears all previously-added objects from the current export bundle
// without saving it.
void clearExportBundle();



// returned vector is maintained internally
// NOT destroyed by caller
SimpleVector<int> *getCurrentExportList();


// gets the hash value for the current working bundle list
// destroyed by caller
char *getCurrentBundleHash();


// gets the hash value for a list of object IDs.
// inIDList must be pre-sorted
// inIDList destroyed by caller
//
// return value destroyed by caller
char *getObjectIDListHash( SimpleVector<int> *inIDList );




// finalizes and saves the bundle as an .oxp or .oxz file in the exports folder
// depending on settings/compressExports.ini
//
// clears objects from export bundle (next call to addExportObject will add
// an object to an empty bundle)
// 
// Returns true on success, false on failure
char finalizeExportBundle( const char *inExportName );
