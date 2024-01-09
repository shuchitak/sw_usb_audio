
#ifndef _USER_MAIN_H_
#define _USER_MAIN_H_


#ifdef __XC__

#include "app_dsp.h"

void AudioHwRemote(chanend c);

extern unsafe chanend uc_audiohw;
extern void dsp_main_wrapper(chanend c_control);

#define USER_MAIN_DECLARATIONS \
    chan c_audiohw; \
    chan c_control;

#define USER_MAIN_CORES on tile[1]: {\
                                        par\
                                        {\
                                            unsafe{\
                                                uc_audiohw = (chanend) c_audiohw;\
                                            }\
                                            app_dsp_main(c_control); \
                                        }\
                                    }\
\
                        on tile[0]: {\
                                        par\
                                        {\
                                            AudioHwRemote(c_audiohw);\
                                        }\
                                    }
#endif

#endif
