/*
 * File:   helpers.c
 * Author: slaw
 *
 * Created on 13. Juni 2021, 20:37
 */
#include "typedefs.h"

void vWaitCycles(uint8_t ui8Cycles){
    if(ui8Cycles != 0){
        while (ui8Cycles--){}
    }
}


/*****************************
 * 
 * Convert Int to Ascii
 * 
 *****************************/
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

/*****************************
 * 
 * Convert Int to ascii buffer
 * 
 *****************************/
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

/*****************************
 * 
 * Convert Temperature to ascii
 * 
 *****************************/
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
