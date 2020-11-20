#include "gpitrigger.h"


uint32_t convert_value(float value, nBlocks_OutputType value_type) {
   switch (value_type) {
        case OUTPUT_TYPE_FLOAT:
            uint32_t result;
            memcpy(&(result), &(value), sizeof(value));
            return result;
        
        case OUTPUT_TYPE_INT:
            return (int)value;
    }
    return 0; // Failsafe catch-all
}


 

nBlock_GPITrigger::nBlock_GPITrigger(PinName pinIn, float value, nBlocks_OutputType value_type): _in(pinIn) {
    _value_float = value;
    outputType[0] = value_type;
    outputType[1] = value_type;
    outputType[2] = value_type;    
    output[0] = convert_value( (_in? value : 0.0), value_type);
    available[0] = 1; // We start by firing the initial state
    return;
}

void nBlock_GPITrigger::endFrame(void) {
    uint32_t _temp_value;
    
    // Rising edge
    if ((old_in == 0) && (_in != 0)) {
        available[0] = 1;
        available[1] = 1;
        available[2] = 0;
        _temp_value = convert_value( (_in? _value_float : 0.0), outputType[0]);
        
        output[0] = _temp_value;
        output[1] = _temp_value;
    }
    // Falling edge
    else if ((old_in == 1) && (_in == 0)) {
        available[0] = 1;
        available[1] = 0;
        available[2] = 1;
        _temp_value = convert_value( (_in? _value_float : 0.0), outputType[0]);

        output[0] = _temp_value;
        output[2] = _temp_value;
    }
    // No edge, no new data
    else {
        available[0] = 0;
        available[1] = 0;
        available[2] = 0;
    }
    old_in = _in;
    return;
}
