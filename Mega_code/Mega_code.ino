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
const int sizeUNO = 750; // size of the array for uno
const int sizeMega = 3000; // size of the array for Mega

int arrayM[sizeMega + sizeUNO]; // Array to store random numbers


unsigned long start;
unsigned long end;
int index = 0;

void sendArray(){
    int array[sizeUNO]; // Temp array for split

    for(int i=sizeMega;i<(sizeUNO + sizeMega);i++)
    array[i]=arrayM[i];

    Serial1.write((byte*) array, sizeUNO*sizeof(int));
    delay(100);
}


void receiveArray(){
    int array[sizeUNO]; // Array to 
    
    while(Serial1.available()>0){
      Serial1.readBytes((byte*) array, sizeUNO*sizeof(int));
    }
    
    // get the array from UNO 
    // and put it from index sizeMega to ( sizeUNO + sizeMega )
    for(int i=sizeMega;i<(sizeUNO + sizeMega);i++)
    arrayM[i]=array[i];
}

void randomNumberGn(){
// Generate and print the random numbers
  for (int i = 0; i < (sizeUNO + sizeMega); i++) 
    arrayM[i] = random(1, 501); 
}

void printArray(){

  for (int i = 0; i < (sizeUNO + sizeMega); i++) {
    Serial.print(i + 1);
    Serial.print(":");
    Serial.print(arrayM[i]);
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
  arrayM[sizeMega]=0;
}

void loop() {
    Sort sort;
    receiveArray();
    if(arrayM[sizeMega]!=0){
      printArray();
      sort.quickSort(arrayM,0(sizeUNO + sizeMega)-1)
      printArray();
      while(1){}
    }
}