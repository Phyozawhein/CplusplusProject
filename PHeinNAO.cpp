#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>
using namespace std;



int RollCheckOnesandDecide(int& mainscore, int HumanOrCom, int whoiswinning) // the main component of the program that encompasses the whole operation
{	
	int count=0, score=0, sum=0, humansum=0; //  for the switch statement and score of computer
	
	char response; // Response for banking scores
	
	vector<int>threedice; // to store all three numbers from three dice
	
	
	if(!HumanOrCom)
	{
		
		cout<<"Computer's turn"<<endl;
	}
	
	cout << "Rolled "; // Indication when 3 dice are being rolled
	
	//Rolling three dice
	for(int i=0; i<3;i++)
	{	
		
		
		int num = rand()%6+1;
		
		cout << num ;
		
		if(i<2)
		{
			cout<<", "; // adding ", " after every number except the last one 
		}
		
		
			sum+=num; // storing all the value of 3 dice to for AI decision
		
		
		threedice.push_back(num); // putting numbers in the vector
	}
	
	
	// Checking if three dice have ones
	for(int i=0;i<threedice.size();i++)
	{
		if(threedice.at(i)==1)
		{
			count++; // Keeping count of ones after each cast
		}
		
	}
	
	//Making decision depending on the results from checking for ones
	switch(count)
	{
		case 1: cout<<" \nSingle one, lose turn.\n"; sum=0;break; // the player lose a turn 
		
		case 2: cout<<" \nTwo ones, lose half of holdings and lose turn.\n";
				mainscore=mainscore/2; sum=0; break; // the player lose half the holding score and a turn 
		
		case 3: cout<<"\nThree ones, lose all holdings, and lose turn.\n";
				mainscore=0; sum=0;break;	// the player lose all holdings and a turn 
		
		default: 
				
				if(HumanOrCom>0)		// check if it is human 
					{ cout<<"\nsum = "<<sum<<endl; // showing the sum of 3 dice
				 
						 do{
						 
								 cout<<"Bank (y/n)?";
								 
								 cin>>response;
								 
								 if(response=='y')
								 {
									 for(int j=0;j<threedice.size();j++)
									 {
										 mainscore+=threedice.at(j);
									 }
									 
								 }
								 else if( response=='n')
								 {
									 RollCheckOnesandDecide( mainscore,  HumanOrCom, whoiswinning);
									 
								 }
							}while(response!='y'&&response!='n');
						
					}
					else // if it is computer's turn
					{	
						cout<<"\nsum = "<<sum; // showing the sum of 3 dice
						
						for(int k=0;k<threedice.size();k++)
						{
							score+=threedice.at(k); // adding the score of computer
						}
						
						if( !whoiswinning) // if human has higher score than computer
						{
							if( score >= sum) // bank if the computer's current score is bigger than human's score from previous cast
							{
								mainscore+=score;
								cout<<" bank\n";
							}
							
							else// otherwise, roll again
							{
								score=0;
								cout<<" no bank.\n";
							}
						}
						else // if computer has higher score than human
						{
							mainscore+=score;
							cout<<" bank\n";
						}
						
						sum=0; // clearing out after the checking 
						
					}
					break;
	}
	
	threedice.clear(); // eliminating all the elements of the vector, making it ready for the new number from next cast
	
	
	
	return 0;
}

int CheckWinner(int player,int com) // this function checks if there is a winner during the game
{
	int overflag=0;
	
	if( player>=150&&com>=150)	// See if both players have score over 150
	{
		if(player > com)		// See if the player's score is larger than  the computer's
		{
			cout<<endl<<" \nHuman won";
		}
		else if (player<com)	// See if the computer's score is larger than  the player's
		{
			cout<<endl<<"\nComputer won";
		}
		else						//See if both of them have the same score
		{
			cout<<endl<<"\nTie";
		}
		
		overflag=1; 				// Sending a signal back to while if the game is over or not
	}
	else if( player >=150)			// See if the player has score over 150 before the computer does
	{
		cout<<endl<<"\nHuman Won";
		overflag=1;
	}
	else if( com >= 150)			// See if the computer has score over 150 before the player does
	{
		cout<<endl<<"\nComputer Won";
		overflag=1;
	}
	else
	{
		overflag=0;
	}
	
	return overflag;// the result that determines if the game is over or not
}

int main() // the main fucntion that activates the game 
{
	int human=0, computer=0, round=0,over=0, whoiswinning=0;// definition of human score, computer score, round number, overflag for when to stop the game
	
	srand((unsigned)time(0)); // seed for random number generator 
	
	while(!over) // the game goes on until one of them wins
	{	
		++round ; // incrementing round numbers
		
		RollCheckOnesandDecide(human,1,whoiswinning);//Roll and Check for human player
		
		RollCheckOnesandDecide(computer,0,whoiswinning);// Roll and Check for computer
		
		cout<<"After round "<<round<<" human has "<<human<<" and computer has "<<computer<<"\n"<<endl; // announcing participants' scores each round

		over=CheckWinner(human,computer);	// check if there is any winner yet
		
		if(human>computer)
		{
			whoiswinning=0;
		}
		else
		{
			whoiswinning=1;
		}
	}
	
	
	return 0;
	
}