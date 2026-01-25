//this example shows metasprite use, two pads polling,
//and simple collision detection that changes palette

#include "lib/neslib.h"
#include "resource/test2_blank.h"
#include "resource/open_name.h"
#include "resource/qr.h"
#include "resource/menu.h"
#include "resource/jeesus.h"

#include <stdlib.h>

#include "quarto_data.h"
#include "quarto_state.h"

//#define debug
#ifdef debug
#endif

void リセット処理(void) ;

#define _KOMA_TYPE		0
#define _CHOOSE_KOMA	1
#define _SEL_BW			2

#define stage_y_offset 0x80

void 乱数ボックス初期化()
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

/*
void 盤面プリアニメ(unsigned char g座標X, unsigned char g座標Y, unsigned char argアクション)
{
	gスプライトID = 0 ;
	for( g一時値1 = 0; g一時値1 < 32 ; g一時値1++ ){
		oam_meta_spr( (g座標X*32)-(g座標Y*32)+115-g一時値1, (g座標Y*16)+(g座標X*16)+71, gスプライトID, kメタマスクロング ) ;
		if( argアクション == 0 ){ return ; }
		//ppu_wait_frame();	// wait for next TV gフレームカウンタ

		//if( g一時値1 % 16 == 0 ){ delay(1) ; }
	}
	oam_clear() ;
}
*/
void 上方向処理(unsigned char g座標X, unsigned char g座標Y )
{
	for( gループI = 0; gループI < 5; gループI++ ){
		if( gアニメ格子[g座標X][g座標Y] == 0 ){
			//盤面プリアニメ(g座標X,g座標Y,0) ;
			if( gループI != 0 && gループI != 4 ){
				g更新リスト[gループI+3-1] = 0 ; 
			}
			g更新リスト[gループI+(6)+3] = (unsigned char)(0xE5+gループI) ;
			g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xF5+gループI) ;
		}else if( gアニメ格子[g座標X][g座標Y] == 1 ){
			if( gループI != 0 && gループI != 4 ){
				g更新リスト[gループI+3-1] = 0 ; 
			}
			g更新リスト[gループI+(6)+3] = (unsigned char)(0xE5+gループI) ;
			g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xF5+gループI) ;
		}else if( gアニメ格子[g座標X][g座標Y] == 2 ){
			if( gループI != 0 && gループI != 4 ){
				g更新リスト[gループI+3-1] = 0 ; 
			}
			g更新リスト[gループI+(6)+3] = (unsigned char)(0xE0+gループI) ;
			g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xF0+gループI) ;
		}else if( gアニメ格子[g座標X][g座標Y] == 3 ){
			if( gループI != 0 && gループI != 4 ){
				g更新リスト[gループI+3-1] = (unsigned char)(0xC5+gループI) ;
			}
			if( gループI == 0 || gループI == 4 ){
				g更新リスト[gループI+(6)+3] = (unsigned char)(0xC5+gループI) ;
			}
			g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xD5+gループI) ;
		}else if( gアニメ格子[g座標X][g座標Y] == 4 ){
			if( gループI != 0 && gループI != 4 ){
				g更新リスト[gループI+3-1] = (unsigned char)(0xC0+gループI) ;
			}
			if( gループI == 0 || gループI == 4 ){
				g更新リスト[gループI+(6)+3] = (unsigned char)(0xC0+gループI) ;
			}
			g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xD0+gループI) ;
		}else{
			return ;
		}
	}
	delay(1) ;
}
void 盤面アドレス設定(unsigned char g座標X, unsigned char g座標Y )
{
	unsigned char calcAdr = 0x00 ;
	calcAdr = k盤面座標テーブル[g座標X][g座標Y][1]+1+stage_y_offset > 0xFF ? k盤面座標テーブル[g座標X][g座標Y][0]+1 : k盤面座標テーブル[g座標X][g座標Y][0];
	g更新リスト[0]=(0x20+calcAdr)&0xFF|NT_UPD_HORZ;//horizontal update sequence, dummy address
	g更新リスト[1]=k盤面座標テーブル[g座標X][g座標Y][1]+1+stage_y_offset;

	calcAdr = k盤面座標テーブル[g座標X][g座標Y][3]+stage_y_offset > 0xFF ? k盤面座標テーブル[g座標X][g座標Y][2]+1 : k盤面座標テーブル[g座標X][g座標Y][2];
	g更新リスト[(6)]=(0x20+calcAdr)&0xFF|NT_UPD_HORZ;//horizontal update sequence, dummy address
	g更新リスト[(6)+1]=k盤面座標テーブル[g座標X][g座標Y][3]+stage_y_offset;

	calcAdr = k盤面座標テーブル[g座標X][g座標Y][5]+stage_y_offset > 0xFF ? k盤面座標テーブル[g座標X][g座標Y][4]+1 : k盤面座標テーブル[g座標X][g座標Y][4];
	g更新リスト[(6+8)]=(0x20+calcAdr)&0xFF|NT_UPD_HORZ;//horizontal update sequence, dummy address
	g更新リスト[(6+8)+1]=k盤面座標テーブル[g座標X][g座標Y][5]+stage_y_offset;
}
void 盤面上昇(unsigned char g座標X, unsigned char g座標Y )
{
	盤面アドレス設定(g座標X,g座標Y);
/*
	g更新リスト[0]=0x20+k盤面座標テーブル[g座標X][g座標Y][0]|NT_UPD_HORZ;//horizontal update sequence, dummy address
	g更新リスト[1]=k盤面座標テーブル[g座標X][g座標Y][1]+1;
	g更新リスト[(6)]=0x20+k盤面座標テーブル[g座標X][g座標Y][2]|NT_UPD_HORZ;//horizontal update sequence, dummy address
	g更新リスト[(6)+1]=k盤面座標テーブル[g座標X][g座標Y][3];
	g更新リスト[(6+8)]=0x20+k盤面座標テーブル[g座標X][g座標Y][4]|NT_UPD_HORZ;//horizontal update sequence, dummy address
	g更新リスト[(6+8)+1]=k盤面座標テーブル[g座標X][g座標Y][5];
*/
	sfx_play(5,0);

	for( gアニメ格子[g座標X][g座標Y] = 0 ; gアニメ格子[g座標X][g座標Y] < 5; gアニメ格子[g座標X][g座標Y]++ ){
/*
		for( gループI = 0; gループI < 5; gループI++ ){
			if( gアニメ格子[g座標X][g座標Y] == 0 ){
				//盤面プリアニメ(g座標X,g座標Y,0) ;
				if( gループI != 0 && gループI != 4 ){
					g更新リスト[gループI+3-1] = 0 ; 
				}
				g更新リスト[gループI+(6)+3] = (unsigned char)(0xE5+gループI) ;
				g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xF5+gループI) ;
			}else if( gアニメ格子[g座標X][g座標Y] == 1 ){
				if( gループI != 0 && gループI != 4 ){
					g更新リスト[gループI+3-1] = 0 ; 
				}
				g更新リスト[gループI+(6)+3] = (unsigned char)(0xE5+gループI) ;
				g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xF5+gループI) ;
			}else if( gアニメ格子[g座標X][g座標Y] == 2 ){
				if( gループI != 0 && gループI != 4 ){
					g更新リスト[gループI+3-1] = 0 ; 
				}
				g更新リスト[gループI+(6)+3] = (unsigned char)(0xE0+gループI) ;
				g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xF0+gループI) ;
			}else if( gアニメ格子[g座標X][g座標Y] == 3 ){
				if( gループI != 0 && gループI != 4 ){
					g更新リスト[gループI+3-1] = (unsigned char)(0xC5+gループI) ;
				}
				if( gループI == 0 || gループI == 4 ){
					g更新リスト[gループI+(6)+3] = (unsigned char)(0xC5+gループI) ;
				}
				g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xD5+gループI) ;
			}else if( gアニメ格子[g座標X][g座標Y] == 4 ){
				if( gループI != 0 && gループI != 4 ){
					g更新リスト[gループI+3-1] = (unsigned char)(0xC0+gループI) ;
				}
				if( gループI == 0 || gループI == 4 ){
					g更新リスト[gループI+(6)+3] = (unsigned char)(0xC0+gループI) ;
				}
				g更新リスト[gループI+(6+8)+3] = (unsigned char)(0xD0+gループI) ;
			}else{
				return ;
			}
		}
		delay(1) ;
		*/
		上方向処理(g座標X,g座標Y) ;
	}
}
/*
void 盤面下降(unsigned char g座標X, unsigned char g座標Y )
{
	盤面アドレス設定(g座標X,g座標Y);
	sfx_play(1,0);

	for( gアニメ格子[g座標X][g座標Y] = 4 ; gアニメ格子[g座標X][g座標Y] >= 0; gアニメ格子[g座標X][g座標Y]-- ){
		上方向処理(g座標X,g座標Y) ;
	}
}
*/
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
#define posy_offset 4
void 盤面座標取得(unsigned char arg位置X, unsigned char arg位置Y)
{
	//位置補正.
	gループJ = 0 ;
	if(arg位置X >= 2 && arg位置X <= 5){
		if( arg位置Y >= 10+posy_offset && arg位置Y <= 12+posy_offset ){ arg位置X = 3 ;arg位置Y = 12+posy_offset ; gループJ++; g座標インデックスX=0 ; g座標インデックスY=3 ;}
	}	
	if(arg位置X >= 6 && arg位置X <= 9){
		if( arg位置Y >= 8+posy_offset && arg位置Y <= 10+posy_offset ){ arg位置X = 7 ;arg位置Y = 10+posy_offset ; gループJ++; g座標インデックスX=0 ; g座標インデックスY=2 ;}
		if( arg位置Y >= 12+posy_offset && arg位置Y <= 14+posy_offset ){ arg位置X = 7 ;arg位置Y = 14+posy_offset ; gループJ++; g座標インデックスX=1 ; g座標インデックスY=3 ;}
	}	
	if(arg位置X >= 10 && arg位置X <= 13){
		if( arg位置Y >= 6+posy_offset && arg位置Y <= 8+posy_offset ){ arg位置X = 11 ;arg位置Y = 8+posy_offset ; gループJ++; g座標インデックスX=0 ; g座標インデックスY=1 ;}
		if( arg位置Y >= 10+posy_offset && arg位置Y <= 12+posy_offset ){ arg位置X = 11 ;arg位置Y = 12+posy_offset ; gループJ++; g座標インデックスX=1 ; g座標インデックスY=2 ;}
		if( arg位置Y >= 14+posy_offset && arg位置Y <= 16+posy_offset ){ arg位置X = 11 ;arg位置Y = 16+posy_offset ; gループJ++; g座標インデックスX=2 ; g座標インデックスY=3 ;}
	}
	if(arg位置X >= 14 && arg位置X <= 17){
		if( arg位置Y >= 4+posy_offset && arg位置Y <= 7+posy_offset ){ arg位置X = 15 ;arg位置Y = 6+posy_offset ; gループJ++; g座標インデックスX=0 ; g座標インデックスY=0 ; }
		if( arg位置Y >= 8+posy_offset && arg位置Y <= 10+posy_offset ){ arg位置X = 15 ;arg位置Y = 10+posy_offset ; gループJ++; g座標インデックスX=1 ; g座標インデックスY=1 ;}
		if( arg位置Y >= 12+posy_offset && arg位置Y <= 14+posy_offset ){ arg位置X = 15 ;arg位置Y = 14+posy_offset ; gループJ++; g座標インデックスX=2 ; g座標インデックスY=2 ;}
		if( arg位置Y >= 16+posy_offset && arg位置Y <= 18+posy_offset ){ arg位置X = 15 ;arg位置Y = 18+posy_offset ; gループJ++; g座標インデックスX=3 ; g座標インデックスY=3 ;}
	}
	if(arg位置X >= 18 && arg位置X <= 21){
		if( arg位置Y >= 6+posy_offset && arg位置Y <= 8+posy_offset ){ arg位置X = 19 ;arg位置Y = 8+posy_offset ; gループJ++; g座標インデックスX=1 ; g座標インデックスY=0 ;}
		if( arg位置Y >= 10+posy_offset && arg位置Y <= 12+posy_offset ){ arg位置X = 19 ;arg位置Y = 12+posy_offset ; gループJ++; g座標インデックスX=2 ; g座標インデックスY=1 ;}
		if( arg位置Y >= 14+posy_offset && arg位置Y <= 16+posy_offset ){ arg位置X = 19 ;arg位置Y = 16+posy_offset ; gループJ++; g座標インデックスX=3 ; g座標インデックスY=2 ;}
	}
	if(arg位置X >= 22 && arg位置X <= 25){
		if( arg位置Y >= 8+posy_offset && arg位置Y <= 10+posy_offset ){ arg位置X = 23 ;arg位置Y = 10+posy_offset ; gループJ++; g座標インデックスX=2 ; g座標インデックスY=0 ;}
		if( arg位置Y >= 12+posy_offset && arg位置Y <= 14+posy_offset ){ arg位置X = 23 ;arg位置Y = 14+posy_offset ; gループJ++; g座標インデックスX=3 ; g座標インデックスY=1 ;}
	}
	if(arg位置X >= 26 && arg位置X <= 29){
		if( arg位置Y >= 10+posy_offset && arg位置Y <= 12+posy_offset ){ arg位置X = 27 ;arg位置Y = 12+posy_offset ; gループJ++;g座標インデックスX=3 ; g座標インデックスY=0 ;}
	}
	
	if( arg位置Y < 8 ){
		g設定アドレス上位 = 0x20 ;
		g設定アドレス下位 = 0x00 + (0x20*arg位置Y) + arg位置X ;
	}else{
		g設定アドレス上位 = 0x20 + arg位置Y / 8 ;
		g設定アドレス下位 = 0x00 + (0x20*(arg位置Y%8)) + arg位置X ;
	}
	g設定座標X = arg位置X ;
	g設定座標Y = arg位置Y ;
	
}
void 属性共有(unsigned char argアクション)
{
	if( argアクション == 0 ){
		g属性更新バッファ[3][2] = g属性状態配列[3] ;
		g属性更新バッファ[4][2] = g属性状態配列[4] ;
	}else{
		g属性状態配列[3] = g属性更新バッファ[3][2] ;
		g属性状態配列[4] = g属性更新バッファ[4][2] ;
	}
}

