;this file for FamiTone2 library generated by text2data tool

pentup_music_data:
	db 5
	dw @instruments
	dw @samples-3
	dw @song0ch0,.song0ch1,.song0ch2,.song0ch3,.song0ch4,307,256
	dw @song1ch0,.song1ch1,.song1ch2,.song1ch3,.song1ch4,337,281
	dw @song2ch0,.song2ch1,.song2ch2,.song2ch3,.song2ch4,307,256
	dw @song3ch0,.song3ch1,.song3ch2,.song3ch3,.song3ch4,215,179
	dw @song4ch0,.song4ch1,.song4ch2,.song4ch3,.song4ch4,307,256

@instruments:
	db $30 ;instrument $00
	dw @env5,.env0,.env0
	db $00
	db $b0 ;instrument $01
	dw @env1,.env0,.env0
	db $00
	db $30 ;instrument $07
	dw @env2,.env9,.env0
	db $00
	db $70 ;instrument $08
	dw @env6,.env0,.env0
	db $00
	db $30 ;instrument $09
	dw @env3,.env0,.env11
	db $00
	db $30 ;instrument $0a
	dw @env4,.env0,.env12
	db $00
	db $70 ;instrument $0b
	dw @env7,.env0,.env0
	db $00
	db $b0 ;instrument $0c
	dw @env8,.env0,.env0
	db $00
	db $b0 ;instrument $0d
	dw @env1,.env9,.env10
	db $00

@samples:
	db $00+<(FT_DPCM_PTR),$00,$00	;1
	db $00+<(FT_DPCM_PTR),$00,$00	;2
	db $00+<(FT_DPCM_PTR),$00,$00	;3
	db $00+<(FT_DPCM_PTR),$00,$00	;4
	db $00+<(FT_DPCM_PTR),$00,$00	;5
	db $00+<(FT_DPCM_PTR),$00,$00	;6
	db $00+<(FT_DPCM_PTR),$00,$00	;7
	db $00+<(FT_DPCM_PTR),$00,$00	;8
	db $00+<(FT_DPCM_PTR),$00,$00	;9
	db $00+<(FT_DPCM_PTR),$00,$00	;10
	db $00+<(FT_DPCM_PTR),$00,$00	;11
	db $00+<(FT_DPCM_PTR),$00,$00	;12
	db $00+<(FT_DPCM_PTR),$00,$00	;13
	db $00+<(FT_DPCM_PTR),$00,$00	;14
	db $00+<(FT_DPCM_PTR),$00,$00	;15
	db $00+<(FT_DPCM_PTR),$00,$00	;16
	db $00+<(FT_DPCM_PTR),$00,$00	;17
	db $00+<(FT_DPCM_PTR),$00,$00	;18
	db $00+<(FT_DPCM_PTR),$00,$00	;19
	db $00+<(FT_DPCM_PTR),$00,$00	;20
	db $00+<(FT_DPCM_PTR),$00,$00	;21
	db $00+<(FT_DPCM_PTR),$00,$00	;22
	db $00+<(FT_DPCM_PTR),$00,$00	;23
	db $00+<(FT_DPCM_PTR),$00,$00	;24
	db $00+<(FT_DPCM_PTR),$00,$00	;25
	db $00+<(FT_DPCM_PTR),$00,$00	;26
	db $00+<(FT_DPCM_PTR),$b3,$0f	;27
	db $00+<(FT_DPCM_PTR),$00,$00	;28
	db $00+<(FT_DPCM_PTR),$00,$00	;29
	db $00+<(FT_DPCM_PTR),$00,$00	;30
	db $00+<(FT_DPCM_PTR),$00,$00	;31
	db $00+<(FT_DPCM_PTR),$00,$00	;32
	db $00+<(FT_DPCM_PTR),$00,$00	;33
	db $00+<(FT_DPCM_PTR),$00,$00	;34
	db $00+<(FT_DPCM_PTR),$00,$00	;35
	db $00+<(FT_DPCM_PTR),$00,$00	;36
	db $47+<(FT_DPCM_PTR),$7c,$0f	;37
	db $00+<(FT_DPCM_PTR),$00,$00	;38
	db $00+<(FT_DPCM_PTR),$00,$00	;39
	db $67+<(FT_DPCM_PTR),$3f,$0f	;40
	db $2d+<(FT_DPCM_PTR),$66,$0f	;41
	db $00+<(FT_DPCM_PTR),$00,$00	;42
	db $00+<(FT_DPCM_PTR),$00,$00	;43
	db $00+<(FT_DPCM_PTR),$00,$00	;44
	db $00+<(FT_DPCM_PTR),$00,$00	;45
	db $00+<(FT_DPCM_PTR),$00,$00	;46
	db $00+<(FT_DPCM_PTR),$00,$00	;47
	db $00+<(FT_DPCM_PTR),$00,$00	;48
	db $00+<(FT_DPCM_PTR),$00,$00	;49
	db $00+<(FT_DPCM_PTR),$00,$00	;50
	db $00+<(FT_DPCM_PTR),$00,$00	;51
	db $00+<(FT_DPCM_PTR),$00,$00	;52
	db $00+<(FT_DPCM_PTR),$00,$00	;53
	db $00+<(FT_DPCM_PTR),$00,$00	;54
	db $00+<(FT_DPCM_PTR),$00,$00	;55
	db $00+<(FT_DPCM_PTR),$00,$00	;56
	db $00+<(FT_DPCM_PTR),$00,$00	;57
	db $00+<(FT_DPCM_PTR),$00,$00	;58
	db $00+<(FT_DPCM_PTR),$00,$00	;59
	db $00+<(FT_DPCM_PTR),$00,$00	;60
	db $00+<(FT_DPCM_PTR),$00,$00	;61
	db $00+<(FT_DPCM_PTR),$00,$00	;62
	db $00+<(FT_DPCM_PTR),$00,$00	;63

