
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "munkres.h"
#include "adapters/boostmatrixadapter.h"

int
main(int argc, char *argv[]) {
	int nrows = 101;
	int ncols = 101;

	if ( argc == 3 ) {
		nrows = atoi(argv[1]);
		ncols = atoi(argv[2]);
	}

	Matrix<double> matrix(nrows, ncols);

	srandom(time(nullptr)); // Seed random number generator.

	// Initialize matrix with random values.
	for ( int row = 0 ; row < nrows ; row++ ) {
		for ( int col = 0 ; col < ncols ; col++ ) {
			matrix(row,col) = (double)random();
		}
	}

	// Display begin matrix state.
	for ( int row = 0 ; row < nrows ; row++ ) {
		for ( int col = 0 ; col < ncols ; col++ ) {
			std::cout.width(2);
			std::cout << matrix(row,col) << ",";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Apply Munkres algorithm to matrix.
	Munkres<double> m;
	m.solve(matrix);

	// Display solved matrix.
	for ( int row = 0 ; row < nrows ; row++ ) {
		for ( int col = 0 ; col < ncols ; col++ ) {
			std::cout.width(2);
			std::cout << matrix(row,col) << ",";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;


	for ( int row = 0 ; row < nrows ; row++ ) {
		int rowcount = 0;
		for ( int col = 0 ; col < ncols ; col++  ) {
			if ( matrix(row,col) == 0 )
				rowcount++;
		}
		if ( rowcount != 1 )
			std::cerr << "Row " << row << " has " << rowcount << " columns that have been matched." << std::endl;
	}

	for ( int col = 0 ; col < ncols ; col++ ) {
		int colcount = 0;
		for ( int row = 0 ; row < nrows ; row++ ) {
			if ( matrix(row,col) == 0 )
				colcount++;
		}
		if ( colcount != 1 )
			std::cerr << "Column " << col << " has " << colcount << " rows that have been matched." << std::endl;
	}

	return 0;
}
