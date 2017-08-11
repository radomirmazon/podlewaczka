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
        if (!isAutoMode) {
            return;
        }

        if (isRunning() && rainController->isCanRun()) {
          executorsLogic->start();
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

    //{rain},{rainDecision},{timeAfterNight},{secondAfterDark},{rainForget},{rainTreshold};
    void print() {
      char buff[8];
      if (rainController->isRain()) {
        Serial.print("R,");  
      } else {
        Serial.print("-,");
      }
      Serial.print(rainController->isCanRun());
      Serial.print(',');
      sprintf(buff, "%05u,", rainController->getRainCounter());
      Serial.print(buff);
      sprintf(buff, "%05u|", rainController->getAfterRain());
      Serial.print(buff);
      if (nightController->isNight()) {
        Serial.print("N,");
      } else {
        Serial.print("D,");
      }
      sprintf(buff, "%05u,", nightController->howLong());
      Serial.print(buff);
      sprintf(buff, "%05u|", config->secondAfterDark);
      Serial.print(buff);
      sprintf(buff, "%05u,", config->rainForget);
      Serial.print(buff);
      sprintf(buff, "%05u", config->rainTreshold);
      Serial.print(buff);
    }
    
  private:    
    boolean isRunning() {
      uint32_t howLongAfterDark = nightController->howLong();
      return howLongAfterDark == (config->secondAfterDark) && isAutoMode;
    }

    boolean isAutoMode = false;
    MainConfiguration* config;
    ExecutorsLogic* executorsLogic;
    NightController* nightController;
    RainController* rainController;
};



#endif // TIMER_LOGIC_H_
