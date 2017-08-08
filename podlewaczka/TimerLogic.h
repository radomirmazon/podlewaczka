#ifndef TIMER_LOGIC_H_   /* Include guard */
#define TIMER_LOGIC_H_

#include "configConst.h"


class TimerLogic {

  public:
    TimerLogic() {
       runAfterDark[0] = 3*60*60; //3 hour after dark
       runAfterDark[1] = 0; //run after runAfterDark[0]
    }

   void tick() {

   }
   
  private:
    uint32_t runAfterDark[2];

};



#endif // TIMER_LOGIC_H_