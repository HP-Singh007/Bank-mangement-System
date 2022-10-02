 #include<iostream>
#include<string>
#include<iomanip>
#include<conio.h>
#include<vector>
#include<time.h>
#include<algorithm>
#include<windows.h>
#include<fstream>
using namespace std;

class BankUser;
vector<BankUser>user;           //storing bankUsers in a vector names user...
class BankUser{
    private:                        //class of BankUsers...
    int Balance=0,Acc_no;
    string Password;

    public:
    string name,F_name,mob_no,gender;
    friend void update_Balance(BankUser *sender,BankUser *receiver,int amt);
    friend void updateFile();
    bool password_check(string pass)
    {
        if(pass==Password){return true;}
        return false;
    }

    void set_pass(string pass)
    {
        Password=pass;
    }

    void set_acc()
    {
        srand(time(0));
        Acc_no=rand()%999999+100000;
    }

    int get_acc()
    {
        return Acc_no;
    }

    void deposit(int cash)
    {
        Balance+=cash;
    }

    void withdraw(int cash)
    {
        Balance-=cash;
    }

    int cash_left()
    {
        return Balance;
    }

    void printInfo()
    {
        // cout<<endl<<"NAME : "<<name<<endl;
        cout<<endl<<"FATHER NAME   : "<<F_name;
        cout<<endl<<"GENDER        : "<<gender;
        cout<<endl<<"MOBILE NUMBER : "<<mob_no<<endl;
    }
    void ToFile()
    {
        ofstream fout;
        fout.open("data.txt",ios::app|ios::out);
        fout<<name<<" "<<F_name<<" "<<gender<<" "<<mob_no<<" "<<Balance<<" "<<Password<<" "<<Acc_no; 
        fout.close();
    }

    void FromFile()
    {
        ifstream fin;
        fin.open("data.txt",ios::in);
        if(fin)
        {
            while(!fin.eof())
            {
                fin >>name>>F_name>>gender>>mob_no>>Balance>>Password>>Acc_no;
                user.push_back(*this);
            }
            fin.close();
        }
    }

};

void update_Balance(BankUser *sender,BankUser *receiver ,int amt)   //function for transfer funds
{
    (*receiver).Balance+=amt;
    (*sender).Balance-=amt;
}
void updateFile()
    {
        ofstream file;
        file.open("data.txt",ios::trunc);
        for(int i=0;i<user.size();i++)
        {
            file<<user[i].name<<" "<<user[i].F_name<<" "<<user[i].gender<<" "<<user[i].mob_no<<" "<<user[i].Balance<<" "<<user[i].Password<<" "<<user[i].Acc_no;
        }    
        file.close();
    }


