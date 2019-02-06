//solution:
// input at first stage are store in the variable "input",
// after 6 digits are entry, it goes to stage2, and repeat the process but store input into varaible input2 
// if two input match, it goes back to stage 1, otherwise keep looking instage 2

//set up cup speed
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>   		//registrs lib
#include <util/delay.h> 	//delay lib
#include <avr/interrupt.h> 	// interrupts lib
#include <avr/power.h> 		//For power testing
#include <avr/sleep.h>  	// For power saving

//Define all pins needed for this projects
#define LED_PIN0 (1 << PB0)
#define LED_PIN1 (1 << PB1)
#define LED_PIN2 (1 << PB2)
#define KEY_PIN0 (1 << PB3)
#define KEY_PIN1 (1 << PB4)

// variables declaration 
uint8_t input= 0b00000000;      // stage 1 input
int size=0;    			//stage 1 input count
int stages = 1;
uint8_t input2= 0b00000000;     //stage 2 input
int count = 0;                  //stage 2 input count

int main(void) {

// Set the pin change mask so that PB4 n PB3 triggers interrupt
PCMSK = (1 << PCINT4)|(1 << PCINT3);
// enable pin change interrupts
GIMSK = (1 << PCIE);
// Enable interrupts
sei();

//stage machine below
while(1){
  switch(stages){
//first stage##############program stage/unlock#############
case 1:{
while(stages==1){
shineYellow();
shineGreen();}
}
//second stage#############lock stage######################
case 2:{
while(stages==2){shineRed();}
}
//third stage#############reset stage######################
case 3:{
while(stages==3){shineYellow();stages=1;input=0;size=0;count=0;}
} 
 }

    }
//stage machine above	
	}



// Modules

//shine some freshly jucy Green light
int shineGreen(void){
DDRB = LED_PIN1|LED_PIN0;      //set direction: UPPER TWO PB as output stage, and Bottom PB as input statge 
PORTB = LED_PIN0;              //Light up Green
}


//shine some sunny burnish yellow light
int shineYellow(void){

DDRB = LED_PIN1|LED_PIN0;     //set direction: UPPER TWO PB as output stage, and Bottom PB as input statge 
PORTB = LED_PIN1;            //Light up Yellow
}


//shine some clamly salty blue light
int shineBlue(void){

DDRB = LED_PIN1|LED_PIN2;   //set direction: LOWER TWO PB as output stage, and Upper PB as input statge 
PORTB = LED_PIN1;           //Light up Blue
}


//shalalala, shalalala in the evening.
int shineRed(void){
DDRB = LED_PIN1|LED_PIN2;  //set direction: LOWER TWO PB as output stage, and Upper PB as input statge 
PORTB = LED_PIN2;          //Light up Red
}


//flash yellow
int flashYellow(int x){
TCCR0B = 0B101;                  // PRESCALE BY 1024, TCCR0B: TIMMER CONTROL
uint8_t flashcycle = TCNT0 +0Xf; //TCNT0 : COUNT REGISTER
while(x!=0){      		// X is the amount of time it flash
while(flashcycle==TCNT0){
shineYellow();
_delay_ms(50);
x-=1;
}
PORTB = 0;

	}
		}



//interupts

ISR(PCINT0_vect) {
cli();               	//debouncing logic in one line of code.

//stage 2 interrupt code####################match input2 with input after 6 digits entry to input2#######
if(stages ==2 ){          // when key0 is press
if((PINB&KEY_PIN0)==0){
input2 = (input2|0);	 //store 0 to input2 and shift left,makeroom for next entry
input2 = (input2 << 1);
shineBlue();              // confirm user input
_delay_ms(500);           //debouncing logic               
count+=1;                  // increase input count by 1;            
}

if((PINB&KEY_PIN1)==0){    //when key1 is press
input2 = (input2|1);       // same logic below as key0
input2 = (input2 << 1);     
shineBlue();
_delay_ms(500);
count+=1;
}if(count==6){              //check if stage2 input match with stage1 input
if(input2==input){
stages=3;                     // go unlock stage if two input matches;
	}else{flashYellow(5);input2=0;count=0;} //reset stage2 input and count otherwise
}
}

//stage 1 interrupt code#################################6 digits entry to input ####################
if(stages==1){               
if((PINB&KEY_PIN0)==0){       //key0 is press;    
input = (input|0);             //store 0 to input and shift left, makeroom for next entry
input = (input << 1);         // shift left, makeroom for next entry
shineBlue();                  //confirm user input
_delay_ms(500);               //debounce logic
size+=1;                      //increase input size by 1;
}
if((PINB&KEY_PIN1)==0){        //when key1 is press
input = (input|1);              //same logic below as key0
input = (input << 1);
shineBlue();
_delay_ms(500);
size+=1;
}if(size==6){
stages=2;
}

	}









//################### enable interrupt before exist
sei();
		}



