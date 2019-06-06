#include "mbed.h" 
#include "USBSerial.h" 
#include "PwmOut.h"

PwmOut led(PD_12);//green
DigitalOut myleds[]={(PD_13), (PD_14),(PD_15)};// orange, red, blue
enum states{ORANGE, RED, BLUE};
int state;
Ticker ticker;
Timeout timeout;
Timer timer;
USBSerial pc;
char cmd;
float pwm_step=0.02,tblink=0.1,tread=1;

void blink();

int main(){
    wait(10);
    pc.printf("type + to increase and - to decrease LED intensity\n");

    while(1){
    
        if (pc.readable()) {
            cmd = pc.getc();
            if (cmd == '+'){
                led = led + pwm_step;
                myleds[ORANGE] = 0;
                state = BLUE;
                myleds[state] = 1;
                timeout.attach(&blink,tblink);
            }
            else if(cmd == '-'){
                led = led - pwm_step;
                myleds[BLUE] = 0;
                state = ORANGE;
                myleds[state] = 1;
                timeout.attach(&blink,tblink); 
            }
            else{
                myleds[ORANGE] = 0;
                myleds[BLUE] = 0;
            }

        }     
    }
}

void blink(){
    myleds[state] = !myleds[state];
}