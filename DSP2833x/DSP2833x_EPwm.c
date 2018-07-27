// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:19 $
//###########################################################################
//
// FILE:   DSP2833x_EPwm.c
//
// TITLE:  DSP2833x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

// Configure the period for each timer
// 1 count = 6.67ns @ TBCLK = 150MHz
// TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV)
// Period = 15000 TBCLK counts = 100us @ TBCLK = 150MHz
#if 1
#define PWM1_TIMER_TBPRD   	 7500		// 0x1D4C
#define PWM2_TIMER_TBPRD   	 7500
#define PWM3_TIMER_TBPRD   	 7500
#define PWM4_TIMER_TBPRD   	 7500
#define PWM5_TIMER_TBPRD   	 7500
#define PWM6_TIMER_TBPRD   	 7500
#endif

#if 0
#define PWM1_TIMER_TBPRD   	 15000		// 0x1D4C
#define PWM2_TIMER_TBPRD   	 15000
#define PWM3_TIMER_TBPRD   	 15000
#define PWM4_TIMER_TBPRD   	 15000
#define PWM5_TIMER_TBPRD   	 15000
#define PWM6_TIMER_TBPRD   	 15000
#endif

#define HalfDuty	3750

// Maximum Dead Band values
// Dead Band = 150 TBCLK counts = 1us @ TBCLK = 150MHz
#define EPWM1_DB   285		// 0x01C2
#define EPWM2_DB   285
#define EPWM3_DB   285
#define EPWM4_DB   285
#define EPWM5_DB   285
#define EPWM6_DB   285

//---------------------------------------------------------------------------
// Example: InitEPwmGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 

void InitEPwmGpio(void)
{
   InitEPwm1Gpio();
   InitEPwm2Gpio();
   InitEPwm3Gpio();
#if DSP28_EPWM4
   InitEPwm4Gpio();
#endif // endif DSP28_EPWM4
#if DSP28_EPWM5
   InitEPwm5Gpio();
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
   InitEPwm6Gpio();
#endif // endif DSP28_EPWM6
}

void InitEPwm1Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)   
   
/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
   
    EDIS;
}

void InitEPwm2Gpio(void)
{
   EALLOW;
	
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)

/* Configure ePWM-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
   
    EDIS;
}

void InitEPwm3Gpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
       
/* Configure ePWM-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
	
    EDIS;
}


#if DSP28_EPWM4
void InitEPwm4Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)

/* Configure ePWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
	
    EDIS;
}
#endif // endif DSP28_EPWM4  


#if DSP28_EPWM5
void InitEPwm5Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)

/* Configure ePWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
	
    EDIS;
}
#endif // endif DSP28_EPWM5


#if DSP28_EPWM6
void InitEPwm6Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    // Enable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up on GPIO11 (EPWM6B)

/* Configure ePWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
	
    EDIS;
}
#endif // endif DSP28_EPWM6  

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM Synch pins
//

void InitEPwmSyncGpio(void)
{

   EALLOW;

/* Configure EPWMSYNCI  */
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO32 (EPWMSYNCI)    

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)    

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.   

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Enable pull-up on GPIO32 (EPWMSYNCI)    



