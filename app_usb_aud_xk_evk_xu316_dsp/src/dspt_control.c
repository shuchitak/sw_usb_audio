#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xassert.h>
#include "debug_print.h"
#include <xcore/channel.h>
#include <xcore/chanend.h>
#include <xcore/select.h>
#include "dspt_control.h"
#include "dspt_module.h"

typedef struct {
    uint32_t cmd_id; // CmdID
    uint32_t offset;    // offset
    uint32_t size;      //size
}module_config_offsets_t;
#include "cmd_offsets.h"    // Autogenerated

#define APP_CONTROL_CMD_CONFIG 0x00
#define APP_CONTROL_CMD_CONFIG_OFFSET 0x01

static module_instance_t* get_module_control_instance(module_instance_t **modules, uint32_t res_id, size_t num_modules)
{
    //printf("res id = %d\n", res_id);
    for(int i=0; i<num_modules; i++)
    {
        if(modules[i]->control.id == res_id)
        {
            return modules[i];
        }
    }
    printf("ERROR: Cannot find a module for the instance-id %lu\n", res_id);
    xassert(0);
    return NULL;
}

static void get_control_cmd_config_offset(module_instance_t *module, uint8_t cmd_id, uint32_t *offset, uint32_t *size)
{
    //printf("cmd id = %d\n", cmd_id);
    all_dsp_modules_t module_type = module->control.module_type;
    module_config_offsets_t *config_offsets = ptr_module_offsets[module_type];

    for(int i=0; i<module->control.num_control_commands; i++)
    {
        if(cmd_id == (uint8_t)config_offsets[i].cmd_id)
        {
            *offset = config_offsets[i].offset;
            *size = config_offsets[i].size;
            return;
        }
    }
    printf("ERROR: cmd_id %d not found in module_type %d\n", cmd_id, module_type);
    xassert(0);
    return;
}


#define MAX_CONTROL_PAYLOAD_LEN 64
void dsp_control_thread(chanend_t c_control, module_instance_t** modules, size_t num_modules)
{
    int8_t payload[MAX_CONTROL_PAYLOAD_LEN] = {0};
    uint8_t temp = chan_in_byte(c_control);
    printf("dsp_control_thread received init token %d\n", temp);

    SELECT_RES(
        CASE_THEN(c_control, event_do_control)
    )
    {
        event_do_control: {
            control_req_t req;
            chan_in_buf_byte(c_control, (uint8_t*)&req, sizeof(control_req_t));
            if(req.cmd_id & 0x80) // Read command
            {
                //printf("Read command\n");
                module_instance_t *module = get_module_control_instance(modules, req.res_id, num_modules);
                // From the cmd_id, get the offset and size into the config struct
                uint32_t offset, size;
                get_control_cmd_config_offset(module, (req.cmd_id & 0x7f), &offset, &size);
                if(size != req.payload_len - 1) // 1 extra payload byte to return status in
                {
                    printf("ERROR: payload_len mismatch. Expected %lu, but received %u\n", size, req.payload_len);
                    xassert(0);
                }
                payload[0] = 0; // status
                memcpy((uint8_t*)&payload[1], (uint8_t*)module->control.config + offset, size);
                chan_out_buf_byte(c_control, (uint8_t*)payload, req.payload_len);
            }
            else // write command
            {
                //printf("Write command. res_id %d\n", req.res_id);
                module_instance_t *module = get_module_control_instance(modules, req.res_id, num_modules);
                // From the cmd_id, get the offset and size into the config struct
                uint32_t offset, size;
                get_control_cmd_config_offset(module, req.cmd_id, &offset, &size);
                if(size != req.payload_len)
                {
                    printf("ERROR: payload_len mismatch. Expected %lu, but received %u\n", size, req.payload_len);
                    xassert(0);
                }
                if(module->control.config_rw_state == config_none_pending)
                {
                    // Receive write payload
                    chan_in_buf_byte(c_control, (uint8_t*)module->control.config + offset, req.payload_len);
                    module->control.cmd_id = req.cmd_id;
                    module->control.config_rw_state = config_write_pending;
                }
                else
                {
                    chan_in_buf_byte(c_control, (uint8_t*)payload, req.payload_len); // Copy write payload to temp buffer and discard
                    printf("ERROR: Previous write to the config not applied by the module!! Ignoring write command.");
                }
            }
        }
        continue;
    }
}
