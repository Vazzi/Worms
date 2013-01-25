#ifndef _CPlayableWorm_
#define _CPlayableWorm_

#include "CWorm.h"
/** @brief Represented a worm controlled by player. Contain data processing that you can get from another computer over the network or you can send.*/
class CPlayableWorm :public CWorm{
public:
                            CPlayableWorm       ( const string, int );
    int                     moveWorm            ( void );
    int                     moveWorm            ( const string & );
    void                    directionChange     ( const int );
    string                  getInfo             ( void );
    /** Retrun if worm has been moved. */
    bool                    refreshed           ( void ) const { return m_Refreshed;};
private:    
    bool                    m_Refreshed; /**< If worm has moved true. If worm change direction false.*/
    bool                    m_Moved; /**< If worm has moved true. Only in network. */
    int                     m_ChangedDirection; /**< This is for getInfo() method. If worm has changed direction.*/
    int                     m_NextStep; /**< This is for getInfo() method. If there was a move after direction changed. */

};


#endif