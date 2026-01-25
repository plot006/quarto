#include "lib/neslib.h"

#include "anim.h"
#include "data.h"
#include "defs.h"
#include "state.h"

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
static void 上方向処理(unsigned char g座標X, unsigned char g座標Y)
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
static void 盤面アドレス設定(unsigned char g座標X, unsigned char g座標Y)
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
