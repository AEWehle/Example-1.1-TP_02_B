#include "mbed.h"
#include "arm_book_lib.h"

int main()
{
    DigitalIn gasDetector(D2);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);

    alarmLed = OFF;

    while (true) {
        if ( gasDetector == ON ) {
            printf("%s\n", "se detecta gas, alarma sonando");
            alarmLed = ON;
        }
        
        if ( gasDetector == OFF ) {
            printf("%s\n", "no se detecta gas, alarma apagada");
            alarmLed = OFF;
        }
    }
}
