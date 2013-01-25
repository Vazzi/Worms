#ifndef _CScene_
#define _CScene_


#include <ncurses.h>
#include <cstdlib>
#include "CHead.h"
#include "CSMenu.h"
#include "CTMenu.h"
#include "CPlayableWorm.h"

/** @brief Abstract class. Create a game scene. Control worms. */
class CScene {
public:
                        CScene              ( void );
                        CScene              ( const int );
    virtual             ~CScene             ( void );
    virtual int         show                ( void );

protected:
    /** Ncurses color pairs. */
    enum COLORS {
        TEXT, /**< Text and border colors.*/
        WORM1, /**< Worm 1 color (Green).*/
        WORM2, /**< Worm 2 color (Red).*/
        WORM3, /**< Worm 3 color (Blue).*/
        WORM4 /**< Worm 4 color (Yellow)*/
    };  
    static const int            WORMS_MAX = 4; /**< Maximum worms count. */
    static const unsigned int   MILISECONDS = 20000; /**< Miliseconds elapsed in Timer. */
    CHead              *m_Head; /**< Pointer to header. */
    CWorm              *m_Worms[WORMS_MAX]; /**< Array of pointer to worms.*/
    int                 m_WormCount; /**< Worms count. */
    
    virtual int         keys                ( const int ) = 0;
    virtual void        print               ( void ) const;
    virtual int         control             ( void );
    void                refresh             ( int & );
    string              firstWorm           ( void );
    void                wormStartPos        ( const int, CWorm * );
    void                printBorder         ( void ) const;
    void                printHeader         ( void ) const;
    int                 printMenu           ( void );

};

#endif