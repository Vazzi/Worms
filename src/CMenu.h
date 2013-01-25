#ifndef _CMenu_
#define _CMenu_

#include <ncurses.h>
#include <string>

using std::string;
/** @brief Abstract class represented menu in game.
*/
class CMenu {
public:
                        CMenu           ( const int, const int ); 
    int                 show            ( void );
    void                setTexts        ( const string& , const string & );
protected:
    /** @brief Defines button label and return value. */
    struct TButton {
        string          m_Label; /**< Button label */
        int             m_Value; /**< Button return value */
    };

    static const int    TITLE_SIZE = 63; /**< Title size */
    static const int    BUTTON_SIZE = 20; /**< Button size */
    string              m_SubTitle; /**< Subtitle text */
    string              m_EndTitle; /**< Text on last line */
    string              m_Text; /**< Text under title */
    int                 m_Cols; /**< Number of colummns */
    int                 m_Lines; /**< Number of lines */
    int                 m_PosY; /**< Where the content start (Line position) */
    int                 m_Size; /**< Height of content (number of lines) */
    
    virtual int         control         ( void ) = 0;
    virtual void        print           ( void ) = 0;
    void                printTitle      ( void );
    void                printAll        ( void );
    void                printEnd        ( void ) const;
    void                fill            ( string &, const char, const int);
    

};

#endif
