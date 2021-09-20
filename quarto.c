//this example shows metasprite use, two pads polling,
//and simple collision detection that changes palette

#include "lib/neslib.h"
#include "resource/test2_blank.h"
#include "resource/open_name.h"
#include "resource/qr.h"
#include "resource/menu.h"
#include "resource/jeesus.h"

#include <stdlib.h>
static unsigned char strbuf[16];

//#define debug
#ifdef debug
#endif

void reset(void) ;

//variables

//static unsigned char bank;

static unsigned char quarto;
//static unsigned char checking;

static unsigned char i;
static unsigned char j;

static unsigned char k;
static unsigned char l;
static unsigned char m;
static unsigned char n;

static unsigned char o;
static unsigned char p;


static unsigned char x;
static unsigned char y;
static unsigned char tmp_x;
static unsigned char tmp_y;

static unsigned char x_index;
static unsigned char y_index;

static unsigned char timer;
static unsigned char timerSetCount;

static unsigned char set_posh;
static unsigned char set_posl;
static unsigned char whichTurn;
static unsigned char selBW;

static unsigned char pad,spr;

static unsigned char calc;
static unsigned char tmp;
static unsigned char tmp2;
static unsigned char tmp3;
static unsigned char tmp4;
static unsigned char frame;
static unsigned char koma_frame;
static unsigned char anime[4][4]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

static unsigned char q_black;
static unsigned char q_white;
static unsigned char q_high;
static unsigned char q_low;
static unsigned char q_square;
static unsigned char q_circle;
static unsigned char q_plane;
static unsigned char q_dot;
static unsigned char err[2] ;

static unsigned char set_posx;
static unsigned char set_posy;

static unsigned char moving;
static unsigned char p1only;

static unsigned char koma_pos[2];
static unsigned char koma_x[2];
static unsigned char koma_y[2];
static unsigned char ChooseKoma;
static unsigned char koma_exist[2][8];
static unsigned char tmp_line[8];

static unsigned char bgpl;
static unsigned char game_music;
static unsigned char reach;
static unsigned char autoChoose;
static unsigned char isForceFin;
static unsigned char isVsCPU;

static unsigned char attr_stat[40];

static unsigned char rand_box1[4] ;
static unsigned char rand_box2[4] ;
static unsigned char rand_box3[2] ;
static unsigned char rand_box4[8] ;


const unsigned char attr_pos[4][4][4] ={
	0xCB,	0xCC,	0xD3,	0xD4,
	0xD2,	0xD3,	0xD2,	0xD3,
	0xD1,	0xD2,	0xD9,	0xDA,
	0xD8,	0xD9,	0xD8,	0xD9,

	0xD4,	0xD5,	0xD4,	0xD5,
	0xD3,	0xD4,	0xDB,	0xDC,
	0xDA,	0xDB,	0xDA,	0xDB,
	0xD9,	0xDA,	0xE1,	0xE2,

	0xD5,	0xD6,	0xDD,	0xDE,
	0xDC,	0xDD,	0xDC,	0xDD,
	0xDB,	0xDC,	0xE3,	0xE4,
	0xE2,	0xE3,	0xE2,	0xE3,

	0xDE,	0xDF,	0xDE,	0xDF,
	0xDD,	0xDE,	0xE5,	0xE6,
	0xE4,	0xE5,	0xE4,	0xE5,
	0xE3,	0xE4,	0xEB,	0xEC

};

const unsigned char stage_anime_index[16][2] = {
	0,0,
	0,1,
	0,2,
	0,3,
	1,3,
	2,3,
	3,3,
	3,2,
	3,1,
	3,0,
	2,0,
	1,0,
	1,1,
	1,2,
	2,2,
	2,1,
};

//two players coords

/*
static unsigned char cat_x[2];
static unsigned char cat_y[2];
static unsigned char term[2];
static unsigned char isHit[2];
*/

//static unsigned char x_index[2];
//static unsigned char y_index[2];
//static unsigned char chr_index[2];
//static unsigned char dk_x_r_index;
//static unsigned char dk_x_l_index;
//static unsigned char dk_y_u_index;
//static unsigned char dk_chr_index1;
static unsigned char stage_stat[4][4][3];
#define _KOMA_TYPE		0
#define _CHOOSE_KOMA	1
#define _SEL_BW			2

static unsigned char quarto_line[4][2];


static unsigned char update_list[6+8+8+1];
static unsigned char update_koma[(3+3)*4+1];
static unsigned char update_koma_color[3+1+1];

static unsigned char update_debug[3+16+1];
static unsigned char dbgcnt;


//first player metasprite, data structure explained in neslib.h
const unsigned char msgBlank[]= "              " ;

#define stage_y_offset 0x80
const unsigned char stage_pos[4][4][6]={
	0x01,	0x0e,	0x01,	0x2E,	0x01,	0x4E,
	0x01,	0x4A,	0x01,	0x6A,	0x01,	0x8A,
	0x01,	0x86,	0x01,	0xA6,	0x01,	0xC6,
	0x01,	0xC2,	0x01,	0xE2,	0x02,	0x02,
	0x01,	0x52,	0x01,	0x72,	0x01,	0x92,
	0x01,	0x8E,	0x01,	0xAE,	0x01,	0xCE,
	0x01,	0xCA,	0x01,	0xEA,	0x02,	0x0A,
	0x02,	0x06,	0x02,	0x26,	0x02,	0x46,
	0x01,	0x96,	0x01,	0xB6,	0x01,	0xD6,
	0x01,	0xD2,	0x01,	0xF2,	0x02,	0x12,
	0x02,	0x0E,	0x02,	0x2E,	0x02,	0x4E,
	0x02,	0x4A,	0x02,	0x6A,	0x02,	0x8A,
	0x01,	0xDA,	0x01,	0xFA,	0x02,	0x1A,
	0x02,	0x16,	0x02,	0x36,	0x02,	0x56,
	0x02,	0x52,	0x02,	0x72,	0x02,	0x92,
	0x02,	0x8E,	0x02,	0xAE,	0x02,	0xCE
};

//const unsigned char pal_spr_data1[16]={ 0x0f,0x00,0x0f,0x0f,0x0f,0x0c,0x30,0x31,0x0f,0x0c,0x30,0x37,0x0f,0x0c,0x0f,0x0f };


const unsigned char open_palette1[16]={ 0x0f,0x0c,0x30,0x31,0x0f,0x05,0x25,0x35,0x0f,0x0c,0x2c,0x3c,0x0f,0x0a,0x3a,0x3a };
const unsigned char open_palette2[16]={ 0x0f,0x05,0x25,0x35,0x0f,0x0c,0x2c,0x3c,0x0f,0x0a,0x3a,0x3a,0x0f,0x0c,0x30,0x31 };
const unsigned char open_palette3[16]={ 0x0f,0x0c,0x2c,0x3c,0x0f,0x0a,0x3a,0x3a,0x0f,0x0c,0x30,0x31,0x0f,0x05,0x25,0x35 };
const unsigned char open_palette4[16]={ 0x0f,0x0a,0x3a,0x3a,0x0f,0x0c,0x30,0x31,0x0f,0x05,0x25,0x35,0x0f,0x0c,0x2c,0x3c };

const unsigned char palette1[16]={ 0x0f,0x00,0x0f,0x0f,0x0f,0x0c,0x30,0x31,0x0f,0x0c,0x30,0x37,0x0f,0x0c,0x0f,0x0f };
const unsigned char palette2[16]={ 0x0f,0x0c,0x3c,0x0f,0x0f,0x0f,0x30,0x15,0x0f,0x0f,0x30,0x1c,0x0f,0x05,0x35,0x0f };
//const unsigned char palette2[16]={ 0x0f,0x1c,0x3c,0x0f,0x0f,0x0f,0x30,0x05,0x0f,0x0f,0x30,0x0c,0x0f,0x15,0x35,0x0f };
const unsigned char palette3[16]={ 0x0c,0x0c,0x0c,0x0c,0x0c,0x00,0x30,0x30,0x0c,0x10,0x30,0x0f,0x0c,0x0c,0x0c,0x0c };
const unsigned char palette4[16]={ 0x0b,0x0b,0x0b,0x0b,0x0b,0x26,0x30,0x07,0x0b,0x17,0x30,0x37,0x0b,0x0b,0x0b,0x0b };
const unsigned char* bg_palettes[]={
	palette1,
	palette2,
	palette3,
	palette4
};


const unsigned char palette5[16]={ 0x0f,0x0f,0x0f,0x0f,0x0f,0x24,0x0f,0x0f,0x0f,0x21,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f };
const unsigned char palette6[16]={ 0x0f,0x0f,0x0f,0x0f,0x0f,0x24,0x0f,0x24,0x0f,0x21,0x0f,0x21,0x0f,0x0f,0x0f,0x0f };
const unsigned char palette7[16]={ 0x0f,0x0f,0x0f,0x0f,0x0f,0x24,0x30,0x24,0x0f,0x21,0x30,0x21,0x0f,0x0f,0x0f,0x0f };
const unsigned char palette8[16]={ 0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x24,0x24,0x0f,0x0f,0x21,0x21,0x0f,0x0f,0x0f,0x0f };
const unsigned char* bg_palettes2[]={
	palette5,
	palette6,
	palette7,
	palette8
};

const unsigned char palette_jeesus[16]={ 0x0f,0x05,0x30,0x26,0x0f,0x05,0x30,0x36,0x0f,0x16,0x30,0x36,0x0f,0x26,0x30,0x30 };

/*
const unsigned char meta_bar1[]={
	0xDD,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,
	0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDE,0xDF
};
const unsigned char meta_bar2[]={
	0xED,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,
	0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEF
};
*/
/*
const unsigned char meta_mask[]={
	0,	0,	0x42,	0,
	8,	0,	0x42,	0,
	128
};
const unsigned char meta_mask_long[]={
	0,	0,	0x42,	0,
	8,	0,	0x42,	0,
	16,	0,	0x42,	0,
	24,	0,	0x42,	0,
	0,	8,	0x42,	0,
	8,	8,	0x42,	0,
	16,	8,	0x42,	0,
	24,	8,	0x42,	0,
	128
};
*/

const unsigned char meta_quarto[]={
	8*0,	0,	'Q'-0x20,	1,
	8*1,	0,	'U'-0x20,	1,
	8*2,	0,	'A'-0x20,	1,
	8*3,	0,	'R'-0x20,	1,
	8*4,	0,	'T'-0x20,	1,
	8*5,	0,	'O'-0x20,	1,
	8*6,	0,	'!'-0x20,	1,
	128
};

const unsigned char meta_p1win[]={
	8*0,	0,	'P'-0x20,	1,
	8*1,	0,	'1'-0x20,	1,
	8*2,	0,	' '-0x20,	1,
	8*3,	0,	'W'-0x20,	1,
	8*4,	0,	'I'-0x20,	1,
	8*5,	0,	'N'-0x20,	1,
	8*6,	0,	'!'-0x20,	1,
	128
};
const unsigned char meta_p2win[]={
	8*0,	0,	'P'-0x20,	1,
	8*1,	0,	'2'-0x20,	1,
	8*2,	0,	' '-0x20,	1,
	8*3,	0,	'W'-0x20,	1,
	8*4,	0,	'I'-0x20,	1,
	8*5,	0,	'N'-0x20,	1,
	8*6,	0,	'!'-0x20,	1,
	128
};
const unsigned char meta_right_cursor[]={
	0,	0,	0x1E,	1,
	128
};

const unsigned char meta_pos1[]={
	0,	0,	0xCF,	1,
	128
};
const unsigned char meta_pos2[]={
	0,	0,	0xCF,	2,
	128
};

