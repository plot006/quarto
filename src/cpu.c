#include "lib/neslib.h"

#include "board.h"
#include "cpu.h"
#include "data.h"
#include "defs.h"
#include "state.h"
#include "ui.h"

void 乱数ボックス初期化(void)
{
	memfill( g乱数ボックス1, 9, 4 );
	memfill( g乱数ボックス2, 9, 4 );
	memfill( g乱数ボックス3, 9, 2 );
	memfill( g乱数ボックス4, 9, 8 );

	for( gループI=0; gループI < 4;){
		g一時値1 = (rand8()+gフレームカウンタ)%4 ;
		if( g乱数ボックス1[g一時値1] == gループI || g乱数ボックス1[g一時値1] != 9 ){
			gフレームカウンタ += kオープンパレット1[g一時値1] ;
			continue ;
		}
		g乱数ボックス1[g一時値1] = gループI ;
		gループI++ ;
	}
	for( gループI=0; gループI < 4;){
		g一時値1 = (rand8()+gフレームカウンタ)%4 ;
		if( g乱数ボックス2[g一時値1] == gループI || g乱数ボックス2[g一時値1] != 9 ){
			gフレームカウンタ += kオープンパレット1[g一時値1] ;
			continue ;
		}
		g乱数ボックス2[g一時値1] = gループI ;
		gループI++ ;
	}

	for( gループI=0; gループI < 2;){
		g一時値1 = (rand8()+gフレームカウンタ)%2 ;
		if( g乱数ボックス3[g一時値1] == gループI || g乱数ボックス3[g一時値1] != 9 ){
			gフレームカウンタ += kオープンパレット1[g一時値1] ;
			continue ;
		}
		g乱数ボックス3[g一時値1] = gループI ;
		gループI++ ;
	}
	for( gループI=0; gループI < 8;){
		g一時値1 = (rand8()+gフレームカウンタ)%8 ;
		if( g乱数ボックス4[g一時値1] == gループI || g乱数ボックス4[g一時値1] != 9 ){
			gフレームカウンタ += kオープンパレット1[g一時値1] ;
			continue ;
		}
		g乱数ボックス4[g一時値1] = gループI ;
		gループI++ ;
	}

}

unsigned char 敗北チェック(void)
{
	for( gループK = 0; gループK < 4; gループK++ ){
		for( gループL = 0; gループL < 4; gループL++ ){
			if( g盤面状態マップ[gループK][gループL][_KOMA_TYPE] == 0 ){
				if( g対CPUフラグ == 1 && g現在手番==0 ){
					if( gフレームカウンタ&2 ){
						//pal_spr_bright(0);
						敵駒点滅(0) ;
					}else{
						//pal_spr_bright(4);
						敵駒点滅(1) ;
					}
				}
				gフレームカウンタ++ ;
				if( 事前クアルト確認( gループK, gループL ) == 1 ){
					//pal_spr_bright(4);
					敵駒点滅(1) ;
					return 1 ;
				}
			}
		}
	}
	//pal_spr_bright(4);
	敵駒点滅(1) ;
	return 0 ;
}

unsigned char 自動選択処理( unsigned char argチェックOnly )
{
	unsigned char q = 0 ;
	unsigned char r = 0 ;
	g文字列バッファ[0] = g駒色選択;
	g文字列バッファ[1] = g選択駒番号;

	for( q=0; q<2; q++){
		for( r=0; r<8; r++){
			if( g駒存在配列[g乱数ボックス3[q]][g乱数ボックス4[r]] == 1 ){

				g駒色選択 = g乱数ボックス3[q];
				g選択駒番号 = g乱数ボックス4[r];

				//カーソル描画() ;
				//sfx_play(3,1) ;
				
				if( g対CPUフラグ == 1 && gリーチ状態 == 1 && g現在手番 == 0 && 敗北チェック() == 1){
					continue ;
				}
				//デバッグ表示更新(1,10, 1, itoa(g駒色選択, &g文字列バッファ[0], 10 ));
				//デバッグ表示更新(4,10, 1, itoa(g選択駒番号, &g文字列バッファ[0], 10 ));

				if( argチェックOnly == 1 ){
					g駒色選択 = g文字列バッファ[0] ;
					g選択駒番号 = g文字列バッファ[1];
				}
				return 0;
			}
		}
	}
	if( argチェックOnly == 1 ){
		g駒色選択 = g文字列バッファ[0] ;
		g選択駒番号 = g文字列バッファ[1];
	}
	return 1 ;
}

void 座標自動設定(void)
{
	unsigned char k2 ;
	unsigned char l2 ;
	unsigned char lastX ;
	unsigned char lastY ;
	gループM = 0 ;
	gループN = 0 ;
	gデバッグカウンタ = 0 ;
	for( k2=0; k2<4; k2++){
		gループO = g乱数ボックス1[k2] ;
		for( l2=0; l2<4; l2++){
			if( gフレームカウンタ&2 ){
				敵駒点滅(0) ;
				//pal_spr_bright(0);
			}else{
				敵駒点滅(1) ;
				//pal_spr_bright(4);
			}
			gフレームカウンタ++ ;

			gループP = g乱数ボックス2[l2] ;

			g座標X = (gループO*32)-(gループP*32)+115+16 ;
			g座標Y = (gループP*16)+(gループO*16)+101-16 ;
			
			// 仮保存(全クアルトチェック後に返す奴).
			//デバッグ表示更新(1,10, 1, itoa(g座標X, &g文字列バッファ[0], 10 ));
			//デバッグ表示更新(4,10, 1, itoa(g座標Y, &g文字列バッファ[0], 10 ));
			if( 配置判定(g座標X/8, g座標Y/8) == 1 ){
				continue ;
			}
			lastX = g座標X ;
			lastY = g座標Y ;

			if( g対CPUフラグ == 1 && g現在手番==0 && 事前クアルト確認(gループO, gループP) == 1 ){
				//pal_spr_bright(4);
				敵駒点滅(1) ;
				return ;
//				continue ; 
			}

			// 次渡して負ける場所かのチェック
			盤面仮設定(gループO,gループP) ;
			if( g対CPUフラグ == 1 && g現在手番==0 && 自動選択処理(1) == 1 ){
				盤面仮解除(gループO,gループP) ;
				continue ;
			}
			盤面仮解除(gループO,gループP) ;
			gデバッグカウンタ = 1 ;

			gループM = g座標X ;
			gループN = g座標Y ;

			//break ;
			continue ;

			//return ;
		}
		//if( gデバッグカウンタ == 1 ){break ;}
	}
	// 仮保存の座標を戻す.
	if( gループM == 0 && gループN == 0 ){
		g座標X = lastX ;
		g座標Y = lastY ;
	}else{
		g座標X = gループM ;
		g座標Y = gループN ;
	}
	配置判定(g座標X/8, g座標Y/8) ;
	//pal_spr_bright(4);
	敵駒点滅(1) ;
}
