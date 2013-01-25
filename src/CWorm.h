#ifndef _CWorm_
#define _CWorm_

#include <ncurses.h>
#include <string>

using std::string;
/**
* @brief Abstract Class represented worm.
*/
class CWorm {
public:
                    CWorm               ( const string &, int );
    virtual         ~CWorm              ( void );

    virtual int     moveWorm            ( void ) = 0;
    virtual bool    refreshed           ( void ) const = 0;
    virtual int     moveWorm            ( const string & ) = 0;
    virtual void    directionChange     ( const int ) = 0;
    virtual string  getInfo             ( void ) = 0;

    /** Return if worm si active. */
    bool            isActive            ( void ) const { return m_Active; };
    /** Get the name of worm. */
    string          getName             ( void ) const { return m_Name; };
    /** Set score 0. */
    void            nullScore           ( void ) { m_Score = 0; };
    string          getScore            ( void ) const;
    void            setStartPos         ( const int, const int, const int, const int );
    void            printAll            ( void ) const;
    
    

    bool            operator <          ( const CWorm & ) const;

protected:
    /** @brief Structure that represents worm's body part. */
    struct TChars {
                    TChars  (int y, int x, int part):m_Part(part) {m_X= x; m_Y=y; m_Next = NULL;};
                    ~TChars ( void ) { if(m_Next!=NULL) delete m_Next;};
        int         m_X; /**< X position. */
        int         m_Y; /**< Y position. */
        int         m_Part; /**< Character which has to be printed. */
        TChars     *m_Next; /**< Next body part. */
    };

    static const int    NAME_LEN = 8; /**< Maximum name len. */
    /** Worm direction. */
    enum EDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT 
    };

    TChars         *m_FirstPart; /**< Pointer to first part of worm's body.*/
    TChars         *m_LastPart; /**< Pointer to last part of worm's body.*/
    int             m_CountParts; /**< Body parts count. */
    string          m_Name; /**< Worm's name. */
    int             m_Score;
    int             m_Color; /**< Worm's color. */
    bool            m_Active; /**< Is worm alive or dead.*/
    int             m_Direction; /**< Current direction where worm is going. */
    int             m_PosX; /**< Last X position. */
    int             m_PosY; /**< Last Y position. */

    int             clearWay            ( const int, const int ) const ;

};

#endif