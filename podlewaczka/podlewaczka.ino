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
#include "CommandLogic.h"


//// core objects:
ExecutorsLogic* pExecutorsLogic;
MainConfiguration mainConfig;
SoftwarePRInput pr;
ButtonInput button;
Display* pDisplay;
RainController* pRainController;
NightController* pNightController;
TimerLogic* pTimerLogic;
ExtraButtonDecoder buttonDecoder;
CommandLogic* pCommandLogic;

void setup() {
  Serial.begin(9600);  //Begin serial communcation

  pDisplay = new Display(17, 11, 18, 12, 19, 16, 15, 13);
  pRainController = new RainController(&mainConfig);
  pNightController = new NightController(&mainConfig);

  pExecutorsLogic = new ExecutorsLogic(&mainConfig, &pr, pDisplay);
  pExecutorsLogic->loadConfiguration();

  pTimerLogic = new TimerLogic(&mainConfig, pExecutorsLogic, pNightController, pRainController);
  pCommandLogic = new CommandLogic(pExecutorsLogic, pTimerLogic);
}

void oneSecondTick() {
  pRainController->tick();
  pNightController->tick();
  pExecutorsLogic->tick();
  pTimerLogic->tick();
  pDisplay->showManual(pTimerLogic->isManual());
  pDisplay->oneSecondTick();
}

void fastTick() {
  switch(buttonDecoder.decode(button.tick())) 
  {
    case BUTTON_PRESS:
      pTimerLogic->onButtonPress();
      //pExecutorsLogic->next();
      break;
    case BUTTON_PRESS_PRE_LONG:
    case BUTTON_EXTRA_PRE_LONG_PRESS:
      pDisplay->preLongButtonPress();
      break;
    case BUTTON_PRESS_LONG:
    case BUTTON_EXTRA_LONG_PRESS:
      pTimerLogic->onButtonPressLong();
      break;
    case BUTTON_PRESS_PRE_LONG2:
      pDisplay->preLong2ButtonPress();
      break;
    case BUTTON_EXTRA_PRESS:
      pr.next();
      break;
    case BUTTON_PRESS_LONG2:
      pDisplay->showExecTimeLimit(pr.getValue()); 
      break;
  }

  switch(pr.tick()) 
  {
    case ONCHAGE_PR_VALUE:
      pDisplay->showExecTimeLimit(pr.getValue()); 
    break;
  }

  pDisplay->tick();
  buttonDecoder.tick();
  pExecutorsLogic->update();
  pCommandLogic->tick();
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
