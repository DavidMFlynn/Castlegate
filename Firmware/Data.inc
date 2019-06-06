	subtitle	"Data.inc"
;
;===========================================================================================
;
;  FileName: Data.inc
;  Date: 6/2/2007
;  File Version: 1.0.1
;  
;  Author: David M. Flynn
;  Company: HPRR
;  Project: Casper Tower
;
;===========================================================================================
; Revision History
;
; 1.0.1  6/2/07	Added kLastBlkModule
; 1.0    3/27/03	File first created.
;
;============================================================================================
; Notes:
;
;  This file has data that is loaded from the eeROM to SRAM
;  evDataROM*256 is added to the PC here to get the SRAM address
;
;  The BD and DW commands are related to the STR and RES commands.
;  The label is stored with the currnt PC value then
;   the PC is incremented by the data length
;  A "d.d" file is created containing the data for the eerom file.
;  Copy the "d.d" file to the WWW page subdirectory then run eeROM 
;   to make an eeROM.binary file.
;  Then run eeROM Uploader to upload the eeROM.binary file into the
;   first 24LC256 at U2.
;
;============================================================================================
	DataFileOn LE
	ORG	0x0000
;
EOD	EQU	0xFF
;
	include HPRRMenuData.inc
;
kLastBlkModule	EQU	0x1F
; output address of the speaker
SPKR	EQU	0x041D
;
kNumDefaultValues	EQU	d'1'	;FactoryDefaults list
;  see BytesToMvFrmEE
FactoryDefaults	DB	kDefaultIOCtrl
;
;
;Buttons add 0x0000 to get Input #
ButtonIBoard	EQU	0x00
;
Cab1Btn	EQU	0x10	;Cab 1
Cab2Btn	EQU	0x11
Cab3Btn	EQU	0x12
Cab4Btn	EQU	0x13
Cab5Btn	EQU	0x14	;Cab 5
Cab6Btn	EQU	0x15	;CT
;
;
	include	PanelCtrlData.inc
;
; Block number to Block Module Number table		;Blk#, Blk Name, d'Blk#
BlkModID	DB	0xFE	;none, BlkNumRDY1 0
	DB	0xFE	;none, BlkNumRDY2 1
	DB	0xFE	;none, BlkNumFYL 2
	DB	0xFE	;none, BlkNum100 3
	DB	0xFE	;none, BlkNum101 4
	DB	0xFE	;none, BlkNum110 5
	DB	0xFE	;none, BlkNum111 6
	DB	0xFE	;none, BlkNum120 7
	DB	0xFE	;none, BlkNum121 8
	DB	0xFE	;none, BlkNum130 9
	DB	0xFE	;none, BlkNum131 10
	DB	0xFE	;none, BlkNum140 11
	DB	0xFE	;none, BlkNum141 12
	DB	0xFE	;none, BlkNumPT1 13
	DB	0xFE	;none, BlkNumPT2 14
	DB	0xFE	;none, BlkNum150 15
	DB	0xFE	;none, BlkNum151 16
	DB	0xFE	;none, BlkNum160 17
	DB	0xFE	;none, BlkNum170 18
	DB	0xFE	;none, BlkNum171 19
	DB	0xFE	;none, BlkNumSYL 20
	DB	0xFE	;none, BlkNum180 21
	DB	0xFE	;none, BlkNum190 22
	DB	0xFE	;none, BlkNum191 23
	DB	0x14	;0x18, BlkNum200 24
	DB	0x15	;0x19, BlkNum201 25
	DB	0x13	;0x1A, BlkNum202 26
	DB	0x12	;0x1B, BlkNum210 27
	DB	0x0F	;0x1C, BlkNum220 28
	DB	0x10	;0x1D, BlkNum221 29
	DB	0x11	;0x1E, BlkNum222 30
	DB	0x0E	;0x1F, BlkNum230 31
	DB	0x0D	;0x20, BlkNum240 32
	DB	0x0C	;0x21, BlkNum250 33
	DB	0x0B	;0x22, BlkNum251 34
	DB	0x07	;0x23, BlkNum260 35
	DB	0x04	;0x24, BlkNum270 36
	DB	0x05	;0x25, BlkNum271 37
	DB	0x02	;0x26, BlkNum280 38
	DB	0x00	;0x27, BlkNum290 39
	DB	0x01	;0x28, BlkNum291 40
	DB	0x1F	;0x29, BlkNum300 41
	DB	0x1A	;0x2A, BlkNum3101 42
	DB	0x16	;0x2B, BlkNum3102 43
	DB	0x1B	;0x2C, BlkNum3111 44
	DB	0x17	;0x2D, BlkNum3112 45
	DB	0x1C	;0x2E, BlkNum3121 46
	DB	0x18	;0x2F, BlkNum3122 47
	DB	0x1D	;0x30, BlkNum3131 48
	DB	0x19	;0x31, BlkNum3132 49
	DB	0xFE	;none, BlkNum320 50
	DB	0xFE	;none, BlkNum390 51
	DB	0xFE	;none, BlkNum330 52
	DB	0xFE	;none, BlkNum380 53
	DB	0xFE	;none, BlkNum340 54
	DB	0xFE	;none, BlkNum370 55
	DB	0xFE	;none, BlkNum350 56
	DB	0xFE	;none, BlkNum351 57
	DB	0xFE	;none, BlkNum360 58
	DB	0xFE	;none, BlkNum361 59
	DB	0xFE	;none, BlkNum362 60
	DB	0xFE	;none, BlkNum363 61
	DB	0xFE	;none, BlkNum364 62
	DB	0xFE	;none, BlkNum365 63
;
	DB	0xFE	;none, BlkNumVY1 64
	DB	0xFE	;none, BlkNumVY2 65
	DB	0xFE	;none, BlkNumVY3 66
	DB	0xFE	;none, BlkNumVY4 67
	DB	0xFE	;none, BlkNumVY5 68
	DB	0xFE	;none, BlkNumVY6 69
	DB	0xFE	;none, BlkNumEYF 70
	DB	0x06	;0x47, BlkNumPHL 71
	DB	0x08	;0x48, BlkNumPH1 72
	DB	0x09	;0x49, BlkNumPH2 73
	DB	0x0A	;0x4A, BlkNumPH3 74
	DB	0x03	;0x4B, BlkNumPH4 75
	DB	0x1E	;0x4C, BlkMZR Manzanar 76
	DB	0xFE
	DB	0xFE
	DB	0xFE
;
;
;
;==========================================================
;Individual LEDs
;
WatchDogLED	EQU	0x041C
;
;
Cab1EastLED	DW	0x0410
Cab1WestLED	DW	0x0411
;
Cab2EastLED	DW	0x0412
Cab2WestLED	DW	0x0413
;
Cab3EastLED	DW	0x0414
Cab3WestLED	DW	0x0415
;
Cab4EastLED	DW	0x0416
Cab4WestLED	DW	0x0417
;
Cab5EastLED	DW	0x0418
Cab5WestLED	DW	0x0419
;
Cab6EastLED	DW	0x041A	;CT
Cab6WestLED	DW	0x041B
;
;
;
	include	BlockData.inc
