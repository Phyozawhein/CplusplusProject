#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>

using namespace std;

void Input(vector<string>& vec, string& instr  )
{ 
		string temp;
		
				for(int i=0;i<instr.length(); i++)
			{
				if(instr[i]!=' ')
				{
					temp+=instr[i];
					
					if(i==instr.length()-1)
					{
						vec.push_back(temp);
					}
				}
				else
				{
					if(isalnum(temp[0]))
					{
					vec.push_back(temp);
					}
					temp.clear();
					
				}
				
			}
			
			
			instr.clear();
}
		


void ShufflePromptandCompare( vector<string> vec,vector<string>& randomvec,vector<string>& inputvec,string instr, int& level,int& successcount)
{
	
	int randomlength=rand()%3+1, randomstrindex, countflag=0; 
	 
	string temp;
	
	vector<char> outputvec;
	
	// This is the part where animals' names are picked out randomly  and strikeout are place randomly depending on the number of success.
	
	while(randomvec.size()<randomlength) // creating random string to be shuffled
	{
		
		randomstrindex=rand()%vec.size(); // generating the random index for the animal name

		
		if(find(randomvec.begin(),randomvec.end(),vec[randomstrindex])==randomvec.end())
		{
			randomvec.push_back(vec[randomstrindex]);//inserting random animal name into the random vector
		
			temp+=vec[randomstrindex]; //inserting random animal name from the vector
		}
		else
		{
			continue;
		}
		
		
	}
	
	

	for(int i=0; i<level; i++)	// random strikeout placement
	{
		int randomstrikeoutpos=rand()%temp.length(); 
	
		temp.replace(randomstrikeoutpos,1,"_");
	}
	
	for(int j=0; j<temp.length();j++)
	{ 	
		
		outputvec.push_back(temp[j]); // inserting scrambled characters for the ouput
	}

	random_shuffle(outputvec.begin(),outputvec.end()); // shuffling the words inside the string
	
	temp.clear(); // clearing temp for further use

	cout<<"\nWhat are "<< randomlength<<" animals in \""; // outputing scrambled names
	
	for( int k=0; k<outputvec.size();k++)
	{
		cout<<outputvec[k];
	}
	
	cout<<"\" ? ";
	
	
	do // asking for input and checking if user input the right amount of words
	{	
		
		getline(cin,instr);
			
		Input(inputvec,instr);
		
		
		for (int i =0; i< inputvec.size();i++)
		
		{			
		
		
			
			
			if( inputvec[i]=="quit")
			{
				return;
			}
			else if ( inputvec[i]=="?")
			{
				inputvec.erase(inputvec.begin()+i);
				for( int j=0; j<vec.size();j++)
				{
					cout<<j<< " : "<<vec[j]<<endl;
				}
				cout<<"Enter again : ";
				inputvec.clear();
			}
			else if(inputvec.size()!=randomvec.size()) // if the user failed to enter the correct amount of words.
			{	
				
				
					cout<<"Your number of input is incorrect. Enter again: ";	
					inputvec.clear();
					break;
				
			}
		}
	} while(inputvec.size()!=randomvec.size());
	
	
	// This is the part where the program matches the user input against the randomized vector and determines the level of challange
		
	for(int i=0;i<randomvec.size();i++) // checking if the user enter correct names
	{
		for(int j=0;j<inputvec.size();j++)
		{
			if(inputvec[j]==randomvec[i])
			{
				countflag++;
			}
		}
	}
	
	
	
	if(countflag==randomvec.size()) // if the user input all the correct names
	{
		cout<<"Yes!"<<endl;
		
		successcount++;
	}
	else
	{
		cout<<"Nope!"<<endl;
		successcount--;
	
		
	}

		if(successcount%2==0&&successcount>0)
		{
			cout<<"Succeeded two consecutive times, challenge goes up!"<<endl;
			level++;
			successcount=0;
		}
		else if(successcount%2==0&&successcount<0)
		{
			
			if(level>0)
			{	cout<<"Missed two consecutive times, challenge goes down!"<<endl;
				level--;
				successcount=0;
			}
			else
			{
				level=0;
				successcount=0;
			}
		
		}
	
	inputvec.clear();
	randomvec.clear();
	return;
}







int main()
{
	srand((unsigned)time(0));
	
	int level=0,successcount=0;
	
	string instr;
	
	vector<string> randomvec,inputvec, vec;
	
	bool flag=true, quitflag=true; // flag= input flag , quitflag= flag for quiting
	
	cout<<"Enter at least five animal names, e.g., cat, dog, etc... "<<endl;
	
	while(flag)//accepting animals and words
	{
		
		getline(cin,instr);
		if(instr.empty()&&vec.size()>=5)
		{
			flag=false;
		}
		else
		{
			Input( vec, instr );
		}	
	}
	
	for(int i=0; i<vec.size();i++) // display the contents after the user input
	{
		cout<<i<<" : "<<vec[i]<<endl;
	}
	
	do{
			
		ShufflePromptandCompare( vec,randomvec,inputvec, instr, level,successcount); 
		
		for (int i =0; i< inputvec.size();i++)
		
		{			
			if( inputvec[i]=="quit")
			{
				quitflag=false;
			}
		}
		
		
		
	}while(	 quitflag );
		
	cout<<"Bye...\n";
			
	return 0;
}