void 属性座標取得(unsigned char arg位置X, unsigned char arg位置Y)
{
	g設定アドレス上位 = 0x23 ;
	g設定アドレス下位 = 0xC0 + (0x08*(arg位置Y/4)) + arg位置X/4 ;
}


#define attr_pos_offset 0x08
void 盤面駒色設定(unsigned char argカラー)
{
	//getStageAttrPos() ;
	g更新駒カラー[0]=0x23|NT_UPD_HORZ;
	g更新駒カラー[1]=0x00;
	g更新駒カラー[2]=1;
	g更新駒カラー[4]=NT_UPD_EOF;
	set_vram_update(g更新駒カラー);

	for( gループI=0; gループI < 4; gループI++ ){
		g更新駒カラー[0]=0x23|NT_UPD_HORZ;
		g更新駒カラー[1]=k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]+attr_pos_offset;
		if( (g座標インデックスX - g座標インデックスY) % 2 == 0 ){
			if( gループI == 0 ){ g一時値1 = g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] ; g一時値2 = argカラー==0x55?0b01000000:0b10000000 ; g一時値3 = 0b00111111 ;}
			if( gループI == 1 ){ g一時値1 = g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] ; g一時値2 = argカラー==0x55?0b00010000:0b00100000 ; g一時値3 = 0b11001111 ;}
			if( gループI == 2 ){ g一時値1 = g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] ; g一時値2 = argカラー==0x55?0b00000100:0b00001000 ; g一時値3 = 0b11110011 ;}
			if( gループI == 3 ){ g一時値1 = g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] ; g一時値2 = argカラー==0x55?0b00000001:0b00000010 ; g一時値3 = 0b11111100 ;}
			if( argカラー==0x00 ){ g一時値2 = 0x00 ;}
			g一時値1 = g一時値1 & g一時値3;
			g一時値1 = g一時値1 | g一時値2;
			g更新駒カラー[3] = g一時値1 ;

			g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] = g一時値1 ;
		}else{
			if( gループI == 0 ){ g一時値1 = g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] ; g一時値2 = argカラー==0x55?0b00000100:0b00001000 ; g一時値3 = 0b11110011 ;}
			if( gループI == 1 ){ g一時値1 = g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] ; g一時値2 = argカラー==0x55?0b00000001:0b00000010 ; g一時値3 = 0b11111100 ;}
			if( gループI == 2 ){ g一時値1 = g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] ; g一時値2 = argカラー==0x55?0b01000000:0b10000000 ; g一時値3 = 0b00111111 ;}
			if( gループI == 3 ){ g一時値1 = g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] ; g一時値2 = argカラー==0x55?0b00010000:0b00100000 ; g一時値3 = 0b11001111 ;}
			if( argカラー==0x00 ){ g一時値2 = 0x00 ;}
			g一時値1 = g一時値1 & g一時値3;
			g一時値1 = g一時値1 | g一時値2;
			g更新駒カラー[3] = g一時値1 ;

			g属性状態配列[k属性座標テーブル[g座標インデックスX][g座標インデックスY][gループI]-0xC8] = g一時値1 ;
		}
		属性共有(0) ;
		ppu_wait_nmi();
	}
}
void 駒色設定(unsigned char arg位置X, unsigned char arg位置Y, unsigned char argカラー )
{
	// 上ブロック下段.
	属性座標取得(arg位置X, arg位置Y) ;
	g更新駒カラー[0]=g設定アドレス上位|NT_UPD_HORZ;
	g更新駒カラー[1]=g設定アドレス下位;
	g更新駒カラー[2]=1;
	g更新駒カラー[4]=NT_UPD_EOF;
	set_vram_update(g更新駒カラー);

	g一時値1 = g属性更新バッファ[arg位置X/4][(arg位置Y-2)/4] & 0b00001111 ;
	g一時値2 = argカラー&0b11110000 ;
	g一時値1 = g一時値1 | g一時値2 ;
	g属性更新バッファ[arg位置X/4][(arg位置Y-2)/4] = g一時値1 ;

	g更新駒カラー[3] = g一時値1 ;

	ppu_wait_nmi();
/*
	ppu_off() ;
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_read( &g一時値1, 1 ) ;
	ppu_on_all() ;
*/
	// 下ブロック上段.
	属性座標取得(arg位置X, arg位置Y+2) ;
	g更新駒カラー[0]=g設定アドレス上位|NT_UPD_HORZ;
	g更新駒カラー[1]=g設定アドレス下位;
	g更新駒カラー[2]=1;
	g更新駒カラー[4]=NT_UPD_EOF;
	set_vram_update(g更新駒カラー);

	g一時値1 = g属性更新バッファ[arg位置X/4][((arg位置Y-2)/4)+1] & 0b11110000 ;
	g一時値2 =  argカラー&0b00001111 ;
	g一時値1 = g一時値1 | g一時値2 ;
	g属性更新バッファ[arg位置X/4][((arg位置Y-2)/4)+1] = g一時値1 ;

	g更新駒カラー[3] = g一時値1 ;
	ppu_wait_nmi();

	属性共有(1) ;
}
unsigned char 配置判定(unsigned char arg位置X, unsigned char arg位置Y)
{
	盤面座標取得(arg位置X, arg位置Y) ;
	if( gループJ == 0 ){
		return 1;
	}
	if( g盤面状態マップ[g座標インデックスX][g座標インデックスY][_KOMA_TYPE] != 0 ){
		return 1 ;
	}
	return 0 ;
}
void ストック駒配置(unsigned char arg位置X, unsigned char arg位置Y, unsigned char argカラー, unsigned char* argメタデータ)
{
	盤面座標取得(arg位置X, arg位置Y) ;
	g更新駒データ[0]=g設定アドレス上位|NT_UPD_VERT;
	g更新駒データ[1]=g設定アドレス下位;
	g更新駒データ[2]=4;
	g更新駒データ[7]=g設定アドレス上位|NT_UPD_VERT;
	g更新駒データ[8]=g設定アドレス下位+1;
	g更新駒データ[9]=4;
	g更新駒データ[14]=g設定アドレス上位|NT_UPD_VERT;
	g更新駒データ[15]=g設定アドレス下位+2;
	g更新駒データ[16]=4;
	g更新駒データ[(3+4)*3]=NT_UPD_EOF;
	set_vram_update(g更新駒データ);

	for( gループI=0; gループI<3; gループI++ ){
		for( gループJ=0; gループJ<4; gループJ++ ){
			g更新駒データ[7*gループI+gループJ+3] = argメタデータ[4*(4*gループI+gループJ)+2] ;
		}
	}
	ppu_wait_nmi();
	駒色設定( arg位置X, arg位置Y, argカラー) ;
}

