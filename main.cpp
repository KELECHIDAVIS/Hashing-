/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: kboss
 *
 * Created on December 3, 2023, 11:28 AM
 */

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <string>
#include <bits/stdc++.h>
using namespace std;

/*
 * 
 */

unsigned int JSHash(const string& ); 
int binarySearch ( string *  , int, string ); 
int linearSearch ( string * , int , string );
int hashSearch ( list<string>* , int , string ); 

string randString ( int , string&); 
int main(int argc, char** argv) {
    
    const int numChars = 20; // the number of chars per string in arr 
    string letters = "abcdefghijklmnopqrstuvwxyz"; 
    const int N = 20000;  // num of elements 
    
    //first init rando array, original 
    string arr[N];  
    list<string> hashArr[N] ; // array specifically for the hashing lookup; 
    for(int i =0; i<N; i++)
    {
        arr[i] = randString(numChars, letters) ; 
        unsigned int index = JSHash(arr[i]) % N; // index for that specific string ; 
        
        hashArr[index].push_front(arr[i]);  // inserts the certain string there 
    }
    
    
    // for each one of these function imma take a few strings at random from the passed in array and create a few random strings and search the array for all of them 
    
    // first create an array that will hold the strings we are searching for then fill half of it up with strings that are in the array 
    
    const int searchElementsSize = 2500; 
    
    string searchArray[searchElementsSize]; 
    
    for(int i = 0 ; i< searchElementsSize; i++ ){
        
        if( i < searchElementsSize /2 ){
            searchArray[i] = arr[rand()%N]; 
        }else{
            searchArray[i] = randString(numChars, letters); 
        }
        

    }
    
    
    
    // start with linear 
    auto begin = std::chrono::steady_clock::now();
    for(int i = 0 ; i< searchElementsSize ; i++ ){
        linearSearch (arr, N , searchArray[i]); 
    }
    auto end = std::chrono::steady_clock::now();

    std::cout << "Linear Search Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()/1000.0<< " seconds " << std::endl;
    
    
    // now binary 
    //sort array first 
    std::sort(arr, arr+N); 
    
    // now perform bin search and take time 
    begin = std::chrono::steady_clock::now();
    for(int i = 0 ; i< searchElementsSize ; i++ ){
        binarySearch (arr, N , searchArray[i]); 
    }
    end = std::chrono::steady_clock::now();

    std::cout << "Binary Search Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0<< " seconds " << std::endl;
    
    
    // now hashing 
    
  
    begin = std::chrono::steady_clock::now();
    for(int i = 0 ; i< searchElementsSize ; i++ ){
        hashSearch (hashArr, N , searchArray[i]); 
    }
    end = std::chrono::steady_clock::now();

    std::cout << "Hash Search Time = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()/ 1000000000.0<< "  seconds " << std::endl;
    
    return 0;
}


int linearSearch ( string * arr , int size , string targetString )
{
    for(int i = 0 ; i< size ; i++ )
    {
        if(arr[i] == targetString)
        {
            return i ; 
        }
    }
    return -1 ; 
}

int binarySearch ( string * arr , int size , string targetString )
{
    // assuming a sorted array
    
    int start = 0, end = size-1, mid; 
    
    while(start <= end)
    {
        mid = (start +end )/2 ; 
        
        if(arr[mid] >targetString)
        {
            end = mid -1; 
        }else if(arr[mid] <targetString)
        {
            start = mid +1; 
        }else{
            return mid ; 
        }
    }
    
    return -1 ; 
    
}

int hashSearch (list<string> * arr , int size , string targetString){
    int index = JSHash(targetString)%size; 
    
    list<string>::iterator it ; 
    for(it = arr[index].begin(); it!= arr[index].end(); ++it){
        if(*it == targetString)
            return index; 
    }
    
    return -1; // not found 
}

unsigned int JSHash(const std::string& str)
{
   unsigned int hash = 1315423911;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((hash << 5) + str[i] + (hash >> 2));
   }

   return hash;
}

string randString( int size , string& letters){
    string tempString = ""; 
    for(int j = 0 ; j< size ; j++){
            tempString += letters[rand()% 25]; 
    }    
    
    return tempString; 
}
