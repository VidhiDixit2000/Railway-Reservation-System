#include <stdio.h>
#include "conio2.h"
#include "rlyres.h"
#include <string.h>
#include <ctype.h>
#include <errno.h>
int enterchoice()
{
    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=0;i<80;i++)
    printf("-");

    printf("\nSelect an Option");
    printf("\n1- View Trains");
    printf("\n2- Book Ticket");
    printf("\n3- View Ticket");
    printf("\n4- Search Ticket No");
    printf("\n5- View All Bookings");
    printf("\n6- View Train Bookings");
    printf("\n7- Cancel Ticket");
    printf("\n8- Cancel Train");
    printf("\n9- Quit");
    printf("\n\nEnter choice:");
    scanf("%d", &choice);
    return choice;
}

void add_trains()
{
    FILE*fp=fopen("d:\\online c pro\\Railway Reservation System\\alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[4]={{"123","BPL","GWA",2100,1500},{"546","BPL","DEL",3500,2240},
        {"345","HBJ","AGR",1560,1135},{"896","HBJ","MUM",4500,3360}};
        fp=fopen("d:\\online c pro\\Railway Reservation System\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        textcolor(RED);
        printf("File saved successfully\n");
        textcolor(YELLOW);
        fclose(fp);
    }
    else
    {
        textcolor(RED);
        printf("File already present\n");
        textcolor(YELLOW);
        fclose(fp);
    }
}

void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=1;i<=80;i++)
        printf("-");
    FILE *fp=fopen("d:\\online c pro\\Railway Reservation System\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    printf("\n\n\n\n");
    fclose(fp);
}

int check_train_no(char *trainno)
{
    FILE *fp=fopen("d:\\online c pro\\Railway Reservation System\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,trainno)==0)
        {
           fclose(fp);
           return 1;
        }
    }
    fclose(fp);
    return 0;
}

int check_mob_no(char*p_mob)
    {
        if(strlen(p_mob)!=10)
            return 0;
        while(*p_mob!='\0')
        {
            if(isdigit(*p_mob)==0)
                return 0;
            *p_mob++;
        }
        return 1;

    }

Passenger* get_passenger_details()
{
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter passenger name:");
    static Passenger psn;
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        return NULL;
    }

    int valid;
    printf("Enter gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("\t\t\t\t\t\t\t");
           gotoxy(1,25);
           printf("Reservation Cancelled");
           getch();
           textcolor(YELLOW);
           return NULL;
        }
        if(psn.gender!='M'&& psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Gender should be M or F(in uppercase)");
            valid=0;
            getch();
            gotoxy(20,2);
            printf("\b ");
            gotoxy(19,2);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,3);

    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if(strcmp(psn.train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_train_no(psn.train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Invalid Train No");
            getch();
            gotoxy(20,3);
            printf("\t\t\t\t\t\t\t");
            gotoxy(20,3);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,4);

    printf("Enter travelling class(First AC-F,Second AC-S):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("\t\t\t\t\t\t\t");
           gotoxy(1,25);
           printf("Reservation Cancelled");
           getch();
           textcolor(YELLOW);
           return NULL;
        }
        if(psn.p_class!='F'&& psn.p_class!='S')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Travelling class should be F or S(in uppercase)");
            valid=0;
            getch();
            gotoxy(49,4);
            printf("\b ");
            gotoxy(48,4);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");

    gotoxy(1,5);
    printf("Enter address:");
    fflush(stdin);
    fgets(psn.address,30,stdin);
    pos=strchr(psn.address,'\n');
    *pos='\0';
    if(strcmp(psn.address,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        return NULL;
    }

    printf("Enter age:");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age=='0')
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("\t\t\t\t\t\t\t");
           gotoxy(1,25);
           printf("Reservation Cancelled");
           getch();
           textcolor(YELLOW);
           return NULL;
        }
        if(psn.age<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Age should be positive");
            valid=0;
            getch();
            gotoxy(11,6);
            printf("\t\t\t\t\t\t\t");
            gotoxy(11,6);
            textcolor(YELLOW);
        }

    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,7);

    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Invalid Mobile No");
            getch();
            gotoxy(21,7);
            printf("\t\t\t\t\t\t\t");
            gotoxy(21,7);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return &psn;
}

int get_booked_ticket_count(char*train_no,char tc)
{
    FILE *fp;
    fp=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0&&pr.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
    FILE*fp=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;

}

int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==30)
    {
        printf("\n\nAll seats full in train no %s in %c",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
     FILE*fp=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","ab");
     if(fp==NULL)
     {
         textcolor(LIGHTRED);
         printf("\n\nSorry file cannot be opened");
         return -1;
     }
     fwrite(&p,sizeof(p),1,fp);
     fclose(fp);
     return ticket_no;

}

int accept_ticket_no()
{
    int ticket_no;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter ticket no:");
    do
    {
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!");
            getch();
            textcolor(YELLOW);
            return 0;
        }
        if(ticket_no<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Ticket number should be positive");
            getch();
            gotoxy(17,1);
            printf("\t\t\t");
            gotoxy(17,1);
            textcolor(YELLOW);

        }
    }while(ticket_no<0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t");
    gotoxy(1,2);
    textcolor(YELLOW);
    clrscr();
    return ticket_no;
}

void view_ticket(int ticket_no)
{

    FILE *fp=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo bookings done yet");
        return;
    }

    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("\nNAME\t\t:%s\nGENDER\t\t:%c\nTRAIN NO\t:%s\nCLASS\t\t:%c\nADDRESS\t\t:%s\nAGE\t\t:%d\nMOBILE NO\t:%s\nTICKET NO\t:%d"
                   ,pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            printf("\n\n");
            found=1;
            break;
        }
    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("No details of Ticket no %d found!",ticket_no);
    }
    fclose(fp);
    return;
}

