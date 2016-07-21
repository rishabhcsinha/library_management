#include "classes.cpp"
#include <bits/stdc++.h>
#include <conio.h>
fstream fp,fp1,fp2,fp3,fp4,fp5,fp6;
student st;
book bk;
issdep dep;
issdep is;

void loadrolllist()
{
	rolllist.clear();
    fp6.open("student.bin",ios::binary|ios::in);
	while(fp6.read((char*)&st,sizeof(student)))
	{
		rolllist[st.rollno] = 1;
		//rolllist.insert(make_pair(st.rollno,1));
	}
	fp6.close();
}

// void loadbooklist()
// {
//     fp6.open("book.bin",ios::binary|ios::in);
// 	while(fp6.read((char*)&bk,sizeof(book)))
// 	{
// 		booklist.insert(make_pair(bk.bookid,1));
// 	}
// 	fp6.close();
// }

void loadissuelist()
{
	fp6.open("issue.bin",ios::binary|ios::in);
	while(fp6.read((char*)&is,sizeof(issdep)))
	{
		if (issuelist[is.rollno]<=5)
		{
			issuelist.insert(make_pair(is.rollno,1));
		}
		else
		{
			issuelist[is.rollno]++;
		}
		
	}
	fp6.close();
}
void write_book()
{
	char ch;
	fp.open("book.bin",ios::binary|ios::out|ios::app);
	do
	{
		system("cls");
		//loadbooklist();
		bk.add_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;//
	}while(ch=='y'||ch=='Y');
	fp.close();
}
void write_student()
{
	char ch;
	fp.open("student.bin",ios::binary|ios::out|ios::app);
	do
	{
		loadrolllist();
		st.add_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void display_sptitle(string str)
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.bin",ios::binary|ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(bk.title==str)
		{
			bk.show_book();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}
void display_spb(string str)
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.bin",ios::binary|ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(bk.isbn==str)
		{
			bk.show_book();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}
void display_sps(string str)//str is rollno
{
	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.bin",ios::binary|ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(str==st.rollno)
		{
			st.show_student();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
		cout<<"\n\nStudent does not exist";
	getch();
}

void delete_student()
{
	string str;
	int flag=0,flag2=1;
	system("cls");
	cout<<"\n\n\n\tDELETE STUDENT...";
	cout<<"\n\nEnter The roll no. of the Student You Want To Delete : ";
	cin>>str;
	fp.open("student.bin",ios::binary|ios::in|ios::out);
	fp2.open("Temp.bin",ios::binary|ios::out);
	fp.seekg(0,ios::beg);
	fp3.open("issue.bin",ios::binary|ios::in);

	while(fp.read((char*)&st,sizeof(student)))
	{
		while(fp3.read((char*)&is,sizeof(issdep)))
		{
			if(str==is.rollno)
			{
				cout<<"\nThis Student has issued a book. SORRY! CAN'T DELETE";
				flag2=0;
				break;
			}
		}
		if(st.rollno!=str && flag2==1)
			fp2.write((char*)&st,sizeof(student));
		else
			flag=1;
	}
	fp3.close();
	fp2.close();
	fp.close();
	remove("student.bin");
	rename("Temp.bin","student.bin");
	if(flag==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\nRecord not found";
	getch();
}
void delete_book()
{
	int str,flag2=1;//it is bookid
	system("cls");
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter The book id of the Book You Want To Delete : ";
	cin>>str;
	fp.open("book.bin",ios::binary|ios::in|ios::out);
	fp2.open("Temp.bin",ios::binary|ios::out);
	fp.seekg(0,ios::beg);
	fp3.open("issue.bin",ios::binary|ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		while(fp3.read((char*)&is,sizeof(issdep)))
		{
			if(str==is.bookid)
			{
				cout<<"\nThis Book has been issued by a student. SORRY! CAN'T DELETE";
				flag2=0;
				break;
			}
		}
		if(bk.bookid!=str && flag2==1)
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}
	fp3.close();
	fp2.close();
	fp.close();
	remove("book.bin");
	rename("Temp.bin","book.bin");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}
void display_alls()
{
	system("cls");
	fp.open("student.bin",ios::binary|ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"=============================================================================\n";
	cout<<"Roll No."<<setw(20)<<"Name"<<setw(20)<<"sem"<<setw(20)<<"phone"<<setw(20)<<"\n";
	cout<<"=============================================================================\n";
    cout<<endl;
	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}
	fp.close();
	getch();
}
//***************************************************************
//    	function to display Books list
//****************************************************************
void display_allb()
{
	system("cls");
	fp.open("book.bin",ios::binary|ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}
	cout<<"\n\n\t\tBook LIST\n\n";
	cout<<"=========================================================================\n";
	cout<<"ISBN"<<setw(15)<<"Book Id"<<setw(15)<<"Title"<<setw(20)<<"edition"<<setw(10)<<"author"<<setw(20)<<"\n";
	cout<<"=========================================================================\n";
    cout<<endl;
	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	getch();
}
//***************************************************************
//    	function to issue book
//****************************************************************
void book_issue()
{
	string str;
	int idofbook,flag2=1;
	int found=0,flag=0;
	system("cls");
	loadissuelist();
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's roll no.";
	cin>>str;
	if(issuelist[str]<5)
		{flag2=1;}
	fp.open("student.bin",ios::binary|ios::in|ios::out);
	fp1.open("book.bin",ios::binary|ios::in|ios::out);
	fp3.open("issue.bin",ios::binary|ios::out|ios::app);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(st.rollno==str)
		{
			found=1;
if(flag2==1)//if student has less than 5 books issued
{
	cout<<"\n\n\tEnter the Book Id ";
	cin>>idofbook;
	while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
	{
		if(bk.bookid==idofbook)
		{
			bk.show_book();
			flag=1;
			is.add_issue(st,bk);
			fp3.write((char*)&is,sizeof(issdep));
			cout<<"\n\n\t Book issued successfully\n";
			cout<<"Fine of Rs. 1 per day after validity over"<<endl;
		}
	}
	if(flag==0)
		cout<<"Book no does not exist"<<endl;
}
else
	cout<<"You have already issued five books. CAN'T ISSUE MORE ";

}
}
if(found==0)
	cout<<"Student record not exist...";
getch();
fp.close();
fp1.close();
fp3.close();
}
//***************************************************************
//    	function to deposit book
//****************************************************************
void book_deposit()
{
	string str;
	int idofbook;
	int found=0,flag=0;
	system("cls");
	cout<<"\n\nBOOK DEPOSIT ...";
	cout<<"\n\n\tEnter The student's roll no.";
	cin>>str;
	cout<<"\n\n\tEnter The Book Id";
	cin>>idofbook;
	fp.open("student.bin",ios::binary|ios::in|ios::out);
	fp1.open("book.bin",ios::binary|ios::in|ios::out);
	fp3.open("issue.bin",ios::binary|ios::out|ios::in);
	fp4.open("temp.bin",ios::binary|ios::out);
	fp5.open("deposits.bin",ios::binary|ios::out|ios::app);
	while(fp3.read((char*)&is,sizeof(issdep)))
	{
		if(is.rollno==str)
		{
			found=1;
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
				if(bk.bookid==idofbook)
				{
					bk.show_book();
					flag=1;
					dep=is;
					dep.deposit();
					cout<<"\n\n\t Book deposited successfully";
					fp5.write((char*)&dep,sizeof(issdep));
				}
			}
		}
		else
			fp4.write((char*)&is,sizeof(issdep));
	}
	if(flag==0)
		cout<<"Book no does not exist";
	if(found==0)
		cout<<"Student record not exist...";
	fp.close();
	fp1.close();
	fp3.close();
	fp4.close();
	fp5.close();
	remove("issue.bin");
	rename("temp.bin","issue.bin");
	getch();
}

void display_issues()
{
	system("cls");
	cout<<"\n\tISSUES LIST\n";
	fp2.open("issue.bin",ios::binary|ios::in);
	cout<<"=========================================================================\n";
	cout<<"bookid"<<setw(20)<<"rollno"<<setw(20)<<"dateofiss"<<setw(20)<<endl;
	cout<<"=========================================================================\n";
	while(fp2.read((char*)&is,sizeof(issdep)))
	{
		is.issue_report();
	}
	fp2.close();
	getch();
}
void display_deposits()
{
	system("cls");
	fp2.open("deposits.bin",ios::binary|ios::in);
	cout<<"\n\tDEPOSITS LIST\n";
	cout<<"=========================================================================\n";
	cout<<"bookid"<<setw(10)<<"rollno"<<setw(15)<<"dateofiss"<<setw(20)<<"dateofdep"<<setw(20)<<"fine"<<setw(10)<<endl;
	cout<<"=========================================================================\n";
	while(fp2.read((char*)&dep,sizeof(issdep)))
	{
		dep.deposits_report();
	}
	fp2.close();
	getch();
}
void admin_menu()
{
	system("cls");
	int ch2;
	string str;
	cout<<"\n\n\n\tLIBRARIAN MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t4.DELETE STUDENT RECORD";
	cout<<"\n\n\t5.CREATE BOOK ";
	cout<<"\n\n\t6.DELETE BOOK ";
	cout<<"\n\n\t7.DISPLAY ISSUED HISTORY ";
	cout<<"\n\n\t8.DISPLAY DEPOSIT HISTORY ";
	cout<<"\n\n\t9.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-9) ";
	cin>>ch2;
	switch(ch2)
	{
		case 1:
		write_student();break;
		case 2: display_alls();break;
		case 3:
		system("cls");
		cout<<"\n\n\tPlease Enter The Roll No. ";
		cin>>str;
		display_sps(str);
		break;
		case 4: delete_student();break;
		case 5:	write_book();break;
		break;
		case 6: delete_book();break;
		case 7:
		display_issues();
		break;
		case 8:
		display_deposits();
		break;
		case 9: return;
		default:cout<<"\a";
	}
	admin_menu();
}
void intro()
{
	char ch;
	do
	{
		system("cls");
		string str;
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
		cout<<"\n\n\t03. LIBRARIAN MENU";
		cout<<"\n\n\t04. DISPLAY ALL BOOKS";
		cout<<"\n\n\t05. SEARCH BOOK BY ISBN";
		cout<<"\n\n\t06. SEARCH BOOK BY TITLE";
		cout<<"\n\n\t07. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-7) ";
		ch=getche();
		switch(ch)
		{
			case '1':system("cls");
			book_issue();
			break;
			case '2':book_deposit();
			break;
			case '3':admin_menu();
			break;
			case '4': display_allb();break;
			case '5':
		system("cls");	
		cout<<"\n\n\tPlease Enter The book ISBN No. ";
		cin>>str;
		display_spb(str);
		break;
		    case '6':
		    system("cls");	
		cout<<"\n\n\tPlease Enter The book Title ";
		cin>>str;
		display_sptitle(str);
		break;
			case '7': goto l1; break;
			default :cout<<"\a";
		}
	} while (ch!='4');
	intro();
	l1:return;
}
int main()
{
	intro();
	return 0;
}