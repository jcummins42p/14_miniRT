*** miniRT project for school 42: akretov and jcummins ***

Program will take any number of files as command line arguments, though it will
exit if any of them are not actual files. It currently does NOT check that the
.rt suffix is present in the file name - maybe something to add?

Parser will also mark any file that doesn't supply the minimum 3 unique elements
of the scene (Ambient light, Camera, Light source) and refuse to render it. If
any of these appear twice in the file, this will also mark the scene as invalid.

Once parsed, the program will attempt to display the first scene (given as the
first argument) which will result in a black sceen if that file is invalid.

Use the numpad '+' and '-' keys to select a different scene. The scene number and
file name should be previewed in the top left of the window, along with a warning
if the file cannot be displayed for the above reasons.

Press numpad 'enter' to move to the selected scene. Any changes made to a scene
will persist while the program is running.

Camera controls are currently limited to axis aligned movement. The algorithms
needed to change normal vectors require some complex numbers and I have not yet
looked closely into them. This is also required for the shape transformations.

There are two rays cast per pixel:
	the first from the camera to get the colour of the first object it meeets
	the second from that meeting point towards the light source, to get the
	brightness and distance of the spot light.

Controls:
	Click an object to select it - selected object highlighted in white.
	To select light position (with directional controls below) - press p
	To select light values (

Positional Controls:
	left			cam.point[_X]-- 	= numpad 4
	right 			cam.point[_X]++		= numpad 6
	away from cam	com.dir[_Z] = 1		= numpad 8
	towards cam		com.dir[_Z] = -1	= numpad 2
	down			cam.point[_Y]-- 	= numpad 1
	up				cam.point[_Y]++ 	= numpad 3
	camera turn 90 degrees left			= numpad 7
	camera turn 90 degrees right		= numpad 9

Color Controls:
	Increase hue red component			= numpad 7
	Decrease hue red component			= numpad 1
	Increase hue green component		= numpad 8
	Decrease hue green component		= numpad 2
	Increase hue blue component			= numpad 9
	Decrease hue blue component			= numpad 3
	Decrease luminosity					= numpad 4
	Increase luminosity					= numpad 6

Mandatory:
	Add cylinder maths

Bonus:
	Specular reflections

Performance:
	Add bsp tree culling
	Finish calculating bounding boxes for cylinders (capsules is easier)
