/*
* Name: Anuram Thirumoli
* Date: October 10th, 2021
* Language: Arduino Uno
* Project: R3 - Software Task 1
* Description: Program written for R3 Software Task 1. Displays a number between
*              0 and 99 to two 7-segment displays based on a potentiometers
*              output/position. Uses multiplexing instead of using two CD4511
*              7-segment decoders.
*/


//Function Prototypes (see function headers below)
void display_number(int num, int display_pin); //displays a number on a 7-segment display

  
//Global Variables
//CD4511 decoder pins to display numbers on 7-segment display
const int decoder_pins[] = {11, 10, 9, 8};

//common pins for the two 7-segment displays which show potentiometer value
//(tens column and ones column)
const int tens_disp_pin = 2;
const int ones_disp_pin = 3;


void setup() {
  //sets 7-segment pins to output LOW so any signals to the CD4511 decoder
  //are not displayed prematurely
  pinMode(tens_disp_pin, OUTPUT);
  pinMode(ones_disp_pin, OUTPUT);
  digitalWrite(tens_disp_pin, LOW);
  digitalWrite(ones_disp_pin, LOW);
  
  //sets all the pins for the CD4511 decoder to OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(decoder_pins[i], OUTPUT);
  }
}


void loop() {
  //value ranging from 0-99 set by potentiometer on A0 input
  int pot_range = map(analogRead(A0), 0, 1023, 0, 99);
  
  
  //calculates the digits to display on the two 7-segment display (using the potentiometer range)
  int ones_digit = pot_range % 10;
  int tens_digit = (pot_range - ones_digit) / 10;
  
  //displays the value from 0-99 on the two 7-segment displays
  display_number(tens_digit, tens_disp_pin);
  display_number(ones_digit, ones_disp_pin);
}


/*
* Function Name: display_number
* Return Type: void
* Description: Displays a number from 0-9 to a 7-segment display (can use multiplexing).
* Parameters:
*   int num, the number to display (from 0-9)
*   int display_pin, the pin which the common of the 7-segment display is connected to
*					(for multiplexing purposes)
*/
void display_number(int num, int display_pin) {
  
  //2d array with the binary values for numbers 0-9
  bool num_value[][4] = { 
    {0, 0, 0, 0}, //0
    {0, 0, 0, 1}, //1
    {0, 0, 1, 0}, //2
    {0, 0, 1, 1}, //3
    {0, 1, 0, 0}, //4
    {0, 1, 0, 1}, //5
    {0, 1, 1, 0}, //6
    {0, 1, 1, 1}, //7
    {1, 0, 0, 0}, //8
    {1, 0, 0, 1}  //9
  };
  
  //sets the CD4511 decoder pins to the appropriate binary value
  for (int i = 0; i < 4; i++) {
    digitalWrite(decoder_pins[i], num_value[num][i]);
  }
  
  //sets the 7-segment display to the desired number
  digitalWrite(display_pin, HIGH);
  digitalWrite(display_pin, LOW);
}