#include "gpio.h"
#include "utils.h"
#include "peripherals/aux1.h"
#include "mini_uart.h"

#define TXD 14
#define RXD 15

void uart_init(){
    gpio_pin_set_func(TXD,GFALT5);
    gpio_pin_set_func(RXD,GFALT5);

    gpio_pin_enable(TXD);
    gpio_pin_enable(RXD);
    
    REGS_AUX->enable = 1;
    REGS_AUX->mu_control=0;
    REGS_AUX->mu_ier = 0;
    REGS_AUX->mu_lcr=3;
    REGS_AUX->mu_mcr =0;

#if RPI_VERSION == 3
 REGS_AUX->mu_baud_rate = 270; // 115200 @ 250 MHz
#endif

#if RPI_VERSION == 4
 REGS_AUX->mu_baud_rate = 541; // 115200 @ 500 MHz
#endif

REGS_AUX->mu_control=3;

uart_send("\r");
uart_send("\n");
uart_send("\n");
}

void uart_send(char c){
    while (!(REGS_AUX->mu_lsr & 0x20));
    REGS_AUX->mu_io =c;
}

char uart_recv(){
    while (!(REGS_AUX->mu_lsr & 1));
    return REGS_AUX->mu_io & 0xFF;
}

void uart_send_string(char *str){
    while (*str){
        if (*str == '\n'){
            uart_send("\r");
        }
        uart_send(*str);
        str++;
    }
}