void バー描画(unsigned int argアドレス, unsigned char argアクション )
{
	g更新デバッグバッファ[0]=MSB(argアドレス)|NT_UPD_HORZ;
	g更新デバッグバッファ[1]=LSB(argアドレス);
	g更新デバッグバッファ[2]=16;
	g更新デバッグバッファ[3+16]=NT_UPD_EOF;
	set_vram_update(g更新デバッグバッファ);

	memfill( &g更新デバッグバッファ[3], 0x00, 16 );
	if( argアクション == 1 ){
		for( gループI=0; gループI<16; gループI++ ){
			if( gループI == 0 ){ g更新デバッグバッファ[gループI+3] = argアクション == 1 ? 0xDD: 0xED ; }
			else if( gループI ==15 ){ g更新デバッグバッファ[gループI+3] = argアクション == 1 ? 0xDF: 0xEF ; }
			else { g更新デバッグバッファ[gループI+3] = argアクション == 1 ? 0xDE: 0xEE ; }
		}
	}
	ppu_wait_nmi();
}

/*
void バー初期化()
{
	バー描画( NTADR_A(0,29), 0 );
}
*/
void バー自動描画()
{
//	バー描画( NTADR_A(0,29), 0);
	バー描画( NTADR_A(g現在手番==0?0:16,29), 0);
	バー描画( NTADR_A(g現在手番==1?0:16,29), 1);
}

