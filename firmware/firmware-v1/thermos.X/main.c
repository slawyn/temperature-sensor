/*
 * File:   newmainXC16.c
 * Author: slaw
 *
 * Created on April 10, 2021, 12:51 AM
 */

#include "config.h"
#include "typedefs.h"

/*****************************
 * 
 * Segments
 * 
 *****************************/

// Multiple of 2's
#define defAdcSampleCount (8*2)
#define defAdcSampleShift 3

#define defResetSegmentBars(){LATE |= 0x000F; LATG|=0x0180; LATB |=0x0030;}
#define defDisableSegments() LATB = (LATB&0x3BFF);
#define defSetBarA() LATE = (LATE)& ~0x0004;   // A Bar
#define defSetBarB() LATE = (LATE)& ~0x0008;   // B Bar
#define defSetBarC() LATG = (LATG)& ~0x0080;   // C Bar
#define defSetBarD() LATB = (LATB)& ~0x0010;   // D Bar
#define defSetBarE() LATB = (LATB)& ~0x0020;
#define defSetBarF() LATE = (LATE)& ~0x0002;
#define defSetBarG() LATE = (LATE)& ~0x0001;  
#define defSetBarDP() LATG = (LATG)& ~0x0100;


#define defSegment0() LATB =(PORTB&0x3BFF)|0x8000;
#define defSegment1() LATB =(PORTB&0x3BFF)|0x4000;
#define defSegment2() LATB =(PORTB&0x3BFF)|0x0400;



/*****************************
 * 
 * Globals
 * 
 *****************************/
void vSetSegmentCharacter(uint8_t ui8SegmentCharacter, uint8_t ui8SelectSegment){
    
    defDisableSegments();
    defResetSegmentBars();
    
    if(ui8SegmentCharacter&0x80){
        defSetBarDP();
    }
    
    ui8SegmentCharacter &=0x7F;
    switch(ui8SegmentCharacter){
        case '0':
            defSetBarA();
            defSetBarB();
            defSetBarC();
            defSetBarD();
            defSetBarE();
            defSetBarF();
            break;
        case '1':
            defSetBarB();
            defSetBarC();
            break;
        case 'Z':
        case '2':
            defSetBarA();
            defSetBarB();
            defSetBarG();
            defSetBarE();
            defSetBarD();
            break;
        case '3':
            defSetBarA();
            defSetBarB();
            defSetBarC();
            defSetBarD();
            defSetBarG()
            break;
        case '4':
            defSetBarB();
            defSetBarC();
            defSetBarF();
            defSetBarG()
            break;
        case 'S':
        case '5':
            defSetBarA();
            defSetBarC();
            defSetBarD();
            defSetBarF();
            defSetBarG()
            break;
        case '6':
            defSetBarA();
            defSetBarC();
            defSetBarD();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case '7':
            defSetBarA();
            defSetBarB();
            defSetBarC();
            break;
        case '8':
            defSetBarA();
            defSetBarB();
            defSetBarC();
            defSetBarD();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case '9':
            defSetBarA();
            defSetBarB();
            defSetBarC();
            defSetBarD();
            defSetBarF();
            defSetBarG();
            break;
        case 'A':
            defSetBarA();
            defSetBarB();
            defSetBarC();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case 'c':
            defSetBarD();
            defSetBarE();
            defSetBarG();
            break;
        case 'C':
            defSetBarA();
            defSetBarD();
            defSetBarF();
            defSetBarE();
            break;
        case 'E':
            defSetBarA();
            defSetBarD();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case 'F':
            defSetBarA();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case 'G':
            defSetBarA();
            defSetBarC();
            defSetBarD();
            defSetBarF();
            defSetBarE();
            break;
        case 'H':
            defSetBarB();
            defSetBarC();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case 'n':
            defSetBarA();
            defSetBarB();
            defSetBarC();
            defSetBarF();
            defSetBarE();
            break;
        case 'b':
            defSetBarC();
            defSetBarD();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case 'd':
            defSetBarB();
            defSetBarC();
            defSetBarD();
            defSetBarE();
            defSetBarG();
            break;
        case 'p':
            defSetBarA();
            defSetBarB();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case 'h':
            defSetBarC();
            defSetBarF();
            defSetBarE();
            defSetBarG();
            break;
        case 'j':
            defSetBarB();
            defSetBarC();
            defSetBarD();
            break;
        case 'L':
            defSetBarD();
            defSetBarF();
            defSetBarE();
            break;
        case '-':
            defSetBarG();
            break;
        case '_':
            defSetBarD();
            break;
        case ' ':
            break;
        default:
            break;
    }
    
    switch(ui8SelectSegment){
        case 0:
            defSegment0();
            break;
        case 1:
            defSegment1();
            break;
        case 2:
            defSegment2();
            break;
    }
}

