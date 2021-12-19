/*
 * File:   newmainXC16.c
 * Author: slaw
 *
 * Created on April 10, 2021, 12:51 AM
 */

#include "typedefs.h"
#include "configbits.h"
#include "prototypes.h"
#include "controls.h"

/*******************************
 *      Global Variables
 *******************************/
extern const int16_t arri16QTemperatureValues[];
char arrchString[] = defString;
Status_t xScheduleStatus;
Adc_t xAdcStatus;
uint8_t ui8TrapErrorStatus;

/*****************************
 * 
 * Send Data to Poti using SPI 16-bit
 * 
 *****************************/
uint16_t ui16SpiCommunicatePoti(uint8_t ui8Command, uint8_t ui8Data){
    uint16_t ui16ReceivedData;

    SPI1CON1Lbits.SPIEN= 0;
    SPI1CON1Lbits.MODE = 1;        
    SPI1CON1Lbits.SPIEN= 1;        // Enable 16-bit Mode
    
    defSpiCsPoti(0);
    vWaitCycles(defSpiCsWaitCycles);
    
    SPI1BUFL = ((uint16_t)ui8Command)<<8|ui8Data;
    while(SPI1STATLbits.SPIBUSY);
    ui16ReceivedData = SPI1BUFL;
    defSpiCsPoti(1);
    
    return ui16ReceivedData;
}
/*****************************
 * 
 * Send Data to Poti using SPI 16-bit
 * 
 *****************************/
uint8_t ui8SpiCommunicatePoti(uint8_t ui8Command){
    uint16_t ui16ReceivedData;
    
    SPI1CON1Lbits.SPIEN= 0;
    SPI1CON1Lbits.MODE = 0;        
    SPI1CON1Lbits.SPIEN= 1;        // Enable 8-bit Mode
    
    defSpiCsPoti(0);
    vWaitCycles(defSpiCsWaitCycles);
    
    SPI1BUFL = ui8Command;
    while(SPI1STATLbits.SPIBUSY);
    ui16ReceivedData = SPI1BUFL;
    defSpiCsPoti(1);
    
    return (uint8_t)(ui16ReceivedData);
}

/*****************************
 * 
 * Show Character on Segment
 * 
 *****************************/
