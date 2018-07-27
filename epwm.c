/*
 * EPwm_Init.c
 *
 *  Created on: Jul 21, 2018
 *      Author: ragashe
 */
#include <epwm.h>
#include "DSP28x_Project.h"
#include "variables.h"

void InitEPwm1()
{
    // TBPRD = 2* (SYSCLOCKOUT/(freq in Hz))
    float epwm1_duty = 0.5;
    Uint16 epwm1_time_period = 2*(SYSCLOCKOUT/EPWM1_FREQ);
    EPwm1Regs.TBPRD = epwm1_time_period;            // Set timer period
    EPwm1Regs.TBPHS.half.TBPHS = 0;                 // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                       // Clear counter
    EPwm1Regs.CMPA.half.CMPA = epwm1_time_period*epwm1_duty;

    // Setup TBCLK
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.PRDLD = 0;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;


    // Set actions
    EPwm1Regs.AQCTLA.bit.CAU = 1;               // 1 is clear
    EPwm1Regs.AQCTLA.bit.CAD = 2;               // 2 is set
    EPwm1Regs.AQCTLB.bit.CAU = 2;               // 2 is set
    EPwm1Regs.AQCTLB.bit.CAD = 1;               // 1 is clear

    // ADC
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;             //Enable EPWMxSOCA
    EPwm1Regs.ETSEL.bit.SOCBEN = 0;             //Disable EPWMxSOCB Complimentary signals desired
    EPwm1Regs.ETSEL.bit.SOCASEL = 1;            // Generate SOCA pulse for zero base counter value
    EPwm1Regs.ETPS.bit.SOCACNT = 1;
    EPwm1Regs.ETPS.bit.SOCAPRD=1;               //ePWM SOCA conversion for the very 1st event in SOCACNT

    EPwm1Regs.ETSEL.bit.INTSEL = 1;             // Select INT on zero
    EPwm1Regs.ETSEL.bit.INTEN = 1;              // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = 1;              // Generate INT on 1st event
}

void InitEPwm2()
{
    float epwm2_duty = 0.5;
    Uint16 epwm2_time_period = 2*(SYSCLOCKOUT/EPWM2_FREQ);
    EPwm2Regs.TBPRD = epwm2_time_period;        // Set timer period
    EPwm2Regs.TBPHS.half.TBPHS = 0;             // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                   // Clear counter
    EPwm2Regs.CMPA.half.CMPA = epwm2_time_period*epwm2_duty;

    // Setup TBCLK
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm2Regs.TBCTL.bit.PRDLD = 0;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set actions
    EPwm2Regs.AQCTLA.bit.CAU = 1;               // 1 is clear
    EPwm2Regs.AQCTLA.bit.CAD = 2;               // 2 is set
    EPwm2Regs.AQCTLB.bit.CAU = 2;               // 2 is set
    EPwm2Regs.AQCTLB.bit.CAD = 1;               // 1 is clear
}

void InitEPwm3()
{
    float epwm3_duty = 0.4;
    Uint16 epwm3_time_period = 2*(SYSCLOCKOUT/EPWM3_FREQ);
    EPwm3Regs.TBPRD = epwm3_time_period;           // Set timer period
    EPwm3Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
    EPwm3Regs.TBCTR = 0x0000;                     // Clear counter
    EPwm3Regs.CMPA.half.CMPA = epwm3_time_period*epwm3_duty;

    // Setup TBCLK
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm3Regs.TBCTL.bit.PRDLD = 0;
//    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set actions
    EPwm3Regs.AQCTLA.bit.CAU = 1;               // 1 is clear
    EPwm3Regs.AQCTLA.bit.CAD = 2;               // 2 is set
    EPwm3Regs.AQCTLB.bit.CAU = 2;               // 2 is set
    EPwm3Regs.AQCTLB.bit.CAD = 1;               // 1 is clear
}
void InitEPwm4()
{
    float epwm4_duty = 0.5;
    Uint16 epwm4_time_period = 2*(SYSCLOCKOUT/EPWM4_FREQ);
    EPwm4Regs.TBPRD = epwm4_time_period;        // Set timer period
    EPwm4Regs.TBPHS.half.TBPHS = 0;             // Phase is 0
    EPwm4Regs.TBCTR = 0x0000;                   // Clear counter
    EPwm4Regs.CMPA.half.CMPA = epwm4_time_period*epwm4_duty;

    // Setup TBCLK
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm4Regs.TBCTL.bit.PRDLD = 0;
//    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set actions
    EPwm4Regs.AQCTLA.bit.CAU = 1;               // 1 is clear
    EPwm4Regs.AQCTLA.bit.CAD = 2;               // 2 is set
    EPwm4Regs.AQCTLB.bit.CAU = 2;               // 2 is set
    EPwm4Regs.AQCTLB.bit.CAD = 1;               // 1 is clear
}
void InitEPwm5()
{
    float epwm5_duty = 0.5;
    Uint16 epwm5_time_period = 2*(SYSCLOCKOUT/EPWM5_FREQ);
    EPwm5Regs.TBPRD = epwm5_time_period;        // Set timer period
    EPwm5Regs.TBPHS.half.TBPHS = 0;             // Phase is 0
    EPwm5Regs.TBCTR = 0x0000;                   // Clear counter
    EPwm5Regs.CMPA.half.CMPA = epwm5_time_period*epwm5_duty;

    // Setup TBCLK
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Disable phase loading
    EPwm5Regs.TBCTL.bit.PRDLD = 0;
//    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set actions
    EPwm5Regs.AQCTLA.bit.CAU = 2;               // 1 is clear
    EPwm5Regs.AQCTLA.bit.CAD = 1;               // 2 is set
    EPwm5Regs.AQCTLB.bit.CAU = 1;               // 2 is set
    EPwm5Regs.AQCTLB.bit.CAD = 2;               // 1 is clear
}



