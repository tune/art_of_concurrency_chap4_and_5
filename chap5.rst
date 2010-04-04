
============================
第５章 スレッドライブラリ
============================

抽象化ライブラリ
==================

スレッドの制御(作成・管理・同期)を抽象化し、プログラマに楽をさせてくれるライブラリ。
スレッドを明示的に作成する処理は無く、柔軟性は落ちる。


OpenMP
-------

専用のpragma、指示文(ディレクティブ)、環境変数を用いて並行処理可能な部分を指定する。
並行実行コードはコンパイラにより生成される。
並列環境と非並列環境でほぼ同一のソースコードを使用できるという利点がある。

現在の最新バージョンは3.0。
Visual Studioやgccでサポートされている。
言語はC/C++/FORTRANに対応している。

.. code-block:: c
    :linenos:

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

Intelスレッディング・ビルディング・ブロック
--------------------------------------------

並列アルゴリズムが定義、実装、提供されており、
並行処理がカプセル化されたクラスを通して使用する。

商用バージョンとオープンソースバージョンがある。



明示的スレッドライブラリ
============================

Pthread
---------

POSIX thread


Windowsスレッド
---------------

Windowsで使用できるスレッド


その他
=========

プログラミング言語のライブラリとして使用されるものと、並列プログラミング言語がある。
最近ではGPUに特化したデータ並列プログラミング言語もある。

ライブラリ
------------

並列プログラミング言語
-----------------------

GPU特化データ並列プログラミング言語
------------------------------------






