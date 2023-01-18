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

void *printer(void *y)
{
    long x;
    x = (long)y;
    //sleep(1);
    
    //debugging purposes
  /*  cout<<"THREAD STARTED"<<endl;
    cout<<"PASSED IN: "<<x<<endl;
    pthread_exit(NULL); */
     
    
    if (x == 0)
    {
        cout<<"0 = 1 1 1 1 1 1 0"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 1)
    {
        cout<<"1 = 0 1 1 0 0 0 0"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 2)
    {
        cout<<"2 = 1 1 0 1 1 0 1"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 3)
    {
        cout<<"3 = 1 1 1 1 0 0 1"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 4)
    {
        cout<<"4 = 0 1 1 0 0 1 1"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 5)
    {
        cout<<"5 = 1 0 1 1 0 1 1"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 6)
    {
        cout<<"6 = 1 0 1 1 1 1 1"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 7)
    {
        cout<<"7 = 1 1 1 0 0 0 0"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 8)
    {
        cout<<"8 = 1 1 1 1 1 1 1"<<endl;
        pthread_exit(NULL);
    }
    else if (x == 9)
    {
        cout<<"9 = 1 1 1 1 0 1 1"<<endl;
        pthread_exit(NULL);
    }
     pthread_exit(NULL);
     
    
}


int main()
{
    //attain input
    long input;
    cin>>input;
    
    //used for threads
  //  int idk;
    //the waiting part
 //   pthread_attr_t attr;
 //   void *status;
    
    //save another instance of the input
    long input2 = input;
    
    //find digits in input to find number of threads needed
    int digits = 0;
    while (input != 0)
    {
        input = input/10;
        digits++;
    }
    
    //debugging purposes
 //   cout<<endl;
 //   cout<<"number of digits detected: "<<digits<<endl;
    //end
    
    //a vector with all the digits
    vector<long> digitVect;
    while (input2 > 0)
    {
        digitVect.push_back(input2%10);
        input2/=10;
    }
    reverse(digitVect.begin(), digitVect.end());
    
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
    //part of the waiting
    
  //  pthread_attr_init(&attr);
//   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //creating the threads
   // long lvectnum;
   for (int i = 0; i < nthreads; i++)
    {
    //    lvectnum = (long)digitVect.at(i);
        
        //debugging purposes
    //    cout<<"Digit "<<i+1<<" is " <<digitVect.at(i)<<endl;
       // end
        if (pthread_create(&nums[i], NULL, printer, (void *)digitVect.at(i)))
        {
            cout<<"Error creating thread"<<endl;
            exit(-1);
        }
       
     //   idk =  pthread_join(nums[i], &status);
        
   /*     if (idk)
        {
                cout << "Error" << idk << endl;
                exit(-1);
             } */
         
    }
    
    for (int i = 0; i < nthreads; i++)
    {
        pthread_join(nums[i], NULL);
    }
    
    pthread_exit(NULL);
    
    return 0;
}
