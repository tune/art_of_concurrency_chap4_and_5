
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

スレッドの管理はfork-joinモデルを採用している。
マスタスレッドが並行処理可能な領域(パラレルリージョン)に到達すると、子スレッドが生成され(fork)、
各スレッドがパラレルリージョンを実行する。
パラレルリージョンの終了時には子スレッドが待ち合わせ(join)、
パラレルリージョン後からメインスレッドが処理を続行する。

主な構文は以下の通り。

:parallel for: ループの繰り返し以外で並列処理を用いる場合に使う。sheduleを使うことで静的・動的の切り替えが可能。
:atomic: 1実行文の実行において割り込みが発生しないことを保証する。
:reduction: ループ処理の結果をまとめる。
:task(OpenMP 3.0以降): タスク並行性を実現する。

現在の最新バージョンは3.0。
Visual Studioやgccでサポートされている。
言語はC/C++/FORTRANに対応している。

OpenMPのサンプル1(本より転載、動作確認済み)

.. literalinclude:: _static/openmp.c
    :language: c
    :linenos:

OpenMPのサンプル2(ネットで見つけたサンプルを転載、動作未確認)

.. literalinclude:: _static/openmp2.c
    :language: c
    :linenos:


Intelスレッディング・ビルディング・ブロック
--------------------------------------------

並列アルゴリズムが定義、実装、提供されており、
並行処理がカプセル化されたクラスを通して使用する。
商用バージョンとオープンソースバージョンがある。

主なクラスは以下の通り(Wikipediaより転載)

タスクスケジューラ
*******************

:task_sheduler_initクラス: ? 

並列処理アルゴリズム（Generic Parallel Algorithms）
****************************************************

:parallel_forクラス: ループ間で依存性がない単純なループの並列処理
:parallel_reduceクラス: 指定した範囲をより小さな範囲に再帰的に分割し並列処理
:parallel_scanクラス: 並列プリフィックスを計算
:parallel_whileクラス: 不明領域、動的領域変更を伴う独立したループ操作
:parallel_sortクラス: 並列処理でソートを行う
:pipelineクラス: パイプライン処理

コンテナクラス
****************

:concurrent_hash_mapクラス: STLのmapクラスをスレッドセーフにしたもの
:concurrent_queueクラス: STLのqueueクラスをスレッドセーフにしたもの
:concurrent_vectorクラス: STLのvectorクラスをスレッドセーフにしたもの

アシスタントクラス
*******************

:blocked_rangeクラス: 線形範囲を示すクラス　アルゴリズムやコンテナ走査に使用される
:blocked_range2dクラス: 2次元範囲を示すクラス　blocked_rangeクラスと同様にアルゴリズムやコンテナ走査に使用される
:simple_partitionerクラス: 範囲を限界まで再帰的に細分化するようグレインサイズを設定する　blocked_range/blocked_range2dクラスと共に使用される
:auto_partitionerクラス: タスクスケジューラの挙動を元に最適なグレインサイズを設定する　blocked_range/blocked_range2dクラスと共に使用される

同期プリミティブ
*****************

:atomicクラス: アトミック操作を行う
:spin_mutexクラス: スピンロックを使うミューテックス
:spin_rw_mutexクラス: 複数のスレッドからアクセス可能なspin_mutex
:queuing_mutexクラス: スケーラブルなミューテックス
:queuing_rw_mutexクラス: 複数のスレッドからアクセス可能なqueuing_mutex
:mutexクラス: OSのミューテックスと同様なミューテックス

パフォーマンス測定
********************

:tick_countクラス: 時間取得

Linuxにおけるインストール環境の整備がイマイチで動作確認出来ず。

Intel TBBのサンプル(本より転載、動作未確認)

.. literalinclude:: _static/intel_tbb.cpp
    :language: cpp
    :linenos:


明示的スレッドライブラリ
============================

Pthread
---------

POSIX threadのこと。

サポートされている代表的な構造体に以下がある。

:pthread_t: スレッドのハンドル
:pthread_mutex_t: mutex
:pthread_cond_t: 状態変数

またサポートされている代表的な関数に以下がある。

:pthread_create(): スレッドを関数と関連付ける
:pthread_join(): 他のスレッドと処理を待ち合わせる
:pthread_mutex_lock(): mutexのロック
:pthread_mutex_unlock(): mutexのアンロック
:pthread_cond_wait(): 状態変数の変化があるまで処理を待たせる
:pthread_cond_signal(): 状態変数の変化待ちをしていたスレッドの処理を再開
:pthread_cond_broadcast(): 状態変数の変化待ちをしている全てのスレッド処理を再開

Pthreadのサンプル(本より転載、動作確認済)

.. literalinclude:: _static/pthread.c
    :language: c
    :linenos:


Windowsスレッド
---------------

Windowsで使用できるスレッド。
提供される関数はPthreadと大差ないはず、必要に応じて調べて使いましょう。


その他
=========

プログラミング言語のライブラリとして使用されるものと、並列プログラミング言語がある。
最近ではGPUに特化したデータ並列プログラミング言語もある。

ライブラリ
------------

Intel社のライブラリ(有償)。
 * Intel Math Kernel LIbrary
 * Intel Performance Primitives

IPPライブラリの全ての関数はスレッドセーフ、使える環境があるなら積極的に使いましょう。

並列プログラミング言語
-----------------------

関数型言語が多い。

 * Haskell
 * Erlang
 * go-lang
 * Scala

GPU特化データ並列プログラミング言語
------------------------------------

 * CUDA
 * OpenCL

