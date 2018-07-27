/*
 * variables.h
 *
 *  Created on: Jun 26, 2018
 *      Author: ragashe
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

#define PI          3.141592653
#define SYSCLOCKOUT 37500000    //37.5MHz
#define EPWM1_FREQ  10000       //20kHz
#define EPWM2_FREQ  10000       //20kHz
#define EPWM3_FREQ  5000       //10kHz
#define EPWM4_FREQ  20000       //10kHz
#define EPWM5_FREQ  20000       //10kHz
#define ISR_FREQ    EPWM1_FREQ
#define FGRID       60.0f          //Hz
#define TS          (1.0/(ISR_FREQ))

extern Uint16 AdcData[8];
extern float Vldc;
extern float Vhdc;
extern float Vbat;
extern float Iinv;
extern float Vldc_ref;
extern float Vhdc_ref;
extern float Iinv_ref;
extern float Vldc_err[2], Vhdc_err[2], Iinv_err[3], Vldc_out[2], Vhdc_out[2], Iinv_out[3];
extern float PR_C1,inv_PR_C1, PR_C2,PR_C3,PR_C4;
extern float err_ldc, err_ldc_i;
extern float err_hdc, err_hdc_i;
extern volatile float Uout;
extern const float Kp_DAB;
extern const float Ki_DAB;
extern const float Kp_DRER;
extern const float Ki_DRER;
extern const float Kp_HBridge;
extern const float Kr_HBridge;
extern const float K_SOGI;
extern float Fs;
extern float Ts;
extern volatile float PWM_Duty_Q;
extern unsigned int phase_shift_Q;

#endif /* VARIABLES_H_ */