/* Configure EPWMSYNC0  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Enable pull-up on GPIO33 (EPWMSYNC0)    

}



//---------------------------------------------------------------------------
// Example: InitTzGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 

void InitTzGpio(void)
{
   EALLOW;
   
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user. 
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
   GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
   GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
   GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up on GPIO15 (TZ4)

   GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ5)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ5)

   GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ6) 
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ6)  
   
/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (TZ4)

   GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ5)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ5)

   GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ6) 
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ6)  

   
/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.   
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // Configure GPIO15 as TZ4

   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ5
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ5

   GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ6               
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ6  

   EDIS;
}

//---------------------------------------------------------------------------
// InitEPwm:
//---------------------------------------------------------------------------
// This function initializes the ePWM(s) to a known state.
//

void InitEPwm(void)
{
	// 2. Set TBCLKSYNC to 0.
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	EDIS;

//EPWM Module 1 Config
	EPwm1Regs.TBPRD = PWM1_TIMER_TBPRD; // Period = 15000 TBCLK counts for up down counter
	EPwm1Regs.TBCTL.bit.CTRMODE = 2; //upDown_Mode
	EPwm1Regs.TBCTL.bit.PHSEN = 0;// disable phase since its the master module
	EPwm1Regs.TBPHS.half.TBPHS = 0; // Set Phase Register to zero
	EPwm1Regs.TBCTL.bit.PRDLD = 0; //TBPRD loaded only when TBCTR = 0
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // Sync down stream module

	EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0; // Shadowing CMPA
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0; // Shadowing CMPB
	EPwm1Regs.CMPCTL.bit.LOADAMODE = 0; // Load CMPA at CTR=0
	EPwm1Regs.CMPCTL.bit.LOADBMODE = 0; // Load CMP at CTR=0

	// Unipolar PWM
	EPwm1Regs.AQCTLA.bit.CAU = 1; // 1 is clear
	EPwm1Regs.AQCTLA.bit.CAD = 2;// 2 is set
	EPwm1Regs.AQCTLB.bit.CBU = 1;
	EPwm1Regs.AQCTLB.bit.CBD = 2;
	//EPwm1Regs.AQCTLA.bit.ZRO = 2;
	//EPwm1Regs.AQCTLA.bit.PRD = 1;
	// Bipolar PWM
	/*EPwm1Regs.AQCTLA.bit.CAU =1; // 1 is clear
	EPwm1Regs.AQCTLA.bit.CAD = 2;// 2 is set
	EPwm1Regs.AQCTLB.bit.CBU = 2;
	EPwm1Regs.AQCTLB.bit.CBD = 1;*/

	EPwm1Regs.DBCTL.bit.OUT_MODE = 0; //Deadband disabled
	//EPwm1Regs.DBCTL.bit.OUT_MODE = 3; // Deadband enabled for both rising and falling edges
	EPwm1Regs.DBCTL.bit.IN_MODE = 0;
//	EPwm1Regs.DBCTL.bit.POLSEL = 0;
	//EPwm1Regs.DBCTL.bit.POLSEL = 2;// Active high complimentary i.e. epwmB is inverted

	EPwm1Regs.ETSEL.bit.SOCAEN = 1; //Enable EPWMxSOCA
	EPwm1Regs.ETSEL.bit.SOCBEN = 0; //Disable EPWMxSOCB Complimentary signals desired
	EPwm1Regs.ETSEL.bit.SOCASEL = 1; // Generate SOCA pulse for zero base counter value
	EPwm1Regs.ETPS.bit.SOCACNT = 1;
	EPwm1Regs.ETPS.bit.SOCAPRD=1; //ePWM SOCA conversion for the very 1st event in SOCACNT
	EPwm1Regs.ETSEL.bit.INTSEL = 1;// Select INT on zero
	EPwm1Regs.ETSEL.bit.INTEN = 1;  // Enable INT
	EPwm1Regs.ETPS.bit.INTPRD = 1;           // Generate INT on 1st event
	EPwm1Regs.ETPS.bit.INTCNT = 1;

	EPwm1Regs.DBFED = 100; // Falling edge dead band 200 TBCLK
	EPwm1Regs.DBRED = 100; // Rising edge dead band 200 TBCLK

	// High Speed Time-base Clock Prescale Bits
	// These bits determine part of the time-base clock prescale value.
	// TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV)
	// This divisor emulates the HSPCLK in the TMS320x281x system
	// as used on the Event Manager(EV) peripheral.
	// 000 : /1, 001 : /2 (default on reset), 010 : /4,  011 : /6
	// 100 : /8, 101 : /10, 				  110 : /12, 111 : /14
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	// Time-base Clock Prescale Bits
	// These bits determine part of the time-base clock prescale value.
	// TBCLK = SYSCLKOUT / (HSPCLKDIV * CLKDIV)
	// 000 : /1 (default on reset), 001 : /2,  010 : /4,  011 : /8
	// 100 : /16, 					101 : /32, 110 : /64, 111 : /128
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	// -> TBCLK = 150MHz / (1 * 1) = 150MHz : 15000 count = 0.1ms
//	EPwm1Regs.TBCTL.all = 0x0012;	// 00 0 000 000 0 01 0 0 10		0000 0000 0001 0010

	//EPWM Module 2 Config
	EPwm2Regs.TBPRD = PWM2_TIMER_TBPRD; // Period = 15000 TBCLK counts for up down counter
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // upDown_Mode
	EPwm2Regs.TBCTL.bit.PHSEN = 1;// enable phase
	EPwm2Regs.TBCTL.bit.PHSDIR = 0; // Start up count upon sync
	EPwm2Regs.TBPHS.half.TBPHS = 0;//2*PWM2_TIMER_TBPRD/3; // Set Phase Register to0
	EPwm2Regs.TBCTL.bit.PRDLD = 0;//TB_IMMEDIATE; //TBPRD loaded only when TBCTR = 0
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Sync flow through
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = 0; // Shadowing CMPA
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = 0; // Shadowing CMPB
	EPwm2Regs.CMPCTL.bit.LOADAMODE = 0; // Load CMPA at CTR=0
	EPwm2Regs.CMPCTL.bit.LOADBMODE = 0; // Load CMP at CTR=0
	EPwm2Regs.AQCTLA.bit.ZRO = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.PRD = AQ_SET;
	EPwm2Regs.DBCTL.bit.OUT_MODE = 0; // Deadband disabled for both rising and falling edges
