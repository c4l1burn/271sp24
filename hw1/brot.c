#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
 
// rip from https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
// try "convert x.ppm x.png" and follow the install instructions to get a png

// In C, we make a 3 dimension unsigned char array of size * size * 3
// Hint - how many times should loop? How many times should you call malloc?

//okay so each entry will be a [size, size, o to 3]

//you can treat a mallocced region as an array of characters

// square thre real and imag components then compare to


unsigned char ***create_base(int size)
{
	int i, j, k;
	// go through, make the first array of length size and type unsigned char
	// go through, make the n element of the first array its own array of size size


	unsigned char ***base_x = malloc(sizeof(unsigned char **) * size);
	// this creates an unsinged char pointer which points to a region of memory broken up into char sized chunks which is size big

	for (i=0; i < size; i++)
	{
		unsigned char **base_y = malloc(sizeof(unsigned char *) * size);
		for (j=0; j < size; j++)
		{
			unsigned char *base_color = malloc(sizeof(unsigned char) * 3);
		}
	}
	//the array should be of unsinged char *s, each of which point to an unsinged char **, each of which


	// THIS MAY BE FUCKED UP AND I MIGHT NEED ANOTHER LAYER??
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
	printf("got to c2b\n");
	fflush(stdout);
	*x = 1;
	//y = 0;

	printf("xptr: %p\n",x);
	fflush(stdout);
		/**

	// i think it takes size as a way of taking height and width bcs the image is always a square
	// but i also think the whole base is supposed to be from -2 to 2 in both real and imaginary dimensions, no matter the size of the base
	printf("got to c2b pre math\n");

	//okay its segfaulting here EXACTLY. why.

	printf("creal: %lf\n", creal(c));
	printf("cimag: %lf\n", cimag(c));
	//printf("creal plus two times size over two: %i\n", (int)(cimag(c) + 2) * size / 2);


	//*x = (int)(creal(c) + 2) * size / 2;
	*x = 1;
	// it seems like its having trouble populating the pointer with that value

	printf("got past x pointer");
	fflush(stdout);
	*y = (int)(cimag(c) + 4) * size / 2;
	printf("got to c2b post math\n");

	// the above was adapted from the following code, found here: https://github.com/mcfunley/buddhabrot/blob/master/buddhabrot.c
	// I dropped the int cast because im not sure what it was doing, but maybe ill have to add it back in, idk

   // *x = (int)((creal(z) + 2) * b->width / 3);
   // *y = (int)((cimag(z) + 1) * b->height / 2);



	*/
	return;
}

// in C, we use b2c to loop over all pixels rather than relying on randomization
// return the complex associated with a location x, y
// I've included sample code to work with complex values.
double complex b2c(int size, int x, int y)
{

	// okay so x and y ought to give you indicies (after some massaging to make sure they fit the base probably?)
	// like, .5 + .5i


	//double a = 0, b = 0;
	double complex r = ((x * 4 / size - 2) + ((y * 4 / size - 2) * I));
	return r;
	// does this make sense? Not to me.
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
		if ((creal(c)*creal(c)) + (cimag(c)*cimag(c)) > 4) // custom thing that avoids a call to cabs. does the same thing though.
		{
			return 1; // True, value escapes within iters
		}
	}
	return 0; // False, stays bounded
} //were just gonna say one means "yes it escapes" and zero means "we're cool"

// in C, we accept a 3d array base, an integer for size and for iterations, a color channel of 0,1,2, and a complex value c

	/**
	nothing is returned but the base itself might get fucked with. somehow.
	i think this descriptiuon should still be good:
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

	printf("got to oneval\n");
	if (escapes(c, iters) == 0)
	{
		printf("got to oneval if\n");

		return; // if it doesnt escape, thats the mandelbrot set, thats not what were doing here
	}	// SIDENOTE COME BACK TO THIS TO MAKE A NORMAL MANDELBROT RENDERER BY SWITCHING THIS LATER
	else
	{
		printf("got to oneval else\n");
		// so if it escapes:
		// okay so escapes only tells you if it escapes -- we still have c and can iterate on it ourselves
		// methinks this seems like a lot of wasted work but what do i know

		//okay so "go through the escaping sequence -- meaning m_seq until abs(c>2) or something like that
		// "incrememnt the pixel value) -- THE FINAL ARRAY POINTED TO BY THE Y POINTER FOR THE COLOR GIVEN TO US
		// okay so im literally just gonna steal the escapes code and add some stuff on to it
		int i = 0;
		int* x = 0;
		int* y = 0;
		// make pointers for x and y and stick zeroes in there

		for (i=0; i < iters ; i++)
		{

			c2b(c, size, x, y); // this populates those pointers we just made up with coordinate data

			// use the ints at *x and *y as indicies in base
			printf("got past c2b call in oneval");
			base[*x][*y][color] = base[*x][*y][color + 1];
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
			printf("current complex:");
			printf("%lf\n", c); // trying to print c as we go through it
			// we're just gonna set color to 2 for the moment to make it blue
			one_val(base, size, iters, 2, c);
		}
	}

	FILE *fp = fopen("brot.ppm", "wb"); /* b - binary mode */
	fprintf(fp, "P6\n%d %d\n255\n", size, size);
	static unsigned char color[3];

	fflush(stdout);
	for ( int x = 0 ; x < size ; x++ )
	{
		for ( int y = 0 ; y < size ; y++ )
		{
			color[0] = 0;  /* red */
			color[1] = 0;  /* green */
			color[2] = 0;  /* blue */
			fwrite(color, 1, 3, fp);
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
	make_brot(2000,20);

	//make_brot(4000,50);
	return 0;
}
