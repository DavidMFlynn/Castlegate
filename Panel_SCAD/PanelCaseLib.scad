// ****************************************
// 3D Printed Control Panel Case Library
// Filename: PanelCaseLib
// Created: 12/21/2016
// Revision: 1.1.0 8/20/2017
// Units: Millimeters
// ****************************************
// History:
// 1.1.0 8/20/2017 Added AMP connector and wall bolts
// 1.0.0 12/21/2016 First code
// ****************************************
//  for STL output

//rotate([-Panel_a,0,0])CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=0,Y=0) CaseTop();
//rotate([-Panel_a,0,0])CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=1,Y=0) CaseTop();
//rotate([-Panel_a,0,0])CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=2,Y=0) CaseTop();
//rotate([-Panel_a,0,0])CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=0,Y=1) CaseTop();
//rotate([-Panel_a,0,0])CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=1,Y=1) CaseTop();
//rotate([-Panel_a,0,0])CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=2,Y=1) CaseTop();

//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=0,Y=0,EdgeBolts=true) CaseWall();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=1,Y=0,EdgeBolts=true) CaseWall();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=2,Y=0,EdgeBolts=true) CaseWall();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=0,Y=1,EdgeBolts=true) CaseWall();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=1,Y=1,EdgeBolts=true) CaseWall();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=2,Y=1,EdgeBolts=true) CaseWall();

//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=0,Y=0) CaseBottom();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=1,Y=0) CaseBottom();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=2,Y=0) CaseBottom();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=0,Y=1) CaseBottom();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=1,Y=1) CaseBottom();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=2,Y=1) CaseBottom();

// ***************************************
//  usefull stuff
//AMP_Connector();
//translate([0,0,1])CaseTop();
//CaseWall();
//translate([0,0,-12-1])CaseBottom();
//Panel(Panel_X=Panel_x,Panel_Y=Panel_y,Panel_z);
//RoundRect(X=25,Y=25,Z=25,R=2);
//CutIt(XSize=350,YSize=350,XBite=150,YBite=150,X=0,Y=0) //children();
// ***************************************

include <CommonStuff.scad>

Panel_x=19.5*25.4+2; // includes 2mm extra
Panel_y=9.5*25.4+2;
Panel_z=5;

SupportLip_w=6;
Panel_a=20; // Angle of panel face

Case_Thickness=18;
CaseCorner_r=5;
Case_x=Panel_x+Case_Thickness*2-SupportLip_w*2;
Case_y=cos(Panel_a)*(Panel_y-SupportLip_w*2+Case_Thickness*2);
Case_zf=20;
Case_z=Case_zf+sin(Panel_a)*(Panel_y-SupportLip_w*2+Case_Thickness*2);

		Bolts_x=floor(Case_x/40);
		Bolts_y=floor((Panel_y+Case_Thickness*2-SupportLip_w*2)/40);

echo(Case_y=Case_y/25.4);
echo(Case_x=Case_x/25.4);
echo(Case_z=Case_z/25.4);
//cylinder(r=10,h=Case_z);
Overlap=0.05;
$fn=60;

module AMP_Connector(){
	AMP_xy=45;
	AMP_Corner_r=4.2;
	AMP_Backshell_d=39;
	
	// body
	hull(){
		translate([-AMP_xy/2+AMP_Corner_r,-AMP_xy/2+AMP_Corner_r,0]) cylinder(r1=AMP_Corner_r,r2=AMP_Corner_r*8,h=20);
		translate([AMP_xy/2-AMP_Corner_r,-AMP_xy/2+AMP_Corner_r,0]) cylinder(r1=AMP_Corner_r,r2=AMP_Corner_r*8,h=20);
		translate([-AMP_xy/2+AMP_Corner_r,AMP_xy/2-AMP_Corner_r,0]) cylinder(r1=AMP_Corner_r,r2=AMP_Corner_r*8,h=20);
		translate([AMP_xy/2-AMP_Corner_r,AMP_xy/2-AMP_Corner_r,0]) cylinder(r1=AMP_Corner_r,r2=AMP_Corner_r*8,h=20);
	} // hull
	
