
//goggles
//union(){}
//intersection(){
//cylinder(height, r1, r2, center=true/false)
//cube([,,])

//focal cone
tip_radius = 20;
tip_thickness = 4;
centre_radius = 32;
wall_thickness = 4;
tip_length = 0; //akin to distance between eye and mounted lens

//lens
seating_depth = 5;
lens_radius = 13;

//camera aperture
aperture_radius = 8;

//mount details
phone_mount_location = 15;
mount_width = 7;
mount_depth =5;

//phone details
phone_depth = 12;
mount_height = phone_depth;
claw_length = 10;
claw_depth = mount_depth;
base_depth = tip_radius - lens_radius;

union(){

difference(){

//end disk
translate([tip_length,0,0]) rotate([90,90,90]) cylinder(tip_thickness,tip_radius,tip_radius);

//lens inset
translate([tip_length-tip_thickness/2,0,0]) rotate([90,90,90]) cylinder(seating_depth,lens_radius,lens_radius);

//camera aperture
translate([tip_length-tip_thickness/2,0,0]) rotate([90,90,90]) cylinder(10,aperture_radius,aperture_radius);

}//closes difference for lens mount

translate([tip_length-mount_height,phone_mount_location-mount_width/2,mount_depth/2]) rotate([90,90,90]) cube([mount_width, mount_depth,mount_height]);
translate([tip_length-mount_height-claw_depth,phone_mount_location-mount_width/2-claw_length/2,mount_depth/2]) rotate([90,90,90]) cube([mount_width, claw_length,claw_depth]);
translate([tip_length-mount_depth,phone_mount_location-base_depth/2,mount_depth/2]) rotate([90,90,90]) cube([mount_width, base_depth,claw_depth]);


translate([tip_length-mount_height,-mount_width/2,phone_mount_location+mount_depth/2]) rotate([90,90,90]) cube([mount_depth, mount_width,mount_height]);
translate([tip_length-mount_height-claw_depth,-mount_width/2,phone_mount_location+mount_depth/2]) rotate([90,90,90]) cube([ claw_length,mount_width, claw_depth]);
translate([tip_length-mount_depth,-mount_width/2,phone_mount_location+0.75*base_depth]) rotate([90,90,90]) cube([mount_width, base_depth,claw_depth]);

}//closes union with phone holder