const unsigned char meta_pos1_reverse[]={
	0,	0,	0xCF,	0x81,
	128
};
const unsigned char meta_pos2_reverse[]={
	0,	0,	0xCF,	0x82,
	128
};

const unsigned char cursor[]={
	0,	0,	0x44,	1,
	128
};
const unsigned char cursor2[]={
	0,	0,	0x44,	0x81,
	128
};

const unsigned char koma_1[]={
	0,	0,	0x80,	1,
	0,	8,	0x90,	1,
	0,	16,	0xA0,	1,
	0,	24,	0xB0,	1,
	8,	0,	0x81,	1,
	8,	8,	0x91,	1,
	8,	16,	0xA1,	1,
	8,	24,	0xB1,	1,
	16,	0,	0x82,	1,
	16,	8,	0x92,	1,
	16,	16,	0xA2,	1,
	16,	24,	0xB2,	1,
	128
};
const unsigned char koma_2[]={
	0,	0,	0x86,	1,
	0,	8,	0x90,	1,
	0,	16,	0xA0,	1,
	0,	24,	0xB0,	1,
	8,	0,	0x87,	1,
	8,	8,	0x91,	1,
	8,	16,	0xA1,	1,
	8,	24,	0xB1,	1,
	16,	0,	0x88,	1,
	16,	8,	0x92,	1,
	16,	16,	0xA2,	1,
	16,	24,	0xB2,	1,
	128
};
const unsigned char koma_3[]={
	0,	0,	0x83,	1,
	0,	8,	0x93,	1,
	0,	16,	0xA3,	1,
	0,	24,	0xB3,	1,
	8,	0,	0x84,	1,
	8,	8,	0x94,	1,
	8,	16,	0xA4,	1,
	8,	24,	0xB4,	1,
	16,	0,	0x85,	1,
	16,	8,	0x95,	1,
	16,	16,	0xA5,	1,
	16,	24,	0xB5,	1,
	128
};
const unsigned char koma_4[]={
	0,	0,	0x89,	1,
	0,	8,	0x93,	1,
	0,	16,	0xA3,	1,
	0,	24,	0xB3,	1,
	8,	0,	0x8A,	1,
	8,	8,	0x94,	1,
	8,	16,	0xA4,	1,
	8,	24,	0xB4,	1,
	16,	0,	0x8B,	1,
	16,	8,	0x95,	1,
	16,	16,	0xA5,	1,
	16,	24,	0xB5,	1,
	128
};
const unsigned char koma_5[]={
	0,	0,	0x00,	1,
	0,	8,	0x80,	1,
	0,	16,	0x90,	1,
	0,	24,	0xB0,	1,
	8,	0,	0x00,	1,
	8,	8,	0x81,	1,
	8,	16,	0x91,	1,
	8,	24,	0xB1,	1,
	16,	0,	0x00,	1,
	16,	8,	0x82,	1,
	16,	16,	0x92,	1,
	16,	24,	0xB2,	1,
	128
};
const unsigned char koma_6[]={
	0,	0,	0x00,	1,
	0,	8,	0x86,	1,
	0,	16,	0x90,	1,
	0,	24,	0xB0,	1,
	8,	0,	0x00,	1,
	8,	8,	0x87,	1,
	8,	16,	0x91,	1,
	8,	24,	0xB1,	1,
	16,	0,	0x00,	1,
	16,	8,	0x88,	1,
	16,	16,	0x92,	1,
	16,	24,	0xB2,	1,
	128
};
const unsigned char koma_7[]={
	0,	0,	0x00,	1,
	0,	8,	0x83,	1,
	0,	16,	0x93,	1,
	0,	24,	0xB3,	1,
	8,	0,	0x00,	1,
	8,	8,	0x84,	1,
	8,	16,	0x94,	1,
	8,	24,	0xB4,	1,
	16,	0,	0x00,	1,
	16,	8,	0x85,	1,
	16,	16,	0x95,	1,
	16,	24,	0xB5,	1,
	128
};
const unsigned char koma_8[]={
	0,	0,	0x00,	1,
	0,	8,	0x89,	1,
	0,	16,	0x93,	1,
	0,	24,	0xB3,	1,
	8,	0,	0x00,	1,
	8,	8,	0x8A,	1,
	8,	16,	0x94,	1,
	8,	24,	0xB4,	1,
	16,	0,	0x00,	1,
	16,	8,	0x8B,	1,
	16,	16,	0x95,	1,
	16,	24,	0xB5,	1,
	128
};

const unsigned char koma_1_P2[]={
	0,	0,	0x80,	2,
	0,	8,	0x90,	2,
	0,	16,	0xA0,	2,
	0,	24,	0xB0,	2,
	8,	0,	0x81,	2,
	8,	8,	0x91,	2,
	8,	16,	0xA1,	2,
	8,	24,	0xB1,	2,
	16,	0,	0x82,	2,
	16,	8,	0x92,	2,
	16,	16,	0xA2,	2,
	16,	24,	0xB2,	2,
	128
};
const unsigned char koma_2_P2[]={
	0,	0,	0x86,	2,
	0,	8,	0x90,	2,
	0,	16,	0xA0,	2,
	0,	24,	0xB0,	2,
	8,	0,	0x87,	2,
	8,	8,	0x91,	2,
	8,	16,	0xA1,	2,
	8,	24,	0xB1,	2,
	16,	0,	0x88,	2,
	16,	8,	0x92,	2,
	16,	16,	0xA2,	2,
	16,	24,	0xB2,	2,
	128
};
const unsigned char koma_3_P2[]={
	0,	0,	0x83,	2,
	0,	8,	0x93,	2,
	0,	16,	0xA3,	2,
	0,	24,	0xB3,	2,
	8,	0,	0x84,	2,
	8,	8,	0x94,	2,
	8,	16,	0xA4,	2,
	8,	24,	0xB4,	2,
	16,	0,	0x85,	2,
	16,	8,	0x95,	2,
	16,	16,	0xA5,	2,
	16,	24,	0xB5,	2,
	128
};
const unsigned char koma_4_P2[]={
	0,	0,	0x89,	2,
	0,	8,	0x93,	2,
	0,	16,	0xA3,	2,
	0,	24,	0xB3,	2,
	8,	0,	0x8A,	2,
	8,	8,	0x94,	2,
	8,	16,	0xA4,	2,
	8,	24,	0xB4,	2,
	16,	0,	0x8B,	2,
	16,	8,	0x95,	2,
	16,	16,	0xA5,	2,
	16,	24,	0xB5,	2,
	128
};
const unsigned char koma_5_P2[]={
	0,	0,	0x00,	2,
	0,	8,	0x80,	2,
	0,	16,	0x90,	2,
	0,	24,	0xB0,	2,
	8,	0,	0x00,	2,
	8,	8,	0x81,	2,
	8,	16,	0x91,	2,
	8,	24,	0xB1,	2,
	16,	0,	0x00,	2,
	16,	8,	0x82,	2,
	16,	16,	0x92,	2,
	16,	24,	0xB2,	2,
	128
};
const unsigned char koma_6_P2[]={
	0,	0,	0x00,	2,
	0,	8,	0x86,	2,
	0,	16,	0x90,	2,
	0,	24,	0xB0,	2,
	8,	0,	0x00,	2,
	8,	8,	0x87,	2,
	8,	16,	0x91,	2,
	8,	24,	0xB1,	2,
	16,	0,	0x00,	2,
	16,	8,	0x88,	2,
	16,	16,	0x92,	2,
	16,	24,	0xB2,	2,
	128
};
const unsigned char koma_7_P2[]={
	0,	0,	0x00,	2,
	0,	8,	0x83,	2,
	0,	16,	0x93,	2,
	0,	24,	0xB3,	2,
	8,	0,	0x00,	2,
	8,	8,	0x84,	2,
	8,	16,	0x94,	2,
	8,	24,	0xB4,	2,
	16,	0,	0x00,	2,
	16,	8,	0x85,	2,
	16,	16,	0x95,	2,
	16,	24,	0xB5,	2,
	128
};
const unsigned char koma_8_P2[]={
	0,	0,	0x00,	2,
	0,	8,	0x89,	2,
	0,	16,	0x93,	2,
	0,	24,	0xB3,	2,
	8,	0,	0x00,	2,
	8,	8,	0x8A,	2,
	8,	16,	0x94,	2,
	8,	24,	0xB4,	2,
	16,	0,	0x00,	2,
	16,	8,	0x8B,	2,
	16,	16,	0x95,	2,
	16,	24,	0xB5,	2,
	128
};
const unsigned char OFF_koma_1[]={
	0,	0,	0x80,	0,
	0,	8,	0x90,	0,
	0,	16,	0xA0,	0,
	0,	24,	0xB0,	0,
	8,	0,	0x81,	0,
	8,	8,	0x91,	0,
	8,	16,	0xA1,	0,
	8,	24,	0xB1,	0,
	16,	0,	0x82,	0,
	16,	8,	0x92,	0,
	16,	16,	0xA2,	0,
	16,	24,	0xB2,	0,
	128
};
const unsigned char OFF_koma_2[]={
	0,	0,	0x86,	0,
	0,	8,	0x90,	0,
	0,	16,	0xA0,	0,
	0,	24,	0xB0,	0,
	8,	0,	0x87,	0,
	8,	8,	0x91,	0,
	8,	16,	0xA1,	0,
	8,	24,	0xB1,	0,
	16,	0,	0x88,	0,
	16,	8,	0x92,	0,
	16,	16,	0xA2,	0,
	16,	24,	0xB2,	0,
	128
};
const unsigned char OFF_koma_3[]={
	0,	0,	0x83,	0,
	0,	8,	0x93,	0,
	0,	16,	0xA3,	0,
	0,	24,	0xB3,	0,
	8,	0,	0x84,	0,
	8,	8,	0x94,	0,
	8,	16,	0xA4,	0,
	8,	24,	0xB4,	0,
	16,	0,	0x85,	0,
	16,	8,	0x95,	0,
	16,	16,	0xA5,	0,
	16,	24,	0xB5,	0,
	128
};
const unsigned char OFF_koma_4[]={
	0,	0,	0x89,	0,
	0,	8,	0x93,	0,
	0,	16,	0xA3,	0,
	0,	24,	0xB3,	0,
	8,	0,	0x8A,	0,
	8,	8,	0x94,	0,
	8,	16,	0xA4,	0,
	8,	24,	0xB4,	0,
	16,	0,	0x8B,	0,
	16,	8,	0x95,	0,
	16,	16,	0xA5,	0,
	16,	24,	0xB5,	0,
	128
};
const unsigned char OFF_koma_5[]={
	0,	0,	0x00,	0,
	0,	8,	0x80,	0,
	0,	16,	0x90,	0,
	0,	24,	0xB0,	0,
	8,	0,	0x00,	0,
	8,	8,	0x81,	0,
	8,	16,	0x91,	0,
	8,	24,	0xB1,	0,
	16,	0,	0x00,	0,
	16,	8,	0x82,	0,
	16,	16,	0x92,	0,
	16,	24,	0xB2,	0,
	128
};
const unsigned char OFF_koma_6[]={
	0,	0,	0x00,	0,
	0,	8,	0x86,	0,
	0,	16,	0x90,	0,
	0,	24,	0xB0,	0,
	8,	0,	0x00,	0,
	8,	8,	0x87,	0,
	8,	16,	0x91,	0,
	8,	24,	0xB1,	0,
	16,	0,	0x00,	0,
	16,	8,	0x88,	0,
	16,	16,	0x92,	0,
	16,	24,	0xB2,	0,
	128
};
const unsigned char OFF_koma_7[]={
	0,	0,	0x00,	0,
	0,	8,	0x83,	0,
	0,	16,	0x93,	0,
	0,	24,	0xB3,	0,
	8,	0,	0x00,	0,
	8,	8,	0x84,	0,
	8,	16,	0x94,	0,
	8,	24,	0xB4,	0,
	16,	0,	0x00,	0,
	16,	8,	0x85,	0,
	16,	16,	0x95,	0,
	16,	24,	0xB5,	0,
	128
};
const unsigned char OFF_koma_8[]={
	0,	0,	0x00,	0,
	0,	8,	0x89,	0,
	0,	16,	0x93,	0,
	0,	24,	0xB3,	0,
	8,	0,	0x00,	0,
	8,	8,	0x8A,	0,
	8,	16,	0x94,	0,
	8,	24,	0xB4,	0,
	16,	0,	0x00,	0,
	16,	8,	0x8B,	0,
	16,	16,	0x95,	0,
	16,	24,	0xB5,	0,
	128
};
/*
const unsigned char OFF_koma_1_P2[]={
	0,	0,	0x80,	0,
	0,	8,	0x90,	0,
	0,	16,	0xA0,	0,
	0,	24,	0xB0,	0,
	8,	0,	0x81,	3,
	8,	8,	0x91,	3,
	8,	16,	0xA1,	3,
	8,	24,	0xB1,	3,
	16,	0,	0x82,	3,
	16,	8,	0x92,	3,
	16,	16,	0xA2,	3,
	16,	24,	0xB2,	3,
	128
};
const unsigned char OFF_koma_2_P2[]={
	0,	0,	0x86,	3,
	0,	8,	0x90,	3,
	0,	16,	0xA0,	3,
	0,	24,	0xB0,	3,
	8,	0,	0x87,	3,
	8,	8,	0x91,	3,
	8,	16,	0xA1,	3,
	8,	24,	0xB1,	3,
	16,	0,	0x88,	3,
	16,	8,	0x92,	3,
	16,	16,	0xA2,	3,
	16,	24,	0xB2,	3,
	128
};
const unsigned char OFF_koma_3_P2[]={
	0,	0,	0x83,	3,
	0,	8,	0x93,	3,
	0,	16,	0xA3,	3,
	0,	24,	0xB3,	3,
	8,	0,	0x84,	3,
	8,	8,	0x94,	3,
	8,	16,	0xA4,	3,
	8,	24,	0xB4,	3,
	16,	0,	0x85,	3,
	16,	8,	0x95,	3,
	16,	16,	0xA5,	3,
	16,	24,	0xB5,	3,
	128
};
const unsigned char OFF_koma_4_P2[]={
	0,	0,	0x89,	3,
	0,	8,	0x93,	3,
	0,	16,	0xA3,	3,
	0,	24,	0xB3,	3,
	8,	0,	0x8A,	3,
	8,	8,	0x94,	3,
	8,	16,	0xA4,	3,
	8,	24,	0xB4,	3,
	16,	0,	0x8B,	3,
	16,	8,	0x95,	3,
	16,	16,	0xA5,	3,
	16,	24,	0xB5,	3,
	128
};
const unsigned char OFF_koma_5_P2[]={
	0,	0,	0x00,	3,
	0,	8,	0x80,	3,
	0,	16,	0x90,	3,
	0,	24,	0xB0,	3,
	8,	0,	0x00,	3,
	8,	8,	0x81,	3,
	8,	16,	0x91,	3,
	8,	24,	0xB1,	3,
	16,	0,	0x00,	3,
	16,	8,	0x82,	3,
	16,	16,	0x92,	3,
	16,	24,	0xB2,	3,
	128
};
const unsigned char OFF_koma_6_P2[]={
	0,	0,	0x00,	3,
	0,	8,	0x86,	3,
	0,	16,	0x90,	3,
	0,	24,	0xB0,	3,
	8,	0,	0x00,	3,
	8,	8,	0x87,	3,
	8,	16,	0x91,	3,
	8,	24,	0xB1,	3,
	16,	0,	0x00,	3,
	16,	8,	0x88,	3,
	16,	16,	0x92,	3,
	16,	24,	0xB2,	3,
	128
};
const unsigned char OFF_koma_7_P2[]={
	0,	0,	0x00,	3,
	0,	8,	0x83,	3,
	0,	16,	0x93,	3,
	0,	24,	0xB3,	3,
	8,	0,	0x00,	3,
	8,	8,	0x84,	3,
	8,	16,	0x94,	3,
	8,	24,	0xB4,	3,
	16,	0,	0x00,	3,
	16,	8,	0x85,	3,
	16,	16,	0x95,	3,
	16,	24,	0xB5,	3,
	128
};
const unsigned char OFF_koma_8_P2[]={
	0,	0,	0x00,	3,
	0,	8,	0x89,	3,
	0,	16,	0x93,	3,
	0,	24,	0xB3,	3,
	8,	0,	0x00,	3,
	8,	8,	0x8A,	3,
	8,	16,	0x94,	3,
	8,	24,	0xB4,	3,
	16,	0,	0x00,	3,
	16,	8,	0x8B,	3,
	16,	16,	0x95,	3,
	16,	24,	0xB5,	3,
	128
};
*/
const unsigned char koma_type[] ={ 
	0b00000000,
	0b11110000,
	0b11100001,
	0b11010010,
	0b11000011,
	0b10110100,
	0b10100101,
	0b10010110,
	0b10000111,
	0b01111000,
	0b01101001,
	0b01011010,
	0b01001011,
	0b00111100,
	0b00101101,
	0b00011110,
	0b00001111
};
const unsigned char* koma_list[1][2][8]={
	koma_1,
	koma_2,
	koma_3,
	koma_4,
	koma_5,
	koma_6,
	koma_7,
	koma_8,
	koma_1_P2,
	koma_2_P2,
	koma_3_P2,
	koma_4_P2,
	koma_5_P2,
	koma_6_P2,
	koma_7_P2,
	koma_8_P2
/*
	OFF_koma_1,
	OFF_koma_2,
	OFF_koma_3,
	OFF_koma_4,
	OFF_koma_5,
	OFF_koma_6,
	OFF_koma_7,
	OFF_koma_8,
	OFF_koma_1_P2,
	OFF_koma_2_P2,
	OFF_koma_3_P2,
	OFF_koma_4_P2,
	OFF_koma_5_P2,
	OFF_koma_6_P2,
	OFF_koma_7_P2,
	OFF_koma_8_P2
*/
};

