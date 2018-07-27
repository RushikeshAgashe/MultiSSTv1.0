#include <math.h>
#include "DSP2833x_Device.h"
#include "filter.h"

#ifndef	__DEF28X_H
#define	__DEF28X_H

#define SAMPLING_PERIOD		0.0001		// Sampling time: PWM period and only zero event interrupt
#define FULL_PWM			 7500
#define HALF_PWM			 3750
#define ONETHIRD_PWM		 2500
#define TWOTHIRD_PWM		 5000
#define PWM_RES				  300
#define PWM_MIN				PWM_RES
#define PWM_MAX				7500-PWM_RES
#define DUTY_MAX			0.95 //1.0
#define DUTY_MIN			0.05 //0.02
#define FULL_DUTY			1.0
#define PWM_DB				165

#define SECTOR12			25
#define SECTOR23			2*SECTOR12
#define SECTOR34			3*SECTOR12
#define SECTOR45			4*SECTOR12
#define SECTOR56			5*SECTOR12
#define SECTOR61			6*SECTOR12

#define	Ibat_max 30
#define DAB_Pmax 3000

extern int InitCharge;

extern IIR1 LPF_Vpv;

extern IIR1 ALLPASS_Vg1;
extern IIR2 BPF_Vg1;
extern IIR1 LPF_Vg1;

extern IIR1 ALLPASS_Vpcc1;

extern IIR2 NOTCH_Vc1;
extern IIR2 BPF_Vc1;

extern IIR1 ALLPASS_Ig1;
extern IIR2 BPF_Ig1;
extern IIR1 LPF_Ig1;

extern IIR2 NOTCH_Vhdc1;
extern IIR1 LPF_Vhdc1;

extern IIR2 NOTCH_Vldc1;
extern IIR1 LPF_Vldc1;

extern IIR2 NOTCH_Pg1;
extern IIR1 LPF_Pg1;

extern IIR2 NOTCH_Qg1;
extern IIR1 LPF_Qg1;

extern IIR1 LPF_Vbat1;
extern IIR1 LPF_Iibat1;

extern float Ts, fs;

// ADC variables
extern float ScaleAin[16];
extern float OffsetAin[16];

//extern	int *da0[4] , da0_type[4];
extern float da0_scale[4], da0_mid[4];
extern Uint16 AdcData[16];
extern Uint16 SWFaultFlag;

// Fault
extern int CcCount, CcCountMax, InitiateCount, InitiateCountMax, BalanceCount, BalanceCountMax;	// CC indicator
extern int DebugCount, DebugCountMax, DebugCountLast;
extern int SignalTest;
extern int SectorCount, SectorCountMax;
extern Uint16 Flag_Fault, Flag_Fault_Confirm, FpgaFaultCheck, GatingOff,
		Flag_SW_Fault;		// Fault indicator

// PWM count
extern int EPwm1ACnt, EPwm1BCnt, EPwm2ACnt, EPwm2BCnt, EPwm3ACnt, EPwm3BCnt;// EPwm count number storage
extern int EPwm4ACnt, EPwm4BCnt, EPwm5ACnt, EPwm5BCnt, EPwm6ACnt, EPwm6BCnt;// EPwm count number storage

// Filter Coefficient
extern float APF60C0, APF60C1, APF60C2, APF60C3, APF60C4;// 60Hz All Pass Filter Coefficient
extern float LPF1kC0, LPF1kC1, LPF1kC2;	// 1000Hz Low Pass Filter Coefficient

// Operation Flag
extern int RunInv1, RunRec1;
extern int Flag_ModGain;

// CC setting variables
extern float Tsamp;
// System variables
extern float Rs, Lf, Cf, Rf, Ldc, Cdc, Rdc;
extern float MagE, InvMagE, FreqE, We;// Grid phase voltage magnitude and frequency
extern float Eab, Ebc, Eas, Ebs, Ecs;
//extern float Vdc, InvVdc, VdcA1, VdcU1, VdcU2;
extern float Vdc, InvVdc, Vcap_A, Vcap_B, Vcap_C;
extern float Ias, Ibs, Ics, Idc;
extern float Idss, Iqss, Idse, Iqse;

// PLL variables
extern float EasAPFed, EasAPF0, EasAPF1;
extern float EbsAPFed, EbsAPF0, EbsAPF1;
extern float EcsAPFed, EcsAPF0, EcsAPF1;
extern float Eap, Ebp, Ecp, Ean, Ebn, Ecn;
extern float Edss, Eqss, Edps, Eqps, Edns, Eqns;
extern float Edse, Eqse, Edpe, Eqpe, Edne, Eqne;
extern float EdpeLPFed, EdpeLPF0, EqpeLPFed, EqpeLPF0, EdseLPFed, EdseLPF0, EqseLPFed, EqseLPF0;
extern float IcsLPFed, IcsLPF0, IbsLPFed, IbsLPF0, tmpCLPFed, tmpCLPF0, IdcLPFed, IdcLPF0;
extern float Vcap_ALPFed, Vcap_ALPF0, Vcap_BLPFed, Vcap_BLPF0, Vcap_CLPF0, Vcap_CLPFed;