	// bolts
		translate([-AMP_xy/2+AMP_Corner_r,-AMP_xy/2+AMP_Corner_r,0]) BoltHole6(depth=14);
		translate([AMP_xy/2-AMP_Corner_r,-AMP_xy/2+AMP_Corner_r,0]) BoltHole6(depth=14);
		translate([-AMP_xy/2+AMP_Corner_r,AMP_xy/2-AMP_Corner_r,0]) BoltHole6(depth=14);
		translate([AMP_xy/2-AMP_Corner_r,AMP_xy/2-AMP_Corner_r,0]) BoltHole6(depth=14);
	
	// backshell clearance
	translate([0,0,-20]) cylinder(d=AMP_Backshell_d,h=21);
	
} // AMP_Connector

//AMP_Connector();

module RoundRect(X=25,Y=25,Z=25,R=2){
	hull(){
		translate([-X/2+R,-Y/2+R,0]) cylinder(r=R,h=Z);
		translate([X/2-R,-Y/2+R,0]) cylinder(r=R,h=Z);
		translate([-X/2+R,Y/2-R,0]) cylinder(r=R,h=Z);
		translate([X/2-R,Y/2-R,0]) cylinder(r=R,h=Z);
	} // hull
	
} // RoundRect

//RoundRect();

module Panel(Panel_X=Panel_x,Panel_Y=Panel_y,Panel_z){
	//translate([-Panel_X/2,-Panel_Y/2,0]) 
	cube([Panel_X,Panel_Y,Panel_Z]);
} // Panel

module CaseWall(){
	difference(){
		
		RoundRect(X=Case_x,Y=Case_y,Z=Case_z,R=CaseCorner_r);
		
		// inside
		translate([0,0,-Overlap])
		RoundRect(X=Case_x-Case_Thickness*2,Y=Case_y-Case_Thickness*2,Z=Case_z+Overlap*2,R=2);
		
		// sloped top
		if (Panel_a!=0){
			translate([-Case_x/2-Overlap,-Case_y/2-Overlap,Case_zf]) rotate([Panel_a,0,0])
			cube([Case_x+Overlap*2,Panel_y+Case_Thickness*2,Case_z]);
		} // if
		
		// Panel
		translate([0,0,Case_zf+tan(Panel_a)*(Case_y/2)-Panel_z]) rotate([Panel_a,0,0])
			RoundRect(X=Panel_x,Y=Panel_y,Z=Panel_z+Overlap*2,R=2);
		
		//translate([-Panel_x/2,-Case_y/2,Case_zf]) rotate([Panel_a,0,0])
		//	translate([0,cos(Panel_a)*Case_Thickness-SupportLip_w,-Panel_z])
		//		cube([Panel_x,Panel_y,Panel_z+Overlap*2]);
		
		// Bolt holes
		//echo(Bolts_x);
		//echo(Bolts_y);
		
		// connector on lower left back
		translate([-Case_x/2+50,Case_y/2-Case_Thickness+10,40])rotate([-90,0,0])AMP_Connector();
		
		// top front
		translate([-Case_x/2,-Case_y/2+(Case_Thickness-SupportLip_w)/2,Case_zf])
			for (j=[0:Bolts_x-1]) translate([j*Case_x/Bolts_x+Case_x/Bolts_x/2,0,3])
				BoltHole(depth=15);
		
		// bottom front
		translate([-Case_x/2,-Case_y/2+Case_Thickness/2,0])
			for (j=[0:Bolts_x-1]) translate([j*Case_x/Bolts_x+Case_x/Bolts_x/2,0,0])
				rotate([180,0,0]) BoltHole(depth=15);
		// bottom back
		translate([-Case_x/2,Case_y/2-Case_Thickness/2,0])
			for (j=[0:Bolts_x-1]) translate([j*Case_x/Bolts_x+Case_x/Bolts_x/2,0,0])
				rotate([180,0,0]) BoltHole(depth=15);
	
		// top back
		translate([-Case_x/2,Case_y/2-(Case_Thickness-SupportLip_w)/2,Case_z])
			for (j=[0:Bolts_x-1]) translate([j*Case_x/Bolts_x+Case_x/Bolts_x/2,0,0])
				BoltHole(depth=15);
			
		// top left
		translate([-Case_x/2+(Case_Thickness-SupportLip_w)/2,-Case_y/2,Case_zf]) rotate([Panel_a,0,0])
			for (j=[0:Bolts_y-1]) translate([0,j*Case_y/Bolts_y+Case_y/Bolts_y/2,1])
				rotate([-Panel_a,0,0]) BoltHole(depth=15);
			
		// bottom left
		translate([-Case_x/2+Case_Thickness/2,-Case_y/2,0])
			for (j=[0:Bolts_y-1]) translate([0,j*Case_y/Bolts_y+Case_y/Bolts_y/2,0])
				 rotate([180,0,0]) BoltHole(depth=15);
		// bottom right
		translate([Case_x/2-Case_Thickness/2,-Case_y/2,0])
			for (j=[0:Bolts_y-1]) translate([0,j*Case_y/Bolts_y+Case_y/Bolts_y/2,0])
				 rotate([180,0,0]) BoltHole(depth=15);
			
		// top right
		translate([Case_x/2-(Case_Thickness-SupportLip_w)/2,-Case_y/2,Case_zf]) rotate([Panel_a,0,0])
			for (j=[0:Bolts_y-1]) translate([0,j*Case_y/Bolts_y+Case_y/Bolts_y/2,1])
				rotate([-Panel_a,0,0]) BoltHole(depth=15);

	}// diff
} // CaseWall



