/* 
 * File:   newmain.c
 * Author: Shoumik Dey
 *
 * Created on 10 September, 2020, 12:03 PM
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

// PIC16F628A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
//#define _XTAL_FREQ 4000000
#include <xc.h>
int counter = 8;
int counterTarget = 8;

void toggleLED(void) {
    if(PORTAbits.RA0 == 1){
        PORTAbits.RA0 = 0;
    }
    else{
        PORTAbits.RA0 = 1;
    }
//    PORTAbits.RA0 = !PORTAbits.RA0;
//    PORTAbits.RA1 = !PORTAbits.RA1;

}

void __interrupt() interruptServiceRoutine(void) {

    if (INTCONbits.T0IF == 1) {
        counter++;
        if (counter == counterTarget) {
            toggleLED();
        }
        INTCONbits.T0IF = 0;

    }

        if (INTCONbits.INTF == 1) {
            counterTarget *= 2;
            INTCONbits.INTF = 0;
            
            }

}

int main(int argc, char** argv) {
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b111;
    TRISA = 0x00;
    TRISB = 0xFF;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.INTE = 1;
    OPTION_REGbits.INTEDG = 1;
    INTCONbits.T0IE = 1;
    OPTION_REGbits.T0CS = 0;

    CMCON = 0x07;
    PORTA = 0x00;
    //    while (1) {
    //        
    //        PORTA = PORTA << 1;
    //  __delay_ms(500);
    //        PORTA = PORTA >> 1;
    //        __delay_ms(500);
    //        CLRWDT();
    //        
    //    
//    while(1){
//        toggleLED();
//        __delay_ms(500);
//        toggleLED();
//        __delay_ms(500);
//    }



    return (EXIT_SUCCESS);
}






