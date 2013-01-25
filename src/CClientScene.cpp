#include "CClientScene.h"
#include "CInputIPMenu.h"

/** Inicialize client and setting up worm's name.
* @param name worm's name
*/
CClientScene::CClientScene ( const string &name ) {
    m_Name = name;
    m_Client = new CConnection();
    m_Sended = false;
}

/** Delete m_Client */
CClientScene::~CClientScene ( void ) {
    delete m_Client;
}
/** Create menu to get ip adress from user. Try to connect to the server. If can't, write it to menu else
* send data to server with your worm's name and process recived data. Print scene with players in header.
* Then wait on server if recive more data about more clients (update and print scene again) or if the game
* starts. If the game starts then start() and control(). User can get out by press enter.
* @return 1 every time.
*/
int CClientScene::show( void ){
    int status = 0;
    string ip;
    CInputIPMenu *getIP = new CInputIPMenu(COLS, LINES, "Connect");
    getIP->setTexts("JOIN GAME", "Write down server IP address.");
    string data;

    while(true){
        status = getIP->show();
        if(status != 2) break;
        ip = getIP->getInput();
        
        if(m_Client->connectToIP(ip.c_str())){
            getIP->changeTextLine(0, "Can not connect!");
            m_Client->end();
        }else{
            getIP->changeTextLine(0, "Connected!");
            m_Client->sendData(m_Name);
            
            while(m_Client->reciveData(data)){}

            m_WormCount = data[0]-48;

            int index;

            string name;

            data = data.substr(1,data.length()-1);
            
            m_Head = new CHead( COLS, m_WormCount+1);
            for(int i = 0; i < m_WormCount; i++){
                index = data.find_first_of(';');
                name = data.substr(0,index);
                m_Head->setPlayer ( i, name  );
                data = data.substr(index+1,data.length()-index);    
                m_Worms[i] = new CPlayableWorm (name, i+1);
            }

            m_Worms[m_WormCount] = new CPlayableWorm (m_Name, m_WormCount+1);
            m_Head->setPlayer ( m_WormCount, m_Name );
            
            m_Worm = m_WormCount++;
            this->print();

            timeout(1);
            while(true){
                if(getch()=='q')break;
                if(!m_Client->reciveData(data)){
                    if( data[0] == '1' ) {
                        data = data.substr(1, data.length());
                        this->start( data );
                        if(this->control())
                            getIP->changeTextLine(0, "Errors in connection.");
                        break;
                    }else if( data[0] == '2'){
                        name = data.substr(1,data.length()-1);
                        m_Worms[m_WormCount] = new CPlayableWorm (name, m_WormCount+1);
                        m_Head->setPlayer (m_WormCount++, name );
                        this->print();
                    }else {
                        getIP->changeTextLine(0, "Error in connection.");
                        break;
                    }
                }
            }
            timeout(-1);
            m_Client->end();    
        }

    }
    delete getIP;
    return status;
}

/** Give data to worms.
* @param input input data received from server
* @return Always return 0.
**/
int CClientScene::start ( string & input ){
    for(int i = 0; i < m_WormCount; i++){
        m_Worms[i]->moveWorm(input);
        if(i != m_WormCount-1)
            input = input.substr(input.find_first_of(';')+1, input.length());
    }
    this->print();
    return 0;
}
/** Give data to worms during the game. If data of my worm was sended then don't update my worm. 
* @param input input data received from server
* @return Number of worms that changed to inactive. 
*/
int CClientScene::next ( string & input ){
    int inActive = 0;
    for(int i = 0; i < m_WormCount; i++){
        if(i != 0)
            input = input.substr(input.find_first_of(';')+1, input.length());
        if(i == m_Worm && m_Sended) continue;
        if(m_Worms[i]->isActive()){
            if(m_Worms[i]->moveWorm(input)){
                m_Head->setInactive(i);
                inActive++;
            }
        }
        
        
    }
    this->print();
    return inActive;
}
/** Wait on server to start and then wait on server to send first data. If data are incorrect return.
* Process data and control if user press any key if so call key method. If user want to quit game send
* server "9". Check if server send data and process them. If all of worms are dead then show score menu
* and end.
* @return 1 if there is connection error or 0 if ok.
*/
int CClientScene::control ( void ){
    CTMenu *scoreMenu;
    int status = 1, input, active = m_WormCount;
    string inData, outData;

    while(m_Client->reciveData(inData)){ }
    if(inData[0] != '3' ) return 1;
    while(m_Client->reciveData(inData)){ }

    while(status){

        if( inData[0] != '4' ) return 1;

        inData = inData.substr(1, inData.length());
        active -= this->next(inData);
        m_Sended = false;
        while(true){
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
                status = 0;
                break;
            }
            input = getch();
            status = this->keys(input);
            if(!status) { m_Client->sendData("9"); break; }


            if(!m_Client->reciveData(inData)){
                this->refresh(active);
                break;
            }
        }
    }

    return status;

}
/** Move active worms. If there is new inactive worm then decrement active variable.
* @param active Number of active worms. 
*/
void CClientScene::refresh ( int & active){
    for(int i = 0; i < m_WormCount; i++ ){
        if(m_Worms[i]->isActive()){
            if(m_Worms[i]->moveWorm()){
                m_Head->setInactive(i);
                active--;
            }
        }
    }
    m_Head->refresh();
}

/** Send info about my worm to server.
* @return 1 if fail to send else 0.
*/
int CClientScene::sendInfo ( void ) const{
    string data = " ";
    data[0] = m_Worm + 48;
    data += m_Worms[m_Worm]->getInfo();
    if(m_Client->sendData(data)) return 1;

    return 0;
}

/** Controls keys. Change direction of the worm only if it has not sended before. 
* If direction changed then send data to server.
* @param input Key input. 
* @return 0 if enter pressed else 1.
*/
int CClientScene::keys ( int input ) {
    if(input==10) { // enter key
        return 0;
    }
    if(!m_Sended){
        if(input==int(KEY_LEFT)){
            if(m_Worms[m_Worm]->refreshed()){
                m_Worms[m_Worm]->directionChange(1);
                this->sendInfo();
                m_Sended = true;
            }
        }else if(input==int(KEY_RIGHT)){
            if(m_Worms[m_Worm]->refreshed()){
                m_Worms[m_Worm]->directionChange(0);
                this->sendInfo();
                m_Sended = true;
            }
                
        }
    }
    return 1;
}