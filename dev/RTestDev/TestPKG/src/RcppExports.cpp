// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// test_ublas
void test_ublas();
RcppExport SEXP _TestPKG_test_ublas() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    test_ublas();
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_TestPKG_test_ublas", (DL_FUNC) &_TestPKG_test_ublas, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_TestPKG(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}