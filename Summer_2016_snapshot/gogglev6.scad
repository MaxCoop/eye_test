
//goggles
//union(){}
//intersection(){
//cylinder(height, r1, r2, center=true/false)
//cube()

//focal cone
tip_radius = 28;
tip_thickness = 4;
centre_radius = 32;
wall_thickness = 4;
tip_length = 30; //akin to distance between eye and mounted lens

//eyepiece size
eyepiece_length = 24;
eyepiece_end_radius = 40;

//eyepiece shape
cut_cylinder_radius = 40;
cut_offset = 12;

//lens
seating_depth = 5;
lens_radius = 13;

//led size
led_radius = 4;
led_inset = 3;
pin_width = 1;

//neopixel size
neopixel_radius = 7;
neopixel_inset = 4;
neopixel_location = 13;

//camera aperture
aperture_radius = 5;

//rpi camera mount
cube_size = 27;
mount_height = 10;
mount_wall_thickness = 1;

//LED diffuser - removed - doesn't work
//diffuser_height = 15;
//diffuser_radius = 12;

//upper_diameter = 0.13*(diffuser_height+tip_thickness+1)+tip_radius-1;
//lower_diameter = 0.13*diffuser_height+tip_radius-1;

difference(){
union(){ //adds pegs for rpi camera mount

union(){

difference(){

union(){
//end disk
translate([tip_length,0,0]) rotate([90,90,90]) cylinder(tip_thickness,tip_radius,tip_radius);

//focal tip
difference(){
//subtract one cone from another for hollow cylinder
translate([0,0,0]) rotate([90,90,90]) cylinder(tip_length,centre_radius,tip_radius);
translate([0,0,0]) rotate([90,90,90]) cylinder(tip_length,centre_radius-wall_thickness,tip_radius-wall_thickness);
}
}

//LED  inset
translate([tip_length-tip_thickness/2,tip_radius-1.5*wall_thickness-led_radius,0]) rotate([90,90,90]) cylinder(led_inset,led_radius,led_radius,$fn = 12);

//neopixel insets
translate([tip_length-tip_thickness/2,-neopixel_location,neopixel_location]) rotate([90,90,90]) cylinder(neopixel_inset,neopixel_radius,neopixel_radius,$fn = 12);
translate([tip_length-tip_thickness/2,-neopixel_location,-neopixel_location]) rotate([90,90,90]) cylinder(neopixel_inset,neopixel_radius,neopixel_radius,$fn = 12);

//lens inset
translate([tip_length-tip_thickness/2,0,0]) rotate([90,90,90]) cylinder(seating_depth,lens_radius,lens_radius);
}


//eyepiece
difference(){
//makes hollow cone cylinder as base eyepiece
difference(){
translate([-eyepiece_length,0,0]) rotate([90,90,90]) cylinder(eyepiece_length,eyepiece_end_radius,centre_radius);
translate([-eyepiece_length,0,0]) rotate([90,90,90]) cylinder(eyepiece_length,eyepiece_end_radius-wall_thickness,centre_radius-wall_thickness);
}
//controls shape of eyepiece
//vertical cylinder cut
translate([-cut_cylinder_radius,cut_offset,-cut_cylinder_radius]) rotate([0,0,90]) cylinder(80,cut_cylinder_radius,cut_cylinder_radius);
//sphere cut
//translate([-20,2,0]) sphere(22);
//cylinder cut
//translate([-20,2,0]) rotate([97,90,90]) cylinder(20,28,14);
}

}//closes eyepiece tip base union

//rpi camera mount
translate([tip_length+mount_height-tip_thickness/2+1,-2,2]) rotate([90,45,90]) cube(size = [cube_size, cube_size+1, mount_height], center = true);

//LED diffuser
/*
difference(){
translate([tip_length-diffuser_height,tip_radius-wall_thickness,0]) rotate([90,90,90]) cylinder(tip_thickness,diffuser_radius,diffuser_radius);
//subtraction ring
difference(){
translate([tip_length-diffuser_height-1,0,0]) rotate([90,90,90]) cylinder(tip_thickness+2,2*centre_radius,2*centre_radius);
translate([tip_length-diffuser_height-1,0,0]) rotate([90,90,90]) cylinder(tip_thickness+2,upper_diameter,lower_diameter);
}
}
*/

}//closes goggle mount union

//Rpi mounting bracket
//subtracts centre of mounting block
translate([tip_length+mount_height+1-tip_thickness/2+1,0,0]) rotate([90,45,90]) cube(size = [cube_size+3, cube_size-1, 1.2*mount_height], center = true);
//removes secondary block for neopixel pins
translate([tip_length+mount_height+1-tip_thickness/2+1,0,0]) rotate([90,45,90]) cube(size = [50, 10, 1.2*mount_height], center = true);


//LED pin holes
translate([tip_length-tip_thickness/2,tip_radius-1.5*wall_thickness-led_radius*0.5,0]) rotate([90,90,90]) cylinder(10,pin_width,pin_width);
translate([tip_length-tip_thickness/2,tip_radius-1.5*wall_thickness-led_radius*1.5,0]) rotate([90,90,90]) cylinder(10,pin_width,pin_width);

//neopixel pin holes
//Top
translate([tip_length-tip_thickness/2,-neopixel_location,neopixel_location+0.75*neopixel_radius]) rotate([90,90,90]) cylinder(20,pin_width,pin_width);
//Bottom
translate([tip_length-tip_thickness/2,-neopixel_location,neopixel_location-0.75*neopixel_radius]) rotate([90,90,90]) cylinder(20,pin_width,pin_width);
//Left
translate([tip_length-tip_thickness/2,-neopixel_location-0.75*neopixel_radius,neopixel_location]) rotate([90,90,90]) cylinder(20,pin_width,pin_width);
//Right
translate([tip_length-tip_thickness/2,-neopixel_location+0.75*neopixel_radius,neopixel_location]) rotate([90,90,90]) cylinder(20,pin_width,pin_width);


//Top
translate([tip_length-tip_thickness/2,-neopixel_location,-neopixel_location+0.75*neopixel_radius]) rotate([90,90,90]) cylinder(20,pin_width,pin_width);
//Bottom
translate([tip_length-tip_thickness/2,-neopixel_location,-neopixel_location-0.75*neopixel_radius]) rotate([90,90,90]) cylinder(20,pin_width,pin_width);
//Left
translate([tip_length-tip_thickness/2,-neopixel_location-0.75*neopixel_radius,-neopixel_location]) rotate([90,90,90]) cylinder(20,pin_width,pin_width);
//Right
translate([tip_length-tip_thickness/2,-neopixel_location+0.75*neopixel_radius,-neopixel_location]) rotate([90,90,90]) cylinder(20,pin_width,pin_width);

//camera aperture
translate([tip_length-tip_thickness/2,0,0]) rotate([90,90,90]) cylinder(10,aperture_radius,aperture_radius);

}


