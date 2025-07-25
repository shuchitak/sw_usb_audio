// Copyright 2025 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
xscope_host_data(c_xscope);
#if HID_CONTROLS > 0
on tile[XUD_TILE]: UserHIDPoll();
#endif

on tile[0]: {
                xscope_mode_lossy();
                board_setup();
                xk_audio_316_mc_ab_i2c_master(i2c);
            }


on tile[1]: {
                xscope_mode_lossy();
                unsafe
                {
                    i_i2c_client = i2c[0];
                }
            }

