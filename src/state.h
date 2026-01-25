#ifndef QUARTO_STATE_H
#define QUARTO_STATE_H

extern char g文字列バッファ[16];

extern unsigned char gクアルト状態;

extern unsigned char gループI;
extern unsigned char gループJ;
extern unsigned char gループK;
extern unsigned char gループL;
extern unsigned char gループM;
extern unsigned char gループN;
extern unsigned char gループO;
extern unsigned char gループP;

extern unsigned char g座標X;
extern unsigned char g座標Y;
extern unsigned char g仮座標X;
extern unsigned char g仮座標Y;

extern unsigned char g座標インデックスX;
extern unsigned char g座標インデックスY;

extern unsigned char gタイマー値;
extern unsigned char gタイマー設定回数;

extern unsigned char g設定アドレス上位;
extern unsigned char g設定アドレス下位;
extern unsigned char g現在手番;
extern unsigned char g手番退避;
extern unsigned char g駒色選択;
extern unsigned char g駒色退避;

extern unsigned char gパッド入力;
extern unsigned char gスプライトID;

extern unsigned char g計算値;
extern unsigned char g一時値1;
extern unsigned char g一時値2;
extern unsigned char g一時値3;
extern unsigned char g一時値4;
extern unsigned char gフレームカウンタ;
extern unsigned char g駒フレーム;
extern unsigned char gアニメ格子[4][4];

extern unsigned char g属性黒;
extern unsigned char g属性白;
extern unsigned char g属性高;
extern unsigned char g属性低;
extern unsigned char g属性四角;
extern unsigned char g属性丸;
extern unsigned char g属性平面;
extern unsigned char g属性穴;
extern unsigned char gエラーフラグ[2];

extern unsigned char g設定座標X;
extern unsigned char g設定座標Y;

extern unsigned char g一人プレイ;

extern unsigned char g駒配置スロット[2];
extern unsigned char g駒位置X[2];
extern unsigned char g駒位置Y[2];
extern unsigned char g選択駒番号;
extern unsigned char g選択駒退避;
extern unsigned char g駒存在配列[2][8];

extern unsigned char g背景パレット番号;
extern unsigned char gゲーム音楽モード;
extern unsigned char gリーチ状態;
extern unsigned char g自動選択フラグ;
extern unsigned char gCPU思考中;
extern unsigned char g対CPUフラグ;
extern unsigned char g上級モード;

extern unsigned char g属性状態配列[40];
extern unsigned char g属性更新バッファ[8][3];

extern unsigned char g乱数ボックス1[4];
extern unsigned char g乱数ボックス2[4];
extern unsigned char g乱数ボックス3[2];
extern unsigned char g乱数ボックス4[8];

extern unsigned char g盤面状態マップ[4][4][3];

extern unsigned char gクアルトライン[4][2];

extern unsigned char g更新リスト[6+8+8+1];
extern unsigned char g更新駒データ[(3+3)*4+1];
extern unsigned char g更新駒カラー[3+1+1];

extern unsigned char g更新デバッグバッファ[3+16+1];
extern unsigned char gデバッグカウンタ;

#endif
