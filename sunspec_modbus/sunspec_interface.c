/*
 * sunspec_interface.c
 *
 *  Created on: May 28, 2018
 *      Author: Rushikesh
 */

#include <include/sunspec_interface.h>
#include <include/sunspec_model.h>
#include <include/sunspec_utilities.h>
#include "../variables.h"

/* suns_model_update(void) should be called periodically to update the
 * MODBUS registers with the updated value of the corresponding variables.
 * To ensure correct sunspec datatype, use suitable MACRO from the list below:
 * -----------------------------------------------------------------------------
 *      DATATYPE            MACRO
 * -----------------------------------------------------------------------------
 *      sunssf              SUNS_SF(<int value>)
 *      suns_uint32         SUNS_F32(<positive float value>, <scaling factor>)
 *                          or SUNS_U32(<uint32 value>)
 *      suns_int32          SUNS_F32(<float value>, <scaling factor>)
 *                          or SUNS_S32(<int value>)
 *      suns_uint16         SUNS_U16(<uint16 value>)
 *      suns_int16          SUNS_S32(<int16 value>)
 * -----------------------------------------------------------------------------
 *
 * Example Usage:
 * void suns_model_update(void){
 *   StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
 *   pStandardModel->dummy_sf = SUNS_SF(dummy_sf);
 *   pStandardModel->dummy0 = SUNS_F32(dummy0, pStandardModel->dummy_sf);
 *   pStandardModel->dummy1 = SUNS_U32(dummy1, pStandardModel->dummy_sf);
 *   pStandardModel->dummy2 = SUNS_S16(dummy2, pStandardModel->dummy_sf);
 * }
 *
 * where, dummy_sf, dummy0, dummy1, dummy2 are variables of your project.
 * For example, if your variables are declared in "variables.h", include this file at the top
 * of this file.
 */

void suns_model_default_init(void){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    pStandardModel->E3_sf = SUNS_SF_WRITE(-3);
    pStandardModel->Vhdc_ref = SUNS_F32_WRITE(Vhdc_ref, pStandardModel->E3_sf);
    pStandardModel->Vldc_ref = SUNS_F32_WRITE(Vldc_ref, pStandardModel->E3_sf);
    pStandardModel->Iinv_ref = SUNS_F32_WRITE(Iinv_ref, pStandardModel->E3_sf);
    pStandardModel->Iinv_ref_ramp_rate_per_s = SUNS_F32_WRITE(Iinv_ref_ramp_rate_per_s, pStandardModel->E3_sf);
}

void suns_model_update(void){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    Vhdc_ref = SUNS_F32_READ(pStandardModel->Vhdc_ref, pStandardModel->E3_sf);
    Vldc_ref = SUNS_F32_READ(pStandardModel->Vldc_ref, pStandardModel->E3_sf);
    Iinv_ref = SUNS_F32_READ(pStandardModel->Iinv_ref, pStandardModel->E3_sf);
    Iinv_ref_ramp_rate_per_s = SUNS_F32_READ(pStandardModel->Iinv_ref_ramp_rate_per_s, pStandardModel->E3_sf);
    pStandardModel->Vbat = SUNS_F32_WRITE(Vbat, pStandardModel->E3_sf);
    pStandardModel->Vldc = SUNS_F32_WRITE(Vldc, pStandardModel->E3_sf);
    pStandardModel->Vhdc = SUNS_F32_WRITE(Vhdc, pStandardModel->E3_sf);
    pStandardModel->Iinv = SUNS_F32_WRITE(Iinv, pStandardModel->E3_sf);
    pStandardModel->Iinv_rms = SUNS_F32_WRITE(Iinv_rms, pStandardModel->E3_sf);
    pStandardModel->Iload_rms = SUNS_F32_WRITE(Iload_rms, pStandardModel->E3_sf);
}

void suns_model_update_critical(void){
    StandardModel_S * pStandardModel = (StandardModel_S*)&usRegHoldingBuf[STANDARD_MODEL_OFFSET];
    Iinv_ref = SUNS_F32_READ(pStandardModel->Iinv_ref, pStandardModel->E3_sf);
    pStandardModel->Iinv_rms = SUNS_F32_WRITE(Iinv_rms, pStandardModel->E3_sf);
    pStandardModel->Iload_rms = SUNS_F32_WRITE(Iload_rms, pStandardModel->E3_sf);
}

void suns_init(void){
    ModbusInit(MB_RTU, SLAVE_ID, 0, BUADRATE, MB_PAR_NONE);
    suns_model_init();
}

void suns_poll(void){
    ModbusPoll();
}


