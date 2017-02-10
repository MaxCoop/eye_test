
//goggles
//union(){}
//intersection(){
//cylinder(height, r1, r2, center=true/false)

difference(){
union(){ //adds pegs for rpi camera mount

union(){

difference(){
union(){
translate([15,0,0]) rotate([90,90,90]) cylinder(4,24,24);
difference(){
//must double the length of this cylinder for focal length
translate([0,0,0]) rotate([90,90,90]) cylinder(16,32,24);
translate([0,0,0]) rotate([90,90,90]) cylinder(32,28,20);
}
}

//LED holes
translate([14,12,-12]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
//translate([14,-12,12]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
//translate([14,12,12]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);
//translate([14,-12,-12]) rotate([90,90,90]) cylinder(2,3,3,$fn = 12);


//neopixel insets
translate([14,18,0]) rotate([90,90,90]) cylinder(3,7,7,$fn = 12);
translate([14,0,18]) rotate([90,90,90]) cylinder(3,7,7,$fn = 12);
//translate([14,-18,0]) rotate([90,90,90]) cylinder(3,7,7,$fn = 12);
//translate([14,0,-18]) rotate([90,90,90]) cylinder(3,7,7,$fn = 12);
//pin holes
/*
translate([15,0,-11]) rotate([90,90,90]) cylinder(4,1,1);
translate([15,0,-19]) rotate([90,90,90]) cylinder(4,1,1);
translate([15,3,-15]) rotate([90,90,90]) cylinder(4,1,1);
translate([15,-3,-15]) rotate([90,90,90]) cylinder(4,1,1);
*/

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
translate([24,-2,2]) rotate([90,45,90]) cube(size = [27, 28, 10], center = true);
//translate([20,0,10]) rotate([90,90,90]) cylinder(10,1,1);
//translate([20,-10,0]) rotate([90,90,90]) cylinder(10,1,1);
//translate([20,0,-10]) rotate([90,90,90]) cylinder(10,1,1);

}

//Rpi mounting bracket
//rpi camera mount
translate([25,0,0]) rotate([90,45,90]) cube(size = [30, 26, 12], center = true);

//camera aperture
translate([17,0,0]) rotate([90,90,90]) cylinder(10,5,5);

//LED pin holes
translate([15,-13,13]) rotate([90,90,90]) cylinder(10,1,1);
translate([15,-11,11]) rotate([90,90,90]) cylinder(20,1,1);
translate([15,13,13]) rotate([90,90,90]) cylinder(10,1,1);
translate([15,11,11]) rotate([90,90,90]) cylinder(10,1,1);
translate([15,13,-13]) rotate([90,90,90]) cylinder(10,1,1);
translate([15,11,-11]) rotate([90,90,90]) cylinder(10,1,1);
translate([15,-13,-13]) rotate([90,90,90]) cylinder(10,1,1);
translate([15,-11,-11]) rotate([90,90,90]) cylinder(10,1,1);

}
