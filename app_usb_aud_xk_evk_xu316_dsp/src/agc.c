#include <string.h>
#include <stdlib.h>
#include <xassert.h>
#include "debug_print.h"
#include "agc.h"
#include "xua_conf.h"
#include "cmds.h" // Autogenerated

// TODO duplicated defines!
#define DSP_INPUT_CHANNELS (NUM_USB_CHAN_OUT + NUM_USB_CHAN_IN)
#define DSP_OUTPUT_CHANNELS (DSP_INPUT_CHANNELS)

DSP_MODULE_INIT_ATTR
module_instance_t* agc_init(uint8_t id)
{
    module_instance_t *module_instance = malloc(sizeof(module_instance_t));

    agc_state_t *state = malloc(sizeof(agc_state_t)); // malloc_from_heap
    agc_config_t *config = malloc(sizeof(agc_config_t)); // malloc_from_heap

    memset(state, 0, sizeof(agc_state_t));

    state->config.gain = 1.0;
    memcpy(config, &state->config, sizeof(agc_config_t));

    module_instance->state = state;
    module_instance->process_sample = agc_process;

    // Control stuff
    module_instance->control.config = config;
    module_instance->control.id = id;
    module_instance->control.module_type = agc;
    module_instance->control.num_control_commands = NUM_CMDS_AGC;
    module_instance->control.config_rw_state = config_none_pending;
    return module_instance;
}

DSP_MODULE_PROCESS_ATTR
void agc_process(int32_t *input, int32_t *output, void *app_data_state, module_control_t *control)
{
    xassert(app_data_state != NULL);
    agc_state_t *state = app_data_state;
    xassert(control != NULL);
    agc_config_t *config = control->config;

    // 4 biquads over 4 samples take 290 reference timer cycles
    for(int i=0; i<DSP_OUTPUT_CHANNELS; i++)
    {
        output[i] = (int32_t)(input[i] * state->config.gain);
    }

    if(control->config_rw_state == config_write_pending)
    {
        // Finish the write by updating the working copy with the new config
        memcpy(&state->config, config, sizeof(agc_config_t));
        control->config_rw_state = config_none_pending;
    }
}

