#ifndef __NB_GPITRIGGER
#define __NB_GPITRIGGER

#include "mbed.h"
#include "nworkbench.h"

class nBlock_GPITrigger: public nBlockSimpleNode<3> {
public:
    nBlock_GPITrigger(PinName pinIn, float value, nBlocks_OutputType value_type);
    void endFrame(void);
private:
    DigitalIn _in;
    uint32_t old_in;
    float _value_float;
};


#endif
