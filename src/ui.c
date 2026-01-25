#include "lib/neslib.h"
#include "resource/jeesus.h"

#include <stdlib.h>

#include "board.h"
#include "data.h"
#include "state.h"
#include "ui.h"
#include "flow.h"

extern const unsigned char open_name[];

void デバッグ表示更新(unsigned char g座標X, unsigned char g座標Y, unsigned char arg長さ, const char *arg文字列)
{
	
	g更新デバッグバッファ[0]=MSB(NTADR_A(g座標X,g座標Y))|NT_UPD_HORZ;//set the address
	g更新デバッグバッファ[1]=LSB(NTADR_A(g座標X,g座標Y));
	g更新デバッグバッファ[2]=arg長さ;//update sequence is 4 tiles wide
	g更新デバッグバッファ[3+arg長さ]=NT_UPD_EOF;
	set_vram_update(g更新デバッグバッファ);

	for( gデバッグカウンタ = 0;gデバッグカウンタ<arg長さ;gデバッグカウンタ++)
	{
		if(!*arg文字列) break;
		g更新デバッグバッファ[3+gデバッグカウンタ]=(*arg文字列++)-0x20 ;//fill row buffer with random tiles
	}
	ppu_wait_nmi();
	set_vram_update(0);
}

void 更新初期化(void){
	g更新リスト[0]=0x20|NT_UPD_HORZ;
	g更新リスト[1]=0x00;
	g更新リスト[2]=3;
	
	g更新リスト[(6)]=0x20|NT_UPD_HORZ;
	g更新リスト[(6)+1]=0x00;
	g更新リスト[(6)+2]=5;
	
	g更新リスト[(6+8)]=0x20|NT_UPD_HORZ;
	g更新リスト[(6+8)+1]=0x00;
	g更新リスト[(6+8)+2]=5;
	
	g更新リスト[(6+8+8)]=NT_UPD_EOF;
	set_vram_update(g更新リスト);

}

void 次色サイクル(void)
{
	g背景パレット番号++ ;
	g背景パレット番号 = g背景パレット番号 > 3 ? 0 : g背景パレット番号 ;
	//デバッグ表示更新(NTADR_A(1,24), 5, itoa(g背景パレット番号, &g文字列バッファ[0], 10 ));

	pal_spr(k背景パレット配列[g背景パレット番号]);
	pal_bg(k背景パレット配列[g背景パレット番号]);
}

void 色サイクル(void)
{
	if(gフレームカウンタ%4==0){ pal_bg(kオープンパレット4);}
	if(gフレームカウンタ%4==1){ pal_bg(kオープンパレット3);}
	if(gフレームカウンタ%4==2){ pal_bg(kオープンパレット2);}
	if(gフレームカウンタ%4==3){ pal_bg(kオープンパレット1);}
}

void スプライト色サイクル(void)
{
	if(gフレームカウンタ%4==0){ pal_spr(kオープンパレット4);}
	if(gフレームカウンタ%4==1){ pal_spr(kオープンパレット3);}
	if(gフレームカウンタ%4==2){ pal_spr(kオープンパレット2);}
	if(gフレームカウンタ%4==3){ pal_spr(kオープンパレット1);}
}

unsigned char 強制終了チェック(void)
{
	gパッド入力 = pad_poll(0);
	if(gパッド入力&PAD_START || gパッド入力&PAD_SELECT || gパッド入力&PAD_A || gパッド入力&PAD_B ){
		return 1 ;
	}
	gパッド入力 = pad_poll(1);
	if(gパッド入力&PAD_START || gパッド入力&PAD_SELECT || gパッド入力&PAD_A || gパッド入力&PAD_B ){
		return 1 ;
	}
	return 0 ;
}
/*
unsigned char 駒バッファ設定(unsigned char* arg駒データ, unsigned char argカラー)
{
	for( gループI = 0; gループI < sizeof(koma_buf)/4; gループI++ ){
		memcpy( koma_buf[4*gループI], &arg駒データ[4*gループI], 3 );
		koma_buf[4*gループI+3] = argカラー ;
	}
}
*/

