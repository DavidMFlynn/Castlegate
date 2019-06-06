// ********************************************
// File: PanelLib.scad
// Created: 11/23/2016
// by Dave Flynn
// Model Railroad control panel library
// Units: Inches
// Revision: 1.0.1 11/30/2016
// ********************************************
// History
// 1.0.1 11/30/2016 Added "Has7Seg=true", clean up.
// 1.0.0 11/23/2016 First code.
// ********************************************
// ***** High Level Routines *****
// BlockModuleCuttout(UnderText="100",Has7Seg=true,Mode=3D_Mode); // Seven segment (centered), 11 LEDs, Push Button
//
// ***** Low Level Routines *****
// PanelOutline(X=-10,Y=-6,Size_X=14,Size_Y=10,Mode=3D_Mode);
// PowerSwitch(Mode=3D_Mode);
// AlignmentMark(X=-2,Y=-2,Mode=3D_Mode);
// EngravedText(TheText="100",X=0,Y=0,Height=0.1,Mode=3D_Mode);
// LED_Hole(X=0,Y=0,Mode=3D_Mode);
// SevenSeg_Hole(X=0,Y=0,Mode=3D_Mode); // cuttout for display
// 
// TrackLine(X1=0,Y1=0,X2=1,Y2=0,StartTerm=false,EndTerm=false,Mode=3D_Mode); // point-to-point line
// 
// ***** Test All ******
// PanelTest();


$fn=60;
Overlap=0.001;
IDXtra=0.005;
PanelThickness=0.125;

3D_Mode=0;
Line_Mode=1;
Hole_Mode=2;
Lens_Mode=3;
Cutout_Mode=4;
SwitchHole_Mode=5;

module AlignmentMark(X=-2,Y=-2,Mode=3D_Mode){
		translate([X,Y,0]){
			translate([-0.1,0,0]) square([0.2,0.01]);
			translate([0,-0.1,0]) square([0.01,0.2]);}
} // AlignmentMark

module EngravedText(TheText="100",X=0,Y=0,Height=0.1,Mode=3D_Mode){
	
		if (Mode==3D_Mode){	
			translate([X,Y-Height,PanelThickness-0.030])
				linear_extrude(height=0.3) text(TheText,size=Height,halign="center");
		}
		if (Mode==Line_Mode){
			translate([X,Y-Height,0])
				text(TheText,size=Height,halign="center");
		}

} // EngravedText

LensExtra=0.04;

module LED_Hole(X=0,Y=0,Mode=3D_Mode){
	CutterComp=-0.003;
	LED_Hole_d=0.122+CutterComp;
	
	
	if (Mode==3D_Mode){
		translate([X,Y,-Overlap])
			cylinder(d=LED_Hole_d,h=PanelThickness+Overlap*2);
	}
	if (Mode==Hole_Mode){
		translate([X,Y,0])
			circle(d=LED_Hole_d);
	}
	if (Mode==Lens_Mode){
		translate([X,Y,0])
			circle(d=LED_Hole_d+LensExtra);
	}
		
} // LED_Hole

module SevenSeg_Hole(X=0,Y=0,Mode=3D_Mode){
	CutterComp=-0.002;
	SevenSeg_X=0.276+CutterComp;
	SevenSeg_Y=0.434+CutterComp;

	translate([X-SevenSeg_X/2,Y-SevenSeg_Y/2,-Overlap]){
		if (Mode==3D_Mode){		
			cube([SevenSeg_X,SevenSeg_Y,PanelThickness+Overlap*2]);
		}
		if (Mode==Hole_Mode){
			square([SevenSeg_X,SevenSeg_Y]);
		}
	}
} // SevenSeg_Hole

module SwitchHole(X=0,Y=0,Mode=3D_Mode){
	Switch_d=0.250;
	
	if (Mode==3D_Mode){
		translate([X,Y,-Overlap]) cylinder(d=Switch_d,h=PanelThickness+Overlap*2);
	}
	if ((Mode==Hole_Mode)||(Mode==SwitchHole_Mode)) {
		translate([X,Y,0]) circle(d=Switch_d);
	}
} // SwitchHole

module BlockModuleCuttout(UnderText="100",Has7Seg=true,Mode=3D_Mode){
	LED_Spacing=0.140;
	
	
	UnderText_Y=-0.85;
	UnderText_Size=0.25;
	
	if (Has7Seg==true)
		// Seven Segment Display
		SevenSeg_Hole(X=0,Y=0,Mode=Mode);
		
	// led holes
	translate([-5*LED_Spacing,0,0])
		for (n=[0:10]) LED_Hole(X=n*LED_Spacing,Y=-0.300,Mode=Mode);
			
	// Switch
	SwitchHole(0,-0.575,Mode=Mode);
	
		
	// Text	
	EngravedText(TheText=UnderText,X=0,Y=UnderText_Y,Height=UnderText_Size,Mode=Mode);
	
} // BlockModuleCuttout

//scale([25.4,25.4,25.4]) BlockModuleCuttout(Mode=Line_Mode);

module PanelOutline(X=-10,Y=-6,Size_X=14,Size_Y=10,Mode=3D_Mode){
	if (Mode==3D_Mode){
		translate([X,Y,0]) cube([Size_X,Size_Y,PanelThickness]);}
			
	if (Mode==Cutout_Mode){
			translate([X,Y,0]) square([Size_X,Size_Y]);	}
		
		/*	
	if (Mode==Hole_Mode){translate([X,Y,0]) {
			square([Size_X,0.01]);
			square([0.01,Size_Y]);
			
			translate([0,Size_Y-0.005,0]) square([Size_X,0.01]);
			translate([Size_X-0.005,0,0]) square([0.01,Size_Y]);
	}
	}
			*/
}


