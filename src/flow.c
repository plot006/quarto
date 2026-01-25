//this example shows metasprite use, two pads polling,
//and simple collision detection that changes palette

#include "lib/neslib.h"
#include "resource/test2_blank.h"
#include "resource/open_name.h"
#include "resource/qr.h"
#include "resource/menu.h"

#include <stdlib.h>

#include "anim.h"
#include "board.h"
#include "cpu.h"
#include "data.h"
#include "flow.h"
#include "judge.h"
#include "move.h"
#include "select.h"
#include "state.h"
#include "ui.h"

//#define debug
#ifdef debug
#endif

static void 変数初期化(void){
	//更新初期化() ;
	//set initial coords
	g自動選択フラグ = 0 ;
	g一人プレイ=1;
	g上級モード=0 ;
	g対CPUフラグ=1;
	gタイマー設定回数 = 60 ;
	gクアルト状態 = 0 ;
	g選択駒番号 = 0;
	g現在手番 = 1;
	g駒色選択 = 0;
	g駒配置スロット[0]=3;
	g駒配置スロット[1]=1;

	gループI=0;
	gループJ=0;
	gループK=0;
	gループL=0;
	gループM=0;
	gループN=0;
	gループO=0;
	gループP=0;

	g座標X=0;
	g座標Y=0;
	g仮座標X=0;
	g仮座標Y=0;

	g座標インデックスX=0;
	g座標インデックスY=0;

	g設定アドレス上位=0;
	g設定アドレス下位=0;

	gパッド入力=0;
	gスプライトID=0;

	g計算値=0;

	g駒位置X[0] = 72 ;
	g駒位置Y[0] = 122 ;
	g駒位置X[1] = 152 ;
	g駒位置Y[1] = 122 ;

	gタイマー値 = 0 ;

	gゲーム音楽モード = 1; // 1:game1, 3:game2
	gリーチ状態 = 0 ;
	gCPU思考中 = 0 ;

	//init other vars
	
	g一時値1 = 0 ;	//collision flag
	g一時値2 = 0 ;
	g一時値3 = 0 ;
	g一時値4 = 0 ;
	gフレームカウンタ = 0 ;	//gフレームカウンタ counter

	for( gループI=0; gループI < 40; gループI++ ){
		g属性状態配列[gループI] = 0x55 ;
	}
	gエラーフラグ[0]=0;
	gエラーフラグ[1]=0;

//	memfill(g属性状態配列, 0x55, 40 ) ;
}

