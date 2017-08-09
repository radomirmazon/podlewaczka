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
    }

    void onButtonPress() {
        gotoManualMode();
    }

    void onButtonPressLong() {
        gotoAutoMode();
    }
   
    void tick() {
        if (isRunning()) {

        } 
     
    }

  private:
    boolean isRunning() {
        uint32_t howLongAfterDark = nightController->howLong();
        return howLongAfterDark >= (config->secondAfterDark) && isAutoMode;
    }

    void gotoManualMode() {
        executorsLogic->next();
        isAutoMode = false;
    }

    void gotoAutoMode() {
        executorsLogic->stop();
        isAutoMode = true;
    }

    boolean isAutoMode = false;
    MainConfiguration* config;
    ExecutorsLogic* executorsLogic;
    NightController* nightController;
    RainController* rainController;
};



#endif // TIMER_LOGIC_H_
