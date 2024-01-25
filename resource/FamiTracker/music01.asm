;this file for FamiTone2 library generated by text2data tool

music01_music_data:
	.db 1
	.dw .instruments
	.dw .samples-3
	.dw .song0ch0,.song0ch1,.song0ch2,.song0ch3,.song0ch4,409,341

.instruments:
	.db $30 ;instrument $00
	.dw .env1,.env0,.env0
	.db $00
	.db $b0 ;instrument $01
	.dw .env1,.env0,.env0
	.db $00
	.db $30 ;instrument $02
	.dw .env2,.env0,.env0
	.db $00

.samples:
.env0:
	.db $c0,$00,$00
.env1:
	.db $c1,$c3,$c6,$ca,$cf,$00,$04
.env2:
	.db $cf,$00,$00


.song0ch0:
	.db $fb,$07
.song0ch0loop:
.ref0:
	.db $82,$44,$46,$44,$46,$44,$00,$3e,$00,$40,$00,$44,$00,$4a,$00,$4e
	.db $00
.ref1:
	.db $4b,$45,$41,$3f,$41,$39,$3a,$85
.ref2:
	.db $44,$46,$44,$46,$44,$00,$3e,$00,$40,$00,$44,$00,$4a,$00,$4e,$00
.ref3:
	.db $51,$53,$55,$57,$59,$53,$4b,$00,$81
	.db $fd
	.dw .song0ch0loop

.song0ch1:
.song0ch1loop:
.ref4:
	.db $9f
.ref5:
	.db $9f
.ref6:
	.db $9f
.ref7:
	.db $9f
	.db $fd
	.dw .song0ch1loop

.song0ch2:
.song0ch2loop:
.ref8:
	.db $84,$33,$3a,$00,$40,$00,$83,$46,$00,$83,$44,$00,$83
.ref9:
	.db $40,$00,$3e,$00,$40,$00,$83,$38,$00,$3a,$00,$38,$00,$3a,$00
.ref10:
	.db $33,$3a,$00,$40,$00,$83,$46,$00,$83,$44,$00,$83
	.db $ff,$0f
	.dw .ref9
	.db $fd
	.dw .song0ch2loop

.song0ch3:
.song0ch3loop:
.ref12:
	.db $9f
.ref13:
	.db $9f
.ref14:
	.db $9f
.ref15:
	.db $9f
	.db $fd
	.dw .song0ch3loop

.song0ch4:
.song0ch4loop:
.ref16:
	.db $9f
.ref17:
	.db $9f
.ref18:
	.db $9f
.ref19:
	.db $9f
	.db $fd
	.dw .song0ch4loop