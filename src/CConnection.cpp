#include "CConnection.h"


CConnection::CConnection ( void ){
    m_Socket = -1;
}

/** Make socket. Connect to the server and set socket to unblocking mode.
* @param ip IP address.
* @return 3 if connection fail, 2 Socket fail, 1 host fail, 0 ok.
*/
int CConnection::connectToIP ( const char * ip ){
    enum stat {OK, HOSTFAIL, SOCKETFAIL, CONNECTIONFAIL};

    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_Socket < 0) return SOCKETFAIL;

    hostent * host;

    if(!(host = gethostbyname(ip)))
        return HOSTFAIL;

    struct sockaddr_in serv_addr;

    memcpy(&(serv_addr.sin_addr), host->h_addr, host->h_length);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(55555);

    if(::connect(m_Socket,(sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        return CONNECTIONFAIL;

    m_BlockFlag = fcntl(m_Socket, F_GETFL, 0);
    if (fcntl(m_Socket, F_SETFL, m_BlockFlag | O_NONBLOCK) == -1)
    {
        return SOCKETFAIL;
    }

    return OK;

}

/** Create server. Set socket to unblock mode. And make queue.
* @return 3 queue makeing fail, 2 socket fail, 1 bind fail, 0 ok.
*/
int CConnection::create ( void ){
    enum stat {OK, BINDFAIL, SOCKETFAIL, QUEUEFAIL};

    m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_Socket < 0) return SOCKETFAIL;
    m_BlockFlag = fcntl(m_Socket, F_GETFL, 0);
    if (fcntl(m_Socket, F_SETFL, m_BlockFlag | O_NONBLOCK) == -1)
    {
        return SOCKETFAIL;
    }

    m_SockName.sin_family = AF_INET;
    m_SockName.sin_port = htons(55555);
    m_SockName.sin_addr.s_addr = INADDR_ANY;
    if(bind(m_Socket, (sockaddr *)&m_SockName, sizeof(m_SockName)) < 0 )
        return BINDFAIL;

    if(listen(m_Socket, 3) < 0)
        return QUEUEFAIL;

    return OK;
}

/** Accept requirements for connection.
* @param clientNum Client number - socket.
* @return 0 if nothing to accept or 1 if there is request.
*/
int CConnection::accept( int & clientNum ) const {
    struct sockaddr_in client;
    socklen_t clientLen = sizeof(client);  
    clientNum = ::accept(m_Socket, (sockaddr*)&client, &clientLen);

    fcntl(clientNum, F_SETFL, m_BlockFlag | O_NONBLOCK);

    if( clientNum < 0 )
        return 0;

    return 1;
}

/** Sending data to server or client.
* @param data data to send
* @param client who to send data (default m_Socket)
* @return 1 if can't send 0 if successfully. 
*/
int CConnection::sendData ( const string & data, int client ) const {
    if(client == -1) client = m_Socket;
    if (send(client, data.c_str(), data.size() + 1, 0) == -1){
        return 1;
    }
    return 0;
}

/** Recive data from server or client.
* @param clientNum from who recive data (default m_Socket)
* @param text data which has been recived
* @return 0 if data recived successfully else 1.
*/
int CConnection::reciveData (string &text, int clientNum) const{
    char buf[1000];

    if(clientNum == -1 ) clientNum = m_Socket;
    if (::recv(clientNum, buf, 1000 - 1, 0) != -1){
        text = buf;
       return 0;
    }
    return 1;
}

/** Close socket */
void CConnection::end ( void ){
    if(m_Socket >= 0)
        close(m_Socket);

}
