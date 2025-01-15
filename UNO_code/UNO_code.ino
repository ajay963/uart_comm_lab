/*  
  Author : Ajay Manjhi
  mail : ajay963@outlook.com
  Department : Advanced Technology Development Centre IIT Kharagpur

  IIT Kharagpur
  https://atdc.iitkgp.ac.in

  Receiver Arduino Code
 */
// dont use serial for print purpose
// rather use serial only for communication
// remove all the print statements
#include "sort_fn.h"
#include <SoftwareSerial.h>
SoftwareSerial Serial1(10, 9); // RX, TX

// baud rates
const unsigned long commPORT = 9600;
const unsigned long serialPORT = 9600;

unsigned long start = 0;
unsigned long end = 0;

const int size = 750; // Size of the array
int array[size]; // Array to store received elements
int index = 0; // Index to keep track of where to store the received data


void printArray(){

  for (int i = 0; i < size; i++) {
    Serial.print(i + 1);
    Serial.print(":");
    Serial.print(array[i]);
    Serial.print(" ");
    if(i%20==0) Serial.print("\n");
  }
}

void sendArray(){
    Serial1.write((byte*) array, size*sizeof(int));
    delay(100);
}

void receiveArray(){
    while(Serial1.available()>0){
      Serial1.readBytes((byte*) array, size*sizeof(int));
    }
}


void setup() {
  Serial.begin(serialPORT); 
  Serial1.begin(commPORT);
    delay(200);
}

void loop() {
    Sort sort;
    receiveArray();
    if(array[0]!=0){
      start = micros();
      sort.bubbleSort(array,size);
      end = micros();

      delay(10);
      sendArray();
      delay(100);

      Serial.print("Sort time : ");
      Serial.print((end-start)/1000);
      Serial.print("ms\n");

      printArray();
      while(1){}
    }
}


