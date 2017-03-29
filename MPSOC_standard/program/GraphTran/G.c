#include <stdio.h>
#define EM  -1 //External memory
#define GRAPH_START_EM 25000000
#define EM_SIZE 100000000
#define CORESNUM 64 
#define CORES_SYN_EM_START EM_SIZE-1-2*CORESNUM
#define VISITED_EM 90000000
//#include "barrier.h"
int main()
{

    int threadid = MTA_getthreadID();
    int **graph = NULL;
    int *vertex = NULL, *vertex_line = NULL, *thread_vertex = NULL;
    /* signal[10] is just a data package;
     * 'row' will equal to the number of vertexes of the partition.
     * 'column' equals to the column of the graph matrix, and also is the number of vertexes in this graph;
    */
    int i, j, k, sign, signal[10], column = 0, row = 0, be_read = 1, cores_syn = 0, cores[CORESNUM];

    //cores[] initialize
    for (i = 0; i < CORESNUM; i ++){cores[i] = 0;}

    //a data package,
    for (i = 0; i < 10; i++){signal[i] = i;}

  //first get the partition info
    printf("threadid is %d!\n", threadid);
    fflush(stdout);
  //read graph info file, first line is the number of vertexes
 MTA_read_EM_directly(&column, 1, 0 + GRAPH_START_EM);
 // printf("column is %d!\n", column);
 //fflush(stdout); 
  vertex = (int *)malloc(sizeof(int) * column);
//read partition info, from the second row of graph info file
  MTA_read_EM_directly(vertex, column, 1 + GRAPH_START_EM);
  
  //second get thread corresponding matrix info
   for(i = 0; i < column; i++){
    // printf("\n%d\t", vertex[i]);
    //  fflush(stdout);
    if(vertex[i] == threadid) row++;
  }//after this loop, row equals to the number of vertexes of the partition
 
  vertex_line = (int *)malloc(sizeof(int) * column);//To temporarily store a single line of the graph matrix
  thread_vertex = (int *)malloc(sizeof(int) * row);//Vertexes of the thread

  //partition graph info
  graph = (int **)malloc(sizeof(int *) * row);
  for(i = 0; i < row; i++){
    graph[i] = (int *)malloc(sizeof(int) * column);
  }

  for(i = 0, k = 0; i < column; i++){
    if(threadid == vertex[i]){
      thread_vertex[k] = i;//from k = 0 to k = row

      MTA_read_EM_directly(vertex_line, column, i * column + (column  + 1) + GRAPH_START_EM);
             
      for(j = 0; j < column; j++){
	*(*(graph + k) + j) = *(vertex_line + j);
      }
      k ++;
    }
  }
   printf("Thread %d vertex is: \t", threadid);
   for(i = 0; i < row; i ++){
    printf("%d\t", *(thread_vertex+i));
   }
   printf("\n");
   fflush(stdout);

   // while(1);

  /*start traverse*/

   // MTA_Bar_Stats(1);
// barrier(MTA_getthreadID(), 64);
 //   MTA_Bar_Stats(0);
 //Thread wait to start traverse together
 MTA_write_EM_directly(&be_read, 1, CORES_SYN_EM_START + threadid);
 while(cores_syn == 0){
    cores_syn = 1;
    MTA_read_EM_directly(cores, CORESNUM, CORES_SYN_EM_START);
    for (i = 0; i < CORESNUM; i ++){
        if (0 == cores[i]){
            cores_syn = 0;
            break;
        }
    }
 }

 printf("NOW thread %d Start! @%d\n",threadid,MTA_getsim_cycle() );
 fflush(stdout);

  for(i = 0; i < row; i ++){
   // printf("#Vertex %d (thread %d) has been visited!\n", thread_vertex[i], threadid);
    MTA_write_EM_directly(&be_read, 1, VISITED_EM + thread_vertex[i]);
	//fflush(stdout);
    for(j = thread_vertex[i]; j < column; j ++){
      if(1 == graph[i][j]){
		sign = 1;
		for(k = 0; k < row; k ++){
			if(j == thread_vertex[k]){
			//	printf("#Edge(%d, %d) (thread %d) has been visited!\n", thread_vertex[i], j, threadid);
		//		fflush(stdout);
                MTA_write_EM_directly(&be_read, 1, VISITED_EM + j);
				sign = 0;
				break;
			}
		}
		if(sign){
			MTA_write(vertex[j], signal, 10*sizeof(int), 0x100 * threadid);
		//	printf("#Cross_edge(%d, %d)(from thread %d to %d) has been visited!\n", thread_vertex[i], j, threadid, vertex[j]);
		  //  fflush(stdout);
			MTA_write_EM_directly(&be_read, 1, VISITED_EM + j);
		}
      }
    }
  }
  printf ("Done %d ! @ %d\n",threadid,MTA_getsim_cycle());
  fflush(stdout);
  /*end traverse*/
  //The end of external memory(EM_SIZE -1 -threadid) is used for shutdown
  MTA_write_EM_directly(&be_read, 1, EM_SIZE - 1 - threadid);
  while(1){
      ;
   }
  return 0;
}
