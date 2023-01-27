#include "lib/include.h"

//Experimento 2
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
 * junto con el generador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
 * cuya frecuencia sea de 50Hz con tres potenciometros variar el ciclo de trabajo
 * para controlar la posicion de tres servos sg90 o otros.
 *
 */

int main(void)
{
    //Variables 
    uint16_t Result[3];
    uint16_t duty[3];
   /* uint16_t Result0[3];
    uint16_t duty0[3];
    uint16_t Result1[3];
    uint16_t duty1[3];
    uint16_t Result2[3];
    uint16_t duty2[3];*/

    //Funciones para configuración 
    Configurar_PLL(); 
    //Configurar_UART0();
    Configura_Reg_PWM0(8);
    Configura_Reg_ADC0();

    while(1) 
    {
        //Se llama a la función para leer y convertir valores del ADC
       ADC0_InSeq2(Result,duty);
      
       /* ADC0->PSSI |= (1<<0) | (1<<1) | (1<<2);  //por procesador
        //canal 1
        while((ADC0->RIS&0x01)==0){};  //siii
        Result0[0] = ADC0->SSFIFO0&0xFFF; // En el FIFO0 se almacenan las muestras, por lo que se lee, pag 860 siiii
        duty0[0] = (Result0[0]*50000)/4096; ///SIIIII 20ms con la config. de él esta mueve bien el servo por todos los 180° pero con un pedacito del potenciometro con comb de 45000 y CTL = (0<<0)
        //modificar ciclo de trabajo */
        PWM0->_0_CMPB = duty[0];

        //Canal 2
      /*while((ADC0->RIS&0x02)==0){}; 
      Result1[1] = ADC0->SSFIFO1&0xFFF;
      duty1[1] = (Result1[1]*50000)/4096;//SII*/
        PWM0->_1_CMPA = duty[1];

        //Canal 8
       /*while((ADC0->RIS&0x04)==0){};
       Result2[2] = ADC0->SSFIFO2&0xFFF;
       duty2[2] = (Result2[2]*50000)/4096;*/
       PWM0->_2_CMPA = duty[2];
    }
}
