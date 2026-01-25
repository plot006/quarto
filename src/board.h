#ifndef QUARTO_BOARD_H
#define QUARTO_BOARD_H

unsigned char 配置判定(unsigned char arg位置X, unsigned char arg位置Y);
void ストック駒配置(unsigned char arg位置X, unsigned char arg位置Y, unsigned char argカラー, unsigned char* argメタデータ);
void バー自動描画(void);
void 駒配置(unsigned char arg位置X, unsigned char arg位置Y, unsigned char argカラー, unsigned char* argメタデータ);
void カーソル描画(void);
unsigned char クアルト判定(void);
void 盤面仮設定(unsigned char g座標X, unsigned char g座標Y);
void 盤面仮解除(unsigned char g座標X, unsigned char g座標Y);
unsigned char 事前クアルト確認(unsigned char g座標X, unsigned char g座標Y);
unsigned char リーチ判定(void);

#endif
