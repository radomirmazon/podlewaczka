#ifndef EXEC_H_   /* Include guard */
#define EXEC_H_

#include "Configuration.h"

class Executor {

    public:
    Executor(Configuration* pConfig) {
        this->pConfig = pConfig;
        pinMode(pConfig->getPin(), OUTPUT);
    }

    Configuration* getConfig() {
        return pConfig;
    }

    boolean isEnabled() {
        return pConfig->isEnabled();
    }


    private:
    Configuration* pConfig;
};

#endif // EXEC_H_