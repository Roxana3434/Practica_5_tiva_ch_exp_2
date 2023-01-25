#include "lib/include.h"

extern void Configurar_UART0(void)
{
///////////////////  CONFIGURACIÓN PINES /////////////////////
    // Habilitar RELOJES <UART> y <GPIO> con REGISTROS
    SYSCTL->RCGCUART  = (1<<0);     //Paso 1 (RCGCUART) pag.388 UART/modulo5 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<0);     //Paso 2 (RCGCGPIO) pag.382 Enable clock port A
    
    // (GPIOAFSEL) pag.770 Enable alternate function
    GPIOA_AHB->AFSEL = (1<<1) | (1<<0);
    
    // GPIO Port Control (GPIOPCTL) to assign the UART signals to the appropriate pins
    // PA0-> U0Rx PA1-> U0Tx pag.1808
    GPIOA_AHB->PCTL = (GPIOA_AHB->PCTL&0xFFFFFF00) | 0x00000011;    // (1<<0) | (1<<4); //Indica pin 0 y 1 funcionan como UART pag. 787
    
    // GPIO Digital Enable (GPIODEN) pag.781
    GPIOA_AHB->DEN = (1<<0) | (1<<1);       //PA0 PA1
    
   
   
   
    /////////////////// CONFIGURACIÓN UART /////////////////////
    //UART0 UART Control (UARTCTL) pag.1188 DISABLE!!
    UART5->CTL = (0<<9) | (0<<8) | (0<<0);      // Deshabilito UARTEN, TXE, RXE
    //            RXE       TXE    UARTEN (UARTENable)

    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 20,000,000 / (16 * 9600) = 130.2
    UARTFBRD[DIVFRAC] = integer(0.2 * 64 + 0.5) = 14
    */
    UART0->IBRD = 130;
    
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.1172
    UART0->FBRD = 14;
    
    //  UART Line Control (UARTLCRH) pag.1186 Serial parameters such as data length, parity, and stop bit selection are implemented in this register.
    UART0->LCRH = (0x3<<5)|(1<<4);      // 0x3=8 bits, 1<<4=habilito bit de paridad pero solo se emplea con el UART0

    //  UART Clock Configuration(UARTCC) pag.1213
    UART0->CC =(0<<0);
    
    //Disable UART0 UART Control (UARTCTL) pag.1188
    UART0->CTL = (1<<0) | (1<<8) | (1<<9);
    //            RXE       TXE      UARTEN



}

extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART0->FR & (1<<4)) != 0 );      // Regresa el dato
    v = UART0->DR & 0xFF;
    c = v;
    return c;
}
