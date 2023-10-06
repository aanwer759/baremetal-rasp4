#pragma once

void uart_init();
char uart_recv();
void uart_send (char c);
void uart__send_string (char *str);

