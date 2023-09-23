/* Flame sensor interfacing with 8051*/

#include<reg51.h>
#define lcd P3
 
sbit FLAME=P1^0;
 
sbit rs=P2^0; //register select
sbit rw=P2^1; //RW
sbit en=P2^2; //enable
 
void lcd_init();
void cmd(unsigned char);
void dat(unsigned char);
void delay();
void lcd_string(char *s);
 
void main()
{
    lcd_init();
    lcd_string(" FSI ");
    while(1) {
        if(FLAME) {
            cmd(0xc0); //Force cursor to beginning of 2nd line
            lcd_string("NO Flame");
            delay();
        } else {
            cmd(0xc0); // Force cursor to beginning of 2nd line
            lcd_string("Flame Detected");
        }
    }
}
 
void lcd_init()
{
    cmd(0x38); // 2 lines and 5×7 matrix (8-bit mode)
    cmd(0x0e); // Display on, cursor on
    cmd(0x06); // for entry mode
    cmd(0x01); // Clear displays
    cmd(0x80); // Force cursor to beginning of 1st line
}
 
void cmd(unsigned char a)
{
    lcd=a;
    rs=0; // command register selected  input considered as commands
    rw=0; // write command
    en=1;
    delay();
    en=0;
}
 
void dat(unsigned char b)
{
    lcd=b;
    rs=1; // data register selected input considered as data
    rw=0; // write data 
    en=1;
    delay();
    en=0;
}
 
void lcd_string(char *s)
{
    while(*s) {
       dat(*s++);
     }
}
 
void delay()
{
    unsigned int i;
    for(i=0;i<20000;i++);
}