void seedRandBox()
{
	memfill( rand_box1, 9, 4 );
	memfill( rand_box2, 9, 4 );
	memfill( rand_box3, 9, 2 );
	memfill( rand_box4, 9, 8 );

	for( i=0; i < 4;){
		tmp = (rand8()+frame)%4 ;
		if( rand_box1[tmp] == i || rand_box1[tmp] != 9 ){
			frame += open_palette1[tmp] ;
			continue ;
		}
		rand_box1[tmp] = i ;
		i++ ;
	}
	for( i=0; i < 4;){
		tmp = (rand8()+frame)%4 ;
		if( rand_box2[tmp] == i || rand_box2[tmp] != 9 ){
			frame += open_palette1[tmp] ;
			continue ;
		}
		rand_box2[tmp] = i ;
		i++ ;
	}

	for( i=0; i < 2;){
		tmp = (rand8()+frame)%2 ;
		if( rand_box3[tmp] == i || rand_box3[tmp] != 9 ){
			frame += open_palette1[tmp] ;
			continue ;
		}
		rand_box3[tmp] = i ;
		i++ ;
	}
	for( i=0; i < 8;){
		tmp = (rand8()+frame)%8 ;
		if( rand_box4[tmp] == i || rand_box4[tmp] != 9 ){
			frame += open_palette1[tmp] ;
			continue ;
		}
		rand_box4[tmp] = i ;
		i++ ;
	}

}

void put_update_debug(unsigned char x, unsigned char y, unsigned char len, const char *str)
{
	
	update_debug[0]=MSB(NTADR_A(x,y))|NT_UPD_HORZ;//set the address
	update_debug[1]=LSB(NTADR_A(x,y));
	update_debug[2]=len;//update sequence is 4 tiles wide
	update_debug[3+len]=NT_UPD_EOF;
	set_vram_update(update_debug);

	for( dbgcnt = 0;dbgcnt<len;dbgcnt++)
	{
		if(!*str) break;
		update_debug[3+dbgcnt]=(*str++)-0x20 ;//fill row buffer with random tiles
	}
	ppu_wait_frame();
	set_vram_update(0);
}


void update_init(void){
	update_list[0]=0x20|NT_UPD_HORZ;
	update_list[1]=0x00;
	update_list[2]=3;
	
	update_list[(6)]=0x20|NT_UPD_HORZ;
	update_list[(6)+1]=0x00;
	update_list[(6)+2]=5;
	
	update_list[(6+8)]=0x20|NT_UPD_HORZ;
	update_list[(6+8)+1]=0x00;
	update_list[(6+8)+2]=5;
	
	update_list[(6+8+8)]=NT_UPD_EOF;
	set_vram_update(update_list);

}

