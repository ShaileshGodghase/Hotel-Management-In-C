#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<time.h>
void format_date(char ndate[])
{
char t;
  //swapping index 0 and 3
  t=ndate[0];
  ndate[0]=ndate[3];
  ndate[3]=t;
  //swapping index 1 and 4
  t=ndate[1];
  ndate[1]=ndate[4];
  ndate[4]=t;
}
void assign_ret_date(char original_str[])
{
// retrieve current date and over-write on NOT
  int x;
  char idate[10];
   x=strlen(original_str);
     //date swapping
  _strdate(idate);
  format_date(idate);
  original_str[x-3]='\0';
  strcat(original_str,idate);
}

void write_to_temp_file(char data_to_write[])
{
	// write data_to_write into a tempory file
	int i;
	FILE *fp;
	fp = fopen("temfhote.txt","a");
	i=0;
	while(data_to_write[i] != '\0')
	{
		fputc(data_to_write[i],fp);
		i++;
	}
	fputc('\n',fp);
	fclose(fp);
}

int contains_not(char original_str[])
{
	// in this function we will check whether original_str[] contains NOT or not.
	// only compare last three characters
	// length - 3
	// return 1 if NOT is present else return 0
	int l;
	l=strlen(original_str);
	if(original_str[l-3]=='N' && original_str[l-2]=='O' && original_str[l-1]=='T')
	return 1;
	else
	return 0;
}

void replace(char ar[])
{   int i=0;
    while(ar[i]!='\0')
     {
	   if(ar[i]==32)
	   {
		 ar[i]='_';
	   }
	i++;
     }
}

void replace_space_with_tab(char ar[])
{
	int i=0;
	while(ar[i] != '\0')
	{
		if(ar[i] == ' ')
		{
		ar[
		i] = '\t';
		}
		i++;
	}
}
int search_room_num_in_line(char original_str[],char room[])
{
// in this function we will check the presence of room[] into original_str[]
// only by comparing first five characters original_str[]
// i.e. from 0 to 4 only
// returns 1 if present else return 0
   int i,x=0;
  // printf("\nSearching %s in line %s\n",room,original_str);

   for(i=0;i<5;i++)
   {
	if(room[i] == original_str[i])
	{
	x=1;
	}
   }
   return x;
}

void copy_file_data(char *source_file_name, char *desti_file_name)

{
	FILE *fpr, *fpw;
	char ch;

	fpr = fopen(source_file_name,"r");
	fpw = fopen(desti_file_name,"w");

	do
	{
	ch = fgetc(fpr);
		if(ch!=EOF)
		{
		fputc(ch,fpw);

		}
	}while(ch!=EOF);

	fclose(fpr);
	fclose(fpw);
}

void check_out()
{
	// we will retrieve line-by-line data from file "newcusto.txt"
	// and each line is sent to search_book_num_in_line(original_line,booknum)
	// if this function returns 1 means this line has expected book number
	// now check whether the same line ends with NOT or not
	// if it ends with NOT then update the line's contents apply return date to it
	FILE *fp = NULL;
	FILE *fpw;
	char ch,c;
	char data[200],room[10];
	int i,a,b,flag=1;

	fflush(stdin);
	printf("Enter room number:\n ");
	gets(room);
	fflush(stdin);

	fp = fopen("newcusto.txt","r");

	if(fp==NULL)
	{
		printf("FILE NOT FOUND\n");
	}
	else
	{

		do
		{
			i=0;
			do
			{
				ch = fgetc(fp);
				if(ch!='\n')
				{
					data[i] = ch;
					i++;
				}
				if(ch==EOF)
				{
				break;
				}
			}while(ch!='\n');
			data[i] = '\0';
			a = search_room_num_in_line(data,room);
			if(a==1)
			{
				b = contains_not(data);
			}

			if(a==1 && b==1)
			{
			//means this line contains ret_bknum and also has NOT
			// now send this line to update ret_date instead of NOT
			flag=0;
			assign_ret_date(data);
			}
			// now write this issuedata wali line to a temp file
			write_to_temp_file(data);
		}while(ch!=EOF);
		if(flag==1)
		printf("No results found\n");
		fclose(fp);
		copy_file_data("temfhote.txt","newcusto.txt");
		fpw = fopen("temfhote.txt","w");
		fclose(fpw);
		printf("Successfully checkout....!\n");
	}
}

