/*
 * Timer.h
 *
 * Created: 31-01-2022 00:59:09
 *  Author: GUNJAN
 */ 


#ifndef TIMER_H_
#define TIMER_H_

long fcnt_millis;

void timer0_init(void);
void timer1_init(void);
void timer2_init(void);
long milli(void);

void callback (void);


#endif /* TIMER_H_ */