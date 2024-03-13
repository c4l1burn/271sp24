#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
 
// rip from https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
// try "convert x.ppm x.png" and follow the install instructions to get a png

// In C, we make a 3 dimension unsigned char array of size * size * 3
// Hint - how many times should loop? How many times should you call malloc?
//okay so each entry will be a [size, size, o to 3]
//you can treat a mallocced region as an array of characters
unsigned char ***create_base(int size)
{
	int i, j, k;


	unsigned char ***base_x = malloc(sizeof(unsigned char **) * size);
	// this creates an unsinged char pointer which points to a region of memory broken up into char sized chunks which is size big

	for (i=0; i < size; i++)
	{
		base_x[i] = malloc(sizeof(unsigned char *) * size);
		for (j=0; j < size; j++)
		{
			base_x[i][j] = malloc(sizeof(unsigned char) * 3);
			for (k=0; k < 3; k++)
			{
				base_x[i][j][k] = 0;
			}
		}
	}
	//the array should be of unsinged char *s, each of which point to an unsinged char **, each of which


	// THIS MAY BE FUCKED UP AND I MIGHT NEED ANOTHER LAYER?? // it's probably fine
	return base_x;
}

// Calculate z_(n+1) = z_n^2 + c and return the result
	// z = z^2 + c
// in C, we accept two complex values and produce a complex output
// I've included sample code to work with complex values.
// Hint - don't use exponentiation
double complex m_seq(double complex z_n, double complex c)
{
	//double a = 0, b = 0;
	//double complex r = a + b * I;
	double complex r = (z_n * z_n) + c;
	return r;
}

// in C we accept a complex value and an integer size and two integer pointers, and populate the integer points with the x and y results
// I've included sample code to zero out x and y.

// take in a complex number and the size of the base, output the coordinates of the complex number on that base array thing.
// "output" means return the pointers after theyve been modified
void c2b(double complex c, int size, int *x, int *y)
{
	// there was a bunch of rounding in here that meant most pixels couldn't be set
	*x = (int)((creal(c) + 2.0) * (double)size / 4.0);
	*y = (int)((cimag(c) + 2.0) * (double)size / 4.0);
	//printf("got to c2b\n");
	fflush(stdout);
	return;
}

// in C, we use b2c to loop over all pixels rather than relying on randomization
// return the complex associated with a location x, y
// I've included sample code to work with complex values.
double complex b2c(int size, int x, int y)
{

	double complex r = (((double)x * 4.0 / (double)size - 2.0) + (((double)y * 4.0 / (double)size - 2.0) * I));
	return r;
	// does this make sense? Not to me. // you probably should cast more things to doubles
	// does it draw errors? Not yet!



}

// in C we accept a complex value, and integer number of iterations, and returns with an int that represents whether c escapes, or exceeds absolute value 2 in iters applications of m_seq.
// I included the absolute value sample code

// okay this should be easy. just run m_seq  iters times and check if its greater than 2
int escapes(double complex c, int iters)
{	double complex z_n = c;
	int i = 0;
	for (i=0; i < iters ; i++)
	{
		z_n = m_seq(z_n, c);
		if ((creal(c)*creal(c)) + (cimag(c)*cimag(c)) > 4) // custom thing that avoids a call to cabs. does the same thing though. // good
		{
			return 1; // True, value escapes within iters
		}
	}
	return 0; // False, stays bounded
} //were just gonna say one means "yes it escapes" and zero means "we're cool"

// in C, we accept a 3d array base, an integer for size and for iterations, a color channel of 0,1,2, and a complex value c
	/**
# Description:
# Take a value c.
# If it escapes within iters
# Go through the escaping sequence and increment
# the pixel value for each location passed through by the
# sequence for the given color.
 */

