#include <wixel.h>
#include <usb.h>
#include <usb_com.h>
#include <stdio.h>

int32 CODE param_blink_period_ms = 500;

uint32 lastToggle = 0;

void updateLeds()
{
    usbShowStatusWithGreenLed();

    LED_YELLOW(0);

    if (getMs() - lastToggle >= param_blink_period_ms/2)
    {
        LED_RED(!LED_RED_STATE);
        lastToggle = getMs();
    }
}

void main()
{
    systemInit();
    usbInit();

    P0_5 = 0;
    P0DIR |= (1 << 5);
    delayMs(1); P0_5 = 1;
    delayMs(1); P0_5 = 0;
    delayMs(1); P0_5 = 1;
    delayMs(1); P0_5 = 0;

    while(1)
    {
        boardService();
        updateLeds();
        usbComService();
    }
}
