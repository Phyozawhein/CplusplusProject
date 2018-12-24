#include<iostream>
#include<cstdlib>
#include<cctype>
#include<chrono>
#include<ctime>
#include<string>

using namespace std;

void CreateRandomStr(string& ranstr) // the function that inserts random digits, characters, and non-alphanumerics into random string
{
	int chance;
	
	string randomchar="abcdefghijklmnopqurstuvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // for random alphabet generation
	
	chance =rand()%100+1;	// chance for alphabet, digit and non-alphanumeric
	
	if( chance >90) // chance for non-alphanumeric 10% out of 20%
	{
		ranstr+='*';	 // non-alphanumeric is inserted in to the randomstring
	}
	else if( chance >80)// chance for digit 10% out of 20%
	{
		ranstr+='0';  	// digit is inserted into the randomstring
	}
	else // chance for alphabets i.e 80% out of 100
	{
		ranstr+=randomchar[rand()%52]; // alphabet is inserted into the randomstring
	}
	
}

void CheckInput(const string ranstr, const string instr,int& totalpoint,const double& time_elasped) // accepts user input and compare it with random string 
{
	int offset=0;
	
	cout<<time_elasped<<" milliseconds, ";\
	
	
	for(int k=0; k<ranstr.length(); k++) 
	{
		if(isdigit(ranstr[k])) // if it reaches the index where the content is digit
		{
			if(!isdigit(instr[k])) // checking if it is a digit or not 
			{
				offset+=abs(ranstr[k]-instr[k]);
			
			}
		
		}
		else if(!isalnum(ranstr[k])) // if it reaches the index where the content is non-alphanumeric
		{
			if(isalnum(instr[k])) // checking if it is a non-alphanumeric
			{	
				
				offset+=abs(ranstr[k]-instr[k]);
				
			}
		}
		else // matching the alphabets
		{
			offset+=abs(ranstr[k]-instr[k]);
			
		}
	}
	
	if(offset!=0&&(time_elasped-10000)>0) // if the user's input is incorrect and overdue
	{
		totalpoint=totalpoint-((offset*2)+time_elasped-10000);
		
		cout<<"you *failed* it within the interval of 10000...\nString offset is "<<offset<<", your total penalty is "<<offset<<"...\n";
		
	}
	else if (offset!=0) // if the user's input is incorrect but within time limit
	{			
		cout<<"you made it within the interval of 10000...\nString offset is "<<offset<<", your total penalty is "<<offset<<"...\n";
		
		totalpoint-=offset;
	}
	else if ((time_elasped-10000)>0) // if the user's input is correct but out of time limit
	{	

		cout<<"you *failed* it within the interval of 10000...\n";		
		
		totalpoint -=(time_elasped-10000);
		
	}
	else // if the user's input is correct and within time limit
	{
		cout<<"you made it within the interval of 10000..."<<endl;
		
		totalpoint+=500;
	}
}
int main()
{
	srand((unsigned)time(0)); // random seed generator
	
	string randomstring, inputstring;
	
	int point=2000; 
	
	while(point<5000&&point>0) // run until the point is greater or equal than 5000, or lesser or equal then 0
	{
		double time_elasped=0;
		
		while(randomstring.length()<5) // insert contents into the random string until its length is 5
		{
		
			CreateRandomStr(randomstring);
		
		}
		
		cout<<"Your current points "<<point<<", just type -> ";
		
		for(int i=0;i<randomstring.length();i++) // checking for digits and non-alphanumeric and displaying its contents
		{
			if(isdigit(randomstring[i]))
			{
				cout<<"[0-9]";
			}
			else if (!isalnum(randomstring[i]))
			{
				cout<<"[%-!]";
			}
			else
			{
				cout<<randomstring[i];
			}
		}
		
		cout<<" : ";
		
		auto start = chrono::steady_clock::now(); // start the timer in milliseconds
		
		cin>>inputstring;
		
		auto end=chrono::steady_clock::now(); // end the timer in milliseconds
		
		time_elasped= double(chrono::duration_cast<chrono::milliseconds>(end-start).count()); // find the time elasped
		
			while(inputstring.length()<5) // if user did not input a string of 5 characters.
			{
				inputstring+=' ';
			}
		
		CheckInput(randomstring,inputstring, point,time_elasped); // check user input and change the point according to the result
		
		randomstring.clear();
		
		inputstring.clear();

	
	}
	
	
	cout<<"Bye...\n"; // closing ouput 
	
	return 0;
}