/*
void stagePreAnime(unsigned char x, unsigned char y, unsigned char action)
{
	spr = 0 ;
	for( tmp = 0; tmp < 32 ; tmp++ ){
		oam_meta_spr( (x*32)-(y*32)+115-tmp, (y*16)+(x*16)+71, spr, meta_mask_long ) ;
		if( action == 0 ){ return ; }
		//ppu_wait_frame();	// wait for next TV frame

		//if( tmp % 16 == 0 ){ delay(1) ; }
	}
	oam_clear() ;
}
*/
void upProc(unsigned char x, unsigned char y )
{
	for( i = 0; i < 5; i++ ){
		if( anime[x][y] == 0 ){
			//stagePreAnime(x,y,0) ;
			if( i != 0 && i != 4 ){
				update_list[i+3-1] = 0 ; 
			}
			update_list[i+(6)+3] = (unsigned char)(0xE5+i) ;
			update_list[i+(6+8)+3] = (unsigned char)(0xF5+i) ;
		}else if( anime[x][y] == 1 ){
			if( i != 0 && i != 4 ){
				update_list[i+3-1] = 0 ; 
			}
			update_list[i+(6)+3] = (unsigned char)(0xE5+i) ;
			update_list[i+(6+8)+3] = (unsigned char)(0xF5+i) ;
		}else if( anime[x][y] == 2 ){
			if( i != 0 && i != 4 ){
				update_list[i+3-1] = 0 ; 
			}
			update_list[i+(6)+3] = (unsigned char)(0xE0+i) ;
			update_list[i+(6+8)+3] = (unsigned char)(0xF0+i) ;
		}else if( anime[x][y] == 3 ){
			if( i != 0 && i != 4 ){
				update_list[i+3-1] = (unsigned char)(0xC5+i) ;
			}
			if( i == 0 || i == 4 ){
				update_list[i+(6)+3] = (unsigned char)(0xC5+i) ;
			}
			update_list[i+(6+8)+3] = (unsigned char)(0xD5+i) ;
		}else if( anime[x][y] == 4 ){
			if( i != 0 && i != 4 ){
				update_list[i+3-1] = (unsigned char)(0xC0+i) ;
			}
			if( i == 0 || i == 4 ){
				update_list[i+(6)+3] = (unsigned char)(0xC0+i) ;
			}
			update_list[i+(6+8)+3] = (unsigned char)(0xD0+i) ;
		}else{
			return ;
		}
	}
	delay(1) ;
}
void setStageAdr(unsigned char x, unsigned char y )
{
	unsigned char calcAdr = 0x00 ;
	calcAdr = stage_pos[x][y][1]+1+stage_y_offset > 0xFF ? stage_pos[x][y][0]+1 : stage_pos[x][y][0];
	update_list[0]=(0x20+calcAdr)&0xFF|NT_UPD_HORZ;//horizontal update sequence, dummy address
	update_list[1]=stage_pos[x][y][1]+1+stage_y_offset;

	calcAdr = stage_pos[x][y][3]+stage_y_offset > 0xFF ? stage_pos[x][y][2]+1 : stage_pos[x][y][2];
	update_list[(6)]=(0x20+calcAdr)&0xFF|NT_UPD_HORZ;//horizontal update sequence, dummy address
	update_list[(6)+1]=stage_pos[x][y][3]+stage_y_offset;

	calcAdr = stage_pos[x][y][5]+stage_y_offset > 0xFF ? stage_pos[x][y][4]+1 : stage_pos[x][y][4];
	update_list[(6+8)]=(0x20+calcAdr)&0xFF|NT_UPD_HORZ;//horizontal update sequence, dummy address
	update_list[(6+8)+1]=stage_pos[x][y][5]+stage_y_offset;
}
void up_stage(unsigned char x, unsigned char y )
{
	setStageAdr(x,y);
/*
	update_list[0]=0x20+stage_pos[x][y][0]|NT_UPD_HORZ;//horizontal update sequence, dummy address
	update_list[1]=stage_pos[x][y][1]+1;
	update_list[(6)]=0x20+stage_pos[x][y][2]|NT_UPD_HORZ;//horizontal update sequence, dummy address
	update_list[(6)+1]=stage_pos[x][y][3];
	update_list[(6+8)]=0x20+stage_pos[x][y][4]|NT_UPD_HORZ;//horizontal update sequence, dummy address
	update_list[(6+8)+1]=stage_pos[x][y][5];
*/
	sfx_play(5,0);

	for( anime[x][y] = 0 ; anime[x][y] < 5; anime[x][y]++ ){
/*
		for( i = 0; i < 5; i++ ){
			if( anime[x][y] == 0 ){
				//stagePreAnime(x,y,0) ;
				if( i != 0 && i != 4 ){
					update_list[i+3-1] = 0 ; 
				}
				update_list[i+(6)+3] = (unsigned char)(0xE5+i) ;
				update_list[i+(6+8)+3] = (unsigned char)(0xF5+i) ;
			}else if( anime[x][y] == 1 ){
				if( i != 0 && i != 4 ){
					update_list[i+3-1] = 0 ; 
				}
				update_list[i+(6)+3] = (unsigned char)(0xE5+i) ;
				update_list[i+(6+8)+3] = (unsigned char)(0xF5+i) ;
			}else if( anime[x][y] == 2 ){
				if( i != 0 && i != 4 ){
					update_list[i+3-1] = 0 ; 
				}
				update_list[i+(6)+3] = (unsigned char)(0xE0+i) ;
				update_list[i+(6+8)+3] = (unsigned char)(0xF0+i) ;
			}else if( anime[x][y] == 3 ){
				if( i != 0 && i != 4 ){
					update_list[i+3-1] = (unsigned char)(0xC5+i) ;
				}
				if( i == 0 || i == 4 ){
					update_list[i+(6)+3] = (unsigned char)(0xC5+i) ;
				}
				update_list[i+(6+8)+3] = (unsigned char)(0xD5+i) ;
			}else if( anime[x][y] == 4 ){
				if( i != 0 && i != 4 ){
					update_list[i+3-1] = (unsigned char)(0xC0+i) ;
				}
				if( i == 0 || i == 4 ){
					update_list[i+(6)+3] = (unsigned char)(0xC0+i) ;
				}
				update_list[i+(6+8)+3] = (unsigned char)(0xD0+i) ;
			}else{
				return ;
			}
		}
		delay(1) ;
		*/
		upProc(x,y) ;
	}
}
/*
void down_stage(unsigned char x, unsigned char y )
{
	setStageAdr(x,y);
	sfx_play(1,0);

	for( anime[x][y] = 4 ; anime[x][y] >= 0; anime[x][y]-- ){
		upProc(x,y) ;
	}
}
*/
void cycleNextColor(void)
{
	bgpl++ ;
	bgpl = bgpl > 3 ? 0 : bgpl ;
	//put_update_debug(NTADR_A(1,24), 5, itoa(bgpl, &strbuf[0], 10 ));

	pal_spr((char*)bg_palettes[bgpl]);
	pal_bg((char*)bg_palettes[bgpl]);
}
void cycleColor(void)
{
	if(frame%4==0){ pal_bg((char*)open_palette4);}
	if(frame%4==1){ pal_bg((char*)open_palette3);}
	if(frame%4==2){ pal_bg((char*)open_palette2);}
	if(frame%4==3){ pal_bg((char*)open_palette1);}
}
void cycleSprColor(void)
{
	if(frame%4==0){ pal_spr((char*)open_palette4);}
	if(frame%4==1){ pal_spr((char*)open_palette3);}
	if(frame%4==2){ pal_spr((char*)open_palette2);}
	if(frame%4==3){ pal_spr((char*)open_palette1);}
}
unsigned char checkForceBreak(void)
{
	pad = pad_poll(0);
	if(pad&PAD_START || pad&PAD_SELECT || pad&PAD_A || pad&PAD_B ){
		return 1 ;
	}
	pad = pad_poll(1);
	if(pad&PAD_START || pad&PAD_SELECT || pad&PAD_A || pad&PAD_B ){
		return 1 ;
	}
	return 0 ;
}
/*
unsigned char setKomaBuf(unsigned char* koma, unsigned char color)
{
	for( i = 0; i < sizeof(koma_buf)/4; i++ ){
		memcpy( koma_buf[4*i], &koma[4*i], 3 );
		koma_buf[4*i+3] = color ;
	}
}
*/
void bgFlash(unsigned char action)
{
	pal_bright(action);
	delay(6) ;
	pal_bright(4);
	delay(6) ;
	pal_bright(action);
	delay(6) ;
	pal_bright(4);
}
void bgDown()
{
	pal_bright(3);
	delay(6) ;
	pal_bright(2);
	delay(6) ;
	pal_bright(1);
	delay(6) ;
	pal_bright(0);
}
void bgUp()
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
void move_next(void)
{
	for( i = 0; i < 2; i++ ){
		koma_frame = 0 ;
		while(1){

			if( koma_frame % 10 == 0 ){ frame++ ; }

			delay(1) ;
			cycleColor() ;

			if( koma_frame == 0 ){
				// 初回アニメ処理.
				if( tmp < 10 ){ 
					delay(1) ;
					tmp++ ;
					continue ;
				}
				if( tmp == 10 ){
					tmp++ ;
					delay(20) ;

					bgFlash(0) ;
					bgDown() ;

					ppu_off() ;
					vram_adr(NAMETABLE_A);//set VRAM address
					vram_unrle((unsigned char*)open_name);
					ppu_on_all() ;

					delay(20) ;
					spr = 0 ;
					spr = oam_meta_spr( koma_x[0], koma_y[0], spr, koma_list[0][0][0] ) ;
					spr = oam_meta_spr( koma_x[1], koma_y[1], spr, koma_list[0][1][0] ) ;

					bgUp() ;

					put_update_debug(10,25, 13, "PRESS BUTTON!" );
					put_update_debug(11,27, 10, "006 * 2021" );
					delay(20) ;
					pal_bright(4);
					music_play(0);
				}
				// 駒描写
				for( j = 0; j < 14; j++ ){
					delay(1) ;
					koma_y[i]-- ;
					spr = 0 ;
					spr = oam_meta_spr( koma_x[0], koma_y[0], spr, koma_list[0][0][0] ) ;
					spr = oam_meta_spr( koma_x[1], koma_y[1], spr, koma_list[0][1][0] ) ;
					cycleColor() ;
					if( koma_frame % 10 == 0 ){ frame++ ; }
					koma_frame++ ;
					if( checkForceBreak() ){ return ; }

				}
			}

			if( checkForceBreak() ){ return ; }
			koma_frame++ ;

			spr = 0 ;
			
			spr = oam_meta_spr( koma_x[0], koma_y[0], spr, koma_list[0][0][0] ) ;
			spr = oam_meta_spr( koma_x[1], koma_y[1], spr, koma_list[0][1][0] ) ;


			if( koma_pos[i] == 0 ){
				if( koma_x[i] != 152 ){ koma_x[i]+=2; }
				if( koma_y[i] != 122 ){ koma_y[i]+=1; }
				if( koma_x[i] == 152 && koma_y[i] == 122 ){ 
					koma_pos[i] = 1 ;
					break ;
				}
			}
			else if( koma_pos[i] == 1 ){
				if( koma_x[i] != 112 ){ koma_x[i]-=2; }
				if( koma_y[i] != 144 ){ koma_y[i]+=1; }
				if( koma_x[i] == 112 && koma_y[i] == 144  ){
					koma_pos[i] = 2 ;
					break ;
				}
			}
			else if( koma_pos[i] == 2 ){
				if( koma_x[i] != 72 ){ koma_x[i]-=2; }
				if( koma_y[i] != 122 ){ koma_y[i]-=1; }
				if( koma_x[i] == 72 && koma_y[i] == 122 ){
					koma_pos[i] = 3 ;
					break ;
				}
			}
			else if( koma_pos[i] == 3 ){
				if( koma_x[i] != 112 ){ koma_x[i]+=2; }
				if( koma_y[i] != 96 ){ koma_y[i]-=1; }
				if( koma_x[i] == 112 && koma_y[i] == 96 ){
					koma_pos[i] = 0 ;
					break ;
				}
			}
		}
	}
}
#endif
#define posy_offset 4
void getStagePos(unsigned char posx, unsigned char posy)
{
	//位置補正.
	j = 0 ;
	if(posx >= 2 && posx <= 5){
		if( posy >= 10+posy_offset && posy <= 12+posy_offset ){ posx = 3 ;posy = 12+posy_offset ; j++; x_index=0 ; y_index=3 ;}
	}	
	if(posx >= 6 && posx <= 9){
		if( posy >= 8+posy_offset && posy <= 10+posy_offset ){ posx = 7 ;posy = 10+posy_offset ; j++; x_index=0 ; y_index=2 ;}
		if( posy >= 12+posy_offset && posy <= 14+posy_offset ){ posx = 7 ;posy = 14+posy_offset ; j++; x_index=1 ; y_index=3 ;}
	}	
	if(posx >= 10 && posx <= 13){
		if( posy >= 6+posy_offset && posy <= 8+posy_offset ){ posx = 11 ;posy = 8+posy_offset ; j++; x_index=0 ; y_index=1 ;}
		if( posy >= 10+posy_offset && posy <= 12+posy_offset ){ posx = 11 ;posy = 12+posy_offset ; j++; x_index=1 ; y_index=2 ;}
		if( posy >= 14+posy_offset && posy <= 16+posy_offset ){ posx = 11 ;posy = 16+posy_offset ; j++; x_index=2 ; y_index=3 ;}
	}
	if(posx >= 14 && posx <= 17){
		if( posy >= 4+posy_offset && posy <= 7+posy_offset ){ posx = 15 ;posy = 6+posy_offset ; j++; x_index=0 ; y_index=0 ; }
		if( posy >= 8+posy_offset && posy <= 10+posy_offset ){ posx = 15 ;posy = 10+posy_offset ; j++; x_index=1 ; y_index=1 ;}
		if( posy >= 12+posy_offset && posy <= 14+posy_offset ){ posx = 15 ;posy = 14+posy_offset ; j++; x_index=2 ; y_index=2 ;}
		if( posy >= 16+posy_offset && posy <= 18+posy_offset ){ posx = 15 ;posy = 18+posy_offset ; j++; x_index=3 ; y_index=3 ;}
	}
	if(posx >= 18 && posx <= 21){
		if( posy >= 6+posy_offset && posy <= 8+posy_offset ){ posx = 19 ;posy = 8+posy_offset ; j++; x_index=1 ; y_index=0 ;}
		if( posy >= 10+posy_offset && posy <= 12+posy_offset ){ posx = 19 ;posy = 12+posy_offset ; j++; x_index=2 ; y_index=1 ;}
		if( posy >= 14+posy_offset && posy <= 16+posy_offset ){ posx = 19 ;posy = 16+posy_offset ; j++; x_index=3 ; y_index=2 ;}
	}
	if(posx >= 22 && posx <= 25){
		if( posy >= 8+posy_offset && posy <= 10+posy_offset ){ posx = 23 ;posy = 10+posy_offset ; j++; x_index=2 ; y_index=0 ;}
		if( posy >= 12+posy_offset && posy <= 14+posy_offset ){ posx = 23 ;posy = 14+posy_offset ; j++; x_index=3 ; y_index=1 ;}
	}
	if(posx >= 26 && posx <= 29){
		if( posy >= 10+posy_offset && posy <= 12+posy_offset ){ posx = 27 ;posy = 12+posy_offset ; j++;x_index=3 ; y_index=0 ;}
	}
	
	if( posy < 8 ){
		set_posh = 0x20 ;
		set_posl = 0x00 + (0x20*posy) + posx ;
	}else{
		set_posh = 0x20 + posy / 8 ;
		set_posl = 0x00 + (0x20*(posy%8)) + posx ;
	}
	set_posx = posx ;
	set_posy = posy ;
	
}
void getAttrPos(unsigned char posx, unsigned char posy)
{
	set_posh = 0x23 ;
	set_posl = 0xC0 + (0x08*(posy/4)) + posx/4 ;
	//set_posl = 0xC0 ;
}