void one_val(unsigned char ***base, int size, int iters, int color, double complex c)
{
	// "if it escapes within iters"
	// escapes already calls m_seq, no need to do it here
	//printf("got to one val\n");
	if (escapes(c, iters) == 0)
	{

		return; // if it doesnt escape, thats the mandelbrot set, thats not what were doing here
	}	// SIDENOTE COME BACK TO THIS TO MAKE A NORMAL MANDELBROT RENDERER BY SWITCHING THIS LATER
	else
	{
		//printf("got to else \n");
		// so if it escapes:
		// okay so escapes only tells you if it escapes -- we still have c and can iterate on it ourselves
		// methinks this seems like a lot of wasted work but what do i know

		//okay so "go through the escaping sequence -- meaning m_seq until abs(c>2) or something like that
		// "incrememnt the pixel value) -- THE FINAL ARRAY POINTED TO BY THE Y POINTER FOR THE COLOR GIVEN TO US
		int i = 0;
		int x, y;

		//("got past x y assignment \n");
		for (i=0; i < iters ; i++)
		{
			// the ampersands mean "the pointer to x"
			c2b(c, size, &x, &y);
			// use the ints at *x and *y as indicies in base

			// CURRENT BASTARD ZONE
			// you aren't bounds checking x y. you should do that.
			x = x > size - 1 ? size - 1 : x ;
			y = y > size - 1 ? size - 1 : y ;
			//printf("%i\n", base[x][y][0]);
			//printf("Got to the bastard zone");
			//fflush(stdout);
			base[x][y][0] = 255 ; // changing this just so i can see stuff
		}

	return;
	}
}

// OPTIONAL
// That said, you images will look bad without this.
// The Python sample had a hacky solution.
// We accept a base, and equalize values to percentiles rather than counts
// You equalized images in CS 151 ImageShop.
void equalize(unsigned char ***base, int size)
{
	return;
}
 
// Given an edge size and starting iteration count, make a buddhabrot.
// I'm leaving the ppm code
void make_brot(int size, int iters)
{
	/**
	 * okay so to make a buddhabrot you need to:
	 * 1. Make a base with size size
	 * 2. iterate over every "entry" in that base and get complex numbers from those base entries using b2c
	 * 3. plug that complex number into one_val
	 * 		PROBLEM: No color val given. multiple solutions; you could assign them randomly, or in sequence, or based on how fast it escapes, or whatever
	 * 4. once you get to the end of the base, take the base and do some wizardry to make it a ppm
	 * 5. then do some more wizardry to make it a png.
	 *
	 *  easy!
	 *
	*/
	// creates the base, stores it in a triple pointer named base
	unsigned char ***base = create_base(size);
	printf("%p\n", base);

	// TODO: number 2 in the above list
	// b2c takes size and an x and y coord. set x to i, set y to j
	int i, j;
	for (i=0; i<size; i++)
	{
		int b2c_x = i;
		for (j=0; j<size; j++)
		{
			int b2c_y = j;
			// gets the value c at x y
			double complex c = b2c(size, b2c_x, b2c_y);
			//printf("current complex:");
			//printf("%lf\n", c); // trying to print c as we go through it
			// we're just gonna set color to 2 for the moment to make it blue
			one_val(base, size, iters, 2, c);
		}
	}

	FILE *fp = fopen("brot.ppm", "wb"); /* b - binary mode */
	printf("%p\n", base);

	fprintf(fp, "P6\n%d %d\n255\n", size, size);
	for ( int x = 0 ; x < size ; x++ )
	{
		for ( int y = 0 ; y < size ; y++ )
		{
			// ah - it would be good to not just use zeros lol
			fprintf(stderr,"x: %d, y: %d, base[i][j][0]: %d\n", x, y, base[x][y][0]);
			fwrite(base[x][y], 1, 3, fp);
		}
	}
	fclose(fp);
	return;
}

// core learning obj of buddhabrot: get you to maintain an array representing the complex plane

 
int main()
{
	// a bunch of test code i dont quite wanna throw out yet:

	//create_base(20);
	//double complex sample_complex = 0.5 + 1.9 * I;
	//int test_escape = escapes(sample_complex, 2);
	//printf("%i/n", test_escape);

	//test brot:
	make_brot(100,10);

	//make_brot(4000,50);
	return 0;
}
