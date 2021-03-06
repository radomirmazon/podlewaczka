#ifndef RAIN_H_   /* Include guard */
#define RAIN_H_

#include "configConst.h"

#include "Configuration.h"

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

    boolean isRain() {
        boolean result = analogRead(RAIN) < 500;
        return result;
    }

    uint32_t getAfterRain() {
      return afterRainCounter;
    }

    uint32_t getRainCounter() {
      return rainCounter;
    }
    private:
    MainConfiguration* pConfig;
    uint32_t rainCounter = 0;
    uint32_t afterRainCounter = 0;
    boolean canRun = true;

};


#endif // RAIN_H_