//EPwm2Regs.DBCTL.bit.POLSEL =0;// EPWMB is  inverted
	EPwm2Regs.ETSEL.bit.SOCAEN = 0; //disable EPWMxSOCA
	EPwm2Regs.ETSEL.bit.SOCBEN = 0; //Disable EPWMxSOCB
	EPwm2Regs.ETSEL.bit.SOCASEL = 1; // Generate SOCA pulse for zero base counter value
	EPwm2Regs.ETPS.bit.SOCAPRD=0; //ePWM SOCA conversion for the very 1st event in SOCACNT
	EPwm2Regs.ETSEL.bit.INTEN=0; // Disable PWM interrupts
	EPwm2Regs.DBFED = 100; // Falling edge dead band 200 TBCLK
	EPwm2Regs.DBRED = 100; // Rising edge dead band 200 TBCLK
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

//EPWM Module 3 Config
	EPwm3Regs.TBPRD = PWM3_TIMER_TBPRD; // Period = 15000 TBCLK counts for up down counter
	EPwm3Regs.TBPHS.half.TBPHS = 0; // Set Phase Register to zero
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // UP_Down_Mode
	EPwm3Regs.TBCTL.bit.PHSEN = 1;
	EPwm3Regs.TBCTL.bit.PHSDIR = 0; // Start up count upon sync
	EPwm3Regs.TBCTL.bit.PRDLD = 0;//TB_IMMEDIATE; //TBPRD loaded only when TBCTR = 0
	EPwm3Regs.TBCTL.bit.SYNCOSEL =  TB_SYNC_IN; // Synchronizing signal disbled
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0; // Shadowing CMPA
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = 0; // Shadowing CMPB
	EPwm3Regs.CMPCTL.bit.LOADAMODE = 0; // Load CMPA at CTR=0
	EPwm3Regs.CMPCTL.bit.LOADBMODE = 0; // Load CMP at CTR=0
	EPwm3Regs.AQCTLA.bit.ZRO = AQ_CLEAR;
	EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;
	EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	EPwm3Regs.AQCTLA.bit.PRD = AQ_SET;
	EPwm3Regs.DBCTL.bit.OUT_MODE = 0; // Deadband enabled for both rising and falling edges
//EPwm3Regs.DBCTL.bit.POLSEL = 2;// EPWM is inverted
	EPwm3Regs.ETSEL.bit.SOCAEN = 0; //Enable EPWMxSOCA
	EPwm3Regs.ETSEL.bit.SOCBEN = 0; //Disable EPWMxSOCB
	EPwm3Regs.ETSEL.bit.SOCASEL = 1; // Generate SOCA pulse for zero base counter value
	EPwm3Regs.ETPS.bit.SOCAPRD=1; //ePWM SOCA conversion for the very 1st event in SOCACNT
	EPwm3Regs.ETSEL.bit.INTEN=0; // Disable PWM interrupts
	EPwm3Regs.DBFED = 100; // Falling edge dead band 200 TBCLK
	EPwm3Regs.DBRED = 100; // Rising edge dead band 200 TBCLK
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

