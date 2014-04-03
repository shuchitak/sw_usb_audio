#ifndef CS4384_H_
#define CS4384_H_

//Address on I2C bus
#define CS4384_I2C_ADDR      0x18

//Register Addresess
#define CS4384_CHIP_REV      0x01
#define CS4384_MODE_CTRL     0x02
#define CS4384_PCM_CTRL      0x03
#define CS4384_DSD_CTRL      0x04
#define CS4384_FLT_CTRL      0x05
#define CS4384_INV_CTRL      0x06
#define CS4384_GRP_CTRL      0x07
#define CS4384_RMP_MUTE      0x08
#define CS4384_MUTE_CTRL     0x09
#define CS4384_MIX_PR1       0x0a
#define CS4384_VOL_A1        0x0b
#define CS4384_VOL_B1        0x0c
#define CS4384_MIX_PR2       0x0d
#define CS4384_VOL_A2        0x0e
#define CS4384_VOL_B2        0x0f
#define CS4384_MIX_PR3       0x10
#define CS4384_VOL_A3        0x11
#define CS4384_VOL_B3        0x12
#define CS4384_MIX_PR4       0x13
#define CS4384_VOL_A4        0x14
#define CS4384_VOL_B4        0x15
#define CS4384_CM_MODE       0x16

//Default values used in this application for PCM
#define CS4384_CHIP_REV_PCM  0x01 //CS4384Rev B0 of the chip
#define CS4384_MODE_CTRL_PCM 0xc1 //Control port enable, enable freeze, PCM mode, all DAC pairs enabled, powered down
#define CS4384_MODE_CTL2_PCM 0x80 //Control port enable, disable freeze, PCM mode, all DAC pairs enabled, no power down
#define CS4384_PCM_CTRL_PCM  0x13 //I2S format, auto speed mode detect (32KHz to 200KHz)
#define CS4384_FLT_CTRL_PCM  0x01 //Interpolation filter fast roll off
#define CS4384_INV_CTRL_PCM  0x00 //No inversion of signal polarity for all channels
#define CS4384_GRP_CTRL_PCM  0x40 //Single mute, disable vol controls, vol controls are indvidual
#define CS4384_RMP_MUTE_PCM  0xb0 //Soft ramp mute for mode changes, disable auto-mute, auto polarity detect
#define CS4384_UNMUTE_PCM    0x00 //Disable all mute for all channels
#define CS4384_ALLMUTE_PCM   0xff //Disable all mute for all channels
#define CS4384_MIX_PR1_PCM   0x09 //Disable depmhasis filter, aL, bR ATAPI mode
#define CS4384_VOL_A1_PCM    0x00 //0db volume control
#define CS4384_VOL_B2_PCM    0x00 //0db volume control
#define CS4384_MIX_PR2_PCM   0x09 //Disable depmhasis filter, aL, bR ATAPI mode
#define CS4384_VOL_A2_PCM    0x00 //0db volume control
#define CS4384_VOL_B2_PCM    0x00 //0db volume control
#define CS4384_MIX_PR3_PCM   0x09 //Disable depmhasis filter, aL, bR ATAPI mode
#define CS4384_VOL_A3_PCM    0x00 //0db volume control
#define CS4384_VOL_B3_PCM    0x00 //0db volume control
#define CS4384_MIX_PR4_PCM   0x09 //Disable depmhasis filter, aL, bR ATAPI mode
#define CS4384_VOL_A4_PCM    0x00 //0db volume control
#define CS4384_VOL_B4_PCM    0x00 //0db volume control
#define CS4384_PCM_MODE_PCM  0x00 //No prescaler on MCLK

//Default values used in this application for DSD
#define CS4384_MODE_CTRL_DSD 0xe1 //Control port enable, enable freeze, DSD mode, all DAC pairs enabled, powered down
#define CS4384_MODE_CTL2_DSD 0xA0 //Control port enable, disable freeze, DSD mode, all DAC pairs enabled, no power down
#define CS4384_DSD_CTL_DSD1x 0x48 //For DSD mode, 64x oversample with 8x MCLK (2.8M/22.5792). DSD vol/filter off, static mute on, invalid off, BCKA for phase mod, phase mod off
#define CS4384_DSD_CTL_DSD2x 0xc8 //For DSD mode, 128x oversample with 8x MCLK (2.8M/22.5792). DSD vol/filter off, static mute on, invalid off, BCKA for phase mod, phase mod off



#endif /* CS4384_H_ */