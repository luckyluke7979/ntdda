

#ifndef __STRESS_H__
#define __STRESS_H__


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif



#ifndef __PRINTFUNC__
#define __PRINTFUNC__
typedef int (*PrintFunc)(void * stream, const char * format, ...);
#endif

#ifndef __BOUNDCOND_FUNC__
#define __BOUNCOND_FUNC__
typedef void (*BoundCond)(double * e0, double strain[4]);
#endif


#ifndef __STRAINMODEL_FUNC__
#define __STRAINMODEL_FUNC__
typedef void (*StrainModel)(double * D, double strain[4]);
#endif


#ifndef PLANESTRESS
#define PLANESTRESS 0
#endif
#ifndef PLANESTRAIN
#define PLANESTRAIN 1
#endif


/**
 *
 *
 * @param D deformation variables resulting from an increment
 *  of motion in DDA.
 * 
 * @param e0 material properties and stress vector for blocks.
 *
 * @param k1 stores the index for the ith block deformation 
 *  values in D.
 *
 * @param numblocks is used for looping over e0 and k1.
 *
 * @param planestrainflag = 1 indicates using plane strain 
 *  boundary conditions, plane stress otherwise.
 *
 * @return void.
 */
void     stress_update         (double ** e0, 
                                double ** D, 
                                int * k1, 
                                int numblocks,
                                BoundCond apply_boundary_cond,
                                StrainModel strain_compute);


void     stress_print          (double * s, 
                                PrintFunc printer, 
                                void * stream);


void     stress_print_stresses (double * s, 
                                PrintFunc printer, 
                                void * stream);


double * stress_clone          (const double * s1);

int      stress_equals         (double * d1, 
                                double * d2, 
                                double tol);


void     stress_planestrain    (double * e0,
                                double strains[4]);

void     stress_planestress    (double * e0,
                                double strains[4]);


void     stress_stiffness      (int numblocks, 
                                double ** K, 
                                const int *k1, 
                                double **e0, 
                                double ** moments, 
                                int **n, 
                                int planestrainflag);


void     stress_initial        (int nBlocks, 
                                const int *k1, 
                                double **F, 
                                const double **e0,
                                const double **moments);



/** The strain functions may go into their own module 
 * in the future.  
 */
void     strain_linear_elastic (double * stress, 
                                double strain[4]);


void     strain_green_lagrange (double * stress, 
                                double strain[4]);



/** TCK stress rotation correction, Eq. 17, p. 324,
 * ICADD 1 proceedings.  See also Eqs. 18 and 19 for
 * formulas for updating the deformation rates.
 */
/** @todo Verify that doing the updating here is 
 * mathematically correct.  It might need to be done 
 * before adding to the existing block stresses which
 * are (presumably) already in referential coordinates.
 */
void     stress_rotate      (double * stress, 
                             double r0);



#ifdef __cplusplus
}
#endif


#endif  /* __STRESS_H__ */