@env0:
	db $c0,$00,$00
@env1:
	db $cf,$cd,$cb,$ca,$c8,$c7,$c5,$c4,$00,$07
@env2:
	db $cc,$00,$00
@env3:
	db $c7,$c5,$c2,$c0,$00,$03
@env4:
	db $c8,$c3,$00,$01
@env5:
	db $c0,$c1,$c1,$c2,$c2,$c3,$c4,$00,$06
@env6:
	db $c0,$c0,$c1,$c1,$c2,$00,$04
@env7:
	db $c1,$c1,$c2,$c3,$00,$03
@env8:
	db $cc,$c6,$c5,$c3,$c1,$00,$04
@env9:
	db $be,$c0,$00,$01
@env10:
	db $c0,$bf,$c0,$c1,$05,$c2,$c2,$c3,$c8,$c7,$bf,$b5,$ab,$a3,$a4,$a4
	db $95,$8a,$02,$84,$81,$80,$80,$81,$80,$80,$80,$00,$1a
@env11:
	db $db,$f0,$00,$01
@env12:
	db $d7,$00,$00


@song0ch0:
	db $fb,$06
@song0ch0loop:
@ref0:
	db $82,$4f,$48,$01,$4e,$46,$83,$4f,$48,$01,$4e,$46,$83,$4f,$48,$01
	db $4e
@ref1:
	db $44,$87,$00,$44,$46,$85,$44,$01,$36,$3b,$3e,$41,$44,$49,$4a
@ref2:
	db $4f,$48,$01,$4e,$46,$83,$4f,$48,$01,$4e,$46,$83,$4f,$48,$01,$4e
@ref3:
	db $44,$87,$00,$8f,$36,$45,$3e,$41,$44,$49,$4e
@ref4:
	db $59,$52,$01,$58,$50,$83,$59,$52,$01,$58,$50,$83,$59,$52,$01,$58
@ref5:
	db $4e,$87,$00,$8b,$55,$4e,$01,$54,$4c,$87,$00
	db $ff,$10
	dw @ref2
	db $ff,$0f
	dw @ref1
	db $fd
	dw @song0ch0loop

