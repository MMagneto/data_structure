/*用邻接表表示图*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Vertex;
typedef int WeightType;
typedef char DataType;
int MaxVertexNum = 100;

/* AdjList是邻接表类型*/
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	Vertex AdjV; /*邻接点下标*/
	WeightType Weight; /*边权重*/
	PtrToAdjVNode Next;
};


typedef struct VNode *PtrToVNode;
struct VNode {
	PtrToAdjVNode FirstEdge;
	DataType Data; /*存顶点的数据*/
};
typedef PtrToVNode AdjList;//[MaxVertexNum];


typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv; /*顶点数*/
	int Ne; /*边数*/
	AdjList G; /*邻接表*/
};
typedef PtrToGNode LGraph;

typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2; /*存储边连接的两个结点*/
	WeightType Weight; /*存储权重*/
};
typedef PtrToENode Edge;


LGraph CreateGraph(Vertex Nv);
void InsertEdge(LGraph Graph, Edge E);
LGraph BuildGraph();


LGraph CreateGraph(Vertex Nv) {
	LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = Nv;
	Graph->Ne = 0;
	printf("Nv=%d Ne=%d\n", Graph->Nv, Graph->Ne);

	/*初始化邻接表头指针*/
	Graph->G = (AdjList)malloc(Nv*sizeof(struct AdjVNode));
	Vertex v;
	for(v =0;v<(Graph->Nv);v++) {
		(Graph->G)[v].FirstEdge = NULL;
	}
	
	return Graph;
}

void InsertEdge (LGraph Graph, Edge E) {
	PtrToAdjVNode newNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	newNode->AdjV = E->V2;
	newNode->Weight = E->Weight;
	/*将V2插入V1的表头*/
	newNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = newNode;
	/*若是无向图，还需插入边 <V2, V1> */
	/*为V1建立新的邻接点*/
	newNode = (PtrToAdjVNode)malloc(sizeof(struct VNode));
	newNode->AdjV = E->V1;
	newNode->Weight = E->Weight;
	newNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V1].FirstEdge = newNode;

}

LGraph BuildGraph() {
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	scanf("%d", &Nv); /*读入顶点个数*/
	Graph = CreateGraph(Nv); /*初始化一个有Nv个顶点，但没有边的图*/

	scanf("%d", &(Graph->Ne)); /*读入边数*/
	if( (Graph->Ne) != 0) {
		E = (Edge)malloc(sizeof(struct ENode));
		/*读入边, 格式为“起点 终点 权重”, 插入邻接矩阵*/
		for(i=0;i<(Graph->Ne); i++ ) {
			scanf("%d %d %d", &(E->V1), &(E->V2), &(E->Weight));
			/*注意， 如果权重不是整数，Weight的读入格式要改*/
			InsertEdge(Graph, E);
		}
	}
	/*如果顶点有数据的话，读入数据*/
	for(V = 0; V < (Graph->Nv); V++ ) {
		scanf("%c", &(Graph->G[V].Data));
	}

	return Graph;

}


int main(int argc, const char *argv[])
{
	int n, e;
	int i;
	scanf("%d", &n);
	LGraph Graph = CreateGraph(n);
	scanf("%d", &e);
	PtrToENode edgenode = (PtrToENode)malloc(sizeof(struct ENode)); 
	for(i=0;i<e;i++) { 
		scanf("%d %d", &(edgenode->V1), &(edgenode->V2) );
		InsertEdge(Graph, edgenode);
	}

	return 0;
}

/******************************************************/
    /* 邻接矩阵存储的图 - BFS */
     
    /* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
    /* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
    /* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */
    bool IsEdge( MGraph Graph, Vertex V, Vertex W )
    {
        return Graph->G[V][W]<INFINITY ? true : false;
    }
     
    /* Visited[]为全局变量，已经初始化为false */
    void BFS ( MGraph Graph, Vertex S, void (*Visit)(Vertex) )
    {   /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
        Queue Q;     
        Vertex V, W;
     
        Q = CreateQueue( MaxSize ); /* 创建空队列, MaxSize为外部定义的常数 */
        /* 访问顶点S：此处可根据具体访问需要改写 */
        Visit( S );
        Visited[S] = true; /* 标记S已访问 */
        AddQ(Q, S); /* S入队列 */
         
        while ( !IsEmpty(Q) ) {
            V = DeleteQ(Q);  /* 弹出V */
            for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
                /* 若W是V的邻接点并且未访问过 */
                if ( !Visited[W] && IsEdge(Graph, V, W) ) {
                    /* 访问顶点W */
                    Visit( W );
                    Visited[W] = true; /* 标记W已访问 */
                    AddQ(Q, W); /* W入队列 */
                }
        } /* while结束*/
    }

/*****************************************************/

    /* 邻接表存储的图 - DFS */
     
    void Visit( Vertex V )
    {
        printf("正在访问顶点%d\n", V);
    }
     
    /* Visited[]为全局变量，已经初始化为false */
    void DFS( LGraph Graph, Vertex V, void (*Visit)(Vertex) )
    {   /* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
        PtrToAdjVNode W;
         
        Visit( V ); /* 访问第V个顶点 */
        Visited[V] = true; /* 标记V已访问 */
     
        for( W=Graph->G[V].FirstEdge; W; W=W->Next ) /* 对V的每个邻接点W->AdjV */
            if ( !Visited[W->AdjV] )    /* 若W->AdjV未被访问 */
                DFS( Graph, W->AdjV, Visit );    /* 则递归访问之 */
    }



