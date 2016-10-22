User Interface:
    Switch Between Julia and Mandelbrot graphs: hover over point that the
        Julia set needs to be calculated for in the Mandelbrot view and press
        'J'.  To switch back to Mandelbrot, simply press 'J' again.
    Zoom on point:  Hover mouse cursor over the point of interest and press
        '+' to zoom in or '-' to zoom out. Alternatively, hover over the point
        of interest and scroll the mouse wheel up and down.
    Pan:  To pan, around on the Mandelbrot set, use the arrow keys.  Think of
        this as moving the viewport and not the set itself.  So by pressing the
        down arrow, the set will move upwards in the window since the viewport
        is moving down in world scene coordinates.
    Switching Color palettes:  There are 5 static color sets that we have
        implemented.  To cycle through these, press 'C'.
        To generate a random color set of random numbers, press 'R'
    Animate Colors: To set the colors in animation of random colors, press 'A'
    Switch between parallel and serial mode: To switch between using the CPU
        and the GPU to compute points, press 'V'
    Exiting:  Press 'ESC' to exit the program

Timings:

	To test our times, we set a chrono time object around the for loop that calculates 	all of these points and then we performed
		different functionality things.  Note that all times are approximations and these were determined by a trend that occurred
		in our output statements.  The following is our findings:

		Mandelbrot:
			Upon initialization and first drawing (found by panning slightly up and down):
			Serial: ~.888 seconds 		Parallel: ~.066		Percent Speedup:  1345.450%
			
			Zooming on (0,0) (screen is black):
			Serial: ~3.521				Parallel: ~.1998	Percent Speedup:  1769.346%
	
			Zooming on point that is clearly not in the set:
			Serial: ~.0300				Parallel: ~.0037	Percent Speedup:  810.810%

		Julia:
			Calculating Julia ~(0,0):
			Serial: ~1.44				Parallel: ~.0869	Percent Speedup:  1657.077%

			Calculating Julia ~(-1.75, 0):
			Serial: ~.041				Parallel: .0044		Percent Speedup:  1025%
