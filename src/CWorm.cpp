#include "CWorm.h"

/** Inicialize variables.
* @param name the name of worm
* @param color worm's color
*/
CWorm::CWorm ( const string & name, int color ) :m_Name(name){
    if(color > 8) color = 0;
    m_Color = color;
    m_Score = 0;
    m_Active = true;
    m_CountParts = 0;
    m_FirstPart = NULL;

}

/** Delete body parts. */
CWorm::~CWorm ( void ){
    if(m_FirstPart != NULL) delete m_FirstPart;
}

/** Get the text line with name and score.
* @return Returning the string which contains name and score.
*/
string CWorm::getScore ( void ) const {
    string out,name;
    int len=NAME_LEN + 2;
    name = m_Name;
    len -= m_Name.length();
    while(len--)
        name += " ";

    char buffer[20]; 
    sprintf(buffer,"%s%04d",name.c_str(), m_Score);
    out = buffer;
    return out;
}

/** Set up the first body part and the first direction. Depends on parametrs.
* @param x X position
* @param y Y position
* @param topEdge top edge of the quadrant
* @param bottomEdge bottom edge of the quadrant
*/
void CWorm::setStartPos ( const int x, const int y,  const int topEdge,  const int bottomEdge){
    m_PosY = y;
    m_PosX = x;
    if(m_PosY - topEdge < bottomEdge - m_PosY)
        m_Direction = UP;
    else
        m_Direction = DOWN;

    m_FirstPart = new TChars(m_PosY, m_PosX, ACS_VLINE);
    m_LastPart = m_FirstPart;
    m_CountParts++;
}

/** Compare score. */
bool CWorm::operator < ( const CWorm & a )const{
    if( this->m_Score < a.m_Score ) return true;
    else return false;
}


/** Print all body parts. */
void CWorm::printAll ( void ) const{
    if(m_FirstPart == NULL) return;
    TChars * tmp = m_FirstPart;
    attron(COLOR_PAIR(m_Color)); 
    while(true){
        mvaddch(tmp->m_Y, tmp->m_X, tmp->m_Part);
        if(!tmp->m_Next) break;
        tmp = tmp->m_Next;
    }
    attroff(COLOR_PAIR(m_Color)); 
}

/** Check if in front of the worm (in the way )is something. Read the character on coordinates in parameter.
* @param x x position
* @param y y position 
* @return 0 if on that position is nothing (space) or 1 if there is some character.
*/
int CWorm::clearWay ( const int x, const int y ) const {
    chtype c;
    move(y, x);
    inchnstr(&c,1);
    if(c == ' ') return 0;
    else return 1;
}




