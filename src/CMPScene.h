#ifndef _CMPScene_
#define _CMPScene_

#include "CScene.h"

/** @brief Multiplayer game on one computer. Every player play on one keyboard. No AI worms.*/
class CMPScene: public CScene {
public:
                CMPScene    ( const int );
private:    
    int         keys        ( const int );
};

#endif
