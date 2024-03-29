;this file for FamiTone2 library generated by text2data tool

pentup_music_data:
	.byte 5
	.word @instruments
	.word @samples-3
	.word @song0ch0,.song0ch1,.song0ch2,.song0ch3,.song0ch4,307,256
	.word @song1ch0,.song1ch1,.song1ch2,.song1ch3,.song1ch4,337,281
	.word @song2ch0,.song2ch1,.song2ch2,.song2ch3,.song2ch4,307,256
	.word @song3ch0,.song3ch1,.song3ch2,.song3ch3,.song3ch4,215,179
	.word @song4ch0,.song4ch1,.song4ch2,.song4ch3,.song4ch4,307,256

@instruments:
	.byte $30 ;instrument $00
	.word @env5,.env0,.env0
	.byte $00
	.byte $b0 ;instrument $01
	.word @env1,.env0,.env0
	.byte $00
	.byte $30 ;instrument $07
	.word @env2,.env9,.env0
	.byte $00
	.byte $70 ;instrument $08
	.word @env6,.env0,.env0
	.byte $00
	.byte $30 ;instrument $09
	.word @env3,.env0,.env11
	.byte $00
	.byte $30 ;instrument $0a
	.word @env4,.env0,.env12
	.byte $00
	.byte $70 ;instrument $0b
	.word @env7,.env0,.env0
	.byte $00
	.byte $b0 ;instrument $0c
	.word @env8,.env0,.env0
	.byte $00
	.byte $b0 ;instrument $0d
	.word @env1,.env9,.env10
	.byte $00

@samples:
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;1
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;2
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;3
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;4
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;5
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;6
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;7
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;8
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;9
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;10
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;11
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;12
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;13
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;14
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;15
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;16
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;17
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;18
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;19
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;20
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;21
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;22
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;23
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;24
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;25
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;26
	.byte $00+.lobyte(FT_DPCM_PTR),$b3,$0f	;27
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;28
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;29
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;30
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;31
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;32
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;33
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;34
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;35
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;36
	.byte $47+.lobyte(FT_DPCM_PTR),$7c,$0f	;37
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;38
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;39
	.byte $67+.lobyte(FT_DPCM_PTR),$3f,$0f	;40
	.byte $2d+.lobyte(FT_DPCM_PTR),$66,$0f	;41
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;42
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;43
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;44
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;45
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;46
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;47
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;48
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;49
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;50
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;51
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;52
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;53
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;54
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;55
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;56
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;57
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;58
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;59
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;60
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;61
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;62
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;63

@env0:
	.byte $c0,$00,$00
@env1:
	.byte $cf,$cd,$cb,$ca,$c8,$c7,$c5,$c4,$00,$07
@env2:
	.byte $cc,$00,$00
@env3:
	.byte $c7,$c5,$c2,$c0,$00,$03
@env4:
	.byte $c8,$c3,$00,$01
@env5:
	.byte $c0,$c1,$c1,$c2,$c2,$c3,$c4,$00,$06
@env6:
	.byte $c0,$c0,$c1,$c1,$c2,$00,$04
@env7:
	.byte $c1,$c1,$c2,$c3,$00,$03
@env8:
	.byte $cc,$c6,$c5,$c3,$c1,$00,$04
@env9:
	.byte $be,$c0,$00,$01
@env10:
	.byte $c0,$bf,$c0,$c1,$05,$c2,$c2,$c3,$c8,$c7,$bf,$b5,$ab,$a3,$a4,$a4
	.byte $95,$8a,$02,$84,$81,$80,$80,$81,$80,$80,$80,$00,$1a
@env11:
	.byte $db,$f0,$00,$01
@env12:
	.byte $d7,$00,$00


@song0ch0:
	.byte $fb,$06
@song0ch0loop:
@ref0:
	.byte $82,$4f,$48,$01,$4e,$46,$83,$4f,$48,$01,$4e,$46,$83,$4f,$48,$01
	.byte $4e
@ref1:
	.byte $44,$87,$00,$44,$46,$85,$44,$01,$36,$3b,$3e,$41,$44,$49,$4a
@ref2:
	.byte $4f,$48,$01,$4e,$46,$83,$4f,$48,$01,$4e,$46,$83,$4f,$48,$01,$4e
@ref3:
	.byte $44,$87,$00,$8f,$36,$45,$3e,$41,$44,$49,$4e