;
; Button Number(1..32) to Block Number
;
BtnToBlkNum	DB	0xFE	;Offset, 0 used for debounce
	DB	BlkNum290	;Btn 1  Block Module 0
	DB	BlkNum291	;Btn 2  Block Module 1
	DB	BlkNum280	;Btn 3  Block Module 2
	DB	BlkNumPH4	;Btn 4  Block Module 3
	DB	BlkNum270	;Btn 5  Block Module 4
	DB	BlkNum271	;Btn 6  Block Module 5
	DB	BlkNumPHL	;Btn 7  Block Module 6
	DB	BlkNum260	;Btn 8  Block Module 7
	DB	BlkNumPH1	;Btn 9  Block Module 8
	DB	BlkNumPH2	;Btn 10 Block Module 9
	DB	BlkNumPH3	;Btn 11 Block Module 10
	DB	BlkNum251	;Btn 12 Block Module 11
	DB	BlkNum250	;Btn 13 Block Module 12
	DB	BlkNum240	;Btn 14 Block Module 13
	DB	BlkNum230	;Btn 15 Block Module 14
	DB	BlkNum220	;Btn 16 Block Module 15
	DB	BlkNum221	;Btn 17 Block Module 16
	DB	BlkNum222	;Btn 18 Block Module 17
	DB	BlkNum210	;Btn 19 Block Module 18
	DB	BlkNum202	;Btn 20 Block Module 19
	DB	BlkNum200	;Btn 21 Block Module 20
	DB	BlkNum201	;Btn 22 Block Module 21
	DB	BlkNum3102	;Btn 23 Block Module 22
	DB	BlkNum3112	;Btn 24 Block Module 23
	DB	BlkNum3122	;Btn 25 Block Module 24
	DB	BlkNum3132	;Btn 26 Block Module 25
	DB	BlkNum3101	;Btn 27 Block Module 26
	DB	BlkNum3111	;Btn 28 Block Module 27
	DB	BlkNum3121	;Btn 29 Block Module 28
	DB	BlkNum3131	;Btn 30 Block Module 29
	DB	BlkNumMZR	;Btn 31 Block Module 30
	DB	BlkNum300	;Btn 32 Block Module 31
;	
;==============================================================================================
; Block number to Symbol for Throttle 6		;Blk#, Blk Name, d'Blk#
BlkThr6ToSym	DB	LetterA	;0x00, BlkNumRDY1 0
	DB	LetterA	;0x01, BlkNumRDY2 1
	DB	LetterA	;0x02, BlkNumFYL  2
	DB	LetterA	;0x03, BlkNum100  3
	DB	LetterA	;0x04, BlkNum101  4
	DB	LetterA	;0x05, BlkNum110  5
	DB	LetterA	;0x06, BlkNum111  6
	DB	LetterA	;0x07, BlkNum120  7
	DB	LetterA	;0x08, BlkNum121  8
	DB	LetterA	;0x09, BlkNum130  9
	DB	LetterA	;0x0A, BlkNum131 10
	DB	LetterA	;0x0B, BlkNum140 11
	DB	LetterA	;0x0C, BlkNum141 12
	DB	LetterA	;0x0D, BlkNumPT1 13
	DB	LetterA	;0x0E, BlkNumPT2 14
	DB	LetterA	;0x0F, BlkNum150 15
	DB	LetterA	;0x10, BlkNum151 16
	DB	LetterB	;0x11, BlkNum160 17
	DB	LetterB	;0x12, BlkNum170 18
	DB	LetterB	;0x13, BlkNum171 19
	DB	LetterB	;0x14, BlkNumSYL 20
	DB	LetterB	;0x15, BlkNum180 21
	DB	LetterB	;0x16, BlkNum190 22
	DB	LetterB	;0x17, BlkNum191 23
	DB	LetterB	;0x18, BlkNum200 24
	DB	LetterB	;0x19, BlkNum201 25
	DB	LetterC	;0x1A, BlkNum202 26
	DB	LetterC	;0x1B, BlkNum210 27
	DB	LetterC	;0x1C, BlkNum220 28
	DB	LetterC	;0x1D, BlkNum221 29
	DB	LetterC	;0x1E, BlkNum222 30
	DB	LetterC	;0x1F, BlkNum230 31
	DB	LetterC	;0x20, BlkNum240 32
	DB	LetterC	;0x21, BlkNum250 33
	DB	LetterC	;0x22, BlkNum251 34
	DB	LetterC	;0x23, BlkNum260 35
	DB	LetterC	;0x24, BlkNum270 36
	DB	LetterC	;0x25, BlkNum271 37
	DB	LetterC	;0x26, BlkNum280 38
	DB	LetterC	;0x27, BlkNum290 39
	DB	LetterC	;0x28, BlkNum291 40
	DB	LetterC	;0x29, BlkNum300 41
	DB	LetterD	;0x2A, BlkNum3101 42
	DB	LetterD	;0x2B, BlkNum3102 43
	DB	LetterD	;0x2C, BlkNum3111 44
	DB	LetterD	;0x2D, BlkNum3112 45
	DB	LetterD	;0x2E, BlkNum3121 46
	DB	LetterD	;0x2F, BlkNum3122 47
	DB	LetterD	;0x30, BlkNum3131 48
	DB	LetterD	;0x31, BlkNum3132 49
	DB	LetterD	;0x32, BlkNum320 50
	DB	LetterD	;0x33, BlkNum390 51
	DB	LetterD	;0x34, BlkNum330 52
	DB	LetterD	;0x35, BlkNum380 53
	DB	LetterD	;0x36, BlkNum340 54
	DB	LetterD	;0x37, BlkNum370 55
	DB	LetterD	;0x38, BlkNum350 56
	DB	LetterD	;0x39, BlkNum351 57
	DB	LetterD	;0x3A, BlkNum360 58
	DB	LetterD	;0x3B, BlkNum361 59
	DB	LetterD	;0x3C, BlkNum362 60
	DB	LetterD	;0x3D, BlkNum363 61
	DB	LetterD	;0x3E, BlkNum364 62
	DB	LetterD	;0x3F, BlkNum365 63
	DB	LetterA	;none, BlkNumVY1 64
	DB	LetterA	;none, BlkNumVY2 65
	DB	LetterA	;none, BlkNumVY3 66
	DB	LetterA	;none, BlkNumVY4 67
	DB	LetterA	;none, BlkNumVY5 68
	DB	LetterA	;none, BlkNumVY6 69
	DB	LetterA	;none, BlkNumEYF 70
	DB	LetterC	;0x47, BlkNumPHL 71
	DB	LetterC	;0x48, BlkNumPH1 72
	DB	LetterC	;0x49, BlkNumPH2 73
	DB	LetterC	;0x4A, BlkNumPH3 74
	DB	LetterC	;0x4B, BlkNumPH4 75
	DB	LetterC	;0x4C, BlkMZR Manzanar 76
	DB	LetterE
	DB	LetterE
