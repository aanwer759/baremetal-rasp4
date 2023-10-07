#include "common.h"
#include "mini_uart.h"

void kernel_main(){
    uart_init();
    uart_send_string("From Raspberry PI Bare Metal\n");

    #if RPI_VERSIOn == 3
    uart_send_string("\tFROM Board 3\n");
    #endif
    #if RPI_VERSIOn == 4
    uart_send_string("\tFROM Board 4\n");
    #endif

    uart_send("done \n");

    while(1){
        uart_send(uart_recv());
    }
}