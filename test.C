#include<stdio.h>
#include<stdlib.h>
#include "graph_adt.h"


int main(){
	Graph *graphModel = create_adj_list_complete(5);
	print_graph(graphModel);

return 0;
}
