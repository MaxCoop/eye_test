
//goggles
//union(){}
//intersection(){

//cylinder(height, r1, r2, center=true/false)

union(){
translate([8,0,0]) rotate([90,90,90]) cylinder(1,6,6);
difference(){
translate([0,0,0]) rotate([90,90,90]) cylinder(8,8,6);
translate([0,0,0]) rotate([90,90,90]) cylinder(8,7,5);
}
}

translate([-16,0,0])difference(){
translate([0,0,0]) rotate([90,90,90]) cylinder(16,10,8);
translate([-3,0,0]) rotate([80,90,90]) cylinder(20,12,8);
}