// TI File $Revision: /main/5 $
// Checkin $Date: October 23, 2007   13:34:09 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_usDELAY  5000L

#define ADC_CKPS   0x0   // ADC module clock = HSPCLK/1      = 25.5MHz/(1)   = 25.0 MHz
#define ADC_SHCLK  0x1   // S/H width in ADC module periods                  = 2 ADC cycle


//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);


    // *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	    EALLOW;
		SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
		ADC_cal();
		EDIS;




    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
	// CPU_RATE define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.

    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

	// Clock Setting
	// ACQ_PS[3:0]
	// Acquisition window size. This bit field controls the width of SOC pulse, which,
	// in turn, determines for what time duration the sampling switch is closed.
	// The width of SOC pulse is ADCTRL1[11:8] + 1 times the ADCLK period.
	AdcRegs.ADCTRL1.bit.ACQ_PS = 0xF;
	// ADCCLKPS [3:0]
	// Core clock divider. 28x peripheral clock, HSPCLK, is divided by 2*ADCCLKPS[3-0],
	// except when ADCCLKPS[3-0] is 0000, in which case HSPCLK is directly passed on. The
	// divided clock is further divided by ADCTRL1[7]+1 to generate the core clock, ADCLK.
	// 		ADCCLKPS [3:0] Core Clock Divider ADCLK
	//		xxxx n HSPCLK/[2n*(ADCTRL1[7] + 1)]
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 0;
	// CPS
	// Core clock prescaler.
	// The prescaler is applied to divided device peripheral clock, HSPCLK.
	//		0 : ADCCLK = Fclk/1
	//		1 : ADCCLK = Fclk/2
	//	  Note: Fclk = Prescaled HSPCLK (ADCCLKPS[3:0])
	AdcRegs.ADCTRL1.bit.CPS = 1;

	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0; // Sequential
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1; // Cascaded
	// Configure ADC
	// MAX_CONVn
	// MAX_CONVn bit field defines the maximum number of conversions executed
	// in an autoconversion session. The bit fields and their operation vary
	// according to the sequencer modes (dual/cascaded).
	// For SEQ1 operation, bits MAX_CONV1[2:0] are used.
	// For SEQ2 operation, bits MAX_CONV2[2:0] are used.
	// For SEQ operation, bits MAX_CONV1[3:0] are used. An autoconversion session
	// always starts with the initial state and continues sequentially until
	// the end state if allowed. The result buffer is filled in a sequential order.
	// Any number of conversions between 1 and (MAX_CONVn +1) can be programmed
	// for a session.
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x9;       // Setup 1 conv's on SEQ1 (n+1)
	// 0000 : ADCINA0, 0001 : ADCINA1, 0010 : ADCINA2, 0011 : ADCINA3
	// 0100 : ADCINA4, 0101 : ADCINA5, 0110 : ADCINA6, 0111 : ADCINA7
	// 1000 : ADCINB0, 1001 : ADCINB1, 1010 : ADCINB2, 1011 ADCINB3
	// 1100 : ADCINB4, 1101 : ADCINB5, 1110 : ADCINB6, 1111 ADCINB7

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;	// Setup ADCINB0 as 1st SEQ1 conv. -> Output DC Current
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;	// Setup ADCINB1 as 2nd SEQ1 conv. -> Capacitor C Voltage
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;	// Setup ADCINB2 as 3rd SEQ1 conv. -> Capacitor B Voltage
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;	// Setup ADCINA0 as 4st SEQ1 conv. -> Capacitor A Voltage
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;	// Setup ADCINA1 as 5th SEQ1 conv. -> Input Source Current C
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;	// Setup ADCINA2 as 6th SEQ1 conv.-> Input Source Current B
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;	// Setup ADCINA0 as 11st SEQ1 conv.
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;	// Setup ADCINA0 as 12st SEQ1 conv.
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;	//AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x2;	// Setup ADCINA2 as 6th SEQ1 conv.-> Input Source Current B
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
	//AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;	// Setup ADCINA0 as 11st SEQ1 conv.
	//AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;	// Setup ADCINA0 as 12st SEQ1 conv.

	//AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;	// Setup ADCINA0 as 1st SEQ1 conv.
	//AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;	// Setup ADCINA1 as 2nd SEQ1 conv.
	//AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;	// Setup ADCINA0 as 3rd SEQ1 conv.
	//AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;	// Setup ADCINA0 as 4st SEQ1 conv.
	//AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;	// Setup ADCINA0 as 9st SEQ1 conv.
	//AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;	// Setup ADCINA0 as 10st SEQ1 conv.
	//AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;	// Setup ADCINA0 as 11st SEQ1 conv.
	//AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;	// Setup ADCINA0 as 12st SEQ1 conv.

	// ePWM_SOCA_SEQ1 : ePWM SOCA enable bit for SEQ1
	//		0 : SEQ1 cannot be started by ePWMx SOCA trigger.
	//		1 : Allows SEQ1/SEQ to be started by ePWMx SOCA trigger. The ePWMs can be
	//			programmed to start a conversion on various events.
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// Enable SOCA from ePWM to start SEQ1
	// INT_ENA_SEQ1	: SEQ1 interrupt enable.
	//				  This bit enables the interrupt request to CPU by INT SEQ1.
	//		0 : Interrupt request by INT_SEQ1 is disabled.
	//		1 : Interrupt request by INT_SEQ1 is enabled.
	// cf.	ADC Status and Flag Register (ADCST) Bit 0.
	//	  	INT_SEQ1 :	SEQ1 interrupt flag bit. Write to this bit has no effect.
	//				  	In interrupt mode 0, i.e. when ADCTRL2[10]=0, this bit is set
	//				  	on every end of sequence of Seq 1. In interrupt mode 1, i.e.,
	//				  	when ADCTRL2[10]=1, this bit is set on an end of sequence of Seq 1
	//				  	if EOS_BUF1 is set.
	//			0 : No SEQ1 interrupt event.
	//			1 : SEQ1 interrupt event occurred.
	// 		ADC Status and Flag Register (ADCST) Bit 6.
	//		EOS_BUF1 :	End of sequence buffer bit for SEQ1. This bit is not used and remains
	//					as zero in interrupt mode 0, i.e. when ADCTRL2[10]=0. In interrupt
	//					mode 1, i.e. when ADCTRL2[10]=1, it toggles on every end of sequence
	//					of SEQ1. This bit is cleared on device reset and is not affected
	//					by sequencer reset or clearing of the corresponding interrupt flag.
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;  // Enable SEQ1 interrupt (every EOS)

}

