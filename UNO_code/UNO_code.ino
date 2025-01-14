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


const int size = 750; // Size of the array
int array[size]; // Array to store received elements
int index = 0; // Index to keep track of where to store the received data
unsigned long start;
unsigned long end;

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
  Serial.begin(9600); 
  Serial1.begin(9600);
    delay(200);
}

void loop() {
    Sort sort;
    receiveArray();
    if(array[0]!=0){
      sort.bubbleSort(array,size);
      delay(10);
      sendArray();
      delay(10);
      printArray();
      while(1){}
    }
}