void vInitHardware(){

    TRISG = 0x0000;   // RG7 RG8 Input
    TRISB = 0x0003;   // Config RB15 RB14 and RB10 as Output RB5 RB4 Input
    TRISE = 0x0000;   // RE0 - RE3 Input

    ANSE = 0x0000;     
    ANSB = 0x0003;    // RB0 and RB1 analog inputs
    ANSG = 0x0000;
    
    // Adc: Smallest Clock: 300ns = 3.3Mhz
    // if FOSC is default FRC(8Mhz)/2 = 4 Mhz. ADC-Clock =  2/FOSC = 2Mhz. 
    // ((12*1/2000000 + 16*1/2000000)*16) -> Total Time 2.2 us for 16 samples
    //--------------------------------      
    AD1CSSL = 0x03;                 // Channel AN0 and Channel AN1
    
    AD1CON1bits.SSRC = 0x07;        // Trigger
    AD1CON3bits.SAMC = 0x0F;        // 16 tads for sampling
    
    AD1CON2bits.SMPI = defAdcSampleCount-1;           // After 2 samples
    AD1CON2bits.CSCNA = 1;
    AD1CON1bits.MODE12 = 1;         // 12-bit
    AD1CON1bits.FORM = 0x00;        // Absolute result
    AD1CON1bits.ADON = 1;           // Enable Adc

    
    // Timer1
    //--------------------------------
    T1CON = 0x0200;
    PR1 = 32;
    IEC0 = 0x2008;      // Enable Timer Interrupt T1IE
    T1CONbits.TCS = 1;
    T1CONbits.TECS = 2;
    T1CONbits.TON = 1;
    INTCON2 = 0x8000;   // Enable Global Interrupts
    
    defDisableSegments();
    defResetSegmentBars();
}


char chIntToChar(uint8_t ui8Number){
    if(ui8Number<0x0A){
        return '0'+(ui8Number);
    }else if (ui8Number == 0x0B){
        return 'b';
    }else if (ui8Number == 0x0D){
       return 'd';
    }else{
       return  'A'+((ui8Number-0xA));
    }
}


void vFormatIntIntoBuffer(char arrchBuffer[], uint8_t ui8Offset,uint16_t ui16Value){
    uint8_t ui8TempShift = 4*3;
    uint8_t ui8Temp;
    while(ui8TempShift){
        ui8TempShift-=4;
        ui8Temp = (ui16Value>>ui8TempShift)&0x000F;
        
        arrchBuffer[ui8Offset] = chIntToChar(ui8Temp);
        ui8Offset++;
    }
}


