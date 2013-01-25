#ifndef _CInputMenu_
#define _CInputMenu_

#include "CTMenu.h"
/** @brief Menu that work with IP adress. Contains input field and two buttons.*/
class CInputIPMenu :public CTMenu{
public:
                            CInputIPMenu ( const int, const int, const string &);
    /** Returning IP adress which it gets from user. */
    string                  getInput ( void ) const {return m_IPadress;};
    bool                    changeTextLine(const int, const string &);

protected:
    string                  m_IPadress; /**< Correct Ip adress which user wrote.*/
    int                     m_ScanX; /**< X position where input field starts.*/
    int                     m_ScanY; /**< Y position where input field starts.*/
    TButton                 m_ButtonBack; /**< Back button. */
    bool                    m_ButtonBackA; /**< If button Back is selected. */

    void                    print   ( void );
    int                     control ( void );
    void                    printBorder( const int, const int);
    
};

#endif
