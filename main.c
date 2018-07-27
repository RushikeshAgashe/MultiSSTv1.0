/*
 * main.c
 */
#include "DSP28x_Project.h"
#include "DSP2833x_Sci.h"
#include "DSP2833x_EPwm.h"
#include "stdio.h"
#include "controller.h"
#include "utilities.h"
#include "epwm.h"

//////MODBUS
#include <sunspec_modbus/modbus/include/port.h>
#include <sunspec_modbus/include/sunspec_interface.h>
#include "variables.h"

int main(void) {
    MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);   // used in program to flash

    InitSysCtrl();
    InitGpio();
    InitEPwmGpio();

    //Debug GPIO
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;    // Set as Output
    EDIS;
    GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
    #if SCI_PORT == SCI_A
        InitSciaGpio();
    #elif SCI_PORT == SCI_B
        InitScibGpio();
    #endif
    InitCpuTimers(); //Initialize all CPU timers to known states
    DINT;
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    InitPieVectTable();

    EALLOW;
    PieVectTable.EPWM1_INT = &controller;   // ISR address stored
    PieVectTable.TINT0     = &CpuTimer0IsrHandler;

    //MODBUS
    #if SCI_PORT == SCI_A
        PieVectTable.SCITXINTA  = &SciTxIsrHandler;
        PieVectTable.SCIRXINTA  = &SciRxIsrHandler;
        PieCtrlRegs.PIEIER9.bit.INTx1   = 1;   // PIE Group 9, INT1 //SCIRXINTA_ISR
        PieCtrlRegs.PIEIER9.bit.INTx2   = 1;   // PIE Group 9, INT2 FOR SCIA TX
    #elif SCI_PORT == SCI_B
        PieVectTable.SCITXINTB  = &SciTxIsrHandler;
        PieVectTable.SCIRXINTB  = &SciRxIsrHandler;
        PieCtrlRegs.PIEIER9.bit.INTx3   = 1;   // PIE Group 9, INT3 //SCIRXINTB_ISR
        PieCtrlRegs.PIEIER9.bit.INTx4   = 1;   // PIE Group 9, INT4 FOR SCIB TX
    #endif

    PieCtrlRegs.PIEIER3.bit.INTx1   = 1;      // Enable service to Group3 Interrupt1 i.e. EPWM1_INT
    PieCtrlRegs.PIECTRL.bit.ENPIE   = 1;    // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx7   = 1;   // TINT0 in the PIE: Group 1 interrupt 7

    IER |= M_INT3;                          // Enable Group3 Interrupts (CPU INT3)

    //MODBUS
    IER |= M_INT9; //SCI Tx, Rx ISR         // Enable Group9 Interrupts (CPU INT9)
    IER |= M_INT1; //CPU Timer ISR

    InitEPwm1();
    InitEPwm2();
    InitEPwm3();
    InitEPwm4();
    InitEPwm5();
    InitAdc();
    init_sogi_filter(TS, 2*PI*FGRID, K_SOGI);
    init_PRController_HBridge();
    EINT;
    ERTM; // Enable Global Real Time Interrupt

    suns_init();
    suns_model_default_init();
    while (1){
        suns_model_update();
        suns_poll();
    }
}
