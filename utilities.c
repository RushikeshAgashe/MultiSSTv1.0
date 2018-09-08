/*
 * utilities.c
 *
 *  Created on: Jul 21, 2018
 *      Author: ragashe
 */

#include "utilities.h"

float SOGI_C1 = 0.0f;
float SOGI_C2 = 0.0f;
float SOGI_C3 = 0.0f;
float SOGI_C4 = 0.0f;

float forward_euler(float x_old, float tx, float fx_old)

{
    float x_new = 0;
    x_new = x_old + (tx*fx_old);
    return x_new;
}

float backward_euler(float y_old, float ty, float fy_new,float y_sat_max,float y_sat_min)

{
    float y_new = 0;
    y_new = y_old + (ty*fy_new);
        if (y_new > y_sat_max)
        {
            y_new = y_sat_max;
        }
        if (y_new < y_sat_min)
        {
            y_new = y_sat_max;
        }
    return y_new;
}

float trapezoidal_rule(float z_old, float tz, float fz_old, float fz_new, float Ki_z, float z_sat_max, float z_sat_min)

{
    float z_new = 0;
    z_new = z_old + (0.5)*Ki_z*tz*(fz_old + fz_new);
        if (z_new > z_sat_max)
        {
            z_new = z_sat_max;
        }
        if (z_new < z_sat_min)
        {
            z_new = z_sat_min;
        }
    return z_new;
}

float controller_saturation(float sat_max, float sat_min, float variable_value)

{
    if (variable_value > sat_max)
    {
        variable_value = sat_max;
    }
    if (variable_value < sat_min)
    {
        variable_value = sat_min;
    }
    return variable_value;
}

float parks_transform_d(float alpha_value, float beta_value, float cos_value_d, float sin_value_d)

{
    float d_component = 0;
    d_component = alpha_value*cos_value_d + beta_value*sin_value_d;
    return d_component;
}

float parks_transform_q(float alpha_value, float beta_value, float cos_value_q, float sin_value_q)

{
    float q_component = 0;
    q_component = alpha_value*sin_value_q - beta_value*cos_value_q;
    return q_component;
}

float inverse_parks_transform_alpha(float d, float q, float cos_value_d, float sin_value_d)

{
    float alpha_component = 0;
    alpha_component = d*cos_value_d + q*sin_value_d;
    return alpha_component;
}

float inverse_parks_transform_beta(float d, float q, float cos_value_d, float sin_value_d)

{
    float beta_component = 0;
    beta_component = -q*cos_value_d + d*sin_value_d;
    return beta_component;
}

void init_sogi_filter(float Ts, float w, float k){
    SOGI_C1 = 1.0/(1.0 + k*w*Ts + (w*w)*(Ts*Ts));
    SOGI_C2 = k*w*Ts + 2;
    SOGI_C3 = k*w*Ts;
    SOGI_C4 = k*(w*w)*(Ts*Ts);
}

float update_sogi_filter_alpha(float Vgrid){
    static float vgrid[2] = {0., 0.};
    static float vgrid_alpha[3] = {0., 0., 0.};
    vgrid[0] = Vgrid;
    vgrid_alpha[0] = SOGI_C1*(vgrid_alpha[1]*(SOGI_C2) - vgrid_alpha[2] + (vgrid[0] - vgrid[1])*SOGI_C3);
    vgrid_alpha[2] = vgrid_alpha[1];
    vgrid_alpha[1] = vgrid_alpha[0];
    vgrid[1] = vgrid[0];
    return vgrid_alpha[0];
}

float update_sogi_filter_beta(float Vgrid){
    static float vgrid[1] = {0.};
    static float vgrid_beta[3] = {0., 0., 0.};
    vgrid[0] = Vgrid;
    vgrid_beta[0] = SOGI_C1*(vgrid_beta[1]*(SOGI_C2) - vgrid_beta[2] + vgrid[0]*SOGI_C4);
    vgrid_beta[2] = vgrid_beta[1];
    vgrid_beta[1] = vgrid_beta[0];
    return vgrid_beta[0];
}

float ramp_change(float value, float target, float ramp_rate, float sample_rate){
    float tolerance = 0.001;
    if (fabs(target-value) < tolerance) return value;
    if (target-value < 0) ramp_rate *= -1;
    value += (ramp_rate*sample_rate);
    return value;
}
