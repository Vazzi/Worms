#ifndef _CClientScene_
#define _CClientScene_

#include "CScene.h"
#include "CConnection.h"

/** @brief Multiplayer game scene. Represented client. 
* Client si connection to server. Recieve data from server to play.
*/

class CClientScene: public CScene{
public:
                CClientScene    ( const string & );
                ~CClientScene   ( void );
    int         show            ( void );
private:
    int         m_Worm; /**< Index of my worm*/
    string      m_Name; /**< Name of my worm*/
    CConnection *m_Client; /**< Pointer to object processing connection between server and client (me).*/
    bool        m_Sended; /**< If data has been sended since last synchronization.*/

    int         keys            ( const int );
    int         control         ( void );
    int         start           ( string & );
    int         sendInfo        ( void ) const;
    void        refresh         ( int &);
    int         next            ( string & );

};

#endif