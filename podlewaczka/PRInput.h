#ifndef PRINPUT_CON_H_   /* Include guard */
#define PRINPUT_CON_H_

#include "configConst.h"

class PRValue {
  public:
    virtual uint8_t getValue()=0;
};

class SoftwarePRInput : public PRValue {
    public:
        uint8_t tick() {
          uint8_t result = NO_MESSAGE;
          if (lastPrValue != prValue) {
           result = ONCHAGE_PR_VALUE;
          }
          lastPrValue = prValue;
          return result;
        }

        virtual uint8_t getValue() {
            return prValue;
        }   

        void next() {
            prValue++;
            if (prValue >= 8) {
                prValue = 0;
            }
        }

    private:
      //TODO: move to EEPROM...
        uint8_t prValue = 4; //default in the middle
        uint8_t lastPrValue = 4;
};


#endif // INPUT_CON_H_
