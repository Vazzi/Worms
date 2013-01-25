#include "CInputIPMenu.h"
#include <arpa/inet.h>

/** Inicialize and set up Back button.
* @param c number of columns
* @param l number of lines
* @param b second button label (not Back)
*/
CInputIPMenu::CInputIPMenu ( const int c, const int l, const string & b) :CTMenu(c,l,2,b){
    m_ButtonBack.m_Value = 1;
    m_ButtonBack.m_Label = "Back";
    m_ButtonBackA = false;
    this->fill(m_ButtonBack.m_Label, ' ', BUTTON_SIZE);
}
/**Print input field and two buttons. Button selection depends on m_ButtonBackA.*/
void CInputIPMenu::print ( void ) {
    int posX, i;
    posX = (m_Cols/2)-(TITLE_SIZE/2);
    mvprintw(m_PosY+1, posX+15, "Server IP adress: ");

    this->printBorder( posX + 34, m_PosY);


    attron(COLOR_PAIR(20));
    for(i = 0; i < m_TextLines; i++){
        if(m_CenterText) posX = (m_Cols/2)-(m_Text[i].length()/2);
        move(m_PosY+i, posX);
        addstr(m_Text[i].c_str());
    }
    attroff(COLOR_PAIR(20));

    posX = (m_Cols/2)-(BUTTON_SIZE/2);
    move(m_PosY+i+2, posX);

    if(m_ButtonBackA){
        attron(COLOR_PAIR(20));
        addstr(m_Button.m_Label.c_str());   
        attroff(COLOR_PAIR(20));
        move(m_PosY+i+4, posX);
        attron(COLOR_PAIR(21));
        addstr(m_ButtonBack.m_Label.c_str());   
        attroff(COLOR_PAIR(21));
    }else{
        attron(COLOR_PAIR(21));
        addstr(m_Button.m_Label.c_str());   
        attroff(COLOR_PAIR(21));
        move(m_PosY+i+4, posX);
        attron(COLOR_PAIR(20));
        addstr(m_ButtonBack.m_Label.c_str());   
        attroff(COLOR_PAIR(20));
    }
    

    m_Size = m_PosY+i+6 - m_PosY;
}
/** Print border for input field 
* @param x position of left edge of border
* @param y position of left edge of border
*/
void CInputIPMenu::printBorder ( const int x, const int y ) {
    mvaddch(y,x,ACS_ULCORNER);
    mvhline(y,x+1,ACS_HLINE,15);
    mvaddch(y,x+16,ACS_URCORNER);
    mvaddch(y+1, x, ACS_VLINE);
    mvaddch(y+1, x+16, ACS_VLINE);
    mvaddch(y+2,x,ACS_LLCORNER);
    mvhline(y+2,x+1,ACS_HLINE,15);
    mvaddch(y+2,x+16,ACS_LRCORNER);
    m_ScanY = y+1;
    m_ScanX = x+1;
    m_PosY += 3;
}
/** Print one textline if there is no. Then wait after press enter or change button selection with
* UP and DOWN arrows. If user press enter on first button then check if ip adress is correct. 
* Looking if ip has four points and if is correct. Print text line if it is ok or not.
* @return Return selected button value.
*/
int CInputIPMenu::control ( void ){
    int x, y, c;
    string  ip;
    echo(); // to see what user typing
    if(m_TextLines==0){
        this->addTextLine(" ");
        this->centerText();
        this->printAll();
    }


    move(m_ScanY, m_ScanX);

    while(true){
        c = getch();
        if(c==10){ // enter key
            noecho();
            if(m_ButtonBackA) return 1;
            move(m_ScanY, m_ScanX);
            chtype  input[17];
            inchnstr(input,15);
            
            ip.clear();
            int points = 3;
            int i;
            for( i = 0; i < 16; i++){
                if(input[i]==' ')break;
                if(input[i]=='.') points--;
                ip += (char *) &input[i];
            }

            if( (inet_addr(ip.c_str())  == INADDR_NONE) || points ){
                this->changeTextLine(0, "Incorrect IP adress!");
            }else{
                this->changeTextLine(0, "Connecting...");
                this->printAll();
                mvaddstr(m_ScanY, m_ScanX,ip.c_str());
                m_IPadress = ip;
                return m_Button.m_Value;
            } 
            
            this->printAll();
            move(m_ScanY, m_ScanX);
            echo();
        }else if(c == KEY_UP){
            m_ButtonBackA = false;
            this->printAll();
            move(m_ScanY, m_ScanX);
        }else if(c == KEY_DOWN){
            m_ButtonBackA = true;
            this->printAll();
            move(m_ScanY, m_ScanX);
        }
        if(is_term_resized(m_Lines, m_Cols)) return 0;
        getyx(stdscr,y,x);
        if(x>=m_ScanX+15)move(m_ScanY, m_ScanX+14);
        refresh();
    }
    return 0;
}

/** Change text line. 
* @param index line index
* @param line new text to line
* @return False if index is out of array or return true.
*/
bool CInputIPMenu::changeTextLine(const int index, const string &line){
    if(index >= m_TextLines) return false;
    m_Text[index] = line;
    return true;
}





