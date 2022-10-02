#include<iostream>
#include<conio.h>
#include<iomanip>
using namespace std;
char arr[3][3];
char inp_char;
int count,score1=0,score2=0;
char sign,winner;
bool gameover;

void setup()
{
    gameover=false;
    count=0;
    winner='0';
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)        //storing empty array with spaces...
        {
            arr[i][j]=' ';
        }
    }
}

void draw()
{
    system("cls");
    cout<<"\t  TIC TAC TOE";
    cout<<endl<<endl;
    for(int row=0;row<5;row++)
    {
        cout<<setw(12);
        for(int col=0;col<5;col++)
        {                                             //drawing outlines...
            if(row%2==0)
            {
                if(col%2!=0){cout<<"| ";}
                else{cout<<arr[row/2][col/2]<<" ";}
            }
            else{
                cout<<"__";
            }
        }cout<<endl;
    }
    for(int i=0;i<3;i++)
    {
        if((arr[i][0]==arr[i][1])&&(arr[i][1]==arr[i][2])&&(arr[i][2]!=' ')){gameover=true;}
    }
    for(int i=0;i<3;i++)                    //checking won or not...
    {
        if((arr[0][i]==arr[1][i])&&(arr[1][i]==arr[2][i])&&(arr[2][i]!=' ')){gameover=true;}
    }
    if((arr[0][0]==arr[1][1])&&(arr[1][1]==arr[2][2])&&(arr[1][1]!=' ')){gameover=true;}
    if((arr[0][2]==arr[1][1])&&(arr[1][1]==arr[2][0])&&(arr[1][1]!=' ')){gameover=true;}
    if(gameover){winner=sign;cout<<endl<<sign<<" "<<"WON THE MATCH!!!"<<endl;}
    if((count==9)&&(!gameover)){cout<<endl<<"THERE IS A TIE !!!"<<endl<<"NO ONE WON!!!";}

}

void input()
{
    if(!gameover){inp_char=getch();}
}

void logic()
{
    if(!gameover)
    {if(count%2==0){sign='X';}
    else{sign='O';}
    count++;
    switch(inp_char)
    {
        case '1':if(arr[2][0]==' '){arr[2][0]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        case '2':if(arr[2][1]==' '){arr[2][1]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        case '3':if(arr[2][2]==' '){arr[2][2]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        case '4':if(arr[1][0]==' '){arr[1][0]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        case '5':if(arr[1][1]==' '){arr[1][1]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        case '6':if(arr[1][2]==' '){arr[1][2]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        case '7':if(arr[0][0]==' '){arr[0][0]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        case '8':if(arr[0][1]==' '){arr[0][1]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        case '9':if(arr[0][2]==' '){arr[0][2]=sign;}else{cout<<endl<<"ALREADY ASSIGNED"<<endl;getch();};break;
        default:break;
    }
    }
    if(winner=='X'){score1+=1;}       
    else if(winner=='O'){score2+=1;}       
}

int main()
{
    string player1,player2;
    start_page:
    system("cls");
    cout<<"\tTIC TAC TOE";
    cout<<"\nPLAYER 1 : ";cin>>player1;
    cout<<"\nPLAYER 2 : ";cin>>player2;
    if(score1||score2)
    {   
        score_page:
        system("cls");
        cout<<setw(5)<<"SCORES : "<<endl;
        cout<<"---------------------------"<<endl;
        cout<<player1<<" : "<<score1<<endl;
        cout<<player2<<" : "<<score2<<endl<<endl<<endl;
        cout<<endl<<setw(10)<<"PRESS Enter :CONTINUE ";
        cout<<endl<<setw(10)<<"PRESS n     :NEW GAME ";
        cout<<endl<<setw(10)<<"PRESS x     :EXIT ";
        switch((getch()))
        {
            case 'n':goto start_page;break;
            case 'x':goto end;break;
            default:break;
        }
    }

    setup();
    while((!gameover)&&count<=9){
    draw();
    input();
    logic();
    }
    getch();goto score_page;
    end:
    return 0;
}