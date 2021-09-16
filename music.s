;this file for FamiTone2 library generated by text2data tool

pentup_music_data:
	.byte 4
	.word @instruments
	.word @samples-3
	.word @song0ch0,@song0ch1,@song0ch2,@song0ch3,@song0ch4,307,256
	.word @song1ch0,@song1ch1,@song1ch2,@song1ch3,@song1ch4,221,184
	.word @song2ch0,@song2ch1,@song2ch2,@song2ch3,@song2ch4,307,256
	.word @song3ch0,@song3ch1,@song3ch2,@song3ch3,@song3ch4,307,256

@instruments:
	.byte $30 ;instrument $00
	.word @env0,@env0,@env0
	.byte $00
	.byte $b0 ;instrument $01
	.word @env1,@env0,@env0
	.byte $00
	.byte $30 ;instrument $02
	.word @env3,@env0,@env0
	.byte $00
	.byte $30 ;instrument $03
	.word @env4,@env0,@env8
	.byte $00
	.byte $30 ;instrument $04
	.word @env4,@env0,@env0
	.byte $00
	.byte $30 ;instrument $05
	.word @env5,@env0,@env0
	.byte $00
	.byte $30 ;instrument $06
	.word @env6,@env7,@env0
	.byte $00
	.byte $30 ;instrument $07
	.word @env2,@env0,@env0
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
	.byte $2d+.lobyte(FT_DPCM_PTR),$a2,$0f	;25
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
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;37
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;38
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;39
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;40
	.byte $00+.lobyte(FT_DPCM_PTR),$00,$00	;41
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
	.byte $c1,$c1,$c2,$c3,$c4,$00,$04
@env4:
	.byte $cb,$c0,$00,$01
@env5:
	.byte $c1,$c1,$c2,$c3,$c5,$00,$04
@env6:
	.byte $cb,$c9,$c6,$c2,$00,$03
@env7:
	.byte $c9,$c6,$b1,$b1,$b1,$00,$04
@env8:
	.byte $d9,$d1,$00,$01


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
	.byte $8e,$45,$3a,$01,$44,$36,$83,$45,$3a,$01,$44,$36,$83,$45,$3a,$01
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
	.byte $fb,$03
@song1ch0loop:
@ref40:
	.byte $84,$46,$48,$83,$01,$48,$00,$87,$4a,$85,$01,$4a,$00,$85,$4c,$4e
	.byte $85,$01,$4e,$00
@ref41:
	.byte $83,$4a,$89,$4f,$4a,$89,$49,$01,$40,$00,$48,$00,$8d,$36
@ref42:
	.byte $40,$48,$52,$00,$4c,$00,$4e,$00,$af
	.byte $fd
	.word @song1ch0loop

@song1ch1:
@song1ch1loop:
@ref43:
	.byte $84,$3e,$40,$83,$01,$40,$00,$87,$44,$85,$01,$44,$00,$85,$46,$48
	.byte $85,$01,$48,$00
@ref44:
	.byte $83,$44,$87,$00,$49,$44,$89,$59,$01,$4e,$00,$58,$00,$8d,$8a,$36
	.byte $ff,$09
	.word @ref42
	.byte $fd
	.word @song1ch1loop

@song1ch2:
@song1ch2loop:
@ref46:
	.byte $8e,$28,$00,$87,$28,$00,$87,$2c,$00,$87,$2c,$00,$87,$30,$00,$87
	.byte $30,$00
@ref47:
	.byte $83,$2c,$89,$31,$2c,$89,$28,$00,$87,$28,$00,$8d,$8a,$36
	.byte $ff,$09
	.word @ref42
	.byte $fd
	.word @song1ch2loop

@song1ch3:
@song1ch3loop:
@ref49:
	.byte $88,$08,$89,$12,$85,$09,$08,$89,$12,$85,$1e,$1e,$08,$85,$1f,$12
	.byte $81
@ref50:
	.byte $83,$1f,$08,$85,$1f,$13,$1f,$12,$83,$04,$09,$0f,$12,$85,$09,$09
	.byte $8c,$16,$81
@ref51:
	.byte $88,$1e,$00,$8c,$17,$88,$1e,$00,$86,$04,$89,$88,$1e,$1e,$18,$85
	.byte $18,$85,$1e,$85,$1e,$89
	.byte $fd
	.word @song1ch3loop

@song1ch4:
@song1ch4loop:
@ref52:
	.byte $bf
@ref53:
	.byte $bf
@ref54:
	.byte $bf
	.byte $fd
	.word @song1ch4loop


@song2ch0:
	.byte $fb,$06
@song2ch0loop:
@ref55:
	.byte $f9,$85
	.byte $fd
	.word @song2ch0loop

@song2ch1:
@song2ch1loop:
@ref56:
	.byte $f9,$85
	.byte $fd
	.word @song2ch1loop

@song2ch2:
@song2ch2loop:
@ref57:
	.byte $f9,$85
	.byte $fd
	.word @song2ch2loop

@song2ch3:
@song2ch3loop:
@ref58:
	.byte $f9,$85
	.byte $fd
	.word @song2ch3loop

@song2ch4:
@song2ch4loop:
@ref59:
	.byte $36,$f9,$83
	.byte $fd
	.word @song2ch4loop


@song3ch0:
	.byte $fb,$06
@song3ch0loop:
@ref60:
	.byte $f9,$85
	.byte $fd
	.word @song3ch0loop

@song3ch1:
@song3ch1loop:
@ref61:
	.byte $f9,$85
	.byte $fd
	.word @song3ch1loop

@song3ch2:
@song3ch2loop:
@ref62:
	.byte $f9,$85
	.byte $fd
	.word @song3ch2loop

@song3ch3:
@song3ch3loop:
@ref63:
	.byte $f9,$85
	.byte $fd
	.word @song3ch3loop

@song3ch4:
@song3ch4loop:
@ref64:
	.byte $32,$f9,$83
	.byte $fd
	.word @song3ch4loop