//EPWM Module 4 Config
	EPwm4Regs.TBPRD = PWM4_TIMER_TBPRD; // Period = 15000 TBCLK counts for up down counter
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // up down_Mode
	EPwm4Regs.TBCTL.bit.PHSEN = 0;
	EPwm4Regs.TBPHS.half.TBPHS = 0;//2*PWM3_TIMER_TBPRD/3;
	EPwm4Regs.TBCTL.bit.PRDLD = 0; //TBPRD loaded only when TBCTR = 0
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Sync flow through
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = 0; // Shadowing CMPA
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = 0; // Shadowing CMPB
	EPwm4Regs.CMPCTL.bit.LOADAMODE = 0; // Load CMPA at CTR=0
	EPwm4Regs.CMPCTL.bit.LOADBMODE = 0; // Load CMP at CTR=0
	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR; // Set EPWMA low for CTR=CMPA for up count
	EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;// Set EPWMA low for CTR=CMPA for down count
	EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm4Regs.AQCTLA.bit.PRD = AQ_CLEAR;
//	EPwm4Regs.AQCTLB.bit.CBU = 1; // Set EPWMB low for CTR=CMPB for up count
//	EPwm4Regs.AQCTLB.bit.CBD = 2;// Set EPWMB high for CTR=CMPB for down count
	EPwm4Regs.DBCTL.bit.OUT_MODE = 0; // Deadband disabled for both rising and falling edges
//EPwm4Regs.DBCTL.bit.POLSEL = 2;// EPWMB is  inverted
	EPwm4Regs.ETSEL.bit.SOCAEN = 0; //disable EPWMxSOCA
	EPwm4Regs.ETSEL.bit.SOCBEN = 0; //Disable EPWMxSOCB
	EPwm4Regs.ETSEL.bit.SOCASEL = 1; // Generate SOCA pulse for zero base counter value
	EPwm4Regs.ETPS.bit.SOCAPRD=0; //ePWM SOCA conversion for the very 1st event in SOCACNT
	EPwm4Regs.ETSEL.bit.INTEN=0; // Disable PWM interrupts
	EPwm4Regs.DBFED = 100; // Falling edge dead band 200 TBCLK
	EPwm4Regs.DBRED = 100; // Rising edge dead band 200 TBCLK
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
/*
//EPWM Module 4 Config
	EPwm4Regs.TBPRD = PWM4_TIMER_TBPRD;				// Set timer period
	EPwm4Regs.TBPHS.half.TBPHS = 0x0000;           	// Phase is 0
	EPwm4Regs.TBCTR = 0x0000;                      	// Clear counter

// Setup Time-Base Submodule Registers
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; 	// Up-down-count mode
	EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;			// Disable phase loading. Mastser Module
	EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

// Setup Counter-Compare Submodule Registers
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;


//
	// Setup compare
	EPwm4Regs.CMPA.half.CMPA = 3750;

// Set actions
	EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM4A on Zero
	EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;

//	EPwm4Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM4B on Zero
//	EPwm4Regs.AQCTLB.bit.CAD = AQ_SET;

// Active High PWMs - Setup Deadband
	EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
//EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
	EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
//EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
	EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;
	EPwm4Regs.DBRED = 450;
	EPwm4Regs.DBFED = 450;

// Interrupt where we will change the Deadband
	EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;   	// Select INT on Zero event
	EPwm4Regs.ETSEL.bit.INTEN = 0;					// Enable INT
	EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;         	// Generate INT on 1st event
*/
#if 0
//EPWM Module 5 Config
	EPwm5Regs.TBPRD = PWM5_TIMER_TBPRD; // Period = 15000 TBCLK counts for up down counter
	EPwm5Regs.TBPHS.half.TBPHS = PWM5_TIMER_TBPRD/3; // Set Phase Register to zero
	EPwm5Regs.TBCTL.bit.CTRMODE = 2; // UP_Down_Mode
	EPwm5Regs.TBCTL.bit.PHSEN =1;
	EPwm5Regs.TBCTL.bit.PHSDIR = 1; // Start up count upon sync
	EPwm5Regs.TBCTL.bit.PRDLD = 0; //TBPRD loaded only when TBCTR = 0
	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Synchronizing signal disbled
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = 0; // Shadowing CMPA
	EPwm5Regs.CMPCTL.bit.SHDWBMODE = 0; // Shadowing CMPB
	EPwm5Regs.CMPCTL.bit.LOADAMODE = 0; // Load CMPA at CTR=0
	EPwm5Regs.CMPCTL.bit.LOADBMODE = 0; // Load CMP at CTR=0
