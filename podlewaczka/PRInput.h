#ifndef PRINPUT_CON_H_   /* Include guard */
#define PRINPUT_CON_H_

#include "configConst.h"

class PRValue {
    virtual uint8_t getPrValue()=0;
};

class PRInput : public PRValue {

  public:
    PRInput() {
        pinMode(PR, INPUT);
    }

    //tick can simply send-back message, like event... @see configConst.h
    uint8_t tick() {
        return readPR();
    }

    virtual uint8_t getPrValue() {
        return prValue;
    }

  private:
    uint8_t prValue;
    uint8_t lastPrValue;
   
    uint8_t readPR() {
        uint8_t result = NO_MESSAGE;
        prValue = map(analogRead(PR), 0, 1000, 0, 7);
        if (lastPrValue != prValue) {
            result = ONCHAGE_PR_VALUE;
        }
        lastPrValue = prValue;
        return result;
    }
};



#endif // INPUT_CON_H_