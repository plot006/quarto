#include "lib/neslib.h"

#include "data.h"
#include "defs.h"
#include "flow.h"
#include "judge.h"
#include "state.h"
#include "ui.h"

unsigned char 終了チェック(void)
{
	unsigned char q = 0 ;
	unsigned char r = 0 ;
	for( q=0; q<4; q++){
		for( r=0; r<4; r++){
			if( g盤面状態マップ[q][r][_KOMA_TYPE] == 0 ){
				return 0 ;
			}
		}
	}
	return 1 ;
}

void クアルト判定処理(void){
	if( gクアルト状態 != 0 ){
		music_stop() ;
		ライフ初期化() ;
		メッセージ初期化() ;
		タイマー表示初期化() ;

		oam_clear() ;
		//delay(40) ;
		背景フラッシュ(8) ;
		delay(40) ;
		music_play(0) ;

		//バー初期化();
		//メッセージ表示(2) ;

		g一時値1 = rand8() ;
		g一時値2 = rand8() ;
		g一時値3 = rand8() ;
		g一時値4 = rand8() ;
		while(1){
			//g座標X-=4 ;
			gスプライトID = 0 ;
			//gスプライトID = oam_meta_spr( g座標X + g一時値1, 20, gスプライトID, kメタクアルト) ;
			//gスプライトID = oam_meta_spr( g座標X + g一時値2, 40, gスプライトID, kメタクアルト) ;
			//gスプライトID = oam_meta_spr( g座標X + g一時値3, 180, gスプライトID, kメタクアルト) ;
			//gスプライトID = oam_meta_spr( g座標X + g一時値3, 200, gスプライトID, kメタクアルト) ;
			//gスプライトID = oam_meta_spr( g座標X + g一時値2, 100, gスプライトID, g現在手番!=0?kメタ先手勝利:kメタ後手勝利) ;
			//gスプライトID = oam_meta_spr( g座標X + g一時値4, 140, gスプライトID, g現在手番!=0?kメタ先手勝利:kメタ後手勝利) ;
			for( gループI = 0; gループI < 4; gループI++ ){
				gループK = (gクアルトライン[gループI][0]*32)-(gクアルトライン[gループI][1]*32)+115+14 ;
				gループL = (gクアルトライン[gループI][1]*16)+(gクアルトライン[gループI][0]*16)+101-32 ;
				gスプライトID = oam_meta_spr( gループK, gループL+gフレームカウンタ%5, gスプライトID, kメタ位置2) ;
			}

			if( gフレームカウンタ & 2 ){
				gスプライトID = oam_meta_spr( g現在手番!=0?10:190 ,80, gスプライトID, g現在手番!=0?kメタ先手勝利:kメタ後手勝利);
			}else{ 
				oam_hide_rest(gスプライトID) ; 
			}

			スプライト色サイクル() ;
			//delay(2);

			駒回転アニメ(4) ;
			gフレームカウンタ++ ;

			gパッド入力=pad_poll(0);
			if( gパッド入力&PAD_START || gパッド入力&PAD_A ){
				oam_clear() ;

				for( gループI=0 ; gループI< 5; gループI++ ){
					駒回転アニメ(4) ;
					gフレームカウンタ++ ;
				}
				music_play(2) ;
				for( gループI=0 ; gループI< 10; gループI++ ){
					駒回転アニメ(2) ;
					gフレームカウンタ++ ;
				}
				for( gループI=0 ; gループI< 25; gループI++ ){
					駒回転アニメ(1) ;
					scroll(0,gループI*10) ;
					gフレームカウンタ++ ;
				}
				music_stop() ;
				駒回転停止() ;
				リセット処理() ;
			}
			continue ;
		}
	}
}
