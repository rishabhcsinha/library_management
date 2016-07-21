#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

map<string,int> rolllist;
//map<int,int> booklist;
map<string,int> issuelist;

int checkrollno(string str)
{
	int flag=0;
	if (((int)str[0]<=9)&&((int)str[1]<=9)&&((int)str[2]<=9)&&((int)str[5]<=9)&&((int)str[6]<=9))
	{
		flag=1;
	}
	if(str.size()==7)
		flag=1;
	return flag;
}
int checkdate(string str)
{
	int flag=0;
	if (((int)str[0]<=3)&&((int)str[1]<=9)&&((int)str[3]<=1)&&((int)str[4]<=9)&&((int)str[6]<=9)&&((int)str[7]<=9))
	{
		flag=1;
	}
	if(str.size()==8)
		flag=1;
	return flag;
}
class book
{
	public:
	string isbn;
	string title;
	string author_name[5];
	int edition;
	int validity=15;
	int bookid;
	void add_book()
	{
		string str;int i=0;
		cout<<"\nAdd Book...\n";
		cout<<"\nEnter ISBN:";
		cin>>isbn;
		cout<<"\n\nEnter The Name of The Book ";
		cin.ignore();
		char temp[1000];
        cin.getline(temp,1000);
        title.assign(temp);
		//cin>>title;
		cout<<"\n\nEnter The Author's Name (to end enter 0)";
		while(str!="0" && i<5)
		{
			getch();getline(cin,str);author_name[i++]=str;
		}
		//cout<<"Enter Validity:";
		//cin>>validity;
		cout<<"Enter Edition: ";
		cin>>edition;
		bookid=(int)title[0]+validity+edition*19;//unique key
		// while (booklist[bookid]==1)
		// {
		// 	bookid=bookid+1;
		// }

	}
	void show_book()
	{
		int i=0;
		cout<<"\nISBN : "<<isbn;
		cout<<"\nTitle : ";
		cout<<title;
		cout<<"Author Name : ";
		while(author_name[i]!="0")
		{
			cout<<author_name[i++]<<",";
		}
		cout<<"\nValidity : "<<validity;
		cout<<"\nEdition : "<<edition;
    }
    void report()
    {
    	cout<<isbn<<setw(15)<<bookid<<setw(15)<<title<<setw(20)<<edition<<setw(10)<<author_name[0]<<setw(20)<<"\n";
    }
    friend void write_book();
    friend void display_spb(int);
    friend void display_allb();
    friend void book_issue();
	friend void book_deposit();
	friend void delete_book();
	friend void loadbooklist();
	friend class issdep;

};
class student
{
	string rollno;
	string name;
	int sem;
	string phone;
	public:
	void add_student()
	{
		system("cls");
		string str;
	 	cout<<"\nADD STUDENT...\n";
		cout<<"\nEnter The roll no. (e.g. 347CO13)";
		cin>>str;
		if ((rolllist[str]==1) && checkrollno(str))
		{
			cout<<"This Student Already Exists or invalid data"<<endl;
			getch();
			add_student();
		}

		else
			{rollno=str;}
		cout<<"\n\nEnter The Name of The Student ";
		cin>>name;
		cout<<"\n\nEnter The Phone No.";
		cin>>phone;
		sem=16-(((int)rollno[5]-48)*10+((int)rollno[6]-48));
		sem=2*sem;
	}
	void show_student()		
	{
		cout<<"\nRoll no. : "<<rollno;
		cout<<"\nStudent Name : ";
		cout<<name;
		cout<<"\nSemester : "<<sem;
		cout<<"\nPhone No. : "<<phone;

	}
	void report()
	{
		cout<<rollno<<setw(20)<<name<<setw(20)<<sem<<setw(20)<<phone<<setw(20)<<"\n";
	}
	friend void display_alls();
	friend void write_student();
	friend void display_sps(string);
	friend void book_issue();
	friend void book_deposit();
	friend void delete_student();
	friend void loadrolllist();
	friend class issdep;
};
class issdep
{
		string dateofiss;
		string rollno;
		int bookid;
		string dateofdep;
		int fine=0;
	public:
		void add_issue(student &st,book &bk)
		{
			cout<<"\nenter date of issue :(dd/mm/yy) ";
			cin>>dateofiss;
			if (!checkdate(dateofiss))
			{
				cout<<"invalid date"<<endl;
				getch();
				cout<<"\nenter date of issue :(dd/mm/yy) ";
			    cin>>dateofiss;
			}
			rollno=st.rollno;
			bookid=bk.bookid;
			return;
		}
		void deposit()
		{
			cout<<"\n enter date of deposit :(dd/mm/yy)  ";
			cin>>dateofdep;
			if (!checkdate(dateofdep))
			{
				cout<<"invalid date"<<endl;
				getch();
				deposit();
			}
			int mm,dd,yy;
			mm=(((int)dateofdep[3]-48)*10+((int)dateofdep[4]-48))-(((int)dateofiss[3]-48)*10+((int)dateofiss[4]-48));
			dd=(((int)dateofdep[0]-48)*10+((int)dateofdep[1]-48))-(((int)dateofiss[0]-48)*10+((int)dateofiss[1]-48));
			yy=(((int)dateofdep[6]-48)*10+((int)dateofdep[7]-48))-(((int)dateofiss[6]-48)*10+((int)dateofiss[7]-48));
			fine=((yy*365)+(mm*30)+dd)-15;
			if(fine<=0)fine=0;
			if(fine>0) cout<<"Deposit Fine :"<<fine<<endl;
		}
		void issue_report()
		{
			cout<<bookid<<setw(20)<<rollno<<setw(20)<<dateofiss<<setw(20)<<endl;
		}
		void deposits_report()
		{
			cout<<bookid<<setw(10)<<rollno<<setw(15)<<dateofiss<<setw(20)<<dateofdep<<setw(20)<<fine<<setw(10)<<endl;
		}
		friend void delete_student();
		friend void delete_book();
		friend void book_issue();
		friend void book_deposit();
		friend void display_issues();
		friend void display_deposits();
		friend void loadissuelist();
};