#define attr_pos_offset 0x08
void putStageKomaColor(unsigned char color)
{
	//getStageAttrPos() ;
	update_koma_color[0]=0x23|NT_UPD_HORZ;
	update_koma_color[1]=0x00;
	update_koma_color[2]=1;
	update_koma_color[4]=NT_UPD_EOF;
	set_vram_update(update_koma_color);

	for( i=0; i < 4; i++ ){
		update_koma_color[0]=0x23|NT_UPD_HORZ;
		update_koma_color[1]=attr_pos[x_index][y_index][i]+attr_pos_offset;
		if( (x_index - y_index) % 2 == 0 ){
			if( i == 0 ){ tmp = attr_stat[attr_pos[x_index][y_index][i]-0xC8] ; tmp2 = color==0x55?0b01000000:0b10000000 ; tmp3 = 0b00111111 ;}
			if( i == 1 ){ tmp = attr_stat[attr_pos[x_index][y_index][i]-0xC8] ; tmp2 = color==0x55?0b00010000:0b00100000 ; tmp3 = 0b11001111 ;}
			if( i == 2 ){ tmp = attr_stat[attr_pos[x_index][y_index][i]-0xC8] ; tmp2 = color==0x55?0b00000100:0b00001000 ; tmp3 = 0b11110011 ;}
			if( i == 3 ){ tmp = attr_stat[attr_pos[x_index][y_index][i]-0xC8] ; tmp2 = color==0x55?0b00000001:0b00000010 ; tmp3 = 0b11111100 ;}
			if( color==0x00 ){ tmp2 = 0x00 ;}
			tmp = tmp & tmp3;
			tmp = tmp | tmp2;
			update_koma_color[3] = tmp ;

			attr_stat[attr_pos[x_index][y_index][i]-0xC8] = tmp ;
		}else{
			if( i == 0 ){ tmp = attr_stat[attr_pos[x_index][y_index][i]-0xC8] ; tmp2 = color==0x55?0b00000100:0b00001000 ; tmp3 = 0b11110011 ;}
			if( i == 1 ){ tmp = attr_stat[attr_pos[x_index][y_index][i]-0xC8] ; tmp2 = color==0x55?0b00000001:0b00000010 ; tmp3 = 0b11111100 ;}
			if( i == 2 ){ tmp = attr_stat[attr_pos[x_index][y_index][i]-0xC8] ; tmp2 = color==0x55?0b01000000:0b10000000 ; tmp3 = 0b00111111 ;}
			if( i == 3 ){ tmp = attr_stat[attr_pos[x_index][y_index][i]-0xC8] ; tmp2 = color==0x55?0b00010000:0b00100000 ; tmp3 = 0b11001111 ;}
			if( color==0x00 ){ tmp2 = 0x00 ;}
			tmp = tmp & tmp3;
			tmp = tmp | tmp2;
			update_koma_color[3] = tmp ;

			attr_stat[attr_pos[x_index][y_index][i]-0xC8] = tmp ;
		}
		ppu_wait_frame();
	}
}

void putKomaColor(unsigned char posx, unsigned char posy, unsigned char color )
{
	getAttrPos(posx, posy) ;
	update_koma_color[0]=set_posh|NT_UPD_HORZ;
	update_koma_color[1]=set_posl;
	update_koma_color[2]=1;
	update_koma_color[4]=NT_UPD_EOF;
	set_vram_update(update_koma_color);
	
	update_koma_color[3] = color;

	ppu_wait_frame();
	
}
unsigned char checkPutPos(unsigned char posx, unsigned char posy)
{
	getStagePos(posx, posy) ;
	if( j == 0 ){
		return 1;
	}
	if( stage_stat[x_index][y_index][_KOMA_TYPE] != 0 ){
		return 1 ;
	}
	return 0 ;
}
void putStockKoma(unsigned char posx, unsigned char posy, unsigned char color, unsigned char* meta)
{
	getStagePos(posx, posy) ;
	update_koma[0]=set_posh|NT_UPD_VERT;
	update_koma[1]=set_posl;
	update_koma[2]=4;
	update_koma[7]=set_posh|NT_UPD_VERT;
	update_koma[8]=set_posl+1;
	update_koma[9]=4;
	update_koma[14]=set_posh|NT_UPD_VERT;
	update_koma[15]=set_posl+2;
	update_koma[16]=4;
	update_koma[(3+4)*3]=NT_UPD_EOF;
	set_vram_update(update_koma);

	for( i=0; i<3; i++ ){
		for( j=0; j<4; j++ ){
			update_koma[7*i+j+3] = meta[4*(4*i+j)+2] ;
		}
	}
	ppu_wait_frame();
	// 手持ちコマ用
/*
	if( posy == 26 ){
		tmp = color & 0b11110000 | 0b00000101 ;
		//put_update_debug(NTADR_A(1,24), 3, itoa(posx, &strbuf[0], 10 ));
		//put_update_debug(NTADR_A(4,24), 3, itoa(posy, &strbuf[0], 10 ));
		//put_update_debug(NTADR_A(7,24), 12, itoa(tmp, &strbuf[0], 16 ));
		putKomaColor( posx, posy, tmp ) ;
		putKomaColor( posx, posy+2, color ) ;
	}else{
		putKomaColor( posx, posy, color) ;
	}
*/
	putKomaColor( posx, posy, color) ;
}

void printBar(unsigned int adr, unsigned char action )
{
	update_debug[0]=MSB(adr)|NT_UPD_HORZ;
	update_debug[1]=LSB(adr);
	update_debug[2]=16;
	update_debug[3+16]=NT_UPD_EOF;
	set_vram_update(update_debug);

	memfill( &update_debug[3], 0x00, 16 );
	if( action == 1 ){
		for( i=0; i<16; i++ ){
			if( i == 0 ){ update_debug[i+3] = action == 1 ? 0xDD: 0xED ; }
			else if( i ==15 ){ update_debug[i+3] = action == 1 ? 0xDF: 0xEF ; }
			else { update_debug[i+3] = action == 1 ? 0xDE: 0xEE ; }
		}
	}
	ppu_wait_frame();
}

/*
void initBar()
{
	printBar( NTADR_A(0,29), 0 );
}
*/
void autoPrintBar()
{
//	printBar( NTADR_A(0,29), 0);
	printBar( NTADR_A(whichTurn==0?0:16,29), 0);
	printBar( NTADR_A(whichTurn==1?0:16,29), 1);
}

void putKoma(unsigned char posx, unsigned char posy, unsigned char color, unsigned char* meta)
{
	putStageKomaColor( color ) ;

	getStagePos(posx, posy) ;
	update_koma[0]=set_posh|NT_UPD_VERT;
	update_koma[1]=set_posl;
	update_koma[2]=4;
	update_koma[7]=set_posh|NT_UPD_VERT;
	update_koma[8]=set_posl+1;
	update_koma[9]=4;
	update_koma[14]=set_posh|NT_UPD_VERT;
	update_koma[15]=set_posl+2;
	update_koma[16]=4;
	update_koma[(3+4)*3]=NT_UPD_EOF;
	set_vram_update(update_koma);

	for( i=0; i<3; i++ ){
		for( j=0; j<4; j++ ){
			update_koma[7*i+j+3] = meta[4*(4*i+j)+2] ;

			// 頭被り補正処理.
			//if( checking != 0 ){continue ;}

			if( x_index != 0 && y_index != 0){
				if( j == 0 ){
					if( ChooseKoma >= 4 && ChooseKoma <= 7 ){
						// 被りなしコマ.
						update_koma[7*i+j+3] = 0xD1+i ;
					}else{
						// 被りありコマ. ※左端2マスのみ再描画.
						if( i == 1 ){ continue ; }
						if( ChooseKoma == 0 ){ update_koma[7*i+j+3] = i == 0 ? 0xAA : 0xAA+1 ;}
						if( ChooseKoma == 1 ){ update_koma[7*i+j+3] = i == 0 ? 0xBA : 0xBA+1 ;}
						if( ChooseKoma == 2 ){ update_koma[7*i+j+3] = i == 0 ? 0xAC : 0xAC+1 ;}
						if( ChooseKoma == 3 ){ update_koma[7*i+j+3] = i == 0 ? 0xBC : 0xBC+1 ;}
					}
				}
			}
		}
	}
	ppu_wait_frame();
}

