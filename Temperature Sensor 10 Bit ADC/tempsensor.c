#include<msp430g2553.h>

/*This project was implemented to work with the Energia IDE. It utilizes the built in temperature sensor that comes
with the MSP430G2. To get it to work with your MSP430G2, you can rotate the J3 jumper to 90 degrees to enable the serial monitor
if you are having trouble reading the values.
*/

volatile int temp;    //initialize

void tempInit()
{
    ADC10CTL0=SREF_1 + REFON + ADC10ON + ADC10SHT_3 ; //1.5V ref,Ref on,64 clocks for sample
    ADC10CTL1=INCH_10+ ADC10DIV_3; //temp sensor is at 10 and clock/4
}
int tempOut()
{
    int t=0;
    delay(1000);              //wait 4 ref to settle
    ADC10CTL0 |= ENC + ADC10SC;      //enable conversion and start conversion
    while(ADC10CTL1 & BUSY);         //wait..i am converting..pum..pum..
    t=ADC10MEM;                       //store val in t
    ADC10CTL0&=~ENC;                     //disable adc conv
    return(int) ((t * 27069L - 18169625L) >> 16); //convert and pass
}

void setup(){
  
    Serial.begin(9600);
    temp=0;
    Serial.println("Initial TEMP: ");
    Serial.println(temp); //testing again2
    tempInit();//initialise adc
  
 }
void loop(){
 
   
        delay(500); //wait and set break point
        temp=tempOut();           //read temp
        Serial.println("Testing T: ");
        Serial.println(temp); //testing again
        delay(500);  //wait and set breakpoint
  
  
  }  