@ref4:
	.byte $59,$52,$01,$58,$50,$83,$59,$52,$01,$58,$50,$83,$59,$52,$01,$58
@ref5:
	.byte $4e,$87,$00,$8b,$55,$4e,$01,$54,$4c,$87,$00
	.byte $ff,$10
	.word @ref2
	.byte $ff,$0f
	.word @ref1
	.byte $fd
	.word @song0ch0loop

@song0ch1:
@song0ch1loop:
@ref8:
	.byte $83,$82,$40,$01,$00,$3e,$83,$01,$40,$01,$00,$3e,$83,$01,$40,$01
	.byte $00
@ref9:
	.byte $3a,$87,$00,$3a,$3c,$85,$3a,$00,$95
@ref10:
	.byte $83,$40,$01,$00,$3e,$83,$01,$40,$01,$00,$3e,$83,$01,$40,$01,$00
@ref11:
	.byte $3a,$87,$00,$a3
@ref12:
	.byte $83,$4a,$01,$00,$48,$83,$01,$4a,$01,$00,$48,$83,$01,$4a,$01,$00
@ref13:
	.byte $44,$87,$00,$8f,$46,$01,$00,$44,$87,$00
	.byte $ff,$10
	.word @ref10
	.byte $ff,$09
	.word @ref9
	.byte $fd
	.word @song0ch1loop

@song0ch2:
@song0ch2loop:
@ref16:
	.byte $84,$45,$3a,$01,$44,$36,$83,$45,$3a,$01,$44,$36,$83,$45,$3a,$01
	.byte $44
@ref17:
	.byte $28,$87,$00,$28,$2a,$85,$28,$00,$95
@ref18:
	.byte $45,$3a,$01,$44,$36,$83,$45,$3a,$01,$44,$36,$83,$45,$3a,$01,$44
@ref19:
	.byte $28,$87,$00,$a3
@ref20:
	.byte $4f,$44,$01,$4e,$40,$83,$4f,$44,$01,$4e,$40,$83,$4f,$44,$01,$4e
@ref21:
	.byte $32,$87,$00,$8b,$4b,$40,$01,$4a,$3c,$87,$00
	.byte $ff,$10
	.word @ref18
	.byte $ff,$09
	.word @ref17
	.byte $fd
	.word @song0ch2loop

@song0ch3:
@song0ch3loop:
@ref24:
	.byte $af
@ref25:
	.byte $af
@ref26:
	.byte $af
@ref27:
	.byte $af
@ref28:
	.byte $af
@ref29:
	.byte $af
@ref30:
	.byte $af
@ref31:
	.byte $af
	.byte $fd
	.word @song0ch3loop

@song0ch4:
@song0ch4loop:
@ref32:
	.byte $af
@ref33:
	.byte $af
@ref34:
	.byte $af
@ref35:
	.byte $af
@ref36:
	.byte $af
@ref37:
	.byte $af
@ref38:
	.byte $af
@ref39:
	.byte $af
	.byte $fd
	.word @song0ch4loop


@song1ch0:
	.byte $fb,$07
@song1ch0loop:
@ref40:
	.byte $f9,$f9,$ab
	.byte $fd
	.word @song1ch0loop

@song1ch1:
@song1ch1loop:
@ref41:
	.byte $8e,$33,$3a,$40,$83,$40,$83,$44,$83,$40,$83,$3a,$83,$3b,$36,$32
	.byte $83,$36,$83,$3b,$40,$40,$87,$00,$4a,$83,$4a,$89,$4f,$4e,$4b,$44
	.byte $40,$83,$45,$40,$40,$83,$32,$83,$3b,$40,$36,$87,$00,$3b,$36,$32
	.byte $83,$36,$83,$3b,$40,$40,$83,$40,$83,$45,$40,$40,$83,$40,$83,$3b
	.byte $40,$40,$87,$00,$4b,$4a,$4a,$83,$4a,$83,$45,$4a,$4a,$87,$00,$44
	.byte $83,$41,$40,$41,$40,$32,$89,$00,$83
	.byte $fd
	.word @song1ch1loop

