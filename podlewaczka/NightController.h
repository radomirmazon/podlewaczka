#ifndef NIGHT_H_   /* Include guard */
#define NIGHT_H_

#include "configConst.h"

#include "configuration.h"

class NightController {

    public:
    NightController(MainConfiguration* config) {
        pConfiguration = config;
        counter = 0;
        pinMode(LIGHT, INPUT);
    }

    void tick() {
        counter++;
    }

    boolean isNight() {
        return LIGHT_NIGHT > analogRead(LIGHT);
    }

    uint32_t howLong() {
        if (!isNight()) {
            counter = 0;
        }
        return counter;
    }

    private:
    MainConfiguration* pConfiguration;
    uint32_t counter;

};


#endif // NIGHT_H_