void 背景フラッシュ(unsigned char argアクション)
{
	pal_bright(argアクション);
	delay(6) ;
	pal_bright(4);
	delay(6) ;
	pal_bright(argアクション);
	delay(6) ;
	pal_bright(4);
}

void 背景ダウン()
{
	pal_bright(3);
	delay(6) ;
	pal_bright(2);
	delay(6) ;
	pal_bright(1);
	delay(6) ;
	pal_bright(0);
}

void 背景アップ()
{
	pal_bright(0);
	delay(10) ;
	pal_bright(1);
	delay(4) ;
	pal_bright(2);
	delay(4) ;
	pal_bright(4);
}

#ifndef debug
void 次処理へ移動(void)
{
	for( gループI = 0; gループI < 2; gループI++ ){
		g駒フレーム = 0 ;
		while(1){

			if( g駒フレーム % 10 == 0 ){ gフレームカウンタ++ ; }

			delay(1) ;
			色サイクル() ;

			if( g駒フレーム == 0 ){

				// 初回アニメ処理.
				if( g一時値1 < 10 ){ 
					delay(1) ;
					g一時値1++ ;
					continue ;
				}
				if( g一時値1 == 10 ){

					g一時値1++ ;
					delay(20) ;

					背景フラッシュ(0) ;
					背景ダウン() ;

					ppu_off() ;
					vram_adr(NAMETABLE_A);//set VRAM address
					vram_unrle((unsigned char*)open_name);
					ppu_on_all() ;

					delay(20) ;
					gスプライトID = 0 ;
					//gスプライトID = oam_meta_spr( g駒位置X[0], g駒位置Y[0], gスプライトID, k駒スプライトリスト[0][0][0] ) ;
					//gスプライトID = oam_meta_spr( g駒位置X[1], g駒位置Y[1], gスプライトID, k駒スプライトリスト[0][1][0] ) ;

					背景アップ() ;

					デバッグ表示更新(10,25, 13, "PRESS BUTTON!" );
					デバッグ表示更新(11,27, 10, "006 * 2021" );
					//delay(20) ;
					pal_bright(4);
					music_play(0);
				}
				// 駒描写
				for( gループJ = 0; gループJ < 14; gループJ++ ){
					delay(1) ;
					g駒位置Y[gループI]-- ;
					gスプライトID = 0 ;
					gスプライトID = oam_meta_spr( g駒位置X[0], g駒位置Y[0], gスプライトID, k駒スプライトリスト[0][0][0] ) ;
					gスプライトID = oam_meta_spr( g駒位置X[1], g駒位置Y[1], gスプライトID, k駒スプライトリスト[0][1][0] ) ;
					色サイクル() ;
					if( g駒フレーム % 10 == 0 ){ gフレームカウンタ++ ; }
					g駒フレーム++ ;
					if( 強制終了チェック() ){ return ; }

				}
			}

			if( 強制終了チェック() ){ return ; }
			g駒フレーム++ ;

			gスプライトID = 0 ;
			
			gスプライトID = oam_meta_spr( g駒位置X[0], g駒位置Y[0], gスプライトID, k駒スプライトリスト[0][0][0] ) ;
			gスプライトID = oam_meta_spr( g駒位置X[1], g駒位置Y[1], gスプライトID, k駒スプライトリスト[0][1][0] ) ;


			if( g駒配置スロット[gループI] == 0 ){
				if( g駒位置X[gループI] != 152 ){ g駒位置X[gループI]+=2; }
				if( g駒位置Y[gループI] != 122 ){ g駒位置Y[gループI]+=1; }
				if( g駒位置X[gループI] == 152 && g駒位置Y[gループI] == 122 ){ 
					g駒配置スロット[gループI] = 1 ;
					break ;
				}
			}
			else if( g駒配置スロット[gループI] == 1 ){
				if( g駒位置X[gループI] != 112 ){ g駒位置X[gループI]-=2; }
				if( g駒位置Y[gループI] != 144 ){ g駒位置Y[gループI]+=1; }
				if( g駒位置X[gループI] == 112 && g駒位置Y[gループI] == 144  ){
					g駒配置スロット[gループI] = 2 ;
					break ;
				}
			}
			else if( g駒配置スロット[gループI] == 2 ){
				if( g駒位置X[gループI] != 72 ){ g駒位置X[gループI]-=2; }
				if( g駒位置Y[gループI] != 122 ){ g駒位置Y[gループI]-=1; }
				if( g駒位置X[gループI] == 72 && g駒位置Y[gループI] == 122 ){
					g駒配置スロット[gループI] = 3 ;
					break ;
				}
			}
			else if( g駒配置スロット[gループI] == 3 ){
				if( g駒位置X[gループI] != 112 ){ g駒位置X[gループI]+=2; }
				if( g駒位置Y[gループI] != 96 ){ g駒位置Y[gループI]-=1; }
				if( g駒位置X[gループI] == 112 && g駒位置Y[gループI] == 96 ){
					g駒配置スロット[gループI] = 0 ;
					break ;
				}
			}
		}
	}
}
#endif



