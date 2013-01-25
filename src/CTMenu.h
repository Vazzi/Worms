#ifndef _CTMenu_
#define _CTMenu_

#include <ncurses.h>
#include "CMenu.h"

/** @brief Text menu. Content of this menu are text lines and close button. */
class CTMenu :public CMenu{
public: 
                        CTMenu      ( const int, const int, const int, const string& );
    bool                addTextLine ( const string & );
    /** Set m_CenterText on true. */
    void                centerText  ( void ) { m_CenterText = true; }; 

protected:
    static const int    LINES_MAX = 8; /**< Maximum lines. */
    TButton             m_Button; /**< Close button. */
    string              m_Text[LINES_MAX]; /**< Array of text lines. */
    int                 m_TextLines; /**< Number of text lines. */
    bool                m_CenterText; /**< Define if text is center or left align. */

    virtual void        print       ( void );
    int                 control     ( void );
};

#endif