;
;	
; Block number to Symbol for Throttle 7		;Blk#, Blk Name, d'Blk#
BlkThr7ToSym	DB	LetterE	;0x00, BlkNumRDY1 0
	DB	LetterE	;0x01, BlkNumRDY2 1
	DB	LetterV	;0x02, BlkNumFYL  2
	DB	LetterE	;0x03, BlkNum100  3
	DB	LetterE	;0x04, BlkNum101  4
	DB	LetterE	;0x05, BlkNum110  5
	DB	LetterE	;0x06, BlkNum111  6
	DB	LetterE	;0x07, BlkNum120  7
	DB	LetterE	;0x08, BlkNum121  8
	DB	LetterE	;0x09, BlkNum130  9
	DB	LetterE	;0x0A, BlkNum131 10
	DB	LetterE	;0x0B, BlkNum140 11
	DB	LetterE	;0x0C, BlkNum141 12
	DB	LetterE	;0x0D, BlkNumPT1 13
	DB	LetterE	;0x0E, BlkNumPT2 14
	DB	LetterB	;0x0F, BlkNum150 15
	DB	LetterB	;0x10, BlkNum151 16
	DB	LetterE	;0x11, BlkNum160 17
	DB	LetterE	;0x12, BlkNum170 18
	DB	LetterE	;0x13, BlkNum171 19
	DB	LetterE	;0x14, BlkNumSYL 20
	DB	LetterE	;0x15, BlkNum180 21
	DB	LetterE	;0x16, BlkNum190 22
	DB	LetterE	;0x17, BlkNum191 23
	DB	LetterC	;0x18, BlkNum200 24
	DB	LetterC	;0x19, BlkNum201 25
	DB	LetterB	;0x1A, BlkNum202 26
	DB	LetterE	;0x1B, BlkNum210 27
	DB	LetterE	;0x1C, BlkNum220 28
	DB	LetterE	;0x1D, BlkNum221 29
	DB	LetterE	;0x1E, BlkNum222 30
	DB	LetterE	;0x1F, BlkNum230 31
	DB	LetterE	;0x20, BlkNum240 32
	DB	LetterE	;0x21, BlkNum250 33
	DB	LetterE	;0x22, BlkNum251 34
	DB	LetterE	;0x23, BlkNum260 35
	DB	LetterE	;0x24, BlkNum270 36
	DB	LetterE	;0x25, BlkNum271 37
	DB	LetterE	;0x26, BlkNum280 38
	DB	LetterE	;0x27, BlkNum290 39
	DB	LetterE	;0x28, BlkNum291 40
	DB	LetterE	;0x29, BlkNum300 41
	DB	LetterC	;0x2A, BlkNum3101 42
	DB	LetterC	;0x2B, BlkNum3102 43
	DB	LetterC	;0x2C, BlkNum3111 44
	DB	LetterC	;0x2D, BlkNum3112 45
	DB	LetterC	;0x2E, BlkNum3121 46
	DB	LetterC	;0x2F, BlkNum3122 47
	DB	LetterC	;0x30, BlkNum3131 48
	DB	LetterC	;0x31, BlkNum3132 49
	DB	LetterE	;0x32, BlkNum320 50
	DB	LetterE	;0x33, BlkNum390 51
	DB	LetterE	;0x34, BlkNum330 52
	DB	LetterE	;0x35, BlkNum380 53
	DB	LetterE	;0x36, BlkNum340 54
	DB	LetterE	;0x37, BlkNum370 55
	DB	LetterE	;0x38, BlkNum350 56
	DB	LetterE	;0x39, BlkNum351 57
	DB	LetterE	;0x3A, BlkNum360 58
	DB	LetterE	;0x3B, BlkNum361 59
	DB	LetterE	;0x3C, BlkNum362 60
	DB	LetterE	;0x3D, BlkNum363 61
	DB	LetterE	;0x3E, BlkNum364 62
	DB	LetterE	;0x3F, BlkNum365 63
	DB	LetterV	;none, BlkNumVY1 64
	DB	LetterV	;none, BlkNumVY2 65
	DB	LetterV	;none, BlkNumVY3 66
	DB	LetterV	;none, BlkNumVY4 67
	DB	LetterV	;none, BlkNumVY5 68
	DB	LetterV	;none, BlkNumVY6 69
	DB	LetterV	;none, BlkNumEYF 70
	DB	LetterE	;0x47, BlkNumPHL 71
	DB	LetterE	;0x48, BlkNumPH1 72
	DB	LetterE	;0x49, BlkNumPH2 73
	DB	LetterE	;0x4A, BlkNumPH3 74
	DB	LetterE	;0x4B, BlkNumPH4 75
	DB	LetterE	;0x4C, BlkMZR Manzanar 76
	DB	LetterE
	DB	LetterE
;
;	
; Block number to Symbol for Throttle 8		;Blk#, Blk Name, d'Blk#
BlkThr8ToSym	DB	LetterE	;0x00, BlkNumRDY1 0
	DB	LetterE	;0x01, BlkNumRDY2 1
	DB	LetterW	;0x02, BlkNumFYL  2
	DB	LetterE	;0x03, BlkNum100  3
	DB	LetterE	;0x04, BlkNum101  4
	DB	LetterE	;0x05, BlkNum110  5
	DB	LetterE	;0x06, BlkNum111  6
	DB	LetterE	;0x07, BlkNum120  7
	DB	LetterE	;0x08, BlkNum121  8
	DB	LetterE	;0x09, BlkNum130  9
	DB	LetterE	;0x0A, BlkNum131 10
	DB	LetterE	;0x0B, BlkNum140 11
	DB	LetterE	;0x0C, BlkNum141 12
	DB	LetterE	;0x0D, BlkNumPT1 13
	DB	LetterE	;0x0E, BlkNumPT2 14
	DB	LetterE	;0x0F, BlkNum150 15
	DB	LetterE	;0x10, BlkNum151 16
	DB	LetterE	;0x11, BlkNum160 17
	DB	LetterE	;0x12, BlkNum170 18
	DB	LetterE	;0x13, BlkNum171 19
	DB	LetterE	;0x14, BlkNumSYL 20
	DB	LetterE	;0x15, BlkNum180 21
	DB	LetterE	;0x16, BlkNum190 22
	DB	LetterE	;0x17, BlkNum191 23
	DB	LetterE	;0x18, BlkNum200 24
	DB	LetterE	;0x19, BlkNum201 25
	DB	LetterE	;0x1A, BlkNum202 26
	DB	LetterE	;0x1B, BlkNum210 27
	DB	LetterE	;0x1C, BlkNum220 28
	DB	LetterE	;0x1D, BlkNum221 29
	DB	LetterE	;0x1E, BlkNum222 30
	DB	LetterE	;0x1F, BlkNum230 31
	DB	LetterE	;0x20, BlkNum240 32
	DB	LetterE	;0x21, BlkNum250 33
	DB	LetterE	;0x22, BlkNum251 34
	DB	LetterE	;0x23, BlkNum260 35
	DB	LetterE	;0x24, BlkNum270 36
	DB	LetterE	;0x25, BlkNum271 37
	DB	LetterE	;0x26, BlkNum280 38
	DB	LetterE	;0x27, BlkNum290 39
	DB	LetterE	;0x28, BlkNum291 40
	DB	LetterE	;0x29, BlkNum300 41
	DB	LetterG	;0x2A, BlkNum3101 42
	DB	LetterG	;0x2B, BlkNum3102 43
	DB	LetterG	;0x2C, BlkNum3111 44
	DB	LetterG	;0x2D, BlkNum3112 45
	DB	LetterG	;0x2E, BlkNum3121 46
	DB	LetterG	;0x2F, BlkNum3122 47
	DB	LetterG	;0x30, BlkNum3131 48
	DB	LetterG	;0x31, BlkNum3132 49
	DB	LetterE	;0x32, BlkNum320 50
	DB	LetterE	;0x33, BlkNum390 51
	DB	LetterE	;0x34, BlkNum330 52
	DB	LetterE	;0x35, BlkNum380 53
	DB	LetterE	;0x36, BlkNum340 54
	DB	LetterE	;0x37, BlkNum370 55
	DB	LetterE	;0x38, BlkNum350 56
	DB	LetterE	;0x39, BlkNum351 57
	DB	LetterE	;0x3A, BlkNum360 58
	DB	LetterE	;0x3B, BlkNum361 59
	DB	LetterE	;0x3C, BlkNum362 60
	DB	LetterE	;0x3D, BlkNum363 61
	DB	LetterE	;0x3E, BlkNum364 62
	DB	LetterE	;0x3F, BlkNum365 63
	DB	LetterW	;none, BlkNumVY1 64
	DB	LetterW	;none, BlkNumVY2 65
	DB	LetterW	;none, BlkNumVY3 66
	DB	LetterW	;none, BlkNumVY4 67
	DB	LetterW	;none, BlkNumVY5 68
	DB	LetterW	;none, BlkNumVY6 69
	DB	LetterW	;none, BlkNumEYF 70
	DB	LetterE	;0x47, BlkNumPHL 71
	DB	LetterE	;0x48, BlkNumPH1 72
	DB	LetterE	;0x49, BlkNumPH2 73
	DB	LetterE	;0x4A, BlkNumPH3 74
	DB	LetterE	;0x4B, BlkNumPH4 75
	DB	LetterE	;0x4C, BlkMZR Manzanar 76
	DB	LetterE
	DB	LetterE
