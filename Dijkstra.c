#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int visited[MAX];
int m[MAX];
int n[MAX];
int min[MAX][MAX];
//int dis[MAX][MAX];
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
    printf("矩阵:\n");
    printf("start|end       ");
    for(i=0;i<G.n;i++)
       printf("%c       ",G.Vex[i]);
    printf("\n");
    for(i=0;i<G.n;i++){
        printf("  %c       \t",G.Vex[i]);
        for(j=0;j<G.n;j++)
        {
            if(G.Edge[i][j]==MAX) printf("MAX     ");
            else
            printf("%d\t",G.Edge[i][j]);
        }
        printf("\n");
    }
}

void Dijkstra(int x, int Distance[], int prev[])
{
    int s[G.n];
    int mm,d;
    int i, j, u;
    for(i=0; i<G.n; i++)
    {
        Distance[i] = G.Edge[x][i];
        s[i] = 0;
        if(Distance[i] == MAX)
            prev[i] = -1;
        else
            prev[i] = x;
    }
    Distance[x] = 0;
    s[x] = 1;
    for(i=1; i < G.n; i++)
    {
        mm = MAX;
        u = x;
        for (j=0; j < G.n; j++)
            if(s[j]==0 && Distance[j]<mm)
            {
                mm = Distance [j];
                u = j;
            }
        s[u] = 1;
        for(j=0; j<G.n; j++)
        if(s[j]==0 && G.Edge[u][j]<MAX)
        {
            d = Distance[u] +G.Edge[u][j];
            if(Distance[j] > d)
            {
                Distance[j] = d;
                prev[j] = u;
            }
        }
    }
}

void PrintPrev(int prev[],int vn,int x)
{
    int t = vn;
    int i, j;
    int m=0;
    int temp[G.n];
    for(i=0; i < G.n; i++)
        temp[i] = 0;
    temp[x] = 0;
    for(i =0, j=1; j < G.n ;j++)
    {
        if(prev[t]!=-1 && t!=x)
        {
            temp[i] = prev[t]+1;
            t = prev[t];
            i++;
        }
        else break;
    }
    for(i=G.n-1; i >= 0; i--)
    {
        if(temp[i] != 0)
        {
            printf("%c", G.Vex[temp[i]-1]);
            if(i)
                printf("-->");
            m=1;
        }
    }
    if(m==0)  printf("%c",G.Vex[x]);
    printf("-->%c", G.Vex[vn]);
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
    //printf("`````%d```",G.Edge[0][0]);
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
              // G.Edge[q][p]=c-48;
            }
            sum++;
        }while(c!=EOF);
        G.e=sum/3;
    }
    Show(G);
    int Distance[G.n];
    int prev[G.n];
    int x;
    for(x=0;x<G.n;x++)
    {
        for(i=0;i<G.n;i++)
        {
            min[x][i]=MAX;
        }
    }
    printf("1.输出源点及其到其他顶点的最短路径长度和最短路径\n");
    printf("input i:(eg:1)\n");
    scanf("%d",&x);
    printf("when start with %c:\n",G.Vex[x]);
    Dijkstra(x, Distance, prev);
    i=0;
    for(i=0; i < G.n; i++)
    {
        printf("%c-->%c:",G.Vex[x], G.Vex[i]);
        if(Distance[i]!=MAX)
        {
            printf("the distance is:%d", Distance[i]);
            printf("\n      the routine is:  ");
            PrintPrev(prev, i,x);
            printf("\n");
        }
        if(Distance[i]==MAX)
        {
            printf("Routine does not exist!", G.Vex[x], G.Vex[i]);
            printf("\n");
        }
    }
    printf("-----------------------------------------------------\n");
    printf("2.单目标最短路径问题:找出图中每个顶点v到某个指定顶点c最短路径\n");
    printf("input i:(eg:1)\n");
    scanf("%d",&j);
    printf("when end in %c:\n",G.Vex[j]);
    for(i=0; i < G.n; i++)
    {
        Dijkstra(i, Distance, prev);
        printf("%c-->%c ",G.Vex[i], G.Vex[j]);
        if(Distance[j]==MAX)
        {
            printf("Routine does not exist!");
            printf("\n");
        }
        if(Distance[j]!=MAX)
        {
            printf("the distance is:%d", Distance[j]);
            printf("\n      the routine is:");
            PrintPrev(prev, j,i);
            printf("\n");
        }
    }
    printf("-----------------------------------------------------\n");
    printf("3.单顶点对间最短路径问题：对于某对顶点u和v找出u到v和v到u的一条最短路径 \n");
    printf("input:(i,j)(eg:1,2):(注意要用英文输入法输入数字！)\n");
    int a,b;
    scanf("%d,%d",&x,&i);
    printf("when start with %c:\n",G.Vex[x]);
    Dijkstra(x, Distance, prev);
    printf("%c-->%c:",G.Vex[x], G.Vex[i]);
    if(Distance[i]!=MAX)
    {
        printf("the distance is:%d", Distance[i]);
        printf("\n      the routine is:  ");
        PrintPrev(prev, i,x);
        printf("\n");
    }
    if(Distance[i]==MAX)
    {
        printf("Routine does not exist!");
        printf("\n");
    }
    printf("-----------------------------------------------------\n");
    printf("when start with %c:\n",G.Vex[i]);
    Dijkstra(i, Distance, prev);
    printf("%c-->%c:",G.Vex[i], G.Vex[x]);
    if(Distance[x]!=MAX)
    {
        printf("the distance is:%d", Distance[x]);
        printf("\n      the routine is:  ");
        PrintPrev(prev, x,i);
        printf("\n");
    }
    if(Distance[x]==MAX)
    {
        printf("Routine does not exist!");
        printf("\n");
    }
    printf("-----------------------------------------------------\n");


    return 0;
}
