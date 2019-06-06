// ******************************************
// File: Castlegate.scad
// Created: 11/30/2016
// by Dave Flynn
// Castlegate Storage Yard
// Units: Inches
// Revision: 1.0.0 11/30/2016 First Code.
// ******************************************
// History
// 1.0.0 11/30/2016 First Code.
// ******************************************
include <PanelLib.scad>
// ***** High Level Routines *****
// BlockModuleCuttout(UnderText="100",Has7Seg=true,Mode=3D_Mode); // Seven segment (centered), 11 LEDs, Push Button
//
// ***** Low Level Routines *****
// PowerSwitch(Mode=3D_Mode);
// AlignmentMark(X=-2,Y=-2,Mode=3D_Mode);
// EngravedText(TheText="100",X=0,Y=0,Height=0.1,Mode=3D_Mode);
// LED_Hole(X=0,Y=0,Mode=3D_Mode);
// SevenSeg_Hole(X=0,Y=0,Mode=3D_Mode); // cuttout for display
// 
// TrackLine(X1=0,Y1=0,X2=1,Y2=0,StartTerm=false,EndTerm=false,Mode=3D_Mode); // point-to-point line

3D_Mode=0;
Line_Mode=1;
Hole_Mode=2;
Lens_Mode=3;
Cutout_Mode=4;
SwitchHole_Mode=5;

//scale([25.4,25.4,25.4]) CastlegateWest(Mode=Cutout_Mode);
//scale([25.4,25.4,25.4]) CastlegateWest(Mode=3D_Mode); // 3D view
//scale([25.4,25.4,25.4]) CastlegateWest(Mode=Line_Mode); // Text and track lines
//scale([25.4,25.4,25.4]) CastlegateWest(Mode=Hole_Mode);  //Holes only
//scale([25.4,25.4,25.4]) CastlegateWest(Mode=Lens_Mode); //LED lenses for overlay
//scale([25.4,25.4,25.4]) CastlegateWest(Mode=SwitchHole_Mode); // Switch holes only for overlay

$fn=60;
Overlap=0.001;
IDXtra=0.005;
PanelThickness=0.125;
BlockLineLen=1.0;

module Block171(Mode=3D_Mode){
	translate([0,3,0]){
		TrackLine(X1=-BlockLineLen,Y1=0,X2=BlockLineLen,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
		translate([0,0.45,0]) EngravedText(TheText="171",X=0,Y=0,Height=0.3,Mode=Mode);
	}
	translate([0,1.5,0]) BlockModuleCuttout(UnderText="",Has7Seg=true,Mode=Mode);
} // Block171

module Block170(Mode=3D_Mode){
	translate([0,3,0]){
		TrackLine(X1=-BlockLineLen,Y1=0,X2=BlockLineLen,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
		translate([0,0.45,0]) EngravedText(TheText="170",X=0,Y=0,Height=0.25,Mode=Mode);
	}
	//BlockModuleCuttout(UnderText="170",Has7Seg=true,Mode=Mode);
} // Block171

module BlockSYL(Mode=3D_Mode){
	translate([0,3,0]){
		TrackLine(X1=-BlockLineLen,Y1=0,X2=BlockLineLen,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
		translate([-0.3,0.45,0]) EngravedText(TheText="SYL",X=0,Y=0,Height=0.3,Mode=Mode);
	}
	translate([-0.3,1.5,0]) BlockModuleCuttout(UnderText="",Has7Seg=true,Mode=Mode);
} // BlockSYL



module BlockLocal(Name="A",StartTerm=false,EndTerm=false,Mode=3D_Mode){
	TrackLine(X1=-BlockLineLen,Y1=0,X2=BlockLineLen,Y2=0,StartTerm=StartTerm,EndTerm=EndTerm,Mode=Mode);
	translate([0,0.45,0]) EngravedText(TheText=Name,X=0,Y=0,Height=0.3,Mode=Mode);
	
	translate([0,0.3,0]) BlockModuleCuttout(UnderText="",Has7Seg=false,Mode=Mode);
} // BlockLocal

module Converge(Mode=3D_Mode){
		TrackLine(X1=0,Y1=-1,X2=1,Y2=-1,StartTerm=false,EndTerm=false,Mode=Mode);
		LED_Hole(X=0.6,Y=-1,Mode=Mode);
		
