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
    gpio_t gasDetector; // es una estructura que matchea los regstros de hardware, lo crea st
    // la direccion de base es 0x3800ul se llama rcc_base
    //definido en mbed-os/targets/TARGET_STM/TARGET_STM32F4/STM32Cube_FW/CMSIS/stm32f407xx.h
    // segun qué micro tiene elige una libreria u otra
    
    gpio_init_in(&gasDetector, PF_15);
    // usanod c++ es mas comodo ya que no debemos crear un puntero para cada pin

    //DigitalOut alarmLed(LED1);
    gpio_t  alarmLed;
    gpio_init_out(&alarmLed, PB_0);

    //gasDetector.mode(PullDown);
    mode(&gasDetector,PullDown); // pulldown enmascara un bit
    // este metodo esta en mbed-os/drivers/source/DigitalIn.cpp
    // la macro esta en mbed-os/targets/TARGET_STM/pinmap.c

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
