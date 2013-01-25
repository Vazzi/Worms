#include "CAIWorm.h"

CAIWorm::CAIWorm ( const string name, int color ) :CWorm(name, color){
    m_changeDirection = 10;
}

/** 
* Move worm one part forward. If something is before worm he turn left or right randomly.
* If there is also a block change direction to the other side. If there is also a block 
* then worm just die (set inactive). Then depends on m_changeDirection. If that variable
* isn't zero then decrement else change randomly direction. If there is a block then don't 
* change direction. After that add random number to m_changeDirection.
* @return 0 if everything is ok and 1 if the worm is not active anymore.
*/
int CAIWorm::moveWorm ( void ){
    if(!m_Active) return 0;
    int character, x =m_PosX, y =m_PosY, way, chances = 2, prevDirec = m_Direction;
    bool direc;
    while(true){
        switch(m_Direction){
            case UP:
                y--;
                character = ACS_VLINE;
                break;
            case DOWN:
                y++;
                character = ACS_VLINE;
                break;
            case LEFT:
                x--;
                character = ACS_HLINE;
                break;
            case RIGHT:
                x++;
                character = ACS_HLINE;
                break;
        }
        way = this->clearWay(x, y);
        if( way && chances==2){
            chances--;
            direc = rand()%2;
            this->directionChange(direc);
            x = m_PosX;
            y = m_PosY;
        }else if(way && chances==1){
            m_Direction= prevDirec;
            chances--;
            direc = direc?0:1;
            this->directionChange(direc);
            x = m_PosX;
            y = m_PosY;
        }else if(way && chances==0 ){
            m_Direction= prevDirec;
            if(m_Direction == UP || m_Direction == DOWN) m_LastPart->m_Part = ACS_VLINE;
            else m_LastPart->m_Part = ACS_HLINE;
            attron(COLOR_PAIR(m_Color)); 
            mvaddch(m_LastPart->m_Y, m_LastPart->m_X, m_LastPart->m_Part );
            attroff(COLOR_PAIR(m_Color));
            m_Active = false;
            return 1;
        }else{
            break;
        }
    }
    m_PosX = x;
    m_PosY = y;
    TChars *buffer = new TChars(m_PosY, m_PosX, character);

    attron(COLOR_PAIR(m_Color)); 
    mvaddch(buffer->m_Y, buffer->m_X, buffer->m_Part);
    attroff(COLOR_PAIR(m_Color)); 
    m_LastPart->m_Next = buffer;
    m_LastPart = buffer;
    m_Score++;

    if(!m_changeDirection){
        m_changeDirection = rand()%20+5;
        if((rand()%2)){
            prevDirec = m_Direction;
            int prevPart = m_LastPart->m_Part;
            this->directionChange(rand()%2);
            x = m_PosX; y = m_PosY;
            switch(m_Direction){
                case UP:
                    y--; break;
                case DOWN:
                    y++; break;
                case LEFT:
                    x--; break;
                case RIGHT:
                    x++; break;
            }
            if(this->clearWay(x, y)){
                m_Direction = prevDirec; 
                m_LastPart->m_Part = prevPart;
                attron(COLOR_PAIR(m_Color)); 
                mvaddch(m_LastPart->m_Y, m_LastPart->m_X, m_LastPart->m_Part);
                attroff(COLOR_PAIR(m_Color)); 
            }
        }
    }
    m_changeDirection--;

    return 0;   
}

/** 
* Change worm direction. Change last body part to corner and reprinted it.
* You can turn only left or right. So the calculation of the new direction
* depends on direction before.
* @param direction 1 is left and 0 is right
*/
void CAIWorm::directionChange ( int direction ){
    if(!m_Active) return;
    direction = (direction ? LEFT : RIGHT );
    switch(m_Direction){
        case UP:
            if(direction == LEFT)
                m_LastPart->m_Part = ACS_URCORNER;
            else
                m_LastPart->m_Part = ACS_ULCORNER;
            m_Direction = direction;            
            break;
        case DOWN:
            if(direction == LEFT){
                m_LastPart->m_Part = ACS_LLCORNER;
                m_Direction = RIGHT;
            }else{
                m_LastPart->m_Part = ACS_LRCORNER;
                m_Direction = LEFT;
            }
            break;
        case LEFT:
            if(direction == LEFT){
                m_LastPart->m_Part = ACS_ULCORNER;
                m_Direction = DOWN;
            }else{
                m_LastPart->m_Part = ACS_LLCORNER;
                m_Direction = UP;

            }
            break;
        case RIGHT:
            if(direction == LEFT){
                m_LastPart->m_Part = ACS_LRCORNER;
                m_Direction = UP;
            }else{
                m_LastPart->m_Part = ACS_URCORNER;
                m_Direction = DOWN;
            }
            break;
    }
    attron(COLOR_PAIR(m_Color)); 
    mvaddch(m_LastPart->m_Y, m_LastPart->m_X, m_LastPart->m_Part);
    attroff(COLOR_PAIR(m_Color)); 
    return;
}

