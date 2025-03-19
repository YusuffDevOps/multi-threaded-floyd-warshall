#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define INF 999999 //Infinity value

int **dist; //Declare distance 2D array globally
sem_t readLock; //Semaphore for reader
sem_t writeLock; //Semaphore for writers


//Struct for passing arguments to worker functions
struct arg_s{
	int n; //Number of nodes
	int i; //corresponding i value 
	int k;	//	corresponding k value 	
};

/**
*This is the worker function. 
It is responsible for updating the distance matrix 
based on the shortest paths computed using intermediate nodes
*/
void *worker(void *args){
	//get n,i,k from args
	int j;
	struct arg_s *a;
	a = args;
	//Get variables from args struct
	int n = a->n; //Get number of nodes 
	int k = a->k; //Get k value from main function
	int i = a->i; //Get i value from main function
	for (j = 0; j<n; j++)
	{
		//acquire read lock
		sem_wait(&readLock);
		if ((dist[i][k] + dist[k][j]) < dist[i][j]){
			//release read lock
			sem_post(&readLock);
			//acquire write lock
			sem_wait(&writeLock);
			dist[i][j] = dist[i][k] + dist[k][j];
			//release write lock
			sem_post(&writeLock);
		}else{
			//release read lock
			sem_post(&readLock);
		}
	}
	pthread_exit(NULL); //Running thread exits 
}
	


int main (){
	FILE *myFile; //File object 
	int i,j,k; //Loop counters
	myFile = fopen("graph.txt", "r"); //Get file input
	int m, n; // initialize number of nodes and edges in the graph
	fscanf(myFile, "%d", &n); //Read number of nodes in file
	fscanf(myFile, "%d", &m); //Read number of undirected edges in file
	sem_init(&readLock, 0, 1); //Initialize the read semaphore 
	sem_init(&writeLock, 0, 1);//Inititalize the write semaphore
	pthread_t *Threads;
	Threads = (pthread_t *)malloc(sizeof(pthread_t) * n); //Create n threads 
	
	//dynamic memory allocation for 2D array (dist array)
	dist = malloc(n * sizeof(int *));
	for(i=0; i<n; i++){
		dist[i] = malloc(n * sizeof(int *));
	}
	//Set diagonal elements to 0 and add INF on all other cells
	for( i=0; i<n; i++){
		for(j =0; j<n; j++){
			if(i==j){ 
				dist[i][j] = 0; //Set diagonal element to 0
			}else{
				dist[i][j] = INF; //Set non-diagonal element to an INFINTY value
			}
		}
	}
	
	//Get weight of undirected edges and update dist matrix 
	for(i=0; i<m; i++){
		int u, v, w;
		fscanf(myFile, "%d", &u); //Get node ui
		fscanf(myFile, "%d", &v);//Get node vi
		fscanf(myFile, "%d", &w); //Get weight of edge
		//Since edge is undirected update both sides of the adjacency matrix
		dist[u-1][v-1] = w;
		dist[v-1][u-1] = w;
	}
	
	//Run the Floyd-Warshall Algorithm on dist matrix
	for(k=0; k<n; k++){
		for(i=0; i<n; ++i){
			
			//Argument struct passed to the running thread
			struct arg_s arg = {
				n, i, k
			};
			struct args_s *args = &arg;
			pthread_create((Threads + i), NULL, worker, (void *)args); //Create a new thread
			pthread_join(*(Threads + i), NULL);	
		}
	}
	//Destroy the semaphores after complete execution
	sem_destroy(&writeLock);
	sem_destroy(&readLock);
	//Print new distance matrix 
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf(" %d " ,dist[i][j]);
		}
		printf("\n");
	}
	
	
	
	
	return 0;
}