module PowerSwitch(Mode=3D_Mode){
	PowerBlock_x=1.25;
	PowerBlock_y=2;
	
	if (Mode==3D_Mode){
		translate([0,0,PanelThickness-0.03]){
			cube([PowerBlock_x,0.05,0.1]);
			cube([0.05,PowerBlock_y,0.1]);
			
			translate([0,PowerBlock_y-0.05,0]) cube([PowerBlock_x,0.05,0.1]);
			translate([PowerBlock_x-0.05,0,0]) cube([0.05,PowerBlock_y,0.1]);
		}
		
	}
	
	if (Mode==Line_Mode){
			square([PowerBlock_x,0.05]);
			square([0.05,PowerBlock_y]);
			
			translate([0,PowerBlock_y-0.05,0]) square([PowerBlock_x,0.05]);
			translate([PowerBlock_x-0.05,0,0]) square([0.05,PowerBlock_y]);
		
	}
	
	SwitchHole(PowerBlock_x/2,0.30,Mode=Mode);
	SwitchHole(PowerBlock_x/2,0.9,Mode=Mode);
	
	EngravedText(TheText="Power",X=PowerBlock_x/2,Y=PowerBlock_y-0.1,Height=0.25,Mode=Mode);
	EngravedText(TheText="ON",X=PowerBlock_x/2,Y=1.3,Height=0.2,Mode=Mode);
	EngravedText(TheText="OFF",X=PowerBlock_x/2,Y=0.7,Height=0.2,Mode=Mode);
	
	// led hole
	LED_Hole(X=PowerBlock_x/2,Y=PowerBlock_y-0.500,Mode=Mode);
		
} // PowerSwitch

//scale([25.4,25.4,25.4]) PowerSwitch(Mode=3D_Mode);

module TrackLine(X1=0,Y1=0,X2=1,Y2=0,StartTerm=false,EndTerm=false,Mode=3D_Mode){
	TrackLine_W=0.125;
	
	if (Mode==3D_Mode){
	translate([0,0,PanelThickness-0.03]){
		hull(){
			translate([X1,Y1,0]) cylinder(d=TrackLine_W,h=0.1);
			translate([X2,Y2,0]) cylinder(d=TrackLine_W,h=0.1);
		} // hull
		
		if (StartTerm==true) translate([X1-TrackLine_W/2,Y1-0.125,0]) cube([TrackLine_W/2,0.25,0.1]);
			
		if (EndTerm==true) translate([X2,Y2-0.125,0]) cube([TrackLine_W/2,0.25,0.1]);
	}}

	if (Mode==Line_Mode) {
		hull(){
			translate([X1,Y1,0]) circle(d=TrackLine_W);
			translate([X2,Y2,0]) circle(d=TrackLine_W);
		} // hull
		
		if (StartTerm==true) translate([X1-TrackLine_W/2,Y1-0.125,0]) square([TrackLine_W/2,0.25]);
			
		if (EndTerm==true) translate([X2,Y2-0.125,0]) square([TrackLine_W/2,0.25]);
	}

} // TrackLine

//scale([25.4,25.4,25.4]) TrackLine(X1=-1,Y1=0,X2=1,Y2=0,StartTerm=true,EndTerm=true,Mode=Line_Mode);

module PanelTest(Mode=3D_Mode){
	if (Mode==3D_Mode) {
	difference(){
		
		translate([-2,-2,0]) cube([4,5,PanelThickness]);
		
		translate([0,2.25,0])
		BlockModuleCuttout(UnderText="XCG",Has7Seg=false,Mode=Mode);
		
		BlockModuleCuttout(UnderText="YCG",Has7Seg=true,Mode=Mode);
		
		TrackLine(X1=-1,Y1=1,X2=1,Y2=1,StartTerm=true,EndTerm=false,Mode=Mode);
		LED_Hole(X=0.75,Y=1,Mode=Mode);
		
		TrackLine(X1=1,Y1=1,X2=0.5,Y2=0.5,StartTerm=false,EndTerm=false,Mode=Mode);
		LED_Hole(X=0.8,Y=0.8,Mode=Mode);
		
		TrackLine(X1=-1,Y1=0.5,X2=0.5,Y2=0.5,StartTerm=true,EndTerm=false,Mode=Mode);
	}} else {
		translate([0,2.25,0])
		BlockModuleCuttout(UnderText="XCG",Has7Seg=false,Mode=Mode);
		
		BlockModuleCuttout(UnderText="XCG",Has7Seg=true,Mode=Mode);
		
		TrackLine(X1=-1,Y1=1,X2=1,Y2=1,StartTerm=true,EndTerm=false,Mode=Mode);
		LED_Hole(X=0.75,Y=1,Mode=Mode);
		
		TrackLine(X1=1,Y1=1,X2=0.5,Y2=0.5,StartTerm=false,EndTerm=false,Mode=Mode);
		LED_Hole(X=0.8,Y=0.8,Mode=Mode);
		
		TrackLine(X1=-1,Y1=0.5,X2=0.5,Y2=0.5,StartTerm=true,EndTerm=false,Mode=Mode);
		//Alignment mark
		AlignmentMark(X=-2,Y=-2,Mode=Mode);
		
	}
} // PanelTest


//scale([25.4,25.4,25.4]) PanelTest(Mode=3D_Mode); // 3D view
//scale([25.4,25.4,25.4]) PanelTest(Mode=Line_Mode); // Text and track lines
//scale([25.4,25.4,25.4]) PanelTest(Mode=Hole_Mode);  //Holes only
//scale([25.4,25.4,25.4]) PanelTest(Mode=Lens_Mode); //LED lenses for overlay
//scale([25.4,25.4,25.4]) PanelTest(Mode=SwitchHole_Mode); // Switch holes only for overlay





















