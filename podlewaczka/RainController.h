#ifndef RAIN_H_   /* Include guard */
#define RAIN_H_

#include "configConst.h"

#include "configuration.h"

class RainController {

    public:
    RainController(MainConfiguration* config) {
        pConfig = config;
        pinMode(RAIN, INPUT);
    }

    void tick() {
        if (isRain()) {
            //jeśli padało i ostatni deszcz był poniżej TR to reset
            if (afterRainCounter > 0) {
            afterRainCounter = 0;
            }
        rainCounter++;
        } else {
            if (afterRainCounter == 0 && rainCounter < pConfig->rainTreshold) {
            rainCounter = 0;
            afterRainCounter = 0;
            }
            if (rainCounter >0) {
            afterRainCounter ++;
            }
        }

        if (afterRainCounter > pConfig->rainForget) {
            afterRainCounter=0;
            rainCounter=0;
        }

        canRun = afterRainCounter == 0  && rainCounter == 0;
    }

    boolean isCanRun() {
        return canRun;
    }

    private:
    MainConfiguration* pConfig;
    uint32_t rainCounter = 0;
    uint32_t afterRainCounter = 0;
    boolean canRun = true;

    boolean isRain() {
        boolean result = analogRead(RAIN) < 500;
        return result;
    }

};


#endif // RAIN_H_