#ifndef NIGHT_H_   /* Include guard */
#define NIGHT_H_

#include "configConst.h"

#include "configuration.h"

class NightController {

    public:
    NightController(MainConfiguration* config) {
        pConfiguration = config;
        pinMode(LIGHT, INPUT);
    }

    boolean isNight() {
        return LIGHT_NIGHT > analogRead(LIGHT);
    }

    void tick() {
        counter++;
        boolean isn = isNight();
        if (wasNight != isn && isn) {
            counter = 0;
        }   
        wasNight = isn;
    }

    uint32_t howLong() {
        return counter;
    }

    private:
    MainConfiguration* pConfiguration;
    uint32_t counter = 0;
    boolean wasNight = false;

};


#endif // NIGHT_H_