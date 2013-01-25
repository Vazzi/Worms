#include "CMPScene.h"

/** Inicialize worms and give them default names (Player1, Player2, etc.)
* @param players players count
*/
CMPScene::CMPScene ( const int players ) :CScene(players){
    string name;
    for(int i = 0; i < m_WormCount; i++){
        name = "Player ";
        name += i+49;
        m_Worms[i] = new CPlayableWorm(name, i+1);
        this->wormStartPos(i, m_Worms[i]);
        m_Head->setPlayer(i,name);
    }

}

/** Process keyboard input. If enter then print menu. Other keys are for worms direction change.
* @param input key from keyboard
* @return 1 if user choose exit in menu else 0.
*/
int CMPScene::keys ( int input ){
    if(input==10) { //enter key
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
    if(m_WormCount>1){
        if(input==int('a')){
            if(m_Worms[1]->refreshed())
                m_Worms[1]->directionChange(1);
        }else if(input==int('s')){
            if(m_Worms[1]->refreshed())
                m_Worms[1]->directionChange(0);
        }
        if(m_WormCount>2){
            if(input==int('j')){
                if(m_Worms[2]->refreshed())
                    m_Worms[2]->directionChange(1);
            }else if(input==int('k')){
                if(m_Worms[2]->refreshed())
                    m_Worms[2]->directionChange(0);
            }
            if(m_WormCount>3){
                if(input==int('4')){
                    if(m_Worms[3]->refreshed())
                        m_Worms[3]->directionChange(1);
                }else if(input==int('5')){
                    if(m_Worms[3]->refreshed())
                        m_Worms[3]->directionChange(0);
                }
            }
        }
    }

    return 0;
}