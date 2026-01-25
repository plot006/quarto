#include "state.h"

char g文字列バッファ[16];

unsigned char gクアルト状態;

unsigned char gループI;
unsigned char gループJ;
unsigned char gループK;
unsigned char gループL;
unsigned char gループM;
unsigned char gループN;
unsigned char gループO;
unsigned char gループP;

unsigned char g座標X;
unsigned char g座標Y;
unsigned char g仮座標X;
unsigned char g仮座標Y;

unsigned char g座標インデックスX;
unsigned char g座標インデックスY;

unsigned char gタイマー値;
unsigned char gタイマー設定回数;

unsigned char g設定アドレス上位;
unsigned char g設定アドレス下位;
unsigned char g現在手番;
unsigned char g手番退避;
unsigned char g駒色選択;
unsigned char g駒色退避;

unsigned char gパッド入力;
unsigned char gスプライトID;

unsigned char g計算値;
unsigned char g一時値1;
unsigned char g一時値2;
unsigned char g一時値3;
unsigned char g一時値4;
unsigned char gフレームカウンタ;
unsigned char g駒フレーム;
unsigned char gアニメ格子[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char g属性黒;
unsigned char g属性白;
unsigned char g属性高;
unsigned char g属性低;
unsigned char g属性四角;
unsigned char g属性丸;
unsigned char g属性平面;
unsigned char g属性穴;
unsigned char gエラーフラグ[2];

unsigned char g設定座標X;
unsigned char g設定座標Y;

unsigned char g一人プレイ;

unsigned char g駒配置スロット[2];
unsigned char g駒位置X[2];
unsigned char g駒位置Y[2];
unsigned char g選択駒番号;
unsigned char g選択駒退避;
unsigned char g駒存在配列[2][8];

unsigned char g背景パレット番号;
unsigned char gゲーム音楽モード;
unsigned char gリーチ状態;
unsigned char g自動選択フラグ;
unsigned char g対CPUフラグ;
unsigned char g上級モード;

unsigned char g属性状態配列[40];
unsigned char g属性更新バッファ[8][3];

unsigned char g乱数ボックス1[4];
unsigned char g乱数ボックス2[4];
unsigned char g乱数ボックス3[2];
unsigned char g乱数ボックス4[8];

unsigned char g盤面状態マップ[4][4][3];

unsigned char gクアルトライン[4][2];

unsigned char g更新リスト[6+8+8+1];
unsigned char g更新駒データ[(3+3)*4+1];
unsigned char g更新駒カラー[3+1+1];

unsigned char g更新デバッグバッファ[3+16+1];
unsigned char gデバッグカウンタ;