void vFormatTemperatureIntoBuffer(char arrchBuffer[], uint8_t ui8Offset, int16_t i16Temperature){
    uint8_t ui8InitialOffset;
    uint8_t ui8Index;
    uint8_t ui8Length;
    uint8_t ui8Fractional;
    uint16_t ui16Absolute;
    const uint8_t ui8Base = 10;
    char chTemp;
    
    ui8InitialOffset = ui8Offset;
    
    if(i16Temperature<0){
        arrchBuffer[ui8Offset++] = '-';
        i16Temperature = (~i16Temperature)+1;
    }
    
    // Split into Fractional
    ui16Absolute = i16Temperature>>4;
    ui8Fractional = i16Temperature&0x0F;
    
    // Convert to Base
    while (ui16Absolute > 0)
    {
        arrchBuffer[ui8Offset++] = chIntToChar(ui16Absolute % ui8Base);
        ui16Absolute /= ui8Base;
    }
    
    // Reverse Result
    ui8Length = ui8Offset-ui8InitialOffset;
    for (ui8Index = 0; ui8Index < ui8Length/2; ui8Index++)
    {
        chTemp = arrchBuffer[ui8InitialOffset+ui8Index];
        arrchBuffer[ui8InitialOffset+ui8Index] = arrchBuffer[ui8Offset-ui8Index-1];
        arrchBuffer[ui8Offset-1-ui8Index] = chTemp;
    }
    arrchBuffer[ui8Offset-1]|=0x80;         // Add dot
    arrchBuffer[ui8Offset++]=chIntToChar(ui8Fractional*ui8Base/16);
    arrchBuffer[ui8Offset++]='c';
}

/*******************************
 *      Global Variables
 *******************************/
#define defQStart  -55
#define defQStep     5
extern int16_t arri16QTemperatureValues[];

#define defString "    "
char arrchString[] = defString;
Status_t xScheduleStatus;
Adc_t xAdcStatus;

/*******************************
 *      Main
 *******************************/
