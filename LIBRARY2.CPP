//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include"iostream.h"
#include"fstream.h"
#include"conio.h"
#include"stdio.h"
#include"process.h"
#include"string.h"
#include"iomanip.h"
#include"graphics.h"

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************



class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
		cout<<"\n\n\t\t\t\tNEW BOOK ENTRY\n";
		cout<<"\n\n\t\tEnter The book no. :";
		cin>>bno;
		cout<<"\n\n\t\tEnter The Name of The Book : ";
		gets(bname);
		cout<<"\n\n\t\tEnter The Author's Name : ";
		gets(aname);
		cout<<"\n\n\n\t\t\t\tBook Created..";
	}

	void show_book()
	{
		cout<<"\n\n\t\tBook no. : "<<bno;
		cout<<"\n\n\t\tBook Name : ";
		puts(bname);
		cout<<"\n\n\t\tAuthor Name : ";
		puts(aname);
	}

	void modify_book()
	{
		cout<<"\n\n\t\t\tBook no. : "<<bno;
		cout<<"\n\n\t\t\tModify Book Name : ";
		gets(bname);
		cout<<"\n\n\t\t\tModify Author's Name of Book : ";
		gets(aname);
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;}


};         //class ends here




class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
public:
	void create_student()
	{
		clrscr();
		cout<<"\n\t\t\t\tNEW STUDENT ENTRY...\n";
		cout<<"\n\n\t\tEnter The admission no.: ";
		cin>>admno;
		cout<<"\n\n\t\tEnter The Name of The Student: ";
		gets(name);
		token=0;
		stbno[0]='/0';
		cout<<"\n\n\t\t\tStudent Record Created..";
	}

	void show_student()
	{
		cout<<"\n\n\t\t\tAdmission no. : "<<admno;
		cout<<"\n\n\t\t\tStudent Name : ";
		puts(name);
		cout<<"\n\n\t\t\tNo of Book issued : "<<token;
		if(token==1)
			cout<<"\n\n\t\t\tBook No "<<stbno;
	}

	void modify_student()
	{
		cout<<"\n\n\t\tAdmission no. : "<<admno;
		cout<<"\n\n\t\tModify Student Name : ";
		gets(name);
	}

	char* retadmno()
	{
		return admno;
	}

	char* retstbno()
	{
		return stbno;
	}

	int rettoken()
	{
		return token;
	}

	void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}

	void report()
	{cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};         //class ends here




//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

fstream fp,fp1;
book bk;
student st;


//***************************************************************
//    	function to write in file
//****************************************************************

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\n\t\t\tDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_student()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\n\n\t\t\tDo you want to add more record..(y/n?) ";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_spb(char n[])
{
	cout<<"\n\t\t\t\tBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\n\t\t SORRY! Book does not available";
	getch();
}

void display_sps(char n[])
{
	cout<<"\n\t\t\t\tSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\n\t\t\tStudent does not exist";
	getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_book()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\t\t\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\t\tEnter The book no. of The book :";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			cout<<"\n\N\t\t\tEnter The New Details of book "<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			cout<<"\n\n\n\t\t\t\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n\n\t\t\t Record Not Found ";
	getch();
}


void modify_student()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\t\t\t\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\t\tEnter The admission no. of The student : ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\n\t\tEnter The New Details of student :"<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t\t\t\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n\t\t\t Record Not Found ";
	getch();
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_student()
{
	char n[6];
	int flag=0;
	clrscr();
	cout<<"\n\n\n\t\t\t\tDELETE STUDENT...";
	cout<<"\n\n\tEnter The admission no. of the Student You Want To Delete : ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
			fp2.write((char*)&st,sizeof(student));
		else
			flag=1;
	}

	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
		cout<<"\n\n\t\t\tRecord Deleted ..";
	else
		cout<<"\n\n\t\t\tRecord not found";
	getch();
}


void delete_book()
{
	char n[6];
	clrscr();
	cout<<"\n\n\n\t\t\t\tDELETE BOOK ...";
	cout<<"\n\n\tEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}

	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	cout<<"\n\n\n\t\t\t\tRecord Deleted ..";
	getch();
}



//***************************************************************
//    	function to display all students list
//****************************************************************

