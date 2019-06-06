	subtitle	MLSMData.inc
	page
;
;============================================================================================================
;
;  FileName: MLSMData.inc
;  Date: 7/12/09
;  File Version: 1.0.0
;  
;  Author: David M. Flynn
;  Company: HPRR
;  Project: Casper Tower
;
;============================================================================================================
; Revision History
;
; 1.0.0  7/12/2009	First reved version.
;
;============================================================================================================
; Notes:
;
;  This file has data that is loaded from the eeROM to SRAM
;  evDataROM*256 is added to the PC here to get the SRAM address
;
;  The BD and DW commands are related to the STR and RES commands.
;  The label is stored with the currnt PC value then
;   the PC is incremented by the data length
;  A "d.d" file is created containing the data for the eerom file.
;  Copy the "d.d" file to the WWW page subdirectory then run eeROM to make an eeROM.binary file.
;  Then run eeROM Uploader to upload the eeROM.binary file into the first 24LC256 at U2 on the Brain GP CPU.
;
;============================================================================================================
;
SMNumOff	EQU	0x00
SMNum2Off	EQU	0x02
SMNum3Off	EQU	0x04
SMRootBlk	EQU	0x06
SMNormBlk	EQU	0x08
SMRevBlk	EQU	0x0A
SMLamp	EQU	0x0C	;Block#(offset to BlkModID):Output(00,02,0A,0C)
SMLamp2	EQU	0x0E
SMToggle	EQU	0x10	;Bit 6 inverts the toggle
SMEnable	EQU	0x12	;Bit 6 inverts the enable
SMFlagsWord	EQU	0x14
;
SMAddBlk	EQU	0x16
;None	EQU	0xFEFE
;EOD	EQU	0xFF
;
SMEnableInvert	EQU	0x4000
SMOffRouteFlag	EQU	0x0200
SMOffRouteFlagBit	EQU	0x01
OddSMOBFlag	EQU	0x4000
OddSMOBFlagBit	EQU	0x06
; Overview Tower Zone Disable Pseudo SMs
; SM500 is the BPK Mode 2 status bit
DisableOVZoneD2	EQU	d'501'	;245,Disable Overview Tower Zone D2
DisableOVZoneD1	EQU	d'502'	;Disable Overview Tower Zone D1
DisableOVZoneC3	EQU	d'503'	;Disable Overview Tower Zone C3
DisableOVZoneC2	EQU	d'504'	;Disable Overview Tower Zone C2
DisableOVZoneC1	EQU	d'505'	;Disable Overview Tower Zone C1
DisableOVZoneB2	EQU	d'506'	;Disable Overview Tower Zone B2
DisableOVZoneB1	EQU	d'507'	;Disable Overview Tower Zone B1
DisableOVZoneA3	EQU	d'508'	;Disable Overview Tower Zone A3
DisableOVZoneA2	EQU	d'509'	;Disable Overview Tower Zone A2
DisableOVZoneA1	EQU	d'510'	;254,Disable Overview Tower Zone A1
;SM511	DW	0x1040	;Disable Auto Blk Selector
;
EnableDTZoneD2	EQU	d'482'	;SM CTRL psuedo SM, Enable D2
EnableDTZoneD1	EQU	d'483'	;SM CTRL psuedo SM, Enable D1
EnableCTZoneC3	EQU	d'484'	;SM CTRL psuedo SM, Enable C3
EnableCTZoneC2	EQU	d'485'	;SM CTRL psuedo SM, Enable C2
EnableCTZoneC1	EQU	d'486'	;SM CTRL psuedo SM, Enable C1
EnableBTZoneB2	EQU	d'487'	;SM CTRL psuedo SM, Enable B2
EnableBTZoneB1	EQU	d'488'	;SM CTRL psuedo SM, Enable B1
EnableATZoneA3	EQU	d'489'	;SM CTRL psuedo SM, Enable A3
EnableATZoneA2	EQU	d'490'	;SM CTRL psuedo SM, Enable A2
EnableATZoneA1	EQU	d'491'	;SM CTRL psuedo SM, Enable A1
;
;-----------------------
; SMToggle Flags
SMToggleInvert	EQU	0x4000
;
;-----------------------
; SMFlagsWord Flags
;
AllowInMode2	EQU	0x0001
AIM2_Bit	EQU	0
DisabledInMode2	EQU	0x0000
;
SMLamp2InvertFlag	EQU	0x0002	;Lamps are normally on when the SM is active
SML2InvFlag	EQU	1	;bit number for BSF/BCF
;
SM2InvertFlag	EQU	0x0004	;Not to ctrl SMs, used to light LEDs
SM2InvFlag	EQU	2
SM2RequiredFlag	EQU	0x0008
SM2ReqFlag	EQU	3
RevBlkRequired	EQU	0x0010
RevBlkReqFlag	EQU	4
RootCabRequired	EQU	0x0040
RootCabReqFlag	EQU	6
;
SMLampIsOB	EQU	0x0020	;Use output board instead of block module
SMLampIsOBFlag	EQU	5
;-----------------------
;
MLSM1
MLSM21
	DW	d'55'	;SM Num 1
	DW	d'84'	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum210	;ROOT
	DW	BlkNum200	;NORMAL
	DW	BlkNum202	;REV.
	DW	0x1C02	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag+RevBlkRequired	;Flags