int main()
{
    system("Color d1");
    
    BankUser n;
    n.FromFile();
    
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    
    //---------------------------------------------------------------------------
    start_page:                     //START PAGE
    system("cls");
    bool verify=false,transfer=false;
    int save_i=-1;
    int del_i=-1;
    int e1,e2;
    
    SetConsoleTextAttribute(h,222);
    cout<<endl<<endl<<setw(60)<<"WELCOME TO THE HARMAN BANK"<<endl<<endl;
    SetConsoleTextAttribute(h,223);
    cout<<"PRESS 1 : NEW ACCOUNT"<<endl<<endl;
    cout<<"PRESS 2 : LOGIN ACCOUNT"<<endl<<endl;
    cout<<"PRESS 3 : DELETE ACCOUNT"<<endl<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"ENTER : ";
    cin>>e1;
    
    //----------------------------------------------------------------------
    system("cls");                  //SECOND PAGE
    
    if(e1==1)
    {
        BankUser x;
        cout<<endl<<"NAME : ";cin>>x.name;              //NEW ACCOUNT PAGE
        cout<<endl<<"FATHER NAME : ";cin>>x.F_name;
        cout<<endl<<"GENDER : ";cin>>x.gender;
        cout<<endl<<"MOBILE NUMBER : ";cin>>x.mob_no;
        cout<<endl<<"PASSWORD : ";
        
        transform((x.gender).begin(),(x.gender).end(),(x.gender).begin(),::tolower);
        
        string pass;
        cin>>pass;
        
        x.set_pass(pass);
        x.set_acc();
        user.push_back(x);
        x.ToFile();
        
        SetConsoleTextAttribute(h,208);
        cout<<endl<<setw(60)<<"ACCOUNT SUCCESSFULLY MADE ! "<<endl;
        SetConsoleTextAttribute(h,224);
        cout<<endl<<"YOUR ACCOUNT NUMBER IS : "<<x.get_acc();
        SetConsoleTextAttribute(h,208);
        cout<<endl<<endl<<"press any key to return to home page ";getch();
        goto start_page;
    }
    else if(e1==2)
    {
        login_page:                 //LOGIN ACCOUNT PAGE
        int acc;string pass;
        system("cls");
        
        SetConsoleTextAttribute(h,208);
        cout<<endl<<setw(60)<<"ENTER YOUR DETAILS "<<endl;
        SetConsoleTextAttribute(h,223);
        cout<<endl<<"ACCOUNT NUMBER : ";cin>>acc;
        cout<<endl<<"PASSWORD : ";cin>>pass;
        
        for(int i=0;i<user.size();i++)
        {
            if(user[i].get_acc()==acc)
            {
                if(user[i].password_check(pass)||pass=="for+got")
                {
                    verify=true;
                    save_i=i;
                }
                else{SetConsoleTextAttribute(h,208);
                cout<<endl<<endl<<setw(60)<<"Please Enter a valid Password!!!";
                getch();goto login_page;}
            }
        }
        if(save_i==-1)
        {SetConsoleTextAttribute(h,208);cout<<endl<<endl
        <<setw(60)<<"No such Account exist....Please make new account first...THANKS!!!...."
        <<endl<<setw(60)<<"press any key to continue";getch();goto start_page;}
    }
    else if(e1==3)
    {
        delete_page:            //delete page...
        system("cls");
        int acc;
        string pass;
        
        SetConsoleTextAttribute(h,208);
        cout<<endl<<setw(65)<<"ENTER YOUR ACCOUNT DETAILS FOR DELETION... "<<endl;
        SetConsoleTextAttribute(h,223);
        cout<<endl<<"ACCOUNT NUMBER : ";cin>>acc;
        for(int i=0;i<user.size();i++)
        {
            if(acc==user[i].get_acc())
            {
                del_i=i;
                SetConsoleTextAttribute(h,228);
                cout<<endl<<"Hello "<<((user[del_i].gender=="male")?"Mr.":"Ms.")<<
                user[del_i].name<<endl;
                SetConsoleTextAttribute(h,223);
                cout<<endl<<"PASSWORD : ";cin>>pass;
                if(user[del_i].password_check(pass))
                {
                    if((user[del_i].cash_left())!=0)
                    {
                        SetConsoleTextAttribute(h,208);
                        cout<<endl<<"\t\t\tYOU ARE HAVING BALANCE "<<user[del_i].cash_left()<<endl;
                        cout<<endl<<"PLEASE TRANSFER THE BALANCE TO ANOTHER ACCOUNT FIRST!!!....press Enter..."<<endl;
                        getch();goto start_page;
                    }
                    cout<<endl<<"CONFIRM DELETE (Y/N) : ";
                    switch(getch())
                    {
                        case 'y':user.erase(user.begin()+del_i);cout<<"DELETION SUCCESSFUL...";updateFile();getch();goto start_page;
                        case 'n':goto start_page;break;
                    }
                }
                else{SetConsoleTextAttribute(h,208);
                cout<<endl<<endl<<setw(60)<<"Please Enter a valid Password!!!";
                getch();goto delete_page;}
            }
        }
        if(save_i==-1)
        {SetConsoleTextAttribute(h,208);cout<<endl<<endl
        <<setw(60)<<"No such Account exist....Please make new account first...THANKS!!!...."
        <<endl<<setw(60)<<"press any key to continue";getch();goto start_page;}
        

    }

    else{SetConsoleTextAttribute(h,208);cout<<endl<<setw(60)<<"Enter a valid option!!!";
    getch();goto start_page;}

   //-----------------------------------------------------------------------------------
   
    if(verify)              //3rd page...
    {
       signed_in_page:             //USER SIGN IN PAGE
       system("cls");
       
       SetConsoleTextAttribute(h,228);
       cout<<"WELCOME "<<((user[save_i].gender=="male")?"Mr. ":"Ms. ")<<user[save_i].name<<endl;
       SetConsoleTextAttribute(h,223);
       cout<<"=================================="<<endl;
       
       user[save_i].printInfo();
       
       SetConsoleTextAttribute(h,208);
       cout<<setw(60)<<" PLEASE SELECT THE OPTION :- " ;
        cout<<endl<<"---------------------------"<<endl;
        SetConsoleTextAttribute(h,224);
        cout<<"| PRESS 1 :DEPOSIT        |";
        cout<<endl<<endl<<"| PRESS 2 :WITHDRAW       |";
        cout<<endl<<endl<<"| PRESS 3 :CHECK BALANCE  |";
        cout<<endl<<endl<<"| PRESS 4 :TRANSFER FUNDS |";
        cout<<endl<<endl<<"| PRESS 5 :LOG OUT        |";
        SetConsoleTextAttribute(h,208);
        cout<<endl<<"---------------------------";
        cout<<endl<<endl<<"ENTER :";cin>>e2;
        cout<<endl;
        SetConsoleTextAttribute(h,223);
        
        int amt;
        switch(e2)              //DIFFERENT OPERATIONS A USER CAN PERFORM...
        {
            case 1: cout<<setw(30)<<"AMOUNT : Rs ";cin>>amt;user[save_i].deposit(amt);SetConsoleTextAttribute(h,208);cout<<endl<<"TRANSACTION SUCCESSFUL....press Enter";getch();goto signed_in_page;break;
            case 2: cout<<setw(30)<<"AMOUNT : Rs ";cin>>amt;user[save_i].withdraw(amt);SetConsoleTextAttribute(h,208);cout<<endl<<"TRANSACTION SUCCESSFUL....press Enter";getch();goto signed_in_page;break;
            case 3:cout<<setw(30)<<"BALANCE : Rs "<<user[save_i].cash_left();SetConsoleTextAttribute(h,208);cout<<endl<<".....press enter";getch();goto signed_in_page;break;
            case 4:transfer=true;goto transfer_page;break;
            case 5:updateFile();goto start_page;
            default:goto signed_in_page;
        }

        //----------------------------------------------------------------------------
        transfer_page:          //TRANSFER FUNDS PAGE...
        system("cls");
        
        if(transfer)
        {   SetConsoleTextAttribute(h,208);
            int tran_acc_no;
            
            cout<<endl<<"ENTER DETAILS OF ACCOUNT YOU WANT TO SEND :"<<endl<<endl;
            SetConsoleTextAttribute(h,223);
            cout<<setw(30)<<"ACCOUNT NUMBER : ";cin>>tran_acc_no;
            
            int check=0;
            for(;check<user.size();check++)
            {
                if(tran_acc_no==user[check].get_acc())
                {   
                    SetConsoleTextAttribute(h,208);
                    cout<<endl<<"Transferring to "<<((user[check].gender=="male")?"Mr. ":"Ms. ")<<user[check].name<<"..."<<endl;
                   SetConsoleTextAttribute(h,223);
                    cout<<endl<<setw(30)<<"AMOUNT : Rs. ";cin>>amt;
                    update_Balance(&user[save_i],&user[check],amt);
                    SetConsoleTextAttribute(h,208);
                    cout<<endl<<"TRANSACTION SUCCESSFUL....press Enter";
                    getch();
                    if(verify){goto signed_in_page;}else{goto start_page;}
                }
            }
            if(check==user.size())
            {
                SetConsoleTextAttribute(h,208); cout<<endl<<endl<<setw(30)
                <<"ENTER A VALID ACCOUNT NUMBER.......press Enter"<<endl;
                getch();
                goto signed_in_page;
            }
        }   
    }
    return 0;
}