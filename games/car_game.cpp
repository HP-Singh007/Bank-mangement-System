#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
int x,y,car1X,car1Y,car2X,car2Y,car3X,car3Y,score;
const int width=7;
const int height=30; 
char path[height];
bool gameover;
enum directions{STOP,LEFT,RIGHT};
directions dir;


void setup()
{
    score=0;
    gameover=false;
    x=width/2-1;
    y=height-4;
    dir=STOP;
    path[0]=0;
    for(int i=0;i<height-1;i++)
    {
        path[i+1]=path[i]-1;
    }
    car1X=rand()%(width-1)+1;
    car2X=rand()%(width-1)+1;
    car3X=rand()%(width-1)+1;
    car1Y=0;
    car2Y=-(height/3);
    car3Y=-(2*height/3);
    
    
   
}

void draw()
{
    system("cls");
    cout<<"\t   SCORE : "<<score<<"\t"<<endl;
    for (int row=0;row<=height;row++)
    {
        for(int col=0;col<=width;col++)
        {
            if(col==0||col==width)
            {
                for(int i=0;i<height;i++)
                {
                    if(row==path[i])
                    {
                        if(i%3==0){cout<<" || ";}
                        else{cout<<"    ";}
                    }
                    
                }
            }
            else
            {
                if(row==y&&col==x)
                {cout<<"|__|";}
                else if(row==y-1&&col==x)
                {cout<<"||||";}
                else if(row==y-2&&col==x)
                {cout<<"/--\\";}
                else if(row==car1Y&&col==car1X)
                {cout<<"/--\\";}
                else if(row==car1Y-1&&col==car1X)
                {cout<<"|__|";}
                else if(row==car2Y&&col==car2X)
                {cout<<"/__\\";}
                else if(row==car2Y-1&&col==car2X)
                {cout<<"(__)";}
                else if(row==car3Y&&col==car3X)
                {cout<<"/**\\";}
                else if(row==car3Y-1&&col==car3X)
                {cout<<"T__T";}
                else{cout<<"    ";}
            }
        }
        cout<<endl;
    }
}

void input()
{
    dir=STOP;
    if(_kbhit())
    {
        switch(_getch())
        {
            case 75:dir=LEFT;break;
			case 77:dir=RIGHT;break;
			case 'x':gameover=true;
        }
    }
}

void logic()
{
    for(int i=0;i<height;i++)
    {
        path[i]++;
        if(path[i]==height){path[i]=0;}
    }
    switch(dir)
    {
        case STOP:break;
        case LEFT:if(x!=1){x--;}break;
        case RIGHT:if(x!=width-1){x++;}break;
    }
    car1Y++;
    car2Y++;
    car3Y++;
    if(car1Y==height){car1Y=0;car1X=rand()%(width-1)+1;}
    if(car2Y==height){car2Y=0;car2X=rand()%(width-1)+1;}
    if(car3Y==height){car3Y=0;car3X=rand()%(width-1)+1;}

    if(y==car1Y||y==car1Y-1||y-1==car1Y||y-1==car1Y-1||y-2==car1Y||y-2==car1Y-1)
    {
        if(x==car1X){gameover=true;}
    }
    if(y==car2Y||y==car2Y-1||y-1==car2Y||y-1==car2Y-1||y-2==car2Y||y-2==car2Y-1)
    {
        if(x==car2X){gameover=true;}
    }
    if(y==car3Y||y==car3Y-1||y-1==car3Y||y-1==car3Y-1||y-2==car3Y||y-2==car3Y-1)
    {
        if(x==car3X){gameover=true;}
    }
    score++;
}

int main()
{
    setup();
    while(!gameover)
    {
        draw();
        input();
        logic();
        Sleep(20);
    }
    return 0;
}