void vSetSegmentCharacter(uint8_t ui8SegmentCharacter, uint8_t ui8SelectSegment){
    defDisableSegments();
    defResetSegmentBars();
    
    if(ui8SegmentCharacter&0x80){
        defSetBarDP();
    }
    
    switch(ui8SegmentCharacter&0x7F){
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
    
    defEnableSegment(ui8SelectSegment);
}
/*****************************
 * 
 * Initialize Hardware
 * 
 *****************************/
void vInitHardware(){
   // Gpio Configuration
   //--------------------------------
    TRISG = 0x0000;   // RG7 In     D
                      // RG8 In     E
    TRISB = 0x0003;   // RB15 In
                      // RB14 In
                      // RB10 In 
                      // RB5 In  SDI 
                      // RB4 Out SCK
                      // RB0 In Analog IN2
                      // RB1 In Analog IN1
    TRISE = 0x0000;   // RE0 In G
                      // RE1 In F
                      // RE2 In DP
                      // RE3 In C
    TRISC = 0xC000;   // RC15 In A
                      // RC14 Out SDO
                      // RC13 Free
                      // RC12 Out CS
    TRISF = 0x0000;   // RF1  In  B
    ANSE = 0x0000;     
    ANSB = 0x0003;    // RB0 and RB1 analog inputs
    ANSG = 0x0000;

    //- Pin remapping
    RPOR9bits.RP18R =  7;           // SDI (SDO1. uc -> Poti)
    RPOR14bits.RP28R = 8;           // SCK (SCK1. uc -> Poti)
    RPINR20bits.SDI1R = 37;         // SDO(SDI1. uc <- Poti)
            
    // Clear Configurations
    //---------------------------------
    defDisableSegments();           // Bars
    defResetSegmentBars();          // Segments
    defSpiCsPoti(1);                // Cs
    
    RCON = 0x0000;                              // Clear "Reset cause"
    ui8TrapErrorStatus = 0;                     // Clear "Trap Error cause"
    xAdcStatus.ui16AdcNewDataAvailable = 0;     // Clear Adc Data Flag
    xScheduleStatus.ui16TimerSchedule = 0x0000; // Clear Timer Flags
    
    // Spi
    //--------------------------------
    SPI1CON1Lbits.SPIEN = 0;        // Disable Spi
    SPI1CON1Lbits.ENHBUF = 0;       // Standard Buffer
    SPI1CON1Lbits.DISSDO = 0;       // Sdo controlled by module
    SPI1CON1Lbits.DISSDI = 0;       // Sdi controlled by module
    SPI1CON1Lbits.DISSCK = 0;       // Sck controlled by module
    SPI1CON1Lbits.CKE = 1;          // Sample at rising edge
    SPI1CON1Lbits.CKP = 0;          // Idle High(MODE 0,0)
    SPI1CON1Lbits.MODE = 1;         // 16-bit Mode
    SPI1CON1Hbits.AUDEN = 0;        // cont. 8-bit Mode
    SPI1STATLbits.SPIROV = 0;       // Clear Offerflow
    
    SPI1BRGL = 0x000A;              // Set  Baud: Fpb/(2*(SPI1BRG+1))
 
    SPI1CON1Lbits.MSTEN = 1;        // Master Mode
    SPI1CON1Lbits.SPIEN = 1;

    // Adc: Smallest Clock: 300ns = 3.3Mhz
    // if FOSC is default FRC(8Mhz)/2 = 4 Mhz. ADC-Clock =  2/FOSC = 2Mhz. 
    // ((12*1/2000000 + 16*1/2000000)*16) -> Total Time 2.2 us for 16 samples
    //--------------------------------      
    AD1CSSL = 0x03;                  // Channel AN0 and Channel AN1
    AD1CON1bits.SSRC = 0x07;         // Trigger
    AD1CON3bits.SAMC = 0x0F;         // 16 tads for sampling
    AD1CON2bits.SMPI = defAdcSampleCount-1;  // After 2 samples
    AD1CON2bits.CSCNA = 1;
    AD1CON1bits.MODE12 = 1;          // 12-bit
    AD1CON1bits.FORM = 0x00;         // Absolute result
    AD1CON1bits.ADON = 1;            // Enable Adc

    // Timer1
    //--------------------------------
    T1CON = 0x0200;
    PR1 = 32;
    IEC0 = 0x2008;                   // Enable Timer Interrupt T1IE
    T1CONbits.TCS = 1;
    T1CONbits.TECS = 2;
    T1CONbits.TON = 1;
    INTCON2 = 0x8000;                // Enable Global Interrupts
}

/*******************************
 *      Main
 *******************************/
int main(void) {
    int32_t i32Temperature;
    int32_t i32DifferenceX;
    int32_t i32DifferenceY;
    uint8_t ui8Index;
    uint8_t ui8SelectSegment = 0;
    uint8_t ui8SegmentShiftDirection = 0;
    uint8_t ui8CharacterOffset = 0;

    // Initialization
    vInitHardware();
    while(1){
        
        // Scheduler: Set Scheduler Bits
        //-----------------------------------------
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
        //-------------------------------------------------------
        // 7-Segment: Character rolling
        if(xScheduleStatus.ui16TimerSchedule500ms){
            if(ui8SegmentShiftDirection){
                ui8CharacterOffset = (ui8CharacterOffset-1);
                if(ui8CharacterOffset == 0){
                    ui8SegmentShiftDirection =~ui8SegmentShiftDirection;
                }
            }else{
                ui8CharacterOffset = (ui8CharacterOffset+1);
                if(ui8CharacterOffset == (sizeof(defString)-1-3)){
                    ui8SegmentShiftDirection =~ui8SegmentShiftDirection;
                }
            }
            
        }
        if(xScheduleStatus.ui16TimerSchedule100ms){
             //ui16SpiCommunicateWithPoti((0x00<<defSpiAddressShift)|defSpiCommandWriteMask|defSpiCommandCmdErrorMask,1);
             ui16SpiCommunicatePoti((0x04<<defSpiAddressShift)|defSpiCommandReadMask, 0xFF);

            //ui16SpiCommunicateWithPoti((0x05<<defSpiAddressShift)|defSpiCommandReadMask|defSpiCommandCmdErrorMask,1);
        }
        
        // 7-Segment: Time multiplex
        if(xScheduleStatus.ui16TimerSchedule1ms){
            //vSetSegmentCharacter(arrchString[ui8SelectSegment+ui8CharacterOffset],ui8SelectSegment);
            ui8SelectSegment =(ui8SelectSegment+1)%3;
        }
        
        // Fetch Adc: Synchronized on new data
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
                    
                // When region found interpolate between two values
                if(xAdcStatus.i16AdcChannelDifference<arri16QTemperatureValues[ui8Index]){
                    
                    // Interpolation: y = y0 + (x-x0)*(y1-y0)/(x1-x0)
                    i32DifferenceX = (int32_t)(arri16QTemperatureValues[ui8Index]-arri16QTemperatureValues[ui8Index-1]);
                    i32DifferenceY = ((int32_t)(defQStart + ui8Index*defQStep)<<10)  -  ((int32_t)(defQStart + (ui8Index-1)*defQStep)<<10);               // Multiply by 1024
                    i32Temperature = (i32DifferenceY*(xAdcStatus.i16AdcChannelDifference-arri16QTemperatureValues[ui8Index-1]));
                    i32Temperature /= i32DifferenceX;
                    i32Temperature +=((int32_t)(defQStart + (ui8Index-1)*defQStep)<<10);        
                    i32Temperature >>=6;        // Lower 4 bits symbolize fixed point
                    
                    //vFormatTemperatureIntoBuffer(arrchString, 0, i32Temperature);   
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
    if(IFS0bits.T1IF){
      IFS0bits.T1IF = 0;                // Clear timer interrupt flag
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

/****************************
 *      Oscillator Fail Trap
 ****************************/
void __attribute__((interrupt,no_auto_psv)) _OscillatorFail(void){
    INTCON1bits.OSCFAIL = 0;
    ui8TrapErrorStatus = 1;
}

/****************************
 *      Address Error Trap
 ****************************/
void __attribute__((interrupt,no_auto_psv)) _AddressError(void){
    INTCON1bits.ADDRERR = 0;
    ui8TrapErrorStatus = 2;
}

/****************************
 *      Stack Error Trap
 ****************************/
void __attribute__((interrupt,no_auto_psv)) _StackError(void){
    INTCON1bits.STKERR = 0;
    ui8TrapErrorStatus = 3;
}

/****************************
 *      Math Error Trap
 ****************************/
void __attribute__((interrupt,no_auto_psv)) _MathError(void){
    INTCON1bits.MATHERR = 0;
    ui8TrapErrorStatus = 4;
}

/****************************
 *      NVM Error Trap
 ****************************/
void __attribute__((interrupt,no_auto_psv)) _NVMError(void){
    ui8TrapErrorStatus = 5;
    
}

/****************************
 *      General Error Trap
 ****************************/
void __attribute__((interrupt,no_auto_psv)) _GeneralError(void){
    ui8TrapErrorStatus = 6;
}