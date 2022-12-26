#include<stdio.h>
#include<locale.h>
#include<math.h>
#include<io.h>
#include<stdlib.h>
//Указатель функции
typedef double (*Tsch) (double);
struct sad {
	double x;
	double x1;
	double x2;
	double sh;
	Tsch func;
};
typedef struct sad SAD;
//Прототипы функции
double sch_y(double);
double sch_v(double);
void t_result(Tsch, double, double, double);
void plot(double x0, double x1, Tsch f);
void file(Tsch f, double xn, double xk, double h, int z);
int* zip(int* array, int n, int m);
int zip2(int* array, int n, int m);
void saddle(int* a, int n, int m);
void pain(int* a, int n, int m);
void main()
{
	setlocale(LC_ALL, "RUS");
	SAD das = {2, -5, 5, 0.5, sch_y};
	int r = -1, n, m;
	char s1, s2, semicolon;
	int* a;
	while (r!=0)
	{
		printf("\n|-----------------------------------------------------------|\n");
		printf("|                 Выполнил: Летников Дионис                 |\n");
		printf("|                     Группа: бИСТ-222                      |\n");
		printf("|Выберите действие:                                         |\n");
		printf("|1. Расчёт функции с одним аргументом                       |\n");
		printf("|2. Расчёт функции по интервалу                             |\n");
		printf("|3. Работа с массивом                                       |\n");
		printf("|                                                           |\n");
		printf("|                                                           |\n");
		printf("|___________________________________________________________|\n");
		scanf("%d",&r);
		switch (r)
		{
		 case 1:
			 printf("Для расчёта первой функции нажмите 1, для второй - 2.\n");
			 scanf("%d", &r);
			 switch (r)
			 {
			  case 1:
				 printf("Введите аргумент x:");
				 scanf("%lf", &das.x);
				 if (das.x == -1) printf("Введено недопустимое значение аргумента");
				 else printf("Y(x) = %lf", das.func(das.x));
				 break;
			  case 2:
				 printf("Введите аргумент x:");
				 scanf("%lf", &das.x);
				 das.func = sch_v;
				 printf("V(x) = %lf", das.func(das.x));
				 break;
			  default:
				  printf("Ошибка!");
				  break;
			 }
			 break;
		 case 2:
			 printf("Для расчёта первой функции нажмите 1, для второй - 2.\n");
			 scanf("%d", &r);
			 switch (r)
			 {
			  case 1:
				 printf("Введите интервал, или полуинтервал, или отрезок:\n");
				 scanf(" %c%lf%c%lf%c", &s1, &das.x1, &semicolon, &das.x2, &s2);
				 printf("Введите шаг табуляции:\n");
				 scanf("%lf", &das.sh);
				 if (s1 == '(') das.x1 += das.sh;
				 if (s2 == ')') das.x2 -= das.sh;
				 das.func = sch_y;
				 t_result(das.func, das.x1, das.x2, das.sh);
				 printf("\nЖелаете вывести график для функции? Да - 1, Нет - 2\n");
				 scanf("%d", &r);
				 switch (r)
				 {
				  case 1:
					  plot(das.x1, das.x2, das.func);
					  break;
				  case 2:
					  break;
				  default:
					  printf("Ошибка!");
					  break;
				 }
				 printf("\nЖелаете занести результаты табуляци в файл? Да - 1, Нет - 2\n");
				 scanf("%d", &r);
				 switch (r)
				 {
				  case 1:
					  file(das.func,das.x1,das.x2,das.sh,1);
					  break;
				  case 2:
					  break;
				  default:
					  printf("Ошибка!");
					  break;
				 }
				 break;
			  case 2:
				 printf("Введите интервал, или полуинтервал, или отрезок:\n");
				 scanf(" %c%lf%c%lf%c", &s1, &das.x1, &semicolon, &das.x2, &s2);
				 printf("Введите шаг табуляции:\n");
				 scanf("%lf", &das.sh);
				 if (s1 == '(') das.x1 += das.sh;
				 if (s2 == ')') das.x2 -= das.sh;
				 das.func = sch_v;
				 t_result(das.func, das.x1, das.x2, das.sh);
				 printf("\nЖелаете вывести график для функции? Да - 1, Нет - 2\n");
				 scanf("%d", &r);
				 switch (r)
				 {
				  case 1:
					 plot(das.x1, das.x2, das.func);
					 break;
				  case 2:
					 break;
				  default:
					 printf("Ошибка!");
					 break;
				 }
				 printf("\nЖелаете занести результаты табуляци в файл? Да - 1, Нет - 2\n");
				 scanf("%d", &r);
				 switch (r)
				 {
				 case 1:
					 file(das.func, das.x1, das.x2, das.sh, 2);
					 break;
				 case 2:
					 break;
				 default:
					 printf("Ошибка!");
					 break;
				 }
				 break;
			  default:
				 printf("Ошибка!");
				 break;
			 }
			 break;
			 case 0:
				 break;
		 case 3:
			 printf("\nВведите количество строк: ");
			 scanf("%d", &n);
			 printf("\nВведите количество столбцов: ");
			 scanf("%d", &m);
			 a = (int*)malloc(n * m * sizeof(int));
			 a = zip(a, n, m);
			 zip2(a, n, m);
			 pain(a,n,m);
			 saddle(a,n,m);
			 break;
		 default:
			 printf("Ошибка!");
			 break;
		}
	}
}
double sch_y(double x)
{
	double y;

	y = ((pow(sin(x), 2) * cos(x)) / (x + 1)) + ((x + 3) / (1 + pow(cos(x), 2)));

	return y;
}
double sch_v(double x)
{
	double y = 0;
	if (x > 0.75)
	{
		y = fabs(x + 1);
	}
	if (x >= 0 && x <= 0.75)
	{
		y = 1 - pow(x, 5);
	}
	if (x < 0)
	{
		y = x + log(fabs(cos(x)));
	}
	return y;
}
void t_result(Tsch f, double xn, double xk, double h)
{
	char t = ' ';
	printf("\n|%3cx%3c|%7cF(x)%6c|", t, t, t, t);
	for (double x = xn; x <= xk; x += h)
	{

		printf("\n| %5.2lf | %15.4lf |", x, f(x));
	}
}
void plot(double x0, double x1, Tsch f)
{
	int SCREENW = 60, SCREENH = 40;//размеры поля вывода в символах
	char screen[60][40];
	double x, y[60];
	double ymin = 0, ymax = 0;
	double hx, hy;
	int i, j;
	int xz, yz;
	hx = (x1 - x0) / (SCREENW - 1);
	for (i = 0, x = x0; i < SCREENW; ++i, x += hx)
	{
		y[i] = f(x); //расчет значений функции для каждой точки поля вывода графика
		if (y[i] < ymin) ymin = y[i];
		if (y[i] > ymax) ymax = y[i];
	}
	hy = (ymax - ymin) / (SCREENH - 1);
	yz = (int)floor(ymax / hy + 0.5);
	xz = (int)floor((0. - x0) / hx + 0.5);
	//построение осей и заполнение массива отображения пробелами
	for (j = 0; j < SCREENH; ++j)
		for (i = 0; i < SCREENW; ++i)
		{
			if (j == yz && i == xz) screen[i][j] = '+';
			else if (j == yz) screen[i][j] = '-';
			else if (i == xz) screen[i][j] = '|';
			else screen[i][j] = ' ';
		}
	//определение положения значения функции на поле вывода
	for (i = 0; i < SCREENW; ++i)
	{
		j = (int)floor((ymax - y[i]) / hy + 0.5);
		screen[i][j] = '*';
	}
	//печать массива символов
	for (j = 0; j < SCREENH; ++j)
	{
		for (i = 0; i < SCREENW; ++i)  putchar(screen[i][j]);
		putchar('\n');
	}
}
void file(Tsch f, double xn, double xk, double h, int z)
{
	if (z == 1)
	{
		FILE* result;
		char name[20] = "tabulation1.txt";
		if ((result = fopen(name, "w")) == NULL)
		{
			printf("Ошибка открытия файла для записи");
			return 0;
		}
		char t = ' ';
		fprintf(result, "\n|%3cx%3c|%7cF(x)%6c|", t, t, t, t);
		for (double x = xn; x <= xk; x += h)
		{
			fprintf(result, "\n| %5.2lf | %15.4lf |", x, f(x));
		}
		fclose(result);
	}
	if (z == 2)
	{
		FILE* result1;
		char name2[20] = "tabulation2.txt";
		if ((result1 = fopen(name2, "w")) == NULL)
		{
			printf("Ошибка открытия файла для записи");
			return 0;
		}
		char t = ' ';
		fprintf(result1, "\n|%3cx%3c|%7cF(x)%6c|", t, t, t, t);
		for (double x = xn; x <= xk; x += h)
		{
			fprintf(result1, "\n| %5.2lf | %15.4lf |", x, f(x));
		}
		fclose(result1);
	}
}
int* zip(int* array, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", (array + i * m + j));
		}
	}
	return array;
}
int zip2(int* array, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%5d ", *(array + i * m + j));
		}
		printf("\n");
	}
	return 0;
}
void saddle(int* a, int n, int m)
{
	int i, j, k, f, min, minpos;
	for (i = 0; i < n; i++)
	{
		min = *(a + i * m + 0);
		minpos = 0;
		for (j = 0; j < m; j++)
		{
			if (*(a + i * m + j) < min)
			{
				min = *(a + i * m + j);
				minpos = j;
			}
		}
		f = 1;
		for (k = 0; k < n; k++)
		{
			if (min < *(a + k * m + minpos)) // Если минимальное значение текущей строки меньше значения в столбце, то есть число не является седловой точкой
			{
				f = 0;
				break;
			}
		}
		if (f == 1)
		{
			printf("\nСедловая точка вашей матрицы = %d(%d;%d)", min, i, minpos);
		}
		else
		{
			printf("\nВ вашей матрице отсутствует седловая точка.");
		}
	}
}
void pain(int* a, int n, int m)
{
	int counter = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (*(a + i * m + j) == 0)
			{
				for (j = 0; j < m; j++)
				{
					if (*(a + i * m + j) < 0)
					{
						counter++;
					}
				}
			}
		}
		printf("\n");
	}
	printf("Количество отрицательных элементов в тех строках, которые содержат хотя бы один нулевой элемент: %d", counter);
}