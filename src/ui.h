#ifndef QUARTO_UI_H
#define QUARTO_UI_H

void デバッグ表示更新(unsigned char g座標X, unsigned char g座標Y, unsigned char arg長さ, const char *arg文字列);
void 更新初期化(void);
void 次色サイクル(void);
void 色サイクル(void);
void スプライト色サイクル(void);
unsigned char 強制終了チェック(void);
void 背景フラッシュ(unsigned char argアクション);
void 背景ダウン(void);
void 背景アップ(void);
void 次処理へ移動(void);
void タイマー表示初期化(void);
void タイマー表示(void);
void 駒回転停止(void);
void 駒回転アニメ(unsigned char argスピード);
void メッセージ初期化(void);
void メッセージ表示(unsigned char argアクション);
void ライフ初期化(void);
void ライフ表示(void);
void 敗北アニメ(void);
void クアルト宣言処理(void);
void タイマー設定(void);
void 敵駒点滅(unsigned char argアクション);

#endif
