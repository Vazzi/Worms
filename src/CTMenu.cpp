#include "CTMenu.h"

/** Setting up close button. 
* @param value button return value
* @param label button label
*/
CTMenu::CTMenu ( const int cols, const int lines, const int value, const string & label) :CMenu(cols, lines){
    m_Button.m_Value = value;
    m_Button.m_Label = label;
    m_CenterText = false;
    m_TextLines =0;
    this->fill(m_Button.m_Label, ' ', BUTTON_SIZE);
}
/** Add new text line.
* @param line text line which will be added
* @return False if line length is too big or there is too much text lines.
*/
bool CTMenu::addTextLine ( const string & line ){
    if(m_TextLines >= LINES_MAX) return false;
    if(line.length() > (unsigned int)TITLE_SIZE) return false;
    m_Text[m_TextLines++] = line;
    return true;
}
/** Print content ( text lines and button ). Select close button.*/
void CTMenu::print( void ){
    int posX, i;
    posX = (m_Cols/2)-(TITLE_SIZE/2);

    attron(COLOR_PAIR(20));
    for(i = 0; i < m_TextLines; i++){
        if(m_CenterText) posX = (m_Cols/2)-(m_Text[i].length()/2);
        move(m_PosY+i, posX);
        addstr(m_Text[i].c_str());
    }
    attroff(COLOR_PAIR(20));

    posX = (m_Cols/2)-(BUTTON_SIZE/2);
    move(m_PosY+i+2, posX);

    attron(COLOR_PAIR(21));
    addstr(m_Button.m_Label.c_str());   
    attroff(COLOR_PAIR(21));

    m_Size = m_PosY+i+4 - m_PosY;
}
/** Keyboard control.
* @return Button value or 0 if error ( terminal resize ).
*/
int CTMenu::control ( void ) {
    int c;
    while(true){
        c = getch();
        if(c==10){
            return m_Button.m_Value;
        }
        if(is_term_resized(m_Lines, m_Cols)) return 0;
        refresh();
    }
    return 0;
}
