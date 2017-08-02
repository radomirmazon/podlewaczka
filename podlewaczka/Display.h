#ifndef DISPLAY_H_   /* Include guard */
#define DISPLAY_H_

/**
 In this case - display mean 8 LEDs connect to 8 arduino ports.
 You can implement any display with IDisplay interface
 **/

class IDisplay {
    public:
    virtual void init()=0;
    virtual void preLongButtonPress()=0;
    virtual void preLong2ButtonPress()=0;
    virtual void showExecTimeLimit(uint8_t value)=0;
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
            digitalWrite(ledPinout[i] ,LOW);
        }
    }

    virtual void init(){}
    virtual void preLongButtonPress(){}
    virtual void preLong2ButtonPress(){}
    virtual void showExecTimeLimit(uint8_t value){}

    void tick() {

    }

    private:
    uint8_t ledPinout[8];
};

#endif // DISPLAY_H_