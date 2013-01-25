#include "CHead.h"

/** 
* Inicialize colors, name len and column width. 
* Create labels with default names (Player1, Player2...).
* @param width screen width ( screen columns count )
* @param cols number of labels / columns / players.
*/
CHead::CHead ( const int width, int cols){
    init_pair(11, COLOR_BLACK, COLOR_GREEN);
    init_pair(12, COLOR_BLACK, COLOR_RED); 
    init_pair(13, COLOR_BLACK, COLOR_BLUE); 
    init_pair(14, COLOR_BLACK, COLOR_YELLOW);
    init_pair(30, COLOR_RED, COLOR_BLACK);

    m_Width = width;
    if(cols > COLS_MAX) cols = 4;
    else if(cols < 1) cols = 1;
    m_ColsCount = cols;
    m_NameLen = (width/cols)/2 - 4;
    m_ColWidth = width/cols;
    m_Players = new TLabel[COLS_MAX];
    for(int i = 0; i < COLS_MAX; i++){
        m_Players[i].m_Name = "Player";
        m_Players[i].m_Name += i + 49;
        m_Players[i].m_Score = 0;
        m_Players[i].m_Active = true;
    }
}
/** Delete labels. */
CHead::~CHead ( void ){
    delete [] m_Players;
}
/** Call private print() method.
* @return Always 0.
*/
int CHead::show ( void ) const{
    this->print();
    return 0;
}
/** Refresh players score when they are active and print score with printScore(int) method.*/
void CHead::refresh ( void ) const{
    for(int i = 0; i < m_ColsCount; i++){
        if(m_Players[i].m_Active)
            m_Players[i].m_Score++;
        if(i==m_ColsCount-1)move(1, m_Width-13); 
        else move(1, m_ColWidth*(i+1)-10);
        this->printScore(i);
        move(1, m_ColWidth*(i+1)+4);
    }
}
/** Set player inactive.
* @param index player index
* @return False if index is out of range.
*/
bool CHead::setInactive ( const int index ){
    if(index >= m_ColsCount || index < 0) return false;
    m_Players[index].m_Active = false;
    return true;
}
/** Change players name.
* @param index player index
* @param name new player name
* @return GOOD(0) if everything is ok. INDEX(1) if index is out of range and NAMELEN(2) if name is too long.
*/
int CHead::setPlayer ( const int index, const string & name){
    enum EStatus {GOOD, INDEX, NAMELEN};

    if(index > COLS_MAX || index < 0) return INDEX;
    if(index > m_ColsCount) return INDEX;
    if(index == m_ColsCount) {
        m_ColsCount++;
        m_NameLen = (m_Width/m_ColsCount)/2 - 4;
        m_ColWidth = m_Width/m_ColsCount;
    }
    if(name.length() > (unsigned int)m_NameLen) return NAMELEN;
    m_Players[index].m_Name = name;
    return GOOD;
}
/** Print labels. One label mean players name, color and score. */
void CHead::print ( void ) const{
    attron(COLOR_PAIR(0));

    this->printBorder();

    move(1,2);

    for(int i = 0; i < m_ColsCount; i++){
        addstr(m_Players[i].m_Name.c_str());
        if(i)move(1, m_NameLen+4+(m_ColWidth*i));
        else move(1, m_NameLen+2);

        attron(COLOR_PAIR(i+11));
        printw(" ");
        attroff(COLOR_PAIR(i+11));
        if(i==m_ColsCount-1)move(1, m_Width-13); 
        else move(1, m_ColWidth*(i+1)-10);
        this->printScore(i);
        move(1, m_ColWidth*(i+1)+4);
    }
    attroff(COLOR_PAIR(0));
}
/** Print head border. */
void CHead::printBorder ( void ) const {
    for(int i = 1; i < m_ColsCount;i++){
        mvaddch(0,(m_ColWidth*i)+2,ACS_TTEE);
        mvaddch(1,(m_ColWidth*i)+2,ACS_VLINE);
        mvaddch(2,(m_ColWidth*i)+2,ACS_BTEE);
    }
}
/** Print score. If player is inactive print it red. 
* @param index Player index.
*/
void CHead::printScore ( const int index) const{
    int scoreNumber = m_Players[index].m_Score;
    if(m_Players[index].m_Active) attron(COLOR_PAIR(0));
    else attron(COLOR_PAIR(30));
    printw("SCORE: %04d",scoreNumber);
    if(m_Players[index].m_Active) attroff(COLOR_PAIR(0));
    else attroff(COLOR_PAIR(30));
}




