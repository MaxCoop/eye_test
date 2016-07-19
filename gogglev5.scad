
//goggles
//union(){}
//intersection(){

//cylinder(height, r1, r2, center=true/false)


union(){


difference(){
union(){
translate([16,0,0]) rotate([90,90,90]) cylinder(2,24,24);
difference(){
translate([0,0,0]) rotate([90,90,90]) cylinder(16,32,24);
translate([0,0,0]) rotate([90,90,90]) cylinder(16,28,20);
}
}
//LED holes
translate([15,12,-12]) rotate([90,90,90]) cylinder(2,2,2,$fn = 12);
translate([15,12,12]) rotate([90,90,90]) cylinder(2,2,2,$fn = 12);
translate([15,-12,-12]) rotate([90,90,90]) cylinder(2,2,2,$fn = 12);
translate([15,-12,12]) rotate([90,90,90]) cylinder(2,2,2,$fn = 12);
//neopixel holes
translate([15,16,0]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
translate([15,0,16]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
translate([15,-16,0]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
translate([15,0,-16]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
//camera aperture
translate([15,0,0]) rotate([90,90,90]) cylinder(4,3,3);
}
//translate([-16,0,0])
difference(){
difference(){
translate([-24,0,0]) rotate([90,90,90]) cylinder(24,40,32);
translate([-24,0,0]) rotate([90,90,90]) cylinder(24,36,28);
}


//vertical cylinder cut
translate([-40,12,-40]) rotate([0,0,90]) cylinder(80,40,40);
//sphere cut
//translate([-20,2,0]) sphere(22);
//cylinder cut
//translate([-20,2,0]) rotate([97,90,90]) cylinder(20,28,14);


}
}