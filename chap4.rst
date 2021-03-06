
=========================================================
第４章 マルチスレッドアプリケーション設計の8つのルール
=========================================================

8つのルール
============

スレッド化設計モデルに加えるべきルール、順不同。

 1. 真に独立した処理を特定する
 2. 並行性はより上位で実装する
 3. コア数増加に備えスケーラビリティ対応を早期に計画する
 4. スレッドセーフなライブラリを使用する
 5. 適切なスレッドモデルを採用する
 6. 実行順序を前提としない
 7. ローカル変数を使用する、できなければロックで保護する
 8. 並行性向上のためのアルゴリズム変更を恐れない


ルール1: 真に独立した処理を特定する
------------------------------------

これが最も重要。
処理が互いに独立していなければ並行実行できない。
並行化出来ない依存性があったら「2.2 並列化不可能？」を参照すること。


ルール2: 並行性はより上位で実装する
-------------------------------------

並行性を見つける方法は2種類ある。

 * ボトムアップ
 * トップダウン

どちらを選ぶにせよ、より上位で並行化した方が良い。
アルゴリズムの上位レイヤほど、より多くの独立した処理を含んでいるからである。


ルール3: コア数増加に備えスケーラビリティ対応を早期に計画する
---------------------------------------------------------------

今後もプロセッサコア数は増加の一途であることが予想される。
開発中のソフトウェアであっても、このことは考慮に入れておくべき。

並行性の設計はタスク分解とデータ分解の2種類があったが、
アプリケーション内の独立した処理とデータサイズではデータサイズの方が増える傾向が強いため、
データ分解設計の方がスケーラビリティーでは有利である。

設計中のソフトウェア/システムが計画している処理能力を十分に達成できても、
将来要求される処理能力は増加する可能性が高い。
**処理能力に余裕があれば、処理するデータはまだ誰かが持っている。**


ルール4: スレッドセーフなライブラリを使用する
----------------------------------------------

*車輪の再発明は決していい方法ではない。*
一般的なライブラリ関数で置換可能であればそれを使うこと。

 * Intelマス・カーネル・ライブラリ
 * Intelインテグレーテッド・パフォーマンス・プリミティブ

使用の際には、マニュアルを参照してライブラリがスレッドセーフであるかを必ず確認する。
自作ライブラリなら関数がリエントラント [#]_ であるように設計する。

.. [#] プログラムやサブルーチンが、静的な内部状態をもたないので、
        再帰的にも、複数のスレッドからも、データを壊すおそれなく呼び出せる場合をいう。
        関数がリエントラントであるためには、静的データを保持してはならず、
        静的データへのポインタを返してもいけない。
        呼出し側が提供したデータだけに基づいて処理を行わなければならず、
        リエントラントでない関数を呼び出してはならない。
        ( `Wikipedia リエントラント <http://http://ja.wikipedia.org/wiki/%E3%83%AA%E3%82%A8%E3%83%B3%E3%83%88%E3%83%A9%E3%83%B3%E3%83%88>`_ )


ルール5: 適切なスレッドモデルを採用する
-----------------------------------------

スレッドの明示的な使用(Pthread/Windowsスレッドの直接的な利用)は避けるべき。
抽象化ライブラリ(OpenMP/Intel Threading Building Blocks)を通してスレッドを利用すること。
多くの並行化作業はスレッドを明示的に操作する必要があるほど柔軟性が求められておらず、
実装が複雑になるとバグが入る可能性が高くなる。

開発上の規約などにより、抽象化ライブラリの使用が禁止されている場合でも、
プロトタイプは抽象化ライブラリを使うことで手間を省くことが出来る。


ルール6: 実行順序を前提としない
--------------------------------

スレッドの実行はOSなどのスケジューラで管理されるものであり、
アプリケーション側で順序を決定することは出来ない(非決定性がある)。
スレッドがどんな順序で実行されても正しい結果を返すように設計すること。

また性能の観点から、出来る限りスレッドの実行に制約を課すべきではない。
例えばスレッド処理の待ち合わせをするときは本当に必要か立ち止まって考える必要がある。


ルール7: ローカル変数を使用する、できなければロックで保護する
--------------------------------------------------------------

同期処理は必要悪だが、最小限の使用に留める必要がある。
共有変数の更新が少ないほど、オーバーヘッドも少なく済む。

まずはスレッドごとに持たせるローカル変数で問題が解決出来ないかを考える。
駄目なら適切なロックを共有データに対して適用する。
デッドロックの温床となるため、1データに対して複数のロックを対応付けてはならない。


ルール8: 並行性向上のためのアルゴリズム変更を恐れない
-------------------------------------------------------

逐次処理では最良だったアルゴリズムが、並行処理では最良でないことがある。
並行化出来なかったり、他のアルゴリズムの方が並行化による恩恵を受けやすいことがある。