		TrackLine(X1=0,Y1=0,X2=1,Y2=-1,StartTerm=false,EndTerm=false,Mode=Mode);
		LED_Hole(X=0.7,Y=-0.7,Mode=Mode);
} // Converge

module Diverge(Mode=3D_Mode){
		TrackLine(X1=0,Y1=0,X2=1,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
		LED_Hole(X=0.4,Y=0,Mode=Mode);
		
		TrackLine(X1=0,Y1=0,X2=1,Y2=1,StartTerm=false,EndTerm=false,Mode=Mode);
		LED_Hole(X=0.3,Y=0.3,Mode=Mode);
} // Diverge

module CastlegateWest(Mode=3D_Mode){
translate([6,-3,0]) {Block171(Mode=Mode);
	translate([-BlockLineLen-1,2,0]) Diverge(Mode=Mode);
	translate([-BlockLineLen-1,2,0]) mirror([0,1,0]) Converge(Mode=Mode);
	
	translate([BlockLineLen,3,0])  Converge(Mode=Mode);
	translate([BlockLineLen,3,0])  mirror([0,1,0]) Diverge(Mode=Mode);
	TrackLine(X1=BlockLineLen+1,Y1=3,X2=BlockLineLen+2,Y2=3,StartTerm=false,EndTerm=true,Mode=Mode);
	translate([BlockLineLen+1,3.45,0]) EngravedText(TheText="Deka",X=0,Y=0,Height=0.25,Mode=Mode);
	}

translate([6,-4,0]) {Block170(Mode=Mode);
	TrackLine(X1=BlockLineLen+1,Y1=3,X2=BlockLineLen+2,Y2=3,StartTerm=false,EndTerm=false,Mode=Mode);
	translate([BlockLineLen+1.5,3.45,0]) EngravedText(TheText="160",X=0,Y=0,Height=0.25,Mode=Mode);
	TrackLine(X1=-BlockLineLen-2,Y1=3,X2=-BlockLineLen-1,Y2=3,StartTerm=false,EndTerm=false,Mode=Mode);
	translate([-BlockLineLen-1.5,3.45,0]) EngravedText(TheText="180",X=0,Y=0,Height=0.25,Mode=Mode);
}
translate([3,-3,0]) BlockSYL(Mode=Mode);

LongCenter_X=-8;
translate([LongCenter_X,-3,0]) {
	BlockLocal(Name="CG 1",Mode=Mode);
	TrackLine(X1=BlockLineLen,Y1=0,X2=BlockLineLen+0.5,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
}
translate([LongCenter_X,-2,0]) BlockLocal(Name="CG 2",Mode=Mode);
translate([LongCenter_X,-1,0]) BlockLocal(Name="CG 3",Mode=Mode);
translate([LongCenter_X,0,0]) BlockLocal(Name="CG 4",Mode=Mode);
translate([LongCenter_X+BlockLineLen+3.5,-1,0]) mirror([0,1,0]) Converge(Mode=Mode); // A,10
translate([LongCenter_X+BlockLineLen+3,-1.5,0]) rotate([0,0,45])
	BlockLocal(Name="CG 10",StartTerm=true,Mode=Mode);

translate([LongCenter_X+BlockLineLen,-1,0]) mirror([0,1,0]) Converge(Mode=Mode); // 3,4
translate([LongCenter_X+BlockLineLen+1,-1,0]){ mirror([0,1,0]) Converge(Mode=Mode); // 3,4 + 2
TrackLine(X1=-1,Y1=-1,X2=0,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);}

translate([LongCenter_X+BlockLineLen+2.5,-1,0]){ mirror([0,1,0]) Converge(Mode=Mode); // 3,4,2+1
TrackLine(X1=-2,Y1=-2,X2=0,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);}

TrackLine(X1=LongCenter_X+BlockLineLen+2,Y1=0,X2=LongCenter_X+BlockLineLen+2.5,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
translate([LongCenter_X+BlockLineLen+2.35,0,0]) Diverge(Mode=Mode);

translate([LongCenter_X,1,0]) BlockLocal(Name="CG 5",Mode=Mode);
translate([LongCenter_X,2,0]) BlockLocal(Name="CG 6",Mode=Mode);
translate([LongCenter_X+BlockLineLen,1,0]) mirror([0,1,0]) Converge(Mode=Mode); // 5,6
translate([LongCenter_X+BlockLineLen+3.35,1,0]){ mirror([0,1,0]) Converge(Mode=Mode); // 5,6+1..4
	
	TrackLine(X1=-2.35,Y1=1,X2=0,Y2=1,StartTerm=false,EndTerm=false,Mode=Mode);
}

translate([LongCenter_X+BlockLineLen+4,3,0]) {Converge(Mode=Mode);
	translate([2,0,0]) BlockLocal(Name="CG 9",EndTerm=true,Mode=Mode);
	//TrackLine(X1=1,Y1=0,X2=3,Y2=0,StartTerm=false,EndTerm=true,Mode=Mode);
}
	
translate([LongCenter_X+BlockLineLen+4,3,0]) {mirror([0,1,0]) Diverge(Mode=Mode);
	TrackLine(X1=-3,Y1=0,X2=0,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
}
	
translate([LongCenter_X,3,0]) BlockLocal(Name="CG 7",Mode=Mode);
translate([LongCenter_X,4,0]) BlockLocal(Name="CG 8",Mode=Mode);
translate([LongCenter_X+BlockLineLen,4,0]) Converge(Mode=Mode); // 7,8

translate([-1,0,0]) {BlockLocal(Name="Lead A",Mode=Mode);
	TrackLine(X1=-BlockLineLen-0.5,Y1=0,X2=-BlockLineLen,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
	translate([BlockLineLen+1,1,0]) {Converge(Mode=Mode);
		TrackLine(X1=-1,Y1=-1,X2=0,Y2=-1,StartTerm=false,EndTerm=false,Mode=Mode);
		TrackLine(X1=-1,Y1=1,X2=0,Y2=0,StartTerm=false,EndTerm=false,Mode=Mode);
	}
}
translate([-1,2,0]) BlockLocal(Name="Lead B",Mode=Mode);

	translate([7,2.5,0]) PowerSwitch(Mode=Mode);
	AlignmentMark(X=-11,Y=-5,Mode=Mode);
	EngravedText(TheText="Castlegate",X=0,Y=4.9,Height=0.9,Mode=Mode);
	EngravedText(TheText="West",X=3,Y=3.8,Height=0.3,Mode=Mode);

	PanelOutline(X=-9.75,Y=-4.0,Size_X=19.5,Size_Y=9.5,Mode=Mode);
	
} // CastlegateWest
















