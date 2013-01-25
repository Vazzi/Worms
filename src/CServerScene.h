#ifndef _CServerScene_
#define _CServerScene_

#include "CScene.h"
#include "CConnection.h"
/** @brief Multiplayer game scene for network connection. Create a server and wait for clients.
* User playing a game with clients.
*/
class CServerScene: public CScene{
public:
                    CServerScene    ( const string & );
    int             show            ( void );
    
private:
    static const int CONFAIL = -2; /**< Connection error. */
    static const int CREATEFAIL = -1; /**< Can not create server. */
    int             m_Sockets[WORMS_MAX]; /**< Array of clients sockets. Where to send data. */
    string          m_Name; /**< Name of worm on this computer. */ 
    CConnection     m_Server; /**< Connection. Sending, recieving data and create, end connection.*/

    int             keys            ( const int );
    int             addPlayer       ( const int , const string & );
    int             start           ( void ) ;
    int             control         ( void );
    int             sendInfo        ( void ) const;
    void            printServer     ( void ) const;

};

#endif