@song1ch2:
@song1ch2loop:
@ref42:
	.byte $84,$32,$01,$32,$01,$32,$01,$32,$01,$32,$01,$32,$01,$32,$01,$32
	.byte $01,$32,$01,$32,$00,$32,$32,$01,$32,$01,$32,$01,$32,$01,$32,$01
	.byte $32,$01,$32,$01,$32,$01,$2e,$00,$2e,$2e,$01,$2c,$01,$26,$00,$26
	.byte $28,$87,$00,$32,$00,$32,$32,$01,$32,$01,$32,$00,$32,$32,$01,$32
	.byte $01,$32,$00,$32,$32,$01,$32,$01,$32,$00,$32,$32,$01,$32,$01,$2e
	.byte $00,$2e,$2e,$01,$2e,$01,$2c,$00,$2c,$2c,$01,$8e,$2c,$00,$84,$26
	.byte $28,$01,$28,$00,$28,$28,$00,$28,$32,$89,$00,$83
	.byte $fd
	.word @song1ch2loop

@song1ch3:
@song1ch3loop:
@ref43:
	.byte $f9,$f9,$ab
	.byte $fd
	.word @song1ch3loop

@song1ch4:
@song1ch4loop:
@ref44:
	.byte $f9,$f9,$ab
	.byte $fd
	.word @song1ch4loop


@song2ch0:
	.byte $fb,$06
@song2ch0loop:
@ref45:
	.byte $f9,$85
	.byte $fd
	.word @song2ch0loop

@song2ch1:
@song2ch1loop:
@ref46:
	.byte $f9,$85
	.byte $fd
	.word @song2ch1loop

@song2ch2:
@song2ch2loop:
@ref47:
	.byte $f9,$85
	.byte $fd
	.word @song2ch2loop

@song2ch3:
@song2ch3loop:
@ref48:
	.byte $f9,$85
	.byte $fd
	.word @song2ch3loop

@song2ch4:
@song2ch4loop:
@ref49:
	.byte $36,$f9,$83
	.byte $fd
	.word @song2ch4loop


@song3ch0:
	.byte $fb,$04
@song3ch0loop:
@ref50:
	.byte $86,$40,$ad,$3e,$ad
@ref51:
	.byte $3c,$ad,$3a,$95,$38,$89,$3c,$89
	.byte $fd
	.word @song3ch0loop

@song3ch1:
@song3ch1loop:
@ref52:
	.byte $8c,$32,$ad,$46,$ad
@ref53:
	.byte $44,$a7,$47,$44,$42,$95,$40,$89,$86,$30,$89
	.byte $fd
	.word @song3ch1loop

@song3ch2:
@song3ch2loop:
@ref54:
	.byte $df
@ref55:
	.byte $df
	.byte $fd
	.word @song3ch2loop

@song3ch3:
@song3ch3loop:
@ref56:
	.byte $8a,$1f,$88,$04,$0e,$83,$8a,$05,$88,$0e,$04,$83,$8a,$1f,$88,$04
	.byte $0e,$83,$8a,$05,$88,$0e,$04,$83,$8a,$1e,$83,$88,$0e,$83,$8a,$05
	.byte $88,$0e,$04,$83,$05,$0e,$83,$0e,$12,$04,$0a,$12,$83
	.byte $ff,$21
	.word @ref56
	.byte $fd
	.word @song3ch3loop

@song3ch4:
@song3ch4loop:
@ref58:
	.byte $4b,$52,$83,$52,$50,$89,$4a,$89,$50,$89,$4b,$52,$83,$52,$50,$89
	.byte $4a,$83,$4a,$83,$50,$87,$4a
	.byte $ff,$17
	.word @ref58
	.byte $fd
	.word @song3ch4loop


@song4ch0:
	.byte $fb,$06
@song4ch0loop:
@ref60:
	.byte $84,$61,$63,$5d,$61,$5b,$5d,$5b,$55,$52,$54,$52,$50,$52,$95,$00
	.byte $85
	.byte $fd
	.word @song4ch0loop

@song4ch1:
@song4ch1loop:
@ref61:
	.byte $84,$3f,$41,$3b,$3f,$39,$3b,$39,$33,$30,$32,$30,$2e,$30,$95,$00
	.byte $85
	.byte $fd
	.word @song4ch1loop

@song4ch2:
@song4ch2loop:
@ref62:
	.byte $80,$49,$4b,$45,$49,$43,$45,$43,$3d,$3a,$3c,$3a,$38,$3a,$95,$00
	.byte $85
	.byte $fd
	.word @song4ch2loop

@song4ch3:
@song4ch3loop:
@ref63:
	.byte $c7
	.byte $fd
	.word @song4ch3loop

@song4ch4:
@song4ch4loop:
@ref64:
	.byte $c7
	.byte $fd
	.word @song4ch4loop