;
;	
; Block number to Symbol for Throttle 9		;Blk#, Blk Name, d'Blk#
BlkThr9ToSym	DB	LetterE	;0x00, BlkNumRDY1 0
	DB	LetterE	;0x01, BlkNumRDY2 1
	DB	LetterE	;0x02, BlkNumFYL  2
	DB	LetterE	;0x03, BlkNum100  3
	DB	LetterE	;0x04, BlkNum101  4
	DB	LetterE	;0x05, BlkNum110  5
	DB	LetterE	;0x06, BlkNum111  6
	DB	LetterE	;0x07, BlkNum120  7
	DB	LetterE	;0x08, BlkNum121  8
	DB	LetterE	;0x09, BlkNum130  9
	DB	LetterE	;0x0A, BlkNum131 10
	DB	LetterE	;0x0B, BlkNum140 11
	DB	LetterE	;0x0C, BlkNum141 12
	DB	LetterE	;0x0D, BlkNumPT1 13
	DB	LetterE	;0x0E, BlkNumPT2 14
	DB	LetterE	;0x0F, BlkNum150 15
	DB	LetterE	;0x10, BlkNum151 16
	DB	LetterE	;0x11, BlkNum160 17
	DB	LetterE	;0x12, BlkNum170 18
	DB	LetterE	;0x13, BlkNum171 19
	DB	LetterE	;0x14, BlkNumSYL 20
	DB	LetterE	;0x15, BlkNum180 21
	DB	LetterE	;0x16, BlkNum190 22
	DB	LetterE	;0x17, BlkNum191 23
	DB	LetterE	;0x18, BlkNum200 24
	DB	LetterE	;0x19, BlkNum201 25
	DB	LetterE	;0x1A, BlkNum202 26
	DB	LetterE	;0x1B, BlkNum210 27
	DB	LetterE	;0x1C, BlkNum220 28
	DB	LetterE	;0x1D, BlkNum221 29
	DB	LetterE	;0x1E, BlkNum222 30
	DB	LetterE	;0x1F, BlkNum230 31
	DB	LetterE	;0x20, BlkNum240 32
	DB	LetterE	;0x21, BlkNum250 33
	DB	LetterE	;0x22, BlkNum251 34
	DB	LetterE	;0x23, BlkNum260 35
	DB	LetterE	;0x24, BlkNum270 36
	DB	LetterE	;0x25, BlkNum271 37
	DB	LetterE	;0x26, BlkNum280 38
	DB	LetterE	;0x27, BlkNum290 39
	DB	LetterE	;0x28, BlkNum291 40
	DB	LetterE	;0x29, BlkNum300 41
	DB	LetterH	;0x2A, BlkNum3101 42
	DB	LetterH	;0x2B, BlkNum3102 43
	DB	LetterH	;0x2C, BlkNum3111 44
	DB	LetterH	;0x2D, BlkNum3112 45
	DB	LetterH	;0x2E, BlkNum3121 46
	DB	LetterH	;0x2F, BlkNum3122 47
	DB	LetterH	;0x30, BlkNum3131 48
	DB	LetterH	;0x31, BlkNum3132 49
	DB	LetterE	;0x32, BlkNum320 50
	DB	LetterE	;0x33, BlkNum390 51
	DB	LetterE	;0x34, BlkNum330 52
	DB	LetterE	;0x35, BlkNum380 53
	DB	LetterE	;0x36, BlkNum340 54
	DB	LetterE	;0x37, BlkNum370 55
	DB	LetterE	;0x38, BlkNum350 56
	DB	LetterE	;0x39, BlkNum351 57
	DB	LetterE	;0x3A, BlkNum360 58
	DB	LetterE	;0x3B, BlkNum361 59
	DB	LetterE	;0x3C, BlkNum362 60
	DB	LetterE	;0x3D, BlkNum363 61
	DB	LetterE	;0x3E, BlkNum364 62
	DB	LetterE	;0x3F, BlkNum365 63
	DB	LetterE	;none, BlkNumVY1 64
	DB	LetterE	;none, BlkNumVY2 65
	DB	LetterE	;none, BlkNumVY3 66
	DB	LetterE	;none, BlkNumVY4 67
	DB	LetterE	;none, BlkNumVY5 68
	DB	LetterE	;none, BlkNumVY6 69
	DB	LetterE	;none, BlkNumEYF 70
	DB	LetterE	;0x47, BlkNumPHL 71
	DB	LetterE	;0x48, BlkNumPH1 72
	DB	LetterE	;0x49, BlkNumPH2 73
	DB	LetterE	;0x4A, BlkNumPH3 74
	DB	LetterE	;0x4B, BlkNumPH4 75
	DB	LetterE	;0x4C, BlkMZR Manzanar 76
	DB	LetterE
	DB	LetterE
;
;==============================================================================================
; Cab 6 to Throttle #	(Casper Tower)		;Blk#, Blk Name, d'Blk#
BlkCab6ToThr	DB	0x00	;0x00, BlkNumRDY1 0
	DB	0x00	;0x01, BlkNumRDY2 1
	DB	0x00	;0x02, BlkNumFYL  2
	DB	0x00	;0x03, BlkNum100  3
	DB	0x00	;0x04, BlkNum101  4
	DB	0x00	;0x05, BlkNum110  5
	DB	0x00	;0x06, BlkNum111  6
	DB	0x00	;0x07, BlkNum120  7
	DB	0x00	;0x08, BlkNum121  8
	DB	0x00	;0x09, BlkNum130  9
	DB	0x00	;0x0A, BlkNum131 10
	DB	0x00	;0x0B, BlkNum140 11
	DB	0x00	;0x0C, BlkNum141 12
	DB	0x00	;0x0D, BlkNumPT1 13
	DB	0x00	;0x0E, BlkNumPT2 14
	DB	0x00	;0x0F, BlkNum150 15
	DB	0x00	;0x10, BlkNum151 16
	DB	0x00	;0x11, BlkNum160 17
	DB	0x00	;0x12, BlkNum170 18
	DB	0x00	;0x13, BlkNum171 19
	DB	0x00	;0x14, BlkNumSYL 20
	DB	0x00	;0x15, BlkNum180 21
	DB	0x00	;0x16, BlkNum190 22
	DB	0x00	;0x17, BlkNum191 23
	DB	0x07	;0x18, BlkNum200 24
	DB	0x07	;0x19, BlkNum201 25
	DB	0x06	;0x1A, BlkNum202 26
	DB	0x06	;0x1B, BlkNum210 27
	DB	0x06	;0x1C, BlkNum220 28
	DB	0x06	;0x1D, BlkNum221 29
	DB	0x06	;0x1E, BlkNum222 30
	DB	0x06	;0x1F, BlkNum230 31
	DB	0x06	;0x20, BlkNum240 32
	DB	0x06	;0x21, BlkNum250 33
	DB	0x06	;0x22, BlkNum251 34
	DB	0x06	;0x23, BlkNum260 35
	DB	0x06	;0x24, BlkNum270 36
	DB	0x06	;0x25, BlkNum271 37
	DB	0x06	;0x26, BlkNum280 38
	DB	0x06	;0x27, BlkNum290 39
	DB	0x06	;0x28, BlkNum291 40
	DB	0x06	;0x29, BlkNum300 41
	DB	0x07	;0x2A, BlkNum3101 42
	DB	0x07	;0x2B, BlkNum3102 43
	DB	0x07	;0x2C, BlkNum3111 44
	DB	0x07	;0x2D, BlkNum3112 45
	DB	0x07	;0x2E, BlkNum3121 46
	DB	0x07	;0x2F, BlkNum3122 47
	DB	0x07	;0x30, BlkNum3131 48
	DB	0x07	;0x31, BlkNum3132 49
	DB	0x00	;0x32, BlkNum320 50
	DB	0x00	;0x33, BlkNum390 51
	DB	0x00	;0x34, BlkNum330 52
	DB	0x00	;0x35, BlkNum380 53
	DB	0x00	;0x36, BlkNum340 54
	DB	0x00	;0x37, BlkNum370 55
	DB	0x00	;0x38, BlkNum350 56
	DB	0x00	;0x39, BlkNum351 57
	DB	0x00	;0x3A, BlkNum360 58
	DB	0x00	;0x3B, BlkNum361 59
	DB	0x00	;0x3C, BlkNum362 60
	DB	0x00	;0x3D, BlkNum363 61
	DB	0x00	;0x3E, BlkNum364 62
	DB	0x00	;0x3F, BlkNum365 63
	DB	0x00	;none, BlkNumVY1 64
	DB	0x00	;none, BlkNumVY2 65
	DB	0x00	;none, BlkNumVY3 66
	DB	0x00	;none, BlkNumVY4 67
	DB	0x00	;none, BlkNumVY5 68
	DB	0x00	;none, BlkNumVY6 69
	DB	0x00	;none, BlkNumEYF 70
	DB	0x06	;0x47, BlkNumPHL 71
	DB	0x06	;0x48, BlkNumPH1 72
	DB	0x06	;0x49, BlkNumPH2 73
	DB	0x06	;0x4A, BlkNumPH3 74
	DB	0x06	;0x4B, BlkNumPH4 75
	DB	0x00	;0x4C, BlkMZR Manzanar 76
	DB	0x00
	DB	0x00
