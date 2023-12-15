#ifndef AGC_H
#define AGC_H

#include "dspt_module.h"
#include "agc_config.h" // Autogenerated


#define MAX_CHANNELS (4)
// Go in DSP module file

typedef struct
{
    agc_config_t config;
    int32_t current_gain;
}agc_state_t;

// Public functions
DSP_MODULE_INIT_ATTR module_instance_t* agc_init(uint8_t id);

DSP_MODULE_PROCESS_ATTR  void agc_process(int32_t *input, int32_t *output, void *app_data_state, void *app_data_config, bool config_dirty, uint8_t cmd);


#endif