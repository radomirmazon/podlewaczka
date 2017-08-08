#ifndef EXECL_H_   /* Include guard */
#define EXECL_H_

#include "Configuration.h"
#include "Executor.h"

class ExecutorsLogic {

    public:
    ExecutorsLogic(MainConfiguration* config, PRValue* pr) {
        this->config = config;
          //pitout
        executorConfig[0].setPin(RELAY_0);
        executorConfig[1].setPin(RELAY_1);
        executorConfig[2].setPin(RELAY_2);
        executorConfig[3].setPin(RELAY_3);
        executorConfig[4].setPin(RELAY_4);
        executorConfig[5].setPin(RELAY_5);
        executorConfig[6].setPin(RELAY_6);
        executorConfig[7].setPin(RELAY_7);
        for (uint8_t i=0 ;i<8; i++) {
            executors[i] = new Executor(&executorConfig[i], pr);
        }
    }

    void loadConfiguration() {
        //uint8_t runWitch, boolean enabled, uint8_t fill, boolean simulateLP
        executorConfig[0].load(RUN_INDEPENDENTLY, true, 80, false);
        executorConfig[1].load(RUN_INDEPENDENTLY, true, 80, false);
        executorConfig[2].load(RUN_WITCH_CH1, true, 80, false);
        executorConfig[3].load(RUN_INDEPENDENTLY, true, 100, false);
        executorConfig[4].load(RUN_INDEPENDENTLY, true, 100, false);
        executorConfig[5].load(RUN_INDEPENDENTLY, false, 100, false);
        executorConfig[6].load(RUN_INDEPENDENTLY, false, 100, false);
        executorConfig[7].load(RUN_INDEPENDENTLY, false, 100, false);
        setNumberOfCycle(2);
    }

    //one second internal propose ticker....
    void tick() {
        for (uint8_t i=0; i<8; i++) {
            executors[i]->tick();
        }

        if (!isRunning) {
            if (!executors[getExecutorIndex()]->isOn()) {
                executors[getExecutorIndex()]->on();
                if (!executors[runningIndex]->isOn()) {
                    next();
                }
            }

            //auto stop
            if (runningIndex >= runningIndexLimit) {
                stop();
            }
        }
    }

    void start() {
        stop();
        isRunning = true;
    }

    void stop() {
        for (uint8_t i=0; i<8; i++) {
            executors[i]->off();
        }
        isRunning = false;
        runningIndex = 0;
    }

    void next() {
        runningIndex++;
    }

    private:
    uint8_t getExecutorIndex() {
        return runningIndex%8;
    }

    void setNumberOfCycle(uint8_t cycle) {
        runningIndexLimit = 8*cycle;
    }

    Executor* executors[8];
    Configuration executorConfig[8];
    MainConfiguration* config;
    boolean isRunning = false;
    uint8_t runningIndex = 0;
    uint8_t runningIndexLimit = 8*2;
    
};

#endif // EXECL_H_