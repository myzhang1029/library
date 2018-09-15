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

#include <slib.h>
#include <stdlib.h>
#include <string.h>

const char *ver = "0.1.2";

typedef struct Book
{
	char bkname[100];
	char bktype[30];
	char bkloc[90];
	char bknum[20];
} BOOK;

typedef struct User
{
	char urname[20];
	char urnum[20];
} USER;

int main(int argc, char *argv[])
{
	BOOK bk;
	USER ur;
	int content, counter;
	FILE *fp, *np;

	if (chdir("library.db") == -1)
	{
		perror("chdir: library.db");
		exit(1);
	}
	while (1)
	{
		printf("1=Add book\n2=Check book number by book name\n3=Check book info by"
		       " book number\n4=Lend out book\n5=Add user\n6=Return book\n");
		content = getchar();
		switch (content)
		{
			case '1':
				printf("Enter the name of the book:");
				fflush(stdin);
				fgets(bk.bkname, 100, stdin);
				printf("\nEnter the type of the book:");
				fflush(stdin);
				fgets(bk.bktype, 30, stdin);
				printf("\nEnter the number of the book:");
				fflush(stdin);
				fgets(bk.bknum, 20, stdin);
				printf("\nEnter the location:");
				fflush(stdin);
				fgets(bk.bkloc, 90, stdin);
				*strchr(bk.bktype, '\n') = 0;
				*strchr(bk.bknum, '\n') = 0;
				*strchr(bk.bkname, '\n') = 0;
				*strchr(bk.bkloc, '\n') = 0;
				fp = fopen(bk.bknum, "r");
				if (fp)
				{
					printf("A book with the same number already exists!");
					printf("Failed!");
					fclose(fp);
					break;
				}
				fp = fopen(bk.bknum, "w");
				if (!fp)
				{
					perror("fopen: book");
					break;
				}
				fprintf(fp, "\nbook_name:%s\nbook_location:%s\nbook_type_number:%s%s", bk.bkname,
					bk.bkloc, bk.bktype, bk.bknum);
				fclose(fp);
				fp = fopen("index", "a+");
				if (!fp)
				{
					perror("fopen: index");
					break;
				}
				fprintf(fp, "%s\t%s\n", bk.bknum, bk.bkname);
				fclose(fp);
				printf("\nSuccess!\n");
				break;
			case '2':
			{
				int found = 0;
				printf("Enter the book name:");
				fflush(stdin);
				fgets(bk.bkname, 80, stdin);
				fp = fopen("index", "r");
				if (!fp)
				{
					perror("fopen: index");
					break;
				}
				rewind(fp);
				*strchr(bk.bkname, '\n') = 0;
				while (1)
				{
					char trythisline[128];
					fgets(trythisline, 128, fp);
					if (strstr(trythisline, bk.bkname) != NULL)
					{
						found = 1;
						printf("\n%s", trythisline);
						break; /*while(1)*/
					}
					if (feof(fp))
					{
						break;
					}
				}
				if (found == 0)
					printf("No such book!");
				fclose(fp);
				break;
				case '3':
					printf("Enter the book number:");
					fflush(stdin);
					fgets(bk.bknum, 20, stdin);
					*strchr(bk.bkname, '\n') = 0;
					fp = fopen(bk.bkname, "a+");
					if (!fp)
						printf("No such book!");
					iofile(fp, stdin);
					break;
				case '4':
					printf("Enter user number:");
					fflush(stdin);
					fgets(ur.urnum, 20, stdin);
					printf("Enter book number:");
					fflush(stdin);
					fgets(bk.bknum, 20, stdin);
					*strchr(ur.urnum, '\n') = 0;
					*strchr(bk.bknum, '\n') = 0;
					fp = fopen(ur.urnum, "a+");
					if (!fp)
					{
						perror("fopen: user");
						break;
					}
					fseek(fp, 0L, SEEK_END);
					{
						char line[30];
						fgets(line, 30, fp);
						if (strstr(line, "borrowed: "))
							printf("Book already borrowed by %s", strchr(line, ' '));
						break;
					}
					fprintf(fp, "borrowed: %s\n", bk.bknum);
					fclose(fp);
					if (!fp)
					{
						perror("fopen: book");
						break;
					}
					fseek(fp, 0L, SEEK_END);
					fprintf(fp, "\nLended to:%s", ur.urnum);
					fclose(fp);
					printf("Success!");
					break;
				case '5':
					printf("Enter username:");
					fflush(stdin);
					fgets(ur.urname, 19, stdin);
					printf("Enter user number:");
					fgets(ur.urnum, 19, stdin);
					*strchr(ur.urname, '\n') = 0;
					*strchr(ur.urnum, '\n') = 0;
					fp = fopen(ur.urnum, "w+");
					if (!fp)
					{
						perror("fopen: user");
						break;
					}
					fprintf(fp, "\nusername:%s\nusernumber:%s", ur.urname, ur.urnum);
					fclose(fp);
					printf("Success!");
					break;
				case '6':
					printf("Enter returning book number:");
					fflush(stdin);
					fgets(bk.bknum, 80, stdin);
					printf("Enter returning user number:");
					fgets(ur.urnum, 20, stdin);
					*strchr(bk.bknum, '\n') = 0;
					*strchr(ur.urnum, '\n') = 0;
					fp = fopen(ur.urnum, "a+");
					if (!fp)
					{
						perror("fopen: user");
						break;
					}
					rewind(fp);
					fgets(buf2, 40, fp);
					buf3 = strlen(buf2);
					fseek(fp, (long)buf3, SEEK_SET);
					np = fopen("1.temp", "w+");
					if (!np)
						prterr("file opening error!");
					iofile(fp, np);
					remove(buf);
					rename("1.temp", buf);
					freopen("1.temp", "w+", np);
					if (!np)
						prterr("file opening error!");
					buf = bk.bknum;
					buf2 = bk.bktype;
					buf = strtok(buf, "\n");
					buf = strtok(buf, "\n");
					boker = (char *)bok;
					buf = strcat(buf2, buf);
					buf = strcat(boker, buf);
					buf = strcat(buf, ".book");
					freopen(buf, "a+", fp);
					if (!fp)
						prterr("file opening error!");
					fgets(buf2, 40, fp);
					buf3 = strlen(buf2);
					fseek(fp, (long)buf3, SEEK_SET);
					iofile(fp, np);
					remove(buf);
					rename("1.temp", buf);
					fclose(fp);
					fclose(np);
					printf("Success!");
					break;
				case 'q':
					exit(0);
				default:
					fprintf("Unknow option: `%c'\n", content);
			}
			fail:
		}
	fatal:
		return 0;
	}
