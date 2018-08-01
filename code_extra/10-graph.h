/*****************************Adjacency Table邻接表法*****************************************************************/
#include <iostream>
#include <cstdio>
using namespace std;

#define maxn 100  //最大顶点个数
int n, m;       //顶点数，边数

struct arcnode  //边结点
{
    int vertex;     //与表头结点相邻的顶点编号
    int weight = 0;     //连接两顶点的边的权值
    arcnode * next; //指向下一相邻接点
    arcnode() {}
    arcnode(int v,int w):vertex(v),weight(w),next(NULL) {}
    arcnode(int v):vertex(v),next(NULL) {}
};

struct vernode      //顶点结点，为每一条邻接表的表头结点
{
    int vex;    //当前定点编号
    arcnode * firarc;   //与该顶点相连的第一个顶点组成的边
}Ver[maxn];

void Init()  //建立图的邻接表需要先初始化，建立顶点结点
{
    for(int i = 1; i <= n; i++)
    {
        Ver[i].vex = i;
        Ver[i].firarc = NULL;
    }
}

void Insert(int a, int b, int w)  //尾插法，插入以a为起点，b为终点，权为w的边，效率不如头插，但是可以去重边
{
    arcnode * q = new arcnode(b, w);
    if(Ver[a].firarc == NULL)
        Ver[a].firarc = q;
    else
    {
        arcnode * p = Ver[a].firarc;
        if(p->vertex == b)  //如果不要去重边，去掉这一段
        {
            if(p->weight < w)
                p->weight = w;
            return ;
        }
        while(p->next != NULL)
        {
            if(p->next->vertex == b)    //如果不要去重边，去掉这一段
            {
                if(p->next->weight < w);
                    p->next->weight = w;
                return ;
            }
            p = p->next;
        }
        p->next = q;
    }
}
void Insert2(int a, int b, int w)   //头插法，效率更高，但不能去重边
{
    arcnode * q = new arcnode(b, w);
    if(Ver[a].firarc == NULL)
        Ver[a].firarc = q;
    else
    {
        arcnode * p = Ver[a].firarc;
        q->next = p;
        Ver[a].firarc = q;
    }
}

void Insert(int a, int b)   //尾插法，插入以a为起点，b为终点，无权的边，效率不如头插，但是可以去重边
{
    arcnode * q = new arcnode(b);
    if(Ver[a].firarc == NULL)
        Ver[a].firarc = q;
    else
    {
        arcnode * p = Ver[a].firarc;
        if(p->vertex == b) return;      //去重边，如果不要去重边，去掉这一句
        while(p->next != NULL)
        {
            if(p->next->vertex == b)    //去重边，如果不要去重边，去掉这一句
                return;
            p = p->next;
        }
        p->next = q;
    }
}
void Insert2(int a, int b)   //头插法，效率跟高，但不能去重边
{
    arcnode * q = new arcnode(b);
    if(Ver[a].firarc == NULL)
        Ver[a].firarc = q;
    else
    {
        arcnode * p = Ver[a].firarc;
        q->next = p;
        Ver[a].firarc = q;
    }
}
void Delete(int a, int b)   //删除以a为起点，b为终点的边
{
    arcnode * p = Ver[a].firarc;
    if(p->vertex == b)
    {
        Ver[a].firarc = p->next;
        delete p;
        return ;
    }
    while(p->next != NULL)
        if(p->next->vertex == b)
        {
            p->next = p->next->next;
            delete p->next;
            return ;
        }
}

void Show()     //打印图的邻接表（有权值）
{
    for(int i = 1; i <= n; i++)
    {
        cout << Ver[i].vex;
        arcnode * p = Ver[i].firarc;
        while(p != NULL)
        {
            cout << "->(" << p->vertex << "," << p->weight << ")";
            p = p->next;
        }
        cout << "->NULL" << endl;
    }
}

