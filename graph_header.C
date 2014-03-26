#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "graph_adt.h" 

int weightGet(Vertex_root *from, Vertex_root *to){
	if(from == to){
		return 0;
	}else{
		Edge *tempE = from->edges;
		while(tempE != NULL){
			if(tempE->vertx == to){
				return tempE->weight;
			}
			tempE = tempE->next;
		}
	}
	return 9999;
}

Vertex_root *search_vertex(Graph *graphModel, int needle){
	for(int i=0;i<graphModel->vertex_number;i++){
		if(graphModel->vertices[i]->name == needle){
			return graphModel->vertices[i];
		}
	}
	return NULL;
}
int is_Visited(Vertex_root **visited, Vertex_root *needle){
	int i=0;
	while(visited[i] != NULL){
		if(visited[i] == needle){
			return 1;
		}
		i++;
	}
	return 0;
}
void enqueue(Vertex_root **queue, int v, Vertex_root *value){
	int i=0;
	for(i=0;i<v;i++){
		if(queue[i] == NULL){
			break;
		}
	}
	if(i==v){
		printf("Cannot Enqueuw, Queue Full");
		return;
	}
	queue[i] = value;

}
Vertex_root *dequeue(Vertex_root **queue, int v){
	Vertex_root *returnVal;
	if(queue[0] == NULL){
		printf("Queue Empty");
		return NULL;
	}else{
		returnVal = queue[0];
		for(int i=0;i<v;i++){
			if(queue[i] != NULL){
				queue[i] = queue[i+1];
			}
		}
		return returnVal;
	}

}
void extract_from_comma(char *str, int *result, int is_weight, int v){
int isCorrect =0,temp=0,j=0,is_neg=0;
	while(!isCorrect){
		for(int i=0;i<strlen(str);i++){
			if(str[i]!= ' '){
				if(str[i] == ','&& temp){
					if((temp <=v && temp >0) || is_weight){
						result[j++] = temp-1+is_weight;
						is_neg = 0;
					}else{	
						printf("Invalid Edge, Start from the top");
						break;
					}
					temp=0;
				}else{
					//determine if negetive
					if(str[i] == '-'){
						is_neg=1;
					}else{
						if(!is_neg){
							temp = temp*10+str[i]-'0';
						}else{
							printf("WTF %d %d %d",temp,str[i],str[i]-'0');
							temp = temp*10-str[i]+'0';
							printf("%d \n", temp);
						}
												
					}
				}
			}
		}
			
		
		if(temp){
			result[j++] = temp-1+is_weight;
			is_neg = 0;
		}
		/*for(int i=0;i<edges;i++){
			printf("%d ", result[i]);
		}*/
		isCorrect = 1;
	}
	return;

}
int *get_edge_list_w_a(int k,int *out_counter, int v){
	int d,j=0,edges=0,i=0,flag=0;
	int *result;
	char *str=(char *)malloc(1024*sizeof(char));
	printf("Enter the Edges from vertex %d separated by comma(n for no edges):",(k+1));
	scanf("%s", str);
//	puts(str);
	///////////////////////////////////////
	if(str[0] != 'n'){
	for(i=0;i<strlen(str);i++){
		if((str[i] ==',' || str[i] == ':') && !flag){
			flag=0;
		}
		else if(str[i] !=',' && !flag){
			flag=1;
		}
		if(str[i] == ',' && flag){
			edges++;
		}
	}
	edges++;
	printf("Edges %d\n", edges);
	//////////////////////////////////
	result = (int *)malloc((edges*2)*sizeof(int));
	*out_counter = edges;
	extract_from_comma(str, result,0,v);
	printf("Enter the Weights of the Edges from vertex %d separated by comma:",(k+1));
	scanf("%s", str);
	extract_from_comma(str, &result[edges],1,v);
	//printf("I am returning\n");
	}else{
		result = (int *)malloc(sizeof(int));
		out_counter = 0;
	}
	free(str);
	return result;
}