;
; Cab 7 to Throttle #	(Baker Tower)		;Blk#, Blk Name, d'Blk#
BlkCab7ToThr	DB	0x00	;0x00, BlkNumRDY1 0
	DB	0x00	;0x01, BlkNumRDY2 1
	DB	0x00	;0x02, BlkNumFYL  2
	DB	0x00	;0x03, BlkNum100  3
	DB	0x00	;0x04, BlkNum101  4
	DB	0x00	;0x05, BlkNum110  5
	DB	0x00	;0x06, BlkNum111  6
	DB	0x00	;0x07, BlkNum120  7
	DB	0x00	;0x08, BlkNum121  8
	DB	0x00	;0x09, BlkNum130  9
	DB	0x00	;0x0A, BlkNum131 10
	DB	0x00	;0x0B, BlkNum140 11
	DB	0x00	;0x0C, BlkNum141 12
	DB	0x00	;0x0D, BlkNumPT1 13
	DB	0x00	;0x0E, BlkNumPT2 14
	DB	0x00	;0x0F, BlkNum150 15
	DB	0x00	;0x10, BlkNum151 16
	DB	0x00	;0x11, BlkNum160 17
	DB	0x00	;0x12, BlkNum170 18
	DB	0x00	;0x13, BlkNum171 19
	DB	0x00	;0x14, BlkNumSYL 20
	DB	0x00	;0x15, BlkNum180 21
	DB	0x00	;0x16, BlkNum190 22
	DB	0x00	;0x17, BlkNum191 23
	DB	0x00	;0x18, BlkNum200 24
	DB	0x00	;0x19, BlkNum201 25
	DB	0x00	;0x1A, BlkNum202 26
	DB	0x00	;0x1B, BlkNum210 27
	DB	0x00	;0x1C, BlkNum220 28
	DB	0x00	;0x1D, BlkNum221 29
	DB	0x00	;0x1E, BlkNum222 30
	DB	0x00	;0x1F, BlkNum230 31
	DB	0x00	;0x20, BlkNum240 32
	DB	0x00	;0x21, BlkNum250 33
	DB	0x00	;0x22, BlkNum251 34
	DB	0x00	;0x23, BlkNum260 35
	DB	0x00	;0x24, BlkNum270 36
	DB	0x00	;0x25, BlkNum271 37
	DB	0x00	;0x26, BlkNum280 38
	DB	0x00	;0x27, BlkNum290 39
	DB	0x00	;0x28, BlkNum291 40
	DB	0x00	;0x29, BlkNum300 41
	DB	0x00	;0x2A, BlkNum3101 42
	DB	0x00	;0x2B, BlkNum3102 43
	DB	0x00	;0x2C, BlkNum3111 44
	DB	0x00	;0x2D, BlkNum3112 45
	DB	0x00	;0x2E, BlkNum3121 46
	DB	0x00	;0x2F, BlkNum3122 47
	DB	0x00	;0x30, BlkNum3131 48
	DB	0x00	;0x31, BlkNum3132 49
	DB	0x00	;0x32, BlkNum320 50
	DB	0x00	;0x33, BlkNum390 51
	DB	0x00	;0x34, BlkNum330 52
	DB	0x00	;0x35, BlkNum380 53
	DB	0x00	;0x36, BlkNum340 54
	DB	0x00	;0x37, BlkNum370 55
	DB	0x00	;0x38, BlkNum350 56
	DB	0x00	;0x39, BlkNum351 57
	DB	0x00	;0x3A, BlkNum360 58
	DB	0x00	;0x3B, BlkNum361 59
	DB	0x00	;0x3C, BlkNum362 60
	DB	0x00	;0x3D, BlkNum363 61
	DB	0x00	;0x3E, BlkNum364 62
	DB	0x00	;0x3F, BlkNum365 63
	DB	0x00	;none, BlkNumVY1 64
	DB	0x00	;none, BlkNumVY2 65
	DB	0x00	;none, BlkNumVY3 66
	DB	0x00	;none, BlkNumVY4 67
	DB	0x00	;none, BlkNumVY5 68
	DB	0x00	;none, BlkNumVY6 69
	DB	0x00	;none, BlkNumEYF 70
	DB	0x00	;0x47, BlkNumPHL 71
	DB	0x00	;0x48, BlkNumPH1 72
	DB	0x00	;0x49, BlkNumPH2 73
	DB	0x00	;0x4A, BlkNumPH3 74
	DB	0x00	;0x4B, BlkNumPH4 75
	DB	0x00	;0x4C, BlkMZR Manzanar 76
	DB	0x00
	DB	0x00
;
; Cab 8 to Throttle #			;Blk#, Blk Name, d'Blk#
BlkCab8ToThr	DB	0x00	;0x00, BlkNumRDY1 0
	DB	0x00	;0x01, BlkNumRDY2 1
	DB	0x00	;0x02, BlkNumFYL  2
	DB	0x00	;0x03, BlkNum100  3
	DB	0x00	;0x04, BlkNum101  4
	DB	0x00	;0x05, BlkNum110  5
	DB	0x00	;0x06, BlkNum111  6
	DB	0x00	;0x07, BlkNum120  7
	DB	0x00	;0x08, BlkNum121  8
	DB	0x00	;0x09, BlkNum130  9
	DB	0x00	;0x0A, BlkNum131 10
	DB	0x00	;0x0B, BlkNum140 11
	DB	0x00	;0x0C, BlkNum141 12
	DB	0x00	;0x0D, BlkNumPT1 13
	DB	0x00	;0x0E, BlkNumPT2 14
	DB	0x00	;0x0F, BlkNum150 15
	DB	0x00	;0x10, BlkNum151 16
	DB	0x00	;0x11, BlkNum160 17
	DB	0x00	;0x12, BlkNum170 18
	DB	0x00	;0x13, BlkNum171 19
	DB	0x00	;0x14, BlkNumSYL 20
	DB	0x00	;0x15, BlkNum180 21
	DB	0x00	;0x16, BlkNum190 22
	DB	0x00	;0x17, BlkNum191 23
	DB	0x00	;0x18, BlkNum200 24
	DB	0x00	;0x19, BlkNum201 25
	DB	0x00	;0x1A, BlkNum202 26
	DB	0x00	;0x1B, BlkNum210 27
	DB	0x00	;0x1C, BlkNum220 28
	DB	0x00	;0x1D, BlkNum221 29
	DB	0x00	;0x1E, BlkNum222 30
	DB	0x00	;0x1F, BlkNum230 31
	DB	0x00	;0x20, BlkNum240 32
	DB	0x00	;0x21, BlkNum250 33
	DB	0x00	;0x22, BlkNum251 34
	DB	0x00	;0x23, BlkNum260 35
	DB	0x00	;0x24, BlkNum270 36
	DB	0x00	;0x25, BlkNum271 37
	DB	0x00	;0x26, BlkNum280 38
	DB	0x00	;0x27, BlkNum290 39
	DB	0x00	;0x28, BlkNum291 40
	DB	0x00	;0x29, BlkNum300 41
	DB	0x00	;0x2A, BlkNum3101 42
	DB	0x00	;0x2B, BlkNum3102 43
	DB	0x00	;0x2C, BlkNum3111 44
	DB	0x00	;0x2D, BlkNum3112 45
	DB	0x00	;0x2E, BlkNum3121 46
	DB	0x00	;0x2F, BlkNum3122 47
	DB	0x00	;0x30, BlkNum3131 48
	DB	0x00	;0x31, BlkNum3132 49
	DB	0x00	;0x32, BlkNum320 50
	DB	0x00	;0x33, BlkNum390 51
	DB	0x00	;0x34, BlkNum330 52
	DB	0x00	;0x35, BlkNum380 53
	DB	0x00	;0x36, BlkNum340 54
	DB	0x00	;0x37, BlkNum370 55
	DB	0x00	;0x38, BlkNum350 56
	DB	0x00	;0x39, BlkNum351 57
	DB	0x00	;0x3A, BlkNum360 58
	DB	0x00	;0x3B, BlkNum361 59
	DB	0x00	;0x3C, BlkNum362 60
	DB	0x00	;0x3D, BlkNum363 61
	DB	0x00	;0x3E, BlkNum364 62
	DB	0x00	;0x3F, BlkNum365 63
	DB	0x00	;none, BlkNumVY1 64
	DB	0x00	;none, BlkNumVY2 65
	DB	0x00	;none, BlkNumVY3 66
	DB	0x00	;none, BlkNumVY4 67
	DB	0x00	;none, BlkNumVY5 68
	DB	0x00	;none, BlkNumVY6 69
	DB	0x00	;none, BlkNumEYF 70
	DB	0x00	;0x47, BlkNumPHL 71
	DB	0x00	;0x48, BlkNumPH1 72
	DB	0x00	;0x49, BlkNumPH2 73
	DB	0x00	;0x4A, BlkNumPH3 74
	DB	0x00	;0x4B, BlkNumPH4 75
	DB	0x00	;0x4C, BlkMZR Manzanar 76
	DB	0x00
	DB	0x00
