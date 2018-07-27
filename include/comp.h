/***************************************************************
	COMP.H
	
	programmed by Yo-chan Son, Oct 2000.
	copyright (c) 1991, 2000 by EEPEL, SNU, SEOUL, KOREA
	All Rights Reserved.
****************************************************************/

#ifndef	_CUSTOMIZED_COMP
#define	_CUSTOMIZED_COMP

#define SYS_CLK			150e6
#define SYS_CLK_PRD		6.666666666666667e-009
#define SAMPLING_TIME	100e-6


#define TRUE			1
// Floating-point Constants
#define	PI			((float)3.141592653589793)
#define	TWOPI		((float)6.283185307179586)
#define	SQRT2		((float)1.414213562373095)
#define	SQRT3		((float)1.732050807568877)
#define	INV_SQRT3	((float)0.577350269189626)
#define	INV_SQRT2	((float)0.707106781186547)
#define	INV_3		((float)0.333333333333333)
#define INV_2PI		((float)0.159154943091895)
#define Rm2Rpm		((float)9.549296585513720)	
#define Rpm2Rm		((float)0.104719755119659)
#define INV3_2		((float)0.666666666666667)
#define Grid_Speed  ((float)377)


// Inverse Factorial 
#define f2      	((float)(1./2.))
#define	f3			((float)(f2/3.))
#define	f4			((float)(f3/4.))
#define	f5			((float)(f4/5.))
#define	f6			((float)(f5/6.))
#define	f7			((float)(f6/7.))
#define	f8			((float)(f7/8.))
#define	f9			((float)(f8/9.))
#define	f10			((float)(f9/10.))
#define	f11			((float)(f10/11.))
#define	f12			((float)(f11/12.))
#define	f13			((float)(f12/13.))
#define	f14			((float)(f13/14.))
#define	f15			((float)(f14/15.))
// Macro Functions
//#define	BOUND_PI(x)		((x) - 2.*PI*(int)((x + PI)/(2.*PI)))
//#define BOUND_PI(x)		((x>0)?((x)-2.*PI*(int)((x+PI)/(2.*PI))):((x)-2.*PI*(int)((x-PI)/(2.*PI))))
//#define BOUND_PI(x)		((x>0)?((x)-2.*PI*(int)((x+PI)*INV_2PI)):((x)-2.*PI*(int)((x-PI)*INV_2PI)))
#define BOUND_PI(x)		((x)>0?((x)-TWOPI*(long)(((x)+PI)*INV_2PI)):((x)-TWOPI*(long)(((x)-PI)*INV_2PI)))
#define SIN(x,x2)		((x)*((float)1.-(x2)*(f3-(x2)*(f5-(x2)*(f7-(x2)*(f9-(x2)*(f11-(x2)*(f13-(x2)*f15))))))))
#define COS(x2)			((float)1.-(x2)*(f2-(x2)*(f4-(x2)*(f6-(x2)*(f8-(x2)*(f10-(x2)*(f12-(x2)*f14)))))))
//#define SIN_INV_X(x2)   (((float)1.-(x2)*(f3-(x2)*(f5-(x2)*(f7-(x2)*(f9-(x2)*(f11-(x2)*(f13-(x2)*f15))))))))
//#define EXP(x)			((float)1.+(x)*((float)1.+(x)*(f2+(x)*(f3+(x)*(f4+(x)*(f5+(x)*(f6+(x)*f7)))))))

// 2-D Arctangent Approximation
#define	ATAN_TABLE_SIZE	2048
#define	ATAN_TABLE(f)	(*(float *)(p_atanTable + (int)(f*(float)atanSize + 0.5)))
#define	atan1Table(f)	ATAN_TABLE((f))

int atanTableInit(void);
float atan2Table(const float y, const float x);

//slip-torque table
/*
#define T200      	1
#define	T400		1.1
#define	T600		1.2
#define	T800		1.3
#define	T1000		1.5
#define	T1200		3.089
#define	T1400		7.395
#define	T1500		10.707
#define	T1600		17.199
#define	T1700		9
#define	T1720		4.2
*/
/*
#define INV_T200      	2.5
#define	INV_T400		2.3810
#define	INV_T600		1.7544
#define	INV_T800		1.2346
#define	INV_T1000		0.6944
#define	INV_T1200		0.3237
#define	INV_T1400		0.1352
#define	INV_T1500		0.0934
#define	INV_T1600		0.0584
#define	INV_T1700		0.1111
#define	INV_T1720		0.2381 
*/
#define INV_200    	0.005
#define	INV_100		0.01
#define INV_20		0.05
#define INV_80		0.0125


#endif
