#include <iostream>
#include<conio.h>
#include <Windows.h>
#include<time.h>

using namespace std;
bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
int tailX[100], tailY[100], nTail=0;
void setup();
void draw();
void input();
void logic();
eDirection dir;

int main()
{
	retry:
	setup();
	while (!gameover)
	{
		draw();
		input();
		logic();
		Sleep(60);
	}

    system("cls");    
    cout<<"YOUR SCORE IS  "<<score<<endl;
    cout<<"                                    "<<endl;
    cout<<"                                    "<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"         G A M E  O V E R           "<<endl;
    cout<<"------------------------------------"<<endl;
    cout<<"                                    "<<endl;
    cout<<"                                    "<<endl;
    cout<<"PRESS R TO RETRY"<<endl;
    cout<<"PRESS any other key TO EXIT"<<endl;
    if(getch()=='r'){goto retry;}
    
}

void setup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	srand(time(0));
	fruitX = rand() % (width-4)+2;
	fruitY = rand() % (height-4)+2;
	score = 0;
    for(int i=0;i<nTail;i++)
    {
        tailX[i]=0;
        tailY[i]=0;
    }
    nTail=0;

}

void draw()
{
system("cls");
    bool print;
    cout<<"\t"<<"\tSCORE: "<<score<<endl;
    for (int row=0;row<height;row++)               
    {
        for(int col=0;col<width;col++)
        {
            if(row==0||row==(height-1)) 
            {cout<<"=="; }
            else 
            {   
                if (col==0||col==(width-1))
                {cout<<"||";}
                else
                {
                    for(int i=0;i<nTail;i++)            //to print tail
                    {
                        if(row==tailY[i]&&col==tailX[i])
                        {
                            print=true;
                            cout<<"o"<<" ";
                        }   
                    }
                    if(row==y&&col==x)                  //this is to print snake
                    {cout<<"O"<<" ";}
                    else if(row==fruitY&&col==fruitX)
                    {cout<<"$"<<" ";}                    //this is to print fruit
                    else if (!print) {cout<<" "<<" ";}
                    print = false;              
                }
            }

            
        }
        cout<<endl;
    }


}

void input()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 75:dir=LEFT;break;
			case 77:dir=RIGHT;break;
			case 72:dir=UP;break;
			case 80:dir=DOWN;break;
			case 'x':gameover=true;
		}
	}
}

void logic()
{
	
	
	// int prevX = tailX[0];
	// int prevY = tailY[0];
	// int prev2X, prev2Y;
	// tailX[0] = x;
	// tailY[0] = y;
	// for (int i = 1; i < nTail; i++)
	// {
	// 	prev2X = tailX[i];
	// 	prev2Y = tailY[i];
	// 	tailX[i] = prevX;
	// 	tailY[i] = prevY;
	// 	prevX = prev2X;
	// 	prevY = prev2Y;
	// }
	

	int prevX=x;
    int prevY=y;

	switch (dir)
	{
	case LEFT: x--; break;
	case RIGHT: x++; break;
	case UP: y--; break;
	case DOWN: y++; break;
	default:
		break;

	}

if(x==fruitX&&y==fruitY)
{
	srand(time(0));
	fruitX=rand()%(width-4)+2;
	fruitY=rand()%(height-4)+2;
	score+=10;
	nTail++;

}
if(x==0){x=width-2;}
else if(x==width-1){x=1;}
else if(y==0){y=height-2;}
else if(y==height-1){y=1;}

for(int i=0;i<nTail;i++)
{
	if(x==tailX[i]&&y==tailY[i])
	{
		gameover=true;
	}
}

for(int i=(nTail-1);i>0;i--)
    {
        tailX[i]=tailX[i-1];    
        tailY[i]=tailY[i-1];    
    }
    tailX[0]=prevX;
    tailY[0]=prevY;

    for(int i=0;i<nTail;i++)
    {
        if(x==tailX[i]&&y==tailY[i])
        {
            gameover=true;
        }
    }

 }
