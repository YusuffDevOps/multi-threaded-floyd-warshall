#include <stdio.h>
#include <stdlib.h>

#define INF 999999 //Infinity value

int **dist; //Declare distance 2D array globally

int main (){
	FILE *myFile; //File object 
	int i,j,k; //Loop counters
	myFile = fopen("graph.txt", "r"); //Get file input
	int m, n;
	fscanf(myFile, "%d", &n); //Read number of nodes in file
	fscanf(myFile, "%d", &m); //Read number of undirected edges in file
	//dynamic memory allocation for 2D array (dist array)
	dist = malloc(n * sizeof(int *));
	for(i=0; i<n; i++){
		dist[i] = malloc(n * sizeof(int *));
	}
	//Set diagonal elements to 0 and add INF on all other cells
	for( i=0; i<n; i++){
		for(j =0; j<n; j++){
			if(i==j){
				dist[i][j] = 0; 
			}else{
				dist[i][j] = INF;
			}
		}
	}
	
	//Get weight of undirected edges and update dist matrix 
	for(i=0; i<m; i++){
		int u, v, w;
		fscanf(myFile, "%d", &u); //Get node ui
		fscanf(myFile, "%d", &v);//Get node vi
		fscanf(myFile, "%d", &w); //Get weight of edge
		//Since edge is undirected update both sides
		dist[u-1][v-1] = w;
		dist[v-1][u-1] = w;
	}
	
	//Run the Floyd-Warshall Algorithm on dist matrix
	for(k=0; k<n; k++){
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				if(dist[i][k]+dist[k][j]<dist[i][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	
	//Print new distance matrix  

	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf(" %d ", dist[i][j]);
		}
		printf("\n");
	}
	
	
	
	
	return 0;
}
