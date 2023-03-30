#include "mbed.h"
#include "arm_book_lib.h"

void mode(gpio_t* gpio ,PinMode pull)
{
    core_util_critical_section_enter();
    gpio_mode(gpio, pull);
    core_util_critical_section_exit();
}

int main()
{
    //DigitalIn gasDetector(D2);
    gpio_t gasDetector;
    gpio_init_in(&gasDetector, PF_15);

    //DigitalOut alarmLed(LED1);
    gpio_t  alarmLed;
    gpio_init_out(&alarmLed, PB_0);

    //gasDetector.mode(PullDown);
    mode(&gasDetector,PullDown);

    //alarmLed = OFF; // off es 0
    gpio_write(&alarmLed, 0);

    while (true) {
        //if ( gasDetector == ON ) {
        if ( gpio_read(&gasDetector)== ON ) {
            printf("%s\n", "se detecta gas, alarma sonando");
            //alarmLed = ON;
            gpio_write(&alarmLed, 1);
        }
        
        //if ( gasDetector == OFF ) {
        if ( gpio_read(&gasDetector)== OFF ) {
            printf("%s \n", "no se detecta gas, alarma apagada");
            //alarmLed = OFF;
            gpio_write(&alarmLed, 0);
            //int printf(char *, ...)
        }
    }
}
