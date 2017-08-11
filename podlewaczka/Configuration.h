#ifndef CONFIG_H_   /* Include guard */
#define CONFIG_H_

class IConfiguration {
    virtual void serialize(uint8_t* data)=0; 
    virtual void deserialize(uint8_t* data)=0;
};

class Configuration : public IConfiguration {

    public:
    boolean isRunWith() { return runWith;}
    void load(boolean _runWitch, boolean _enabled, uint8_t _fill) {
        setRunWith(_runWitch);
        setEnabled(_enabled);
        setFill(_fill);
    }
    void setRunWith(boolean b) { this->runWith = b;}
    void setEnabled(boolean b) {this->enabled = b;}
    boolean isEnabled() {return enabled;}
    void setFill(uint8_t f) {this->fill = f;}
    uint8_t getFill() {return fill;}
    void setPin(uint8_t p) {pin = p;}
    uint8_t getPin() {return pin;}

    virtual void serialize(uint8_t* data) {}
    virtual void deserialize(uint8_t* data) {}

    private:
    uint8_t pin;
    boolean enabled;
    uint8_t fill; //in % 0 - 100
    boolean runWith = false;
};

class MainConfiguration : public IConfiguration {
    public:
    virtual void serialize(uint8_t* data) {}
    virtual void deserialize(uint8_t* data) {}

    uint32_t secondAfterDark = 3*60*60;

    //After how many seconds we forget that it was raining
    // 12h = 432000
    uint32_t rainForget =432000;
    //jak dlugo musi padac, zeby trac to po uwage
    //How long does it take to lose to lose it?
    // 2h = 3600 raun + drying
    uint32_t rainTreshold = 7200;
};

#endif // CONFIG_H_