int *get_edge_list_w(int k,int *out_counter, int v){
	int d,temp=0,j=0,edges=0,isCorrect=0,i=0,tempW=0;
	int *result;
	char *str=(char *)malloc(1024*sizeof(char));
	printf("Enter the Edges from vertex %d with weight in this format vertex:wight separated by comma:",(k+1));
	scanf("%s", str);
//	puts(str);
	///////////////////////////////////////
	int flag=0;
	for(i=0;i<strlen(str);i++){
		if((str[i] ==',' || str[i] == ':') && !flag){
			flag=0;
		}
		else if(str[i] !=',' && !flag){
			flag=1;
		}
		if(str[i] == ',' && flag){
			edges++;
		}
	}
	edges++;
	printf("Edges %d\n", edges);
	//////////////////////////////////
	result = (int *)malloc((edges*2)*sizeof(int));
	*out_counter = edges;
	int is_colon_started = 0,is_neg=0;

	while(!isCorrect){
		for(i=0;i<strlen(str);i++){
			if(str[i]!= ' '){
				if(str[i] == ','&& temp){//left side was an key value pair
					if(temp <=v && temp >0){
						//printf("--%d--", j);
						result[j++] = temp-1;
						if(is_neg)
							result[j+edges-1] = -1*tempW; 
						else
							result[j+edges-1] = tempW;
						is_colon_started =0;
						is_neg = 0;
					}else{	
						printf("Invalid Edge, Start from the top");
						break;
					}
					temp=0;
					tempW=0;
				}else{
					if(str[i] != ':'){
						if(str[i] != '-'){
							if(!is_colon_started){
								temp = temp*10+str[i]-'0';						
							}else{
								tempW = tempW*10+str[i] - '0';
							}
						}else if(str[i] == '-' && is_colon_started){
							is_neg = 1;
						}
					}else if(str[i] == ':' && !is_colon_started){
						is_colon_started = 1;
					}
				}
			}
		}
			
		
		if(temp){
			result[j++] = temp-1;
			if(is_neg)
				result[j+edges-1] = -1*tempW;
			else
				result[j+edges-1] = tempW;
		}
		/*for(int i=0;i<edges;i++){
			printf("%d ", result[i]);
		}*/
		isCorrect = 1;
	}
	//printf("I am returning\n");
	return result;
}

int *get_edge_list(int k,int *out_counter, int v){
	int d,temp=0,j=0,edges=0,isCorrect=0,i=0;
	int *result;
	char *str=(char *)malloc(80*sizeof(char));
	printf("Enter the Edges from vertex %d separated by comma:",(k+1));
	scanf("%s", str);
//	puts(str);
	///////////////////////////////////////
	int flag=0;
	for(i=0;i<strlen(str);i++){
		if(str[i] ==','&& !flag){
			flag=0;
		}else if(str[i] !=',' && !flag){
			flag=1;
		}
		if(str[i] == ',' && flag){
			edges++;
		}
	}
	edges++;
	printf("Edges %d\n", edges);
	//////////////////////////////////
	result = (int *)malloc(edges*sizeof(int));
	*out_counter = edges;
	while(!isCorrect){
		for(i=0;i<strlen(str);i++){
			if(str[i]!= ' '){
				if(str[i] == ','&& temp){
					if(temp <=v && temp >0){
						result[j++] = temp-1;
					}else{	
						printf("Invalid Edge, Start from the top");
						break;
					}
					temp=0;
				}else{
					temp = temp*10+str[i]-'0';
				}
			}
		}
			
		
		if(temp){
			result[j++] = temp-1;
		}
		/*for(int i=0;i<edges;i++){
			printf("%d ", result[i]);
		}*/
		isCorrect = 1;
	}
	//printf("I am returning\n");
	return result;
}
void get_weight_from_file(char *str, int **weightList, int v){
	FILE *fp;int retry=0;
	while(retry<10){
		fp = fopen(str, "a+");
		if(fp == NULL){
			fprintf(stderr, "cannot access the file check CHMOD.. retrying");
			retry++;
		}else{
			break;
		}
	}
	if(retry >= 10) exit(1);
	char ch;
	int temp=0,i=0,j=0,is_neg=0;
	while((ch=fgetc(fp))!=EOF){
//	printf("am i here?%c %d %d\n",ch,i,j);fflush(stdout);
		if(isspace(ch)){
			//store
			if(is_neg){
				temp = temp * -1;
			}
			weightList[i][j] = temp;
			temp=0;is_neg=0;
			j++;
		}else if(ch=='-'){
			//-ve
			is_neg = 1;
		}else if(isdigit(ch)){
			temp= temp*10 + ch-'0'; 
		}else{
			continue;
		}
		if(j>=v){
			i++;
			j %=v;
		}
		if(i>=v){
			break;
		}
	}

}
Graph *create_adj_list_complete(int v){
	
	Graph *graphModel = (Graph *)malloc(sizeof(Graph));
	graphModel->vertices = (Vertex_root **)malloc(v*sizeof(Vertex_root *));
	graphModel->vertex_number = v;
	Edge *tempEdge;
	int **Weights= (int **)malloc(v*sizeof(int *));

	for(int i=0;i<v;i++){
		Weights[i] = (int *)malloc(sizeof(int)*v);
	}
	//vertices Initialization
	for(int i=0;i<v;i++){
		graphModel->vertices[i] = (Vertex_root *)malloc(sizeof(Vertex_root));
		graphModel->vertices[i]->visited = 0;
		graphModel->vertices[i]->name = i;
		graphModel->vertices[i]->edges = NULL;
		graphModel->vertices[i]->shortest_path_estimate = 9999;
		graphModel->vertices[i]->predecessor = NULL;
		graphModel->vertices[i]->is_activated = 1;
	}
	
	for(int i=0;i<v;i++){
		//now for the edges
		get_weight_from_file("weights.txt", Weights, v);
		//get weight from file
		Edge *txEdge = NULL;
		//----------------
//printf("am i here?\n");fflush(stdout);
		for(int j=0;j<v;j++){
			if(i==j) continue;

			tempEdge = (Edge *)malloc(sizeof(Edge));
			tempEdge->vertx = graphModel->vertices[j];
			tempEdge->weight = Weights[i][j];
			tempEdge->next = NULL;

			//trav to last position;
			Edge *tEdge = graphModel->vertices[i]->edges;
			if(graphModel->vertices[i]->edges == NULL){
				graphModel->vertices[i]->edges = tempEdge;
				txEdge = graphModel->vertices[i]->edges;
			}else{
				txEdge->next = tempEdge;
				txEdge = txEdge->next;
			}
		}
	}

return graphModel;
}