void 駒配置(unsigned char arg位置X, unsigned char arg位置Y, unsigned char argカラー, unsigned char* argメタデータ)
{
	盤面駒色設定( argカラー ) ;

	盤面座標取得(arg位置X, arg位置Y) ;
	g更新駒データ[0]=g設定アドレス上位|NT_UPD_VERT;
	g更新駒データ[1]=g設定アドレス下位;
	g更新駒データ[2]=4;
	g更新駒データ[7]=g設定アドレス上位|NT_UPD_VERT;
	g更新駒データ[8]=g設定アドレス下位+1;
	g更新駒データ[9]=4;
	g更新駒データ[14]=g設定アドレス上位|NT_UPD_VERT;
	g更新駒データ[15]=g設定アドレス下位+2;
	g更新駒データ[16]=4;
	g更新駒データ[(3+4)*3]=NT_UPD_EOF;
	set_vram_update(g更新駒データ);

	for( gループI=0; gループI<3; gループI++ ){
		for( gループJ=0; gループJ<4; gループJ++ ){
			g更新駒データ[7*gループI+gループJ+3] = argメタデータ[4*(4*gループI+gループJ)+2] ;

			// 頭被り補正処理.
			//if( checking != 0 ){continue ;}

			if( g座標インデックスX != 0 && g座標インデックスY != 0){
				if( gループJ == 0 ){
					if( g選択駒番号 >= 4 && g選択駒番号 <= 7 ){
						// 被りなしコマ.
						g更新駒データ[7*gループI+gループJ+3] = 0xD1+gループI ;
					}else{
						// 被りありコマ. ※左端2マスのみ再描画.
						if( gループI == 1 ){ continue ; }
						if( g選択駒番号 == 0 ){ g更新駒データ[7*gループI+gループJ+3] = gループI == 0 ? 0xAA : 0xAA+1 ;}
						if( g選択駒番号 == 1 ){ g更新駒データ[7*gループI+gループJ+3] = gループI == 0 ? 0xBA : 0xBA+1 ;}
						if( g選択駒番号 == 2 ){ g更新駒データ[7*gループI+gループJ+3] = gループI == 0 ? 0xAC : 0xAC+1 ;}
						if( g選択駒番号 == 3 ){ g更新駒データ[7*gループI+gループJ+3] = gループI == 0 ? 0xBC : 0xBC+1 ;}
					}
				}
			}
		}
	}
	ppu_wait_nmi();
}

