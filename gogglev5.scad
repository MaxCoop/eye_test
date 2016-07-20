
//goggles
//union(){}
//intersection(){
//cylinder(height, r1, r2, center=true/false)

union(){ //adds pegs for rpi camera mount

union(){

difference(){
union(){
translate([15,0,0]) rotate([90,90,90]) cylinder(4,24,24);
difference(){
translate([0,0,0]) rotate([90,90,90]) cylinder(16,32,24);
translate([0,0,0]) rotate([90,90,90]) cylinder(16,28,20);
}
}

//LED holes
translate([14,12,-12]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
translate([14,-12,12]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
translate([14,12,12]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
translate([14,-12,-12]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
//pin holes
translate([15,-13,13]) rotate([90,90,90]) cylinder(6,1,1);
translate([15,-11,11]) rotate([90,90,90]) cylinder(6,1,1);
translate([15,13,13]) rotate([90,90,90]) cylinder(6,1,1);
translate([15,11,11]) rotate([90,90,90]) cylinder(6,1,1);
translate([15,13,-13]) rotate([90,90,90]) cylinder(6,1,1);
translate([15,11,-11]) rotate([90,90,90]) cylinder(6,1,1);
translate([15,-13,-13]) rotate([90,90,90]) cylinder(6,1,1);
translate([15,-11,-11]) rotate([90,90,90]) cylinder(6,1,1);

//neopixel insets
translate([14,17,0]) rotate([90,90,90]) cylinder(2,7,7,$fn = 12);
translate([14,0,17]) rotate([90,90,90]) cylinder(3,7,7,$fn = 12);
translate([14,-18,0]) rotate([90,90,90]) cylinder(3,7,7,$fn = 12);
translate([14,0,-18]) rotate([90,90,90]) cylinder(2,7,7,$fn = 12);
//pin holes
/*
translate([15,0,-11]) rotate([90,90,90]) cylinder(4,1,1);
translate([15,0,-19]) rotate([90,90,90]) cylinder(4,1,1);
translate([15,3,-15]) rotate([90,90,90]) cylinder(4,1,1);
translate([15,-3,-15]) rotate([90,90,90]) cylinder(4,1,1);
*/

//camera aperture
translate([15,0,0]) rotate([90,90,90]) cylinder(4,3,3);
//lens inset
translate([14,0,0]) rotate([90,90,90]) cylinder(4,13,13);
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

//rpi camera mount
translate([20,10,0]) rotate([90,90,90]) cylinder(10,1,1);
translate([20,0,10]) rotate([90,90,90]) cylinder(10,1,1);
translate([20,-10,0]) rotate([90,90,90]) cylinder(10,1,1);
translate([20,0,-10]) rotate([90,90,90]) cylinder(10,1,1);

}
