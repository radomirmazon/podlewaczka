/*
 * 1 - jz
 * 2 - ziel
 * 3 - jpom
 * 4 - pom
 * 5 - jbro
 * 6 - bro
 * 7 - nie
 * 8 - jnie
 */
//void loadConfiguration();

#include "configConst.h"
#include "Configuration.h"
#include "Executor.h"
#include "NightController.h"
#include "RainController.h"
#include "ButtonController.h"
#include "Display.h"

//// core objects:
MainConfiguration mainConfig;

Configuration config_0;
Configuration config_1;
Configuration config_2;
Configuration config_3;
Configuration config_4;
Configuration config_5;
Configuration config_6;
Configuration config_7;

Executor* executor_0 = new Executor(&config_0);
Executor* executor_1 = new Executor(&config_1);
Executor* executor_2 = new Executor(&config_2);
Executor* executor_3 = new Executor(&config_3);
Executor* executor_4 = new Executor(&config_4);
Executor* executor_5 = new Executor(&config_5);
Executor* executor_6 = new Executor(&config_6);
Executor* executor_7 = new Executor(&config_7);

Executor* executors[8];

uint16_t execLimits[8];

ButtonController buttonController;

Display display;
RainController* pRainController = new RainController(&mainConfig);
NightController* pNightController = new NightController(&mainConfig);

void setup() {
  Serial.begin(9600);  //Begin serial communcation
  executors[0] = executor_0;
  executors[1] = executor_1;
  executors[2] = executor_2;
  executors[3] = executor_3;
  executors[4] = executor_4;
  executors[5] = executor_5;
  executors[6] = executor_6;
  executors[7] = executor_7;
  //pitout
  config_0.setPin(2);
  config_1.setPin(3);
  config_2.setPin(4);
  config_3.setPin(5);
  config_4.setPin(6);
  config_5.setPin(7);
  config_6.setPin(8);
  config_7.setPin(9);

  //tablica limitow
  execLimits[0] = 5*60;
  execLimits[1] = 10*60;
  execLimits[2] = 15*60;
  execLimits[3] = 20*60;
  execLimits[4] = 25*60;
  execLimits[5] = 30*60;
  execLimits[6] = 35*60;
  execLimits[7] = 40*60;

  loadConfiguration();
}

void oneSecondTick() {
    //uint_t runWitch, boolean enabled, uint8_t fill, boolean simulateLP
  pRainController->tick();
  pNightController->tick();
}

void fastTick() {
  switch(buttonController.tick()) {
    case BUTTON_PRESS:
    //todo:
    break;
    case BUTTON_PRESS_LONG:
    //todo:
    break;
    case ONCHAGE_PR_VALUE:
    //todo:
    break;
  }

  display.tick();
}

void loadConfiguration() {
  config_0.load(10, true, 80, false);
  config_1.load(10, true, 80, false);
  config_2.load( 1, true, 80, false);
  config_3.load(10, true, 100, false);
  config_4.load(10, true, 100, false);
  config_5.load(10, false, 100, false);
  config_6.load(10, false, 100, false);
  config_7.load(10, false, 100, false);
}

////////////////////////////////////////////////////////////////////////////////////////////
unsigned long time = 0;
unsigned long lastTime = 0; 
void loop() {
  time = millis();
  if (time - lastTime > 1000) {
    oneSecondTick();
  }
  if ((time - lastTime) % 50 == 0 ) {
    fastTick();
  }
}