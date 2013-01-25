#include "CTimer.h"
/** Return if time has elapsed. 
* @param ms number of miliseconds
* @return True if time elapsed and false if not.
*/
bool CTimer::elapsed ( const clock_t ms ) { 
    clock_t tick = clock();

    if((tick - m_Counter) >= ms){
         m_Counter = tick;
         return true;
    }
    return false;
}