void カーソル描画()
{
	gスプライトID = 0 ;
//	gスプライトID = oam_meta_spr( g選択駒番号*32+8, 30+(g駒色選択*170), gスプライトID, g駒色選択==0 ? kカーソルスプライト : kカーソルスプライト2  ) ;
//	gスプライトID = oam_meta_spr( g選択駒番号*32+8, g駒色選択==0? 30 : 30+170, gスプライトID, g駒色選択==0 ? kメタ位置1 : kメタ位置2  ) ;
//	gスプライトID = oam_meta_spr( g選択駒番号*32+9, g駒色選択==0? 28-gフレームカウンタ%6 : 60-gフレームカウンタ%6, gスプライトID, g駒色選択==0 ? kメタ位置1逆 : kメタ位置2逆) ;
	gスプライトID = oam_meta_spr( g選択駒番号*32+9, g駒色選択==0? 42-gフレームカウンタ%6 : 76-gフレームカウンタ%6, gスプライトID, g駒色選択==0 ? kメタ位置1逆 : kメタ位置2逆) ;
	//if( gフレームカウンタ&2 ){ oam_hide_rest(gスプライトID) ; return ; }
//	gスプライトID = oam_meta_spr( g選択駒番号*32+9, g駒色選択==0? 0-gフレームカウンタ%6 : 202+gフレームカウンタ%6, gスプライトID, g駒色選択==0 ? kメタ位置1 : kメタ位置2  ) ;

}
/*
unsigned char パッド無入力()
{
	gパッド入力 = pad_poll(0);
	if(gパッド入力==0){
		moving = 0 ;
		return 1 ;
	}
	return 0 ;
}
*/
unsigned char ラインクアルト判定()
{
	if ( g属性黒 == 4 || g属性白 == 4 || g属性高 == 4 || g属性低 == 4 || 
	g属性四角 == 4 || g属性丸 == 4 || g属性平面 == 4 || g属性穴 == 4 ) {
		return 1 ;
	}
	return 0 ;
}
void クアルトフラグ初期化()
{
	g属性黒 =0 ;
	g属性白 = 0 ;
	g属性高 = 0 ;
	g属性低 = 0 ;
	g属性四角 = 0 ;
	g属性丸 = 0 ;
	g属性平面 = 0 ;
	g属性穴 = 0 ;
}
void ビット計算(unsigned char g座標X, unsigned char g座標Y)
{
	g計算値 = g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] ; if( g計算値 & 0b10000000 ){ g属性黒++ ;}
	g計算値 = g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] ; if( g計算値 & 0b01000000 ){ g属性高++ ;}
	g計算値 = g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] ; if( g計算値 & 0b00100000 ){ g属性四角++ ;}
	g計算値 = g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] ; if( g計算値 & 0b00010000 ){ g属性平面++ ;}
	g計算値 = g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] ; if( g計算値 & 0b00001000 ){ g属性白++ ;}
	g計算値 = g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] ; if( g計算値 & 0b00000100 ){ g属性低++ ;}
	g計算値 = g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] ; if( g計算値 & 0b00000010 ){ g属性丸++ ;}
	g計算値 = g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] ; if( g計算値 & 0b00000001 ){ g属性穴++ ;}
}
unsigned char クアルト判定()
{
	for( gループI = 0; gループI < 4; gループI++ ){
		クアルトフラグ初期化() ;
		for( gループJ = 0; gループJ < 4; gループJ++ ){
			ビット計算(gループI,gループJ) ;
		}
		if( ラインクアルト判定() == 1 ){
			for( gループJ = 0; gループJ < 4; gループJ++ ){
				gクアルトライン[gループJ][0] = gループI ;
				gクアルトライン[gループJ][1] = gループJ ;
			}
			return 1 ;
		}
	}
	for( gループJ = 0; gループJ < 4; gループJ++ ){
		クアルトフラグ初期化() ;
		for( gループI = 0; gループI < 4; gループI++ ){
			ビット計算(gループI,gループJ) ;
		}
		/*
		if( gループJ == 3 ){
			デバッグ表示更新(1,11, 3, itoa(g属性黒, &g文字列バッファ[0], 10 ));
			デバッグ表示更新(4,11, 3, itoa(g属性高, &g文字列バッファ[0], 10 ));
			デバッグ表示更新(7,11, 3, itoa(g属性四角, &g文字列バッファ[0], 10 ));
			デバッグ表示更新(10,11, 3, itoa(g属性平面, &g文字列バッファ[0], 10 ));
			デバッグ表示更新(13,11, 3, itoa(g属性白, &g文字列バッファ[0], 10 ));
			デバッグ表示更新(16,11, 3, itoa(g属性低, &g文字列バッファ[0], 10 ));
			デバッグ表示更新(19,11, 3, itoa(g属性丸, &g文字列バッファ[0], 10 ));
			デバッグ表示更新(22,11, 3, itoa(g属性穴, &g文字列バッファ[0], 10 ));
		}
		*/
		if( ラインクアルト判定() == 1 ){
			for( gループI = 0; gループI < 4; gループI++ ){
				gクアルトライン[gループI][0] = gループI ;
				gクアルトライン[gループI][1] = gループJ ;
			}
			return 1 ;
		}
	}

	// クロス縦.
	クアルトフラグ初期化() ;
	for( gループI = 0; gループI < 4; gループI++ ){
		ビット計算(gループI,gループI) ;
	}
	if( ラインクアルト判定() == 1 ){
		for( gループI = 0; gループI < 4; gループI++ ){
			gクアルトライン[gループI][0] = gループI ;
			gクアルトライン[gループI][1] = gループI ;
		}
		return 1 ;
	}

	// クロス横.
	クアルトフラグ初期化() ;
	for( gループI = 0; gループI < 4; gループI++ ){
		ビット計算(gループI,3-gループI) ;
	}
	if( ラインクアルト判定() == 1 ){
		for( gループI = 0; gループI < 4; gループI++ ){
			gクアルトライン[gループI][0] = gループI ;
			gクアルトライン[gループI][1] = 3-gループI ;
		}
		return 1 ;
	}

	// ボックス(上級ルール).
	if( g上級モード == 1 ){
		for( gループI = 0; gループI < 3; gループI++ ){
			for( gループJ = 0; gループJ < 3; gループJ++ ){
				クアルトフラグ初期化() ;
				ビット計算(gループI,gループJ) ;
				ビット計算(gループI,gループJ+1) ;
				ビット計算(gループI+1,gループJ) ;
				ビット計算(gループI+1,gループJ+1) ;
				if( ラインクアルト判定() == 1 ){
					gクアルトライン[0][0] = gループI ;
					gクアルトライン[0][1] = gループJ ;
					gクアルトライン[1][0] = gループI ;
					gクアルトライン[1][1] = gループJ+1 ;
					gクアルトライン[2][0] = gループI+1 ;
					gクアルトライン[2][1] = gループJ ;
					gクアルトライン[3][0] = gループI+1 ;
					gクアルトライン[3][1] = gループJ+1 ;
					return 1 ;
				}
			}
		}
	}

	return 0 ;
}

