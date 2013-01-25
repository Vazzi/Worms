#ifndef _CAIWorm_
#define _CAIWorm_

#include <cstdlib>
#include "CWorm.h"
/** @brief Represented Artificial Intelligence worm. */
class CAIWorm : public CWorm {
    public:
                    CAIWorm         ( const string, int );
        int         moveWorm        ( void );

        /** Do nothing. Just return false. */
        bool        refreshed       ( void ) const {return false;};
        /** Do nothing. Return 0. */
        int         moveWorm        ( const string & ) { return 0;};
        /** Do nothing. Return empty string. */
        string      getInfo         ( void ) { return "";};

    private:
        int         m_changeDirection; /**< Contains random number. If contains zero worm change direction. */

        void        directionChange ( int );
};

#endif