#ifndef SPRITE_PICKABLE_INCLUDED
#define SPRITE_PICKABLE_INCLUDED


#include "Pickable.h"


#include "spriteBank.h"
#include "objectBank.h"


#include "EditorObjectPage.h"

extern EditorObjectPage *objectPage;


class SpritePickable : public Pickable {
        
    public:
        virtual void **search( const char *inSearch, 
                               int inNumToSkip, 
                               int inNumToGet, 
                               int *outNumResults, int *outNumRemaining ) {

            if( strcmp( inSearch, "." ) == 0 ) {
                int *stackResults = 
                    getStackRange( inNumToSkip, inNumToGet,
                                   outNumResults, outNumRemaining );
                void **results = new void *[ *outNumResults ];
                
                for( int i=0; i< *outNumResults; i++ ) {
                    results[i] = (void*)getSpriteRecord( stackResults[i] );
                    }

                delete [] stackResults;
                return results;
                }
            else {
                return (void**)searchSprites( inSearch, inNumToSkip, inNumToGet,
                                              outNumResults, outNumRemaining );
                }
                        
            }
        


        virtual void draw( void *inItem, doublePair inPos ) {
            SpriteRecord *r = (SpriteRecord*)inItem;

            // don't access r->sprite directly here
            // getSprite needed to invoke dynamic sprite loading
            SpriteHandle sprite = getSprite( r->id );

            double zoom = 1;
            
            if( r->maxD > 64 ) {
                zoom = 64.0 / r->maxD;
                }
            
            drawSprite( sprite, inPos, zoom );
            }



        virtual int getID( void *inItem ) {
            SpriteRecord *r = (SpriteRecord*)inItem;
            
            return r->id;
            }
                
        
        
        virtual void *getItemFromID( int inID ) {
            SpriteRecord *o = getSpriteRecord( inID );
            
            return (void*) o;
            }



        virtual char canDelete( int inID ) {
            return ! isSpriteUsed( inID );
            }
        
        
        virtual void deleteID( int inID ) {
            Pickable::deleteID( inID );
            
            objectPage->clearUseOfSprite( inID );
            deleteSpriteFromBank( inID );
            }
        
        

        virtual const char *getText( void *inItem ) {
            SpriteRecord *r = (SpriteRecord*)inItem;
            
            return r->tag;
            }
        


        virtual float getItemFieldValue( void *inItem,
                                         const char *inFieldName,
                                         char *outFound ) {
            *outFound = true;
            
            // filled with garbage undefined values, but that's okay
            SpriteRecord defaultS;
            
            SpriteRecord *inS = (SpriteRecord*)inItem;

            if( inS == NULL ) {
                inS = &defaultS;
                }

            if( strcmp( inFieldName, "solid" ) == 0 ) {
                return ! inS->multiplicativeBlend;
                }
            if( strcmp( inFieldName, "w" ) == 0 ) {
                return inS->w;
                }
            if( strcmp( inFieldName, "h" ) == 0 ) {
                return inS->h;
                }
            if( strcmp( inFieldName, "visiblew" ) == 0 ) {
                return inS->visibleW;
                }
            if( strcmp( inFieldName, "visibleh" ) == 0 ) {
                return inS->visibleH;
                }
            
            *outFound = false;
            return 0;
            }

        

        virtual void **getAllItemsForFieldSearch( int *outNumItems ) {
            SpriteRecord **returnArray = getAllSprites( outNumItems );
            
            return (void**)returnArray;
            }

        
    protected:
        

        virtual SimpleVector<int> *getStack() {
            return &sStack;
            }

        
        static SimpleVector<int> sStack;

    };
        

#endif
