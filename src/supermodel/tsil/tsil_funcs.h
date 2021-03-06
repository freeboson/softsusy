/* Prototypes for functions not in the user API */

#ifndef TSIL_FUNCS_H
#define TSIL_FUNCS_H

#include "tsil.h"

/* Setup and initialization functions */
void TSIL_Construct             (TSIL_DATA *);
void TSIL_InitialValue          (TSIL_DATA *, TSIL_COMPLEX);
void TSIL_InitialValueThreshAt0 (TSIL_DATA *, TSIL_COMPLEX);

/* High-level evaluation functions */
int  TSIL_CaseSpecial (TSIL_DATA *);
void TSIL_CaseGeneric (TSIL_DATA *);

/* Miscellaneous functions */
TSIL_REAL    TSIL_MaxAbs    (TSIL_REAL *, int);
TSIL_REAL    TSIL_MinAbs    (TSIL_REAL *, int);
TSIL_COMPLEX TSIL_AddIeps   (TSIL_COMPLEX);
TSIL_COMPLEX TSIL_EtaBranch (TSIL_COMPLEX, TSIL_COMPLEX);
TSIL_REAL    TSIL_Alpha     (TSIL_REAL, TSIL_REAL); 
TSIL_COMPLEX TSIL_Delta     (TSIL_COMPLEX, TSIL_COMPLEX, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_I20xy     (TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_I200x     (TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_xI2p2     (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_Dilog     (TSIL_COMPLEX);
TSIL_COMPLEX TSIL_Trilog    (TSIL_COMPLEX);
TSIL_COMPLEX TSIL_fPT       (TSIL_REAL, TSIL_REAL);
void         TSIL_Rescale   (TSIL_DATA *);
void         TSIL_Unscale   (TSIL_DATA *);
void         TSIL_ScaleData (TSIL_DATA *, TSIL_REAL);
int          TSIL_NearThreshold (TSIL_DATA *, TSIL_REAL *, TSIL_REAL);
TSIL_REAL    TSIL_Th2       (TSIL_REAL, TSIL_REAL);
TSIL_REAL    TSIL_Ps2       (TSIL_REAL, TSIL_REAL);
void         TSIL_SwapR     (TSIL_REAL *, TSIL_REAL *);
void         TSIL_SwapC     (TSIL_COMPLEX *, TSIL_COMPLEX *);
void         TSIL_PermuteResults  (TSIL_DATA *, int p);
void         TSIL_CheckConsistent (TSIL_COMPLEX, TSIL_COMPLEX);

int TSIL_ValidIdentifier (const char *);

/* Analytic special cases */
TSIL_COMPLEX TSIL_B0x  (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_B00  (TSIL_COMPLEX, TSIL_REAL);

TSIL_COMPLEX TSIL_S0xy    (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_S00x    (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_S000    (TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_SxyyAtx (TSIL_REAL, TSIL_REAL, TSIL_REAL);

TSIL_COMPLEX TSIL_Tx0y      (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Tx00      (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_TxyyAtx   (TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_TyyxAtx   (TSIL_REAL, TSIL_REAL, TSIL_REAL);

TSIL_COMPLEX TSIL_Tbar0xy      (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Tbar00x      (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Tbar000      (TSIL_COMPLEX, TSIL_REAL);

void         TSIL_CorrectUs (TSIL_DATA *foo);
TSIL_COMPLEX TSIL_U0000     (TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Ux000     (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_U0x00     (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_U000x     (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Uxy0y     (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_U0x0y     (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_U00xx     (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_U00xy     (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_U0xyz     (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Uxy00     (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Uxx00     (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_U0x0y     (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Ux00y     (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_Ux0yyAtx  (TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_Uy0yxAtx  (TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_Ux0yzAtx  (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_COMPLEX **tptr, TSIL_REAL);

TSIL_COMPLEX TSIL_Vxy0y     (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_V0xyz     (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_V0x0y     (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_V0x0x     (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);
TSIL_COMPLEX TSIL_V0x00     (TSIL_REAL, TSIL_COMPLEX, TSIL_REAL);

TSIL_COMPLEX TSIL_Mxxyy0    (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M00xx0    (TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M00xy0    (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M000x0    (TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M0000x    (TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M0x0xx    (TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M00000    (TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M0x0y0    (TSIL_REAL, TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M0xx00    (TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M0xxx0    (TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M0x0x0    (TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M000xx    (TSIL_REAL, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_M0xx0xAtx (TSIL_REAL);
TSIL_COMPLEX TSIL_M0yy0xAtx (TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_M0xy0yAtx (TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_S12FKV    (TSIL_COMPLEX);

/* For setting auxiliary values after other functions are known: */
void TSIL_SetV    (TSIL_DATA *);
void TSIL_SetTbar (TSIL_DATA *);
void TSIL_SetBold (TSIL_DATA *);

/* The Runge-Kutta routines */
int  TSIL_rk6 (TSIL_DATA *, TSIL_COMPLEX *, TSIL_COMPLEX *, TSIL_REAL, int, TSIL_REAL, int);
void TSIL_rk5 (TSIL_DATA *, TSIL_COMPLEX *, TSIL_COMPLEX, TSIL_REAL, int);
int  TSIL_rk6_STU (TSIL_DATA *, TSIL_COMPLEX *, TSIL_COMPLEX *, TSIL_REAL, int, TSIL_REAL, int);
void TSIL_rk5_STU (TSIL_DATA *, TSIL_COMPLEX *, TSIL_COMPLEX, TSIL_REAL, int);
int  TSIL_rk6_ST (TSIL_DATA *, TSIL_COMPLEX *, TSIL_COMPLEX *, TSIL_REAL, int, TSIL_REAL, int);
void TSIL_rk5_ST (TSIL_DATA *, TSIL_COMPLEX *, TSIL_COMPLEX, TSIL_REAL, int);
int  TSIL_Integrate (TSIL_DATA *, TSIL_COMPLEX, TSIL_COMPLEX, int, int, TSIL_REAL);

/* "Constructors", series expansions, and derivatives of basis functions: */
void         TSIL_ConstructB   (TSIL_BTYPE *, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_dBds_rk         (TSIL_BTYPE, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_BAtZero      (TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_BprimeAtZero (TSIL_REAL, TSIL_REAL, TSIL_REAL);

void         TSIL_ConstructS   (TSIL_STYPE *, int, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_dSds         (TSIL_STYPE, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_SAtZero      (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_SprimeAtZero (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);

void         TSIL_ConstructT   (TSIL_TTYPE *, int, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_dTds         (TSIL_TTYPE, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_TAtZero      (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_TprimeAtZero (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);

void         TSIL_ConstructU     (TSIL_UTYPE *, int, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_dUds           (TSIL_UTYPE, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_UAtZero        (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_UprimeAtZero   (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);

void         TSIL_ConstructV    (TSIL_VTYPE *, int, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);

int          TSIL_ConstructM    (TSIL_MTYPE *, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_dsMds         (TSIL_MTYPE, TSIL_COMPLEX);
TSIL_COMPLEX TSIL_sMAtZero      (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);
TSIL_COMPLEX TSIL_sMprimeAtZero (TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL, TSIL_REAL);

/* Output and status functions */
int  TSIL_UnnaturalCase (TSIL_DATA *);
void TSIL_cfprintf      (FILE *, double complex);
void TSIL_cfprintfM     (FILE *, double complex);

/* Diagnostics -- no longer used */
/* void PrintDerivs (TSIL_DATA *); */
/* void PrintCoeffs (TSIL_DATA *); */

#endif /* TSIL_FUNCS_H */
