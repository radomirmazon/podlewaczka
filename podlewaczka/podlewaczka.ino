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
#include "ExecutorsLogic.h"
#include "TimerLogic.h"


//// core objects:
ExecutorsLogic* pExecutorsLogic;
MainConfiguration mainConfig;
PRInput pr;
ButtonInput button;
Display* pDisplay;
RainController* pRainController;
NightController* pNightController;
TimerLogic* pTimerLogic;

void setup() {
  Serial.begin(9600);  //Begin serial communcation

  pDisplay = new Display(17, 11, 18, 12, 19, 16, 15, 13);
  pRainController = new RainController(&mainConfig);
  pNightController = new NightController(&mainConfig);

  pExecutorsLogic = new ExecutorsLogic(&mainConfig, &pr);
  pExecutorsLogic->loadConfiguration();

  pTimerLogic = new TimerLogic(&mainConfig, pExecutorsLogic, pNightController, pRainController);
}

void oneSecondTick() {
  pRainController->tick();
  pNightController->tick();
  pExecutorsLogic->tick();
  pTimerLogic->tick();
}

void fastTick() {
  switch(button.tick()) 
  {
    case BUTTON_PRESS:
      pTimerLogic->onButtonPress();
    break;
    case BUTTON_PRESS_PRE_LONG:
      //todo: blink twice -> display.showPressPreLong();
    break;
    case BUTTON_PRESS_LONG:
      pTimerLogic->onButtonPressLong();
    break;
    case BUTTON_PRESS_PRE_LONG2:
      //
    break;
    case BUTTON_PRESS_LONG2:
      // 
    break;
  }

  switch(pr.tick()) 
  {
    case ONCHAGE_PR_VALUE:
    //todo: always show value on display
    break;
  }

  //refresh display
  pDisplay->tick();
}

////////////////////////////////////////////////////////////////////////////////////////////
unsigned long time = 0;
unsigned long lastTime = 0; 
void loop() {
  time = millis();
  if (time - lastTime > 1000) {
    oneSecondTick();
    lastTime = time;
  }
  if ((time - lastTime) % 50 == 0 ) {
    fastTick();
  }
}