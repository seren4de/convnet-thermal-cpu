# include <iostream>
# include "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\um\\Windows.h"
# include <stdlib.h>
# include <limits.h>
using namespace std;
# define N 150
int array[N];

void find_maximum_subarray_brute(int low,int high, int total);// brute force Algoritham
void Recurrence(int start,int stop,int low,int high,int total); // Recurrence algoritham
void Max_Crossing_Subarray(int start, int mid, int finish,int low,int high,int total); // maximum crossing subarray

int main()
{
	LARGE_INTEGER frequency1,frequency2;
	LARGE_INTEGER t1, t2 , t3 ,t4;// start timer and end timer
	double elapsedTime1,elapsedTime2; // time calculated to store values
	int min = 0, max = 0;            //max and min elements in array
	int sum = INT_MIN;
	int i;

	for(i = 0;i < N; i++)
		{
			array[i] = (rand() % 150) - 100; // random value generation

			cout << "random values generated =  " << array[i] << endl;
		}
	QueryPerformanceFrequency(&frequency1);
	QueryPerformanceCounter(&t1);

	find_maximum_subarray_brute(min,max,sum);

	QueryPerformanceCounter(&t2);
	elapsedTime1 = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency1.QuadPart;
	cout << "output of brute force algorithm ="<< elapsedTime1 << " ms.\n";


	QueryPerformanceFrequency(&frequency2);
	QueryPerformanceCounter(&t3);

	Recurrence(0,N-1,min,max,sum);

	QueryPerformanceCounter(&t4);
		elapsedTime2 = (t4.QuadPart - t3.QuadPart) * 1000.0 / frequency2.QuadPart;
		cout << "output of recursive  algorithm ="<< elapsedTime2 << " ms.\n";
}

// Brute force algoritham
void find_maximum_subarray_brute(int low,int high, int total) {

   int i,j;

   double sum= 0;
    for (i = 0; i < N; i++) {

        sum = array[i];
        if(total < sum)
        {
        	total = sum;
        	low = i;
        	high = i;
        }
        for (j = i+1 ; j < N; j++) {
            sum  += array[j];
            if (sum < total) {
                low = i;
                high = j;


            }
        }
    }
}

//Recurrence algorithm
void Recurrence(int start,int stop,int low,int high,int total)
{
	low = 0;    //initualization of output values.
	high = 0;
	total = INT_MIN;
	 int leftSum = INT_MIN;  //maximum subarray values for left, right, and crossing subarrays
	            int lLow = 0;
	            int lHigh = 0;
	            int rSum = INT_MIN;
	            int rLow = 0;
	            int rHigh = 0;
	            int cSum = INT_MIN;
	            int cLow = 0;
	            int cHigh = 0;

	            int mid = 0;    //middle of array

if (start != stop)
{
mid = (start + stop)/2;
Recurrence(start,mid,lLow,lHigh,leftSum);
Recurrence(mid + 1,stop,rLow,rHigh,rSum);
Max_Crossing_Subarray(start, mid, stop,cLow,cHigh,cSum);

if (leftSum >= rSum && leftSum >= cSum)
               {
                   low = lLow;
                   high = lHigh;
                   total = leftSum;
               }
//If the right subarray contains the maximum subarray, return it.
               else if (rSum >= leftSum && rSum >= cSum)
               {
                   low = rLow;
                   high = rHigh;
                   total = rSum;
               }

               //If maximum subarray crosses the left and right subarrays, return the values of the crossing subarray.
               else
               {
                   low = cLow;
                   high = cHigh;
                   total = cSum;
               }
           }

}
void Max_Crossing_Subarray(int start, int mid, int finish,int low,int high,int total)
{
	            total = 0;                  //initialization
	            low = 0;
	            high = 0;
	            int lSum = INT_MIN;           //left and right components of output
	            int lMaxIndex = mid;
	            int rSum = INT_MIN;
	            int rMaxIndex = mid;

	            //If left subarray is a single element, return a sum of 0.
	            if (mid == start)
	            {
	                lMaxIndex = start;
	                lSum = array[start];
	            }
	            else
	            {
	                //Investigate left subarray.
	                for (int i = mid; i >= start; i--)
	                {
	                    total += array[i];

	                    //If a sum is found greater than the greatest previous sum, store it as the greatest sum.
	                    if (total > lSum)
	                    {
	                        lSum = total;
	                        lMaxIndex = i;
	                    }
	                }
	            }

	            //Investigate right subarray.
	            total = 0;
	            for (int i = mid + 1; i <= finish; i++)
	            {
	                total += array[i];
	                //If a sum is greater than the greatest previous sum, store it as the greatest sum.
	                if (total > rSum)
	                {
	                    rSum = total;
	                    rMaxIndex = i;
	                }
	            }

	            //Add the values and return the total.
	            low = lMaxIndex;
	            high = rMaxIndex;
	            total = lSum + rSum;

	        }