// HVADC
extern float HV_A, HV_B, HV_C;

// Controller
extern float Igrid, Vgrid, Igrid_fil, Vgrid_fil;
extern float Vgds, Vgqs, Igds, Igqs;
extern float Vgde, Vgqe, Igde, Igqe;
extern float Vdc1, Vdc2, Vdc3, Vdc_avg, Vdc_avg_fil;
extern float Vdc1_fil, Vdc2_fil, Vdc3_fil;
extern float Ig_rated;
extern float Igde_ref, Igqe_ref;
extern float Vsde_ref, Vsde_ref_sat, Vsqe_ref, Vsqe_ref_sat, Vsqe_ref_inv3;
extern float Vsde_ref1, Vsde_ref1_sat, Vsde_ref2, Vsde_ref2_sat, Vsde_ref3, Vsde_ref3_sat;
extern float Vsqe_ref1_sat, Vsqe_ref2_sat, Vsqe_ref3_sat;
extern float Vsds_ref1, Vsds_ref2, Vsds_ref3;
extern float Vsqs_ref1, Vsqs_ref2, Vsqs_ref3;
extern float Vsds_ref1_sat, Vsds_ref2_sat, Vsds_ref3_sat;
extern float Vsqs_ref1_sat, Vsqs_ref2_sat, Vsqs_ref3_sat;

///////////////////////////CC
extern int CC_run;
extern float Igde_err, Igqe_err;
extern float Igde_integ, Igqe_integ;
extern float Fc_cc;
extern float Ki_cc, Ki_ccT, Kp_cc, Ka_cc, Wc_cc;
extern float Rv;

///////////////////////////VC
extern int VC_run;
extern float Vdc_ref, Vdc_sum_ref, Vdc_ref_ramp;
extern float Err_Vdc;
extern float Vdc_integ, Vdc_ff;
extern float Idc_ref;
extern float Pdc_ref;
extern float Pg_ref;
extern float Kp_vc, Ki_vc, Ki_vcT, Ka_vc, Wc_vc, Zeta_vc, Fc_vc;
extern float Kg;
extern float Vdc_ref_setting, Vdc_ref_slope;
extern float Ig_amp_ref_bf, Igde_ref_bf, Igqe_ref_bf;
extern float P_ref, Q_ref;

// Space Vector Modulation
extern float MagRef, AngRef, AngPrime; //Magnitude and Angle of the Reference Vector
//extern float SinAng1, SinAng2; //sin(pi/6-theta'), sin(pi/6+theta')
//extern float d1, d2, m; //T1/Tsample, T2/Tsample, modulation index
//extern int Sector, SectorB;
extern int PWMCntT1, PWMCntT1PlusT2;
extern int PWMCntT1B, PWMCntT1PlusT2B;
//extern int SectorTransition;

////////////// test
//extern int tmpA;
//extern int tmpB;
extern float tmpC;
extern float tmpD;
extern float tmpA1, tmpA2;
extern float tmpB1, tmpB2;
extern float tmpC1, tmpC2;
extern float tmpD1, tmpD2;
extern float tmpE1, tmpE2;
extern float tmpF1, tmpF2;
extern int tmpG;
extern int tmpH;
extern int tmpI;
extern int tmpFlag;

/////////////boost
extern float Vpv, Iind, Vdc_LV, Vpv_fil;

/////////////////////////CC
extern int CC_PV_on;
extern float Iind_Err;
extern float Iind_integ;
extern float Vind_ff, Vind_anti;
extern float Vind_ref, Vind_ref_set;
extern float Ki_pv, Kp_pv, Ka_pv, Wcc_pv;

///////////////////////////VC
extern int VC_PV_on;
extern float Vpv_ref ;
extern float Err_Vpv;
extern float Vpv_integ, Ipv_ff;
extern float Ipv_ref, Ipv_ref_set;
extern float Kp_vc_pv,  Ki_vc_pv,   Ka_vc_pv, Wvc_pv, zeta_vc_pv;
extern float Vpv_ref_setting, Vpv_ref_slope;
extern float Cpv;
extern float Ipv_rated;

extern float Lpv;
extern float Rpv;
extern float Vpv_ramp;
extern float Pref_slope;
extern float Pref_ramp;
extern float Pref;
extern float time_test;

// Grid Switch
extern int Grid_on;
extern int Grid_on_flag;

// PLL Vg1
extern float all_Vg1, Vg1_f, Vg1h;
extern float Vg1_amp;
extern float Vgde1, Vgqe1;
extern float integ_PLL;
extern float Wg1;
extern float theta_g1, cos_theta_g1, sin_theta_g1;
extern float fc_PLL, zeta_PLL, wc_PLL, Ki_PLL, Ki_PLLT, Kp_PLL, Ka_PLL;
//extern float ThetaeAdv, CosThetaeAdv, SinThetaeAdv;
//extern float ErrThetae, WeFbInteg, WeFb, We_hat, WeHatAnti;