//EPwm5Regs.AQCTLA.bit.CAU = 1; // Set EPWMA low for CTR=CMPA for up count
//EPwm5Regs.AQCTLA.bit.CAD = 2;// Set EPWMA low for CTR=CMPA for down count
//EPwm5Regs.AQCTLB.bit.CBU = 2; // Set EPWMB low for CTR=CMPB for up count
//EPwm5Regs.AQCTLB.bit.CBD = 1;// Set EPWMB high for CTR=CMPB for down count
	EPwm5Regs.DBCTL.bit.OUT_MODE = 3; // Deadband enabled for both rising and falling edges
//EPwm5Regs.DBCTL.bit.POLSEL = 2;// EPWM is non inverted
	EPwm5Regs.ETSEL.bit.SOCAEN = 0; //Enable EPWMxSOCA
	EPwm5Regs.ETSEL.bit.SOCBEN = 0; //Disable EPWMxSOCB
	EPwm5Regs.ETSEL.bit.SOCASEL = 1; // Generate SOCA pulse for zero base counter value
	EPwm5Regs.ETPS.bit.SOCAPRD=1; //ePWM SOCA conversion for the very 1st event in SOCACNT
	EPwm5Regs.ETSEL.bit.INTEN=0; // Disable PWM interrupts
	EPwm5Regs.DBFED = 100; // Falling edge dead band 200 TBCLK
	EPwm5Regs.DBRED = 100; // Rising edge dead band 200 TBCLK
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

//EPWM Module 6 Config
	EPwm6Regs.TBPRD = PWM6_TIMER_TBPRD; // Period = 15000 TBCLK counts for up down counter
	EPwm6Regs.TBPHS.half.TBPHS = 0; // Set Phase Register to zero
	EPwm6Regs.TBCTL.bit.CTRMODE = 2; // UP_Down_Mode
	EPwm6Regs.TBCTL.bit.PHSEN = 1;
	EPwm6Regs.TBCTL.bit.PHSDIR = 1; // Start up count upon sync
	EPwm6Regs.TBCTL.bit.PRDLD = 0; //TBPRD loaded only when TBCTR = 0
	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;// Synchronizing signal disbled
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = 0; // Shadowing CMPA
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = 0; // Shadowing CMPB
	EPwm6Regs.CMPCTL.bit.LOADAMODE = 0; // Load CMPA at CTR=0
	EPwm6Regs.CMPCTL.bit.LOADBMODE = 0; // Load CMP at CTR=0
//EPwm6Regs.AQCTLA.bit.CAU = 1; // Set EPWMA low for CTR=CMPA for up count
//EPwm6Regs.AQCTLA.bit.CAD = 2;// Set EPWMA low for CTR=CMPA for down count
//EPwm6Regs.AQCTLB.bit.CBU = 2; // Set EPWMB low for CTR=CMPB for up count
//EPwm6Regs.AQCTLB.bit.CBD = 1;// Set EPWMB high for CTR=CMPB for down count
	EPwm6Regs.DBCTL.bit.OUT_MODE = 3; // Deadband enabled for both rising and falling edges
//EPwm6Regs.DBCTL.bit.POLSEL = 2;// EPWM is non inverted
	EPwm6Regs.ETSEL.bit.SOCAEN = 0; //Enable EPWMxSOCA
	EPwm6Regs.ETSEL.bit.SOCBEN = 0; //Disable EPWMxSOCB
	EPwm6Regs.ETSEL.bit.SOCASEL = 1; // Generate SOCA pulse for zero base counter value
	EPwm6Regs.ETPS.bit.SOCAPRD=1; //ePWM SOCA conversion for the very 1st event in SOCACNT
	EPwm6Regs.ETSEL.bit.INTEN=0; // Disable PWM interrupts
	EPwm6Regs.DBFED = 100; // Falling edge dead band 200 TBCLK
	EPwm6Regs.DBRED = 100; // Rising edge dead band 200 TBCLK*/
	EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;		// Clock ratio to SYSCLKOUT
	EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;
#endif

	// 4. Set TBCLKSYNC(Time Base Clock) to 1.
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
