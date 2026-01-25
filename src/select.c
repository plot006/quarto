#include "lib/neslib.h"

#include "anim.h"
#include "board.h"
#include "cpu.h"
#include "data.h"
#include "judge.h"
#include "select.h"
#include "state.h"
#include "ui.h"

static void 選択ボタンAイベント(void)
{
	g駒存在配列[g駒色選択][g選択駒番号] = 0 ;
	ストック駒配置((g選択駒番号*4),g駒色選択==0?2:6, g駒色選択==0?0x00:0xFF,  (unsigned char*)k駒スプライトリスト[0][0][g選択駒番号]) ;

	oam_clear() ;
	//pal_spr(k背景パレット配列[g背景パレット番号]);//set background palette from an array

	//gスプライトID = 0 ;
	g座標X = g選択駒番号*32 ;
	g座標Y = 10+g駒色選択*32 ;
	駒移動演出( g座標X, g座標Y, g現在手番==0?24:200, 70, (unsigned char*)k駒スプライトリスト[0][g駒色選択==0?1:0][g選択駒番号] ) ;
	//gスプライトID = oam_meta_spr( g座標X, g座標Y, gスプライトID, k駒スプライトリスト[0][g駒色選択==0?1:0][g選択駒番号] ) ;
	ppu_wait_nmi();	// wait for next TV gフレームカウンタ
	
	sfx_play(5,1);

	g現在手番 = g現在手番 == 0? 1:0 ;
	gタイマー値 = gタイマー設定回数 ;
	
	メッセージ表示(1);
}

void 駒選択処理(void)
{
	メッセージ表示(0) ;
	ライフ表示() ;

//	gタイマー値 = 5;
//	タイマー表示() ;
	//gタイマー値 = gタイマー設定回数 ;
	//g自動選択フラグ=0;
	while(1)
	{
		カーソル描画() ;
		タイマー設定() ;
		// カーソルセレクト
		//パッド無入力() ;
		gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ;
		if( g対CPUフラグ != 0 && g現在手番==0 ){
			gパッド入力=0 ;
			g自動選択フラグ = 1 ;
		} ;

		if(gパッド入力&PAD_LEFT){
			//gフレームカウンタ = 0 ;
			g選択駒番号 = g選択駒番号 <= 0 ? 7 : --g選択駒番号 ;
			カーソル描画() ;
			for( ;gパッド入力&PAD_LEFT ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				ppu_wait_nmi();	// wait for next TV gフレームカウンタ
				gフレームカウンタ++ ;
				タイマー設定() ;
				カーソル描画() ;
				if( g自動選択フラグ==1){break ;}
			}
		}
/*
			if( moving == 0 || moving == 2 ){
				//for( gループI = 0 ; パッド無入力() != 1 && gループI < 25; gループI++ ){
				for( gループI = 0; gループI < 25 &&  gパッド入力&PAD_LEFT ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
					gループI++ ;
					//delay(1) ;
					ppu_wait_nmi();	// wait for next TV gフレームカウンタ
					gフレームカウンタ++ ;
					タイマー設定() ;
				}
			}else{
				delay(5) ;
			}
			moving = 1 ;
		}
*/

		if(gパッド入力&PAD_RIGHT){
			//gフレームカウンタ = 0 ;
			g選択駒番号 = g選択駒番号 >= 7 ? 0 : ++g選択駒番号 ;
			カーソル描画() ;
			for( ;gパッド入力&PAD_RIGHT ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				ppu_wait_nmi();	// wait for next TV gフレームカウンタ
				gフレームカウンタ++ ;
				タイマー設定() ;
				カーソル描画() ;
				if( g自動選択フラグ==1){break ;}
			}
		}
/*
			if( moving == 0 || moving == 1 ){
				//for( gループI = 0 ; パッド無入力() != 1 && gループI < 25; gループI++ ){
				for( gループI = 0; gループI < 25 && gパッド入力&PAD_RIGHT ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
					gループI++ ;
					//delay(1) ;
					ppu_wait_nmi();	// wait for next TV gフレームカウンタ
					gフレームカウンタ++ ;
					タイマー設定() ;
				}
			}else{
				delay(5) ;
			}
			moving = 2 ;
		}
*/
		if(gパッド入力&PAD_UP){
			g駒色選択 = 0 ;
			//カーソル描画() ;
		}
		if(gパッド入力&PAD_DOWN){
			g駒色選択 = 1 ;
			//カーソル描画() ;
		}

		if(gパッド入力&PAD_A){
			if( g駒存在配列[g駒色選択][g選択駒番号] == 0 ){
				sfx_play(3,0);

				for( ; gパッド入力&PAD_A ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
					//delay(1) ;
				}
				continue ;
			}
			
			g一時値1 = pad_poll(1) ;
			if( g一時値1&PAD_SELECT && 敗北チェック() == 1 ){
				sfx_play(3,0);
				continue ;
			}
			
			選択ボタンAイベント() ;
			return ;
			
		}

		if(gパッド入力&PAD_SELECT){
			次色サイクル() ;
			for( ; gパッド入力&PAD_SELECT ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}
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
			メッセージ表示(0) ;
			for( ; gパッド入力&PAD_START ;gパッド入力=pad_poll((g現在手番!=0 || g一人プレイ==1)?0:1) ){
				//delay(1) ;
			}
			continue ;
		}
		if( g自動選択フラグ==1){
			gCPU思考中 = 1 ;
			oam_clear() ;
			g駒色退避 = g駒色選択;
			g選択駒退避 = g選択駒番号;
			g手番退避 = 1 ;

			// 自動コマ選択.
			乱数ボックス初期化() ;

			if( g対CPUフラグ != 1 && g駒存在配列[g駒色選択][g選択駒番号] != 0 ){
				
			}else{
				自動選択処理(0) ;
				if( 終了チェック() == 1 ){
					敗北アニメ() ;
					gCPU思考中 = 0 ;
					return ;
				}
			}
			カーソル描画() ;
			
			選択ボタンAイベント() ;
			gCPU思考中 = 0 ;
			return ;
			
		}

		ppu_wait_nmi();	// wait for next TV gフレームカウンタ
		gフレームカウンタ++;
	}
}
