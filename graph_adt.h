#ifndef GRAPH_IMPLEMENTATION
#define GRAPH_IMPLEMENTATiON
typedef struct GraphStruct{
	int vertex_number;
	struct VertexRootStruct **vertices;
} Graph;
typedef struct VertexRootStruct{
	int visited; // is visited(yet to implement)
	int name;//the label
	struct EdgeStruct *edges;//the freaking edges
	int shortest_path_estimate;//in shortest path algos
	struct VertexRootStruct *predecessor;//in shortest path alogos
	int is_activated;
} Vertex_root;
typedef struct EdgeStruct{
	struct VertexRootStruct *vertx;
	int weight;
	struct EdgeStruct *next;

} Edge;

Graph *create_adj_list(int v);
void get_weight_from_file(char *, int **, int);
Graph *create_adj_list_complete(int v);
void print_graph(Graph *graphModel);
int *get_edge_list(int k, int *out_counter,int v);
int *get_edge_list_w(int k, int *out_counter,int v);
void enqueue(Vertex_root **queue, int v, Vertex_root *value);
Vertex_root *dequeue(Vertex_root **queue, int v);
Vertex_root *search_vertex(Graph *graphModel, int needle);
int is_Visited(Vertex_root **visited, Vertex_root *needle);
int weightGet(Vertex_root *from, Vertex_root *to);
int *get_edge_list_w_a(int k, int *out_counter, int v);
void extract_from_comma(char *str, int *result, int is_weight);
#endif
