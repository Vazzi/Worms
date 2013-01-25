#include "CScene.h"
#include "CTimer.h"

/** Inicialize ncurses colors */
CScene::CScene ( void ){
    init_pair(TEXT, COLOR_WHITE, COLOR_BLACK);  
    init_pair(WORM1, COLOR_GREEN, COLOR_BLACK);
    init_pair(WORM2, COLOR_RED, COLOR_BLACK); 
    init_pair(WORM3, COLOR_BLUE, COLOR_BLACK); 
    init_pair(WORM4, COLOR_YELLOW, COLOR_BLACK);
    srand ( time( NULL ) );
    m_WormCount = 0;
    m_Head = NULL;

    
}
/** Inicialize ncurses colors, m_Head and player count. 
* @param players players count
*/
CScene::CScene ( const int players ){
    init_pair(TEXT, COLOR_WHITE, COLOR_BLACK);  
    init_pair(WORM1, COLOR_GREEN, COLOR_BLACK);
    init_pair(WORM2, COLOR_RED, COLOR_BLACK); 
    init_pair(WORM3, COLOR_BLUE, COLOR_BLACK); 
    init_pair(WORM4, COLOR_YELLOW, COLOR_BLACK);
    srand ( time( NULL ) );

    m_WormCount = players;
    if(players > WORMS_MAX)m_WormCount = 4;
    m_Head = new CHead(COLS, players);
}

 /** Delete head and worms. */
CScene::~CScene( void ){
    if(m_Head)
        delete m_Head;

    for(int i = 0; i < m_WormCount;i++)
        if(m_Worms[i]) delete m_Worms[i];   

}
/** Call print() and control() methods.
* @return Control status.
*/
int CScene::show ( void ){  
    this->print();
    return this->control();
}

/** Print border around the screen. */
void CScene::printBorder ( void ) const{
    attron(COLOR_PAIR(TEXT)); 
    border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    mvaddch(2,0,ACS_LTEE);
    mvhline(2,1,ACS_HLINE,COLS-2);
    mvaddch(2,COLS-1,ACS_RTEE);

    attroff(COLOR_PAIR(TEXT));

}
/** Print header. */
void CScene::printHeader ( void ) const{
    m_Head->show();
}

/** 
* Start the game. Every MILISECONDS refresh scene and move worms. If any key is pressed call keys method.
* Active variable contains active worm count. If Active is zero then show score menu. Print ladder 
* of player with score. 
* @return 1 if everything is ok and 0 if terminal has been resized. 
*/
int CScene::control( void ){
    CTMenu *scoreMenu;
    CTimer timer;
    int input, active = m_WormCount;

    timeout(1); //To unblock mode ( because of getch() it's blocking )

    while(true){
        input = getch();
        if(this->keys(input))break;

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
            break;
        }

        if(timer.elapsed(MILISECONDS)){
            this->refresh(active);
        }
        if(is_term_resized(LINES, COLS)) return 0;

    }

    timeout(-1); //Set to block mode
    return 1;
}

/** Find the worm with the highest score and null his score.
* @return Return the string of first worm. String contains name and score.
*/
string CScene::firstWorm ( void ) {
    CWorm *tmp;
    string first;
    int worm = 0;

    tmp = m_Worms[0];
    for(int i = 1; i < m_WormCount; i++){
        if(*tmp < *m_Worms[i]){
            tmp = m_Worms[i]; 
            worm = i;
        }
    }

    first = tmp->getScore();
    tmp->nullScore();
    tmp = NULL;
    return first;
    
}
/** Clear screen and call print border, header and worms. */
void CScene::print( void ) const{
    clear();
    this->printBorder();
    this->printHeader();
    for(int i = 0; i < m_WormCount; i++){
        m_Worms[i]->printAll();
    }

}
/** Move worms. If worm is inactive update header. Refresh header.
* @param active decrement this variable if any worm get inactive
*/
void CScene::refresh ( int & active ){
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

/** Set start position to worm. Calculate it randomly. Every worm has his own quadrant.
* @param i the number of worm also a quadrant
* @param worm the worm we want to set start position
*/
void CScene::wormStartPos ( const int i, CWorm * worm ) {
    int x = 2;
    int y = 4;
    int width = (COLS-(2*x))/2;
    int height = (LINES - (2*y))/2;

    switch(i){
        case 1: 
            x += width;
            y += height;
            break;
        case 2:
            y += height;
            break;
        case 3:
            x += width;
            break;
    }

    worm->setStartPos(rand() % width + x, rand() % height + y, y, y+height);

} 

/** Print pause menu. Two choices - return to game or end the game.
* @return 1 if user choose exit in menu else 0. 
*/
int CScene::printMenu ( void ){
    CSMenu *pauseMenu;
    int status;
    pauseMenu = new CSMenu(COLS, LINES);
    pauseMenu->buttonAdd("Return", 0);
    pauseMenu->buttonAdd("Exit", 1);
    pauseMenu->setTexts("PAUSE", "Comon we do not want to wait!");
    status = pauseMenu->show();
    delete pauseMenu;
    if(status)return 1;
    return 0;
}