@song0ch1:
@song0ch1loop:
@ref8:
	db $83,$82,$40,$01,$00,$3e,$83,$01,$40,$01,$00,$3e,$83,$01,$40,$01
	db $00
@ref9:
	db $3a,$87,$00,$3a,$3c,$85,$3a,$00,$95
@ref10:
	db $83,$40,$01,$00,$3e,$83,$01,$40,$01,$00,$3e,$83,$01,$40,$01,$00
@ref11:
	db $3a,$87,$00,$a3
@ref12:
	db $83,$4a,$01,$00,$48,$83,$01,$4a,$01,$00,$48,$83,$01,$4a,$01,$00
@ref13:
	db $44,$87,$00,$8f,$46,$01,$00,$44,$87,$00
	db $ff,$10
	dw @ref10
	db $ff,$09
	dw @ref9
	db $fd
	dw @song0ch1loop

@song0ch2:
@song0ch2loop:
@ref16:
	db $84,$45,$3a,$01,$44,$36,$83,$45,$3a,$01,$44,$36,$83,$45,$3a,$01
	db $44
@ref17:
	db $28,$87,$00,$28,$2a,$85,$28,$00,$95
@ref18:
	db $45,$3a,$01,$44,$36,$83,$45,$3a,$01,$44,$36,$83,$45,$3a,$01,$44
@ref19:
	db $28,$87,$00,$a3
@ref20:
	db $4f,$44,$01,$4e,$40,$83,$4f,$44,$01,$4e,$40,$83,$4f,$44,$01,$4e
@ref21:
	db $32,$87,$00,$8b,$4b,$40,$01,$4a,$3c,$87,$00
	db $ff,$10
	dw @ref18
	db $ff,$09
	dw @ref17
	db $fd
	dw @song0ch2loop

@song0ch3:
@song0ch3loop:
@ref24:
	db $af
@ref25:
	db $af
@ref26:
	db $af
@ref27:
	db $af
@ref28:
	db $af
@ref29:
	db $af
@ref30:
	db $af
@ref31:
	db $af
	db $fd
	dw @song0ch3loop

@song0ch4:
@song0ch4loop:
@ref32:
	db $af
@ref33:
	db $af
@ref34:
	db $af
@ref35:
	db $af
@ref36:
	db $af
@ref37:
	db $af
@ref38:
	db $af
@ref39:
	db $af
	db $fd
	dw @song0ch4loop


@song1ch0:
	db $fb,$07
@song1ch0loop:
@ref40:
	db $f9,$f9,$ab
	db $fd
	dw @song1ch0loop

@song1ch1:
@song1ch1loop:
@ref41:
	db $8e,$33,$3a,$40,$83,$40,$83,$44,$83,$40,$83,$3a,$83,$3b,$36,$32
	db $83,$36,$83,$3b,$40,$40,$87,$00,$4a,$83,$4a,$89,$4f,$4e,$4b,$44
	db $40,$83,$45,$40,$40,$83,$32,$83,$3b,$40,$36,$87,$00,$3b,$36,$32
	db $83,$36,$83,$3b,$40,$40,$83,$40,$83,$45,$40,$40,$83,$40,$83,$3b
	db $40,$40,$87,$00,$4b,$4a,$4a,$83,$4a,$83,$45,$4a,$4a,$87,$00,$44
	db $83,$41,$40,$41,$40,$32,$89,$00,$83
	db $fd
	dw @song1ch1loop

@song1ch2:
@song1ch2loop:
@ref42:
	db $84,$32,$01,$32,$01,$32,$01,$32,$01,$32,$01,$32,$01,$32,$01,$32
	db $01,$32,$01,$32,$00,$32,$32,$01,$32,$01,$32,$01,$32,$01,$32,$01
	db $32,$01,$32,$01,$32,$01,$2e,$00,$2e,$2e,$01,$2c,$01,$26,$00,$26
	db $28,$87,$00,$32,$00,$32,$32,$01,$32,$01,$32,$00,$32,$32,$01,$32
	db $01,$32,$00,$32,$32,$01,$32,$01,$32,$00,$32,$32,$01,$32,$01,$2e
	db $00,$2e,$2e,$01,$2e,$01,$2c,$00,$2c,$2c,$01,$8e,$2c,$00,$84,$26
	db $28,$01,$28,$00,$28,$28,$00,$28,$32,$89,$00,$83
	db $fd
	dw @song1ch2loop