void printCursor()
{
	spr = 0 ;
//	spr = oam_meta_spr( ChooseKoma*32+8, 30+(selBW*170), spr, selBW==0 ? cursor : cursor2  ) ;
//	spr = oam_meta_spr( ChooseKoma*32+8, selBW==0? 30 : 30+170, spr, selBW==0 ? meta_pos1 : meta_pos2  ) ;
	spr = oam_meta_spr( ChooseKoma*32+9, selBW==0? 28-frame%6 : 60-frame%6, spr, selBW==0 ? meta_pos1_reverse : meta_pos2_reverse) ;
	//if( frame&2 ){ oam_hide_rest(spr) ; return ; }
//	spr = oam_meta_spr( ChooseKoma*32+9, selBW==0? 0-frame%6 : 202+frame%6, spr, selBW==0 ? meta_pos1 : meta_pos2  ) ;

}
/*
unsigned char isPadNull()
{
	pad = pad_poll(0);
	if(pad==0){
		moving = 0 ;
		return 1 ;
	}
	return 0 ;
}
*/
unsigned char checkLineQuarto()
{
	if ( q_black == 4 || q_white == 4 || q_high == 4 || q_low == 4 || 
	q_square == 4 || q_circle == 4 || q_plane == 4 || q_dot == 4 ) {
		return 1 ;
	}
	return 0 ;
}
void initQuartoFlg()
{
	q_black =0 ;
	q_white = 0 ;
	q_high = 0 ;
	q_low = 0 ;
	q_square = 0 ;
	q_circle = 0 ;
	q_plane = 0 ;
	q_dot = 0 ;
}
void bitCalc(unsigned char x, unsigned char y)
{
	calc = stage_stat[x][y][_KOMA_TYPE] ; if( calc & 0b10000000 ){ q_black++ ;}
	calc = stage_stat[x][y][_KOMA_TYPE] ; if( calc & 0b01000000 ){ q_high++ ;}
	calc = stage_stat[x][y][_KOMA_TYPE] ; if( calc & 0b00100000 ){ q_square++ ;}
	calc = stage_stat[x][y][_KOMA_TYPE] ; if( calc & 0b00010000 ){ q_plane++ ;}
	calc = stage_stat[x][y][_KOMA_TYPE] ; if( calc & 0b00001000 ){ q_white++ ;}
	calc = stage_stat[x][y][_KOMA_TYPE] ; if( calc & 0b00000100 ){ q_low++ ;}
	calc = stage_stat[x][y][_KOMA_TYPE] ; if( calc & 0b00000010 ){ q_circle++ ;}
	calc = stage_stat[x][y][_KOMA_TYPE] ; if( calc & 0b00000001 ){ q_dot++ ;}
}
unsigned char checkQuarto()
{
	for( i = 0; i < 4; i++ ){
		initQuartoFlg() ;
		for( j = 0; j < 4; j++ ){
			bitCalc(i,j) ;
		}
		if( checkLineQuarto() == 1 ){
			for( j = 0; j < 4; j++ ){
				quarto_line[j][0] = i ;
				quarto_line[j][1] = j ;
			}
			return 1 ;
		}
	}
	for( j = 0; j < 4; j++ ){
		initQuartoFlg() ;
		for( i = 0; i < 4; i++ ){
			bitCalc(i,j) ;
		}
		/*
		if( j == 3 ){
			put_update_debug(1,11, 3, itoa(q_black, &strbuf[0], 10 ));
			put_update_debug(4,11, 3, itoa(q_high, &strbuf[0], 10 ));
			put_update_debug(7,11, 3, itoa(q_square, &strbuf[0], 10 ));
			put_update_debug(10,11, 3, itoa(q_plane, &strbuf[0], 10 ));
			put_update_debug(13,11, 3, itoa(q_white, &strbuf[0], 10 ));
			put_update_debug(16,11, 3, itoa(q_low, &strbuf[0], 10 ));
			put_update_debug(19,11, 3, itoa(q_circle, &strbuf[0], 10 ));
			put_update_debug(22,11, 3, itoa(q_dot, &strbuf[0], 10 ));
		}
		*/
		if( checkLineQuarto() == 1 ){
			for( i = 0; i < 4; i++ ){
				quarto_line[i][0] = i ;
				quarto_line[i][1] = j ;
			}
			return 1 ;
		}
	}

	// クロス縦.
	initQuartoFlg() ;
	for( i = 0; i < 4; i++ ){
		bitCalc(i,i) ;
	}
	if( checkLineQuarto() == 1 ){
		for( i = 0; i < 4; i++ ){
			quarto_line[i][0] = i ;
			quarto_line[i][1] = i ;
		}
		return 1 ;
	}

	// クロス横.
	initQuartoFlg() ;
	for( i = 0; i < 4; i++ ){
		bitCalc(i,3-i) ;
	}
	if( checkLineQuarto() == 1 ){
		for( i = 0; i < 4; i++ ){
			quarto_line[i][0] = i ;
			quarto_line[i][1] = 3-i ;
		}
		return 1 ;
	}

	return 0 ;
}

void moveKoma(unsigned char src_x, unsigned char src_y, unsigned char dst_x, unsigned char dst_y, unsigned char* meta )
{
	// 2単位で増減するので、src,dstどこかが奇数となると無限ループする.
	koma_x[0] = src_x % 2 == 0 ? src_x : src_x-1 ;
	koma_y[0] = src_y % 2 == 0 ? src_y : src_y-1 ;
	dst_x = dst_x % 2 == 0 ? dst_x : dst_x-1 ;
	dst_y = dst_y % 2 == 0 ? dst_y : dst_y-1 ;
	
	while(1){
		koma_frame++ ;
		if( koma_frame % 5 != 0 ){ continue ; }
		//ppu_wait_frame();
		spr = 0 ;
		spr = oam_meta_spr( koma_x[0], koma_y[0], spr, meta ) ;

		if( koma_y[0] > dst_y ){ koma_y[0]-=2; }
		else if( koma_y[0] < dst_y ){ koma_y[0]+=2; }
		else if( koma_x[0] > dst_x ){ koma_x[0]-=2; }
		else if( koma_x[0] < dst_x ){ koma_x[0]+=2; }

		if( koma_x[0] == dst_x && koma_y[0] == dst_y ){ 
			break ;
		}

	}
	x = dst_x ;
	y = dst_y ;
	ppu_wait_frame();
}
/*
void stageAnime(unsigned char action)
{
	spr = 0 ;
	for( i = 0; i < 32 ; i++ ){
		for( x = 0; x < 4 ; x++ ){
			for( y = 0; y < 4 ; y++ ){
				spr = oam_meta_spr( (x*32)-(y*32)+117-i, (y*16)+(x*16)+79, spr, meta_mask ) ;
			}
		}
		if( action == 0 ){
			return ;
		}
	}
}
*/
void printTimerInit()
{
	put_update_debug(2,25, 3, "   " );
	put_update_debug(28,25,  3, "   " );
}
void printTimer()
{
	printTimerInit() ;
	if( timerSetCount != 0 ){
		put_update_debug(whichTurn!=0?2:28,25, 3, itoa(timer, &strbuf[0], 10 ) );
	}
}

/*
void offStageDraw()
{
	for( k = 1; k < 4; k++ ){
		for( l = 1; l < 4; l++ ){
			if( stage_stat[k][l][_KOMA_TYPE] != 0 ){
				ChooseKoma = stage_stat[k][l][_CHOOSE_KOMA] ;
				selBW = stage_stat[k][l][_SEL_BW] ;
				x = (k*32)-(l*32)+115+16 ;
				y = (l*16)+(k*16)+71-16 ;
				putKoma( x/8, y/8, selBW==0?0xAA:0x55, (unsigned char*)koma_list[0][0][ChooseKoma] ) ;
			}
		}
	}
}
*/
void animeKomaTurnOff()
{
	bank_bg(0);
	pal_bg((char*)bg_palettes[bgpl]);
	pal_spr((char*)bg_palettes[bgpl]);

}
void animeKomaTurn(unsigned char speed)
{
//	checking = 1 ;
//	pal_bg((char*)bg_palettes2[0]);
//	offStageDraw();

//	for( i = 0; i < 5; i++){
	
	if( frame % 4 == 0 ){
		bank_bg(0);
		pal_bg((char*)bg_palettes2[0]);
	}
	if( frame % 4 == 1 ){
		bank_bg(1);
		pal_bg((char*)bg_palettes2[1]);
		//delay(1) ;
	}
	if( frame % 4 == 2 ){
		pal_bg((char*)bg_palettes2[2]);
		//delay(2) ;
	}
	if( frame % 4 == 3 ){
		pal_bg((char*)bg_palettes2[3]);
		//delay(1) ;
	}
	delay(speed) ;

//	checking = 0 ;
//	offStageDraw() ;

}
void initMsg()
{
	//initBar() ;
	//printTimerInit() ;
	put_update_debug(1,28, 14, (const char*)msgBlank );
	put_update_debug(17,28, 14, (const char*)msgBlank );
}
void printMsg(unsigned char action)
{
	autoPrintBar();

	if( action == 0 ){
		put_update_debug(1,28, 14, whichTurn!=0?"P1:SELECT NEXT":(const char*)msgBlank );
		put_update_debug(17,28, 14, whichTurn==0?"P2:SELECT NEXT":(const char*)msgBlank );

	}else if( action == 1 ){
		put_update_debug(1,28, 14, whichTurn!=0?"P1:PLAYING    ":(const char*)msgBlank );
		put_update_debug(17,28, 14, whichTurn==0?"P2:PLAYING    ":(const char*)msgBlank );
		printTimer() ;
	}
/*
	else if( action == 2 ){
		put_update_debug(1,24, 14, whichTurn!=0?"P1:WIN!       ":(const char*)msgBlank );
		put_update_debug(1,5, 14, whichTurn==0?"P2:WIN!       ":(const char*)msgBlank );
	}
*/

}
void initLife()
{
	put_update_debug(1,27, 3, "   " );
	put_update_debug(25,27, 3,  "   " );
}
void printLife()
{
	put_update_debug(1,27, 3, err[1] == 0 ? "   ": err[1] == 1 ?"X  ": err[1] == 2 ?"XX ": "XXX" );
	put_update_debug(25,27, 3, err[0] == 0 ? "   ": err[0] == 1 ?"X  ": err[0] == 2 ?"XX ": "XXX" );
}
void loseAnime()
{
	oam_clear() ;
	ppu_off() ;
	delay(60) ;

	bank_bg(1);
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_unrle((unsigned char*)jeesus);
	pal_bg(palette_jeesus);
	ppu_on_all();//enable rendering

	music_play(3) ;
	delay(90);
	music_stop() ;
	bank_bg(0);

	reset() ;

}
void procSayQuarto(){
	oam_clear() ;
	initMsg() ;
	initLife() ;
	printTimerInit() ;
	
	music_play(2) ;

//	tmp = rand8() ;
//	tmp2 = rand8() ;
//	tmp3 = rand8() ;
//	tmp4 = rand8() ;
	for( i=0 ; i< 20; i++ ){
		animeKomaTurn(2) ;

		//x-=4 ;
		spr = 0 ;
		spr = oam_meta_spr( 100, 80, spr, meta_quarto) ;
//		spr = oam_meta_spr( x + 0, 80, spr, meta_quarto) ;
//		spr = oam_meta_spr( x + 30, 60, spr, meta_quarto) ;
//		spr = oam_meta_spr( x + 60, 80, spr, meta_quarto) ;
//		spr = oam_meta_spr( x + 90, 100, spr, meta_quarto) ;
		cycleSprColor() ;
		frame++ ;
	}
	oam_clear() ;
	animeKomaTurnOff() ;
	delay(20) ;
	music_stop() ;
}
void timerSet()
{
	if( frame % 50 == 0 && autoChoose!=1 && timerSetCount != 0 ){
		timer--;
		printTimer() ;
		if( timer == 0 ){
			autoChoose=1;
			sfx_play(3,0);
			//err[whichTurn==0?1:0]++ ;
			//printLife() ;
			timer = timerSetCount ;
		}
		frame=0 ;
	}
}
unsigned char preQuartoCheck(unsigned char x, unsigned char y )
{
	tmp3 = 0 ;
	stage_stat[x][y][_KOMA_TYPE] = selBW==0 ? koma_type[1+ChooseKoma] : koma_type[1+ChooseKoma+8] ;
	stage_stat[x][y][_CHOOSE_KOMA] = ChooseKoma ;
	stage_stat[x][y][_SEL_BW] = selBW ;
	if( checkQuarto() == 1 ){
		tmp3 = 1 ;
	}else{
		tmp3 = 0 ;
	}
	stage_stat[x][y][_KOMA_TYPE] = 0 ;
	stage_stat[x][y][_CHOOSE_KOMA] = 0 ;
	stage_stat[x][y][_SEL_BW] = 0 ;
	return tmp3 ;
}
unsigned char dieCheck(){
	for( k = 0; k < 4; k++ ){
		for( l = 0; l < 4; l++ ){
			if( stage_stat[k][l][_KOMA_TYPE] == 0 ){
				if( preQuartoCheck( k, l ) == 1 ){
					return 1 ;
				}
			}
		}
	}
	return 0 ;
}

