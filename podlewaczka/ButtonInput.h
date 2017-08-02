#ifndef BINPUT_CON_H_   /* Include guard */
#define BINPUT_CON_H_

#include "configConst.h"

#define LONG_COUNT 350
#define LONG2_COUNT 600

class ButtonInput {

  public:
    ButtonInput() {
        pinMode(BUTTON, INPUT_PULLUP);
    }

    //tick can simply send-back message, like event... @see configConst.h
    uint8_t tick() {
        return readSwitch();
    }

    private:
    uint16_t buttonCounter = 0;

    uint8_t readSwitch() {
        uint8_t result = NO_MESSAGE;
        if (digitalRead(BUTTON) == 0) {
            if (buttonCounter == LONG_COUNT) {
                result = BUTTON_PRESS_PRE_LONG;
            }
            if (buttonCounter == LONG2_COUNT) {
                result = BUTTON_PRESS_PRE_LONG2;
            }
            buttonCounter++;
        } else {
            if (buttonCounter > 10 && buttonCounter < LONG_COUNT) {
                result = BUTTON_PRESS;
            } 
            if (buttonCounter >= LONG_COUNT && buttonCounter < LONG2_COUNT) {
                 result = BUTTON_PRESS_LONG;
            }
            if (buttonCounter >= LONG2_COUNT) {
                result = BUTTON_PRESS_LONG2;
            }
            buttonCounter = 0;
        }

        return result;
    }
};



#endif // INPUT_CON_H_