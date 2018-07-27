/***************************************************************
	FILTER.H
	generic 1st- and 2nd-order filter
	
	1st-order filter : 
	void IIR1CoeffInit(IIR1 *p_gIIR, const dt);
	void IIR1Init(IIR1 *p_gIIR, const float sample_time);
	float IIR1Update(IIR1 *p_gIIR, const float input);

	2nd-order filter : 
	void IIR2CoeffInit(IIR1 *p_gIIR, const dt);
	void IIR2Init(IIR2 *p_gIIR, const float sample_time);
	float IIR2Update(IIR2 *p_gIIR, const float input);

	programmed by Yo-chan Son, Oct 2000.
	copyright (c) 1991, 2000 by EEPEL, SNU, SEOUL, KOREA
	All Rights Reserved.

	modified by T.S.Kwon, 2008
	1st-order filter : 
	void IIR1CoeffInit(IIR1 *p_gIIR, float w0 );
	void IIR1Init(IIR1 *p_gIIR, float w0 );
	float IIR1Update(IIR1 *p_gIIR, const float input );

	2nd-order filter : 
	void IIR2CoeffInit(IIR1 *p_gIIR, float w0, float zeta );
	void IIR2Init(IIR2 *p_gIIR, float w0, float zeta );
	float IIR2Update(IIR2 *p_gIIR, const float input);

	Added by Yonghwan Cho, 2017, FREEDM, NCSU, Raleigh, NC
	Quasi-Resonant Controller :
	float QRUpdate(QR *p_gQR, const float x);
	void gainQR(QR *p_gQR, float wc, float w, float Ki, float Ts);
	void initiateQR(QR *p_gQR, float wc, float w, float Ki, float Ts);
****************************************************************/
#ifndef _CUSTOMIZED_FILTER__
#define _CUSTOMIZED_FILTER__

#define	K_ALLPASS	0
#define	K_LPF		1
#define	K_HPF		2
#define	K_BPF		3
#define	K_NOTCH		4

#define IIR1DEFINE(type, w0, Ts)		{(int)(type), (float)(w0), (float)(Ts), 0, 0, 0, 0}
#define IIR2DEFINE(type, w0, zeta,Ts)	{(int)(type), (float)(w0), (float)(zeta), (float)(Ts), 0, 0, 0, 0, 0, 0, 0}

typedef struct	{
	int type;
	float w0;
	float delT;
	float coeff[3], reg;
}	IIR1;

typedef struct	{
	int type;
	float w0, zeta;
	float delT;
	float coeff[5], reg[2];
}	IIR2;

typedef struct	{
	float wc, w, Ki;
	float delT;
	float coeff[5], reg[2];
}	QR;

IIR1 IIR1DEFINE_F(int type, float w0, float Tsamp);


IIR2 IIR2DEFINE_F(int type, float w0, float zeta, float Tsamp);
//extern IIR1 Vqse_filter;
extern IIR1 LPF_We_hat;
extern IIR1 LAM_HPF_d;
extern IIR1 LAM_HPF_q;

//extern IIR1 LAM_LPF_d;
//extern IIR1 LAM_LPF_q;
//extern IIR1 Idrs_LPF_d;
//extern IIR1 Iqrs_LPF_q;

/*void IIR1CoeffInit(IIR1 *p_gIIR, const float dt);
void IIR1Init(IIR1 *p_gIIR, const float dt);
float IIR1Update(IIR1 *p_gIIR, const float x);*/
extern void IIR1CoeffInit(IIR1 *p_gIIR, float w0 );
extern void IIR1Init(IIR1 *p_gIIR, float w0 );


extern void initiateIIR1(IIR1 *p_gIIR, int type, float w0, float T);
extern void initiateIIR2(IIR2 *p_gIIR, int type, float w0, float zeta, float T);
extern void initiateQR(QR *p_gQR, float wc, float w, float Ki, float Ts);
extern void gainQR(QR *p_gQR, float wc, float w, float Ki, float Ts);

extern float IIR1Update(IIR1 *p_gIIR, float input);
extern float IIR2Update(IIR2 *p_gIIR, const float input);
extern float QRUpdate(QR *p_gQR, const float x);

/*void IIR2CoeffInit(IIR2 *p_gIIR, const float dt);
void IIR2Init(IIR2 *p_gIIR, const float dt);
float IIR2Update(IIR2 *p_gIIR, const float x);*/
extern void IIR2CoeffInit(IIR2 *p_gIIR, float w0, float zeta );
extern void IIR2Init(IIR2 *p_gIIR, float w0, float zeta );


//extern IIR1 Filter_Vdc;
//extern IIR1 Filter_Vdcf;
//extern IIR1 Filter_Ede;
//extern IIR1 Filter_Vsc1 ;
//extern IIR1 Filter_W1 ;
//extern IIR2 Filter_W2 ;
//extern IIR1 Filter_T_GEN ;
//extern IIR1 Filter_Current_d ;
//extern IIR1 Filter_Current_q ;
//extern IIR2 Filter_Current_d ;
//extern IIR2 Filter_Current_q ;
extern IIR2 Filter_Lamdss;
extern IIR2 Filter_Lamqss;
extern IIR2 Vd_emf_f;
extern IIR2 Vq_emf_f;
//extern IIR1 Idre_emf_f;
//extern IIR1 Iqre_emf_f;
extern IIR1 Vd_emf_f1;
extern IIR1 Vq_emf_f1; 
extern IIR1 Wrpm_filter;
extern IIR1 Wind_filter;
extern IIR1 Wind_filter_ini;
extern IIR1 Iqre_filter_wind;

extern IIR1 Is_amp_filter;
extern IIR1 Ir_amp_filter;

extern IIR1 Ids_filter;
extern IIR1 Iqs_filter;
extern IIR1 Idr_filter;
extern IIR1 Iqr_filter; 
extern IIR1 Vout_filter;
extern IIR1 Vout_filter_r;

extern IIR1 Wslip_filter;
/*
extern IIR1 Ids_f1;
extern IIR1 Iqs_f1;
extern IIR1 Idr_f1;
extern IIR1 Iqr_f1;

extern IIR1 Ids_f2;
extern IIR1 Iqs_f2;
extern IIR1 Idr_f2;
extern IIR1 Iqr_f2; 
*/
//extern IIR1 Iall_f; 
//extern IIR1 Iamp_f; 

extern IIR1 power_s_f; 
extern IIR1 power_r_f; 

#endif


