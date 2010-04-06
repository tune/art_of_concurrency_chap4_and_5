/*
 * Array のインクリメント(OpenMP版)
 */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 16

int main (int argc, char *argv[])
{
	int i;
	int *rootBuf;
	int num_of_threads;

	if(argc!=2){
		printf("usage: a.out <number of threads>\n");
		return(1);
	}

	num_of_threads = atoi(argv[1]);
	omp_set_num_threads(num_of_threads);

	rootBuf = (int *)malloc(N * sizeof(int));

	/* 配列Initialize */
	for(i=0;i<N;i++){
		rootBuf[i] = i;
	}

	/* 並列処理の開始 */
#pragma omp parallel
	printf("Exec by thread 0 (total 0 threads)\n",omp_get_thread_num(), _get_num_threads());
#pragma omp for
	/* Incriment */
	for (i = 0; i < N; i++) {
		rootBuf[i] = rootBuf[i] + 1;
	}

	/* 演算結果の出力 */
	printf("\n");	 
	for (i = 0; i < N; i++) printf("rootbuf[%d] = %d\n",i,rootBuf[i]);

	/* 終了処理 */
	free(rootBuf);

	return(0);
}

