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

#ifndef CONTROLS_H
#define	CONTROLS_H


/*****************************
 * 
 * Defines
 * 
 *****************************/

// Multiple of 2's
#define defAdcSampleCount (8*2)
#define defAdcSampleShift 3

#define defResetSegmentBars(){ LATE |= 0x000F; LATF |= 0x0002; LATG|=0x0180; LATC |=0x8000;}
#define defSetBarA() LATC = (LATC)& ~0x8000;   
#define defSetBarB() LATF = (LATF)& ~0x0002;   
#define defSetBarC() LATE = (LATE)& ~0x0008;   
#define defSetBarD() LATG = (LATG)& ~0x0080;  
#define defSetBarE() LATG = (LATG)& ~0x0100;
#define defSetBarF() LATE = (LATE)& ~0x0002;
#define defSetBarG() LATE = (LATE)& ~0x0001;  
#define defSetBarDP() LATE = (LATE)& ~0x0004;


#define defDisableSegments() LATB = (LATB|0xC400);
#define defEnableSegment(x) if(x == 0)LATB =(PORTB&0x7FFF); else if(x==1)LATB =(PORTB&0xBFFF); else LATB =(PORTB&0xFBFF);

#define defQStart  -55
#define defQStep     5
#define defString "   8888   "

#define defSpiCsPoti(x) if(x) LATC |= (0x1000); else LATC &= (~0x1000); 
#define defSpiCsWaitCycles            10
#define defSpiAddressShift             4
#define defSpiCommandShift             2
#define defSpiCommandCmdErrorMask   (0x03<<0)
#define defSpiCommandReadMask       (0x03<<defSpiCommandShift)|defSpiCommandCmdErrorMask
#define defSpiCommandWriteMask      (0x00<<defSpiCommandShift)|defSpiCommandCmdErrorMask
#define defSpiCommandIncrementMask  (0x01<<defSpiCommandShift)|defSpiCommandCmdErrorMask
#define defSpiCommandDescrementMask (0x02<<defSpiCommandShift)|defSpiCommandCmdErrorMask


#endif	

