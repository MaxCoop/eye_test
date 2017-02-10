
//goggles
//union(){}
//intersection(){

//cylinder(height, r1, r2, center=true/false)

union(){

union(){
translate([8,0,0]) rotate([90,90,90]) cylinder(1,6,6);
difference(){
translate([0,0,0]) rotate([90,90,90]) cylinder(8,8,6);
translate([0,0,0]) rotate([90,90,90]) cylinder(8,7,5);
}
}

//translate([-16,0,0])
difference(){
difference(){
translate([-8,0,0]) rotate([90,90,90]) cylinder(8,10,8);
translate([-8,0,0]) rotate([90,90,90]) cylinder(8,9,7);
}

translate([-20,1,0]) rotate([90,90,90]) cylinder(20,16,7);
}

}