#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

double fun(double x)
{
	return x * x;
}

main(int argc, char **argv)
{
int liczba_procesu,numer_procesu;
int tag=20;
double suma;
int a, b;
a = 0;
b = 3;
double aa = (double)a;
double bb = (double)b;

MPI_Init(&argc, &argv);
int it = 1; 
suma = 0;
MPI_Status status;
MPI_Comm_rank(MPI_COMM_WORLD, &numer_procesu);
MPI_Comm_size(MPI_COMM_WORLD, &liczba_procesu);

if (numer_procesu == liczba_procesu-1)
{
double temp = (double)it / liczba_procesu;
double temp2 = aa + (temp * (bb - aa));

suma = fun(temp2);
it++;
temp = 0;
temp2 = 0;

MPI_Send(&aa, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);
MPI_Send(&bb, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);
MPI_Send(&it, 1, MPI_INT, numer_procesu-1,tag, MPI_COMM_WORLD);
MPI_Send(&suma, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);

}
if (numer_procesu>0 && numer_procesu<liczba_procesu-1)
{
MPI_Recv(&aa, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
MPI_Recv(&bb, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
MPI_Recv(&it, 1, MPI_INT, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
MPI_Recv(&suma, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);

double temp = (double)it / liczba_procesu;
double temp2 = aa + (temp * (bb - aa));

suma = suma + fun(temp2);
it++;

temp = 0;
temp2 = 0;

MPI_Send(&aa, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);
MPI_Send(&bb, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);
MPI_Send(&it, 1, MPI_INT, numer_procesu-1,tag, MPI_COMM_WORLD);
MPI_Send(&suma, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);

}
if(numer_procesu == 0)
{
MPI_Recv(&aa, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
MPI_Recv(&bb, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
MPI_Recv(&it, 1, MPI_INT, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
MPI_Recv(&suma, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);

suma = suma + (fun(bb) / 2) + (fun(aa) / 2);
double h = (bb - aa) / liczba_procesu;

printf("Calka x * x w granicach a = %d i b = %d, Wynik = %lf\n",(int)aa, (int)bb, suma * h);

}
MPI_Finalize();
}