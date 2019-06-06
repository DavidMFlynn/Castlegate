;**********************************************************************
;
;    Filename: CastleGate.asm
;    Date:5/16/2018
;    File Version:1.0d1
;
;    Author:David M. Flynn
;    Company:Highland Pacific RR, Inc.
;    Project:Castle Gate Yard computer
; 
;**********************************************************************
;
;    Files required:	CastleGate.asm	this file
;	P16F877.INC	! processor equ's
;	SerialNo.inc	serialization
;	BrainEQUs.inc	! Standard EQUs
;	BMacros.asm	! macro definitions
;	Strings.inc	# string data
;	Data.inc	other data
;	 HPRRMenuData.inc	# TCC Menus Data
;	 PanelCtrlData.inc	# Panel module control data and EQUs
;	 BlockData.inc	  Block numbers
;	 MLSMData.inc	Switch machine block data
;	LowStuff.asm	! mostly I/O routines
;	DataAccessSeg0.asm	# Quick 'n easy access to SRAM Data
;	BlockControlSeg0.asm	# Block Power and Control
;	NICStuff.asm	! 10baseT Network I/O
;	Main.asm	# Main event loop
;	PanelControl.asm	# Control panel I/O routines
;	CT IO.asm	Communications Loop
;	RecBlkPwr.inc	# UDP receiver of Blk Pwr and SM Data
;	Dispatch.asm	! User Button Cmd Inturpeter
;	DispatchHPRR.asm	# custom part of Cmd Inturpeter
;	Ether.asm	# TCC Custom HTTP I/O
;	HTTPServer.asm	! HTTP Sever
;	UDP_DataInOut.asm	! UDP Support
;	DMFE_Intf.asm	! Low Level I/O
;	DMFEInit.asm	# Init, Comm IO, Cab Btns, etc.
;	Seg3Custom.asm	Custom I/O
;	Seg3Custom2.asm	Custom I/O
;	Bootloader.asm	! Boot Loader to do software updates
;
;  ! These are standard files used in multiple projects, there are no
;    custom routines in these files.
;  # These files are common to HPRR TCC projects. 
;
;**********************************************************************
;
;    Notes:
;
;Castle Gate Keyboard Computer
;This computer is located in the Castle Gate control panel
; It communicates with the MP SM & BP computer.
;
; Unless specified All routines exit with ram bank zero selected.
;
; CGI:Common Gateway Interface
;  Data is received via http requests in the form "GET /index.html?a=6&b=23"
;  These requests are generated when a browser processes a POST form's SEND command
;
; EGI:Embedded Gateway Interface
;  The a two types of EGI
;   Value repacement where "@1" or "@g" are replaced with a string
;     example: @1 is replaced with the ADC1 voltage "2.3"
;              @g is replaced with ADC7's value "00980" 0..1023 posible with 10bit A/D
;   There can be a different set of EGI's @1..@z for each file based on fileidx
;   The second type is # value substitution
;    this is where a tag like <!--#A--> is replaced with the tag
;       <img src='ledoff.gif'> or <img src='ledon.gif'> depending on the value of the var $led1
;
;**********************************************************************
; Revision History
;
; 1.0d1    5/16/2018	Copied from Casper Tower
; 1.0b3    7/12/2009	Copied common code from Overview Tower, Cab to Thr x-later + Data
; 1.0b2    6/2/2007	First working version of Casper Tower
; 1.0b1    6/22/2005	Copied from BPK
; 1.0b1    9/5/2004	Added Dispatch, Bootloader, and standard HTTP server
; 1.0d1    12/15/2002  Copied from Resist v1.0d3
;	Removed resist specific code
;
; 1.0b3    10/29/2002  All non-standard code has been moved from LowStuff.asm
;	Standard NIC suport routines have all been moved to NICStuff.asm
;	Added suport for CGI's
; 1.0b2    10/25/2002  Moved OnTheHalfSecond to segment 2 (Main.asm)
;	Moved serial and other unused routines back into LowStuff.asm
; 1.0b1    10/21/2002  Fixed pH Up/Down Speed and Water Flow Error.
;	Added "Filling... 00016"
; 1.0d4    10/9/2002   Added Error display on 4th line, Panel count down
;	 causes water add, Sump lvl Sw opens spent valve,
;	 auto and manual adds.
; 1.0d3    10/2/2002	pH data is good, Front panel setup routines work.
; 1.0d2    10/1/2002	Created BMacros.asm, Strings moved to Main.asm
;	Added Service routines.
; 1.0d1    8/29/2002	Copied Flow 1.0b5  Begin of change to Resist.asm
;
;**********************************************************************
; Technical Stuff
;
; Assumptions:
;	The subnet mask is 255.255.255.0
;	This subnet is 192.168.1 (from eeprom) and must be correct
;	  as we don't do RARP, BOOTP, or DHCP.
;	The routers IP Address is 192.168.1.1 (this subnet.1)
;	My IP address is in eeprom (192.168.1.123)
;	
; Ethernet frame:
;	Preamble (8 bytes) added by NIC
;	Destination Address (6 bytes)
;	Source Address (6 bytes)
;	Frame Type (pcol) (2 bytes)
;	  (PCOL_ARP, PCOL_IP)
;	The Data (46 to 1500 bytes)
;	CRC code (4 bytes) added by NIC
;
; ARP/RARP message format: this all goes into the Data field in the Ethernet Frame (type PCOL_ARP)
;	Hardware Type (2 bytes) ethernet=1, HTYPE
;	Proticol Type (2 bytes) IP type=800, ARPPRO
;	Hardware Address Length (HLEN) (1 byte) ethernet=6, MACLEN
;	Proticol Addres Length (PLEN) (1 byte) IPv4=4, IPAddrLEN
;	Operation (2 bytes) 1 ARPREQ or 2 ARPRESP
;	Sender's Hardware Address (MAC)
;	Sender's IP Address
;	Target's Hardware Address (MAC)
;	Target's IP Address (MAC)
;
; IP Datagram message format: this all goes into the Data field in the Ethernet Frame (type PCOL_IP)
;	Vers and Header Length (1 nibble each), hardcoded as 0x45, IPv4, 5 long words
;	Servive Type (1 byte) hardcoded as 0x00
;	Total Length of datagram in bytes (2 bytes), 46..1500, iplen
;	Identification (2 bytes) ++IPDatagramID (high byte is hardcoded as 0x00)
;	Flags (3 bits) and Fragment offset (13 bits) hardcoded as 0x0000
;	Time to Live (1 byte) hardcoded as 0x64
;	Proticol (1 byte) ipcol
;	Header Checksum (2 bytes) checkhi:checklo
;	Source IP Address (4 bytes) myip
;	Destination IP Address (4 bytes) remip
;	Data 0..1480 bytes
;
; ICMP Message format for "PING": this all goes into the data field in an IP Datagram
;	Type (1 byte) 0 ICMP_EReply, or 8 ICMP_ERequest
;	Code (1 byte) 0
;	ICMP Checksum (2 bytes)	We only read down to here
;	Identifier (2 bytes)		 the rest gets send back as is.
;	Sequence Number (2 bytes)
;	Optional Data 0..1472 bytes
;
; UDP User Datagram Protocol "user datagram" (ipcol from IP Datagram = PUDP):
;    this all goes into the data field in an IP Datagram
;
;	pseudo header (8 bytes) not send with the data
;	    Source IP Address from IP Datagram (4 bytes)
;	    Dest IP Address from IP Datagram (4 bytes)
;	    0x00 byte
;	    ipcol byte from IP Datagram (PUDP=17)
;	    UDP message length (2 bytes) including header,
;	     not including the pseudo header (8..1480)
;
;	Source port (2 bytes) 0 or where to send replies
;	Destination port (2 bytes) application port
;	Message length (2 bytes) including header (8..1480)
;	Checksum (2 bytes) (optional 0 of csum value 0=FFFF)
;	    if used the pseudo-header must be included in the csum
;	Data (0..1472 bytes)
;
; TCP  Transmission Control Protocol (ipcol from IP Datagram = PTCP):
;     this all goes into the data field in an IP Datagram
;
;	pseudo header (8 bytes) not send with the data
;	    Source IP Address from IP Datagram (4 bytes)
;	    Dest IP Address from IP Datagram (4 bytes)
;	    0x00 byte
;	    ipcol byte from IP Datagram (PUDP=17)
;	    Message length (2 bytes) including header,
;	     not including the pseudo header (8..1480)
;
;	Source Port (2 bytes)
;	Destination Port (2 bytes)
;	Sequence Number (4 bytes) location in the senders byte stream this data fits
;	Acknowledgment Number (4 bytes) byte number the source expects next,
;		 for bi-directional transfer.
;	Header length (4 bits) length of header in 32 bit words (5)
;	Reserved (6 bits)
;	Code Bits (6 bits)
;	Window (2 bytes) aka buffer size of source, mine is 32 bytes, their's is ignored.
;	Checksum (2 bytes) (optional 0 of csum value 0=FFFF)
;	    if used the pseudo-header must be included in the csum
;	Urgent Pointer (2 bytes) incoming ones are ignored
;	Options (if used must be in 32 bit chuncks), MSS sent, incoming ones are ignored
;	Data (1480-header length)
;
;
; TTFTP Tiny Trivial File Transport Protocol (this all goes in the Data field of a TCP segment
;  uses the TFTPPort
;  incoming data on this port is written to the eeROM (serial eeproms)
;
;	Length (1 byte) 1..32
;	Address (3 bytes) big endian 0..
;	Data (Length bytes)
;
;**********************************************************************
;
;Constants for conditional assembly
;
	constant	ARPsNeverDie=1
	constant	TTFTPtoSRAM=1	;TTFTP to SRAM
	constant	TTFTPtoEEROM=1	;TTFTP to eeRom
	constant	EnableEEROMCopy=0	;Allow EEROM to be copied to SRAM
;
	constant	SRAM_Strings=1	;Strings are stored in SRAM
	constant	CodeMemStrings=0	;Strings are stored in Code Memory
	constant	ISR_Timers=0	;# of Timers used 0..6
	constant	UsesTimerFinished=0
	constant	testing=0	;NIC/ether status chars to Disp
	constant	ErrMsgsToLCD=1	;NIC/ether errors to Disp
	constant	testingRTC=0	;set_rtc at powerup
	constant	ARPtesting=0	;Show arp msgs on LCD
	constant	UDPtesting=0	;Show UDP msgs on LCD
	constant	TFTPtesting=0	;Show TFTP msgs on LCD
	constant	ShowSplashScrn=1	;Show the splash screen at startup
	constant	UsesTCPIPDataPort=0
	constant	UsesUDP=1
	constant	UseUCEGIs=0	;Uses upper case EGI's
	constant	UsesHashEGIs=0
	constant	oldCode=0	;kills old code without deleting it
;  analog IO
	constant	UsesMAX110=0	;MAXIM MAX110 14bit ADC
	constant	MAXANA0=0	; pH probe
	constant	MAXANA1=0	; not used
	constant	AnyANAUsed=0	;Set 0 if no Analog IO to save memory
	constant	StdANA0=0	;Standard Analog
	constant	StdANA1=0	;Analog 1 is active?
	constant	StdANA2=0	;Analog 2 is active?
	constant	StdANA3=0	;Analog 3 is active?
	constant	StdANA4=0	;Analog 4 is active?
	constant	StdANA5=0	;Analog 5 is active?
	constant	StdANA6=0	;Analog 6 is active?
	constant	StdANA7=0	;Analog 7 is active?
	constant	ANATest=0	;Display the first 3 Analog values?
;
; features control...
	constant	UsesNIC=1
	constant	AllowReceiveBroadcast=0
	constant	UsesSRAM=1
	constant	UsesDataROM=1	;Uses Data ROM image from d.d file
			; Requires SRAM_Strings
	constant	UsesISR=0
	constant	UsesBootloader=1	;Tell LowStuff to call PwrUpTest
	constant	UsesPushPop=0
	constant	UsesSRamPushPop=0
	constant	UsesSpeedTrap=0	;Travel Time, Speed and Acceleration
			; Requires: (HasISR=0x80)
	constant	UsesLCD=1	;Uses the 4x20 Optrix LCD
LCD_ChrsPerLine	EQU	d'20'
	constant	Useslcd_ReadData=1
	constant	UsesScrollMenu=0
	constant	UsesI2C=1
	constant	UsesEEROMFiles=1
	constant	UsesDataLogging=0	;Data logging to eeRom 0x008000-0x00FFFF
	constant	UsesRS232BufIO=0
	constant	UsesRS232=0	;if 0 don't assm the RS232 code
	constant	RS232Active=0	;RS232 port is enabled for output?
	constant	RS232Config=0	;Get IP and data (xmodem)
	constant	xmodemEEROM=0	;xmodem_recv
	constant	HasRTC=0	;Has a Real Time Clock?
	constant	UsesLDI0=1	;Latched data inputs 0..7
	constant	UsesLDI1=0	;Latched data inputs 8..15
	constant	UsesLDI2=0	;Latched data inputs 16..23
	constant	UsesLDI3=0	;Latched data inputs 24..31
	constant	UsesLDO0=1	;Reset,LEDs, and LDO_7
	constant	UsesLDO1=1	;latched data outputs 8..15
	constant	UsesLDO2=0
	constant	UsesLDO3=0
	constant	UsesDiv24x0A=0
	constant	UsesDiv16x16=0
; the tests...
	constant	RTCTest=0	;Display the RTC?
	constant	Do_LD_Test=0	;run the LED and Button test
	constant	Do_SRAM_Test=0	;run the SRAM (512KB) test
	constant	Do_ZeroRAM=1	;Load 0x00 into SRAM
	constant	Do_eeROM_Test=0	;run the eeROM test
	constant	Do_RS232_Test=0	;run the RS232 test
;
; Optional feature overides
	constant	Use_display_rtc=0
	constant	UsesInOutC=1
;
;**********************************************************************
;
	list	p=16f877,r=hex,W=0	;list directive to define processor
	include	p16f877.inc	; processor specific variable definitions
;	
	__CONFIG _CP_OFF & _WDT_OFF & _BODEN_ON & _PWRTE_ON & _HS_OSC & _WRT_ENABLE_ON & _LVP_OFF & _DEBUG_OFF & _CPD_OFF 
;
; Code Protection Off, Watch Dog Off, Brown-Out Reset On, Power-Up Timer On,
; High-Speed Crystal, Write Enable Program Memory On, Low-Voltage Programming Off,
; In-Circuit Debugger Mode Off, Code Protect EEPROM Off
;
; '__CONFIG' directive is used to embed configuration data within .asm file.
; The lables following the directive are located in the respective .inc file.
; See respective data sheet for additional information on configuration word.
;
;
;=========================================================================================
;=========================================================================================
;Constants
	include	SerialNo.inc
;
	include	BrainEQUs.inc
;
BaudRate	EQU	Baud1200
;
LDO_0_InitVal	EQU	0x7F
LDO_1_InitVal	EQU	0x00
LDO_2_InitVal	EQU	0x00
;
TRISAValue	EQU	0x2F	;low 4 bits in System LED out
TRISBValue	EQU	0x00	;All Output
TRISEValue	EQU	0x07	;aka all in PSP off
;
	if AnyANAUsed
ADCON1_Value	EQU	RA0_RA1_RA3_ANALOG	; initial ADCON1 value
	else
ADCON1_Value	EQU	All_Digital
	endif
;
;================================================================================================
;  Bank0 Ram 020h-06Fh
;
;  Note: there are x bytes free
;  The fisrt bytes in this bank must be maintained, however bytes after nicin.nic.stat
;   may be reused as temp vars in modal routines which don't use NICStuff routines.
;
;================================================================================================
	ORG	0x20
lastc	RES	1	;part of tickcount timmer
tickcount	RES	1	;Timer tick count
ledticks	RES	1	;LED tick count
;
ScrnNumber	RES	1
Flags24	RES	1
Flags25	RES	1
Flags26	RES	1
Flags27	RES	1
Flags28	RES	1
; additional flag bytes go here...
CGI_BtnQueued	RES	1	; 1 Queued Btn from CGI
;
myeth0	RES	1	;My MAC Address 6 bytes  msb
myeth1	RES	1
myeth2	RES	1
myeth3	RES	1
myeth4	RES	1
myeth5	RES	1	;  lsb
myip_b3	RES	1	; 4 bytes  My IP adress  MSB
myip_b2	RES	1
myip_b1	RES	1
myip_b0	RES	1	;LSB
next_page	RES	1	; NIC page number
curr_rx_page	RES	1	; Current NIC Rx page
concount_b0	RES	1	;WORD Connection count (for high word of my seq num) 
concount_b1	RES	1
; NIC hardware packet header NICETHERHEADER
nicin.nic.stat	RES	1	;Error status
nicin.nic.next	RES	1	;Pointer to next block
nicin.nic.len	RES	2	;Length of this frame incl. CRC 2 bytes
; Ethernet frame header ETHERHEADER
nicin.eth.dest	RES	6	;Destination MAC addresses (6 bytes) Should be mine
nicin.eth.srce	RES	6	;Source MAC addresses (6 bytes) Where this datagram is from
nicin.eth.pcol	RES	2	;Protocol (PCOL_ARP or PCOL_IP) (2 bytes MSB first)
tpxdlen	RES	2	;Length of external data in Tx frame (2 bytes)
checkhi	RES	1	;The working checksum, may include d_checkhi
checklo	RES	1
d_checkhi	RES	1	;Checksum value for data 
d_checklo	RES	1
rxin	RES	2	;Length of data found in ethernet frame 46..1500 (NIC RAM is buffer)
rxout	RES	2	;Offset into Rx buffer. Done reading when rxout=rxin.
txin	RES	1	;Offset to txbuff. txbuff+txin=RAM address of next byte.
ipcol	RES	1	;ipcol  IP protocol byte (PICMP, PTCP or PUDP)		
remip_b3	RES	1	;remote IP address (4 bytes) MSB
remip_b2	RES	1
remip_b1	RES	1
remip_b0	RES	1	;LSB
locport_b0	RES	1	;locport WORD ..and TCP/UDP port numbers
locport_b1	RES	1
remport_b0	RES	1	;remport WORD
remport_b1	RES	1 
rseq_b3	RES	1	;rseq LWORD  TCP sequence & acknowledge values
rseq_b2	RES	1
rseq_b1	RES	1
rseq_b0	RES	1
rack_b3	RES	1	;rack LWORD
rack_b2	RES	1
rack_b1	RES	1
rack_b0	RES	1
rflags	RES	1	; Rx flags
tflags	RES	1	; Tx flags
rpdlen_b0	RES	1	;Length of data in Rx buffer 
rpdlen_b1	RES	1
iplen_b0	RES	1	;iplen 2 bytes low>high  Incoming/outgoing IP length word
iplen_b1	RES	1
;
;
	if AnyANAUsed
CurADC	RES	1	;0..7
	endif
;
PWAccessCode	RES	1	;is 0 or a password code from IPDatagramID
;
;******************************************************************
;CAUTION: these (52 bytes) are volitile locations
; DO NOT USE if NIC is active
; Check to ensure not to overwrite data past iplen_b1
;
	ORG	nicin.nic.stat
PM_Addr_Lo	RES	1	;Prog mem dest address
PM_Addr_Hi	RES	1
PM_Data_Lo	RES	1	;Current data
PM_Data_Hi	RES	1
PM_StopAddrL	RES	1	;Last address + 1
PM_StopAddrH	RES	1
PM_CSumL	RES	1	;Checksum
PM_CSumH	RES	1
PM_FileNum	RES	1	;File number 0=b.b, 1=b1.b, etc.
;
;******************************************************************
;
;Flags24 bits
;
;Flags25 bits
#Define	DispDec2pl	Flags25,0
#Define	DispDec3pl	Flags25,1
#Define	BtnDebounce	Flags25,2	;set when any button is found
;
#Define	PWGood	Flags25,3	;Set wen a password is good
#Define	ClrLine	Flags25,4
;
#Define	DispLSpaces	Flags25,7	;Show leading spaces
;
;Flags26 bits
#Define	atend	Flags26,1
#Define	checkflag	Flags26,2
checkflagMask	EQU	0x04
CheckFlagFileReg	EQU	Flags26
#Define	SendToLCD	Flags26,4
#Define	SendRS232	Flags26,5
#Define	escaped	Flags26,6
;
;Flags27 bits
#Define	NumsToRam	Flags27,0
#Define	Disp_LZO	Flags27,1
#Define	DispDec1pl	Flags27,2
#Define	Disp_NLS	Flags27,3
#Define	NumsToNic	Flags27,4	;divert numbers from DisplaysW to putnic_checkbyte
;
;Flags28 bits
#Define	ServiceMode	Flags28,0	;allow eerom erase and stuff
;
;========================================================================================================
;  Bank1 Ram A0h-DFh 80 bytes
;   used as I/O buffer, keyboard buffer
;========================================================================================================
	ORG	0xA0
txbuff	RES	0x40	;Tx buffer TXBUFFLEN 0A0..0DF
;
; temp arp record
;  This struct overlaps the end of txbuff, but since this data is used at the beginning an arp message
;  any message large enough to overwrite these arp structures would be done with this data early on.
;  The bytes (ar_op..ar_tpa) are an arp message the bytes (ae_state..ar_spa) are cache table fields
;  stored in the cache table. They are overlapped like this to save ram
	ORG	0xD0
ae_state	RES	1	; state of this AR cache entry
AS_FREE	EQU	0	; this arp cache entry is free
AS_PENDING	EQU	1	; entry is used but incomplete
AS_RESOLVED	EQU	2	; entry has been resolved
;
ae_attempts	RES	1	; number of retries so far
ae_ttl	RES	1	; time to live
ATTL_Max	EQU	d'10'	; re-ARP every ATTL_Max datagrams
;
; These next fields are hard coded to save ram
;  ar_hwtype	RES	2	; hardware type (HTYPE)
;  ar_prtype	RES	2	; protocol type (ARPPRO)
;  ar_hwlen	RES	1	; hardware address len (MACLEN)
;  ar_prlen	RES	1	; protocol address len (IPAddrLEN)
ar_op	RES	2	; operation (1 ARPREQ, 2 ARPRESP, 3 RARPREQ, or 4 RARPSESP)
ar_sha	RES	MACLEN	; sender's hardware address
ar_spa	RES	IPAddrLEN	; sender's protocol address
ar_tha	RES	MACLEN	; target's hardware address
ar_tpa	RES	IPAddrLEN	; target's protocol address
;
; The cache table used ARP_TSIZE * ARP_TELEN bytes at 
ARP_TSIZE	EQU	d'32'	; cache table entries 
ARP_TELEN	EQU	d'16'	; cache entry length
ARP_TELEN_mask	EQU	0xF0	; anded with SRAM address to get back to
			;  the beginning of an entry
;
;========================================================================================================
;========================================================================================================
;  Bank2 Ram 110h-16Fh (96 bytes)
;  There are x Bytes free
;   everything in this bank except IPDatagramID is scratch pad space for various routines
;   and in most cases serves more than perpose
;========================================================================================================
	ORG	0x110
;Filename block structure (19 bytes)
romdir.f.len	RES	2	;word Length of file in bytes
romdir.f.start	RES	2	;word Start address of file data in ROM
romdir.f.check	RES	2	;word TCP checksum of file
romdir.f.flags	RES	1	;byte Embedded Gateway Interface (EGI) flags
; Embedded Gateway Interface (EGI) flag values
EGI_ATVARS	EQU	0x01	;'@' variable substitution scheme
#DEFINE	EGI_ATVARS_bit	romdir.f.flags,0
EGI_HASHVARS	EQU	0x02	;'#' and '|' boolean variables
#DEFINE	EGI_HASHVARS_bit	romdir.f.flags,1
#DEFINE	End_Of_File	romdir.f.flags,7	;bit is set when last byte is read
;
romdir.f.name	RES	d'12'	;(ROM_FNAMELEN)12 bytes Lower-case filename with extension
;
;TTFTP data (36 bytes) (coexists with file block)
eeROMbuff.len	RES	1	;bytes received
eeROMbuff.Addr	RES	3	; 3 bytes (big endian)
eeROMbuff.Data	RES	d'32'	; 32 bytes of data 114..133
;
	ORG	0x137	;Rewind
RAM137	RES	1
RAM138	RES	1
RAM139	RES	1
RAM13A	RES	1
RAM13B	RES	1
RAM13C	RES	1	; used by Div16x16
RAM13D	RES	1
RAM13E	RES	1
RAM13F	RES	1
RAM140	RES	1
RAM141	RES	1
RAM142	RES	1
RAM143	RES	1
RAM144	RES	1
RAM145	RES	1
RAM146	RES	1
;
	if HasRTC
; values read from the RTC
RTC_Year	RES	1	; 00..99
RTC_Month	RES	1	; 01..12
RTC_Day	RES	1	; 01..31
RTC_Hours	RES	1	; 00..24
RTC_Minutes	RES	1	; 00..59
RTC_Seconds	RES	1	; 00..59
	endif
;
	if AnyANAUsed
adc0LSB	RES	1	;adc0 2 bytes lsb
adc0MSB	RES	1	;  msb
adc1LSB	RES	1	;adc1 2 bytes lsb
adc1MSB	RES	1	; msb
adc2LSB	RES	1	;adc2 2 bytes lsb
adc2MSB	RES	1	; msb
adc3LSB	RES	1	;adc3 2 bytes lsb
adc3MSB	RES	1	; msb
adc4LSB	RES	1	;adc4 2 bytes lsb
adc4MSB	RES	1	; msb
adc5LSB	RES	1	;adc5 bytes lsb
adc5MSB	RES	1	; msb
adc6LSB	RES	1	;adc6 2 bytes lsb
adc6MSB	RES	1	; msb
adc7LSB	RES	1	;adc7 2 bytes lsb
adc7MSB	RES	1	; msb
	endif
;
eeROMFDataA0	RES	1	; Ptr to last byte saved
eeROMFDataA1	RES	1	;  loops FFFF>>8000..FFFF>>8000
eeROMFDataA2	RES	1
;
IPDatagramID	RES	1	;only used in put_ip
;
;========================================================================================================
;  Bank3 Ram 190h-1EFh (96 Bytes) 
;========================================================================================================
	ORG	0x190
;
	if UsesISR
;
FSR_Save	RES	1
ISR_FSR_Save	RES	1
ISR_PCLATH_Save	RES	1
ISR_W_Save	RES	1
ISR_Status_Save	RES	1
;
	endif
;
;
SRAM_UDP_Tx_DT	RES	1	;Transmited data type
SRAM_Len	RES	1	; 2 bytes Bigendian
SRAM_Len_Lo	RES	1
SRAM_DestAddr2	RES	1	; 3 bytes Bigendian
SRAM_DestAddr1	RES	1
SRAM_DestAddr0	RES	1
SRAM_UDP_Rx_IP	RES	1	;Low byte of IP address
SRAM_UDP_Rx_DT	RES	1	;Received data type
SRAM_Len_Rx	RES	1	; 2 bytes Bigendian
SRAM_Len_Lo_Rx	RES	1
SRAM_DestAddr1_Rx	RES	1	; 2 bytes Bigendian
SRAM_DestAddr0_Rx	RES	1
TTFTP_Flags	RES	1
#Define	UDP_DataReceived	TTFTP_Flags,0
#Define	UDP_DataSent	TTFTP_Flags,1
;
;SRAM addresses are 000000..07FFFF (512KB)
SRAM_Addr0	RES	1	;low byte of SRAM sddress
SRAM_Addr1	RES	1
SRAM_Addr2	RES	1	;high byte of SRAM sddress
;
;The Current address
CurrentAddr0	RES	1	;low byte of address
CurrentAddr1	RES	1
CurrentAddr2	RES	1	;high byte of address
;The last data written
CurrentLDO_0	RES	1	; last data sent
CurrentLDO_1	RES	1
;
;The last data read
	if UsesLDI0
CurrentLDI_0	RES	1	; last data read
;LDI_0 bits
SW2	EQU	0	;SW2 is lower left under LCD
SW3	EQU	1
SW4	EQU	2
SW5	EQU	3
SW6	EQU	4	;SW6 is upper left
SW7	EQU	5
LDI_0_6	EQU	6	;J2-28 not used
LDI_0_7	EQU	7	;J2-29 not used
	endif
;
	if UsesLDI1
CurrentLDI_1	RES	1
;LDI_1 bits
LDI_1_0	EQU	0	;Active High J2-33
LDI_1_1	EQU	1	;J2-34
LDI_1_2	EQU	1	;J2-35
LDI_1_3	EQU	1	;J2-36
LDI_1_4	EQU	1	;J2-37
LDI_1_5	EQU	1	;J2-38
LDI_1_6	EQU	1	;J2-39
LDI_1_7	EQU	1	;J2-40
	endif
;
;
CMD_LDO_0	RES	1	; value to set next time
;LDO_0 bits
NIC_Reset	EQU	0
LED1	EQU	1	;D6 LEDs are active low
LED2	EQU	2
LED3	EQU	3
LED4	EQU	4
LED5	EQU	5
LED6	EQU	6	;D11
LED6_Mask	EQU	b'01000000'
LED4_Mask	EQU	b'00010000'
;
CMD_LDO_1	RES	1	;  through the loop
;LDO_1 bits
;
;
	if ISR_Timers>0
;  16 bit event timers
;  Timers are decremented to Zero by the ISR
;  Each count is 0.00390625 seconds
;   Common times:
;      1 sec = 256 Counts
;      10 sec = 2560 Counts
;      100 sec = 25600 Counts
;      255 sec = 65535 Counts
;
BtnDebounceTime	EQU	d'16'	;1/16th sec
CGIBtnDebounceTime	EQU	d'128'	;1/2th sec
Timer1Lo	RES	1	;24 bit timer
Timer1Hi	RES	1	;UDP xmit timer
Timer1MSB	RES	1
	else
BtnDebounceTime	EQU	d'2'	;2/20th sec
CGIBtnDebounceTime	EQU	d'10'	;1/2th sec
BtnDeBounceTimer	RES	1
	endif
	if ISR_Timers>1
Timer2Lo	RES	1	;16 bit timer
Timer2Hi	RES	1	; bebounce timer
BtnDeBounceTimer	EQU	Timer2Lo
	endif
	if ISR_Timers>2
Timer3Lo	RES	1	;Beep Timer
Timer3Hi	RES	1
	endif
	if ISR_Timers>3
Timer4Lo	RES	1	;Test Timer
Timer4Hi	RES	1
	endif
	if ISR_Timers>4
Timer5Lo	RES	1
Timer5Hi	RES	1
	endif
	if ISR_Timers>5
Timer6Lo	RES	1
Timer6Hi	RES	1
	endif
;
UDPTimer	RES	1
kUDPTime	EQU	10	;half secs
;
BeepTimer	RES	1
kBeepTime	EQU	0x20	;Ticks 1/20's
;
;
OSlot	RES	1	;SLOT #0..3 
OBit	RES	1	;BIT #0..127 
OActive	RES	1	;0x80=ON 0x00=OFF 
OBoard	RES	1	;BOARD #0..7
;
ISlot	RES	1	;SLOT #0..3 
IBit	RES	1	;BIT #0..127 
IActive	RES	1	;0x80=ON 0x00=OFF 
IBoard	RES	1	;BOARD #0..7
;
;scratch pad vars
;DETTemp	RES	2
CurBlk	RES	2	;ptr to SRAM location with Bit,Slot and Board
SMDispPtr	RES	2
SMSvsPtr	RES	1
CurSM	RES	2
SvsBlkNum	RES	1
SvsCabNum	RES	1
BlockPwrTblPtr	RES	2
LampTblPtr	RES	2
BPTemp	RES	2
#Define	AnyCabOnFlag	BPTemp,7
#Define	Cab1IsPwrdFlag	BPTemp,4
#Define	Cab2IsPwrdFlag	BPTemp,3
#Define	Cab3IsPwrdFlag	BPTemp,2
#Define	Cab4IsPwrdFlag	BPTemp,1
#Define	Cab5IsPwrdFlag	BPTemp,0
#Define	Cab6IsPwrdFlag	BPTemp+1,3
#Define	Cab7IsPwrdFlag	BPTemp+1,2
#Define	Cab8IsPwrdFlag	BPTemp+1,1
#Define	Cab9IsPwrdFlag	BPTemp+1,0
;
BPTemp2	RES	2
BlockNum	RES	1
ScannerBlkNum	RES	1
DisplayBlkNum	RES	1
SegmentPtr	RES	2	;two byte ptr start of data
			; for 7 segment display
LastCabVal	RES	1	;Current Cab if any 0..9
;
CabEastFB	EQU	0
CabWestFB	EQU	1
CabDetEastFB	EQU	6
CabDetWestFB	EQU	5
CabSelectedFB	EQU	7
;
Cab1ModeFlags	RES	1
#define	C1East	Cab1ModeFlags,CabEastFB
#define	C1West	Cab1ModeFlags,CabWestFB
#Define	Cab1DetEast	Cab1ModeFlags,CabDetEastFB
#Define	Cab1DetWest	Cab1ModeFlags,CabDetWestFB
#define	C1Selected	Cab1ModeFlags,CabSelectedFB
Cab2ModeFlags	RES	1
#define	C2East	Cab2ModeFlags,CabEastFB
#define	C2West	Cab2ModeFlags,CabWestFB
#Define	Cab2DetEast	Cab2ModeFlags,CabDetEastFB
#Define	Cab2DetWest	Cab2ModeFlags,CabDetWestFB
#define	C2Selected	Cab2ModeFlags,CabSelectedFB
Cab3ModeFlags	RES	1
#define	C3East	Cab3ModeFlags,CabEastFB
#define	C3West	Cab3ModeFlags,CabWestFB
#Define	Cab3DetEast	Cab3ModeFlags,CabDetEastFB
#Define	Cab3DetWest	Cab3ModeFlags,CabDetWestFB
#define	C3Selected	Cab3ModeFlags,CabSelectedFB
Cab4ModeFlags	RES	1
#define	C4East	Cab4ModeFlags,CabEastFB
#define	C4West	Cab4ModeFlags,CabWestFB
#Define	Cab4DetEast	Cab4ModeFlags,CabDetEastFB
#Define	Cab4DetWest	Cab4ModeFlags,CabDetWestFB
#define	C4Selected	Cab4ModeFlags,CabSelectedFB
Cab5ModeFlags	RES	1
#define	C5East	Cab5ModeFlags,CabEastFB
#define	C5West	Cab5ModeFlags,CabWestFB
#Define	Cab5DetEast	Cab5ModeFlags,CabDetEastFB
#Define	Cab5DetWest	Cab5ModeFlags,CabDetWestFB
#define	C5Selected	Cab5ModeFlags,CabSelectedFB
Cab6ModeFlags	RES	1
#define	C6East	Cab6ModeFlags,CabEastFB
#define	C6West	Cab6ModeFlags,CabWestFB
#Define	Cab6DetEast	Cab6ModeFlags,CabDetEastFB
#Define	Cab6DetWest	Cab6ModeFlags,CabDetWestFB
#define	C6Selected	Cab6ModeFlags,CabSelectedFB
;
;  Input Board  0x0000..0x007F
;  Output Board 0x0400..0x047F
kFirstOB	EQU	0x04
kLastOB	EQU	0x04
kDefaultCab	EQU	0x06
kLastCab	EQU	0x06	;Cab Count
kDefaultCMF	EQU	Cab6ModeFlags
;
;
LastBtn	RES	1
DispBlockNum	RES	1
;
DispFlags	RES	1
#Define	WDLED_Flag	DispFlags,0
WDLED_Mask	EQU	b'00000001'
#Define	TestModeFlag	DispFlags,1
TestModeMask	EQU	b'00000010'
#Define	CabBtnDB_Flag	DispFlags,2
#Define	TestCycleBit	DispFlags,3
;
;
BPK_Flags	RES	1
#Define	BeepOn	BPK_Flags,2
;
;
;
SvsInSlotBoard	RES	1
SMHighSvsPtr	RES	1
SvsCurBlk	RES	2
SvsBMdlNum	RES	1	;Block modle # 0..95
SvsBMdlVal	RES	1	;LED to light 0..24 
;
SMScanFlags	RES	1
#Define	SMLowNumRecvd	SMScanFlags,0
#Define	SMHiNumRecvd	SMScanFlags,1
#Define	BlkNumRecvd	SMScanFlags,2
#Define	SMTableLowChngFlag	SMScanFlags,3
#Define	SMTableHiChngFlag	SMScanFlags,4
#Define	BlockCmdChngFlag	SMScanFlags,5
#Define	BlockCmdChngFlag2	SMScanFlags,6
#Define	IsMyCabFlag	SMScanFlags,7
;
SMScanFlags2	RES	1
#Define	BlockDataChngFlag	SMScanFlags2,0
#Define	BlockDataChngFlag2	SMScanFlags2,1
;
BlockModuleNum	RES	1	;0..31
BlkModAddr0	RES	1
BlkModAddr1	RES	1
BlkModBits0	RES	1
BlkModBits1	RES	1
BlkModBoard	RES	1
;
SyncBlkNum	RES	1	;A blk num that is SyncBlkNum++
			; each time through the main loop
SyncSMNum	RES	1	;A sm num that is SyncSMNum++
			; each time through the main loop
;ScannerRetry	RES	1	;retry counts
;
;=======================================================================================================
;========================================================================================================
; Constants for HPRR stuff
;
NOSlot	EQU	0x78	;BITS TO DEACTIVATE ALL DEV'S 
;
;Block Power Table Bits
DetectMask	EQU	0x60	;Detect bits E/W
DetectInvertMask	EQU	0x9F	;Not Detect bits E/W
DetectFlashFlag	EQU	0x00	;set to 0x80 to flash
;
;
;========================================================================================================
;========================================================================================================
; Storage locations "Page Numbers" in the serial eproms (000..3FF) (256KB)
;
seFiles	EQU	0x0000	;Start of file storage
seParamSets	EQU	0x007F	;8 sets 256 bytes 0x007F00 to 0x007FFF
seFlowData	EQU	0x0080	;32KB 0x008000 to 0x00FFFF
; serial eproms 3..8 are not installed.
;
;========================================================================================================
;========================================================================================================
; SRAM locations "Page Numbers" they are 0000..07FF (512KB) (256 bytes/page)
;
SMTable	EQU	0x0002	;one byte for each SM
SMTableHigh	EQU	0x0003
BlockPwrTable	EQU	0x0004	;one byte for each Block
BlockCmdTable	EQU	0x0005	;one byte for each Block
BlockPwrTable2	EQU	0x0006	;one byte for each Block
BlockCmdTable2	EQU	0x0007	;one byte for each Block
InputsTable	EQU	0x0008	;one byte for each input
BlockOwnerTable	EQU	0x0009	;one byte for each Block
;
BlockModuleBitsL	EQU	0x000A	;One Byte for each block
BlockModuleBitsH	EQU	0x000B	; storage for LED bits
;
evDataROM	EQU	0x0010	;start of data
;
evParamStack	EQU	0x00F0	;256 bytes = 32 deep stack
evStrings	EQU	0x00F2	;start of strings
evARPcache	EQU	0x00F8	;ARP cache 0x00F800..0x00F9FF (512 bytes)
evStatSaveBuffer	EQU	0x017F	;Buffer for status saving
evBuff32KB	EQU	0x0180	;32KB Buffer for data tx, rx, etc.
;
kUDP_SRAM_Page	EQU	0x02
evUDPDest	EQU	0x0200	;64KB
evUDP_SMTable	EQU	0x0202	;from MPSMBP
evUDP_SMTableHigh	EQU	0x0203	;from MPSMBP
evUDP_BlockPwrTable	EQU	0x0204	;from MPSMBP
evUDP_BlockPwrCmdTbl	EQU	0x0205
evUDP_BlockPwrTable2	EQU	0x0206
evUDP_BlockPwrCmdTbl2	EQU	0x0207
;
evEndOfSRAM	EQU	0x0206	;shortens boot time
;
;========================================================================================================
;========================================================================================================
; EEPROM locations 256 bytes of EEPROM in F877
	ORG	0x0000
;
eMACAddr4	RES	1	; 5th byte of MAC Address
eMACAddr5	RES	1
eIPAddr3	RES	1	; MSB of IP Address
eIPAddr2	RES	1
eIPAddr1	RES	1
eIPAddr0	RES	1
eCSum	RES	1	; csum for first 6 bytes
eROMFDA0	RES	1	; LSB of eeROM Flow Data address
eROMFDA1	RES	1
eROMFDA2	RES	1
eSN0	RES	1	; LSB of Vis-U-Etch serial number
eSN1	RES	1
;
eScrnNumber	RES	1	;0..kLastNormScrn
eSvsScrnNumber	RES	1	;0..kLastSvsScrn
eParamSetNumber	RES	1	;0..7
ePM_Flags	RES	1
;
eSRAMErrStr	EQU	0xD8	;'SRAM Err'
eSplashText	EQU	0xE0	;See SerialNo.asm for data
eSplashText2	EQU	0xF0	; 0x10 bytes each
;
;========================================================================================================
; Initialize EEPROM memory
	ORG	0x2100	;eeprom
	DE	high kMAClsw	; 2 lower bytes of MAC address
	DE	low kMAClsw
	DE	kIPmsb,kIPb2,kIPb3	;IP address (i.e. 192.168.1.)
	DE	kIPlsb	;IP address (i.e. 124)
	DE	kCSum	;checksum
;
	DE	0xFF,0x7F	;placeholder for flow data pointer
	DE	0x00
	DE	low kSerialNumber	;S/N lsb,msb
	DE	high kSerialNumber
;
	DE	0x00	;ScrnNumber
	DE	0x00	;SvsScrnNumber
	DE	0x00	;eParamSetNumber 0..7
	DE	0x00	;ePM_Flags
;
	ORG	0x21D8
	DE	'S','R','A','M','E','r','r'
	DE	0x00
;
; Initialize ID locations
	ORG	0x2000
	DE	'1','0','D','1'
;
	ORG	0x21E0	;eeprom last 32 bytes
;Splash screen text (must be 15 chars)
	DE	' ','O','x','f','o','r','d',' '
	DE	'V','.','U','.','E','.',' '
	DE	0x00
	DE	' ',' ','G','P',' ','C','P'
	DE	'U',' ','B','I','O','S',' ',' '
	DE	0x00
;
;============================================================================================
;
	include	BMacros.asm	;common macros for the brain GP computer
	include	Strings.inc	;string definitions
	include	Data.inc
	include	LowStuff.asm	;starts at 0x0000
	include	DataAccessSeg0.asm
	include	BlockControlSeg0.asm
	include	NICStuff.asm	; 0x0800
	include	Main.asm	; 0x1000
	include	PanelControl.asm
	include	CG IO.ASM
	include	Dispatch.asm
	include	DispatchHPRR.asm
	include	Ether.asm	; 0x1800
	include	HTTPServer.asm
	include	UDP_DataInOut.asm
	include	DMFE_Intf.asm
	include	DMFEInit.asm
	include	Seg3Custom.asm
	include	Seg3Custom2.asm
	include	Bootloader.asm
;
;
;
;
;
;
;
;
	END		; directive 'end of program'
;
;
