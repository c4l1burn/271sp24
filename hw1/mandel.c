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
	//printf("mseq z_n: %lf, mseq c: %lf\n", z_n, c);
	//fflush(stdout);
	double complex r = (z_n * z_n) + c;
	//printf("mseq z_n + 1: %lf\n", r);
	//fflush(stdout);

	return r;
}

// in C we accept a complex value and an integer size and two integer pointers, and populate the integer points with the x and y results
// I've included sample code to zero out x and y.

// take in a complex number and the size of the base, output the coordinates of the complex number on that base array thing.
// "output" means return the pointers after theyve been modified
void c2b(double complex c, int size, int *x, int *y)
{

	*x = (creal(c) + 2) * size / 4;
	*y = (cimag(c) + 2) * size / 4;

	// HEY REMEMBER THAT THOSE USED TO BE DIVIDED BY 2. MAYBE THAT WAS FOR A REASON IDK

	//printf("got to c2b\n");
	return;
}

// in C, we use b2c to loop over all pixels rather than relying on randomization
// return the complex associated with a location x, y
// I've included sample code to work with complex values.
double complex b2c(int size, int x, int y)
{
	double complex r = ((x * 4.0 / size - 2.0) + ((y * 4.0  / size - 2.0) * I));
		// wweeeeeiiiiiirrrd
	//printf("b2c result real component: %lf \n", creal(r));
	//printf("b2c result imaginary component: %lf \n", cimag(r));
	//((x * 4.0 / size - 2.0), (y * 4.0 / size - 2.0))
	//printf("b2c result: \n", r);
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
		//printf("calling mseq from escapes ...\n");
		z_n = m_seq(z_n, c);
		if ((creal(z_n)*creal(z_n)) + (cimag(z_n)*cimag(z_n)) >= 4) // custom thing that avoids a call to cabs. does the same thing though.
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
	//printf("Entering one_val ...\n");
	if (escapes(c, iters) == 1)
	{
		return; // if it doesnt escape, thats the mandelbrot set, thats not what were doing here
	}	// SIDENOTE COME BACK TO THIS TO MAKE A NORMAL MANDELBROT RENDERER BY SWITCHING THIS LATER
	else
	{
		int x, y;

			c2b(c, size, &x, &y);
			base[x][y][0] = base[x][y][0] + 255;
			base[x][y][1] = base[x][y][1] + 255;
			base[x][y][2] = base[x][y][2] + 255;
	}
	return;
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
	// creates the base, stores it in a triple pointer named base
	unsigned char ***base = create_base(size);
	// initializes c
	double complex c;
	// b2c takes size and an x and y coord. set x to i, set y to j
	int i, j;
	int color_picker_value = 0;
	for (i=0; i<size; i++)
	{
		int b2c_x = i;
		for (j=0; j<size; j++)
		{
			int b2c_y = j;
			printf("current x, y: %i %i\n", i, j);
			c = b2c(size, b2c_x, b2c_y);
			one_val(base, size, iters, color_picker_value, c);

		}
	}

	FILE *fp = fopen("mandel.ppm", "wb"); /* b - binary mode */
	fprintf(fp, "P6\n%d %d\n255\n", size, size);
	static unsigned char color[3];

	fflush(stdout);
	for ( int x = 0 ; x < size ; x++ )
	{
		for ( int y = 0 ; y < size ; y++ )
		{
			color[0] = base[x][y][0];  /* red */
			color[1] = base[x][y][1];  /* green */
			color[2] = base[x][y][2];  /* blue */
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
	//make_brot(500,20);

	//make_brot(2000,50);

	//deeply stupid, do not use:
	make_brot(22000, 50);
	return 0;
}