void タイマー表示初期化()
{
	デバッグ表示更新(2,25, 3, "   " );
	デバッグ表示更新(28,25,  3, "   " );
}
void タイマー表示()
{
	タイマー表示初期化() ;
	if( gタイマー設定回数 != 0 ){
		デバッグ表示更新(g現在手番!=0?2:28,25, 3, itoa(gタイマー値, &g文字列バッファ[0], 10 ) );
	}
}

/*
void 盤面外描画()
{
	for( gループK = 1; gループK < 4; gループK++ ){
		for( gループL = 1; gループL < 4; gループL++ ){
			if( g盤面状態マップ[gループK][gループL][_KOMA_TYPE] != 0 ){
				g選択駒番号 = g盤面状態マップ[gループK][gループL][_CHOOSE_KOMA] ;
				g駒色選択 = g盤面状態マップ[gループK][gループL][_SEL_BW] ;
				g座標X = (gループK*32)-(gループL*32)+115+16 ;
				g座標Y = (gループL*16)+(gループK*16)+71-16 ;
				駒配置( g座標X/8, g座標Y/8, g駒色選択==0?0xAA:0x55, (unsigned char*)k駒スプライトリスト[0][0][g選択駒番号] ) ;
			}
		}
	}
}
*/

void 駒回転停止()
{
	bank_bg(0);
	pal_bg(k背景パレット配列[g背景パレット番号]);
	pal_spr(k背景パレット配列[g背景パレット番号]);

}

void 駒回転アニメ(unsigned char argスピード)
{
//	checking = 1 ;
//	pal_bg(k背景パレット代替[0]);
//	盤面外描画();

//	for( gループI = 0; gループI < 5; gループI++){
	
	if( gフレームカウンタ % 4 == 0 ){
		bank_bg(0);
		pal_bg(k背景パレット代替[0]);
	}
	if( gフレームカウンタ % 4 == 1 ){
		bank_bg(1);
		pal_bg(k背景パレット代替[1]);
		//delay(1) ;
	}
	if( gフレームカウンタ % 4 == 2 ){
		pal_bg(k背景パレット代替[2]);
		//delay(2) ;
	}
	if( gフレームカウンタ % 4 == 3 ){
		pal_bg(k背景パレット代替[3]);
		//delay(1) ;
	}
	delay(argスピード) ;

//	checking = 0 ;
//	盤面外描画() ;

}

void メッセージ初期化()
{
	//バー初期化() ;
	//タイマー表示初期化() ;
	デバッグ表示更新(1,28, 14, k空白メッセージ );
	デバッグ表示更新(17,28, 14, k空白メッセージ );
}