; Clear SMs for 210 to 201 traffic
	DW	d'55'	;SM Num 1
	DW	d'84'	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum202	;ROOT
	DW	None	;NORMAL
	DW	BlkNum210	;REV.
	DW	None	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	RevBlkRequired	;Flags
MLSM22
	DW	d'54'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum210	;ROOT
	DW	BlkNum200	;NORMAL
	DW	BlkNum201	;REV.
	DW	0x1B0C	;SM LAMP
	DW	0x1B02	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
; Clear SM for 210 to 202 traffic
;	DW	d'54'	;SM Num 1
;	DW	None	;SM Num 2
;	DW	None	;SM Num 3
;	DW	BlkNum210	;ROOT
;	DW	BlkNum202	;NORMAL
;	DW	None	;REV.
;	DW	None	;SM LAMP
;	DW	None	;SM Lamp2
;	DW	None	;SM Toggle Sw
;	DW	EnableCTZoneC1	;SM Enable
;	DW	0x0000	;Flags
;210 to 220
	DW	d'56'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum210	;ROOT
	DW	BlkNum220	;NORMAL
	DW	None	;REV.
	DW	0x1C0C	;SM LAMP
	DW	0x1D02	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;210 to 221
	DW	d'56'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum210	;ROOT
	DW	None	;NORMAL
	DW	BlkNum221	;REV.
	DW	None	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;210 to 222
	DW	d'56'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum210	;ROOT
	DW	None	;NORMAL
	DW	BlkNum222	;REV.
	DW	None	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;210 to 222
	DW	d'57'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum210	;ROOT 210 End
	DW	BlkNum221	;NORMAL
	DW	BlkNum222	;REV.
	DW	0x1F02	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw 0x204B+SMToggleInvert
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;230 to 220
	DW	d'59'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum230	;ROOT
	DW	BlkNum220	;NORMAL
	DW	None	;REV.
	DW	0x1F0A	;SM LAMP
	DW	0x1F0C	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;230 to 221	
	DW	d'59'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum230	;ROOT
	DW	None	;NORMAL
	DW	BlkNum221	;REV.
	DW	None	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;230 to 222	
	DW	d'59'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum230	;ROOT
	DW	None	;NORMAL
	DW	BlkNum222	;REV.
	DW	None	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;230 to 222
	DW	d'58'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum230	;ROOT 230 End
	DW	BlkNum221	;NORMAL
	DW	BlkNum222	;REV.
	DW	0x2002	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw 0x204A+SMToggleInvert
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;240 to 251
	DW	d'60'	;SM #
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum240	;ROOT
	DW	BlkNum250	;NORMAL
	DW	BlkNum251	;REV.
	DW	0x2102	;SM LAMP 240-251
	DW	0x210C	;SM Lamp2 240-250
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC1	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;260 to 251
	DW	d'61'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum260	;ROOT
	DW	BlkNum250	;NORMAL
	DW	BlkNum251	;REV.
	DW	0x210A	;SM LAMP 260-251
	DW	0x220A	;SM Lamp2 260-250
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC2	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;260 to 271
	DW	d'62'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum260	;ROOT
	DW	BlkNum270	;NORMAL
	DW	BlkNum271	;REV.
	DW	0x220C	;SM LAMP 260-271
	DW	0x2202	;SM Lamp2 260-270
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC2	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;280 to 271
	DW	d'63'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum280	;ROOT
	DW	BlkNum270	;NORMAL
	DW	BlkNum271	;REV.
	DW	0x2402	;SM LAMP 280-271
	DW	0x250A	;SM Lamp2 280-270
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC2	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;280 to 291
	DW	d'64'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum280	;ROOT
	DW	BlkNum290	;NORMAL
	DW	BlkNum291	;REV.
	DW	0x240C	;SM LAMP 280-291
	DW	0x240A	;SM Lamp2 280-290
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC2	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;300 to 291
	DW	d'65'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum290	;NORMAL
	DW	BlkNum291	;REV.
	DW	0x2602	;SM LAMP
	DW	0x260A	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
