/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TYPEDEFS_H
#define	XC_HEADER_TYPEDEFS_H
#include "p24FJ128GL302.h"

typedef struct{
    uint8_t ui8Interrupt1ms;
    uint8_t ui8Counter3ms;
    uint8_t ui8Counter7ms;
    uint8_t ui8Counter10ms;
    uint8_t ui8Counter10msBase;
    union{
        uint16_t ui16TimerSchedule;
        struct{
            uint16_t ui16TimerSchedule1ms:1;
            uint16_t ui16TimerSchedule3ms:1;
            uint16_t ui16TimerSchedule7ms:1;
            uint16_t ui16TimerSchedule10ms:1;
            uint16_t ui16TimerSchedule50ms:1;
            uint16_t ui16TimerSchedule100ms:1;
            uint16_t ui16TimerSchedule500ms:1;
            uint16_t ui16TimerSchedule1000ms:1;
        };
    };
} Status_t;

typedef struct{
    uint16_t ui16AdcChannelReference;
    uint16_t ui16AdcChannelNtc;
    int16_t i16AdcChannelDifference;
    uint16_t ui16AdcNewDataAvailable;
} Adc_t;


#endif	/* XC_HEADER_TEMPLATE_H */

