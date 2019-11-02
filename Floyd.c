#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int m[MAX];
int n[MAX];
typedef struct Graph
{
    char Vex[MAX];
    int Edge[MAX][MAX];
    int n,e;
}Graph;
Graph G;

void Show(Graph G)
{
    int i=0,j=0;
    printf("G has %d vertex,%d edges\n",G.n,G.e);
    printf("ÁÚ½Ó¾ØÕó:\n");
    printf("        ");
    for(i=0;i<G.n;i++)
       printf("%c       ",G.Vex[i]);
   printf("\n");
    for(i=0;i<G.n;i++){
        printf(" %c \t",G.Vex[i]);
        for(j=0;j<G.n;j++)
        {
             if(G.Edge[i][j]!=MAX)
                printf("%d\t",G.Edge[i][j]);
             else printf("MAX\t");
        }
        printf("\n");
    }
}

void Floyd(Graph G, int Distance[][G.n],int prev[][G.n])
{
    int num[G.n];

    int i, j;
    for (i = 0; i < G.n; i++)
    {
         for (j = 0; j < G.n; j++)
        Distance[i][j] = G.Edge[i][j];
    }

    for (i = 0; i < G.n; i++)
    {
        for (j = 0; j < G.n; j++)
        {
            if (G.Edge[i][j] == MAX)
                prev[i][j] = -1;
            else
                prev[i][j] = i;
        }
    }
    int d, v;
    for (v = 0; v < G.n; v++)
    {
        for (i = 0; i < G.n; i++)
        {
            for (j = 0; j < G.n; j++)
            {
                d = Distance[i][v] + Distance[v][j];
                if (d < Distance[i][j])
                {
                    Distance[i][j] = d;
                    prev[i][j] = v;
                }
            }
        }

    }
    printf("¾àÀë¾ØÕó\n");
    printf("        ");
    for(i=0;i<G.n;i++)
    {
        printf("%c\t",G.Vex[i]);
    }
    printf("\n");
    for (i = 0; i < G.n; i++)
    {
        printf("%c\t",G.Vex[i]);
        for (j = 0; j < G.n; j++)
        {
            if(Distance[i][j]==MAX)
                printf("MAX\t");
            else printf("%d\t",Distance[i][j]);
        }
        printf("\n");
    }
    printf("\n¿É´ï¾ØÕó\n");
    printf("        ");
    for(i=0;i<G.n;i++)
    {
        printf("%c\t",G.Vex[i]);
    }
    printf("\n");
    for (i = 0; i < G.n; i++)
    {
        printf("%c\t",G.Vex[i]);
        for (j = 0; j < G.n; j++)
        {
            if(prev[i][j]!=-1)
                printf("1\t");
            else printf("0\t");
        }
       printf("\n");
    }
    printf("\n");
}

typedef struct
{
    int top;
    int ddd[MAX];
}Stack;

void InitStack(Stack *S)
{
    memset(S,0,sizeof(Stack));
    S->top=-1;
}

int Pop(Stack *S)
{
    int top;
    if(S->top==-1)
        return -2;
    else
    {
        top=S->ddd[S->top];
        S->top--;
     //   printf("...%c...",top);
        return top;
    }
}

void Push(Stack *S,int ch)
{
    S->top++;
    S->ddd[S->top]=ch;
}

int Top(Stack *S)
{
    int top;
    if(S->top==-1)
        return -2;
    else
    {
        top=S->ddd[S->top];
       // S->top--;
     //   printf("...%c...",top);
        return top;
    }
}

int main()
{
    FILE *fp1,*fp2;
    int i=0,j=0;
    int p=0,q=0;
    char c;
    fp1=fopen("ABC.txt","r");
    if(fp1==NULL)
    {
        printf("Reading failed!\n");
        exit(0);
    }
    else
    {
        printf("the names are:");
        do
        {
            c=fgetc(fp1);
            if(c==EOF)
                break;

               G.Vex[i]=c;

                printf("%c",c);
                i++;
        }while(c!=EOF);
        G.n=i;
        printf("\n");
    }
    for(i=0;i<G.n;i++)
    {
        for(j=0;j<G.n;j++)
        {
            G.Edge[i][j]=MAX;
        }

    }
    for(i=0;i<G.n;i++)
    {
        G.Edge[i][i]=0;
    }
    int sum=0;
    fp2=fopen("(i,j).txt","r");
    if(fp2==NULL)
    {
        printf("Reading failed!\n");
        exit(0);
    }
    else
    {
        do
        {
            c=fgetc(fp2);
            if(c==EOF)
                break;
            if(sum%3==0)
                m[sum/3]=c-48;
            else if(sum%3==1)
                n[(sum-1)/3]=c-48;
            else
            {
                p=m[(sum-2)/3];
                q=n[(sum-1)/3];
               G.Edge[p][q]=c-48;
               G.Edge[q][p]=c-48;
            }
            sum++;
        }while(c!=EOF);
        G.e=sum/3;
    }
    Show(G);
     int Distance[G.n][G.n];
     int prev[G.n][G.n];
    Floyd(G,Distance,prev);
    printf("search what(i,j)?(eg:1,2)\n");
    scanf("%d,%d",&i,&j);
    printf("   %c->%c:",G.Vex[i],G.Vex[j]);
    int e=1,v,k=1;
    Stack s;
    InitStack(&s);
    if (Distance[i][j] == 0)
        printf("        routine is:%c->%c",G.Vex[i],G.Vex[j]);
    else if (Distance[i][j] == MAX)
        printf("routine does not exist!");
    else
    {
        Push(&s,j);
        v = j;
        do{
            v = prev[i][v];
            Push(&s,v);
        } while (v != i);
        printf(" min distance:%d\n",Distance[i][j]);
        printf("        routine is:  ");
        while (k!=-2)
        {
            e= Top(&s);
            printf("%c  ",G.Vex[e]);
            k=Pop(&s);
        }
    }
    return 0;
}