char* accept_mob_no()
{
    static char mob_no[11];
    char* pos;
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,13,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("\t\t\t\t\t\t\t");
           printf("Cancelling Input....!");
           getch();
           textcolor(YELLOW);
           return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Invalid Mobile No");
            getch();
            gotoxy(21,1);
            printf("\t\t\t");
            gotoxy(21,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}

int* get_ticket_no(char* p_mob_no)
{
    int count=0;
    FILE* fp=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","rb");
    if (fp==NULL)
    {
        return NULL;
    }

    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int*p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            *(p+i)=pr.ticketno;
            i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}

void view_all_tickets(char* pmob_no,int* pticket_no)
{
    int i;
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n\nSorry!No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for mobile no %s",pmob_no);
    printf("\n\nTICKET NO\n");
    printf("----------");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));

        textcolor(WHITE);
        printf("\n\n\nPress any key to go back to the main screen");
        getch();
    return;
}

char* accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
           textcolor(LIGHTRED);
           gotoxy(1,25);
           printf("\t\t\t\t\t\t\t");
           gotoxy(1,25);
           printf("Cancelling Input....!");
           getch();
           textcolor(YELLOW);
           return NULL;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error!Invalid train Number");
            getch();
            gotoxy(20,1);
            printf("\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}

void view_bookings(char* train_no)
{
    FILE* fp=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","rb");
    if (fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo bookings done yet");
        return;
    }

    Passenger pr;
    int i;
    int found=0;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=1;i<=80;i++)
       printf("-");
    int row=3;
    while(fread(&pr,sizeof(Passenger),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            found=1;
            row++;
        }
    }
    if(found==0)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo details of the train %s found",train_no);
    }
    fclose(fp);
}

int cancel_ticket(int ticket_no)
{
    FILE *fs;
    fs=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","rb");
    if(fs==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo bookings done yet");
        printf("\nError code is %d\n",errno);
        perror("Caused by");
        return -1;
    }
    FILE *fd=fopen("d:\\online c pro\\Railway Reservation System\\temp.dat","wb");
    if(fd==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nError code is %d\n",errno);
        perror("Caused by");
        return -1;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fs)==1)
    {
        if(pr.ticketno!=ticket_no)
            fwrite(&pr,sizeof(pr),1,fd);
         else
                found=1;
    }
    fclose(fs);
    fclose(fd);
    int result;
    if (found==0)
    {
       result=remove("d:\\online c pro\\Railway Reservation System\\temp.dat");
       if(result!=0)
       {
         printf("\nError code is %d\n",errno);
         perror("\nCaused by");
         return 2;
       }

    }
    else
    {
         result=remove("d:\\online c pro\\Railway Reservation System\\allbookings.dat");
         if(result!=0)
         {
              printf("\nError code is %d\n",errno);
              perror("Caused by");
              return 2;
         }

         result=rename("d:\\online c pro\\Railway Reservation System\\temp.dat",
                  "d:\\online c pro\\Railway Reservation System\\allbookings.dat");
         if(result!=0)
         {
            printf("\nError code is %d\n",errno);
            perror("Caused by");
            return 2;
          }

    }
     return found;
}

int cancel_train(char*train_no)
{
    FILE *fs=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","rb");
    if(fs==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo bookings done yet");
        printf("\nError code is %d\n",errno);
        perror("Caused by");
        return -1;
    }
    FILE *fd=fopen("d:\\online c pro\\Railway Reservation System\\temp.dat","wb");
    if(fd==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nError code is %d\n",errno);
        perror("Caused by");
        return -1;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fs)==1)
    {
        if(strcmp(pr.train_no,train_no)!=0)

            fwrite(&pr,sizeof(pr),1,fd);
        else
                found=1;
    }
    fclose(fs);
    fclose(fd);
    int result;
    if (found==0)
    {
       result=remove("d:\\online c pro\\Railway Reservation System\\temp.dat");
       if(result!=0)
       {
         printf("\nError code is %d\n",errno);
         perror("\nCaused by");
         return 2;
       }

    }
    else
    {
         result=remove("d:\\online c pro\\Railway Reservation System\\allbookings.dat");
         if(result!=0)
         {
              printf("\nError code is %d\n",errno);
              perror("Caused by");
              return 2;
         }

         result=rename("d:\\online c pro\\Railway Reservation System\\temp.dat",
                  "d:\\online c pro\\Railway Reservation System\\allbookings.dat");
         if(result!=0)
         {
            printf("\nError code is %d\n",errno);
            perror("Caused by");
            return 2;
          }

    }
    return found;
}

void view_all_bookings()
{
    FILE *fp=fopen("d:\\online c pro\\Railway Reservation System\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo bookings done yet");
        printf("\nError code is %d\n",errno);
        perror("Caused by");
        return;
    }
    Passenger pr;
    int i;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\tTRAIN NO");
    for(i=1;i<=80;i++)
       printf("-");
    int row=3;
    while(fread(&pr,sizeof(Passenger),1,fp)==1)
    {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\t%s\n",pr.gender,pr.age,pr.mob_no,pr.train_no);
            row++;
    }
    if(row==3)
    {
        textcolor(LIGHTRED);
        printf("\n\nNo bookings found");
    }
    fclose(fp);
    return;
}





