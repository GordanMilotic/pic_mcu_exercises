#include <xc.h>
#define _XTAL_FREQ 4000000UL

// --- CONFIG za PIC16F627 (bez WRT!) ---
/*#pragma config FOSC = INTOSCIO  // interni RC, RA6/RA7 kao I/O
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config MCLRE = ON
#pragma config CPD = OFF
#pragma config CP = OFF*/

void main(void)
{
    TRISB = 0x00;    // svi PORTB kao izlazi
    PORTB = 0x00;

    while (1) {
        PORTBbits.RB0 = 1;  __delay_ms(500);
        PORTBbits.RB0 = 0;  __delay_ms(500);
    }
}
