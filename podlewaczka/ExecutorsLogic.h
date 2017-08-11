#ifndef EXECL_H_   /* Include guard */
#define EXECL_H_

#include "Configuration.h"
#include "Executor.h"

class ExecutorsLogic {

    public:
    ExecutorsLogic(MainConfiguration* config, PRValue* pr, IDisplay* display) {
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
            executors[i] = new Executor(&(executorConfig[i]), pr, display, i);
        }
    }

    void loadConfiguration() {
      //TODO: move to EEPROM...
        //boolean runWitch, boolean enabled, uint8_t fill
        executorConfig[0].load(RUN_INDEPENDENTLY, true, 80);
        executorConfig[1].load(RUN_WITCH, true, 80);
        executorConfig[2].load(RUN_INDEPENDENTLY, true, 80);
        executorConfig[3].load(RUN_INDEPENDENTLY, true, 100);
        executorConfig[4].load(RUN_INDEPENDENTLY, true, 100);
        executorConfig[5].load(RUN_INDEPENDENTLY, true, 100);
        executorConfig[6].load(RUN_INDEPENDENTLY, false, 100);
        executorConfig[7].load(RUN_INDEPENDENTLY, false, 100);
        setNumberOfCycle(2);
    }

    //one second internal propose ticker....
    void tick() {
        for (uint8_t i=0; i<8; i++) {
            executors[i]->tick();
        }
    }

    void start() {
        stop();
        runFirst();
        update();
    }

    void stop() {
        for (uint8_t i=0; i<8; i++) {
            executors[i]->off();
        }
        isRunning = false;
        runningIndex = 0;
    }

    void next() {
        if (isRunning) {
            for (uint8_t i=0; i<8; i++) {
                executors[i]->off();
            }
            update();
        }  else {
            start();
        }
    }

    void update() {
      if (isRunning) {
        if (runningIndex < 8) {
          
          uint8_t nextIndex = runningIndex+1;
          if (nextIndex >= 8) {
            nextIndex = 7;
          }
          
          if (!executors[runningIndex]->isOn() || executors[nextIndex]->isRunWith()) {
            if (runningIndex <7) {
              executors[runningIndex+1]->on();
            }
            runningIndex++;
          }
        } else {
          cycle++;
          if (cycle >= cycleLimit || isManualMode) {
            stop();
          } else {
            uint8_t temp = cycle;
            start();
            cycle = temp;
          }
        }
      }
    }

    void setManualMode(boolean b) {
      this->isManualMode = b;
    }

    void onOff(uint8_t index, boolean state) {
      if (index <8) {
        executors[index]->on();
      }
    }

    //{cycle},{mode},
    void print() {
      for (uint8_t i=0; i<8; i++) {
        Serial.print('E');
        executors[i]->print();
        Serial.print(';');
      }
      Serial.print('|');
      Serial.print(cycle);
      Serial.print(',');
      if (isManualMode) {
        Serial.print('M');
      } else {
        Serial.print('A');
      }
      Serial.print('|');
    }
    
    private:
    void runFirst() {
        isRunning = true;
        runningIndex = 0;
        cycle = 0;
        executors[0]->on();
    }
   
    void fireRunWith(uint8_t index) {
        if (index <7) {
            for (uint8_t i=index+1; i<8; i++) {
                if (executors[i]->isRunWith()) {
                    executors[i]->on();
                } else {
                    break;
                }
            }
        }
    }

    void setNumberOfCycle(uint8_t cycle) {
        this->cycleLimit = cycle;
    }

    Executor* executors[8];
    Configuration executorConfig[8];
    MainConfiguration* config;
    boolean isRunning = false;
    boolean isManualMode;
    uint8_t runningIndex = 0;
    uint8_t cycleLimit = 2;
    uint8_t cycle = 0;
    
};

#endif // EXECL_H_
