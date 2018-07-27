/*
 * variables.c
 *
 *  Created on: Jun 26, 2018
 *      Author: ragashe
 */
#include "DSP28x_Project.h"
#include "variables.h"

Uint16 AdcData[8] = {0., 0., 0., 0., 0., 0., 0., 0.};
float Vldc = 0.0f;
float Vhdc = 0.0f;
float Vbat = 0.0f;
float Iinv = 0.0f;
float Vldc_ref = 150.0f;
float Vhdc_ref = 250.0f;
float Iinv_ref = 0.0f;
float Vldc_err[2] = {0., 0.};
float Vhdc_err[2] = {0., 0.};
float Iinv_err[3] = {0., 0., 0.};
float Vldc_out[2] = {0., 0.};
float Vhdc_out[2] ={0., 0.};
float Iinv_out[3] ={0., 0., 0.};
volatile float Uout = 0.0f;
const float Kp_DAB = 0.00951f;
const float Ki_DAB = 0.245929f;
const float Kp_DRER = 20.000147f;
const float Ki_DRER = 114.0406f;
const float Kp_HBridge = 0.0111;
const float Kr_HBridge = 30.0f;
const float K_SOGI = 0.8f;
volatile float PWM_Duty_Q = 0.0f;
unsigned int phase_shift_Q = 180.0f; //180.0f
float PR_C1 = 0.0f;
float inv_PR_C1 = 0.0f;
float PR_C2 = 0.0f;
float PR_C3 = 0.0f;
float PR_C4 = 0.0f;