Graph *create_adj_list(int v){
	int i,j,wegh;
	Graph *graphModel=(Graph *)malloc(sizeof(Graph));//the whole graph like a wrapper
	//Vertex *vert;//the number of vertices
	Edge *tempEdge;
	//Vertex_root *vertices;//the vertex lists
	//vert = (Vertex *)malloc(v*sizeof(Vertex));//NOT GONNA NEED IT!
	graphModel->vertices = (Vertex_root **)malloc(v*sizeof(Vertex_root));
	graphModel->vertex_number = v;
	//*init and make vertex objects
	for(i=0;i<v;i++){
		graphModel->vertices[i] = (Vertex_root *)malloc(sizeof(Vertex_root));
		graphModel->vertices[i]->name = i;
		graphModel->vertices[i]->predecessor = NULL;
		graphModel->vertices[i]->shortest_path_estimate =9999; 
		graphModel->vertices[i]->edges = NULL;
		graphModel->vertices[i]->visited = 0;
	}
	//--done*/
	printf("\nIs the Graph Weighted?(0/1)");
	scanf("%d", &wegh);

	for(i =0;i<v;i++){
		int edgeCounter=0,k;
		int *edges_exist;
		if(wegh){
			edges_exist = get_edge_list_w_a(i, &edgeCounter, v);
		}else{
			edges_exist = get_edge_list(i, &edgeCounter, v);
		}
//		for(int l=0;l<edgeCounter;l++){
//			printf("%d ", edges_exist[l]);
//		}
//		printf("%d edges\n", edgeCounter);
		for(j=0;j<edgeCounter;j++){
			k = edges_exist[j];
			//printf("is it here?");
			if(graphModel->vertices[i]->edges == NULL){//first edge
				//printf("--%d,%d---\n", j,k);	
					tempEdge = (Edge *)malloc(sizeof(Edge));
					tempEdge->vertx = (graphModel->vertices[k]);
					tempEdge->next = NULL;
					tempEdge->weight = (wegh?(edges_exist[j+edgeCounter]):1) ;
					graphModel->vertices[i]->edges = tempEdge;
				}else{
					
					//not the first edge;	
					//printf("--%d, %d, %d--\n", j,k,i);
					Edge *localTemp=graphModel->vertices[i]->edges;
					while(localTemp->next != NULL){
						localTemp = localTemp->next;
					
					}
					//printf("--%d, %d, %d--\n", j,k,i);
					tempEdge = (Edge *)malloc(sizeof(Edge));
					tempEdge->vertx =(graphModel->vertices[k]);
					tempEdge->next = NULL;
					tempEdge->weight = (wegh?(edges_exist[j+edgeCounter]):1);
					localTemp->next = tempEdge;
				}
		}
		free(edges_exist);
		/*///////////////////
		for(j=0;j<v;j++){
			if(j!=i){
				printf("Is there an Edge from %d to %d?(y/n):", (i+1), (j+1));
				fflush(stdout);
				scanf("%c\n", &ch);
				getchar();
				get_edge_list(j, 0);
				//DEBUG DEBUG DEBUG
				
				if(ch == 'Y' || ch == 'y'){
					if(graphModel->vertices[i]->edges == NULL){//first edge
					printf("--%d---\n", j);	
						tempEdge = (Edge *)malloc(sizeof(Edge));
						tempEdge->vertx = (graphModel->vertices[j]);
						tempEdge->next = NULL;
						tempEdge->weight = 1;
						graphModel->vertices[i]->edges = tempEdge;
					}else{
						
						//not the first edge;						
						Edge *localTemp=graphModel->vertices[i]->edges;
						while(localTemp->next != NULL){
							localTemp = localTemp->next;
						
						}
						tempEdge = (Edge *)malloc(sizeof(Edge));
						tempEdge->vertx =(graphModel->vertices[j]);
						tempEdge->next = NULL;
						tempEdge->weight = 1;
						localTemp->next = tempEdge;

					}
				}
			}
		}*/
	}

	return graphModel;
}

void print_graph(Graph *graphModel){
	int i;
	printf("%d", graphModel->vertex_number);
	for(i=0;i<(graphModel->vertex_number);i++){
		printf("\n%d", graphModel->vertices[i]->name+1);
		printf("-->");
		Edge *tempE = graphModel->vertices[i]->edges;
		if(tempE != NULL){
			while(tempE != NULL){
				printf("| %d(%d) | ",tempE->vertx->name+1, tempE->weight);
				tempE = tempE->next;
			}
			printf("\n");
		}else{
			printf("None\n");
		}


	}	
}
