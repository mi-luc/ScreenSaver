#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include<conio.h>
#include <WinBase.h>
#include <time.h>
#define DIM_X 200
#define DIM_Y 40
#define CHR_STANGA_SUS 201
#define CHR_STANGA_JOS 200
#define CHR_DREAPTA_SUS 187
#define CHR_DREPTA_JOS 188
#define CHR_BARA_VERTICALA 186
#define CHR_BARA_ORIZONTALA 205

typedef struct user 
{
	char user[30];
	char pass[30];
};
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void gotoXY(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void afiseaza_chenar()
{
	system("cls");
	printf("%c", CHR_STANGA_SUS);
	for (int i = 0; i < DIM_X; i++)
		printf("%c", CHR_BARA_ORIZONTALA);
	printf("%c\n", CHR_DREAPTA_SUS);
	for (int i = 0; i < DIM_Y; i++) 
	{
		printf("%c", CHR_BARA_VERTICALA);
		printf("                                                                                                                                                                                                        ");
		printf("%c\n", CHR_BARA_VERTICALA);
	}
	printf("%c", CHR_STANGA_JOS);
	for (int i = 0; i < DIM_X; i++)
		printf("%c", CHR_BARA_ORIZONTALA);
	printf("%c\n", CHR_DREPTA_JOS);
}

void citire(char sir[]) {
	int i = 0;
	sir[i] = _getch();
	while (sir[i] != 13) {
		printf("*");
		i++;
		sir[i] = _getch();
	}
	sir[i] = 0;
}
void LOG()
{
	FILE* f = fopen("file.txt","r");
	int numar, i = 0;
	char option;
	char sir[30];
	fscanf(f,"%d",&numar);
	user* lista;
	lista = (user*)malloc((numar+1)*sizeof(user));
	while (!feof(f))
	{
		fscanf(f,"%s",sir);
		strcpy(lista[i].user,sir);
		fscanf(f, "%s", sir);
		strcpy(lista[i].pass, sir);
		i++;
	}
	int chances = 3,ok=0,copy;
	for (int i = 0; i < 3 && ok==0; i++)
	{
		printf("Username:");
		scanf("%s", sir);
		for(int j=0;j<numar;j++)
		if (strcmp(sir, lista[j].user) == 0)
		{
			ok = 1;
			copy = j;
			break;
		}
		if (ok == 0)
		{
			printf("-> Wrong name...Try again\n");
		}
	}
	if (ok == 0)
		exit(0);
	ok = 0;
	char opt;
	printf("Do you want masked (****) password?[y/n]: ");
	scanf("%c",&opt);
	scanf("%c", &opt);
	while (chances && ok==0)
	{
		printf("Password:");
		if (opt == 'y')
		{
			citire(sir);
		}
		else
		{
			scanf("%s", sir);
		}
			if (strcmp(sir, lista[copy].pass) == 0)
			{
				ok = 1;
			}
		if(chances>1 && ok==0)
		printf("\n->Wrong password...Try again, [%d] more tries\n",chances-1);
		chances--;
	}
	if (chances == 0 && ok==0)
	{
		printf("\n\t\t--------TOO MANY REQUESTS--------");
		exit(0);
	}
	if (ok == 1)
		printf("\n-> Succesful login.");
	fclose(f);
}
void verificari(int* x, int* y,int*vx,int*vy)
{
		if (*x > DIM_X - 1)
		{
			*x = DIM_X - 2;
			*vx = (*vx) * (-1);
		}
		if (*y > DIM_Y - 1)
		{
			*y = DIM_Y - 2;
			*vy = (*vy) * (-1);
		}
		if (*x < 2)
		{
			*x = 2;
			*vx = (*vx) * (-1);
		}
		if (*y < 2)
		{
			*y = 2;
			*vy = (*vy) * (-1);
		}
}
void collision(int xn[],int yn[],int xv[],int yv[],int vx[],int vy[])
{
	for(int i=0;i<30;i++)
		for(int j=0;j<30;j++)
			if (xn[i] == xv[j] && yn[i] == xv[j])
			{
				vx[i] *= -1;
				vy[i] *= -1;
				vx[j] *= -1;
				vy[j] *= -1;
				xn[i] = xn[i] + vx[i];
				yn[i] = yn[i] + vy[i];
				xn[j] = xn[j] + vx[j];
				yn[j] = yn[j] + vy[j];
			}
}
void main()
{
	srand(time(NULL));
	printf("-----------------------------------------------------------------\n");
	printf("----------------ULTIMATE SCREEN SAVER VERSION 1.0----------------\n");
	printf("-----------------------------------------------------------------\n");
	printf("----------------LOGIN SCREEN\n\n");
	printf("->Login credidentials are located in file.txt   /number/username/password\n");
	hidecursor();
	LOG();
	Sleep(1000);
	afiseaza_chenar();
	int x_nou[50], y_nou[50], x_vechi[50], y_vechi[50], viteza_x[50], viteza_y[50];
	char caracter[50];
	for (int i = 0; i < 30; i++)
	{
		x_vechi[i] = rand() % (DIM_X-1)+1;
		y_vechi[i] = rand() % (DIM_Y-1)+1;
		viteza_x[i] = rand() % 5-2;
		viteza_y[i] = rand() % 5 - 2;
		if (viteza_x[i] == 0)
			viteza_x[i]++;
		if (viteza_y[i] == 0)
			viteza_y[i]--;
		if (i % 2 == 0)
			caracter[i] = '+';
		else
			caracter[i] = 'o';
	}
	int k=2;
	while (k>0)
	{
		k++;
		hidecursor();
		if (k % 200 == 0)
		{
			afiseaza_chenar();
			hidecursor();
		}
		for (int i = 0; i < 30; i++)
		{
			x_nou[i] = x_vechi[i] + viteza_x[i];
			y_nou[i] = y_vechi[i] + viteza_y[i];
			gotoXY(x_vechi[i], y_vechi[i]);
			printf(" ");
			verificari(&x_nou[i], &y_nou[i], &viteza_x[i], &viteza_y[i]);
			//collision(x_nou, y_nou,x_vechi,y_vechi, viteza_x, viteza_y);
			gotoXY(x_nou[i], y_nou[i]);
			printf("%c",caracter[i]);

			x_vechi[i] = x_nou[i];
			y_vechi[i] = y_nou[i];
		}
		if (k ==1000)
			k = 1;
		Sleep(45);
	}
}