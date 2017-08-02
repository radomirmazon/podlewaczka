/**
 Radomir Mazon (c) 2017
 Project: podlewaczka
 Elements: Arduino nano, fotoresistor, wate drops detector module, microswitch, 8x LEDs
 Others: 5V power supply, executice module (base on relays, or transistors)
 out of the box: wifi module, 
 todo: add temperature module, add humidity module
 long term todo: get data from weather serwice via external software on wifi module. 
 .
**/

#include "configConst.h"
#include "Configuration.h"
#include "Executor.h"
#include "Display.h"
#include "NightController.h"
#include "RainController.h"
#include "ButtonInput.h"
#include "PRInput.h"


//// core objects:
MainConfiguration mainConfig;
PRInput pr;

Configuration config_0;
Configuration config_1;
Configuration config_2;
Configuration config_3;
Configuration config_4;
Configuration config_5;
Configuration config_6;
Configuration config_7;

Executor* executor_0 = new Executor(&config_0, &pr);
Executor* executor_1 = new Executor(&config_1, &pr);
Executor* executor_2 = new Executor(&config_2, &pr);
Executor* executor_3 = new Executor(&config_3, &pr);
Executor* executor_4 = new Executor(&config_4, &pr);
Executor* executor_5 = new Executor(&config_5, &pr);
Executor* executor_6 = new Executor(&config_6, &pr);
Executor* executor_7 = new Executor(&config_7, &pr);

Executor* executors[8];

ButtonInput button;

Display* pDisplay = new Display(17, 11, 18, 12, 19, 16, 15, 13);
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

  loadConfiguration();
}

void oneSecondTick() {
  for (uint8_t i=0; i<8; i++) {
    executors[i]->tick();
  }
  pRainController->tick();
  pNightController->tick();
}

void fastTick() {
  switch(button.tick()) 
  {
    case BUTTON_PRESS:
    //todo:
    break;
    case BUTTON_PRESS_PRE_LONG:
    //todo:
    break;
    case BUTTON_PRESS_LONG:
    //todo:
    break;
    case BUTTON_PRESS_PRE_LONG2:
    //todo: blink twice -> display.showPressPreLong2();
    break;
    case BUTTON_PRESS_LONG2:
    //todo: blink onece -> display.showPressPreLong();
    break;
  }

  switch(pr.tick()) 
  {
    case ONCHAGE_PR_VALUE:
    //todo:
    break;
  }

  pDisplay->tick();
}

void loadConfiguration() {
   //uint8_t runWitch, boolean enabled, uint8_t fill, boolean simulateLP
  config_0.load(RUN_INDEPENDENTLY, true, 80, false);
  config_1.load(RUN_INDEPENDENTLY, true, 80, false);
  config_2.load(RUN_WITCH_CH1, true, 80, false);
  config_3.load(RUN_INDEPENDENTLY, true, 100, false);
  config_4.load(RUN_INDEPENDENTLY, true, 100, false);
  config_5.load(RUN_INDEPENDENTLY, false, 100, false);
  config_6.load(RUN_INDEPENDENTLY, false, 100, false);
  config_7.load(RUN_INDEPENDENTLY, false, 100, false);
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