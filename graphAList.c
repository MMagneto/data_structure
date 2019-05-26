/*用邻接表表示图*/

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct AjdVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV; /*邻接点下标*/
	WeightType Weight; /*边权重*/
	PtrToAdjVNode Next;
}

typedef struct VNode {
	PtrToAdjVNode FirstEdge;
	DataType Data; /*存顶点的数据*/
}AdjList[MaxVertexNum];
/* AdjList是邻接表类型*/

typedef GNode *PtrToGnode;
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
}
	

LGraph CreateGraph(Vertex Nv) {
	LGraph Graph= (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = Nv;
	Graph->Ne = 0;

	/*初始化邻接表头指针*/
	Vertex v;
	for(v =0;v<Graph->Nv;i++) {
		Graph->G[v].FirstEdge = NULL;
	}
	
	return Graph;
}

void InsertEdge (LGraph Graph, Edge E) {
	PtrToAdjVNode newNode = (PtrToAdjVNode)malloc(sizeof(struct VNode));
	newNode->AdjV = E->V2;
	newNode->Weight = E->Weight;
	/*将V2插入V1的表头*/
	newNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = newNode;
	/*若是无向图，还需插入边 <V2, V1> */
	/*为V1建立新的邻接点*/
	newNode = (PtrToAdjVNode)malloc(sizeof(struct VNode));
	newNode->Adj = E->V1;
	newNode->Weight = E->Weight;
	newNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V1].FirstEdge = newNode;

}

LGraph buildGraph() {
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



