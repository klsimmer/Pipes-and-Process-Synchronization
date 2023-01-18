//
//  main.cpp
//  PA1
//
//  Created by Kaytlin Simmer on 9/10/21.
//  Copyright © 2021 Kaytlin Simmer. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <thread>
#include <algorithm>
#include <stdio.h>
#include <unistd.h>
#include <vector>
using namespace std;

int nthreads;
const int base = 10;
const int segments = 7;


const int segmentDisplay[base][segments] =
{
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};

struct segs
{
    long num;
    int displaySegment[segments];
    segs (int i) : num(i){}
    void printer()
    {
        cout<<num<<" = ";
        for (int i = 0; i < segments; i++)
        {
            cout<<displaySegment[i];
            if (i < segments)
                cout<< " ";
        }
    }
};

void *compute(void *y)
{
    segs *x;
    x = (struct segs*)y;
    for (int i=0; i < segments; i++)
    {
        x -> displaySegment[i] = segmentDisplay[x->num][i];
    }
    return NULL;
}


int main()
{
    //attain input
    long input;
    cin>>input;
    
    //save another instance of the input
    long input2 = input;
    
    //find digits in input to find number of threads needed
    int digits = 0;
    while (input != 0)
    {
        input = input/10;
        digits++;
    }
    
    //a vector with all the digits
    vector<long> digitVect;
    while (input2 > 0)
    {
        digitVect.push_back(input2%10);
        input2/=10;
    }
    reverse(digitVect.begin(), digitVect.end());
    
    //a struct vector of the digits w attached seven segment code
    vector<segs> digitStructs;
    for (int i = 0; i < digits; i ++)
    {
        struct segs newSeg(digitVect.at(i));
        digitStructs.push_back(newSeg);
        
    }
    
    //debugging purposes
 //   for (int i = 0; i < digitVect.size(); i++)
 //   {
 //      cout<<"Digit "<<i+1<<" is "<<digitVect.at(i)<<endl;
//   }
    //end

    
    //create as many threads as digits in the input value
    nthreads = digits;
    pthread_t nums[nthreads];
    
    //debugging purposes
  //  cout<<endl;
 //  cout<<"Beginning of thread loop digits: "<<endl;
    //end
    

    //creating the threads
   for (int i = 0; i < nthreads; i++)
    {

        //debugging purposes
    //    cout<<"Digit "<<i+1<<" is " <<digitVect.at(i)<<endl;
       // end
        if (pthread_create(&nums[i], NULL, compute, &digitStructs.at(i)))
        {
            cout<<"Error creating thread"<<endl;
            exit(-1);
        }
         
    }
    
    //rejoin threads
    for (int i = 0; i < nthreads; i++)
    {
        pthread_join(nums[i], NULL);
    }
    
   
    //print the segments
    for(int i = 0; i < nthreads; i++)
    {
        (digitStructs.at(i)).printer();
        if(i < digitStructs.size() - 1)
        {
          cout << endl;
        }

    }
    cout<<endl;
    pthread_exit(NULL);
    
    return 0;
}
