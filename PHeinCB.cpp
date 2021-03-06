#include<iostream>
#include<ctime>
#include<vector>
#include<cstdlib>
#include<math.h>

using namespace std;

void Add(vector<int> &rannum) // function for add random numbers into the vector rannum.
{
	int num=0; // temporary variable to add random number into the vector.
	
	bool flag=true; // to determine if the vector already has the number.
		 
		
	num=rand()%10; // generating random number.
				
	for(int i=0; i<rannum.size(); i++)
	{
		if(rannum.at(i)!=num)
		{

			flag=true; // if the new random number is not already in the vector.
			
		}
		
		else
		{
							
			flag=false; // if the new random number is already in the vector.
				
			break; // breaking out of the loop.
				
		}
	}
	
	if(flag==true) // deciding if the new random number should be added or not.
	{
	
	rannum.push_back(num); // inserting new random number into the vector.
	
	}
}

int main()
{
	time_t start,end; // time object instances.
	
	srand((unsigned)time(0)); // seed for random number.
	
	int minutes,seconds; // to measure elapsed time.
	
	vector<int> rannums; // vector for random numbers
	
	vector<int> inputnum;// vector for numbers from user
	
	int tries=0,bulls=0,cows=0,number, temp;
		
	while(rannums.size()<4) // add digits into the vector until it has 4 unique digits.
	{
		
	 Add(rannums);
	
	}
	
	time(&start); // starts the timer
	
	do // start this iteration until the player manages to get 4 bull scores.
	{	
		tries++;// logging the number of tries.
	
		bulls=0;
			
		cows=0;// resetting bulls and cows scores for the next iteration.
			
		cout<<"Enter a 4 digit number(unique digits): "; // user prompt
		
		cin>>number;
		

		for(int i=3; i>=0; i--) // adding user input into a vector inputnum
		{
			temp=pow(10,i);
					
			inputnum.push_back( (number/temp)% 10 );
		}
			
		for(int j=0;j<4;j++) // checking if the user input matches the random number.
		{
			
			if(rannums.at(j)==inputnum.at(j))
			{
				
				bulls++; // if the user input has the right digit and the right position.
				
			}
			else
			{
				for(int k=0; k<4; k++)
				{
					if(rannums.at(j)==inputnum.at(k))
					{
						
						cows++; // if the user input has the right digit but the wrong position.
					
					}
				}
			}
			
		}
		
		cout<<"bulls = "<<bulls<<" and cows = "<<cows<<endl; // showing cows and bulls scores.
		
		inputnum.clear(); // clearing the input vector for next input.
		
	} while(bulls<4);
	
	time(&end); // ends the timer
	
	minutes=difftime(end,start)/60;// converting time into minutes.
	
	seconds=(int)(difftime(end,start))%60; // converting time into seconds.
	
	cout<<"You guessed it in "<<tries<<" tries, taking "<< minutes<<" minutes and "<<seconds<<" seconds\n";//showing the time  and the number of attempts the player has taken to complete the game. 
	
}