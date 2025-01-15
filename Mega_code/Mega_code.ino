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

// parameters
const int sizeUNO = 750; // size of the array for uno
const int sizeMega = 2000; // size of the array for Mega

// baud rates
const unsigned long commPORT = 9600;
const unsigned long serialPORT = 9600;

const int total = sizeUNO + sizeMega;
int arrayM[sizeMega + sizeUNO]; // Array to store random numbers

unsigned long start = 0;
unsigned long end = 0;
int index = 0;

void sendArray(){
    int array[sizeUNO]; // Temp array for split

    for(int i=sizeMega;i< total;i++)
    array[i-sizeMega]=arrayM[i];

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
    arrayM[i]=array[i-sizeMega];
}

void randomNumberGn(){
// Generate and print the random numbers
  for (int i = 0; i < (sizeUNO + sizeMega); i++) 
    arrayM[i] = random(1, 501); 
}

void printArray(const int arrP[],int size){

  for (int i = 0; i < size; i++) {
    Serial.print(i + 1);
    Serial.print(":");
    Serial.print(arrP[i]);
    Serial.print(" ");
    if(i%20==0) Serial.print("\n");
  }
}

// specify the number of lines of space
void someSpace(const int n){
  for(int i=0;i<n;i++)
  Serial.print("\n");
}

void setup() {
  Serial.begin(serialPORT); 
  Serial1.begin(commPORT);

  randomSeed(analogRead(0));
  start = micros();
  randomNumberGn();
  end = micros();
  printArray(arrayM,total);
  delay(10);
  sendArray();
  Serial.println("success");
  arrayM[sizeMega]=0;
}

void loop() {
    Sort sort;
    receiveArray();
    if(arrayM[sizeMega]!=0){
      
      someSpace(2);
      Serial.println("Array After partial sorted by UNO");
      printArray(arrayM,total);

      start = micros();
      sort.quickSort(arrayM,0,(sizeUNO + sizeMega)-1);
      end = micros();
      
      someSpace(2);
      Serial.print("Sort time : ");
      Serial.print((end-start)/1000);
      Serial.print("ms");
      
      someSpace(4);
      Serial.println("Final sorted array");
      printArray(arrayM,total);
      while(1){}
    }
}