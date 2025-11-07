/* 
 * File:   main.c
 * Author: user
 *
 * Created on 2025. studenoga 06, 14:03
 */
#include <xc.h>
#include <stdio.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000UL
#include "lcd.h"

#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

void mcu_init(void){
    OSCCONbits.IRCF = 0b110;
    OSCCONbits.SCS = 0b10;
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    SSPCONbits.SSPEN = 0;
    RCSTA = 0;
    TXSTA = 0;
}

void main(void){
    mcu_init();
    lcd_init();
    
    lcd_clear();
    lcd_setCursor(0, 1);
    lcd_string("Test");
    lcd_setCursor(1, 4);
    lcd_string("123456789");
    
    while(1){}
}