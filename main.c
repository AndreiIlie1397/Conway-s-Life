#include <stdio.h>
#include <stdlib.h>
void citire(char *x, int *N, int *M, int *k, int *y, char a[1000][1000]) //functia de citire a datelor de intrare
{
    int i, j;
    //N este numarul de linii
    //M este numarul de coloane
    //k este numarul de evolutii
  scanf("%c %d %d %d", *&x, *&M, *&N, *&k);
  if(*x!='P'  && *x!='T') //alta litera introdusa
  {
      *y=1;
      return ;
  }
  for(i=1; i<=*N; i++)     //citirea matricei
        for(j=1; j<=*M; j++)
        scanf("%d", &a[i][j]);
}
void vecini(char x, int i, int j, char a[1000][1000], char b[100][100], char v[1000][1000]) //functia de construire a matricei vecinilor
{
    if(x=='P')
    {
      v[i][j]=0;
       if(a[i-1][j-1]==1)
        v[i][j]=v[i][j]+1;
       if(a[i-1][j]==1)
        v[i][j]=v[i][j]+1;
       if(a[i-1][j+1]==1)
        v[i][j]=v[i][j]+1;
       if(a[i][j+1]==1)
        v[i][j]=v[i][j]+1;
       if(a[i+1][j+1]==1)
        v[i][j]=v[i][j]+1;
       if(a[i+1][j]==1)
        v[i][j]=v[i][j]+1;
       if(a[i+1][j-1]==1)
        v[i][j]=v[i][j]+1;
       if(a[i][j-1]==1)
        v[i][j]=v[i][j]+1;
    }
    if(x=='T')
    {
     v[i][j]=0;
    if(b[i-1][j-1]==1)
        v[i][j]++;
    if(b[i-1][j]==1)
    v[i][j]++;
    if(b[i-1][j+1]==1)
    v[i][j]++;
    if(b[i][j-1]==1)
    v[i][j]++;
    if(b[i][j+1]==1)
    v[i][j]++;
    if(b[i+1][j-1]==1)
    v[i][j]++;
    if(b[i+1][j]==1)
    v[i][j]++;
    if(b[i+1][j+1]==1)
    v[i][j]++;
    }
}
void numarare(char x, char a[1000][1000], char v[1000][1000], int N, int M) //functia de nastere sau omorare a celulelor
{
    int i, j;
        for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
        {
        if(v[i][j]<2 || v[i][j]>3)
            a[i][j]=0;
        if(v[i][j]==3)
         a[i][j]=1;
        }
}
void bordura(char a[1000][1000], char b[100][100], int N, int M) //functia de adaugare a bordurii matricei toroidale
{
   int i,j;
    for(i=1; i<=N+1; i++)
        for(j=1; j<=M+1; j++)

        b[i][j]=a[i][j]; //decalarea matricei
    b[0][0]=a[N][M];
    b[N+1][M+1]=a[1][1];
    b[0][M+1]=a[N][1];
    b[N+1][0]=a[1][M];
    for(j=1;j<M+1;j++)
        b[0][j]=a[N][j];
    for(j=1;j<M+1;j++)
        b[N+1][j]=a[1][j];
    for(i=1;i<N+1;i++)
        b[i][0]=a[i][M];
    for(i=1;i<N+1;i++)
        b[i][M+1]=a[i][1];

}
void afisare(char x, char a[1000][1000], char v[1000][1000], int N, int M) //functia de afisare a matricei
{
    int i,j;
    if(x=='P')
    for(i=1; i<=N; i++)
    {
        for(j=1; j<=M; j++)
            printf("%d ", a[i][j]);
            printf("\n");
    }
    if(x=='T')
        for(i=1; i<=N; i++)
    {
        for(j=1; j<=M; j++)
            printf("%d ", a[i][j]);
            printf("\n");
    }
}
int main() //functia principala main
{
    char x, a[1000][1000], b[100][100], v[1000][1000];
    int N, M, k, i, j, y;
    float procent,max=0, p;
    printf("\n Acest program se numeste Jocul vietii si este implementat de John Conway's.\n\n");
    printf(" Reguli:\n\n");
    printf("     1. Orice celula cu mai putin de doua celule vecini moare de singuratate.\n");
    printf("     2. Orice celula cu mai mult de trei celule vecine moare din cauza supraaglomerarii.\n");
    printf("     3. Orice celula cu doua sau trei celule vecine supravietuieste.\n");
    printf("     4. O celula noua este creata daca are exact trei celule vecine.\n\n");
    printf(" Alegeti tipul jocului.\n\n Apasati P pentru reprezentare planara sau T pentru reprezentare toroidala\n\n");
    y=0;
    citire(&x, &N, &M, &k, &y, &a);
    if(y==1)
       {
        printf("\n Caracterul introdus nu este corect.\n\nIntroduceti P pentru reprezentare planara sau T pentru reprezentare toroidala\n");
    return 0;
   }
   if(x=='P')
   {
     printf("\n Matricea planara rezultata in urma a %d evolutii este:\n\n", k);
   while(k!=0)
   {
       p=0;
       for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
       {
           vecini(x, i, j, a, b, v);
           if(a[i][j]==1)
            p=p+1;
       }
       numarare(x, a, v, N, M);
       if(p>max)
        max=p;
   k=k-1;
   }
   }
   if(x=='T')
   {
       printf("\n Matricea toroidala rezultata in urma a %d evolutii este:\n\n", k);

       while(k!=0)
        {
       p=0;
       bordura(a, b, N, M);
       for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
        {
            vecini(x, i, j, a, b, v);
            if(a[i][j]==1)
         p=p+1;
        }
        numarare(x, a, v, N, M);
        if(p>max)
            max=p;
        k=k-1;
       }
   }
   afisare(x, a, v, N, M);
   procent=(max/(N*M))*100;
   printf("\n Gradul maxim de populare inregistrat pe parcursul simularii este:%.3f %%\n", procent);
   return 0;
}