//color("Blue")
//CaseWall();

CaseTop_z=12;
CaseOA_z=Case_z+CaseTop_z;
PanelLip=5;



module CaseTop(){
	difference(){
		
		hull(){
			// bottom outside corners
			translate([-Case_x/2+CaseCorner_r,-Case_y/2+CaseCorner_r,0]) cylinder(r=CaseCorner_r,h=1);
			translate([Case_x/2-CaseCorner_r,-Case_y/2+CaseCorner_r,0]) cylinder(r=CaseCorner_r,h=1);
			translate([-Case_x/2+CaseCorner_r,Case_y/2-CaseCorner_r,0]) cylinder(r=CaseCorner_r,h=1);
			translate([Case_x/2-CaseCorner_r,Case_y/2-CaseCorner_r,0]) cylinder(r=CaseCorner_r,h=1);
			
			// top outside corners
			translate([-Case_x/2+CaseCorner_r,-Case_y/2+CaseCorner_r,Case_z+CaseTop_z-CaseCorner_r-tan(Panel_a)*Case_y]) sphere(r=CaseCorner_r);
			translate([Case_x/2-CaseCorner_r,-Case_y/2+CaseCorner_r,Case_z+CaseTop_z-CaseCorner_r-tan(Panel_a)*Case_y]) sphere(r=CaseCorner_r);
			translate([-Case_x/2+CaseCorner_r,Case_y/2-CaseCorner_r,Case_z+CaseTop_z-CaseCorner_r]) sphere(r=CaseCorner_r);
			translate([Case_x/2-CaseCorner_r,Case_y/2-CaseCorner_r,Case_z+CaseTop_z-CaseCorner_r]) sphere(r=CaseCorner_r);
			
		} // hull
	
		//RoundRect(X=Case_x,Y=Case_y,Z=Case_z+CaseTop_z,R=CaseCorner_r);
	
		// inside
		translate([0,0,-Overlap])
		RoundRect(X=Case_x-Case_Thickness*2,Y=Case_y-Case_Thickness*2,Z=Case_z+CaseTop_z+Overlap*2,R=2);
		
		// sloped top of Case
		if (Panel_a!=0){
			translate([-Case_x/2-Overlap,-Case_y/2-Overlap,Case_zf]) rotate([Panel_a,0,0])
			mirror([0,0,1])translate([0,-25,0])cube([Case_x+Overlap*2,Panel_y+Case_Thickness*2+25,Case_z]);
		} // if
		
		// sloped top of Case cover
		//if (Panel_a!=0){
		//	translate([-Case_x/2-Overlap,-Case_y/2-Overlap,Case_zf+CaseTop_z]) rotate([Panel_a,0,0])
		//	translate([0,-25,0])cube([Case_x+Overlap*2,Panel_y+Case_Thickness*2+25,Case_z]);
		//} // if
		
		// Panel
		//translate([-Panel_x/2,-Case_y/2,Case_zf]) rotate([Panel_a,0,0])
		//	translate([0,cos(Panel_a)*Case_Thickness-SupportLip_w,-Panel_z])
		//		cube([Panel_x,Panel_y,Panel_z+Overlap*2]);
		
		// Bolt holes
		//echo(Bolts_x);
		//echo(Bolts_y);
		
		// top front
		translate([-Case_x/2,-Case_y/2+(Case_Thickness-SupportLip_w)/2,Case_zf+CaseTop_z])
			for (j=[0:Bolts_x-1]) translate([j*Case_x/Bolts_x+Case_x/Bolts_x/2,0,3])
				BoltHeadHole(depth=15);
		
	
		// top back
		translate([-Case_x/2,Case_y/2-(Case_Thickness-SupportLip_w)/2,Case_z+CaseTop_z])
			for (j=[0:Bolts_x-1]) translate([j*Case_x/Bolts_x+Case_x/Bolts_x/2,0,0])
				BoltHeadHole(depth=15);
			
		// top left
		translate([-Case_x/2+(Case_Thickness-SupportLip_w)/2,-Case_y/2,Case_zf+CaseTop_z]) rotate([Panel_a,0,0])
			for (j=[0:Bolts_y-1]) translate([0,j*Case_y/Bolts_y+Case_y/Bolts_y/2,1])
				rotate([-Panel_a,0,0]) BoltHeadHole(depth=15);
			
			
		// top right
		translate([Case_x/2-(Case_Thickness-SupportLip_w)/2,-Case_y/2,Case_zf+CaseTop_z]) rotate([Panel_a,0,0])
			for (j=[0:Bolts_y-1]) translate([0,j*Case_y/Bolts_y+Case_y/Bolts_y/2,1])
				rotate([-Panel_a,0,0]) BoltHeadHole(depth=15);

	}// diff
} // CaseTop

