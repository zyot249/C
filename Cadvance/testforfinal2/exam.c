#include <stdio.h>
#include "./weightedGraph.h"
#include <stdlib.h>
#include <string.h>

void printMenu(){
	printf("\n--------------Your Option--------------\n");
	printf("1. Doc do thi\n");
	printf("2. In ra danh sach ke\n");
	printf("3. Thanh tri co nhieu duong di truc tiep nhat\n");
	printf("4. Duong di ngan nhat\n");
	printf("5. Exit\n");
	printf("Your choice: ");
}

void readData(char* fileName, Graph graph){
    FILE *fin = fopen(fileName,"r");
	if(fin == NULL){
		printf("Cannot Open File %s !\n",fileName);
		return -1;
	}
    char buff[100];
    fgets(buff, 100, fin);
    int n, m;
    sscanf(buff,"%d\t%d\n", &n, &m);
    printf("%d\t%d\n", n, m);
    for (int i = 0; i < m; i++)
    {
        int id1, id2, time;
        fgets(buff, 100, fin);
        sscanf(buff,"%d\t%d\t%d\n", &id1, &id2, &time);
        printf("%d\t%d\t%d\n", id1, id2, time);
        if(get_vertex(graph, id1) == NULL)
            add_vertex(graph, id1, "abs");
        if(get_vertex(graph, id2) == NULL)
            add_vertex(graph, id2, "abs");
        add_edge(graph, id1, id2, (double)time);    
    }
    
    

}

int main(){
    Graph graph = create_graph(0);
    int* output = (int*)malloc(100*sizeof(int));
    int opt;
    do
    {
        printMenu();
        scanf("%d", &opt);
        switch (opt){
        case 1:
        {
            readData("dothi.txt",graph);
            break;
        }
        case 2:
        {
            list_graph(graph, output);
            break;
        }
        case 3:
        {
            int max = 0;
            int id[100];
            int cnt = 0;
            JRB ptr;
            jrb_traverse(ptr, graph.edges){
                int tmp = indegree(graph, jval_i(ptr->key), output);
                if(tmp > max){
                    max = tmp;
                }
            }
            jrb_traverse(ptr, graph.edges){
                int tmp = indegree(graph, jval_i(ptr->key), output);
                if(tmp == max){
                    id[cnt++] = jval_i(ptr->key);
                }
            }
            printf("Thanh tri co nhieu duong di den nhat la :");    
            for(int i = 0; i < cnt; i++){
                printf("%d\t", id[i]);
            }
            printf("\n");
            break;
        }
        case 4:
        {
            int s, t;
            int* path = (int*)malloc(100*sizeof(int));
            int length;
            printf("Nhap thanh nguon: s = ");
            scanf("%d", &s);
            printf("Nhap thanh dich: t = ");
            scanf("%d", &t);
            double distance = 0;
            distance = shortest_path(graph, s, t, path, &length);
            if(distance != 0){
                printf("Khoang cach duong di ngan nhat la: %g\n", distance);
                printf("Duong di ngan nhat tu %d den %d la: ",s, t);
                for (int i = length-1; i >= 0; i--)
                {
                    printf("%d\t", path[i]);
                }
                printf("\n");
            }else
                printf("ROUTE NOT FOUND");
            
            break;
        }
        case 5:
        {
            printf("Chao ban nhe!\n");
            break;
        }
        default:
        printf("Hay chon tinh nang tu 1-5!");
        }
    } while (opt != 5);
    
    return 0;
}