;
; Cab 9 to Throttle #	(Dawson Tower)		;Blk#, Blk Name, d'Blk#
BlkCab9ToThr	DB	0x00	;0x00, BlkNumRDY1 0
	DB	0x00	;0x01, BlkNumRDY2 1
	DB	0x00	;0x02, BlkNumFYL  2
	DB	0x00	;0x03, BlkNum100  3
	DB	0x00	;0x04, BlkNum101  4
	DB	0x00	;0x05, BlkNum110  5
	DB	0x00	;0x06, BlkNum111  6
	DB	0x00	;0x07, BlkNum120  7
	DB	0x00	;0x08, BlkNum121  8
	DB	0x00	;0x09, BlkNum130  9
	DB	0x00	;0x0A, BlkNum131 10
	DB	0x00	;0x0B, BlkNum140 11
	DB	0x00	;0x0C, BlkNum141 12
	DB	0x00	;0x0D, BlkNumPT1 13
	DB	0x00	;0x0E, BlkNumPT2 14
	DB	0x00	;0x0F, BlkNum150 15
	DB	0x00	;0x10, BlkNum151 16
	DB	0x00	;0x11, BlkNum160 17
	DB	0x00	;0x12, BlkNum170 18
	DB	0x00	;0x13, BlkNum171 19
	DB	0x00	;0x14, BlkNumSYL 20
	DB	0x00	;0x15, BlkNum180 21
	DB	0x00	;0x16, BlkNum190 22
	DB	0x00	;0x17, BlkNum191 23
	DB	0x00	;0x18, BlkNum200 24
	DB	0x00	;0x19, BlkNum201 25
	DB	0x00	;0x1A, BlkNum202 26
	DB	0x00	;0x1B, BlkNum210 27
	DB	0x00	;0x1C, BlkNum220 28
	DB	0x00	;0x1D, BlkNum221 29
	DB	0x00	;0x1E, BlkNum222 30
	DB	0x00	;0x1F, BlkNum230 31
	DB	0x00	;0x20, BlkNum240 32
	DB	0x00	;0x21, BlkNum250 33
	DB	0x00	;0x22, BlkNum251 34
	DB	0x00	;0x23, BlkNum260 35
	DB	0x00	;0x24, BlkNum270 36
	DB	0x00	;0x25, BlkNum271 37
	DB	0x00	;0x26, BlkNum280 38
	DB	0x00	;0x27, BlkNum290 39
	DB	0x00	;0x28, BlkNum291 40
	DB	0x00	;0x29, BlkNum300 41
	DB	0x00	;0x2A, BlkNum3101 42
	DB	0x00	;0x2B, BlkNum3102 43
	DB	0x00	;0x2C, BlkNum3111 44
	DB	0x00	;0x2D, BlkNum3112 45
	DB	0x00	;0x2E, BlkNum3121 46
	DB	0x00	;0x2F, BlkNum3122 47
	DB	0x00	;0x30, BlkNum3131 48
	DB	0x00	;0x31, BlkNum3132 49
	DB	0x00	;0x32, BlkNum320 50
	DB	0x00	;0x33, BlkNum390 51
	DB	0x00	;0x34, BlkNum330 52
	DB	0x00	;0x35, BlkNum380 53
	DB	0x00	;0x36, BlkNum340 54
	DB	0x00	;0x37, BlkNum370 55
	DB	0x00	;0x38, BlkNum350 56
	DB	0x00	;0x39, BlkNum351 57
	DB	0x00	;0x3A, BlkNum360 58
	DB	0x00	;0x3B, BlkNum361 59
	DB	0x00	;0x3C, BlkNum362 60
	DB	0x00	;0x3D, BlkNum363 61
	DB	0x00	;0x3E, BlkNum364 62
	DB	0x00	;0x3F, BlkNum365 63
	DB	0x00	;none, BlkNumVY1 64
	DB	0x00	;none, BlkNumVY2 65
	DB	0x00	;none, BlkNumVY3 66
	DB	0x00	;none, BlkNumVY4 67
	DB	0x00	;none, BlkNumVY5 68
	DB	0x00	;none, BlkNumVY6 69
	DB	0x00	;none, BlkNumEYF 70
	DB	0x00	;0x47, BlkNumPHL 71
	DB	0x00	;0x48, BlkNumPH1 72
	DB	0x00	;0x49, BlkNumPH2 73
	DB	0x00	;0x4A, BlkNumPH3 74
	DB	0x00	;0x4B, BlkNumPH4 75
	DB	0x00	;0x4C, BlkMZR Manzanar 76
	DB	0x00
	DB	0x00
