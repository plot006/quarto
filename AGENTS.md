# Repository Guidelines

## プロジェクト構成とモジュール構成
ルートの quarto.c がゲームループ、UI、AI 制御までを司り、ROM 全体のスタート地点になります。lib/ には cc65 ランタイムと 
eslib のアセンブリ実装がまとまり、リンカが参照する crt0.o もここに保存されています。アセットは esource/ に集約され、FamiTracker/ プロジェクト、.dmc サンプル、	ileset*.chr など NES 固有バイナリが整理されています。描画マップやカラーパレットを追加する際は既存の命名を踏襲し、quarto.cfg のメモリマップを意識してください。mesen/ にはデバッグ用エミュレータが同梱され、Makefile と uild.bat が一貫したビルド手順を提供します。生成物 (quarto.nes, .dbg, .o, .s) はルートに出力されるため、PR 前に make clean を忘れないでください。

## ビルド・テスト・開発コマンド
- make clean quarto: MSYS2 環境で実行し、ROM とデバッグ情報を再生成します。初回は CC65_DIR=../cc65 を git clone あるいはサブモジュールで取得し、make してツールチェーンをコンパイルしてください。
- uild.bat: Windows Terminal から UTF-8 コードページへ切り替えつつ make clean all を呼び出すワンライナーです。CI 代替としてローカル自動化に利用できます。
- mesen/mesen quarto.nes: 生成した ROM を即起動し、入力遅延や VRAM バンク切り替えの異常をチェックします。スクリプトを使う場合は esource/or_chr.py で CHR を整列させてからビルドしてください。

## コーディングスタイルと命名規約
インデントはタブ 1 文字 (表示幅 4) を基本とし、ブロックは開括弧を改行して揃えます。8 ビット CPU を想定し、unsigned char や固定長テーブルで状態を保持し、ループカウンタは i, j のような短い名前で統一します。関数・変数は snake_case、コンスタントは UPPER_CASE を用い、データテーブルは ttr_pos のように意味が取れる識別子を付けます。共通処理は極力 lib/neslib.h に寄せ、直接アセンブリを触る際は対応する .s ファイルへコメントを追加してください。

## テストガイドライン
自動テストは未整備です。mesen を使った手動検証で、タイトル→対戦モード→QUARTO 宣言→リザルトまで通しプレイし、フレーム落ちや入力取りこぼしをチェックしてください。quarto.dbg を Mesen のデバッガに読み込むと、シンボルで PPU / CPU ステップを追跡できます。新しいサウンドやグラフィックを追加した場合は FamiTracker で音量バランスを調整し、	ileset*.chr の差分を確認してタイル衝突がないことを確認します。リグレッションテストとして VS CPU セッションを録画し、挙動比較できると安心です。

## コミットとプルリクエストのガイドライン
コミットメッセージは履歴に倣い、短い日本語サマリ (例: ビルド設定を修正) を現在形で記述し、1 トピックごとにコミットを分割してください。生成物やエミュレータは除外し、make clean 後の差分だけを含めます。PR では目的、変更箇所、動作確認手順、関係する Issue を明記し、可能ならスクリーンショットや GIF を添付します。レビュー前にローカルビルド結果 (quarto.nes の起動確認) と既知の影響範囲をコメントにまとめ、マージ条件を明確にしてください。

## 開発環境とリソース Tips
cc65 を更新する際は ../cc65 を個別ブランチで管理し、lib/crt0.o や untime.lib を再生成したらバイナリ差分をチェックします。esource/ 配下の追加ファイルには用途を示す接頭辞 (例: g_, se_) を付け、未使用アセットはコミット前に削除してください。Mesen のステートやスクリーンショットは .gitignore に含まれているため、共有が必要な場合はクラウドストレージや Issue 添付で提供するとスムーズです。VSCode で開発する場合は同梱の quarto.code-workspace を使い、Alchemy65 拡張のデバッグ設定を再利用してください。

## Agent Checklist / エージェント確認事項
- Before commit run make clean quarto, open the newly built quarto.nes in Mesen, and capture a short verification note in the PR template.
- Keep asset provenance documented: note the FamiTracker project name, author credit, and conversion script such as esource/or_chr.py in the commit body.
- When debugging gameplay logic, save a mesen trace log, attach key screenshots, and describe expected versus actual behavior so reviewers can replay the issue quickly.
- Validate emulator settings: set Audio Sample Rate 44100, disable Overclocking, and include any nondefault configuration values inside the PR description.
- After review approval, run git status --short to ensure only source and asset changes remain; delete compiled artifacts before merging.

