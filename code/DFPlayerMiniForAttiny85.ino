#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(0, 1); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
#define BUSY_PIN 4
int busyState = 0;
int prevBusyState = 0;
int totalFiles = 0;
void printDetail(uint8_t type, int value);

void setup()
{
  
  pinMode( BUSY_PIN, INPUT_PULLUP );
  mySoftwareSerial.begin(9600);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true);
  }

  totalFiles = myDFPlayer.readFileCounts();

  
  myDFPlayer.volume(25);  //Set volume value. From 0 to 30
  myDFPlayer.randomAll();  //Play the first mp3
//  random(1, totalFiles);
  delay(100);
//  myDFPlayer.play(random(1, totalFiles));
//  myDFPlayer.enableLoop();  //Play the first mp3
//  delay(500);
  myDFPlayer.next();

  // initialise the BUSY states
  busyState = digitalRead( BUSY_PIN );
  prevBusyState = busyState;
  
}

void loop()
{
  
  busyState = digitalRead( BUSY_PIN );
//  static unsigned long timer = millis();
  // has the player BUSY pin changed state?
  if ( busyState != prevBusyState ) {
    // state change - has the player stopped playing?
    if ( busyState == HIGH ) {
      // stopped playing so start next track
      myDFPlayer.next();  
    }
    prevBusyState = busyState;
  }
//  delay( 500 );
  
//  if (millis() - timer > 10000) {
//    timer = millis();
//    myDFPlayer.next();  //Play next mp3 every 3 second.
//  }
//  
//  if (myDFPlayer.available()) {
//    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
//  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      break;
    case WrongStack:
      break;
    case DFPlayerCardInserted:
      break;
    case DFPlayerCardRemoved:
      break;
    case DFPlayerCardOnline:
      break;
    case DFPlayerPlayFinished:
      break;
    case DFPlayerError:
      switch (value) {
        case Busy:
          break;
        case Sleeping:
          break;
        case SerialWrongStack:
          break;
        case CheckSumNotMatch:
          break;
        case FileIndexOut:
          break;
        case FileMismatch:
          break;
        case Advertise:
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
