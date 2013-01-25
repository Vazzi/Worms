#include "CSPScene.h"

/**Inicialize variables, header and worms. 
* @param players number of players
* @param playerName player's worm name
*/
CSPScene::CSPScene ( const int players, const string & playerName ) :CScene(players){
    m_WormCount = players;
    string name = playerName;
    m_Worms[0] = new CPlayableWorm(name, 1);
    this->wormStartPos(0, m_Worms[0]);
    m_Head->setPlayer(0,name);

    for(int i = 1; i < m_WormCount; i++){
        name = "WORM ";
        name += i+48;
        m_Worms[i] = new CAIWorm(name, i+1);
        this->wormStartPos(i, m_Worms[i]);
        m_Head->setPlayer(i,name);
    }
} 

/** Change worm's direction if user press KEY_LEFT or KEY_RIGHT and show menu if user press enter.
* @param input input from keyboard
* @return 1 if user want to exit else 0.
*/
int CSPScene::keys ( int input ){
    if(input==10) { // enter key
        if(this->printMenu()) return 1;
        else this->print();
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