// ========================================================================================
// ========================================================================================
void リセット処理(void)
{
	scroll(0,0);
	変数初期化() ;

	oam_clear() ;
	ppu_off() ;
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_unrle((unsigned char*)menu);
	pal_bg(k背景パレット配列[g背景パレット番号]);
	ppu_on_all();//enable rendering

	// MODE SELECT.
	デバッグ表示更新(16,17, 3, "   ");
	デバッグ表示更新(16,17, 3, itoa(gタイマー設定回数, &g文字列バッファ[0], 10 ));
	デバッグ表示更新(16,19, 8, "NORMAL  ");

	while(1){
		gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ;
		if(gパッド入力&PAD_UP && g一人プレイ == 0){
			g一人プレイ = 1 ;
			g対CPUフラグ = 1 ;
			sfx_play(2,0);
		}

		if(gパッド入力&PAD_DOWN && g一人プレイ == 1){
			g一人プレイ = 0 ;
			g対CPUフラグ = 0 ;
			sfx_play(2,0);
		}
		if(gパッド入力&PAD_A){
			sfx_play(5,0);
			for( ; gパッド入力&PAD_A ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}
			break ;
		}
		gスプライトID = 0 ;
		gスプライトID = oam_meta_spr( 70, 63+(g一人プレイ==1?0:1*16), gスプライトID, kメタ右カーソル) ;
		gフレームカウンタ++ ;
	}
	乱数ボックス初期化() ;
/*
	デバッグ表示更新(1,50, 1, itoa(g乱数ボックス1[0], &g文字列バッファ[0], 10 ));
	デバッグ表示更新(3,50, 1, itoa(g乱数ボックス1[1], &g文字列バッファ[0], 10 ));
	デバッグ表示更新(5,50, 1, itoa(g乱数ボックス1[2], &g文字列バッファ[0], 10 ));
	デバッグ表示更新(7,50, 1, itoa(g乱数ボックス1[3], &g文字列バッファ[0], 10 ));
	デバッグ表示更新(1,51, 1, itoa(g乱数ボックス2[0], &g文字列バッファ[0], 10 ));
	デバッグ表示更新(3,51, 1, itoa(g乱数ボックス2[1], &g文字列バッファ[0], 10 ));
	デバッグ表示更新(5,51, 1, itoa(g乱数ボックス2[2], &g文字列バッファ[0], 10 ));
	デバッグ表示更新(7,51, 1, itoa(g乱数ボックス2[3], &g文字列バッファ[0], 10 ));
*/	
	// TIMER設定.
	gスプライトID = 0 ;
	gスプライトID = oam_meta_spr( 70, 134, gスプライトID, kメタ右カーソル) ;
	while(1){
		gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ;
		if(gパッド入力&PAD_UP&& gタイマー設定回数<=200){
			gタイマー設定回数+= gパッド入力&PAD_B?10:1 ;

			if( gタイマー設定回数 < 3 ){ gタイマー設定回数=3 ;} ;

			デバッグ表示更新(16,17, 3, "   ");
			デバッグ表示更新(16,17, 3, itoa(gタイマー設定回数, &g文字列バッファ[0], 10 ));
			sfx_play(2,0);
			delay(2) ;
		}

		if(gパッド入力&PAD_DOWN&&gタイマー設定回数>3){
			g一時値1 = gパッド入力&PAD_B?10:1;
			if( gタイマー設定回数 <= g一時値1 ){ 
				gタイマー設定回数 = 3 ;
			}else{
				gタイマー設定回数-= g一時値1 ;
			}
			デバッグ表示更新(16,17, 3, "   ");
			デバッグ表示更新(16,17, 3, itoa(gタイマー設定回数, &g文字列バッファ[0], 10 ));
			sfx_play(2,0);
			delay(2) ;
		}
		if(gパッド入力&PAD_RIGHT && gタイマー設定回数!=0){
			gタイマー設定回数 = 0 ;
			デバッグ表示更新(16,17, 3, "OFF");
			sfx_play(2,0);
			delay(2) ;
		}
		if(gパッド入力&PAD_A){
			sfx_play(5,0);
			for( ; gパッド入力&PAD_A ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}
			break ;
		}
	}
	gタイマー値=gタイマー設定回数;

	// RULE選択.
	gスプライトID = 0 ;
	gスプライトID = oam_meta_spr( 70, 151, gスプライトID, kメタ右カーソル) ;
	while(1){
		gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ;
		if(gパッド入力&PAD_UP){
			g上級モード = 0 ;
			デバッグ表示更新(16,19, 8, "NOMAL   ");
			sfx_play(2,0);
			delay(2) ;
			for( ; gパッド入力&PAD_UP ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}
		}

		if(gパッド入力&PAD_DOWN){
			g上級モード = 1 ;
			デバッグ表示更新(16,19, 8, "ADVANCED");
			sfx_play(2,0);
			delay(2) ;
			for( ; gパッド入力&PAD_DOWN ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}
		}
		if(gパッド入力&PAD_A){
			sfx_play(5,0);
			for( ; gパッド入力&PAD_A ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}
			break ;
		}
	}
	
	oam_clear() ;
	pal_spr(k背景パレット配列[g背景パレット番号]);//set background palette from an array
	pal_bg(k背景パレット配列[g背景パレット番号]);//set background palette from an array

	ppu_off() ;
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_unrle((unsigned char*)test2_blank);
	ppu_on_all();//enable rendering
	
	music_stop();

	//scroll(0,0) ;
	delay(30) ;

/*
	delay(30) ;

	ppu_off() ;
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_unrle((unsigned char*)test2_init);

	盤面アニメ(0) ;
	ppu_on_all();//enable rendering
	delay(1) ;

	盤面アニメ(1) ;
//	sfx_play(3,0);
	oam_clear() ;
*/
	

	delay(15) ;
	for( g座標X = 0; g座標X < 8; g座標X++ ){
		sfx_play(2,0);
		// P1
		ストック駒配置(g座標X*4,2,0xAA, (unsigned char*)k駒スプライトリスト[0][0][g座標X]) ;

	}
	for( g座標X = 0; g座標X < 8; g座標X++ ){
		sfx_play(2,1);
		// P2
		ストック駒配置(28-(g座標X*4),6,0x55, (unsigned char*)k駒スプライトリスト[0][1][7-g座標X]) ;

	}
	更新初期化() ;
	for( g一時値1=0; g一時値1 < 16; g一時値1++ ){
		盤面上昇(k盤面アニメ順序[g一時値1][0], k盤面アニメ順序[g一時値1][1] );
	}

	memfill( g盤面状態マップ, 0x00, 48 );
	memfill( g駒存在配列, 0x01, 16 );
	memfill( gクアルトライン, 0x00, 8 );

	music_play(gゲーム音楽モード) ;


	//delay(10) ;
/*
	gスプライトID = 0 ;
	gスプライトID = oam_meta_spr( g選択駒番号*32+8, 40+g駒色選択*50, gスプライトID, g駒色選択==0 ? kカーソルスプライト : kカーソルスプライト2 ) ;
*/
	while(1)
	{
		delay(10) ;

		駒選択処理() ;
		クアルト判定処理() ;

		駒移動処理() ;
		クアルト判定処理() ;
	}
}