void customer_details()
{ char name[25],adhar[15],address[30],room[3],cdate[50];
  FILE *fp;
  _strdate(cdate);
  format_date(cdate);

  printf("WELCOME..!\n");
  fp=fopen("newcusto.txt","a");
  fflush(stdin);
  printf("Enter Room NO. to Stay:\n");
  fflush(stdin);
  gets(room);
  printf("Enter Name of Customer:\n");
  fflush(stdin);
  gets(name);
  replace(name);
  printf("Enter adhar card No.:\n");

  fflush(stdin);
  gets(adhar);
  printf("Enter address of Customer:\n");
  fflush(stdin);
  gets(address);
  replace(address);
  fprintf(fp,"%s %s %s %s %s NOT\n",room,name,adhar,address,cdate);
  fclose(fp);
  printf("successfully check in...!");
}
void check_in()
{ int a,d,t,s;
  ABC:
  printf("Press 1 for AC ROOMS:\n");
  printf("Press 2 for NON AC ROOMS:\n");
  scanf("%d",&a);
  switch(a)
  { case 1 : printf("1 Day=1000 Rs.\n");
	     printf("Enter how many days do you want to stay:\n");
	     scanf("%d",&d);
	     t=d*1000;
	     printf("Your Total bill will be %d\n",t);
	     printf("do you want to continue then press 2:\n");
	     scanf("%d",&s);
	     if(s==2)
	     customer_details();
	     else
	     printf("Thanks for coming...!\n");
	     break;
    case 2 : printf("1 Day=500 Rs.\n");
	     printf("Enter how many days do you want to stay:\n");
	     scanf("%d",&d);
	     t=d*500;
	     printf("Your Total bill will be %d\n",t);
	     printf("do you want to continue then press 1:\n");
	     scanf("%d",&s);
	     if(s==1)
	     customer_details();
	     else
	     printf("Thanks for Coming..!\n");
	     break;
    default : printf("Enter a Valid Code:\n");
	      if(a!=1 && a!=2)
	      goto ABC;
	      break;
 }
}

void search_content(char search_data[])
{
	FILE *fp;
	int i,j,k,len,ind,ret,flag=1;
	char data[100],newdata[25];
	char ch;
	fp=NULL;
	len = strlen(search_data);
	fp = fopen("newcusto.txt","r");
	if(fp==NULL)
	{
		printf("FILE NOT FOUND\n");
	}
	else
	{
		do
		{
			i=0;
			flag=1;
			do
			{
				ch = fgetc(fp);
				if(ch!='\n')
				{
					data[i]=ch;
					i++;
				}
				if(ch==EOF)
				{
					break;
				}
			}while(ch!='\n');
			data[i] = '\0';
			// replace_space(data);
			// i contains length of data
			for(j=0;j<i-len;j++)
			{
				k=j;
				ind=0;
				while(k<j+len)
				{
					newdata[ind] = data[k];
					ind++;
					k++;
				}
				newdata[ind] = '\0';
				replace(newdata);
				replace(search_data);
				ret = strcmp(newdata,search_data);
				if(ret==0)
				{
					replace_space_with_tab(data);
					printf("%s\n",data);

				}


			}
		}while(ch!=EOF);
		fclose(fp);
	 //end of else
	}
}
void search()
{
	int ch;
	char search_data[25];

	printf("1 - Search by Room Number:\n");
	printf("2 - Search by Name:\n");
	printf("3 - Search by Adhar NO.:\n");
	printf("Provide your choice : ");
	scanf("%d",&ch);
	fflush(stdin);

	switch(ch)
	{
	case 1: printf("Enter Room number to search : ");
		gets(search_data);
		fflush(stdin);
		search_content(search_data);
		break;
	case 2: printf("Enter Name To Search:\n");
		gets(search_data);
		fflush(stdin);
		search_content(search_data);
		break;
	case 3: printf("Enter Adhar NO.to search : ");
		gets(search_data);
		fflush(stdin);
		search_content(search_data);
		break;

		default:printf("Invalid choice\n");

	} //end of switch case
}
void backup()
{
	copy_file_data("newcusto.txt","bkpcusto.txt");
	printf("Successfully Backup...!\n");
}
int list_of_all_customer(int show_data)
{
	FILE *fp;
	char data[200];
	int i,count=0;
	char ch;
	fp=NULL;

	fp = fopen("newcusto.txt","r");
	if(fp==NULL)
	{
	printf("FILE NOT FOUND\n");
	}
	else
	{
		do
		{
			i=0;
			do
			{
				ch = fgetc(fp);
				if(ch!='\n')
				{
					data[i] = ch;
					i++;
				}
				if(ch==EOF)
				{
				break;
				}
			}while(ch!='\n');
			data[i] = '\0';
			if(show_data==1)
			{
				// now replace space with spaces with '\t'
				replace_space_with_tab(data);

				printf("%s\n\n",data);
				if(count%12 == 0)
				{
					printf("\nPress Any key for Next Page.... ");
					getch();
					clrscr();
					printf("\n");
				}
			}
			count++;
		}while(ch!=EOF);
		fclose(fp);
		return count;
	}
}


void main()
{  int n,count;
   clrscr();
   ABC:
   do
   {
   printf("Press 1 To checkin:\n");
   printf("Press 2 To checkOut:\n");
   printf("Press 3 To search:\n");
   printf("Press 4 To Backup:\n");
   printf("Press 5 To Get List of All Customers:\n");
   printf("Press 6 To Get Total Count of Customers:\n");
   printf("Press 7 To EXIT:\n");
   scanf("%d",&n);
   fflush(stdin);
      switch(n)
      {  case 1 : check_in();
		  break;
	 case 2 : check_out();
		  break;
	 case 3 : search();
		  break;
	 case 4 : backup();
		  break;
	 case 5 : list_of_all_customer(1);
		  break;
	 case 6 : count=list_of_all_customer(0);
		  printf("Total Customer:%d\n",count);
		  break;
	 case 7 : exit(0);
		  break;
	 default : printf("INVALID CODE..!\n");
		   goto ABC;
      };
   }while(1);
   getch();
}