;
;==============================================================================================
; Translate a block used by a throttle to a cab number
;
; Throttle 6 to Cab #			;Blk#, Blk Name, d'Blk#
BlkThr6ToCab	DB	0x00	;0x00, BlkNumRDY1 0
	DB	0x00	;0x01, BlkNumRDY2 1
	DB	0x00	;0x02, BlkNumFYL  2
	DB	0x00	;0x03, BlkNum100  3
	DB	0x00	;0x04, BlkNum101  4
	DB	0x00	;0x05, BlkNum110  5
	DB	0x00	;0x06, BlkNum111  6
	DB	0x00	;0x07, BlkNum120  7
	DB	0x00	;0x08, BlkNum121  8
	DB	0x00	;0x09, BlkNum130  9
	DB	0x00	;0x0A, BlkNum131 10
	DB	0x00	;0x0B, BlkNum140 11
	DB	0x00	;0x0C, BlkNum141 12
	DB	0x00	;0x0D, BlkNumPT1 13
	DB	0x00	;0x0E, BlkNumPT2 14
	DB	0x00	;0x0F, BlkNum150 15
	DB	0x00	;0x10, BlkNum151 16
	DB	0x00	;0x11, BlkNum160 17
	DB	0x00	;0x12, BlkNum170 18
	DB	0x00	;0x13, BlkNum171 19
	DB	0x00	;0x14, BlkNumSYL 20
	DB	0x00	;0x15, BlkNum180 21
	DB	0x00	;0x16, BlkNum190 22
	DB	0x00	;0x17, BlkNum191 23
	DB	0x07	;0x18, BlkNum200 24
	DB	0x07	;0x19, BlkNum201 25
	DB	0x06	;0x1A, BlkNum202 26
	DB	0x06	;0x1B, BlkNum210 27
	DB	0x06	;0x1C, BlkNum220 28
	DB	0x06	;0x1D, BlkNum221 29
	DB	0x06	;0x1E, BlkNum222 30
	DB	0x06	;0x1F, BlkNum230 31
	DB	0x06	;0x20, BlkNum240 32
	DB	0x06	;0x21, BlkNum250 33
	DB	0x06	;0x22, BlkNum251 34
	DB	0x06	;0x23, BlkNum260 35
	DB	0x06	;0x24, BlkNum270 36
	DB	0x06	;0x25, BlkNum271 37
	DB	0x06	;0x26, BlkNum280 38
	DB	0x06	;0x27, BlkNum290 39
	DB	0x06	;0x28, BlkNum291 40
	DB	0x06	;0x29, BlkNum300 41
	DB	0x07	;0x2A, BlkNum3101 42
	DB	0x07	;0x2B, BlkNum3102 43
	DB	0x07	;0x2C, BlkNum3111 44
	DB	0x07	;0x2D, BlkNum3112 45
	DB	0x07	;0x2E, BlkNum3121 46
	DB	0x07	;0x2F, BlkNum3122 47
	DB	0x07	;0x30, BlkNum3131 48
	DB	0x07	;0x31, BlkNum3132 49
	DB	0x00	;0x32, BlkNum320 50
	DB	0x00	;0x33, BlkNum390 51
	DB	0x00	;0x34, BlkNum330 52
	DB	0x00	;0x35, BlkNum380 53
	DB	0x00	;0x36, BlkNum340 54
	DB	0x00	;0x37, BlkNum370 55
	DB	0x00	;0x38, BlkNum350 56
	DB	0x00	;0x39, BlkNum351 57
	DB	0x00	;0x3A, BlkNum360 58
	DB	0x00	;0x3B, BlkNum361 59
	DB	0x00	;0x3C, BlkNum362 60
	DB	0x00	;0x3D, BlkNum363 61
	DB	0x00	;0x3E, BlkNum364 62
	DB	0x00	;0x3F, BlkNum365 63
	DB	0x00	;none, BlkNumVY1 64
	DB	0x00	;none, BlkNumVY2 65
	DB	0x00	;none, BlkNumVY3 66
	DB	0x00	;none, BlkNumVY4 67
	DB	0x00	;none, BlkNumVY5 68
	DB	0x00	;none, BlkNumVY6 69
	DB	0x00	;none, BlkNumEYF 70
	DB	0x06	;0x47, BlkNumPHL 71
	DB	0x06	;0x48, BlkNumPH1 72
	DB	0x06	;0x49, BlkNumPH2 73
	DB	0x06	;0x4A, BlkNumPH3 74
	DB	0x06	;0x4B, BlkNumPH4 75
	DB	0x00	;0x4C, BlkMZR Manzanar 76
	DB	0x00
	DB	0x00
;
; Throttle 7 to Cab #			;Blk#, Blk Name, d'Blk#
BlkThr7ToCab	DB	0x00	;0x00, BlkNumRDY1 0
	DB	0x00	;0x01, BlkNumRDY2 1
	DB	0x00	;0x02, BlkNumFYL  2
	DB	0x00	;0x03, BlkNum100  3
	DB	0x00	;0x04, BlkNum101  4
	DB	0x00	;0x05, BlkNum110  5
	DB	0x00	;0x06, BlkNum111  6
	DB	0x00	;0x07, BlkNum120  7
	DB	0x00	;0x08, BlkNum121  8
	DB	0x00	;0x09, BlkNum130  9
	DB	0x00	;0x0A, BlkNum131 10
	DB	0x00	;0x0B, BlkNum140 11
	DB	0x00	;0x0C, BlkNum141 12
	DB	0x00	;0x0D, BlkNumPT1 13
	DB	0x00	;0x0E, BlkNumPT2 14
	DB	0x00	;0x0F, BlkNum150 15
	DB	0x00	;0x10, BlkNum151 16
	DB	0x00	;0x11, BlkNum160 17
	DB	0x00	;0x12, BlkNum170 18
	DB	0x00	;0x13, BlkNum171 19
	DB	0x00	;0x14, BlkNumSYL 20
	DB	0x00	;0x15, BlkNum180 21
	DB	0x00	;0x16, BlkNum190 22
	DB	0x00	;0x17, BlkNum191 23
	DB	0x06	;0x18, BlkNum200 24
	DB	0x06	;0x19, BlkNum201 25
	DB	0x00	;0x1A, BlkNum202 26
	DB	0x00	;0x1B, BlkNum210 27
	DB	0x00	;0x1C, BlkNum220 28
	DB	0x00	;0x1D, BlkNum221 29
	DB	0x00	;0x1E, BlkNum222 30
	DB	0x00	;0x1F, BlkNum230 31
	DB	0x00	;0x20, BlkNum240 32
	DB	0x00	;0x21, BlkNum250 33
	DB	0x00	;0x22, BlkNum251 34
	DB	0x00	;0x23, BlkNum260 35
	DB	0x00	;0x24, BlkNum270 36
	DB	0x00	;0x25, BlkNum271 37
	DB	0x00	;0x26, BlkNum280 38
	DB	0x00	;0x27, BlkNum290 39
	DB	0x00	;0x28, BlkNum291 40
	DB	0x00	;0x29, BlkNum300 41
	DB	0x06	;0x2A, BlkNum3101 42
	DB	0x06	;0x2B, BlkNum3102 43
	DB	0x06	;0x2C, BlkNum3111 44
	DB	0x06	;0x2D, BlkNum3112 45
	DB	0x06	;0x2E, BlkNum3121 46
	DB	0x06	;0x2F, BlkNum3122 47
	DB	0x06	;0x30, BlkNum3131 48
	DB	0x06	;0x31, BlkNum3132 49
	DB	0x00	;0x32, BlkNum320 50
	DB	0x00	;0x33, BlkNum390 51
	DB	0x00	;0x34, BlkNum330 52
	DB	0x00	;0x35, BlkNum380 53
	DB	0x00	;0x36, BlkNum340 54
	DB	0x00	;0x37, BlkNum370 55
	DB	0x00	;0x38, BlkNum350 56
	DB	0x00	;0x39, BlkNum351 57
	DB	0x00	;0x3A, BlkNum360 58
	DB	0x00	;0x3B, BlkNum361 59
	DB	0x00	;0x3C, BlkNum362 60
	DB	0x00	;0x3D, BlkNum363 61
	DB	0x00	;0x3E, BlkNum364 62
	DB	0x00	;0x3F, BlkNum365 63
	DB	0x00	;none, BlkNumVY1 64
	DB	0x00	;none, BlkNumVY2 65
	DB	0x00	;none, BlkNumVY3 66
	DB	0x00	;none, BlkNumVY4 67
	DB	0x00	;none, BlkNumVY5 68
	DB	0x00	;none, BlkNumVY6 69
	DB	0x00	;none, BlkNumEYF 70
	DB	0x00	;0x47, BlkNumPHL 71
	DB	0x00	;0x48, BlkNumPH1 72
	DB	0x00	;0x49, BlkNumPH2 73
	DB	0x00	;0x4A, BlkNumPH3 74
	DB	0x00	;0x4B, BlkNumPH4 75
	DB	0x00	;0x4C, BlkMZR Manzanar 76
	DB	0x00
	DB	0x00
