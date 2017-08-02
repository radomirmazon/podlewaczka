#ifndef EXEC_H_   /* Include guard */
#define EXEC_H_

#include "Configuration.h"
#include "PRInput.h"

class Executor {

    public:
    Executor(Configuration* pConfig, PRInput* prInput) {
        this->pConfig = pConfig;
        this->prInput = prInput;
        pinMode(pConfig->getPin(), OUTPUT);
        off();
        //limits execution time (in second)
        execLimits[0] = 5*60;
        execLimits[1] = 10*60;
        execLimits[2] = 15*60;
        execLimits[3] = 20*60;
        execLimits[4] = 25*60;
        execLimits[5] = 30*60;
        execLimits[6] = 35*60;
        execLimits[7] = 40*60;
    }

    Configuration* getConfig() {
        return pConfig;
    }

    boolean isEnabled() {
        return pConfig->isEnabled();
    }

    boolean isOn() {
        return internalState;
    }

    void on() {
        if (pConfig->isEnabled()) {
            digitalWrite(pConfig->getPin(), HIGH);
            internalState = true;
            counterDown = getExecLimit();
        } else {
            off();
        }
    }

    void off() {
         digitalWrite(pConfig->getPin(), LOW);
         internalState = false;
    }

    void tick() {
        if (counterDown == 0) {
            off();
            return;
        } 

        counterDown--;
    }


    private:
    Configuration* pConfig;
    PRInput* prInput;
    boolean internalState;
    uint32_t counterDown;
    uint16_t execLimits[8];

    uint16_t getExecLimit() {
        uint8_t prValue = prInput->getPrValue();
        if (prValue < 8) {
            double sec = execLimits[prValue];
            double sec2 = sec * pConfig->getFill();
            return (uint16_t)(sec2/100);
        } 
        return 1;
    }
};

#endif // EXEC_H_