void 駒移動演出(unsigned char arg元座標X, unsigned char arg元座標Y, unsigned char arg先座標X, unsigned char arg先座標Y, unsigned char* argメタデータ )
{
	// 2単位で増減するので、src,dstどこかが奇数となると無限ループする.
	g駒位置X[0] = arg元座標X % 2 == 0 ? arg元座標X : arg元座標X-1 ;
	g駒位置Y[0] = arg元座標Y % 2 == 0 ? arg元座標Y : arg元座標Y-1 ;
	arg先座標X = arg先座標X % 2 == 0 ? arg先座標X : arg先座標X-1 ;
	arg先座標Y = arg先座標Y % 2 == 0 ? arg先座標Y : arg先座標Y-1 ;
	
	while(1){
		g駒フレーム++ ;
		if( g駒フレーム % 5 != 0 ){ continue ; }
		//ppu_wait_nmi();
		gスプライトID = 0 ;
		gスプライトID = oam_meta_spr( g駒位置X[0], g駒位置Y[0], gスプライトID, argメタデータ ) ;

		if( g駒位置Y[0] > arg先座標Y ){ g駒位置Y[0]-=2; }
		else if( g駒位置Y[0] < arg先座標Y ){ g駒位置Y[0]+=2; }
		else if( g駒位置X[0] > arg先座標X ){ g駒位置X[0]-=2; }
		else if( g駒位置X[0] < arg先座標X ){ g駒位置X[0]+=2; }

		if( g駒位置X[0] == arg先座標X && g駒位置Y[0] == arg先座標Y ){ 
			break ;
		}

	}
	g座標X = arg先座標X ;
	g座標Y = arg先座標Y ;
	ppu_wait_frame();
}
/*
void 盤面アニメ(unsigned char argアクション)
{
	gスプライトID = 0 ;
	for( gループI = 0; gループI < 32 ; gループI++ ){
		for( g座標X = 0; g座標X < 4 ; g座標X++ ){
			for( g座標Y = 0; g座標Y < 4 ; g座標Y++ ){
				gスプライトID = oam_meta_spr( (g座標X*32)-(g座標Y*32)+117-gループI, (g座標Y*16)+(g座標X*16)+79, gスプライトID, kメタマスク ) ;
			}
		}
		if( argアクション == 0 ){
			return ;
		}
	}
}
*/
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
unsigned char 終了チェック()
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
unsigned char 敗北チェック() ;
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
void 盤面仮設定( unsigned char g座標X, unsigned char g座標Y )
{
	g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] = g駒色選択==0 ? k駒属性マスク[1+g選択駒番号] : k駒属性マスク[1+g選択駒番号+8] ;
	g盤面状態マップ[g座標X][g座標Y][_CHOOSE_KOMA] = g選択駒番号 ;
	g盤面状態マップ[g座標X][g座標Y][_SEL_BW] = g駒色選択 ;	
}
void 盤面仮解除( unsigned char g座標X, unsigned char g座標Y )
{
	g盤面状態マップ[g座標X][g座標Y][_KOMA_TYPE] = 0 ;
	g盤面状態マップ[g座標X][g座標Y][_CHOOSE_KOMA] = 0 ;
	g盤面状態マップ[g座標X][g座標Y][_SEL_BW] = 0 ;	
}
unsigned char 事前クアルト確認(unsigned char g座標X, unsigned char g座標Y )
{
	g一時値3 = 0 ;
	盤面仮設定(g座標X,g座標Y) ;
	if( クアルト判定() == 1){
		g一時値3 = 1 ;
	}else{
		g一時値3 = 0 ;
	}
	盤面仮解除(g座標X,g座標Y) ;
	return g一時値3 ;
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
unsigned char 敗北チェック(){
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
void 選択ボタンAイベント(void)
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
					return ;
				}
			}
			カーソル描画() ;
			
			選択ボタンAイベント() ;
			return ;
			
		}

		ppu_wait_nmi();	// wait for next TV gフレームカウンタ
		gフレームカウンタ++;
	}
}
unsigned char リーチ判定()
{
	for( gループK = 0; gループK < 4; gループK++ ){
		g一時値1 = 0 ; // X軸3連チェック用.
		g一時値2 = 0 ; // Y軸3連チェック用.
		for( gループL = 0; gループL < 4; gループL++ ){
			// X軸検索.
			if( g盤面状態マップ[gループK][gループL][_KOMA_TYPE] != 0 ){
				g一時値1++ ;
				if( g一時値1 >= 3 ){
					gリーチ状態 = 1 ;
				}	
			}
			// Y軸検索.
			if( g盤面状態マップ[gループL][gループK][_KOMA_TYPE] != 0 ){
				g一時値2++ ;
				if( g一時値2 >= 3 ){
					gリーチ状態 = 1 ;
				}
			}
		}
	}

	g一時値1 = 0 ;
	g一時値2 = 0 ;
	for( gループK = 0; gループK < 4; gループK++ ){
		// X軸クロス検索.
		if( g盤面状態マップ[gループK][gループK][_KOMA_TYPE] != 0 ){
			g一時値1++ ;
			if( g一時値1 >= 3 ){
				gリーチ状態 = 1 ;
			}
		}
		// Y軸クロス検索.
		if( g盤面状態マップ[gループK][3-gループK][_KOMA_TYPE] != 0 ){
			g一時値2++ ;
			if( g一時値2 >= 3 ){
				gリーチ状態 = 1 ;
			}
		}
	}

	if( g上級モード == 1 ){
		for( gループK = 0; gループK < 3; gループK++ ){
			for( gループL = 0; gループL < 3; gループL++ ){
				g一時値1 = 0 ;
				if( g盤面状態マップ[gループK][gループL][_KOMA_TYPE] != 0 ){ g一時値1++ ; }
				if( g盤面状態マップ[gループK][gループL+1][_KOMA_TYPE] != 0 ){ g一時値1++ ; }
				if( g盤面状態マップ[gループK+1][gループL][_KOMA_TYPE] != 0 ){ g一時値1++ ; }
				if( g盤面状態マップ[gループK+1][gループL+1][_KOMA_TYPE] != 0 ){ g一時値1++ ; }

				if( g一時値1 >= 3 ){
					gリーチ状態 = 1 ;
				}
			}
		}
	}

	return gリーチ状態;
}
void 移動ボタンAイベント()
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
void 座標自動設定()
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
void クアルト判定処理(){
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
void 変数初期化(){
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
void main(void)
{
	メインループ();
}
