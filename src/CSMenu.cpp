#include "CSMenu.h"

/** Inicialize values.
* @param cols number of screen columns
* @param number of screen lines
*/
CSMenu::CSMenu ( const int cols, const int lines ) :CMenu(cols, lines){
    m_BCount = 0;
    m_Index = 0;
}
/** Add new button.
* @param label button text label
* @param value button return value
* @return False if there is too much buttons else true.
*/
bool CSMenu::buttonAdd ( const string & label, int value){
    if(m_BCount == BUTTON_MAX-1) return false;
    m_Buttons[m_BCount].m_Label = label;
    m_Buttons[m_BCount].m_Value = value;
    this->fill(m_Buttons[m_BCount].m_Label, ' ', BUTTON_SIZE);
    m_BCount++;
    return true;
}
/** Print content (buttons). Select first button. */
void CSMenu::print( void ){
    int posX, posY;
    posX = (m_Cols/2)-(BUTTON_SIZE/2);
    posY = m_PosY;

    for(int i = 0; i < m_BCount; i++,posY += 2){
        if(i == m_Index) attron(COLOR_PAIR(21)); 
        else attron(COLOR_PAIR(20)); 
        move(posY, posX);
        addstr(m_Buttons[i].m_Label.c_str());
        if(i == m_Index) attroff(COLOR_PAIR(21)); 
        else attroff(COLOR_PAIR(20)); 
    }
    m_Size = posY - m_PosY; 
}
/** Control keyboard input.
* @return Return 0 if error apears (terminal size changed). Else return value of button which is selected.  
*/
int CSMenu::control ( void ){
    int c;
    while(true){
        c = getch();
        if(c==KEY_UP){
            m_Index--;
            if(m_Index < 0)m_Index = 0;
            this->printAll();
        }else if(c == KEY_DOWN){
            m_Index++;
            if(m_Index >= m_BCount) m_Index--;
            this->printAll();
        }else if(c == 10){
            return m_Buttons[m_Index].m_Value;
        }
        if(is_term_resized(m_Lines, m_Cols)) return 0;
        refresh();
    }
    return 0;
}

