#include "CServerScene.h"
#include "CTimer.h"


/** Create first worm. 
* @param name worm's name
*/
CServerScene::CServerScene ( const string & name ):CScene() {
    m_WormCount = 1;
    m_Worms[0] = new CPlayableWorm ( name, 1 );
    
}
/** This method create server. Set up header and checking connection if somebody want to 
* connect. If so then add new worm and send client info about the other worms that are 
* connected and also about my worm. If user press 'q' then server shut down. If user press
* enter and there is connected minimal one client then start the game.
* @return if CREATEFAIL create server fail, CONFAIL if connection error else return stat from control().
*/
int CServerScene::show( void ){
    int client, input;
    int stat = m_Server.create();
    if(stat >= 1) return CREATEFAIL;

    m_Head = new CHead( COLS, 1);
    m_Head->setPlayer (0,m_Worms[0]->getName());
    this->printServer();
    string name;
    timeout(1); //set unblocking mode because of getch()
    stat = 1;
    while(true){
        input = getch();
        if(input==(int)'q')break;
        if(input==10){
            if(m_WormCount > 1){
                this->start();
                stat = this->control();
                break;
            }
        }
        if(m_Server.accept(client)) {
            while(m_Server.reciveData(name, client)){}
            string data = " ";
            data[0] = (char)(m_WormCount+48);
            /* Send connected clients data about new player. */
            for(int i = 0; i < m_WormCount; i ++){
                data += m_Worms[i]->getName() + ';';
                if(i) {
                    if(m_Server.sendData('2'+name,m_Sockets[i])) {
                        m_Server.end();
                        return CONFAIL;
                    }
                }
            }
            m_Server.sendData(data, client);
            if(this->addPlayer( client, name ))break;
            this->printServer();

        }
    }
    timeout(-1); //set blocking mode
    m_Server.end();
    return stat;
}
/** Clear screen and print border, header and info about how to start and quit game. */
void CServerScene::printServer ( void ) const{
    clear();
    this->printBorder();
    this->printHeader();
    mvprintw(LINES/2,COLS/2-10, "To start game press enter.");
    mvprintw(LINES/2+1,COLS/2-10, "To quit game press q.");

}
/**Adding new player to game. Create new worm and new column in header.
* @param id client's socket
* @param name clients's worm name
* @return 1 if worms count equals 4 else 0.
*/
int CServerScene::addPlayer ( const int id , const string &name ){ 
    m_Sockets[m_WormCount] = id;
    m_Worms[m_WormCount] = new CPlayableWorm ( name, m_WormCount+1 );
    m_Head->setPlayer ( m_WormCount, name  );
    m_WormCount++;
    if(m_WormCount == 4) return 1;
    return 0;
}

/** Set worms start position and send data to clients. Sending '1' that starting game.
* @return 0 every time.
*/
int CServerScene::start ( void ){
    string data = "1";
    for(int i = 0; i < m_WormCount; i++){
        this->wormStartPos(i, m_Worms[i]);
        data += m_Worms[i]->getInfo();
    }
    for(int i = 1; i < m_WormCount; i++){
        m_Server.sendData(data, m_Sockets[i]);
    }
    this->print();
    return 0;
}
/** Firstly wait some time because client have to process their data. Then send clients "3" that means
* that server starting a game. Then the control. If server recieve any data process ( move client worm ).
* If time elapsed then refresh() and sendInfo(). If user press any key call keys(). In active variable
* is saved count of active worms if this variable is zero then stop the game wait on user and show score menu.
* @return CONFAIL if connection error (can't send data, bad data recieve) 1 if everything is ok
*/
int CServerScene::control ( void ){
    CTMenu *scoreMenu;
    CTimer timer;
    int status = 0, input, active = m_WormCount;
    string inData;

    while(!timer.elapsed(1000000)) {}

    for(int i = 1; i < m_WormCount; i++){
        if(m_Server.sendData("3", m_Sockets[i])) return CONFAIL;
    }

    while(!status){
        input = getch();
        status = this->keys(input);
        if(status) break;   
        
        if(!m_Server.reciveData(inData, m_Sockets[1])){
            int index = inData[0]-48;
            if(index>=m_WormCount || index < 1) return CONFAIL;
            inData = inData.substr(1,inData.length());
            m_Worms[index]->moveWorm(inData);
        }
        if(!active){
            while(true) if(getch()==10) break;
            scoreMenu = new CTMenu (COLS, LINES, 1, "Main Menu");
            scoreMenu->setTexts("GAME OVER - SCORE", "Who is the boss? Yeah!");
            scoreMenu->centerText();

            int max = m_WormCount, i = 0 ;
            string text;
            while(i++ < max){

                text = i + 48;
                text += ". ";
                text += this->firstWorm();
                scoreMenu->addTextLine(text);
            }
            scoreMenu->show();
            delete scoreMenu;
            status = 1;
            break;
        }
        if(timer.elapsed(MILISECONDS)){
            this->refresh(active);
            status = this->sendInfo();  
        }
    
    }
    return status;
}
/** Sending '4' + data about worms to clients. The first character mean that it is sync data.
* @return CONFAIL if can not send data else 0.
*/
int CServerScene::sendInfo( void ) const{
    string data = "4";
    for(int i = 0; i < m_WormCount; i++){
        data += m_Worms[i]->getInfo();
    }
    for(int i = 1; i < m_WormCount; i++){
        if(m_Server.sendData(data, m_Sockets[i])) return CONFAIL;
    }
    return 0;
}

/** Change worm's direction if user press KEY_LEFT or KEY_RIGHT.
* @param input key input
* @return If user press enter return 1 else return 0.
*/
int CServerScene::keys ( const int input ){
    if(input==10) { //enter key
        return 1;
    }
    if(input==int(KEY_LEFT)){
        if(m_Worms[0]->refreshed())
            m_Worms[0]->directionChange(1);
    }else if(input==int(KEY_RIGHT)){
        if(m_Worms[0]->refreshed())
            m_Worms[0]->directionChange(0);
    }
    return 0;
}

