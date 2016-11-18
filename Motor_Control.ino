/*
 * 
 * On prompt in order to control the arduino running the motor control functions.
 * 
*/
// Constants
const int ForwardPin = 2;     // the number of the pushbutton pin
const int SquarePin = 3;     // the number of the pushbutton pin
const int ledPin1 =  10;      // the number of the LED pin
const int ledPin2 =  11;      // the number of the LED pin

// Variables
int GoForward = 0;         // variable for reading the pushbutton status
int GoSquare = 0;         // variable for reading the pushbutton status

void setup() {
  
  // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(ForwardPin, INPUT);
  pinMode(SquarePin, INPUT);
  
}

void loop() {
  // read the state of the pushbutton value:
  GoForward = digitalRead(ForwardPin);
  GoSquare = digitalRead(SquarePin);

  // check if the pushbutton is pressed.
  if (GoForward == HIGH) {
    digitalWrite(ledPin1, HIGH);

    
    // Forward()

    
    digitalWrite(ledPin1, LOW);
    } 

    // Check If button is pressed
    if (GoSquare == HIGH) {
    digitalWrite(ledPin2, HIGH);
    
    // square()
    
    digitalWrite(ledPin2, LOW);
    }   
}

void forward(){
  // Put "Go Forward" code here
}

void square(){
  // Put "Do a Square Pattern" code here
}

