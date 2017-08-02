#ifndef EXEC_H_   /* Include guard */
#define EXEC_H_

#include "Configuration.h"

class Executor {

    public:
    Executor(Configuration* pConfig) {this->pConfig = pConfig;}
    Configuration* getConfig() {
        
        return pConfig;
    }

    void update() {

    }


    private:
    Configuration* pConfig;
};

#endif // EXEC_H_