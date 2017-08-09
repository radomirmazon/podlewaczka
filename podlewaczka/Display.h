#ifndef DISPLAY_H_   /* Include guard */
#define DISPLAY_H_

/**
 In this case - display mean 8 LEDs connect to 8 arduino ports.
 You can implement any display with IDisplay interface
 **/

class IDisplay {
    public:
    virtual void preLongButtonPress()=0;
    virtual void preLong2ButtonPress()=0;
    virtual void showExecTimeLimit(uint8_t value)=0;
    virtual void showExecutor(uint8_t index, boolean state)=0;
    //etc...
};

class Display : public IDisplay {
    public:
    Display(uint8_t ch0, uint8_t ch1, uint8_t ch2, uint8_t ch3,
                uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7) {
        ledPinout[0] = ch0;
        ledPinout[1] = ch1;
        ledPinout[2] = ch2;
        ledPinout[3] = ch3;
        ledPinout[4] = ch4;
        ledPinout[5] = ch5;
        ledPinout[6] = ch6;
        ledPinout[7] = ch7;
        for (uint8_t i=0; i<8; i++) {
            pinMode(ledPinout[i], OUTPUT);
            digitalWrite(ledPinout[i] ,HIGH);
            delay(20);
            digitalWrite(ledPinout[i] ,LOW);
            intExecutorState[i] = false;
        }
        Serial.println("hello");
    }

    virtual void preLongButtonPress(){
        for (uint8_t i=0; i<8; i++) {
            digitalWrite(ledPinout[i] ,HIGH);
        }
           delay(100);
        for (uint8_t i=0; i<8; i++) {
            digitalWrite(ledPinout[i] ,LOW);
        }
    }
    
    virtual void preLong2ButtonPress(){
        preLongButtonPress();
        delay(100);
        preLongButtonPress();
    } 

    virtual void showExecTimeLimit(uint8_t value) {
      prShowing = true;
      prShowingCounter = 200;
      if (value > 8) return;
      for (uint8_t i=0; i<8; i++) {
          if (i<value+1) {
            digitalWrite(ledPinout[i] ,HIGH);
          } else {
            digitalWrite(ledPinout[i] ,LOW);
          }
      } 
    }

    virtual void showExecutor(uint8_t index, boolean state) {
      if (index <8) {
        intExecutorState[index] = state;
      }
    }

    void tick() {
      if (prShowing) {
        prShowingCounter--;
        if (prShowingCounter == 0) {
          prShowing = false;
        }
      } else {
        update();
      }
    }

    private:
    void update() {
      for (uint8_t i=0; i<8; i++) {
          if (intExecutorState[i]) {
             digitalWrite(ledPinout[i] ,HIGH);
          } else {
            digitalWrite(ledPinout[i] ,LOW);
          }
      }
    }
    uint8_t ledPinout[8];
    boolean intExecutorState[8];
    boolean prShowing = false;
    uint8_t prShowingCounter;
};

#endif // DISPLAY_H_
