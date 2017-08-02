#ifndef INPUT_CON_H_   /* Include guard */
#define INPUT_CON_H_

#include "configConst.h"

#define LONG_COUNTE 400

class ButtonController {

  public:
    ButtonController() {
        pinMode(BUTTON, INPUT_PULLUP);
        pinMode(PR, INPUT);
        pinMode(RAIN, INPUT);
        pinMode(LIGHT, INPUT);
    }

    //tick can simply send-back message, like event... @see configConst.h
    uint8_t tick() {
        uint8_t result = readPR();
        if (result != NO_MESSAGE) {
            result = readSwitch();
        } 
        return result;
    }

    uint8_t getPrValue() {
        return prValue;
    }

  private:
    uint8_t prValue;
    uint8_t lastPrValue;
    uint16_t buttonCounter = 0;
   
    uint8_t readPR() {
        uint8_t result = NO_MESSAGE;
        prValue = map(analogRead(PR), 0, 1000, 0, 7);
        if (lastPrValue != prValue) {
            result = ONCHAGE_PR_VALUE;
        }
        lastPrValue = prValue;
        return result;
    }

    uint8_t readSwitch() {
        uint8_t result = NO_MESSAGE;
        if (digitalRead(BUTTON) == 0) {
        if (buttonCounter == LONG_COUNTE) {
            //buttonPreLongClink();
            result = BUTTON_PRESS_PRE_LONG;
        }
        buttonCounter++;
        } else {
        if (buttonCounter > 10 && buttonCounter < LONG_COUNTE) {
            //buttonClick();
            result = BUTTON_PRESS;
        } 
        if (buttonCounter >= LONG_COUNTE) {
            //buttonLongClick();
             result = BUTTON_PRESS_LONG;
        }
        buttonCounter = 0;
        }

        return result;
    }
};



#endif // INPUT_CON_H_