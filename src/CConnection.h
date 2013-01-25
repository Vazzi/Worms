#ifndef _CConnection_
#define _CConnection_

#include <string>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>

using std::string;
/** @brief Manage connection. Create a server or connect to the server. */
class CConnection {
public:
                CConnection     ( void );
                /** Close socket */
                ~CConnection    ( void ) { this->end();};
    int         connectToIP     ( const char * );
    int         create          ( void );
    int         accept          ( int & ) const;
    int         sendData        ( const string & , int  = -1 ) const;
    int         reciveData      ( string &, int = -1)const ;
    void        end             ( void );
private:    
    int         m_Socket; /**< My socket. */
    sockaddr_in m_SockName; /**< Struct of my/server information (IP address, Port, etc. ). */
    int         m_BlockFlag; /**< Socket block mode flags.  */
};

#endif