;----------------------------------------------------------------------------------------
; Highland and Greeley
;
;
	DW	d'68'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3111	;NORMAL
	DW	BlkNum3101	;REV.
	DW	None	;0x2A0C ;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	0x0000	;Flags
;
	DW	d'68'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3112	;NORMAL
	DW	BlkNum3102	;REV.
	DW	None	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	0x0000	;Flags
;
	DW	d'104'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3101	;NORMAL
	DW	BlkNum3102	;REV.
	DW	None	;SM Lamp (R)
	DW	None	;SM Lamp2 (N)
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
	DW	d'107'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3112	;NORMAL
	DW	BlkNum3111	;REV.
	DW	None	;SM Lamp (R)
	DW	None	;SM Lamp2 (N)
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
	DW	d'66'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3111	;NORMAL
	DW	BlkNum3121	;REV.
	DW	None	;0x2E0C ;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	0x0000	;Flags
;
	DW	d'66'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3101	;NORMAL
	DW	None	;REV.
	DW	None	;SM LAMP
	DW	None	;SM Lamp2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	0x0000	;Flags
;
	DW	d'66'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3112	;NORMAL
	DW	BlkNum3122	;REV.
	DW	None	;SM Lamp (R)
	DW	None	;SM Lamp2 (N)
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
	DW	d'66'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3102	;NORMAL
	DW	None	;REV.
	DW	None	;SM Lamp (R)
	DW	None	;SM Lamp2 (N)
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
	DW	d'67'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3121	;NORMAL
	DW	BlkNum3131	;REV.
	DW	None	;0x300C ;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	0x0000	;Flags
;
	DW	d'66'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	None	;NORMAL
	DW	BlkNum3131	;REV.
	DW	None	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	0x0000	;Flags
;
	DW	d'67'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3122	;NORMAL
	DW	BlkNum3132	;REV.
	DW	None	;SM Lamp (R)
	DW	None	;SM Lamp2 (N)
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
	DW	d'66'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	None	;NORMAL
	DW	BlkNum3132	;REV.
	DW	None	;SM Lamp (R)
	DW	None	;SM Lamp2 (N)
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
	DW	d'120'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3121	;NORMAL
	DW	BlkNum3122	;REV.
	DW	None	;SM Lamp (R)
	DW	None	;SM Lamp2 (N)
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
	DW	d'117'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum300	;ROOT
	DW	BlkNum3132	;NORMAL
	DW	BlkNum3131	;REV.
	DW	None	;SM Lamp (R)
	DW	None	;SM Lamp2 (N)
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC3	;SM Enable
	DW	SMLamp2InvertFlag	;Flags
;
;271 to PHL
	DW	d'264'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum271	;ROOT
	DW	None	;NORMAL
	DW	BlkNumPHL	;REV.
	DW	0x2502	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC2	;SM Enable
	DW	RevBlkRequired	;Flags
;
	DW	d'265'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum260	;ROOT
	DW	None	;NORMAL
	DW	BlkNumPHL	;REV.
	DW	None	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC2	;SM Enable
	DW	RevBlkRequired	;Flags
;
	DW	d'62'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum260	;ROOT
	DW	None	;NORMAL
	DW	BlkNumPHL	;REV.
	DW	None	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC2	;SM Enable
	DW	0x0000	;Flags
;
	DW	d'266'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNumPHL	;ROOT
	DW	None	;NORMAL
	DW	BlkNumPH3	;REV.
	DW	0x2302	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	RevBlkRequired	;Flags
;
	DW	d'267'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNumPHL	;ROOT
	DW	None	;NORMAL
	DW	BlkNumPH2	;REV.
	DW	0x230C	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	RevBlkRequired	;Flags
;
	DW	d'268'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNumPHL	;ROOT
	DW	None	;NORMAL
	DW	BlkNumPH1	;REV.
	DW	0x230A	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	RevBlkRequired	;Flags
