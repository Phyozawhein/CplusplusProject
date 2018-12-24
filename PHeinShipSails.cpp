#include<iostream>
#include<vector>
#include<ctime>
#include<random>
#include<algorithm>
#include<iomanip>

using namespace std;

struct Card
{
	char suit; 
	string number;
};

class Player
{
	protected :

	int selfIndex;      //index within player vector, starting with 0 for the human
	int takeFrom;       //player supplying new Card
	vector<Card> hand;  //holds 7 cards
	static Card discardList[5];
	int discardIndex;   //position within hand of card being discarded
	
	public:
	Player(int SI, int TF):	selfIndex(SI),takeFrom(TF)
	{}
	
	virtual void  choosediscard(int);
	
	
	void replenish();
	
	int getSelfIndex();
	
	void addCard(Card );

	vector<Card> gethand();
	
	bool IsWinner();
	
	
};
Card Player:: discardList[5]={ };

void Player:: choosediscard(int dispos)
{
		discardIndex=dispos;
		discardList[selfIndex]=hand[dispos];
		
			cout<<"\tPlayer "<<selfIndex<<" gave "<<selfIndex+1<<" "<<hand[dispos].suit+hand[dispos].number<<endl;
		
}
 

void Player:: replenish()
{
	hand[discardIndex]=discardList[takeFrom];
}

int Player:: getSelfIndex() // access index of the player
{
	return selfIndex;
}

vector<Card> Player:: gethand() // access hand of the player
{
	return hand;
}

void Player:: addCard(Card temp) // adding card to player
{
	hand.push_back(temp);
}

 bool Player:: IsWinner() // checking if the player has full suit
{	int count=0;
	bool endflag=false;
		
		for(int j=0;j<=6;j++)
		{
			if(hand[j].suit==hand[j+1].suit)
			{
				count++;
			}
		}
		if(count==6)
		{
			cout<<"Player "<<selfIndex<<" is a winner!\n";
	
			endflag=true;
			
			
		}
		
		return endflag;
		
}

class Autoplayer : public Player
{
	public :
	Autoplayer( int SI, int TF):Player(SI,TF)
	{	}
	
	void choosediscard(int);
	
	
};

void Autoplayer:: choosediscard(int pos)// fix the algorithm to find the suit with least number in the hand and choose it 
{	
	string suits="SHDC";
	vector<int> suitcount;
	int count,prevsize=0;
	
	for(int i=0;i<suits.size();i++)
	{	
		
		if(prevsize>suits.size())
		{	prevsize--; // index resetted for moved content and the previous size was adjusted to the current one to prevent infinite loop
			i=0;
		}
		count=0;
		for(int j=0;j<hand.size();j++)
		{
			if(suits[i]==hand[j].suit)
			{
				count++;
			}
		}
		
		if(count==0)
		{	
			prevsize=suits.size();
			
			suits.erase(suits.begin()+i);
			
		}
		
	}
	for(int i=0;i<suits.size();i++)
	{	
		count=0;
		
		for(int j=0;j<hand.size();j++)
		{
			if(suits[i]==hand[j].suit)
			{
				count++;
			}
		}
		
		if(count==0)
		{
			
			suits.erase(suits.begin()+i);
			
		}
		else
		{
				suitcount.push_back(count);
		}
		
	}
	
	for(int i=0;i<suitcount.size();i++) // finding the index of the minimal suit count
	{
		if(suitcount[i]==*std::min_element(suitcount.begin(),suitcount.end()))
		{
			pos=i;
			break;
		}
	}
	
	for(int i=0;i<hand.size();i++) // choosing the card based on pos
	{
		if(suits[pos]==hand[i].suit)
		{
			discardList[selfIndex]=hand[i];
			discardIndex=i;
			if(selfIndex==4)
				{
					cout<<"\tPlayer "<<selfIndex<<" gave "<<0<<" "<<hand[i].suit+hand[i].number<<endl;
				
				}
				else
				{
					cout<<"\tPlayer "<<selfIndex<<" gave "<<selfIndex+1<<" "<<hand[i].suit+hand[i].number<<endl;
				}
				break;
		}
	}
	

	
}



void showhands(vector<Player*> players, int limit) // Showhands
{

	for(int i=0;i<limit;i++)
	{
		cout<<players.at(i)->getSelfIndex()<<":\t";
		
		for(int j=0;j<7;j++)
		{
		
				cout<<setw(6)<<players.at(i)->gethand()[j].suit+players.at(i)->gethand()[j].number;
			
		}
		cout<<endl;
	}

	return;
	
}

int main()
{	int wincount=0;
	string suits="SHDC";
	string index="abcdefg";
	bool flag=true;
	char response;
	Card tempcard;
	vector<Card> deck;
	srand((unsigned) time(0));
	
	vector<Player*> players;
	
	Player zero(0,4);
	Autoplayer one(1,0);
	Autoplayer two(2,1);
	Autoplayer three(3,2);
	Autoplayer four(4,3);
	players.push_back(&zero);
	players.push_back(&one);
	players.push_back(&two);
	players.push_back(&three);
	players.push_back(&four);
	
	for (int i=0; i <4;i++) // setting up a deck of 52 cards
	{
		tempcard.suit=suits[i];
		for(int j=1;j<=13;j++)
		{
			if(j>10)
			{
				switch(j%10)
				{
					case 1: tempcard.number='J';break;
					case 2: tempcard.number='Q';break;
					case 3: tempcard.number='K';break;
					default:break;
				};
			}
			else
			{
				tempcard.number=to_string(j);
			}
			
			deck.push_back(tempcard);
		}
	}

	
	
	
	random_shuffle(deck.begin(),deck.end()); // shuffling the deck of 52 cards
	
	
	
	for(int i=0;i<5;i++) // assigning each player cards
	{
		
		for(int j=0;j<7;j++)
		{
			int randomindex=rand()%deck.size();
			players.at(i)->addCard(deck[randomindex]);
			deck.erase(deck.begin()+randomindex);
			
			
		}
	}
	
	
	
	do
	{
	
		cout<<"Your hand:\n";
		
		showhands(players,1);
		
		cout<<"\t";
		for(int i=0;i<index.length();i++) // showing indices in alphabets
			{
				cout<<setw(6)<<index[i];
			}
			cout<<endl;
			
		do
		{	flag=true;
		cout<<"cmd: ";
			cin>>response;
			if(response=='?') // only a is acceptable fix it !!
			{
				showhands(players,5);
				continue;
			}
			else if(cin.fail()||index.find(response)==std::string::npos)
			{
				cout<<"Invalid choice\n";
			}
			else
			{
				flag=false;
			}
			
		}while(flag);
		
		
		for(int i=0;i<5;i++)
		{
		
			players.at(i)->choosediscard(index.find(response));
			
			
		}
		for(int i=0;i<5;i++)
		{
			
			players.at(i)->replenish();
			
			
		}
		
		
	for(int i=0;i<5;i++)
	{	
		if(players.at(i)->IsWinner())
		{
			
			wincount++;
		}
		
	}
		

	}while(wincount==0);
	cout<<"At the end of the game the players had:\n";
	showhands(players,5);
}