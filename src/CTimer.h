#ifndef _TIMER_
#define _TIMER_

#include <ctime>
/** @brief Easy timer. */
class CTimer {
public:
                /** Just inicialize counter to 0 */
                CTimer      ( void ) :m_Counter(0) { };
    bool        elapsed     ( const clock_t ) ;
private:
    clock_t     m_Counter; /** The last miliseconds. */
   
};

#endif