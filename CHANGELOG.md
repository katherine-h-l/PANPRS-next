# Changes

- Package compilation has been test successfully tested on Linux (Manjaro) and Windows 11.
  - The package fails to compile on Mac OS using Apple M2 Arm chip due to failure to link to fortran compiler. I suspect this is an issue with the clang compiler. To be resolved still.

- TO DO:
  - Have yet to leverage sparse matrices. We already have decreased memory usage just from transitioning to Armadillo and cleaning up some memory allocations. Sparse matrices should be able to further reduce memory usage.
    - What matrices should be treated as sparse?
  - Further reduce the amount of temporary allocations. Try and find a way to elimate the temporary matrices entirely.
  - Implement parallelization using OpenMP
    - What parts of the code should be parallelized?
  - Attempt to convert loops to a branchless style. This should reduce the overhead and increase performance of the for loops even further.

- Ran some memory profiling on the code. The new version of the code uses approximately ~17% less memory already.
  - Modified files: Test.Rmd
  - Output files: Test.html new.html old.html
  - Description: Files show when and how much memory is allocated in each part of the gsfpen function calls.

- Fixed bug in the C++ code that was causing the results to be incorrect. Zmatrix was not being initialized correctly.
  - Modified files: PANPRS.cpp
  - How error was found: Took a subset of the initial summaryZ and funcIndex data. Reduced the number of tuning parameters as well so that the output would be printable / readable. Inserted various print statements through the loops in order to determine where values were different accross the new and old code. 
  - Description: Zmatrix needed to be converted from data frame to a matrix to be passed to C++. My previous implementation was incorrect which has now been fixed. Additionally, there was a bug in the R Internal functions that was causing the lambda vectors to be initialized incorrectly. This has also been fixed.
  - Caveat: The code now matches the previous version of the code in terms of output. Now that all bugs have been fixed though, the new code is now slightly slower (by ~25%) than the previous version. However, we now have everything working with Armadillo and can move to optimization.

- Fixed calculations in new version of the code. Issue was within one of the loops in the C++ code.
  - Modified files: PANPRS.cpp
  - How error was found: Took a subset of the initial summaryZ and funcIndex data. Reduced the number of tuning parameters as well so that the output would be printable / readable. Inserted various print statements through the loops in order to determine where values were different accross the new and old code. 
  - Description: The loop was not iterating over the correct number of values. This has been fixed. The code now matches the previous version of the code in terms of output. 
  - Caveat: Checking for exact equality between new and old does not work due to numerical precision. Checking for approximate equality does work however and the difference is well beyond any meaningful amount. (The ones I checked differend by ~1e-10)

- Fixed return values dimensions not matching between the previous version and current version of the code.
  - Modified files: PANPRS.cpp
  - Description: The return values were being returned from the C++ code and processed by the R cleaning function incorrectly.
  - Caveat: Not all values are being calculated correctly. Roughly 2/3 of the values are incorrect. Still attempting to debug.

- Fixed the return value all_tuning_matrix to match between the previous version and current version of the code.
  - Modified files: PANPRS.cpp
  - Description: The return value all_tuning_matrix was not being set correctly in the C++ code. This has been fixed. Loop index was also not being incremented correctly, which has also been fixed.

- Re-implemented the data cleaning and return values for the R code.
  - Modified files: PANPRS.R
  - Description: Re-added the result cleaning after the C++ code is run. The C++ code now returns a list the beta matrix, the number of iterations took for each set of tuning parameters in a vector, and the tuning parameters in a matrix.
  - Caveat: The C++ code / R code is not behaving correctly and needs to be debugged to have the results match the previous version of the package.

- Changed all data types in the C++ code to use armadillo
  - Modified files: PANPRS.cpp
  - Description: Changed all data types to be base C++ types (like double or int), or to use armadillo for matrices (arma::Mat<double> arma::Mat<int>) and vectors (arma::Col<double> and arma::Col<int>).

- Rewrote all the C++ parameter names and simplified R / C++ interface
  - Modified files: PANPRS.cpp PANPRS.hpp PANPRS.R
  - Description: Moved some initialization of matrices / vectors to C++ to reduce complexity of R function calls. Renamed most variables in C++ code to align with the variable names chosen for the R code. Removed many uneeded global variables in the C++ code.
  - Notes: The C++ code is ~100 lines shorter and more readable now.

- Rewrote major portion of the R code
  - Modified files: PANPRS.R PANPRS.cpp
  - Description: Rewrote and renamed many parameters to be more consistent. Modified how some parameters are stored (lists -> matrices) so that they can be passed to C++ as an Armadillo matrix. Parameters are now reorganized and succesfully get passed to the placeholder C++ function.
  - Caveat: The placeholder C++ function does not do anything yet. It just returns one of the input parameters currently as a test for passing by value or passing by reference.

- Introduced Rcpp and RcppArmadillo
  - Modified files: PANPRS.R PANPRS.cpp PANPRS.hpp NAMEPSACE man
  - Description: Armadillo is linear algebra toolkit for C++. Rcpp is interface between R and C++ code. Created a template package and slowly am transferring in old PANPRS code one bit at a time so that it still compiles. Armadillo has support for sparse matrices (instead of using boost). 
  - Caveat: Armadillo does not let us pass by reference (pass pointers to the C++ code), so function definitions and parameters must all be re-written.

- Renamed files and modified variable names accross all files
  - Modified files: all of them
  - Description: snake case for variables, camel_Case for functions. Makes variable names more readable, consistent, and less confusing / distracting. Also renamed files to be more consistent with the variable names.

- Code documentation [WIP]
  - Modified files: gsfPEN.cpp gsfPEN.R
  - Description: Added comments to the code to make it easier to understand what is going on. A lot of the code is redundant and the interface between R and C code can be greatly simplified, but must proceed with caution to ensure that the code still works.

- Changing from C style arrays (using pointers and malloc) to boost arrays [WIP]
  - Modified files: gsfPEN.cpp
  - Description: Changed from C style arrays to boost arrays. We want to leverage the fact that many of the arrays are sparse which requires, so we can save memory. Proof of concept is in place, and we have successfully switched to CPP, and compiled the package using boost. However, the full transition to boost arrays is still in progress.

- Major refactoring of the C code [WIP]
  - Modified files: gsfPEN.cpp
  - Description: Removed (commented out for now) unecessary initialization loops.

- Implemented OpenMP parallelization proof of concept
  - New files: Makevars
  - Description: Proof of concept demonstrating OpenMP can be used within the C code and work with R. Makevars tells R to link to the openMP library when it compiles the C code.

- Switched to C++
  - Modified files: gsfPEN.c gsfPEN.h utility.c utility.h
  - Description: Functions that must be callable from R code are enclosed in extern "C" { ... } blocks.

- Renamed package to PANPRS from SummaryLasso
  - Modified files: NAMESPACE