;
; Throttle 8 to Cab #	(NOT USED)		;Blk#, Blk Name, d'Blk#
BlkThr8ToCab	DB	0x00	;0x00, BlkNumRDY1 0
	DB	0x00	;0x01, BlkNumRDY2 1
	DB	0x00	;0x02, BlkNumFYL  2
	DB	0x00	;0x03, BlkNum100  3
	DB	0x00	;0x04, BlkNum101  4
	DB	0x00	;0x05, BlkNum110  5
	DB	0x00	;0x06, BlkNum111  6
	DB	0x00	;0x07, BlkNum120  7
	DB	0x00	;0x08, BlkNum121  8
	DB	0x00	;0x09, BlkNum130  9
	DB	0x00	;0x0A, BlkNum131 10
	DB	0x00	;0x0B, BlkNum140 11
	DB	0x00	;0x0C, BlkNum141 12
	DB	0x00	;0x0D, BlkNumPT1 13
	DB	0x00	;0x0E, BlkNumPT2 14
	DB	0x00	;0x0F, BlkNum150 15
	DB	0x00	;0x10, BlkNum151 16
	DB	0x00	;0x11, BlkNum160 17
	DB	0x00	;0x12, BlkNum170 18
	DB	0x00	;0x13, BlkNum171 19
	DB	0x00	;0x14, BlkNumSYL 20
	DB	0x00	;0x15, BlkNum180 21
	DB	0x00	;0x16, BlkNum190 22
	DB	0x00	;0x17, BlkNum191 23
	DB	0x00	;0x18, BlkNum200 24
	DB	0x00	;0x19, BlkNum201 25
	DB	0x00	;0x1A, BlkNum202 26
	DB	0x00	;0x1B, BlkNum210 27
	DB	0x00	;0x1C, BlkNum220 28
	DB	0x00	;0x1D, BlkNum221 29
	DB	0x00	;0x1E, BlkNum222 30
	DB	0x00	;0x1F, BlkNum230 31
	DB	0x00	;0x20, BlkNum240 32
	DB	0x00	;0x21, BlkNum250 33
	DB	0x00	;0x22, BlkNum251 34
	DB	0x00	;0x23, BlkNum260 35
	DB	0x00	;0x24, BlkNum270 36
	DB	0x00	;0x25, BlkNum271 37
	DB	0x00	;0x26, BlkNum280 38
	DB	0x00	;0x27, BlkNum290 39
	DB	0x00	;0x28, BlkNum291 40
	DB	0x00	;0x29, BlkNum300 41
	DB	0x00	;0x2A, BlkNum3101 42
	DB	0x00	;0x2B, BlkNum3102 43
	DB	0x00	;0x2C, BlkNum3111 44
	DB	0x00	;0x2D, BlkNum3112 45
	DB	0x00	;0x2E, BlkNum3121 46
	DB	0x00	;0x2F, BlkNum3122 47
	DB	0x00	;0x30, BlkNum3131 48
	DB	0x00	;0x31, BlkNum3132 49
	DB	0x00	;0x32, BlkNum320 50
	DB	0x00	;0x33, BlkNum390 51
	DB	0x00	;0x34, BlkNum330 52
	DB	0x00	;0x35, BlkNum380 53
	DB	0x00	;0x36, BlkNum340 54
	DB	0x00	;0x37, BlkNum370 55
	DB	0x00	;0x38, BlkNum350 56
	DB	0x00	;0x39, BlkNum351 57
	DB	0x00	;0x3A, BlkNum360 58
	DB	0x00	;0x3B, BlkNum361 59
	DB	0x00	;0x3C, BlkNum362 60
	DB	0x00	;0x3D, BlkNum363 61
	DB	0x00	;0x3E, BlkNum364 62
	DB	0x00	;0x3F, BlkNum365 63
	DB	0x00	;none, BlkNumVY1 64
	DB	0x00	;none, BlkNumVY2 65
	DB	0x00	;none, BlkNumVY3 66
	DB	0x00	;none, BlkNumVY4 67
	DB	0x00	;none, BlkNumVY5 68
	DB	0x00	;none, BlkNumVY6 69
	DB	0x00	;none, BlkNumEYF 70
	DB	0x00	;0x47, BlkNumPHL 71
	DB	0x00	;0x48, BlkNumPH1 72
	DB	0x00	;0x49, BlkNumPH2 73
	DB	0x00	;0x4A, BlkNumPH3 74
	DB	0x00	;0x4B, BlkNumPH4 75
	DB	0x00	;0x4C, BlkMZR Manzanar 76
	DB	0x00
	DB	0x00
;
; Throttle 9 to Cab #	(NOT USED)		;Blk#, Blk Name, d'Blk#
BlkThr9ToCab	DB	0x00	;0x00, BlkNumRDY1 0
	DB	0x00	;0x01, BlkNumRDY2 1
	DB	0x00	;0x02, BlkNumFYL  2
	DB	0x00	;0x03, BlkNum100  3
	DB	0x00	;0x04, BlkNum101  4
	DB	0x00	;0x05, BlkNum110  5
	DB	0x00	;0x06, BlkNum111  6
	DB	0x00	;0x07, BlkNum120  7
	DB	0x00	;0x08, BlkNum121  8
	DB	0x00	;0x09, BlkNum130  9
	DB	0x00	;0x0A, BlkNum131 10
	DB	0x00	;0x0B, BlkNum140 11
	DB	0x00	;0x0C, BlkNum141 12
	DB	0x00	;0x0D, BlkNumPT1 13
	DB	0x00	;0x0E, BlkNumPT2 14
	DB	0x00	;0x0F, BlkNum150 15
	DB	0x00	;0x10, BlkNum151 16
	DB	0x00	;0x11, BlkNum160 17
	DB	0x00	;0x12, BlkNum170 18
	DB	0x00	;0x13, BlkNum171 19
	DB	0x00	;0x14, BlkNumSYL 20
	DB	0x00	;0x15, BlkNum180 21
	DB	0x00	;0x16, BlkNum190 22
	DB	0x00	;0x17, BlkNum191 23
	DB	0x00	;0x18, BlkNum200 24
	DB	0x00	;0x19, BlkNum201 25
	DB	0x00	;0x1A, BlkNum202 26
	DB	0x00	;0x1B, BlkNum210 27
	DB	0x00	;0x1C, BlkNum220 28
	DB	0x00	;0x1D, BlkNum221 29
	DB	0x00	;0x1E, BlkNum222 30
	DB	0x00	;0x1F, BlkNum230 31
	DB	0x00	;0x20, BlkNum240 32
	DB	0x00	;0x21, BlkNum250 33
	DB	0x00	;0x22, BlkNum251 34
	DB	0x00	;0x23, BlkNum260 35
	DB	0x00	;0x24, BlkNum270 36
	DB	0x00	;0x25, BlkNum271 37
	DB	0x00	;0x26, BlkNum280 38
	DB	0x00	;0x27, BlkNum290 39
	DB	0x00	;0x28, BlkNum291 40
	DB	0x00	;0x29, BlkNum300 41
	DB	0x00	;0x2A, BlkNum3101 42
	DB	0x00	;0x2B, BlkNum3102 43
	DB	0x00	;0x2C, BlkNum3111 44
	DB	0x00	;0x2D, BlkNum3112 45
	DB	0x00	;0x2E, BlkNum3121 46
	DB	0x00	;0x2F, BlkNum3122 47
	DB	0x00	;0x30, BlkNum3131 48
	DB	0x00	;0x31, BlkNum3132 49
	DB	0x00	;0x32, BlkNum320 50
	DB	0x00	;0x33, BlkNum390 51
	DB	0x00	;0x34, BlkNum330 52
	DB	0x00	;0x35, BlkNum380 53
	DB	0x00	;0x36, BlkNum340 54
	DB	0x00	;0x37, BlkNum370 55
	DB	0x00	;0x38, BlkNum350 56
	DB	0x00	;0x39, BlkNum351 57
	DB	0x00	;0x3A, BlkNum360 58
	DB	0x00	;0x3B, BlkNum361 59
	DB	0x00	;0x3C, BlkNum362 60
	DB	0x00	;0x3D, BlkNum363 61
	DB	0x00	;0x3E, BlkNum364 62
	DB	0x00	;0x3F, BlkNum365 63
	DB	0x00	;none, BlkNumVY1 64
	DB	0x00	;none, BlkNumVY2 65
	DB	0x00	;none, BlkNumVY3 66
	DB	0x00	;none, BlkNumVY4 67
	DB	0x00	;none, BlkNumVY5 68
	DB	0x00	;none, BlkNumVY6 69
	DB	0x00	;none, BlkNumEYF 70
	DB	0x00	;0x47, BlkNumPHL 71
	DB	0x00	;0x48, BlkNumPH1 72
	DB	0x00	;0x49, BlkNumPH2 73
	DB	0x00	;0x4A, BlkNumPH3 74
	DB	0x00	;0x4B, BlkNumPH4 75
	DB	0x00	;0x4C, BlkMZR Manzanar 76
	DB	0x00
	DB	0x00
;
;
	include	MLSMData.inc
;