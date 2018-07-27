/*
 * utilities.h
 *
 *  Created on: Jul 21, 2018
 *      Author: ragashe
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

float forward_euler(float x_old, float tx, float fx_old);                                                                       // Forward Euler Integration
float backward_euler(float y_old, float ty, float fy_new, float y_sat_max, float y_sat_min);                                    // Backward Euler Integration
float trapezoidal_rule(float z_old, float tz, float fz_old, float fz_new, float Ki_z, float z_sat_max, float z_sat_min);        // Trapezoidal(Tustin) Integration, Adam-Moulton Family, Implicit Method
float controller_saturation(float sat_max, float sat_min, float variable_value);                                                // Controller Output Saturation
float parks_transform_d(float alpha_value, float beta_value, float cos_value_d, float sin_value_d);                             // Parks Transformation for d component
float parks_transform_q(float alpha_value, float beta_value, float cos_value_q, float sin_value_q);                             // Parks Transformation for q component
float inverse_parks_transform_alpha(float d, float q, float cos_value_d, float sin_value_d);                                    // Inverse Parks Transformation for d component
float inverse_parks_transform_beta(float d, float q, float cos_value_d, float sin_value_d);                                     // Inverse Parks Transformation for q component
void init_sogi_filter(float Ts, float w, float k);
float update_sogi_filter_alpha(float Vgrid);                                                                                    // SOGI filter update for alpha component
float update_sogi_filter_beta(float Vgrid);                                                                                     // SOGI filter update for beta component
#endif /* UTILITIES_H_ */
