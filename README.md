# fdf  - fil de fer

fdf is a program that generates 3D wireframe images from 2D character maps.

this project complies with the 42 Network norms.

no for loops,
no declarations/initializations on control structures;
functions have a max of 5 arguments and a total of 25 lines,
maximum 5 functions per file.
no functions from any libray except for,
	open() / close() / read / write / malloc / free
	perror / strerror / exit
	anything from math.h

etc.

first step is veryfying the file exists, that we have authorization to read it and has a valid extension and that the format complies with our softwares requesites.

after this we create a struct that will hold the cartesian coordinates from our input file.
for this i have created a t_point struct that holds 4 ints.
a vector3, x, y, z.
a color, saved in a 32 bit int.

in this process we use get_next_line to read the input file line by line,
and in each line we use split to get the Z value, and if possible, we use split again with atoi to exctract the color value

after creating a 2D array of t_point structs, each one holding the cartesian coordinates and color of each point, we will  convert these values
to their correspondant values in isometric perspective, scale and center these points.

explain conversion, scaling and centering.

after that we use a line drawing algorightm, DDA, to print all the horizontal and vertical lines beetween points, starting at 0,0.

explain DDA logic.

during the application of the DDA algo we also apply color,
in the case that the read file has no color values, we will give a color value based on the Z value of each point.
then using the number of steps necessaery to draw each line, we set a ratio of color to be applied to each pixel on the line, starting with the color of the start point, and ending in the color of the end point.
with each step we blend the color value from the start color to the end color.

explain zoom, translation and rotation


explain the minilibx libary, startup, update and shutdown functions.
