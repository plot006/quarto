#include "lib/neslib.h"

#include "anim.h"
#include "board.h"
#include "cpu.h"
#include "data.h"
#include "defs.h"
#include "judge.h"
#include "move.h"
#include "state.h"
#include "ui.h"

static void 移動ボタンAイベント(void)
{
	駒配置( g座標X/8, g座標Y/8, g駒色選択==0?0xAA:0x55, (unsigned char*)k駒スプライトリスト[0][0][g選択駒番号] ) ;
	/*
	デバッグ表示更新(1,10, 1, itoa(g座標インデックスX, &g文字列バッファ[0], 10 ));
	デバッグ表示更新(4,10, 1, itoa(g座標インデックスY, &g文字列バッファ[0], 10 ));
	*/
	g盤面状態マップ[g座標インデックスX][g座標インデックスY][_KOMA_TYPE] = g駒色選択==0 ? k駒属性マスク[1+g選択駒番号] : k駒属性マスク[1+g選択駒番号+8] ;
	g盤面状態マップ[g座標インデックスX][g座標インデックスY][_CHOOSE_KOMA] = g選択駒番号 ;
	g盤面状態マップ[g座標インデックスX][g座標インデックスY][_SEL_BW] = g駒色選択 ;

	oam_clear() ;
	//pal_spr(k背景パレット配列[g背景パレット番号]);//set background palette from an array
	
	//盤面駒色設定( g座標X/8, g座標Y/8, g駒色選択==0?0xAA:0x55 ) ;
	
	//putStageColor( g設定座標X, g設定座標Y ) ;
	sfx_play(4,1);
	
	//バー初期化() ;
	メッセージ表示(0) ;

	リーチ判定() ;
	if( gリーチ状態 == 1 && gゲーム音楽モード != 3 ){
		gゲーム音楽モード = 3 ;
		music_stop() ;
		//背景フラッシュ(8) ;
		delay(30) ;
		music_play(gゲーム音楽モード) ;
	}

}

void 駒移動処理(void)
{
	
	for( ; gパッド入力&PAD_A ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
		//delay(1) ;
	}

//	gタイマー値 = setCount ;
	//タイマー表示() ;
	//gタイマー値 = gタイマー設定回数 ;
	g自動選択フラグ=0;
	while(1)
	{
		タイマー設定() ;

		//delay(1) ;
		//パッド無入力() ;
		gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ;
		if( g対CPUフラグ != 0 && g現在手番==0 ){
			gパッド入力=0  ;
			g自動選択フラグ = 1 ;
		} ;

		if(gパッド入力&PAD_LEFT){
			if( g座標X > 4 ){
				g座標X-= gパッド入力&PAD_B ? 4 : 2 ;
			}
		}
		if(gパッド入力&PAD_RIGHT){
			if( g座標X < 232){
				g座標X+= gパッド入力&PAD_B ? 4 : 2 ;
			}
		}
		if(gパッド入力&PAD_UP){
			if( g座標Y > 4 ){
				g座標Y-= gパッド入力&PAD_B ? 2 : 1 ;
			}
		}

		if(gパッド入力&PAD_DOWN){
			if( g座標Y < 212){
				g座標Y+= gパッド入力&PAD_B ? 2 : 1 ;
			}
		}
		if(gパッド入力&PAD_A){
			if( 配置判定(g座標X/8, g座標Y/8) == 1 ){
				sfx_play(3,0);
				
				for( ; gパッド入力&PAD_A ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
					//ppu_wait_nmi();
					//gフレームカウンタ++ ;
					//delay(1) ;
				}
			}else{
				移動ボタンAイベント();

				if( 終了チェック() == 1 ){
					if( クアルト判定() == 1 ){
						gクアルト状態 = 1 ;
						return ;
					}else{
						敗北アニメ() ;
					}
				}

				return ;
			}
			
		}
		if(gパッド入力&PAD_SELECT){
			次色サイクル() ;
			for( ; gパッド入力&PAD_SELECT ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}

			/*
			oam_clear() ;
			カーソル描画() ;

			g駒存在配列[g駒色選択][g選択駒番号] = 1 ;
			ストック駒配置((g選択駒番号*4),g駒色選択==0?0:26, g駒色選択==0?0xAA:0x55, (unsigned char*)k駒スプライトリスト[0][0][g選択駒番号]) ;
			g現在手番 = g現在手番 == 0? 1:0 ;
			gタイマー値 = gタイマー設定回数 ;

			sfx_play(6,0);
			
			//バー初期化();
			メッセージ表示(0) ;

			return ;
			*/
		}

		if(gパッド入力&PAD_START){
			クアルト宣言処理() ;

			if( クアルト判定() == 1 ){
				gクアルト状態 = 1 ;
				return ;
			}else{
				sfx_play(3,1);
				music_play(gゲーム音楽モード) ;
				gエラーフラグ[g現在手番]++ ;
				if( gエラーフラグ[g現在手番] == 3 ){
					敗北アニメ() ;
				}
			}
			ライフ表示() ;
			メッセージ表示(1) ;
			for( ; gパッド入力&PAD_START ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}
			continue ;
		}
		if( g自動選択フラグ==1){
			g駒色退避 = g駒色選択;
			g選択駒退避 = g選択駒番号;
			g手番退避 = g現在手番 ;
			// 自動コマ配置.
			if( g対CPUフラグ == 1 && g現在手番==0 && クアルト判定() == 1 ){
				クアルト宣言処理() ;
				gクアルト状態 = 1 ;
				return ;
			}

			g仮座標X = g座標X;
			g仮座標Y = g座標Y ;

			// CPU戦の場合ここでクアルトを狙う.
			タイマー表示初期化() ;

			乱数ボックス初期化() ;
			座標自動設定();
			if( 終了チェック() == 1 ){
				//while(1){continue;}
				敗北アニメ() ;
				return ;
			}
			oam_clear() ;
			駒移動演出( g仮座標X, g仮座標Y, g座標X-9, g座標Y-12, (unsigned char*)k駒スプライトリスト[0][g駒色選択==0?1:0][g選択駒番号] ) ;

			移動ボタンAイベント() ;
			if( g対CPUフラグ == 1 && g現在手番==0 && クアルト判定() == 1 ){
				クアルト宣言処理() ;
				gクアルト状態 = 1 ;
				return ;
			}

			return ;
			
		}
		
		ppu_wait_nmi();	// wait for next TV gフレームカウンタ
		gフレームカウンタ++;

		oam_clear() ;
		gスプライトID = 0 ;
		if( 配置判定(g座標X/8, g座標Y/8) != 1 ){
			gスプライトID = oam_meta_spr( g設定座標X*8+8, g設定座標Y*8+(gフレームカウンタ%8)+10, gスプライトID, g駒色選択==0?kメタ位置1: kメタ位置2 ) ;
		}
		gスプライトID = oam_meta_spr( g座標X, g座標Y, gスプライトID, k駒スプライトリスト[g駒存在配列[g駒色選択][g選択駒番号]][g駒色選択==0?1:0][g選択駒番号] ) ;
			
	}
}