void eventChooseButtonA(void)
{
	koma_exist[selBW][ChooseKoma] = 0 ;
	putStockKoma((ChooseKoma*4),selBW==0?0:4, selBW==0?0x00:0xFF,  (unsigned char*)koma_list[0][0][ChooseKoma]) ;

	oam_clear() ;
	//spr = 0 ;
	x = ChooseKoma*32 ;
	y = 10+selBW*32 ;
	moveKoma( x, y, whichTurn==0?24:200, 70, (unsigned char*)koma_list[0][selBW==0?1:0][ChooseKoma] ) ;
	//spr = oam_meta_spr( x, y, spr, koma_list[0][selBW==0?1:0][ChooseKoma] ) ;
	ppu_wait_frame();	// wait for next TV frame
	
	sfx_play(5,1);

	whichTurn = whichTurn == 0? 1:0 ;
	timer = timerSetCount ;
	
	printMsg(1);
}
void procChooseKoma(void)
{
	printMsg(0) ;
	printLife() ;

//	timer = 5;
//	printTimer() ;
	//timer = timerSetCount ;
	//autoChoose=0;
	while(1)
	{
		printCursor() ;
		timerSet() ;
		// カーソルセレクト
		//isPadNull() ;
		pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ;
		if( isVsCPU != 0 && whichTurn==0 ){
			pad=0 ;
			autoChoose = 1 ;
		} ;

		if(pad&PAD_LEFT){
			//frame = 0 ;
			ChooseKoma = ChooseKoma <= 0 ? 7 : --ChooseKoma ;
			printCursor() ;
			for( ;pad&PAD_LEFT ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
				ppu_wait_frame();	// wait for next TV frame
				frame++ ;
				timerSet() ;
				printCursor() ;
				if( autoChoose==1){break ;}
			}
		}
/*
			if( moving == 0 || moving == 2 ){
				//for( i = 0 ; isPadNull() != 1 && i < 25; i++ ){
				for( i = 0; i < 25 &&  pad&PAD_LEFT ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
					i++ ;
					//delay(1) ;
					ppu_wait_frame();	// wait for next TV frame
					frame++ ;
					timerSet() ;
				}
			}else{
				delay(5) ;
			}
			moving = 1 ;
		}
*/

		if(pad&PAD_RIGHT){
			//frame = 0 ;
			ChooseKoma = ChooseKoma >= 7 ? 0 : ++ChooseKoma ;
			printCursor() ;
			for( ;pad&PAD_RIGHT ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
				ppu_wait_frame();	// wait for next TV frame
				frame++ ;
				timerSet() ;
				printCursor() ;
				if( autoChoose==1){break ;}
			}
		}
/*
			if( moving == 0 || moving == 1 ){
				//for( i = 0 ; isPadNull() != 1 && i < 25; i++ ){
				for( i = 0; i < 25 && pad&PAD_RIGHT ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
					i++ ;
					//delay(1) ;
					ppu_wait_frame();	// wait for next TV frame
					frame++ ;
					timerSet() ;
				}
			}else{
				delay(5) ;
			}
			moving = 2 ;
		}
*/
		if(pad&PAD_UP){
			selBW = 0 ;
			//printCursor() ;
		}
		if(pad&PAD_DOWN){
			selBW = 1 ;
			//printCursor() ;
		}

		if(pad&PAD_A){
			if( koma_exist[selBW][ChooseKoma] == 0 ){
				sfx_play(3,0);

				for( ; pad&PAD_A ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
					delay(1) ;
				}
				continue ;
			}
			
			tmp = pad_poll(1) ;
			if( tmp&PAD_SELECT && dieCheck() == 1 ){
				sfx_play(3,0);
				continue ;
			}
			eventChooseButtonA() ;
			return ;
			
		}

		if(pad&PAD_SELECT){
			cycleNextColor() ;
			for( ; pad&PAD_SELECT ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
				delay(1) ;
			}
		}
		
		if(pad&PAD_START){
			procSayQuarto() ;

			if( checkQuarto() == 1 ){
				quarto = 1 ;
				return ;
			}else{
				sfx_play(3,1);
				music_play(game_music) ;
				err[whichTurn]++ ;
				if( err[whichTurn] == 3 ){
					loseAnime() ;
				}
				
			}
			printLife() ;
			printMsg(0) ;
			for( ; pad&PAD_START ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
				delay(1) ;
			}
			continue ;
		}
		if( autoChoose==1){
			oam_clear() ;
			// 自動コマ選択.
			seedRandBox() ;

			if( isVsCPU != 1 && koma_exist[selBW][ChooseKoma] != 0 ){
				
			}else{
				isForceFin = 1 ;
				tmp = 0 ;
				for( m=0; m<2; m++){
					for( n=0; n<8; n++){
						if( koma_exist[rand_box3[m]][rand_box4[n]] == 1 ){

							selBW = rand_box3[m];
							ChooseKoma = rand_box4[n];
							isForceFin = 0 ;

							//printCursor() ;
							//sfx_play(3,1) ;

							if( isVsCPU == 1 && reach == 1 && dieCheck() == 1){
								continue ;
							}
							//put_update_debug(1,10, 1, itoa(selBW, &strbuf[0], 10 ));
							//put_update_debug(4,10, 1, itoa(ChooseKoma, &strbuf[0], 10 ));
							tmp = 1 ;
							break ;
						}
					}
					if( tmp == 1 ){ break ; }
				}
				if( isForceFin == 1 ){
					loseAnime() ;
					return ;
				}
			}
			printCursor() ;
			
			eventChooseButtonA() ;
			return ;
			
		}

		ppu_wait_frame();	// wait for next TV frame
		frame++;
	}
}

unsigned char checkReach()
{
	for( k = 0; k < 4; k++ ){
		tmp = 0 ; // X軸3連チェック用.
		tmp2 = 0 ; // Y軸3連チェック用.
		for( l = 0; l < 4; l++ ){
			// X軸検索.
			if( stage_stat[k][l][_KOMA_TYPE] != 0 ){
				tmp++ ;
				if( tmp >= 3 ){
					reach = 1 ;
				}	
			}
			// Y軸検索.
			if( stage_stat[l][k][_KOMA_TYPE] != 0 ){
				tmp2++ ;
				if( tmp2 >= 3 ){
					reach = 1 ;
				}
			}
		}
	}

	tmp = 0 ;
	tmp2 = 0 ;
	for( k = 0; k < 4; k++ ){
		// X軸クロス検索.
		if( stage_stat[k][k][_KOMA_TYPE] != 0 ){
			tmp++ ;
			if( tmp >= 3 ){
				reach = 1 ;
			}
		}
		// Y軸クロス検索.
		if( stage_stat[k][3-k][_KOMA_TYPE] != 0 ){
			tmp2++ ;
			if( tmp2 >= 3 ){
				reach = 1 ;
			}
		}
	}

}
eventMoveButtonA()
{
	putKoma( x/8, y/8, selBW==0?0xAA:0x55, (unsigned char*)koma_list[0][0][ChooseKoma] ) ;
	/*
	put_update_debug(1,10, 1, itoa(x_index, &strbuf[0], 10 ));
	put_update_debug(4,10, 1, itoa(y_index, &strbuf[0], 10 ));
	*/
	stage_stat[x_index][y_index][_KOMA_TYPE] = selBW==0 ? koma_type[1+ChooseKoma] : koma_type[1+ChooseKoma+8] ;
	stage_stat[x_index][y_index][_CHOOSE_KOMA] = ChooseKoma ;
	stage_stat[x_index][y_index][_SEL_BW] = selBW ;
	oam_clear() ;
	
	//putStageKomaColor( x/8, y/8, selBW==0?0xAA:0x55 ) ;
	
	//putStageColor( set_posx, set_posy ) ;
	sfx_play(4,1);
	
	//initBar() ;
	printMsg(0) ;

	checkReach() ;
	if( reach == 1 && game_music != 4 ){
		game_music = 4 ;
		music_stop() ;
		//bgFlash(8) ;
		delay(30) ;
		music_play(game_music) ;
	}

}
void autoSetXY()
{
	m = 0 ;
	n = 0 ;
	
	for( k=0; k<4; k++){
		o = rand_box1[k] ;
		for( l=0; l<4; l++){
			p = rand_box2[l] ;

			x = (o*32)-(p*32)+115+16 ;
			y = (p*16)+(o*16)+101-16 ;
			
			// 仮保存(全クアルトチェック後に返す奴).
			//put_update_debug(1,10, 1, itoa(x, &strbuf[0], 10 ));
			//put_update_debug(4,10, 1, itoa(y, &strbuf[0], 10 ));
			if( checkPutPos(x/8, y/8) == 1 ){
				continue ;
			}
			m = x ;
			n = y ;

			if( isVsCPU == 1 && whichTurn==0 && preQuartoCheck(o, p) == 0 ){
				continue ; 
			}
			return ;
		}
	}
	if( m == 0 && n == 0 ){
		isForceFin = 1 ;
		
	}else{
		// 仮保存の座標を戻す.
		x = m ;
		y = n ;
		checkPutPos(x/8, y/8) ;
	}
}

