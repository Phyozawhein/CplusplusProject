#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<chrono>
#include<string>
#include<iomanip>
#ifdef __WIN32__ 
#include <windows.h>
#define sleep(n) Sleep(1000 * n)  //Windows Sleep in ms

#define clear() system("cls")
#endif

#ifdef __APPLE__ 
#include <unistd.h>

#define clear() system("clear")
#endif


using namespace std;


void PromptMatchandCheck(chrono::duration<double>& elapsed_seconds,vector<string> randomstring,vector<string>& outputvec, int timelimit,int& pairsleft, int row, int col, bool& completeflag, bool& timeflag)
{
	int firstslot=0,secondslot=0;
			
			for(int i=0;i<(row*col);i++) // board output
				{
					if(i%col==0)
					{
					cout<<"\n";
					}
					cout<<setw(4)<<outputvec[i];	
				}
			
			
			
			//Prompting for slot positions
		
			
			auto start = std::chrono::system_clock::now();	//getting the time of the start of matching process
			cout<<"\n\n\n\n\n";	
				
			while(firstslot==secondslot||firstslot==0||firstslot>(row*col))
			{
				cout<<"\nEnter the first slot to view: ";
				cin>>firstslot;
				
			}
			while(firstslot==secondslot||secondslot==0||secondslot>(row*col))
			{
				cout<<"Enter the second slot to view: ";
				cin>>secondslot;
				
			}
			
			
			firstslot--;// adjusting to the indices of string and vectors
			secondslot--;// adjusting to the indices of string and vectors
			
			for(int i=0;i<row*col;i++) // board output
			{
				if(i%col==0)
				{
				cout<<"\n";
				}
				
				if(i!=(firstslot)&&i!=(secondslot))
				{
				cout<<setw(4)<<outputvec[i];	
				}
				else
				{
					cout<<setw(4)<<randomstring[i];
				}
			}
			
			if(outputvec[firstslot]==outputvec[secondslot])// Comparing the selected slots
			{
				cout<<"\nPreviously matched\n";
				
			}
			else if(randomstring[firstslot]==randomstring[secondslot])
			{
				cout<<"\n\aMatch\n";
				
				outputvec[firstslot]=randomstring[firstslot];
				
				outputvec[secondslot]=randomstring[secondslot];
				
				pairsleft--;
				
			}
			else
			{
				cout<<"\nNo Match\n";
				
			}
			 
			  
			

			auto end = std::chrono::system_clock::now();  // getting the time of the end of matching process
			 
			  
			  elapsed_seconds=elapsed_seconds+(end-start);// accumulating the total elasped time
			  
			
			  
			  if(!pairsleft) // checking if the player completed all the matching
			{
				completeflag=true;
				
				cout<<"\n\nAll matched within " << (int)elapsed_seconds.count()/60<<" minutes and "<<(int)elapsed_seconds.count()%60<<" seconds\n";
			}
			else if(elapsed_seconds.count()>timelimit) // checking if the time is up
			{
				timeflag=true;
				
				cout<<"\n\nTime expired\nYou revealed:\n";
				
				for(int i=0;i<row*col;i++) // board output
					{
						if(i%col==0)
						{
						cout<<"\n";
						}
						
						if(i==(firstslot)&&i==(secondslot)) // Check if certain slots have been figured out 
						{
							cout<<setw(4)<<randomstring[i];
						}
						else
						{
							cout<<setw(4)<<outputvec[i];
						}
					}
				cout<<"\n\n All the pairs were at:\n";
				for(int i=0;i<(row*col);i++) 
				{
					if(i%col==0)
					{
					cout<<"\n";
					}
					cout<<setw(4)<<randomstring[i];	
				}
			
				
			}
			
				sleep(3);
				clear();
			 
}

int main()
{
	srand((unsigned)time(0));
	
	
	vector<string> alphabets={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","[","\\","]","^","_","`"};

	vector<string> outputvec;
	
	int randchar,randpos, row=0,col=0, insertcount,timelimit,pairsleft;
	
	bool flag=true, timeflag=false, completeflag=false;
	
	chrono::duration<double> elapsed_seconds =(chrono::duration<double>)  0;
	
	cout<<"In this game, pairs of letters will be hidden on a rectangular grid.\nOnce the grid is established you will be asked to enter the numbers of two slots.\nIf the letters at those slots match, they will stay in view.\nIf not, after 3 seconds the letters will disappear and be replaced by the numbers.\nYour job is find all the pairs\n\n\n\n\n";
	
	
	
	do
	{
		cout<<"Size requirment: product of row x col must be between 16 and 64 and be even\n";//Ask for rows and columns and setting up the board
		
		cout<<"Enter rows: ";
		cin>>row;
		cout<<"Enter columns: ";
		cin>>col;
		
		if((row*col)%2==0)
		{
			if((row*col)>=16)
			{
				if((row*col)<=64)
				{
					flag=false;
				}
			}
			
		}
		
		}while(flag);
		
		vector<string> randomstring (row*col," "); 
		
		timelimit=(30*row*col)/2; // time limit in which the user have to complete the matching game.
		
		pairsleft=(row*col)/2; // pairs left to be matched.
		
		
		
		for(int k=0;k<randomstring.size()/2;k++)
		{
			randchar=rand()%alphabets.size(); // random alphabet seed
			
			
			insertcount=0;
				
				
				while(insertcount<2) // placing the random alphabet in 2 random places of the randomstring 
				{
					randpos=rand()%randomstring.size(); // random position inside the table
					
					if( randomstring[randpos]==" ") // if the position has not been filled with an alphabet
					{	
						
						
						randomstring[randpos]=alphabets[randchar]; // putting random alphabet in a random place
						
						insertcount++;
						
					}
					
				}
				alphabets.erase(alphabets.begin()+randchar);
			
		}
		
		for(int i=0;i<(row*col);i++)
		{
			outputvec.push_back(to_string(i+1));
		}
		
		cout<<"\n\n\n\nAllowing 30 seconds per pair\nYou will have "<< timelimit <<" minutes and 0 seconds to find the "<<(row*col)/2<<" pairs.\nLet's play\n";
		
		// Board Output, Prompting slots and Matching them	
		
		do 
		{
			PromptMatchandCheck( elapsed_seconds, randomstring, outputvec, timelimit, pairsleft,row, col, completeflag,timeflag);
			
		}while(!timeflag&&!completeflag);
		



}
