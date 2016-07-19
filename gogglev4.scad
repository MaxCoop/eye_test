
//goggles
//union(){}
//intersection(){

//cylinder(height, r1, r2, center=true/false)


union(){

union(){
translate([8,0,0]) rotate([90,90,90]) cylinder(1,12,12);
difference(){
translate([0,0,0]) rotate([90,90,90]) cylinder(8,16,12);
translate([0,0,0]) rotate([90,90,90]) cylinder(8,14,10);
}
}

//translate([-16,0,0])
difference(){
difference(){
translate([-12,0,0]) rotate([90,90,90]) cylinder(12,20,16);
translate([-12,0,0]) rotate([90,90,90]) cylinder(12,18,14);
}


//vertical cylinder cut
translate([-20,6,-20]) rotate([0,0,90]) cylinder(40,20,20);
//sphere cut
//translate([-20,2,0]) sphere(22);
//cylinder cut
//translate([-20,2,0]) rotate([97,90,90]) cylinder(20,28,14);


}
}