void display_alls()
{
	clrscr();
	fp.open("student.dat",ios::in);
	if(!fp)
	{
		cout<<"\n\t\t\tERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\t\tSTUDENT LIST\n\n";
	cout<<"================================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"================================================================\n";

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
	clrscr();
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"\n\t\t\tERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\t\t\tBook LIST\n\n";
	cout<<"=========================================================================\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
	cout<<"=========================================================================\n";

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
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cout<<"\n\n\t\t\t\tBOOK ISSUE ...";
	cout<<"\n\n\t\tEnter The student's admission no. : ";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
				cout<<"\n\n\t\tEnter the book no. : ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t\t\t Book issued successfully\n\nPlease Note: Write the current date in backside of your book and submit within 15 days fine Rs. 1 for each day after 15 days period";
					}
				}
				if(flag==0)
					cout<<"\n\n\t\tBook no does not exist  ";
			}
			else
				cout<<"\n\n\t\t\tYou have not returned the last book  ";

		}
	}
	if(found==0)
		cout<<"\n\n\t\t\t\tStudent record not exist...";
	getch();
	fp.close();
	fp1.close();
}

//***************************************************************
//    	function to deposit book
//****************************************************************

void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clrscr();
    cout<<"\n\n\t\t\t\tBOOK DEPOSIT ...";
    cout<<"\n\n\t\tEnter The students admission no. :";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				cout<<"\n\n\t\tBook deposited in no. of days : ";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\n\t\tFine has to deposited Rs. : "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout<<"\n\n\t\t Book deposited successfully : ";
			}
		    }
		  if(flag==0)
		    cout<<"\n\n\t\t\tBook no does not exist";
		      }
		 else
			cout<<"\n\n\t\tNo book is issued..please check!!";
		}
	   }
      if(found==0)
	cout<<"\n\n\t\t\tStudent record not exist...";
	getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	clrscr();
	int gdrive=DETECT,gmode;
	initgraph(&gdrive,&gmode,"c:\\tc\\bgi");
	clrscr();
	textbackground(3);
	settextstyle(5,HORIZ_DIR,2);
	outtextxy(150,220,"MADE BY:");
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	outtextxy(230,250,"ANKESH SINGH");
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	outtextxy(285,280,"&");
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
	outtextxy(290,310,"RINKESH KUMAR");
	settextstyle(7,HORIZ_DIR,4);
	outtextxy(75,47,"LIBRARY");
	settextstyle(7,HORIZ_DIR,4);
	outtextxy(220,110,"MANAGEMENT");
	settextstyle(7,HORIZ_DIR,4);
	outtextxy(380,173,"SYSTEM");
	getch();
	closegraph();

}



//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
	clrscr();
	int ch2;
	cout<<"\n\n\n\t\t\t---ADMINISTRATOR MENU---";
	cout<<"\n\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\t\t\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\t\t\t6.CREATE BOOK ";
	cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
	cout<<"\t\t\t8.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t9.MODIFY BOOK ";
	cout<<"\t\t\t\t10.DELETE BOOK ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\n\t\t###########################################################";
	cout<<"\n\t\t\tPlease Enter Your Choice (1-11): ";
	cout<<"\n\t\t###########################################################";
	gotoxy(57,21);cin>>ch2;
	switch(ch2)
	{
		case 1: clrscr();
			write_student();break;
		case 2: display_alls();break;
		case 3:
			char num[6];
			clrscr();
			cout<<"\n\n\t\tPlease Enter The Admission No. : ";
			cin>>num;
			display_sps(num);
			break;
		case 4: modify_student();break;
		case 5: delete_student();break;
		case 6: clrscr();
			write_book();break;
		case 7: display_allb();break;
		case 8: {
			char num[6];
			clrscr();
			cout<<"\n\n\t\tPlease Enter The book No. : ";
			cin>>num;
			display_spb(num);
			break;
			}
		case 9: modify_book();break;
		case 10: delete_book();break;
		case 11: return;
		default:cout<<"\a";
	}
	admin_menu();
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{
	char ch;
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\t\t\t\tMAIN MENU";
		cout<<"\n\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\n\t02. BOOK DEPOSIT";
		cout<<"\n\n\n\t03. ADMINISTRATOR MENU";
		cout<<"\n\n\n\t04. EXIT";
		cout<<"\n\n\n\t\t####################################################";
		cout<<"\n\t\t\tPlease Select Your Option (1-4): ";
		cout<<"\n\t\t####################################################";
	      //	ch=getche();
		char c ;
		gotoxy(57,20);cin>>c;
		switch(c)
		{
			case '1':clrscr();
				 book_issue();
				 break;
			case '2':book_deposit();
				 break;
			case '3':admin_menu();
				 break;
			case '4':exit(0);
			default :cout<<"\a";
		}
	}while(ch!='4');

}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
