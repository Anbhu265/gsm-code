//__GSM BASED INDUSTRIAL AUTOMATION __
#include <lpc21xx.h>
#include <string.h>
#include "4bit.h"

void UART0_CONFIG(void);
void UART0_TX(char d);
char UART0_RX(void);
void UART0_STR(char *);
void Conveyor_motor_on(void);
void Conveyor_motor_off(void);
void Pump_on(void);
void Pump_off(void);
void Actuator_on(void);
void Actuator_off(void);
void Emergency_alarm_on(void);
void Emergency_alarm_off(void);
void Industrial_control_one(void);
void Industrial_control_two(void);
void Industrial_control_three(void);
void Industrial_control_four(void);
void Industrial_control_five(void);
void Industrial_control_six(void);
void Industrial_control_seven(void);
void Industrial_control_eight(void);
void Industrial_control_nine(void);
void Industrial_control_ten(void);

void delay_seconds(int second)
{
    T0PR = 15000000 - 1;
    T0TCR = 0x01;
    while (T0TC < second);
    T0TCR = 0x03;
    T0TCR = 0x00;
}

int main()
{
    char m[100];
    char a[50] = "motoron";
    char b[50] = "motoroff";
    char c[50] = "pumpon";
    char d[50] = "pumpoff";
    char e[50] = "actuatoron";
    char f[50] = "actuatoroff";
    char g[50] = "alarmon";
    char h[50] = "alarmoff";
    char *p;
    int k;
    
    // Set up I/O pins for industrial control (e.g., motors, actuators, alarms)
    IODIR0 = 1 << 9 | 1 << 18 | 1 << 19 | 1 << 10 ;
    IOSET0 = 1 << 9 | 1 << 18 | 1 << 19 | 1 << 10 ;
    
    LCD_INIT();
    LCD_CMD(0x80);
    LCD_STR("GSM BASED");
    LCD_CMD(0xc0);
    LCD_STR("INDUSTRIAL AUTOMATION");
    delay_millisecond(1000);

    UART0_CONFIG();
    UART0_STR("at\r\n");
    delay_seconds(2);
    UART0_STR("at+cmgf=1\r\n");
    delay_seconds(2);

start:
    UART0_STR("at+cmgd=1,4\r\n");
    delay_seconds(2);
    UART0_STR("at+cmgs=\"+91*********\"\r\n");
    delay_seconds(2);
    UART0_STR("WAITING FOR INPUT\r\n");
    UART0_TX(0x1A);
    LCD_CMD(0x01); // To clear the display
    LCD_STR("WAIT FOR INPUT");
    delay_seconds(15);
    UART0_STR("at+cmgr=1\r\n");

    for (k = 0; k < 90; k++)
    {
        m[k] = UART0_RX();
    }
    m[k] = NULL;

    p = strstr(m, a);
    if (p != '\0') Industrial_control_one();

    p = NULL;
    p = strstr(m, b);
    if (p != '\0') Industrial_control_two();

    p = NULL;
    p = strstr(m, c);
    if (p != '\0') Industrial_control_three();

    p = NULL;
    p = strstr(m, d);
    if (p != '\0') Industrial_control_four();

    p = NULL;
    p = strstr(m, e);
    if (p != '\0') Industrial_control_five();

    p = NULL;
    p = strstr(m, f);
    if (p != '\0') Industrial_control_six();

    p = NULL;
    p = strstr(m, g);
    if (p != '\0') Industrial_control_seven();

    p = NULL;
    p = strstr(m, h);
    if (p != '\0') Industrial_control_eight();

    goto start;
}

// UART Receive Function
char UART0_RX(void)
{
    while ((U0LSR & (1 << 0)) == 0);
    return U0RBR;
}

// UART Configuration
void UART0_CONFIG(void)
{
    PINSEL0 |= 0x00000005;
    U0LCR = 0x83;
    U0DLL = 97;
    U0DLM = 0;
    U0LCR = 0x03;
}

// UART Transmit Function
void UART0_TX(char d)
{
    while (!(U0LSR & (1 << 5)));
    U0THR = d;
}

void UART0_STR(char *s)
{
    while (*s)
        UART0_TX(*s++);
}

// Conveyor Motor ON
void Conveyor_motor_on(void)
{
    LCD_CMD(0x01); // Clear the display
    LCD_STR("Conveyor ON");
    delay_millisecond(1000);
    IOCLR0 = 1 << 17;
}

// Conveyor Motor OFF
void Conveyor_motor_off(void)
{
    LCD_CMD(0x01); // Clear the display
    LCD_STR("Conveyor OFF");
    delay_millisecond(1000);
    IOSET0 = 1 << 17;
}

// Pump ON
void Pump_on(void)
{
    LCD_CMD(0x01); // Clear the display
    LCD_STR("Pump ON");
    delay_millisecond(1000);
    IOCLR0 = 1 << 18;
}

// Pump OFF
void Pump_off(void)
{
    LCD_CMD(0x01); // Clear the display
    LCD_STR("Pump OFF");
    delay_millisecond(1000);
    IOSET0 = 1 << 18;
}

// Actuator ON
void Actuator_on(void)
{
    LCD_CMD(0x01); // Clear the display
    LCD_STR("Actuator ON");
    delay_millisecond(1000);
    IOCLR0 = 1 << 19;
}

// Actuator OFF
void Actuator_off(void)
{
    LCD_CMD(0x01); // Clear the display
    LCD_STR("Actuator OFF");
    delay_millisecond(1000);
    IOSET0 = 1 << 19;
}

// Emergency Alarm ON
void Emergency_alarm_on(void)
{
    LCD_CMD(0x01); // Clear the display
    LCD_STR("Emergency Alarm ON");
    delay_millisecond(1000);
    IOSET0 = 1 << 21;
}

// Emergency Alarm OFF
void Emergency_alarm_off(void)
{
    LCD_CMD(0x01); // Clear the display
    LCD_STR("Emergency Alarm OFF");
    delay_millisecond(1000);
    IOCLR0 = 1 << 21;
}

void Industrial_control_one(void)
{
    Conveyor_motor_on();
}

void Industrial_control_two(void)
{
    Conveyor_motor_off();
}

void Industrial_control_three(void)
{
    Pump_on();
}

void Industrial_control_four(void)
{
    Pump_off();
}

void Industrial_control_five(void)
{
    Actuator_on();
}

void Industrial_control_six(void)
{
    Actuator_off();
}

void Industrial_control_seven(void)
{
    Emergency_alarm_on();
}

void Industrial_control_eight(void)
{
    Emergency_alarm_off();
}