//translate([0,0,0.2])
//rotate([-Panel_a,0,0])
//CaseTop();

CaseBottom_t=12;
CaseBotPnl_t=6.7;
echo("Bottom cover x=",Case_x-Case_Thickness*2+10," y=",Case_y-Case_Thickness*2+10);

module CaseBottom(){
	difference(){
		RoundRect(X=Case_x,Y=Case_y,Z=CaseBottom_t,R=CaseCorner_r);
		
		// inside
		translate([0,0,-Overlap])
			RoundRect(X=Case_x-Case_Thickness*2,Y=Case_y-Case_Thickness*2,Z=CaseBottom_t+Overlap*2,R=2);
	
		// Panel
		translate([0,0,CaseBottom_t-CaseBotPnl_t]) 
			RoundRect(X=Case_x-Case_Thickness*2+10,Y=Case_y-Case_Thickness*2+10,Z=CaseBotPnl_t+Overlap*2,R=2);
				
		// Bolt holes
		//echo(Bolts_x);
		//echo(Bolts_y);
		
		// bottom front
		translate([-Case_x/2,-Case_y/2+Case_Thickness/2,0])
			for (j=[0:Bolts_x-1]) translate([j*Case_x/Bolts_x+Case_x/Bolts_x/2,0,0])
				rotate([180,0,0]) BoltHeadHole(depth=15);
			
		// bottom back
		translate([-Case_x/2,Case_y/2-Case_Thickness/2,0])
			for (j=[0:Bolts_x-1]) translate([j*Case_x/Bolts_x+Case_x/Bolts_x/2,0,0])
				rotate([180,0,0]) BoltHeadHole(depth=15);
	
		// bottom left
		translate([-Case_x/2+Case_Thickness/2,-Case_y/2,0])
			for (j=[0:Bolts_y-1]) translate([0,j*Case_y/Bolts_y+Case_y/Bolts_y/2,0])
				 rotate([180,0,0]) BoltHeadHole(depth=15);
			
		// bottom right
		translate([Case_x/2-Case_Thickness/2,-Case_y/2,0])
			for (j=[0:Bolts_y-1]) translate([0,j*Case_y/Bolts_y+Case_y/Bolts_y/2,0])
				 rotate([180,0,0]) BoltHeadHole(depth=15);
			
	}// diff
} // CaseBottom

//CaseBottom();


