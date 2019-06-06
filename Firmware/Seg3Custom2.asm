;====================================================
; Read block detectors for PHL, PH1..PH4
;  Inputs 0x0000..0x000F
;
ReadBlkDet	MOVLW	0x05	;sixth input
	MOVWF	CurBlk
	CLRF	CurBlk+1
	MOVLW	d'10'	;Scan 10 inputs
	MOVWF	Param79
ReadBlkDet_L1	CALL	InputB
	RLF	IActive,F
	RRF	Param75,F
	RRF	Param74,F
	INCF	CurBlk,F
	DECFSZ	Param79,F
	GOTO	ReadBlkDet_L1
;
	MOVLW	0x05	;PHL, PH1..PH4
	MOVWF	Param79
	MOVLW	BlkNumPHL
	MOVWF	XReg
ReadBlkDet_L2	CALL	ReadBlkDetUpdate1
	INCF	XReg,F
	DECFSZ	Param79,F
	GOTO	ReadBlkDet_L2
;
	RETURN
;
ReadBlkDetUpdate1	LCALL	GetBlockPwrTableX
	ANDLW	b'10011111'
	MOVWF	Param7A
	RRF	Param75,F
	RRF	Param74,F
	BTFSC	Param74,5
	BSF	Param7A,5
	RRF	Param75,F
	RRF	Param74,F
	BTFSC	Param74,5
	BSF	Param7A,6
	MOVF	Param78,W
	SUBWF	Param7A,W
	SKPNZ		;Any Change
	RETURN		; No
	MOVF	Param7A,W
	LCALL	SetBlockPwrTableX
	BSF	BlockDataChngFlag
	RETURN
;