// ========================================================================================
// ========================================================================================
void メインループ(void)
{
	変数初期化() ;

#ifndef debug
	pal_spr(k基本パレット2);
	pal_bg(kオープンパレット1);//set background palette from an array

	vram_adr(NAMETABLE_A);//set VRAM address
	vram_unrle((unsigned char*)open_name);
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_fill(0x00, 0x0180);
	gスプライトID = 0 ;

	pal_bright(0);
	ppu_on_all();//enable rendering
	//delay(20) ;

	背景アップ() ;
	delay(20) ;
	g一時値1 = 0 ;

	while(1)
	{
		if(gフレームカウンタ%20==0){ 次処理へ移動(); };

		gフレームカウンタ++;

		if( 強制終了チェック() ){ break ; }

	}
	g背景パレット番号 = 0;

	// QRコード処理.
	gパッド入力 = pad_poll(0);
	if(gパッド入力&PAD_SELECT ){

		ppu_off() ;
		bank_bg(1);
		oam_clear() ;
		vram_adr(NAMETABLE_A);//set VRAM address
		vram_unrle((unsigned char*)qr);
		ppu_on_all();//enable rendering

		while(1){
			for( ; gパッド入力&PAD_SELECT ;gパッド入力=pad_poll(0) ){
				delay(1) ;
			}
			break ;
		}

		while(1){
			gパッド入力 = pad_poll(0);
			if(gパッド入力&PAD_SELECT ){
				bank_bg(0);
				リセット処理() ;
			}
		}
	}

	ppu_off() ;
	//delay(10) ;

	music_play(2) ;
	delay(60) ;
	music_stop() ;

#endif
/*
	//sfx_play(2,0);
	oam_clear() ;
	for( g座標Y = 0; g座標Y < 250; g座標Y++ ){
		scroll(0,g座標Y) ;
		if( gフレームカウンタ % 10 == 0 ){ppu_wait_nmi();}
		gフレームカウンタ++ ;
	}
*/
	while(1){
		リセット処理() ;
	}
}