#if 0
void initialize_ADC_PWM(void)
{
InitAdc();
/*AdcRegs.ADCTRL1.bit.SEQ_CASC = 1; // Dual sequencer (2*8 state) or cascaded mode
//AdcRegs.ADCTRL1.bit.ACQ_PS = 4;
AdcRegs.ADCTRL1.bit.CPS = 1; // clock prescaler
AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// enable epwm SOCA
AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;// core clock divider
AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;// sequential sampling mode*/
AdcRegs.ADCTRL3.bit.ADCCLKPS = 0; // Core Clock divider -> 0 HSPCLK/(ADCTRL![7]+1)
AdcRegs.ADCTRL1.bit.CPS =0; // Core Clock Prescaler - ADCCLK = Fclk/1
AdcRegs.ADCTRL1.bit.ACQ_PS = 0; // 12.5 MHz / 12.5 MSPS sustained conversion rate  = 40ns SH width
AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;     // Enable Sequential Sampling Mode.
AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;      // Enable Operation as a Single 16-state Sequence - Cascade Mode.
AdcRegs.ADCMAXCONV.all = 4;       // Setup 16 conversions for cascade sequence
//AdcRegs.ADCMAXCONV.all = 0x0001;
AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1; // Enable SOCA fr om ePWM to start SEQ1
//AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // Enable SEQ1 interrupt (every EOS)
AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 8;
AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;
AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;
AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2;
AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 3;
AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 4;
AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 5;
AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 6;
AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 7;
AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 8;

}

void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);


    // *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	    EALLOW;
		SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
		ADC_cal();
		EDIS;




    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
	// CPU_RATE define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.

    AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;	// Power up bandgap/reference circuitry
	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;		// Power up rest of ADC
	DSP28x_usDelay(ADC_usDELAY);                  // Delay after powering up ADC
	AdcRegs.ADCTRL3.bit.ADCCLKPS=0;			// ADCCLK= Mhz
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;		// Selectign sequential conversion 
	AdcRegs.ADCMAXCONV.all = 15;      		// Max conversions for Sequential mode 
//	AdcRegs.ADCTRL3.bit.SMODE_SEL = 1;		// Selectign Simultaneous conversion 
//	AdcRegs.ADCMAXCONV.all = 7;      		// Max conversions for Simultaneous mode
	
	AdcRegs.ADCCHSELSEQ1.all= 0x3210; 
    AdcRegs.ADCCHSELSEQ2.all= 0x7654; 
    AdcRegs.ADCCHSELSEQ3.all= 0xba98; 
    AdcRegs.ADCCHSELSEQ4.all= 0xfedc;
    
    AdcRegs.ADCTRL1.bit.SEQ_CASC=0x1;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // Enable SEQ1 interrupt (every EOS)
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 1;
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 1;
	
	
	// Specific ADC setup for this example:
      AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;  // Sequential mode: Sample rate   = 1/[(2+ACQ_PS)*ADC clock in ns]
                           //                     = 1/(3*40ns) =8.3MHz (for 150 MHz SYSCLKOUT)
   					    //                     = 1/(3*80ns) =4.17MHz (for 100 MHz SYSCLKOUT)
   					    // If Simultaneous mode enabled: Sample rate = 1/[(3+ACQ_PS)*ADC clock in ns]
      AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
      AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode
      AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
      AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // Setup continuous run

      AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;       // Enable Sequencer override feature
      AdcRegs.ADCCHSELSEQ1.all = 0x0;         // Initialize all ADC channel selects to A0
      AdcRegs.ADCCHSELSEQ2.all = 0x0;
      AdcRegs.ADCCHSELSEQ3.all = 0x0;
      AdcRegs.ADCCHSELSEQ4.all = 0x0;
      AdcRegs.ADCMAXCONV.all = 0x15;  // convert and store in 16 results registers

}
#endif
//===========================================================================
// End of file.
//===========================================================================
