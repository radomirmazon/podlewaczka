#ifndef COMMANDL_H_   /* Include guard */
#define COMMANDL_H_

#include "ExecutorsLogic.h"

class CommandLogic {
  public:
  CommandLogic(ExecutorsLogic* executorLogic, TimerLogic* timerLogic, SoftwarePRInput* pr) {
    this->executorLogic = executorLogic;
    this->timerLogic = timerLogic;
    this->pr = pr;
  }
  
  void tick() {
    while (Serial.available()) {
      delay(2);  //delay to allow byte to arrive in input buffer
      char c = Serial.read();
      readString += c;
    }

    if (readString.length() >0) {
      
      executeCommand(readString);
      readString="";
    } 
  }

  private:
    void executeCommand(String input) {
        String param = input.substring(1);
        switch(input.charAt(0)) {
          case 'E':
            onOffCommand(param.toInt(), true);    
            break;
          case 'N':
            executorLogic->next();
            break;
          case 'A':
            timerLogic->gotoAutoMode();
            break;
          case 'M':
            timerLogic->gotoManualMode();
            break;
          case 'P':
            int p = param.toInt();
            if (p>=0 && p<8) {
              pr->setValue(p);
            }
        }
    }

    void onOffCommand(uint8_t param, boolean state) {
      if (param < 8) {
        executorLogic->onOff(param, state);  
      } else {
        executorLogic->stop();
      }
    }
    
    String readString;
    ExecutorsLogic* executorLogic;
    TimerLogic* timerLogic;
    SoftwarePRInput* pr;
};



#endif // COMMANDL_H_