void メッセージ表示(unsigned char argアクション)
{
	バー自動描画();

	//メッセージ初期化() ;
	if( argアクション == 0 ){
//		デバッグ表示更新(1,28, 14, g現在手番!=0?"P1:SELECT NEXT":"" );
//		デバッグ表示更新(17,28, 14, g対CPUフラグ == 1 && g現在手番==0 && gフレームカウンタ&4? "P2:SELECT NEXT":"" );
		デバッグ表示更新(1,28, 14, g現在手番!=0?"P1:SELECT NEXT":"P1:           " );
		デバッグ表示更新(17,28, 14, g現在手番==0 ? "P2:SELECT NEXT":"P2:           " );

	}else if( argアクション == 1 ){
//		デバッグ表示更新(1,28, 14, g現在手番!=0?"P1:PLAYING    ":"" );
//		デバッグ表示更新(17,28, 14, g対CPUフラグ == 1 && g現在手番==0 && gフレームカウンタ&4?"P2:PLAYING    ":"" );
		デバッグ表示更新(1,28, 14, g現在手番!=0?"P1:THINKING   ":"P1:           " );
		デバッグ表示更新(17,28, 14, g現在手番==0 ?"P2:THINKING   ":"P2:           " );
		タイマー表示() ;
	}
/*
	else if( argアクション == 2 ){
		デバッグ表示更新(1,24, 14, g現在手番!=0?"P1:WIN!       ":k空白メッセージ );
		デバッグ表示更新(1,5, 14, g現在手番==0?"P2:WIN!       ":k空白メッセージ );
	}
*/

}

void ライフ初期化()
{
	デバッグ表示更新(1,27, 3, "   " );
	デバッグ表示更新(17,27, 3,  "   " );
}

void ライフ表示()
{
	デバッグ表示更新(1,27, 3, gエラーフラグ[1] == 0 ? "   ": gエラーフラグ[1] == 1 ?"X  ": gエラーフラグ[1] == 2 ?"XX ": "XXX" );
	デバッグ表示更新(17,27, 3, gエラーフラグ[0] == 0 ? "   ": gエラーフラグ[0] == 1 ?"X  ": gエラーフラグ[0] == 2 ?"XX ": "XXX" );
}

void 敗北アニメ()
{
	oam_clear() ;
	ppu_off() ;
	delay(60) ;

	bank_bg(1);
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_unrle((unsigned char*)jeesus);
	pal_bg(kジーザスパレット);
	ppu_on_all();//enable rendering

	music_play(4) ;
	//sfx_play(3,0);
	delay(180);
	music_stop() ;
	bank_bg(0);

	リセット処理() ;

}

void クアルト宣言処理(){
	oam_clear() ;
	メッセージ初期化() ;
	ライフ初期化() ;
	タイマー表示初期化() ;
	
	music_play(2) ;

//	g一時値1 = rand8() ;
//	g一時値2 = rand8() ;
//	g一時値3 = rand8() ;
//	g一時値4 = rand8() ;
	for( gループI=0 ; gループI< 20; gループI++ ){
		駒回転アニメ(2) ;

		g座標X-=4 ;
		gスプライトID = 0 ;
		gスプライトID = oam_meta_spr( g座標X + 120, 80, gスプライトID, kメタクアルト) ;
//		gスプライトID = oam_meta_spr( g座標X + 60,140, gスプライトID, kメタクアルト) ;
//		gスプライトID = oam_meta_spr( g座標X + 90, 160, gスプライトID, kメタクアルト) ;
//		gスプライトID = oam_meta_spr( g座標X + 0, 100, gスプライトID, kメタクアルト) ;
//		gスプライトID = oam_meta_spr( g座標X + 30, 120, gスプライトID, kメタクアルト) ;
		スプライト色サイクル() ;
		gフレームカウンタ++ ;
	}
	oam_clear() ;
	駒回転停止() ;
	delay(20) ;
	music_stop() ;
}

void タイマー設定()
{
	if( gフレームカウンタ % 50 == 0 && g自動選択フラグ!=1 && gタイマー設定回数 != 0 ){
		gタイマー値--;
		タイマー表示() ;
		if( gタイマー値 == 0 ){
			g自動選択フラグ=1;
			sfx_play(3,0);
			//gエラーフラグ[g現在手番==0?1:0]++ ;
			//ライフ表示() ;
			gタイマー値 = gタイマー設定回数 ;
		}
		gフレームカウンタ=0 ;
	}
}

void 敵駒点滅(unsigned char argアクション)
{
	if( argアクション == 0 ){
		oam_clear() ;
	}else{
		if( g手番退避 == 1 ){ return ; }
		oam_meta_spr( g手番退避!=0?24:198, 70, 0, (unsigned char*)k駒スプライトリスト[0][g駒色退避==0?1:0][g選択駒退避] ) ;
	}
}
