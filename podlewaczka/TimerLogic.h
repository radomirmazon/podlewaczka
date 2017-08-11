#ifndef TIMER_LOGIC_H_   /* Include guard */
#define TIMER_LOGIC_H_

#include "configConst.h"
#include "ExecutorsLogic.h"
#include "NightController.h"
#include "RainController.h"


class TimerLogic {

  public:
    TimerLogic(MainConfiguration* config, ExecutorsLogic* executorsLogic, NightController* nightController, RainController* rainController) {
        this->config= config;
        this->executorsLogic= executorsLogic;
        this->nightController= nightController;
        this->rainController= rainController;
        executorsLogic->setManualMode(true);
    }

    void onButtonPress() {
        gotoManualMode();
        executorsLogic->next();
    }

    void onButtonPressLong() {
        gotoAutoMode();
    }
   
    void tick() {
        //logika do implementacji
        // - określanie reszczu
        // - włączenie automatyczne
        if (!isAutoMode) {
            return;
        }


        if (isRunning()) {

        } 
     
    }

    boolean isManual() {
      return !isAutoMode;
    }

    void gotoManualMode() {
      executorsLogic->setManualMode(true);
      isAutoMode = false;
    }

    void gotoAutoMode() {
      executorsLogic->setManualMode(false);
      executorsLogic->stop();
      isAutoMode = true;
    }
    
  private:
    boolean isRunning() {
      uint32_t howLongAfterDark = nightController->howLong();
      return howLongAfterDark >= (config->secondAfterDark) && isAutoMode;
    }

    boolean isAutoMode = false;
    MainConfiguration* config;
    ExecutorsLogic* executorsLogic;
    NightController* nightController;
    RainController* rainController;
};



#endif // TIMER_LOGIC_H_