@song1ch3:
@song1ch3loop:
@ref43:
	db $f9,$f9,$ab
	db $fd
	dw @song1ch3loop

@song1ch4:
@song1ch4loop:
@ref44:
	db $f9,$f9,$ab
	db $fd
	dw @song1ch4loop


@song2ch0:
	db $fb,$06
@song2ch0loop:
@ref45:
	db $f9,$85
	db $fd
	dw @song2ch0loop

@song2ch1:
@song2ch1loop:
@ref46:
	db $f9,$85
	db $fd
	dw @song2ch1loop

@song2ch2:
@song2ch2loop:
@ref47:
	db $f9,$85
	db $fd
	dw @song2ch2loop

@song2ch3:
@song2ch3loop:
@ref48:
	db $f9,$85
	db $fd
	dw @song2ch3loop

@song2ch4:
@song2ch4loop:
@ref49:
	db $36,$f9,$83
	db $fd
	dw @song2ch4loop


@song3ch0:
	db $fb,$04
@song3ch0loop:
@ref50:
	db $86,$40,$ad,$3e,$ad
@ref51:
	db $3c,$ad,$3a,$95,$38,$89,$3c,$89
	db $fd
	dw @song3ch0loop

@song3ch1:
@song3ch1loop:
@ref52:
	db $8c,$32,$ad,$46,$ad
@ref53:
	db $44,$a7,$47,$44,$42,$95,$40,$89,$86,$30,$89
	db $fd
	dw @song3ch1loop

@song3ch2:
@song3ch2loop:
@ref54:
	db $df
@ref55:
	db $df
	db $fd
	dw @song3ch2loop

@song3ch3:
@song3ch3loop:
@ref56:
	db $8a,$1f,$88,$04,$0e,$83,$8a,$05,$88,$0e,$04,$83,$8a,$1f,$88,$04
	db $0e,$83,$8a,$05,$88,$0e,$04,$83,$8a,$1e,$83,$88,$0e,$83,$8a,$05
	db $88,$0e,$04,$83,$05,$0e,$83,$0e,$12,$04,$0a,$12,$83
	db $ff,$21
	dw @ref56
	db $fd
	dw @song3ch3loop

@song3ch4:
@song3ch4loop:
@ref58:
	db $4b,$52,$83,$52,$50,$89,$4a,$89,$50,$89,$4b,$52,$83,$52,$50,$89
	db $4a,$83,$4a,$83,$50,$87,$4a
	db $ff,$17
	dw @ref58
	db $fd
	dw @song3ch4loop


@song4ch0:
	db $fb,$06
@song4ch0loop:
@ref60:
	db $84,$61,$63,$5d,$61,$5b,$5d,$5b,$55,$52,$54,$52,$50,$52,$95,$00
	db $85
	db $fd
	dw @song4ch0loop

@song4ch1:
@song4ch1loop:
@ref61:
	db $84,$3f,$41,$3b,$3f,$39,$3b,$39,$33,$30,$32,$30,$2e,$30,$95,$00
	db $85
	db $fd
	dw @song4ch1loop

@song4ch2:
@song4ch2loop:
@ref62:
	db $80,$49,$4b,$45,$49,$43,$45,$43,$3d,$3a,$3c,$3a,$38,$3a,$95,$00
	db $85
	db $fd
	dw @song4ch2loop

@song4ch3:
@song4ch3loop:
@ref63:
	db $c7
	db $fd
	dw @song4ch3loop

@song4ch4:
@song4ch4loop:
@ref64:
	db $c7
	db $fd
	dw @song4ch4loop
