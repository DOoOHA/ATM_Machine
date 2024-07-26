/*
 * TIMERS.h
 *
 * Created: 2/8/2024 3:04:12 AM
 *  Author: LENOVO
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

void Timer0_CTC_Init_Interrupt(void);
void Timer0_wave_nonPWM(void);
void Timer0_wave_FastPWM(void);
void Timer0_wave_PhaseCorrectPWM(void);
void Timer2_OverFlow_Init_Interrupt(void);
void Timer1_wave_FastPWM(double value);

#endif /* TIMERS_H_ */