/*
 *  library.c -Library manage tool
 *
 *  Copyright (C) 2016, 2017 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program file is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include "slib.h"

ccp ver ="1.0.1";
const char bok[6]="b";
const char usr[6]="u";

typedef struct Book
{
	char bkname[100];
	char bktype[30];
	char bkloc[90];
	char bknum[21];
} BOOK;

typedef struct User
{
	char urname[20];
	char urnum[20];
} USER;

int main( int argc,ccp argv[] )
{
	BOOK bk;
	USER ur;
	int content,counter,torf,buf3;
	FILE *fp,*np;
	char *buf,*buf2,*boker,*usrer;

	do
	{
		printf("1=Add book\n2=Check book number by book name\n3=Check book info by"
		       " book number\n4=Lend out book\n5=Add user\n6=Return book\n");
		scanf("%d",&content);
		switch(content)
		{
		case 1:
		{
			printf("Enter the name of the book:");
			fflush(stdin);
			fgets(bk.bkname,80,stdin);
			printf("\nEnter the type of the book:");
			fflush(stdin);
			fgets(bk.bktype,5,stdin);
			printf("\nEnter the number of the book:");
			fflush(stdin);
			fgets(bk.bknum,20,stdin);
			printf("\nEnter the location:");
			fflush(stdin);
			fgets(bk.bkloc,80,stdin);
			strcpy(bk.bktype,strtok(bk.bktype,"\n"));
			strcpy(bk.bknum,strtok(bk.bknum,"\n"));
			strcpy(bk.bkname,strtok(bk.bkname,"\n"));
			strcpy(bk.bkloc,strtok(bk.bkloc,"\n"));
			buf=bk.bktype;
			buf=strncat(buf,bk.bknum,20);
			buf=strtok(buf,"\n");
			boker = (char*)bok;
			buf=mtscat(3,boker,buf,".book");
			printf("%s\n",buf);
			fp=fopen(buf,"r");
			if(!fp) {}
			else
			{
				printf("This book is already exist!");
				printf("Failed!");
				fclose(fp);
				break;
			}
			fp = fopen(buf,"w");
			if(!fp)
			{
				prterr("flie opening error!");
				printf("Failed!");
				break;
			}
			fprintf(fp,"\nbook_name:%s\nbook_location:%s\nbook_type_number:%s%s"
	        		,bk.bkname,bk.bkloc,bk.bktype,bk.bknum);
			fclose(fp);
			fp=fopen("index.txt","a+");
			if(!fp)
			{
				prterr("flie opening error!");
				printf("Failed!");
				break;
			}
			fprintf(fp,"%s\t%s\t%s\n",bk.bktype,bk.bknum,bk.bkname);
			fclose(fp);
			fp = NULL;
			printf("\nSuccess!\n");
			break;
		}
		case 2:
		{
			printf("Enter the book name:");
			fflush(stdin);
			fgets(bk.bkname,80,stdin);
			fp=fopen("index.txt","r");
			if(!fp)prterr("index.txt not installed!");
			rewind(fp);
			buf=bk.bkname;
			buf=strtok(buf,"\n");
			while(1)
			{
				fgets(buf2,80,fp);
				if(strstr(buf2,buf)!=NULL)
				{
					torf = 1;
					printf("\n%s",buf2);
					break;/*while(1)*/
				}
				if(feof(fp))
				{
					torf = 0;
					break;
				}
			}
			if(torf == 0)
				printf("No such book!");
			fclose(fp);
			fp = NULL;
			break;
		}
		case 3:
		{
			printf("Enter the book type:");
			fflush(stdin);
			fgets(bk.bktype,50,stdin);
			printf("Enter the book number:");
			fflush(stdin);
			fgets(bk.bknum,50,stdin);
			buf = bk.bktype;
			buf2 = bk.bknum;
			buf = strtok(buf,"\n");
			buf2 = strtok(buf2,"\n");
			boker = (char*)bok;
			buf = strcat(buf,buf2);
			buf = strcat(boker,buf);
			buf = strcat(buf,".book");
			fp = fopen(buf,"a+");
			if(!fp)
				printf("No such book!");
			prtfile(fp);
			break;
		}
		case 4:
		{
			printf("Enter user number:") ;
			fflush(stdin);
			fgets(ur.urnum,20,stdin);
			printf("Enter book type:");
			fflush(stdin);
			fgets(bk.bktype,29,stdin);
			printf("Enter book number:");
			fflush(stdin);
			fgets(bk.bknum,20,stdin);
			strcpy(ur.urnum,strtok(ur.urnum,"\n"));
			strcpy(bk.bktype,strtok(bk.bktype,"\n"));
			strcpy(bk.bknum,strtok(bk.bknum,"\n"));
			buf = ur.urnum;
			buf = strtok(buf,"\n");
			buf = strcat(buf,".user");
			usrer = (char*)usr;
			buf = strcat(usrer,buf);
			buf = strtok(buf,"\n");
			printf("%s",buf);
			fp = fopen(buf,"a+");
			if(!fp)prterr("file opening error!");
			rewind(fp);
			fprintf(fp,"Lended book:%s%s\n",&bk.bktype,&bk.bknum);
			fclose(fp);
			buf = bk.bktype;
			buf2 = bk.bknum;
			buf = strtok(buf,"\n");
			buf = strcat(buf,buf2);
			buf = strtok(buf,"\n");
			boker = (char*)bok;
			buf = strcat(boker,buf);
			buf = strtok(buf,"\n");
			buf = strcat(buf,".book");
			buf = strtok(buf,"\n");
			fp = fopen(buf,"a+");
			if(!fp)prterr("file opening error!");
			rewind(fp);
			fprintf(fp,"Lended to:%s",&ur.urnum) ;
			fclose(fp);
			fp = NULL;
			printf("Success!") ;
			break;
		}
		case 5:
		{
			printf("Enter username:");
			fflush(stdin);
			fgets(ur.urname,19,stdin);
			printf("Enter user number:");
			fgets(ur.urnum,19,stdin);
			strcpy(ur.urname,strtok(ur.urname,"\n"));
			strcpy(ur.urnum,strtok(ur.urnum,"\n"));
			buf = ur.urnum;
			usrer = (char*)usr;
			buf = strcat(usrer,strcat(buf,".user"));
			printf("%s\n",buf);
			fp = fopen(buf,"w+");
			if(!fp)
			{
				prterr("file opening error!");
				printf("Failed!");
				break;
			}
			fprintf(fp,"\nusername:%s\nusernumber:%s",&ur.urname,&ur.urnum);
			fclose(fp);
			break;
			printf("Success!");
			break;
		}
		case 6:
		{
			printf("Enter returning book type:");
			fflush(stdin);
			fgets(bk.bktype,20,stdin);
			printf("Enter returning book number:");
			fflush(stdin);
			fgets(bk.bknum,80,stdin);
			printf("Enter returning user number:");
			fgets(ur.urnum,20,stdin);
			buf = ur.urnum;
			usrer = (char*)usr;
			buf = strtok(buf,"\n");
			buf = strcat(usrer,buf);
			buf = strcat(buf,".user") ;
			fp = fopen(buf,"a+");
			if(!fp)prterr("file opening error!");
			rewind(fp);
			fgets(buf2,40,fp);
			buf3=strlen(buf2);
			fseek(fp,(long)buf3,SEEK_SET);
			np = fopen("1.temp","w+");
			if(!np)prterr("file opening error!");
			iofile(fp,np);
			remove(buf);
			rename("1.temp",buf);
			freopen("1.temp","w+",np);
			if(!np)prterr("file opening error!");
			buf = bk.bknum;
			buf2 = bk.bktype;
			buf = strtok(buf,"\n");
			buf = strtok(buf,"\n");
			boker = (char*)bok;
			buf = strcat(buf2,buf);
			buf = strcat(boker,buf);
			buf = strcat(buf,".book");
			freopen(buf,"a+",fp);
			if(!fp)prterr("file opening error!");
			fgets(buf2,40,fp);
			buf3=strlen(buf2);
			fseek(fp,(long)buf3,SEEK_SET);
			iofile(fp,np);
			remove(buf) ;
			rename("1.temp",buf);
			fclose(fp);
			fclose(np);
			printf("Success!");
			break;
		}
		}
		printf("\nEnter \"e\"to quit,enter other key to continue:");
		fflush(stdin);
		buf3=getchar();
		buf="\0",buf2="\0";
		system("cls");
	}
	while(buf3!=101);
	return 0;
}
