/*  
  Author : Ajay Manjhi
  mail : ajay963@outlook.com
  Department : Advanced Technology Development Centre, IIT Kharagpur

  IIT Kharagpur
  https://atdc.iitkgp.ac.in
*/

//  class defination
//  array transmission and sort
// recevie array and sort in mega

#include "sort_fn.h"
const int size = 750; // Size of the array
int array[size]; // Array to store random numbers
unsigned long start;
unsigned long end;
int index = 0;

void sendArray(){
    Serial1.write((byte*) array, size*sizeof(int));
    delay(100);
}


void receiveArray(){
    while(Serial1.available()>0){
      Serial1.readBytes((byte*) array, size*sizeof(int));
    }
}

void randomNumberGn(){
// Generate and print the random numbers
  for (int i = 0; i < size; i++) 
    array[i] = random(1, 501); 
}

void printArray(){

  for (int i = 0; i < size; i++) {
    Serial.print(i + 1);
    Serial.print(":");
    Serial.print(array[i]);
    Serial.print(" ");
    if(i%20==0) Serial.print("\n");
  }
}



void setup() {
  Serial.begin(9600); 
  Serial1.begin(9600);

  randomSeed(analogRead(0));
  start = micros();
  randomNumberGn();
  end = micros();
  sendArray();
  Serial.println("success");
  array[0]=0;
}

void loop() {
    Sort sort;
    receiveArray();
    if(array[0]!=0){
      printArray();
      while(1){}
    }
}
 