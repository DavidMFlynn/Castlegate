	subtitle	CG IO.asm
;
;
;
;in SMTable each Byte represents one Switch Machine
; bit0 = Has been sent to TCC Com I/O
; bit1 = unused
; bit2 = unused
; bit3 = unused
; bit4 = unused
; bit5 = Feed Back
; bit6 = Command if 1 then bit 7 will also be 1
; bit7 = Control
;
;SMControlMask	EQU	0x7F
;SMFBMask	EQU	0xDF
;SMChangedMask	EQU	0xFE
;SMCnFMask	EQU	0xA0
;SMCMDMask	EQU	0x40
;
;
OutputC_D10	mCall2To3	OutputC
	RETURN
;
InputC_D10	mCall2To3	InputC
	RETURN
;
OutputB_D10	mCall2To3	OutputB
	RETURN
;
InputB_D10	mCall2To3	InputB
	RETURN
;
OutputA_D10	mCall2To3	OutputA
	RETURN
;
InputA_D10	mCall2To3	InputA
	RETURN
;
Output_D10	mCall2To3	Output
	RETURN
;
;CONSTANTS ******************************************
;
kMaxRetry	EQU	0x05
;
LastSMNumber	EQU	0x0002
EastBound	EQU	0x40
WestBound	EQU	0x20
;
Cab1Mask	EQU	0x10
Cab2Mask	EQU	0x08
Cab3Mask	EQU	0x04
Cab4Mask	EQU	0x02
Cab5Mask	EQU	0x01
Cab1InvertMask	EQU	0x0F
Cab2InvertMask	EQU	0x17
Cab3InvertMask	EQU	0x1B
Cab4InvertMask	EQU	0x1D
Cab5InvertMask	EQU	0x1E
;
;=============================================================
;         ********** MAIN ***********
;=============================================================
;
DoDMFEIO
	if UsePsuedoReset
	BTFSS	PORTA,3	;psuedo Reset
	GOTO	Main
	endif
;
;
	mBank3
	BTFSS	UDP_DataReceived	;Any UDP data?
	GOTO	MainLoop_E2	; No
	BCF	UDP_DataReceived
;
	include RecBlkPwr.inc
;
;======================================================================================
; Enters here when no UDP packet was received
;
MainLoop_E2	mBank3
;
	if UsesSpeaker
; turn off beeper
	BTFSS	BeepOn
	GOTO	MainLoop_1
	MOVF	BeepTimer,F
	SKPZ
	GOTO	MainLoop_1
	BCF	BeepOn
	MOVLW	low SPKR	;#<SPKR or / =Low byte
	MOVWF	CurBlk
	MOVLW	high SPKR	;#>SPKR or mod =Hi byte
	MOVWF	CurBlk+1
	BCF	OActive,7
	CALL	OutputB_D10
;
	endif
;
;
MainLoop_1	mCall2To0	SyncBlkPwr	;kill old 0x00 block cmds
	mCall2To0	SyncSMs	;kill Valid bits if Cmd = Ctrl
;
	mBank0
	BTFSC	ServiceMode
	RETURN
;
	mBank3
	MOVF	DisplayBlkNum,W
	CALL	LightBlkDisplay
	MOVF	DisplayBlkNum,W
	INCF	DisplayBlkNum,F
;
	SUBLW	kMaxBlockNum
	SKPNZ		;All blocks done?
	CLRF	DisplayBlkNum	; Yes
;
; look for any active block module button and set the block data
	CALL	ProccessButtons
;
;
	mCall2To0	SetBlockPwr
	mCall2To0	ScanBlockPwr	;test next 5 blocks
	mCall2To3	Loop7	;Light Odd LEDs not in SM data
;
	mCall2To3	ScanCabBtns
;
; Fall through to MainLoop5 ;Set SMs for one route
	include MainLoop5.inc
;
;===================================================================================================
;
;
;
