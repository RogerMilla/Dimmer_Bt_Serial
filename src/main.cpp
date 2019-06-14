#include "mbed.h" 
#include "USBSerial.h" 
#include "PwmOut.h"

PwmOut led(PD_12);//green
USBSerial pc;
char char_Bt;
float pwm_step=0.02;



int main(){

    while(1){
    
        if (pc.readable()) {
            char_Bt = pc.getc();
            if (char_Bt == '+'){
                led = led + pwm_step; 
            }
            else if(char_Bt == '-'){
                led = led - pwm_step;
            }

        }     
    }
}
