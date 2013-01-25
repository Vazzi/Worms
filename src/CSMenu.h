#ifndef _CSMenu_
#define _CSMenu_

#include <curses.h>
#include "CMenu.h"

using std::string;
/** @brief Standart menu with buttons. */
class CSMenu :public CMenu{
public:
                            CSMenu      ( const int, const int );
    bool                    buttonAdd   ( const string &, const int );
private:
    static const int        BUTTON_MAX = 8; /**< Max buttons we can add.*/
    TButton                 m_Buttons[BUTTON_MAX]; /**< Array of added buttons.*/
    int                     m_BCount; /**< How many buttons we have.*/
    int                     m_Index; /**< Which button is currently selected.*/
    
    void                    print       ( void );
    int                     control     ( void ); 
};

#endif