module CutIt(XSize=350,YSize=350,XBite=3,YBite=2,X=0,Y=0,EdgeBolts=false){
	XStep=XSize/XBite;
	YStep=YSize/YBite;
	echo(XStep=XStep);
	echo(YStep=YStep);
	difference(){
		intersection(){
			translate([-XSize/2+XStep*X-Overlap,-YSize/2+YStep*Y-Overlap,-Overlap]) cube([XStep+Overlap*2,YStep+Overlap*2,200]);
			children();
		} // intersection
		
		if (EdgeBolts==true){
		// front bolt holes
		if (Y==0 && X<XBite-1){
			translate([-XSize/2+XStep*(X+1)+8,-YSize/2+3,10])rotate([0,0,-20])rotate([0,90,0]) #BoltHole(depth=20);
			
		}
		// back bolt holes
		if (Y==YBite-1 && X<XBite-1){
			translate([-XSize/2+XStep*(X+1)+8,YSize/2-3,10])rotate([0,0,20])rotate([0,90,0]) #BoltHole(depth=25);
			translate([-XSize/2+XStep*(X+1)+8,YSize/2-3,50])rotate([0,0,20])rotate([0,90,0]) #BoltHole(depth=25);
			translate([-XSize/2+XStep*(X+1)+8,YSize/2-3,90])rotate([0,0,20])rotate([0,90,0]) #BoltHole(depth=25);
		}
		// left bolt head holes
		if (Y<YBite-1 && X==0){
			translate([-XSize/2+3,-YSize/2+YStep*(Y+1)-8,10])rotate([0,0,-110])rotate([0,90,0]) #BoltHeadHole(depth=20,lAccessDepth=30);
			translate([-XSize/2+3,-YSize/2+YStep*(Y+1)-8,50])rotate([0,0,-110])rotate([0,90,0]) #BoltHeadHole(depth=20,lAccessDepth=30);
		}
		// left bolt holes
		if (Y>0 && X==0){
			translate([-XSize/2+3,-YSize/2+YStep*Y-8,10])rotate([0,0,-110])rotate([0,90,0]) #BoltHole(depth=25);
			translate([-XSize/2+3,-YSize/2+YStep*Y-8,50])rotate([0,0,-110])rotate([0,90,0]) #BoltHole(depth=25);
		}
		// right bolt holes
		if (Y>0 && X==XBite-1){
			translate([XSize/2-3,-YSize/2+YStep*Y-8,10])rotate([0,0,-70])rotate([0,90,0]) #BoltHole(depth=25);
			translate([XSize/2-3,-YSize/2+YStep*Y-8,50])rotate([0,0,-70])rotate([0,90,0]) #BoltHole(depth=25);
		}
		// right bolt head holes
		if (Y<YBite-1 && X==XBite-1){
			translate([XSize/2-3,-YSize/2+YStep*(Y+1)-8,10])rotate([0,0,-70])rotate([0,90,0]) #BoltHeadHole(depth=20,lAccessDepth=30);
			translate([XSize/2-3,-YSize/2+YStep*(Y+1)-8,50])rotate([0,0,-70])rotate([0,90,0]) #BoltHeadHole(depth=20,lAccessDepth=30);
		}
		// front bolt head holes
		if (Y==0 && X>0){
			translate([-XSize/2+XStep*X+8,-YSize/2+3,10])rotate([0,0,-20])rotate([0,90,0]) #BoltHeadHole(depth=20,lAccessDepth=30);
		}
		// back bolt head holes
		if (Y==YBite-1 && X>0){
			translate([-XSize/2+XStep*X+8,YSize/2-3,10])rotate([0,0,20])rotate([0,90,0]) #BoltHeadHole(depth=20,lAccessDepth=30);
			translate([-XSize/2+XStep*X+8,YSize/2-3,50])rotate([0,0,20])rotate([0,90,0]) #BoltHeadHole(depth=20,lAccessDepth=30);
			translate([-XSize/2+XStep*X+8,YSize/2-3,90])rotate([0,0,20])rotate([0,90,0]) #BoltHeadHole(depth=20,lAccessDepth=30);
		}
	}

	}// diff
} // CutIt

//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=1,Y=0,EdgeBolts=true) CaseWall();
//CutIt(XSize=Case_x,YSize=Case_y,XBite=3,YBite=2,X=2,Y=0,EdgeBolts=true) CaseWall();














