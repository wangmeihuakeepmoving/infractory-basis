#include "stm32f4xx_hal.h"
#include "stdint.h"
#ifndef _SHOOT_CONTROL_H_
#define _SHOOT_CONTROL_H_

extern int rub_flag;//s2-1λ����״̬
extern int shoot_flag;//s2-2λ����״̬

void ShootMotor_Velocity_Control(float TargetShootSpeed);
void BLDC_control(uint8_t s2, uint8_t press_r);
void Fire(uint8_t s2, uint8_t press_l);

#endif
