#ifndef _CHead_
#define _CHead_

#include <ncurses.h>
#include <string>

using std::string;

/** @brief Create a header to a game scene where are players with their color and score. */
class CHead {
public:
                        CHead           ( const int, int );
                        ~CHead          ( void );
    int                 setPlayer       ( const int, const string & );
    int                 show            ( void ) const;
    void                refresh         ( void ) const;
    bool                setInactive     ( const int );

private:
    static const int COLS_MAX = 4;  /**< Maximum number of columns (labels)*/
    /** Label structure. Represents one column/label.*/
    struct TLabel{
        string          m_Name; /**< Player name. */
        unsigned int    m_Score; /**< Player score. */
        bool            m_Active; /**< If player is active or inactive (dead or alive).*/
    };

    int                 m_Width; /**< Screen width. */
    int                 m_ColsCount; /**< Count of current columns/label.*/
    int                 m_NameLen; /**< Maximum len name.*/
    int                 m_ColWidth; /**< Column width.*/
    TLabel             *m_Players; /**< Array of labels.*/

    void                print           ( void ) const;
    void                printBorder     ( void ) const;
    void                printScore      ( const int ) const;
    void                rePrint         ( void );
};

#endif