void Show2()     //打印图的邻接表(无权值）
{
    for(int i = 1; i <= n; i++)
    {
        cout << Ver[i].vex;
        arcnode * p = Ver[i].firarc;
        while(p != NULL)
        {
            cout << "->" << p->vertex;
            p = p->next;
        }
        cout << "->NULL" << endl;
    }
}
int main()
{
    int a, b, w;
    cout << "Enter n and m：";
    cin >> n >> m;
    Init();
    while(m--)
    {
        cin >> a >> b >> w;       //输入起点、终点
        Insert(a, b, w);        //插入操作
        Insert(b, a, w);        //如果是无向图还需要反向插入
    }
    Show();
    return 0;
}

/***************************Adjacency Matrix临界矩阵法***************************************/
#include <iostream>
#include <cstdio>
using namespace std;

#define maxn 100
#define INF 1xffffff    //预定于的最大值
int n, m;   //顶点数、边数
int g[maxn][maxn];      //邻接矩阵表示

void Init()
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        g[i][j] = 0;    //讲所有顶点度数置零，若为带权图，则置为INF
}
void Show() //打印邻接矩阵
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            cout << g[i][j] << " ";
        cout << endl;
    }
}
int main()
{
    int a, b;
    cout << "Enter n and m:";
    cin >> n >> m;
    while(m--)
    {
        cin >> a >> b;  //输入为边的始点、终点，若有权，还需输入权w
        g[a][b] = 1;    //a、b间存在边，将g[a][b]置1，若有权，则将其置为权值
        g[b][a] = 1;    //对于无向图，还要插入边(b，a）
    }
    Show();
    return 0;
}
/****************************广度优先遍历（邻接表实现）*******************************************/
#define INF 9999
bool visited[maxn];         //标记顶点是否被考察，初始置为false
int d[maxn], parent[maxn];  //d[]记录最短路径长度，parent[]记录某结点的父亲结点，生成树
void bfs(int s)             //广度优先搜索，邻接表输入（详见“一、图的表示”）
{
    for(int i = 1; i <= n; i++) //初始化
    {
        d[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }
    visited[s] = true;
    d[s] = 0;
    queue<int> q;        //用STL队列实现 ，#include <queue>
    q.push(s);           //压入队列
    while(!q.empty())
    {
        int u = q.front();          //取队头元素
        arcnode * p = Ver[u].firarc;
        while(p != NULL)        //遍历相邻顶点
        {
            if(!visited[p->vertex])
            {
                q.push(p->vertex);  //压入队列
                parent[p->vertex] = u;  //指向父亲
                d[p->vertex] = d[u]+1;  //路径长+1
                visited[p->vertex] = true;   //置为已被考察
            }
            p = p->next;
        }
        q.pop();        //出队列
    }
}
void PrintPath(int s, int v)    //打印从s到v的最短路径，需先调用bfs(s)
{
    if(v == s)
        cout << s << endl;
    else if(parent[v] == -1)
        return;
    else
    {
        PrintPath(s,parent[v]);
        cout << v << endl;
    }
}

/********************************************************深度优先遍历(邻接表实现)********************************************/
#define INF 9999
bool visited[maxn];     //标记顶点是否被考察，初始值为false
int parent[maxn];       //parent[]记录某结点的父亲结点，生成树，初始化为-1
int d[maxn], time, f[maxn]; //时间time初始化为0，d[]记录第一次被发现时，f[]记录结束检查时
void dfs(int s)         //深度优先搜索（邻接表实现），记录时间戳，寻找最短路径
{
    cout << s << " ";
    visited[s] = true;
    time++;
    d[s] = time;
    arcnode * p = Ver[s].firarc;
    while(p != NULL)
    {
        if(!visited[p->vertex])
        {
            parent[p->vertex] = s;
            dfs(p->vertex);
        }
        p = p->next;
    }
    time++;
    f[s] = time;
}
void dfs_travel()       //遍历所有顶点，找出所有深度优先生成树，组成森林
{
    for(int i = 1; i <= n; i++)     //初始化
    {
        parent[i] = -1;
        visited[i] = false;
    }
    time = 0;
    for(int i = 1; i <= n; i++)     //遍历
        if(!visited[i])
            dfs(i);
    cout << endl;
}
