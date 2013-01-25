#ifndef _CSPScene_
#define _CSPScene_


#include "CScene.h"
#include "CAIWorm.h"

/** @brief Singleplayer scene game. Contains one playable worm and AI worms. */
class CSPScene: public CScene {
public:
                    CSPScene    ( const int, const string & );
private:
    int             keys        ( const int );
};


#endif