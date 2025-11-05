#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000UL   // 4mhz interni oscilator jer nemam vanjski

// 
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

//digitalni izlazi, pinovi 22-27
#define LCD_RS PORTBbits.RB6
#define LCD_EN PORTBbits.RB1
#define LCD_D4 PORTBbits.RB2
#define LCD_D5 PORTBbits.RB3
#define LCD_D6 PORTBbits.RB4
#define LCD_D7 PORTBbits.RB5

void lcd_pulse(void) {
    LCD_EN = 1;
    __delay_us(1);
    LCD_EN = 0;
    __delay_us(100);
}

void lcd_send4(uint8_t n) {
    LCD_D4 = (n >> 0) & 1;
    LCD_D5 = (n >> 1) & 1;
    LCD_D6 = (n >> 2) & 1;
    LCD_D7 = (n >> 3) & 1;
    lcd_pulse();
}

void lcd_cmd(uint8_t n) {
    LCD_RS = 0;
    lcd_send4(n >> 4);
    lcd_send4(n & 0x0F);
    if (n == 0x01 || n == 0x02)
        __delay_ms(2);
    else
        __delay_us(50);
}

void lcd_data(uint8_t n) {
    LCD_RS = 1;
    lcd_send4(n >> 4);
    lcd_send4(n & 0x0F);
    __delay_us(50);
}

void lcd_goto(uint8_t row, uint8_t col) {
    // 20x4 / 16x2 kompatibilno:
    // 0: 0x00, 1: 0x40, 2: 0x14, 3: 0x54
    uint8_t row_addr[] = {0x00, 0x40, 0x14, 0x54};
    if (row > 3) row = 3;
    lcd_cmd(0x80 | (row_addr[row] + col));
}

void lcd_puts(const char *s) {
    while (*s) lcd_data(*s++);
}

void lcd_init(void) {
    OSCCONbits.IRCF = 0b110;   // 4 MHz
    OSCCONbits.SCS  = 0b10;    // interni RC

    ANSEL  = 0x00;             // svi analogni izlazi off
    ANSELH = 0x00;

    SSPCONbits.SSPEN = 0;      // I2C/SPI off
    RCSTA = 0;                 // UART off
    TXSTA = 0;

    TRISB = 0x00;              // svi RB postavi kao izlaz
    PORTB = 0x00;

    __delay_ms(20);         
    
    lcd_send4(0x03); __delay_ms(5);
    lcd_send4(0x03); __delay_us(150);
    lcd_send4(0x03); __delay_us(150);
    lcd_send4(0x02); __delay_us(150);

    lcd_cmd(0x28);
    lcd_cmd(0x0C);             // display ON, cursor OFF
    lcd_cmd(0x01);             // clear
    lcd_cmd(0x06);             // entry mode
    __delay_ms(2);
}
// 
void main(void) {
    lcd_init();
    lcd_goto(0, 2);
    lcd_puts("Inductance meter");
    lcd_goto(1, 0);
    lcd_puts("Inductance: 33.10mH");
    lcd_goto(2, 0);
    lcd_puts("--------------------");
    lcd_goto(3, 3);
    lcd_puts("Gordan Milotic");

    while (1) {
      
    }
}





/*
#include <xc.h>
#define _XTAL_FREQ 4000000UL

#pragma config FOSC = INTOSCIO  // interni RC, RA6/RA7 kao I/O
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config MCLRE = ON
#pragma config CPD = OFF
#pragma config CP = OFF

void main(void)
{
    TRISB = 0x00;    // svi PORTB kao izlazi
    PORTB = 0x00;

    while (1) {
        PORTBbits.RB6 = 1;  __delay_ms(500);
        PORTBbits.RB6 = 0;  __delay_ms(500);
        PORTBbits.RB1 = 1;  __delay_ms(500);
        PORTBbits.RB1 = 0;  __delay_ms(500);
        PORTBbits.RB2 = 1;  __delay_ms(500);
        PORTBbits.RB2 = 0;  __delay_ms(500);
        PORTBbits.RB3 = 1;  __delay_ms(500);
        PORTBbits.RB4 = 0;  __delay_ms(500);
        PORTBbits.RB4 = 1;  __delay_ms(500);
        PORTBbits.RB4 = 0;  __delay_ms(500);
        PORTBbits.RB5 = 1;  __delay_ms(500);
        PORTBbits.RB5 = 0;  __delay_ms(500);
    }
}
*/