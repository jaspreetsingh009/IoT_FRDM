#include "mbed.h"
#include "TextLCD.h"
//#include "MMA8451Q.h"

Serial pc(USBTX, USBRX); //Comment if RF interface is used
//Serial pc(PTE22, PTE23); //uncomment for RF interface
InterruptIn select(D4); //To change LCD display
TextLCD lcd(PTC7, PTC0, PTC6, PTC5, PTC4, PTC3); //16x2 LCD 4-bit mode

AnalogIn adc0(A0);
AnalogIn adc1(A1);
AnalogIn adc2(A2);
AnalogIn adc3(A3);
AnalogIn adc4(A4);
AnalogIn adc5(A5);

//#define MMA8451_I2C_ADDRESS (0x1d<<1)  
//MMA8451Q acc(PTE25, PTE24, MMA8451_I2C_ADDRESS);

//Global variables
volatile int txEnable = 0; 
char  inData[10];
float pwmPeriod = 0.01; //100Hz default
int   chSel = 0;
int   InCh[6];
//int   InAc[3];

void setPWM(int channel, int value) //set "channel" in PWM mode with duty = "value"
{
    float duty = ((float) value)/100;
    switch(channel)
    {
        case 0  :  PwmOut ch0(LED1);  ch0 = 1 - duty; ch0.period(pwmPeriod);
                   break;
        case 1  :  PwmOut ch1(LED2);  ch1 = 1 - duty; ch1.period(pwmPeriod);
                   break;
        case 2  :  PwmOut ch2(LED3);  ch2 = 1 - duty; ch2.period(pwmPeriod);
                   break;
        case 3  :  PwmOut ch3(D5);    ch3 = duty;     ch3.period(pwmPeriod);
                   break;
        case 4  :  PwmOut ch4(PTE29); ch4 = duty;     ch4.period(pwmPeriod);
                   break;
        case 5  :  PwmOut ch5(PTE21); ch5 = duty;     ch5.period(pwmPeriod);
                   break;
        //Define more outputs here. No need to change UI code upon addition of outputs
        default :  break;
    }
}

void switchIO(int channel, int value) //Turn "channel" ON/OFF
{
    int signal = value;
    
    switch(channel)
    {
        case 0  :  DigitalOut ch0(LED1);  ch0 = 1 - signal;
                   break;
        case 1  :  DigitalOut ch1(LED2);  ch1 = 1 - signal;
                   break;
        case 2  :  DigitalOut ch2(LED3);  ch2 = 1 - signal;
                   break;
        case 3  :  DigitalOut ch3(D5);    ch3 = signal;
                   break;
        case 4  :  DigitalOut ch4(PTE29); ch4 = signal;
                   break;
        case 5  :  DigitalOut ch5(PTE21); ch5 = signal;
                   break;
        //Define more outputs here
        default :  break;
    }
}

void setFreq(int channel, int value) //Set PWM Frequency
{
    pwmPeriod = (float) (1.0/value);
}

void setSystemIO(char inData[10]) //Set a channel in PWM/ON-OFF Mode based on RX data string
{
    int status = 0;
    int i = 1;
    int channelID = 0;
    
    while(inData[i] != 'X')
    {
        int temp = inData[i] - '0';
        channelID = channelID*10 + temp;
        i++;
        if(i>6) { return; }
    }
        
    int j = i + 1;
        
    while(inData[j] != '\r') {
        int num = inData[j] - '0';
        status = status*10 + num;
        j++;
        if(j>10) { return; }
    }
    
    switch(inData[0]) { //Call functions based in received commands
        case 'p' :  setPWM(channelID, status);
                    break;
        case 's' :  switchIO(channelID, status);
                    break;
        case 'f' :  setFreq(channelID, status);
                    break;
        default  :  break;
    }
}

void Rx_interrupt() //UART Receive (RX) Interrupt Function
{ 
    pc.gets(inData, 10);
    if(inData[0] == 'Z') { 
        txEnable = 1;  //Enable UART TX
        return;
    }
    
    else if(inData[0] == 'z') {
        txEnable = 0;  //Disable UART TX
        return;
    }
    
    setSystemIO(inData);
}

void switchLCDch() {
    chSel++;
    if(chSel > 5 ){  //Replace '5' by '6' if acc module is used
        chSel = 0;
    }
}

int main() {
    pc.attach(&Rx_interrupt, Serial::RxIrq);
    select.fall(&switchLCDch);
    
    while (1) {          
        char str[50];
        InCh[0] = adc0.read_u16();
        InCh[1] = adc1.read_u16();
        InCh[2] = adc2.read_u16();
        InCh[3] = adc3.read_u16();
        InCh[4] = adc4.read_u16();
        InCh[5] = adc5.read_u16();
        //InAc[0] = (int)(acc.getAccX()*100);
        //InAc[1] = (int)(acc.getAccY()*100);
        //InAc[2] = (int)(acc.getAccZ()*100);
        
        lcd.cls();
        
        switch(chSel) {
            case 0  : lcd.printf("ADC0: %u %\nLDR\n", (int)((InCh[1]*100)/65535)); 
                      break;
            case 1  : lcd.printf("ADC1: %u %\nHI300\n", (int)((InCh[2]*100)/65535));
                      break;
            case 2  : lcd.printf("ADC3: %u C\nLM35\n", (int)((InCh[3]*330)/65535));
                      break;
            case 3  : lcd.printf("ADC4: %u %\nMQ2 Gas Sensor\n", (int)((InCh[4]*100)/65535));
                      break;
            case 4  : lcd.printf("ADC5: %u mV\nVoltage\n", (InCh[5]*3300)/65535);
                      break;
            case 5  : lcd.printf("ADC6: %u mV\nVoltage\n", (InCh[0]*3300)/65535);                   
                      break;
           // case 6  : lcd.printf("X:%d,Y:%d,Z:%d\nAccelerometer\n",InAc[0],InAc[1],InAc[2]);
             //         break;
            default : break;
        }  
        
        if(txEnable == 1) {
            sprintf (str,"%dA,%dB,%dC,%dD,%dE,%dF\n",InCh[1],InCh[2],InCh[3],InCh[4],InCh[5],InCh[0]);s
        
            int i = 0;
            while(str[i] != '\n') {
                pc.putc(str[i]);
                i++;
            }
            pc.putc('\n');
        }
        
        wait(0.1);
    }
}