int main(void) {
    int32_t i32Temperature;
    int32_t i32DifferenceX;
    int32_t i32DifferenceY;
    char chCharacter;
    uint8_t ui8Index;
    uint8_t ui8LoopForever = 1;
    uint8_t ui8SelectSegment = 0;
    uint8_t ui8SegmentShiftDirection = 0;
    uint8_t ui8CharacterOffset = 0;


   
    
    // Init Hardware
    vInitHardware();
    
    xAdcStatus.ui16AdcNewDataAvailable = 0;
    while(ui8LoopForever){
        
        // Scheduler: Set Scheduler Bits
        if( xScheduleStatus.ui8Interrupt1ms){
            xScheduleStatus.ui8Interrupt1ms = 0;
            
            ++xScheduleStatus.ui8Counter3ms;
            ++xScheduleStatus.ui8Counter7ms;
            ++xScheduleStatus.ui8Counter10ms;
            
            if(xScheduleStatus.ui8Counter3ms == 3){
                xScheduleStatus.ui8Counter3ms = 0;
                xScheduleStatus.ui16TimerSchedule3ms = 1;
            }
            
            if(xScheduleStatus.ui8Counter7ms == 7){
                xScheduleStatus.ui8Counter7ms = 0;
                xScheduleStatus.ui16TimerSchedule7ms = 1;
            }
            
            if(xScheduleStatus.ui8Counter10ms == 10){
                xScheduleStatus.ui8Counter10ms = 0;
                xScheduleStatus.ui16TimerSchedule10ms = 1;
                ++xScheduleStatus.ui8Counter10msBase;
                
                 if(xScheduleStatus.ui8Counter10msBase%50 == 0){
                    xScheduleStatus.ui16TimerSchedule500ms = 1;
                }
                
                if(xScheduleStatus.ui8Counter10msBase%10 == 0){
                    xScheduleStatus.ui16TimerSchedule100ms = 1;
                }
                if(xScheduleStatus.ui8Counter10msBase%5 == 0){
                    xScheduleStatus.ui16TimerSchedule50ms = 1;
                }
                
               
                
                if(xScheduleStatus.ui8Counter10msBase == 100){
                     xScheduleStatus.ui8Counter10msBase = 0;
                    xScheduleStatus.ui16TimerSchedule1000ms = 1;
                }
            }
            xScheduleStatus.ui16TimerSchedule1ms = 1;
        }
        
        // Scheduled Tasks
        if(xScheduleStatus.ui16TimerSchedule500ms){
            if(ui8SegmentShiftDirection){
                ui8CharacterOffset = (ui8CharacterOffset-1);
                if(ui8CharacterOffset == 0){
                    ui8SegmentShiftDirection =~ui8SegmentShiftDirection;
                }
            }else{
                ui8CharacterOffset = (ui8CharacterOffset+1);
                if(ui8CharacterOffset == sizeof(defString)-3){
                    ui8SegmentShiftDirection =~ui8SegmentShiftDirection;
                }
            }
            
        }

        if(xScheduleStatus.ui16TimerSchedule10ms){
            chCharacter = arrchString[ui8SelectSegment+ui8CharacterOffset];
            vSetSegmentCharacter(chCharacter,ui8SelectSegment);
            ui8SelectSegment =(ui8SelectSegment+1)%3;
        }
        
        
        // Synchronized on new data
        if(xAdcStatus.ui16AdcNewDataAvailable){
            xAdcStatus.ui16AdcNewDataAvailable = 0;
            
            xAdcStatus.ui16AdcChannelNtc = 0;
            xAdcStatus.ui16AdcChannelReference = 0;
            for(ui8Index=0;ui8Index<defAdcSampleCount;ui8Index+=2){
                xAdcStatus.ui16AdcChannelNtc += (*((&ADC1BUF0)+ui8Index));
                xAdcStatus.ui16AdcChannelReference += (*((&ADC1BUF1)+ui8Index));
            }

            xAdcStatus.ui16AdcChannelNtc >>= defAdcSampleShift;    
            xAdcStatus.ui16AdcChannelReference >>=defAdcSampleShift;    
            xAdcStatus.i16AdcChannelDifference = xAdcStatus.ui16AdcChannelReference-xAdcStatus.ui16AdcChannelNtc;
            
  
            // Ntc
            // Circuit: 1k  = 3.3k*(1k/(1k+1k)) = 1.65V -> 0x7FF   
            // Precision: 3%  +- 61 dec
            // Linearisierung: Werte -55 bis 70

            for(ui8Index=0; ui8Index<26;++ui8Index){
                    
                // When sector found interpolate between two values
                if(xAdcStatus.i16AdcChannelDifference<arri16QTemperatureValues[ui8Index]){
                    
                    // Interpolation: y = y0 + (x-x0)*(y1-y0)/(x1-x0)
                    i32DifferenceX = (int32_t)(arri16QTemperatureValues[ui8Index]-arri16QTemperatureValues[ui8Index-1]);
                    i32DifferenceY = ((int32_t)(defQStart + ui8Index*defQStep)<<10)  -  ((int32_t)(defQStart + (ui8Index-1)*defQStep)<<10);               // Multiply by 1024
                    i32Temperature = (i32DifferenceY*(xAdcStatus.i16AdcChannelDifference-arri16QTemperatureValues[ui8Index-1]));
                    i32Temperature /= i32DifferenceX;
                    i32Temperature +=((int32_t)(defQStart + (ui8Index-1)*defQStep)<<10);        
                    i32Temperature >>=6;        // Lower 4 bits symbolize fixed point
                    
                    vFormatTemperatureIntoBuffer(arrchString, 0, i32Temperature);   
                    break;
                }
            }


            //vFormatIntIntoBuffer(arrchString,0,xAdcStatus.ui16AdcChannelNtc);
            //vFormatIntIntoBuffer(arrchString,5,xAdcStatus.ui16AdcChannelReference);

        }
        
       
        xScheduleStatus.ui16TimerSchedule = 0x0000;                 // Reset Scheduler flags
    }
    return 0;
}

/****************************
 *      Timer 1 Interrupt
 ****************************/
void  __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void){
    
    // Delete timer interrupt flag
    if(IFS0bits.T1IF){
      IFS0bits.T1IF = 0;
      AD1CON1bits.ASAM = 1;             // Conversion is started on timer interrupt. Conversion is synced with timer.
      ++xScheduleStatus.ui8Interrupt1ms;    
    }
}

/****************************
 *      ADC Interrupt
 ****************************/
void  __attribute__((__interrupt__, no_auto_psv)) _ADC1Interrupt(void){
    if(IFS0bits.AD1IF){
        AD1CON1bits.ASAM = 0;                   // Stop Conversion
        IFS0bits.AD1IF = 0;
        xAdcStatus.ui16AdcNewDataAvailable = 1;
    }
}