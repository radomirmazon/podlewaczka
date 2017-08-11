#ifndef EXEC_H_   /* Include guard */
#define EXEC_H_

#include "Configuration.h"
#include "PRInput.h"
#include "Display.h"

/**
Responsibility:
Executor can on and off one of relay for some time. Time for "on" is set automaticaly. 
**/

class Executor {

    public:
    Executor(Configuration* pConfig, PRValue* prInput, IDisplay* display, uint8_t id) {
        this->pConfig = pConfig;
        this->prValue = prInput;
        this->display = display;
        this->id = id;
        pinMode(pConfig->getPin(), OUTPUT);
        off();
    }

    Configuration* getConfig() {
        return pConfig;
    }

    boolean isRunWith() {
        return pConfig->isRunWith();
    }

    boolean isOn() {
        return internalState;
    }

    void on() {
        if (pConfig->isEnabled()) {
            digitalWrite(pConfig->getPin(), HIGH);
            internalState = true;
            counterDown = getExecLimit();
            showStatus();
        } else {
            off();
        }
    }

    void off() {
         digitalWrite(pConfig->getPin(), LOW);
         internalState = false;
         showStatus();
    }

    void tick() {
        if (isOn()) {
            if (counterDown == 0) {
                off();
                return;
            } else { 
                counterDown--;
            }
        }
    }

    //{onoff},{fill},{en},{time},{runWith};
    void print() {
      char buf[6];
      Serial.print(id);
      Serial.print(internalState);
      Serial.print(',');
      sprintf(buf, "%03u,", pConfig->getFill());
      Serial.print(buf);
      if (pConfig->isEnabled()) {
        Serial.print('E');
      } else {
        Serial.print('D');
      }
      Serial.print(',');
      if (isOn()) {
        sprintf(buf, "%04u,", counterDown);
        Serial.print(buf);
      } else {
        Serial.print("0000,");
      }
      Serial.print(pConfig->isRunWith());
      
    }

    private:
      Configuration* pConfig;
      PRValue* prValue;
      boolean internalState;
      uint32_t counterDown;
      IDisplay* display;
      uint8_t id;
  
      void showStatus() {
        display->showExecutor(id, internalState); 
      }
    
    uint16_t getExecLimit() {
        uint8_t prval = prValue->getValue();
        if (prval < 8) {
            double sec = (prval+1) * 60 * EXECUTION_LIMITS_STEP_IN_MINUTES;
            double sec2 = sec * pConfig->getFill();
            return (uint16_t)(sec2/100);
        } 
        return 1;
    }
};

#endif // EXEC_H_
