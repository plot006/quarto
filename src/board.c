#include "lib/neslib.h"

#include "board.h"
#include "data.h"
#include "defs.h"
#include "state.h"

static void 盤面座標取得(unsigned char arg位置X, unsigned char arg位置Y)
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
static void 属性共有(unsigned char argアクション)
{
	if( argアクション == 0 ){
		g属性更新バッファ[3][2] = g属性状態配列[3] ;
		g属性更新バッファ[4][2] = g属性状態配列[4] ;
	}else{
		g属性状態配列[3] = g属性更新バッファ[3][2] ;
		g属性状態配列[4] = g属性更新バッファ[4][2] ;
	}
}

static void 属性座標取得(unsigned char arg位置X, unsigned char arg位置Y)
{
	g設定アドレス上位 = 0x23 ;
	g設定アドレス下位 = 0xC0 + (0x08*(arg位置Y/4)) + arg位置X/4 ;
}


static void 盤面駒色設定(unsigned char argカラー)
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
static void 駒色設定(unsigned char arg位置X, unsigned char arg位置Y, unsigned char argカラー)
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

static void バー描画(unsigned int argアドレス, unsigned char argアクション)
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
void バー自動描画(void)
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

void カーソル描画(void)
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
unsigned char クアルト判定(void)
{
	for( gループI = 0; gループI < 4; gループI++ ){
		g一時値1 = g盤面状態マップ[gループI][0][_KOMA_TYPE] ;
		g一時値2 = g盤面状態マップ[gループI][1][_KOMA_TYPE] ;
		g一時値3 = g盤面状態マップ[gループI][2][_KOMA_TYPE] ;
		g一時値4 = g盤面状態マップ[gループI][3][_KOMA_TYPE] ;
		g計算値 = g一時値1 & g一時値2 ;
		g計算値 = g計算値 & g一時値3 ;
		g計算値 = g計算値 & g一時値4 ;
		if( g計算値 != 0 ){
			for( gループJ = 0; gループJ < 4; gループJ++ ){
				gクアルトライン[gループJ][0] = gループI ;
				gクアルトライン[gループJ][1] = gループJ ;
			}
			return 1 ;
		}
	}
	for( gループJ = 0; gループJ < 4; gループJ++ ){
		g一時値1 = g盤面状態マップ[0][gループJ][_KOMA_TYPE] ;
		g一時値2 = g盤面状態マップ[1][gループJ][_KOMA_TYPE] ;
		g一時値3 = g盤面状態マップ[2][gループJ][_KOMA_TYPE] ;
		g一時値4 = g盤面状態マップ[3][gループJ][_KOMA_TYPE] ;
		g計算値 = g一時値1 & g一時値2 ;
		g計算値 = g計算値 & g一時値3 ;
		g計算値 = g計算値 & g一時値4 ;
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
		if( g計算値 != 0 ){
			for( gループI = 0; gループI < 4; gループI++ ){
				gクアルトライン[gループI][0] = gループI ;
				gクアルトライン[gループI][1] = gループJ ;
			}
			return 1 ;
		}
	}

	// クロス縦.
	g一時値1 = g盤面状態マップ[0][0][_KOMA_TYPE] ;
	g一時値2 = g盤面状態マップ[1][1][_KOMA_TYPE] ;
	g一時値3 = g盤面状態マップ[2][2][_KOMA_TYPE] ;
	g一時値4 = g盤面状態マップ[3][3][_KOMA_TYPE] ;
	g計算値 = g一時値1 & g一時値2 ;
	g計算値 = g計算値 & g一時値3 ;
	g計算値 = g計算値 & g一時値4 ;
	if( g計算値 != 0 ){
		for( gループI = 0; gループI < 4; gループI++ ){
			gクアルトライン[gループI][0] = gループI ;
			gクアルトライン[gループI][1] = gループI ;
		}
		return 1 ;
	}

	// クロス横.
	g一時値1 = g盤面状態マップ[0][3][_KOMA_TYPE] ;
	g一時値2 = g盤面状態マップ[1][2][_KOMA_TYPE] ;
	g一時値3 = g盤面状態マップ[2][1][_KOMA_TYPE] ;
	g一時値4 = g盤面状態マップ[3][0][_KOMA_TYPE] ;
	g計算値 = g一時値1 & g一時値2 ;
	g計算値 = g計算値 & g一時値3 ;
	g計算値 = g計算値 & g一時値4 ;
	if( g計算値 != 0 ){
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
				g一時値1 = g盤面状態マップ[gループI][gループJ][_KOMA_TYPE] ;
				g一時値2 = g盤面状態マップ[gループI][gループJ+1][_KOMA_TYPE] ;
				g一時値3 = g盤面状態マップ[gループI+1][gループJ][_KOMA_TYPE] ;
				g一時値4 = g盤面状態マップ[gループI+1][gループJ+1][_KOMA_TYPE] ;
				g計算値 = g一時値1 & g一時値2 ;
				g計算値 = g計算値 & g一時値3 ;
				g計算値 = g計算値 & g一時値4 ;
				if( g計算値 != 0 ){
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

unsigned char リーチ判定(void)
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