// PLL Vpcc1
extern float all_Vpcc1;
extern float Vpcc1_amp;
extern float Vpccde1, Vpccqe1;
extern float integ_PLL_pcc1;
extern float Wpcc1;
extern float theta_pcc1, cos_theta_pcc1, sin_theta_pcc1;

// ========== SOGI ==============
extern float sogi_Vg, sogi_qVg;
extern float x, y, w_sogi, k_sogi;
extern float a1_sogi, a2_sogi, b0_sogi;
extern float u0_sogi, u1_sogi, u2_sogi;

extern float sogi_Ig, sogi_qIg;
extern float Ig0_sogi, Ig1_sogi, Ig2_sogi;

extern float sogi_Vpcc, sogi_qVpcc;
extern float Vpcc0_sogi, Vpcc1_sogi, Vpcc2_sogi;

//=======Reconnection
extern float theta_diff1;
extern float Ki_theta1,Kp_theta1;
extern float integ_theta1;
extern float match_theta1;

// Inverter 1
extern float Vhdc1, Vc1, Vg1, Vpcc1, Ii1, Ig1, Vbat1, Vbat1_f, Vldc1, Iibat1;
extern float sin_test;
extern float d1;

// ==================== Grid Current
extern float all_Ig1, Ig1_f;
extern float Igde1, Igqe1;

// ==================== PWM
extern float ref_Vi1;
extern float ref_sat_Vi1;

// ==================== Vc1 PR Controller
extern int VC_on_rec1;
extern int droop_on;
extern int droop_init;
extern float ref_Vc1, Vc1_f;
extern float err_Vc1, err_1_Vc1, err_2_Vc1;
extern float integ_Vc1, integ_1_Vc1, integ_2_Vc1;
extern QR QR_Vc;

extern float Kp_Vc1;
extern float Ki_Vc1;

extern float ff_ratio1; // feedforward ratio
extern int   ff_count1; // to remove feedforward smooth
extern int   ff_off;
extern float ff_vg1h_on;

extern float err_Ig, err_1_Ig1, err_2_Ig1;
extern QR QR_h3_Ig, QR_h5_Ig, QR_h7_Ig, QR_h9_Ig, QR_h11_Ig;

extern float h3_on, Ki_h3_Ig, integ_h3_Ig;
extern float h5_on, Ki_h5_Ig, integ_h5_Ig;
extern float h7_on, Ki_h7_Ig, integ_h7_Ig;
extern float h9_on, Ki_h9_Ig, integ_h9_Ig;
extern float h11_on,Ki_h11_Ig,integ_h11_Ig;

// ==================== Droop
extern float Mp, Mq;
extern float ref_Pg1, Pg1, Pg1_f, ref_Qg1, Qg1, Qg1_f, ref_ramp_Qg1;
extern float Wc1;
extern float Ec1; // Voltage Magnitude
extern float theta_c1; // Voltage Angle
extern float cos_theta_c1;
// ==================== BMS
extern float Kp_BMS, Ki_BMS, KiT_BMS, err_P_BMS, integ_BMS, ref_P_BMS, Pbat;

// ===================== Qg1 PI Control
extern float err_Qg1, integ_Qg1;
extern float Kp_Qg1, Ki_Qg1;

// DAB 1
extern int VC_on_dab1;
extern float err_Vhdc1, ref_Vhdc1, ref_ramp_Vhdc1, Vhdc1_f;
extern float integ_Vhdc1, anti_Vhdc1;
extern float ref_d1, ref_sat_d1;
extern float Kp_Vhdc1, Ki_Vhdc1, Ka_Vhdc1, KiT_Vhdc1;
extern float f_Vhdc1, w_Vhdc1, zeta_Vhdc1;
extern float ref_Pdc1, ref_sat_Pdc1;
extern float ddb1;

// Buck/Boost 1
//-------------------------Parameter
extern float Chdc1;
extern float Cldc1;
extern float Lbat1;
extern float Rbat1;
extern float Lt1;

//-------------------------Vldc1 PI Controller
extern int VC_on_bat1;
extern float err_Vldc1, ref_Vldc1, ref_ramp_Vldc1, Vldc1_f;
extern float integ_Vldc1, anti_Vldc1;
extern float ref_Iibat1, ref_sat_Iibat1;
extern float Kp_Vldc1, Ki_Vldc1, Ka_Vldc1;
extern float zeta_Vldc1, w_Vldc1, f_Vldc1;

//-------------------------Iibat1 PI Controller
extern int CC_on_bat1;
extern float err_Iibat1, Iibat1_f;
extern float integ_Iibat1, anti_Iibat1;
extern float ref_Vibat1, ref_sat_Vibat1;
extern float Kp_Iibat1, Ki_Iibat1, Ka_Iibat1;
extern float w_Iibat1, f_Iibat1;

#endif

