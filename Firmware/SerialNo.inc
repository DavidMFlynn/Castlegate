;*******************************************************************************
;
;    Filename: SerialNo.inc
;    Date:5/16/2018
;    File Revision:1.0
;
;    Author:David M. Flynn
;    Company:Oxford V.U.E., Inc.
;    Project: HPRR Casper Tower
;    MAC:00 04 A3 00 00 23
;    IP:192.168.2.143
;    S/N:7981
;
; 
;**********************************************************************
;
;    Notes:
;	There is no code in this file,
;	only Data and EQU's
;
;
;**********************************************************************
; Revision History
;
; 1.0    5/16/2018	Updates for Castle Gate Yard
; 1.0    6/22/2004	First created
;
;**********************************************************************
;
	constant SaveStatusRecords=0
	constant UsesBlockCmdTable=1
	constant UsesSyncBP=1
	constant UsesSpeaker=1
	constant UsePsuedoReset=0
	constant UsesBlockModules=1
	constant HasAThrottle=1
MyCabNum	EQU	0x06
	constant UsesInputTester=1
	constant UsesOutputTester=1
	constant StartupInSvsMode=0
	constant BlockToBrainBds=1
	constant UsesGetCabNumX=1
	constant UsesShowInputs=1
	constant UsesBlockCmdTest=1
	constant UsesAutoSMCtrl=1
	constant LightUnusedSMLEDs=1
	constant HasBlkRelays=1
	constant HasBlockDetectors=1
	constant Has_OB_OccLEDs=0
	constant UsesDisableUHSelector=0
	constant CabCount=6
	constant UsesSeg0DataAccess=1
	constant UsesVistaSelect=0
	constant dpIsOwner=1
;
kMaxBlockNum	EQU	d'75'	;0..75 (76 blocks)
;
;
#Define	SignonString	'CastleGate v1.0'
;
kSerialNumber	EQU	d'7981'	; Serial Number <<<<<<< fix
;
EndOfEEROM	EQU	0x01	;0x010000 is the first address past the end
; EEPROMs must be installed in 64KB increments 1=64KB, 2=128KB, 3=192KB, 4=256KB...8=512KB
	constant	Using64KBEEPROM=0	;EEPROM addressing 0:15+3, 1:16+3
;
;
kDefaultIOCtrl	EQU	b'00000000'
;
MAC_Addr0	EQU	0x00	;MSB of MAC Address (48 bit number)
MAC_Addr1	EQU	0x04	; first 3 bytes are assigned by
MAC_Addr2	EQU	0xA3	; IEEE
MAC_Addr3	EQU	0x00	;low 2 bytes are in eprom 0 and 1
;
kMAClsw	EQU	0x0023	;low 16 bits of MAC address
kIPmsb	EQU	d'192'
kIPb2	EQU	d'168'
kIPb3	EQU	d'2'
kIPlsb	EQU	d'143'
kCSum	EQU	0xFD	;csum of last 6 bytes
			; all 7 bytes must add up to xxFF
;
;
;
