#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
using namespace std; 
const int height=10;
const int width=36;
int path[width];
int x,y,score,count;
int tree1,tree2,tree3;
int bird;
int sp;
bool gameover;
enum directions{STOP,UP,DOWN};
directions dir;
int lives;
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

void setup()
{
    dir=STOP;
    gameover=false;
    score=0;
    y=height-1;
    x=width/5;
    count=0;
    srand(time(0));
    tree1=rand() % (width+10)+20;
    tree2=rand()%(width+20)+30;
    tree3=rand()%(width+20)+40;
    bird=rand()%(width+20)+40;
    lives=3;
}

void draw()
{
    system("cls");
    SetConsoleTextAttribute(h,236);
    cout<<"\t\tSCORE : "<<score<<"\t\t\tLIVES LEFT:"<<lives<<endl;
    SetConsoleTextAttribute(h,176);
    for(int row=0;row<=height;row++)
    {
        for(int col=0;col<=width;col++)
        {
            if(row==height)
            {
                for(int i=0;i<width;i++)
                {
                    if(col==path[i])
                    {
                        if(i%2==0){cout<<"___";}
                        else{cout<<"   ";}
                    }
                }
            }
            else
            {
                if(col==x&&row==y)
                {
                    if(count%3==0){cout<<"/ \\";}           //person
                    else{cout<<" | ";}
                    count++;
                }
                else if(col==x&&row==y-1){cout<<"/|\\";}
                else if(col==x&&row==y-2){cout<<" O ";}

                else if(row==height-1&&col==tree1){SetConsoleTextAttribute(h,174);cout<<"T-T";}         //tree1
                else if(row==height-2&&col==tree1){SetConsoleTextAttribute(h,174);cout<<"/ \\";}         
                else if(row==height-3&&col==tree1){SetConsoleTextAttribute(h,174);cout<<" ^ ";}         

                else if(row==height-1&&col==tree2){SetConsoleTextAttribute(h,174);cout<<"T-T";}         //tree2
                else if(row==height-2&&col==tree2){SetConsoleTextAttribute(h,174);cout<<"***";}         
                else if(row==height-3&&col==tree2){SetConsoleTextAttribute(h,174);cout<<" * ";}         

                else if(row==height-1&&col==tree3){SetConsoleTextAttribute(h,174);cout<<"T-T";}         //tree3
                else if(row==height-2&&col==tree3){SetConsoleTextAttribute(h,174);cout<<"/ \\";}         
                else if(row==height-3&&col==tree3){SetConsoleTextAttribute(h,174);cout<<" * ";}

                else if(row==3&&col==bird){SetConsoleTextAttribute(h,180);cout<<"-:=";}         
                
                else{cout<<"   ";}
                SetConsoleTextAttribute(h,176);
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
            case 'j':dir=UP;break;
            case 'x':gameover=true;lives=0;break;
        }
    }
}

void logic()
{
    sp=60-score/25;
    switch(dir)
    {
        case UP:if(y>height-6){y-=2;}else{dir=DOWN;}break;
        case DOWN:y+=2;break;
        case STOP:break;
    }
    if(y>height-2){dir=STOP;}
    
    
    for(int i=0;i<width;i++)
    {
        path[i]--;
    }
    for(int i=0;i<width;i++)
    {
        if(path[i]==0){path[i]=width;}
    }
    tree1--;
    tree2--;
    tree3--;
    bird-=2;
    srand(time(0));
    if(tree1<0){tree1=rand() % (width+10)+20;}
    if(tree2<0){tree2=rand() % (width+20)+30;}
    if(tree3<0){tree3=rand() % (width+10)+40;}
    if(bird<0){bird=rand()%(width+20)+40;}
    score+=5;
    
    if(x==tree1||x==tree2||x==tree3)
    {
        if(y==height-1||y==height-2||y==height-3)
        {gameover=true;lives--;system("Color e1");Sleep(200);}
        else if(y-1==height-1||y-1==height-2||y-1==height-3)
        {gameover=true;lives--;system("Color e1");Sleep(200);}
        else if(y-2==height-1||y-2==height-2||y-2==height-3)
        {gameover=true;lives--;system("Color e1");Sleep(200);}
    }
    else if(x==bird||x-1==bird)
    {
        if(y==3||y-1==3){gameover=true;lives--;system("Color e1");Sleep(200);}
    }
    
}

int main()
{
    retry:
    // system("Color 22");
    path[0]=1;
    for(int i=0;i<width;i++)
    {
        path[i+1]=path[i]+1;
    }
    setup();
    while(!gameover||lives!=0)
    {
        SetConsoleTextAttribute(h,176); 
        draw();
        input();
        logic();
        if(sp>0){Sleep(sp);}else{Sleep(0);}
    }
    last:
    system("cls");
    system("Color d1");
    SetConsoleTextAttribute(h,223);
    cout<<"YOUR SCORE IS  "<<score<<endl;
    cout<<"                         "<<endl;
    cout<<"                         "<<endl;
    cout<<"-------------------------";
    cout<<"-------------------------";
    cout<<"-------------------------";
    cout<<"-------------------------"<<endl;
    cout<<"\t\t\t\t\t\    G A M E  ";
    cout<<" O V E R                 "<<endl;
    cout<<"-------------------------";
    cout<<"-------------------------";
    cout<<"-------------------------";
    cout<<"-------------------------"<<endl;
    cout<<"                         "<<endl;
    cout<<"                         "<<endl;
    cout<<"PRESS X TO EXIT"<<endl;
    cout<<"PRESS R TO RETRY"<<endl;
    if(getch()=='r'){goto retry;}
    else if(getch()!='x'){goto last;}
    return 0;
}