void procMoveKoma(void)
{
	
	for( ; pad&PAD_A ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
		delay(1) ;
	}

//	timer = setCount ;
	//printTimer() ;
	//timer = timerSetCount ;
	autoChoose=0;
	while(1)
	{
		timerSet() ;

		//delay(1) ;
		//isPadNull() ;
		pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ;
		if( isVsCPU != 0 && whichTurn==0 ){
			pad=0  ;
			autoChoose = 1 ;
		} ;

		if(pad&PAD_LEFT){
			if( x > 4 ){
				x-= pad&PAD_B ? 4 : 2 ;
			}
		}
		if(pad&PAD_RIGHT){
			if( x < 232){
				x+= pad&PAD_B ? 4 : 2 ;
			}
		}
		if(pad&PAD_UP){
			if( y > 4 ){
				y-= pad&PAD_B ? 2 : 1 ;
			}
		}

		if(pad&PAD_DOWN){
			if( y < 212){
				y+= pad&PAD_B ? 2 : 1 ;
			}
		}
		if(pad&PAD_A){
			if( checkPutPos(x/8, y/8) == 1 ){
				sfx_play(3,0);
				
				for( ; pad&PAD_A ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
					ppu_wait_frame();
					frame++ ;
					//delay(1) ;
				}
			}else{
				eventMoveButtonA();
				return ;
			}
			
		}
		if(pad&PAD_SELECT){
			cycleNextColor() ;
			for( ; pad&PAD_SELECT ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
				delay(1) ;
			}

			/*
			oam_clear() ;
			printCursor() ;

			koma_exist[selBW][ChooseKoma] = 1 ;
			putStockKoma((ChooseKoma*4),selBW==0?0:26, selBW==0?0xAA:0x55, (unsigned char*)koma_list[0][0][ChooseKoma]) ;
			whichTurn = whichTurn == 0? 1:0 ;
			timer = timerSetCount ;

			sfx_play(6,0);
			
			//initBar();
			printMsg(0) ;

			return ;
			*/
		}

		if(pad&PAD_START){
			procSayQuarto() ;

			if( checkQuarto() == 1 ){
				quarto = 1 ;
				return ;
			}else{
				sfx_play(3,1);
				music_play(game_music) ;
				err[whichTurn]++ ;
				if( err[whichTurn] == 3 ){
					loseAnime() ;
				}
			}
			printLife() ;
			printMsg(1) ;
			for( ; pad&PAD_START ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
				delay(1) ;
			}
			continue ;
		}
		if( autoChoose==1){
			// 自動コマ配置.
			if( isVsCPU == 1 && whichTurn==0 && checkQuarto() == 1 ){
				procSayQuarto() ;
				quarto = 1 ;
				return ;
			}

			tmp_x = x;
			tmp_y = y ;

			// CPU戦の場合ここでクアルトを狙う.
			seedRandBox() ;
			autoSetXY();
			if( isForceFin == 1 ){
				loseAnime() ;
				return ;
			}
			oam_clear() ;
			moveKoma( tmp_x, tmp_y, x-9, y-12, (unsigned char*)koma_list[0][selBW==0?1:0][ChooseKoma] ) ;

			eventMoveButtonA() ;
			if( isVsCPU == 1 && whichTurn==0 && checkQuarto() == 1 ){
				procSayQuarto() ;
				quarto = 1 ;
				return ;
			}

			return ;
			
		}
		
		ppu_wait_frame();	// wait for next TV frame
		frame++;

		oam_clear() ;
		spr = 0 ;
		if( checkPutPos(x/8, y/8) != 1 ){
			spr = oam_meta_spr( set_posx*8+8, set_posy*8+(frame%8)+10, spr, selBW==0?meta_pos1: meta_pos2 ) ;
		}
		spr = oam_meta_spr( x, y, spr, koma_list[koma_exist[selBW][ChooseKoma]][selBW==0?1:0][ChooseKoma] ) ;
			
	}
}
void procCheckQuarto(){
	if( quarto != 0 ){
		music_stop() ;
		initLife() ;
		initMsg() ;
		oam_clear() ;
		delay(40) ;
		bgFlash(8) ;
		delay(40) ;
		music_play(0) ;

		//initBar();
		//printMsg(2) ;

		tmp = rand8() ;
		tmp2 = rand8() ;
		tmp3 = rand8() ;
		tmp4 = rand8() ;
		while(1){
			//x-=4 ;
			spr = 0 ;
			//spr = oam_meta_spr( x + tmp, 20, spr, meta_quarto) ;
			//spr = oam_meta_spr( x + tmp2, 40, spr, meta_quarto) ;
			//spr = oam_meta_spr( x + tmp3, 180, spr, meta_quarto) ;
			//spr = oam_meta_spr( x + tmp3, 200, spr, meta_quarto) ;
			//spr = oam_meta_spr( x + tmp2, 100, spr, whichTurn!=0?meta_p1win:meta_p2win) ;
			//spr = oam_meta_spr( x + tmp4, 140, spr, whichTurn!=0?meta_p1win:meta_p2win) ;
			for( i = 0; i < 4; i++ ){
				k = (quarto_line[i][0]*32)-(quarto_line[i][1]*32)+115+14 ;
				l = (quarto_line[i][1]*16)+(quarto_line[i][0]*16)+101-32 ;
				spr = oam_meta_spr( k, l+frame%5, spr, meta_pos2) ;
			}

			if( frame & 2 ){
				spr = oam_meta_spr( whichTurn!=0?10:190 ,70, spr, whichTurn!=0?meta_p1win:meta_p2win);
			}else{ 
				oam_hide_rest(spr) ; 
			}

			cycleSprColor() ;
			//delay(2);

			animeKomaTurn(4) ;
			frame++ ;

			pad=pad_poll(0);
			if( pad&PAD_START ){
				oam_clear() ;

				for( i=0 ; i< 5; i++ ){
					animeKomaTurn(4) ;
					frame++ ;
				}
				music_play(2) ;
				for( i=0 ; i< 10; i++ ){
					animeKomaTurn(2) ;
					frame++ ;
				}
				for( i=0 ; i< 25; i++ ){
					animeKomaTurn(1) ;
					scroll(0,i*10) ;
					frame++ ;
				}
				music_stop() ;
				animeKomaTurnOff() ;
				reset() ;
			}
			continue ;
		}
	}
}
void initVal(){
	//update_init() ;
	//set initial coords
	autoChoose = 0 ;
	p1only=1;
	isVsCPU=1;
	isForceFin = 0 ;
	timerSetCount = 60 ;
	quarto = 0 ;
	ChooseKoma = 0;
	whichTurn = 1;
	selBW = 0;
	koma_pos[0]=3;
	koma_pos[1]=1;
	x=0;
	y=0;
	koma_x[0] = 72 ;
	koma_y[0] = 122 ;
	koma_x[1] = 152 ;
	koma_y[1] = 122 ;

	timer = 0 ;

	game_music = 1; // 1:game1, 4:game2
	reach = 0 ;

	//init other vars
	
	tmp = 0 ;	//collision flag
	frame = 0 ;	//frame counter

	for( i=0; i < 40; i++ ){
		attr_stat[i] = 0x55 ;
	}
	err[0]=0;
	err[1]=0;

//	memfill(attr_stat, 0x55, 40 ) ;
}

// ========================================================================================
// ========================================================================================
void reset(void)
{
	scroll(0,0);
	initVal() ;

	oam_clear() ;
	ppu_off() ;
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_unrle((unsigned char*)menu);
	pal_bg((char*)bg_palettes[bgpl]);
	ppu_on_all();//enable rendering

	// MODE SELECT.
	put_update_debug(16,17, 3, "   ");
	put_update_debug(16,17, 3, itoa(timerSetCount, &strbuf[0], 10 ));
	while(1){
		pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ;
		if(pad&PAD_UP && p1only == 0){
			p1only = 1 ;
			isVsCPU = 1 ;
			sfx_play(2,0);
		}

		if(pad&PAD_DOWN && p1only == 1){
			p1only = 0 ;
			isVsCPU = 0 ;
			sfx_play(2,0);
		}
		if(pad&PAD_A){
			sfx_play(5,0);
			for( ; pad&PAD_A ;pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ){
				delay(1) ;
			}
			break ;
		}
		spr = 0 ;
		spr = oam_meta_spr( 70, 63+(p1only==1?0:1*16), spr, meta_right_cursor) ;
		frame++ ;
	}
	seedRandBox() ;
/*
	put_update_debug(1,50, 1, itoa(rand_box1[0], &strbuf[0], 10 ));
	put_update_debug(3,50, 1, itoa(rand_box1[1], &strbuf[0], 10 ));
	put_update_debug(5,50, 1, itoa(rand_box1[2], &strbuf[0], 10 ));
	put_update_debug(7,50, 1, itoa(rand_box1[3], &strbuf[0], 10 ));
	put_update_debug(1,51, 1, itoa(rand_box2[0], &strbuf[0], 10 ));
	put_update_debug(3,51, 1, itoa(rand_box2[1], &strbuf[0], 10 ));
	put_update_debug(5,51, 1, itoa(rand_box2[2], &strbuf[0], 10 ));
	put_update_debug(7,51, 1, itoa(rand_box2[3], &strbuf[0], 10 ));
*/	
	spr = 0 ;
	spr = oam_meta_spr( 70, 135, spr, meta_right_cursor) ;
	while(1){
		pad=pad_poll((whichTurn!=0 || p1only==1)?0:1) ;
		if(pad&PAD_UP&& timerSetCount<=200){
			timerSetCount+= pad&PAD_B?10:1 ;

			if( timerSetCount < 3 ){ timerSetCount=3 ;} ;

			put_update_debug(16,17, 3, "   ");
			put_update_debug(16,17, 3, itoa(timerSetCount, &strbuf[0], 10 ));
			sfx_play(2,0);
			delay(2) ;
		}

		if(pad&PAD_DOWN&&timerSetCount>3){
			tmp = pad&PAD_B?10:1;
			if( timerSetCount <= tmp ){ 
				timerSetCount = 3 ;
			}else{
				timerSetCount-= tmp ;
			}
			put_update_debug(16,17, 3, "   ");
			put_update_debug(16,17, 3, itoa(timerSetCount, &strbuf[0], 10 ));
			sfx_play(2,0);
			delay(2) ;
		}
		if(pad&PAD_RIGHT && timerSetCount!=0){
			timerSetCount = 0 ;
			put_update_debug(16,17, 3, "OFF");
			sfx_play(2,0);
			delay(2) ;
		}
		if(pad&PAD_A){
			sfx_play(5,0);
			break ;
		}
	}
	timer=timerSetCount;
	
	oam_clear() ;
	pal_spr((char*)bg_palettes[bgpl]);//set background palette from an array
	pal_bg((char*)bg_palettes[bgpl]);//set background palette from an array

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

	stageAnime(0) ;
	ppu_on_all();//enable rendering
	delay(1) ;

	stageAnime(1) ;
//	sfx_play(3,0);
	oam_clear() ;
*/
	

	delay(15) ;
	for( x = 0; x < 8; x++ ){
		sfx_play(2,0);
		// P1
		putStockKoma(x*4,0,0xAA, (unsigned char*)koma_list[0][0][x]) ;
		sfx_play(2,1);
		// P2
//		putStockKoma(28-(x*4),26,0x55, (unsigned char*)koma_list[0][1][7-x]) ;
		//if( x == 4 ){continue; }
		putStockKoma(x*4,4,0x55, (unsigned char*)koma_list[0][1][x]) ;


	}
	update_init() ;
	for( tmp=0; tmp < 16; tmp++ ){
		up_stage(stage_anime_index[tmp][0], stage_anime_index[tmp][1] );
	}

	memfill( stage_stat, 0x00, 48 );
	memfill( koma_exist, 0x01, 16 );
	memfill( quarto_line, 0x00, 8 );

	music_play(game_music) ;


	delay(10) ;
/*
	spr = 0 ;
	spr = oam_meta_spr( ChooseKoma*32+8, 40+selBW*50, spr, selBW==0 ? cursor : cursor2 ) ;
*/
	while(1)
	{
		delay(10) ;

		procChooseKoma() ;
		procCheckQuarto() ;

		procMoveKoma() ;
		procCheckQuarto() ;
	}
}

// ========================================================================================
// ========================================================================================
void main(void)
{
	initVal() ;

#ifndef debug
	pal_spr((char*)palette2);
	pal_bg((char*)open_palette1);//set background palette from an array

	vram_adr(NAMETABLE_A);//set VRAM address
	vram_unrle((unsigned char*)open_name);
	vram_adr(NAMETABLE_A);//set VRAM address
	vram_fill(0x00, 0x0180);
	spr = 0 ;

	pal_bright(0);
	ppu_on_all();//enable rendering
	delay(20) ;

	bgUp() ;
	delay(20) ;
	tmp = 0 ;

	while(1)
	{
		if(frame%20==0){ move_next(); };

		frame++;

		if( checkForceBreak() ){ break ; }

	}
	bgpl = 0;

	// QRコード処理.
	pad = pad_poll(0);
	if(pad&PAD_SELECT ){

		ppu_off() ;
		bank_bg(1);
		oam_clear() ;
		vram_adr(NAMETABLE_A);//set VRAM address
		vram_unrle((unsigned char*)qr);
		ppu_on_all();//enable rendering

		while(1){
			for( ; pad&PAD_SELECT ;pad=pad_poll(0) ){
				delay(1) ;
			}
			break ;
		}

		while(1){
			pad = pad_poll(0);
			if(pad&PAD_SELECT ){
				bank_bg(0);
				reset() ;
			}
		}
	}

	ppu_off() ;
	delay(10) ;

	music_play(2) ;
	delay(60) ;
	music_stop() ;

#endif
/*
	//sfx_play(2,0);
	oam_clear() ;
	for( y = 0; y < 250; y++ ){
		scroll(0,y) ;
		if( frame % 10 == 0 ){ppu_wait_nmi();}
		frame++ ;
	}
*/
	while(1){
		reset() ;
	}
}