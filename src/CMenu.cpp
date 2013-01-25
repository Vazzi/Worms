#include "CMenu.h"

/** Constructor create color pairs and asign values. Modify titles.
* @param cols number of columns ( screen width ) 
* @param lines number of lines ( screen height )
*/
CMenu::CMenu( const int cols, const int lines ) :m_Cols(cols) {
    init_pair(20, COLOR_WHITE, COLOR_BLACK); 
    init_pair(21, COLOR_BLACK, COLOR_WHITE);
    m_Lines = lines;
    m_SubTitle  = "MENU";
    m_EndTitle = "Jakub Vlasák 2012";
    this->fill(m_SubTitle, '-', TITLE_SIZE);
    this->fill(m_EndTitle, '-', TITLE_SIZE);
}

/** Call methods printAll() and control(). 
* @return Retrun the control() method status.
*/
int CMenu::show( void ){
    this->printAll();
    return this->control();
}
/** Modify subtitle and text. 
* @param subTitle subtitle text
* @param text the text under title
*/
void CMenu::setTexts( const string& subTitle, const string &text ){
    m_SubTitle = subTitle;
    m_Text = text;
    this->fill(m_SubTitle, '-', TITLE_SIZE);
    if(text != "")
        this->fill(m_Text, ' ', TITLE_SIZE);
}
/** Clear screen and call print methods. */
void CMenu::printAll( void ){
    clear();
    this->printTitle();
    this->print();
    this->printEnd();
}
/** Print title WORMS, some text under title and subtitle - describe current menu (MainMenu, Multiplayer etc.).  */
void CMenu::printTitle( void ){
    int posX;

    posX = (m_Cols/2)-(TITLE_SIZE/2);
    if(posX < 0) posX=0;
    attron(COLOR_PAIR(20)); 
    move(1, posX);
    addstr("    :::       :::  ::::::::  :::::::::    :::   :::    ::::::::");
    move(2, posX);
    addstr("   :+:       :+: :+:    :+: :+:    :+:  :+:+: :+:+:  :+:    :+:");
    move(3, posX);
    addstr("  +:+       +:+ +:+    +:+ +:+    +:+ +:+ +:+:+ +:+ +:+         ");
    move(4, posX);
    addstr(" +#+  +:+  +#+ +#+    +:+ +#++:++#:  +#+  +:+  +#+ +#++:++#++  ");
    move(5, posX);
    addstr("+#+ +#+#+ +#+ +#+    +#+ +#+    +#+ +#+       +#+        +#+   ");
    move(6, posX);
    addstr("#+#+# #+#+#  #+#    #+# #+#    #+# #+#       #+# #+#    #+#    ");
    move(7, posX);
    addstr("###   ###    ########  ###    ### ###       ###  ########    ");
    if(m_Text == ""){
        move(9, posX+10);
        printw("This game is running in %dx%d resoluton.",m_Cols, m_Lines);
    }else{
        move(9, posX);
        addstr(m_Text.c_str());
    }
    move(11, posX);
    addstr(m_SubTitle.c_str());
    attroff(COLOR_PAIR(20));
    m_PosY = 13;
}
/** Print last text in menu. Under everything. */
void CMenu::printEnd ( void )const{
    int posX;
    posX = (m_Cols/2)-(TITLE_SIZE/2);
    attron(COLOR_PAIR(20)); 
    move(m_PosY + m_Size, posX);
    addstr(m_EndTitle.c_str());
    attroff(COLOR_PAIR(20));
}
/** Fill text with characters on sides (text in middle).
* @param text this string is going to be changed
* @param character which characters will be filled
* @param size return string len
*/
void CMenu::fill ( string & text, const char character, const int size){
    int i, end = (size/2)-(text.length()/2);
    string subTitle;
    for(i = 0; i < end-1; i++)
        subTitle += character;
    subTitle += ' ';
    subTitle += text;
    subTitle += ' ';
    i+=text.length()+2;
    for(; i < size; i++)
        subTitle += character;
    text = subTitle;
}
