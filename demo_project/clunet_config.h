/* Name: clunet_config.h
 * Project: CLUNET network driver
 * Author: Alexey Avdyukhin
 * Creation Date: 2012-11-08
 * License: DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 */
 
#ifndef __clunet_config_h_included__
#define __clunet_config_h_included__

/* Device address (0-254) */
#define CLUNET_DEVICE_ID 99

/* Device name */
#define CLUNET_DEVICE_NAME "CLUNET device"

/* Buffer sized (memory usage) */
#define CLUNET_SEND_BUFFER_SIZE 128
#define CLUNET_READ_BUFFER_SIZE 128

/* Pin to send data */
#define CLUNET_WRITE_PORT D
#define CLUNET_WRITE_PIN 4

/* Using transistor? */
#define CLUNET_WRITE_TRANSISTOR

/* Pin to receive data, external interrupt required! */
#define CLUNET_READ_PORT D
#define CLUNET_READ_PIN 2

/* Timer prescaler */
#define CLUNET_TIMER_PRESCALER 64

/* Custom T (T >= 8 && T <= 24). 
 T is frame unit size in timer ticks. Lower - faster, highter - more stable
 If not defined T will be calculated as ~64us based on CLUNET_TIMER_PRESCALER value
*/
 //#define CLUNET_T 8

#if defined(__AVR_ATmega8__) 

  /* Timer initialization */
  #define CLUNET_TIMER_INIT { TCCR2 = (1 << CS22); }

  /* Timer registers */
  #define CLUNET_TIMER_REG TCNT2
  #define CLUNET_TIMER_REG_OCR OCR2

  /* MCU Status Register */
  #define CLUNET_MCU_STATUS_REGISTER MCUCSR

  /* How to enable and disable timer interrupts */
  #define CLUNET_ENABLE_TIMER_COMP { TIFR |= (1 << OCF2); TIMSK |= (1 << OCIE2); }
  #define CLUNET_DISABLE_TIMER_COMP { TIMSK &= ~(1 << OCIE2); }

  /* How to init and enable external interrupt (read pin) */
  #define CLUNET_INIT_INT { MCUCR |= (1 << ISC00); MCUCR &= ~(1 << ISC01); GICR |= (1 << INT0); }

  /* Interrupt vectors */
  #define CLUNET_TIMER_COMP_VECTOR TIMER2_COMP_vect
  #define CLUNET_INT_VECTOR INT0_vect

#elif defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__)

  /* Timer initialization */
  #define CLUNET_TIMER_INIT { TCCR2B = (1 << CS22); }

  /* Timer registers */
  #define CLUNET_TIMER_REG TCNT2
  #define CLUNET_TIMER_REG_OCR OCR2A

  /* MCU Status Register */
  #define CLUNET_MCU_STATUS_REGISTER MCUSR

  /* How to enable and disable timer interrupts */
  #define CLUNET_ENABLE_TIMER_COMP { TIFR2 |= (1 << OCF2A); TIMSK2 |= (1 << OCIE2A); }
  #define CLUNET_DISABLE_TIMER_COMP { TIMSK2 &= ~(1 << OCIE2A); }

  /* How to init and enable external interrupt (read pin) */
  #define CLUNET_INIT_INT { EICRA |= (1 << ISC00); EICRA &= ~(1 << ISC01); EIMSK |= (1 << INT0); }

  /* Interrupt vectors */
  #define CLUNET_TIMER_COMP_VECTOR TIMER2_COMPA_vect
  #define CLUNET_INT_VECTOR INT0_vect

#else
  #error Device type not defined

#endif

#endif /* __clunet_config_h_included__ */