;
	DW	d'263'	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	BlkNum271	;ROOT
	DW	None	;NORMAL
	DW	BlkNumPH4	;REV.
	DW	0x250C	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	EnableCTZoneC2	;SM Enable
	DW	RevBlkRequired	;Flags
;
;======================================================================================
; Zone Control LEDs
	DW	EnableCTZoneC3	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	0x4B0A	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	0x0000	;Flags
;
	DW	EnableCTZoneC2	;SM Num 1 Hi 229
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	0x470C	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	0x0000	;Flags
;
	DW	EnableCTZoneC1	;SM Num 1
	DW	None	;SM Num 2
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	0x1E02	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	0x0000	;Flags
; TCC
	DW	DisableOVZoneC3	;SM Num 1 on
	DW	EnableCTZoneC3	;SM Num 2 off
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	0x4B02	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	SM2InvertFlag	;Flags
;
	DW	DisableOVZoneC2	;SM Num 1 on
	DW	EnableCTZoneC2	;SM Num 2 off
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	0x470A	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	SM2InvertFlag	;Flags
;
	DW	DisableOVZoneC1	;SM Num 1 on
	DW	EnableCTZoneC1	;SM Num 2 off
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	0x1E0C	;SM LAMP
	DW	None	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	SM2InvertFlag	;Flags
;
; OV
	DW	DisableOVZoneC3	;SM Num 1 off
	DW	EnableCTZoneC3	;SM Num 2 off
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	None	;SM LAMP
	DW	0x4B0C	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	0x000E	;Flags SM2RequiredFlag+SMLamp2InvertFlag
;
	DW	DisableOVZoneC2	;SM Num 1 off
	DW	EnableCTZoneC2	;SM Num 2 off
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	None	;SM LAMP
	DW	0x4702	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	0x000E	;Flags SM2RequiredFlag+SMLamp2InvertFlag
;
	DW	DisableOVZoneC1	;SM Num 1 off
	DW	EnableCTZoneC1	;SM Num 2 off
	DW	None	;SM Num 3
	DW	None	;ROOT
	DW	None	;NORMAL
	DW	None	;REV.
	DW	None	;SM LAMP
	DW	0x1E0A	;SM LAMP2
	DW	None	;SM Toggle Sw
	DW	None	;SM Enable
	DW	0x000E	;Flags SM2RequiredFlag+SMLamp2InvertFlag
;
	DB	EOD
;
;
;===========================================================================================
; Data to light odd LEDs not in SMData
;
AuxSMLEDsData	
;300 to 310-1
	DW	d'66'+SMOffRouteFlag
	DW	d'68'
	DW	d'104'+SMOffRouteFlag
	DW	None	;Marks end of SMs
	DB	BlkNum300	;Root block
	DW	0x2A0C	;310-1
;300 to 310-2
	DW	d'66'+SMOffRouteFlag
	DW	d'68'
	DW	d'104'
	DW	None	;Marks end of SMs
	DB	BlkNum300	;Root block
	DW	0x2B0C	;310-2
;300 to 311-1
	DW	d'66'+SMOffRouteFlag
	DW	d'68'+SMOffRouteFlag
	DW	d'107'
	DW	None	;Marks end of SMs
	DB	BlkNum300	;Root block
	DW	0x2A0A	;311-1
;300 to 311-2
	DW	d'66'+SMOffRouteFlag
	DW	d'68'+SMOffRouteFlag
	DW	d'107'+SMOffRouteFlag
	DW	None	;Marks end of SMs
	DB	BlkNum300	;Root block
	DW	0x2D0C	;311-2
;300 to 312-1
	DW	d'66'
	DW	d'67'+SMOffRouteFlag
	DW	d'120'+SMOffRouteFlag
	DW	None	;Marks end of SMs
	DB	BlkNum300	;Root block
	DW	0x2E0C	;312-1
;300 to 312-2
	DW	d'66'
	DW	d'67'+SMOffRouteFlag
	DW	d'120'
	DW	None	;Marks end of SMs
	DB	BlkNum300	;Root block
	DW	0x2F0C	;312-2
;300 to 313-1
	DW	d'66'
	DW	d'67'
	DW	d'117'
	DW	None	;Marks end of SMs
	DB	BlkNum300	;Root block
	DW	0x300C	;313-1
;300 to 313-2
	DW	d'66'
	DW	d'67'
	DW	d'117'+SMOffRouteFlag
	DW	None	;Marks end of SMs
	DB	BlkNum300	;Root block
	DW	0x310C	;313-2
;
;
	DB	EOD
	DB	EOD	;it reads this one.
;