
//
//  rlib.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include <mach/mach_time.h>
#include "rng.h"
#include <Rdefines.h>
#include <stdio.h>
#include <R.h>

#include "macro.h"
#include "eventQ.h"
#include "population.h"

using namespace std;

Rng * theRng;
eventQ * theQ;

/* Output Pointers */
extern double * theCARE;
extern double * theCARE_PT;
extern double * theDALY;
extern double * theCOST;
extern double * thePOP_15to49;
extern double * theHIV_15to49;
extern double * theART_15to49;
extern double * thePOP_15plus;
extern double * theAidsDeath_15plus;
extern double * thePOP_AgeSex_2007;
extern double * theHIV_AgeSex_2007;
extern double * thePOP_NoArtCd4_2007;
extern double * thePOP_AgeSex_2012;
extern double * theHIV_AgeSex_2012;
extern double * thePOP_AgeSex_2014;
extern double * theHIV_AgeSex_2014;
extern double * theCD4_200;
extern double * theCD4_200350;
extern double * theCD4_350500;
extern double * theCD4_500;
extern double * theCD4_200_Art;
extern double * theCD4_200350_Art;
extern double * theCD4_350500_Art;
extern double * theCD4_500_Art;
extern double * theWHO_1;
extern double * theWHO_2;
extern double * theWHO_3;
extern double * theWHO_4;
extern double * theWHO_1_Art;
extern double * theWHO_2_Art;
extern double * theWHO_3_Art;
extern double * theWHO_4_Art;
extern double * theINCIDENCE;
extern double * thePreArtCOST;
extern double * theArtCOST;
extern double * thePreArtCOST_Hiv;
extern double * theArtCOST_Hiv;
extern double * theCLINIC;
extern double * theDeath;
extern double * theAidsDeath;
extern double * theDeath_2010_Age;
extern double * theAidsDeath_2010_Age;
extern double * theDALY_OffArt;
extern double * theDALY_OnArt;
extern double * theDALY_LYL;

/* COST UNITS (not Unit Costs) */
extern double * theUNIT_HctVisitCost;
extern double * theUNIT_RapidHivTestCost;
extern double * theUNIT_LinkageCost;
extern double * theUNIT_ImpCareCost;
extern double * theUNIT_PreArtClinicVisitCost;
extern double * theUNIT_LabCd4TestCost;
extern double * theUNIT_PocCd4TestCost;
extern double * theUNIT_AnnualArtCost;
extern double * theUNIT_AnnualAdherenceCost;
extern double * theUNIT_OutreachCost;

/* UNIT COSTS */
extern double * theUnitCost_HctVisitCost;
extern double * theUnitCost_RapidHivTestCost;
extern double * theUnitCost_LinkageCost;
extern double * theUnitCost_ImpCareCost;
extern double * theUnitCost_PreArtClinicVisitCost;
extern double * theUnitCost_LabCd4TestCost;
extern double * theUnitCost_PocCd4TestCost;
extern double * theUnitCost_AnnualArtCost;
extern double * theUnitCost_AnnualAdherenceCost;
extern double * theUnitCost_OutreachCost;

/* Calibration pointers */
extern double * C1;
extern double * L21;
extern double * R3;
extern double * R8;
extern double * ART1;
extern double * ART4;
extern double * ART5;
extern double * ART6;
extern double * ART9;
extern double * ART10;
extern double * ART11;
extern double * ART12;
extern double * ART13;
extern double * ART14;
extern double * Pre2010;
extern unsigned int * In2014;
extern unsigned int * HivArray;
extern unsigned int * DiagArray;
extern unsigned int * ArtArray;
extern unsigned int * R3_Counter;
extern unsigned int * R8_Counter;
extern unsigned int * ART6_Counter;
extern unsigned int * ART10_Counter;
extern unsigned int * ART12_Counter;
extern unsigned int * Pie_1;
extern unsigned int * Pie_2;
extern unsigned int * Pie_3;

/* Intervention Pointers */
int const * p_Hbct;
int const * p_Vct;
int const * p_HbctPocCd4;
int const * p_Linkage;
int const * p_PreOutreach;
int const * p_ImprovedCare;
int const * p_PocCd4;
int const * p_VctPocCd4;
int const * p_ArtOutreach;
int const * p_Adherence;
int const * p_ImmediateArt;
int const * p_UniversalTestAndTreat;
int const * p_Calibration;

/* Guidelines Pointers */
extern int * theGuidelines_PopDist_HivNegative;
extern int * theGuidelines_PopDist_500_NeverDiag;
extern int * theGuidelines_PopDist_500_DiagNotInCareNeverCare;
extern int * theGuidelines_PopDist_500_DiagNotInCareEverCare;
extern int * theGuidelines_PopDist_500_InCareNeverArt;
extern int * theGuidelines_PopDist_500_ArtLessSixMonths;
extern int * theGuidelines_PopDist_500_ArtMoreSixMonths;
extern int * theGuidelines_PopDist_500_OffArt;
extern int * theGuidelines_PopDist_350500_NeverDiag;
extern int * theGuidelines_PopDist_350500_DiagNotInCareNeverCare;
extern int * theGuidelines_PopDist_350500_DiagNotInCareEverCare;
extern int * theGuidelines_PopDist_350500_InCareNeverArt;
extern int * theGuidelines_PopDist_350500_ArtLessSixMonths;
extern int * theGuidelines_PopDist_350500_ArtMoreSixMonths;
extern int * theGuidelines_PopDist_350500_OffArt;
extern int * theGuidelines_PopDist_200350_NeverDiag;
extern int * theGuidelines_PopDist_200350_DiagNotInCareNeverCare;
extern int * theGuidelines_PopDist_200350_DiagNotInCareEverCare;
extern int * theGuidelines_PopDist_200350_InCareNeverArt;
extern int * theGuidelines_PopDist_200350_ArtLessSixMonths;
extern int * theGuidelines_PopDist_200350_ArtMoreSixMonths;
extern int * theGuidelines_PopDist_200350_OffArt;
extern int * theGuidelines_PopDist_200_NeverDiag;
extern int * theGuidelines_PopDist_200_DiagNotInCareNeverCare;
extern int * theGuidelines_PopDist_200_DiagNotInCareEverCare;
extern int * theGuidelines_PopDist_200_InCareNeverArt;
extern int * theGuidelines_PopDist_200_ArtLessSixMonths;
extern int * theGuidelines_PopDist_200_ArtMoreSixMonths;
extern int * theGuidelines_PopDist_200_OffArt;

extern int * theGuidelines_Death_HivNegative;
extern int * theGuidelines_Death_500_NeverDiag;
extern int * theGuidelines_Death_500_DiagNotInCareNeverCare;
extern int * theGuidelines_Death_500_DiagNotInCareEverCare;
extern int * theGuidelines_Death_500_InCareNeverArt;
extern int * theGuidelines_Death_500_ArtLessSixMonths;
extern int * theGuidelines_Death_500_ArtMoreSixMonths;
extern int * theGuidelines_Death_500_OffArt;
extern int * theGuidelines_Death_350500_NeverDiag;
extern int * theGuidelines_Death_350500_DiagNotInCareNeverCare;
extern int * theGuidelines_Death_350500_DiagNotInCareEverCare;
extern int * theGuidelines_Death_350500_InCareNeverArt;
extern int * theGuidelines_Death_350500_ArtLessSixMonths;
extern int * theGuidelines_Death_350500_ArtMoreSixMonths;
extern int * theGuidelines_Death_350500_OffArt;
extern int * theGuidelines_Death_200350_NeverDiag;
extern int * theGuidelines_Death_200350_DiagNotInCareNeverCare;
extern int * theGuidelines_Death_200350_DiagNotInCareEverCare;
extern int * theGuidelines_Death_200350_InCareNeverArt;
extern int * theGuidelines_Death_200350_ArtLessSixMonths;
extern int * theGuidelines_Death_200350_ArtMoreSixMonths;
extern int * theGuidelines_Death_200350_OffArt;
extern int * theGuidelines_Death_200_NeverDiag;
extern int * theGuidelines_Death_200_DiagNotInCareNeverCare;
extern int * theGuidelines_Death_200_DiagNotInCareEverCare;
extern int * theGuidelines_Death_200_InCareNeverArt;
extern int * theGuidelines_Death_200_ArtLessSixMonths;
extern int * theGuidelines_Death_200_ArtMoreSixMonths;
extern int * theGuidelines_Death_200_OffArt;

extern int * theGuidelines_Art_500;
extern int * theGuidelines_Art_350500;
extern int * theGuidelines_Art_200350;
extern int * theGuidelines_Art_200;

extern int * theGuidelines_NewInfectionsAdult;
extern int * theGuidelines_NewDiagnoses;
extern int * theGuidelines_PreArtDropout;
extern int * theGuidelines_ArtDropout;

extern int * mid2010;
extern double * thePOP;

extern "C" {

/////////////////////

SEXP CallCascade(SEXP s_pop,
				 SEXP s_Hbct,
				 SEXP s_Vct,
				 SEXP s_HbctPocCd4,
				 SEXP s_Linkage,
				 SEXP s_VctPocCd4,
				 SEXP s_PreOutreach,
				 SEXP s_ImprovedCare,
				 SEXP s_PocCd4,
				 SEXP s_ArtOutreach,
				 SEXP s_Adherence,
				 SEXP s_ImmediateArt,
				 SEXP s_UniversalTestAndTreat,
				 SEXP s_Calibration) {

	PROTECT(s_pop = coerceVector(s_pop, REALSXP));
	PROTECT(s_Hbct = coerceVector(s_Hbct, INTSXP));
	PROTECT(s_Vct = coerceVector(s_Vct, INTSXP));
	PROTECT(s_HbctPocCd4 = coerceVector(s_HbctPocCd4, INTSXP));
	PROTECT(s_Linkage = coerceVector(s_Linkage, INTSXP));
	PROTECT(s_VctPocCd4 = coerceVector(s_VctPocCd4, INTSXP));
	PROTECT(s_PreOutreach = coerceVector(s_PreOutreach, INTSXP));
	PROTECT(s_ImprovedCare = coerceVector(s_ImprovedCare, INTSXP));
	PROTECT(s_PocCd4 = coerceVector(s_PocCd4, INTSXP));
	PROTECT(s_ArtOutreach = coerceVector(s_ArtOutreach, INTSXP));
	PROTECT(s_Adherence = coerceVector(s_Adherence, INTSXP));
	PROTECT(s_ImmediateArt = coerceVector(s_ImmediateArt, INTSXP));
	PROTECT(s_UniversalTestAndTreat = coerceVector(s_UniversalTestAndTreat, INTSXP));
	PROTECT(s_Calibration = coerceVector(s_Calibration, INTSXP));

	/* Assigning Pointers */
	p_Hbct = INTEGER(s_Hbct);
	p_Vct = INTEGER(s_Vct);
	p_HbctPocCd4 = INTEGER(s_HbctPocCd4);
	p_Linkage = INTEGER(s_Linkage);
	p_VctPocCd4 = INTEGER(s_VctPocCd4);
	p_PreOutreach = INTEGER(s_PreOutreach);
	p_ImprovedCare = INTEGER(s_ImprovedCare);
	p_PocCd4 = INTEGER(s_PocCd4);
	p_ArtOutreach = INTEGER(s_ArtOutreach);
	p_Adherence = INTEGER(s_Adherence);
	p_ImmediateArt = INTEGER(s_ImmediateArt);
	p_UniversalTestAndTreat = INTEGER(s_UniversalTestAndTreat);
	p_Calibration = INTEGER(s_Calibration);

	/* THE MODEL */
	cout << "Hello, Jack - the model is running..." << endl;
	cout << "Caution: WP19 version. Runs until 2035." << endl;
	theRng = new Rng(mach_absolute_time());
	theQ = new eventQ(0,(60 * 365.25) + 1);
	population * thePop = new population(*REAL(s_pop));
	theQ->RunEvents();
	delete theQ;
	delete thePop;
	delete theRng;

	/* OUTPUTS */
	SEXP sOUT, sCARE, sCARE_PT, sDALY, sCOST, sPOP_15to49, sHIV_15to49, sART_15to49, sPOP_15plus, sAidsDeath_15plus,
	sPOP_AgeSex_2007, sHIV_AgeSex_2007, sPOP_NoArtCd4_2007, sPOP_AgeSex_2012, sHIV_AgeSex_2012, sPOP_AgeSex_2014,
	sHIV_AgeSex_2014, sCD4_200, sCD4_200350, sCD4_350500, sCD4_500, sCD4_200_Art, sCD4_200350_Art, sCD4_350500_Art,
	sCD4_500_Art, sWHO_1, sWHO_2, sWHO_3, sWHO_4, sWHO_1_Art, sWHO_2_Art, sWHO_3_Art, sWHO_4_Art, sINCIDENCE, sPreArtCOST,
	sArtCOST, sPreArtCOST_Hiv, sArtCOST_Hiv, sC1, sL21, sR3, sR8, sART1, sART4, sART5, sART6, sART9, sART10, sART11, sART12,
	sART13, sART14, sPre2010, sIn2014, sHivArray, sDiagArray, sArtArray, sR3_Counter, sR8_Counter, sART6_Counter, sART10_Counter, sART12_Counter, sPie_1, sPie_2, sPie_3,
	sCLINIC, sDeath, sAidsDeath, sDeath_2010_Age, sAidsDeath_2010_Age, sDALY_OffArt, sDALY_OnArt, sDALY_LYL, sOUTNAMES;

	/* Guidelines SEXPs */
	SEXP sGuidelines_PopDist_HivNegative, sGuidelines_PopDist_500_NeverDiag,
	sGuidelines_PopDist_500_DiagNotInCareNeverCare, sGuidelines_PopDist_500_DiagNotInCareEverCare,
	sGuidelines_PopDist_500_InCareNeverArt, sGuidelines_PopDist_500_ArtLessSixMonths, sGuidelines_PopDist_500_ArtMoreSixMonths,
	sGuidelines_PopDist_500_OffArt, sGuidelines_PopDist_350500_NeverDiag, sGuidelines_PopDist_350500_DiagNotInCareNeverCare, sGuidelines_PopDist_350500_DiagNotInCareEverCare,
	sGuidelines_PopDist_350500_InCareNeverArt, sGuidelines_PopDist_350500_ArtLessSixMonths, sGuidelines_PopDist_350500_ArtMoreSixMonths, sGuidelines_PopDist_350500_OffArt, sGuidelines_PopDist_200350_NeverDiag,
	sGuidelines_PopDist_200350_DiagNotInCareNeverCare, sGuidelines_PopDist_200350_DiagNotInCareEverCare, sGuidelines_PopDist_200350_InCareNeverArt, sGuidelines_PopDist_200350_ArtLessSixMonths, sGuidelines_PopDist_200350_ArtMoreSixMonths,
	sGuidelines_PopDist_200350_OffArt, sGuidelines_PopDist_200_NeverDiag, sGuidelines_PopDist_200_DiagNotInCareNeverCare, sGuidelines_PopDist_200_DiagNotInCareEverCare, sGuidelines_PopDist_200_InCareNeverArt, sGuidelines_PopDist_200_ArtLessSixMonths,
	sGuidelines_PopDist_200_ArtMoreSixMonths, sGuidelines_PopDist_200_OffArt, sGuidelines_Death_HivNegative, sGuidelines_Death_500_NeverDiag, sGuidelines_Death_500_DiagNotInCareNeverCare, sGuidelines_Death_500_DiagNotInCareEverCare, sGuidelines_Death_500_InCareNeverArt,
	sGuidelines_Death_500_ArtLessSixMonths, sGuidelines_Death_500_ArtMoreSixMonths, sGuidelines_Death_500_OffArt, sGuidelines_Death_350500_NeverDiag, sGuidelines_Death_350500_DiagNotInCareNeverCare, sGuidelines_Death_350500_DiagNotInCareEverCare, sGuidelines_Death_350500_InCareNeverArt,
	sGuidelines_Death_350500_ArtLessSixMonths, sGuidelines_Death_350500_ArtMoreSixMonths, sGuidelines_Death_350500_OffArt, sGuidelines_Death_200350_NeverDiag, sGuidelines_Death_200350_DiagNotInCareNeverCare, sGuidelines_Death_200350_DiagNotInCareEverCare, sGuidelines_Death_200350_InCareNeverArt,
	sGuidelines_Death_200350_ArtLessSixMonths, sGuidelines_Death_200350_ArtMoreSixMonths, sGuidelines_Death_200350_OffArt, sGuidelines_Death_200_NeverDiag, sGuidelines_Death_200_DiagNotInCareNeverCare, sGuidelines_Death_200_DiagNotInCareEverCare, sGuidelines_Death_200_InCareNeverArt, sGuidelines_Death_200_ArtLessSixMonths,
	sGuidelines_Death_200_ArtMoreSixMonths, sGuidelines_Death_200_OffArt, sGuidelines_Art_500, sGuidelines_Art_350500, sGuidelines_Art_200350, sGuidelines_Art_200, sGuidelines_NewInfectionsAdult, sGuidelines_NewDiagnoses, sGuidelines_PreArtDropout, sGuidelines_ArtDropout;

	/* Cost Units */
	SEXP sUNIT_HctVisitCost;
	SEXP sUNIT_RapidHivTestCost;
	SEXP sUNIT_LinkageCost;
	SEXP sUNIT_ImpCareCost;
	SEXP sUNIT_PreArtClinicVisitCost;
	SEXP sUNIT_LabCd4TestCost;
	SEXP sUNIT_PocCd4TestCost;
	SEXP sUNIT_AnnualArtCost;
	SEXP sUNIT_AnnualAdherenceCost;
	SEXP sUNIT_OutreachCost;

	/* Unit Costs */
	SEXP sUnitCost_HctVisitCost;
	SEXP sUnitCost_RapidHivTestCost;
	SEXP sUnitCost_LinkageCost;
	SEXP sUnitCost_ImpCareCost;
	SEXP sUnitCost_PreArtClinicVisitCost;
	SEXP sUnitCost_LabCd4TestCost;
	SEXP sUnitCost_PocCd4TestCost;
	SEXP sUnitCost_AnnualArtCost;
	SEXP sUnitCost_AnnualAdherenceCost;
	SEXP sUnitCost_OutreachCost;

	SEXP sMid2010;
	SEXP sPOP;

	PROTECT(sCARE = allocVector(REALSXP,6));
	PROTECT(sCARE_PT = allocVector(REALSXP,6));
	PROTECT(sDALY = allocVector(REALSXP,20));
	PROTECT(sCOST = allocVector(REALSXP,20));
	PROTECT(sPOP_15to49 = allocVector(REALSXP,66));
	PROTECT(sHIV_15to49 = allocVector(REALSXP,66));
	PROTECT(sART_15to49 = allocVector(REALSXP,66));
	PROTECT(sPOP_15plus = allocVector(REALSXP,66));
	PROTECT(sAidsDeath_15plus = allocVector(REALSXP,66));
	PROTECT(sPOP_AgeSex_2007 = allocVector(REALSXP,20));
	PROTECT(sHIV_AgeSex_2007 = allocVector(REALSXP,20));
	PROTECT(sPOP_NoArtCd4_2007 = allocVector(REALSXP,4));
	PROTECT(sPOP_AgeSex_2012 = allocVector(REALSXP,16));
	PROTECT(sHIV_AgeSex_2012 = allocVector(REALSXP,16));
	PROTECT(sPOP_AgeSex_2014 = allocVector(REALSXP,10));
	PROTECT(sHIV_AgeSex_2014 = allocVector(REALSXP,10));
	PROTECT(sCD4_200 = allocVector(REALSXP,66));
	PROTECT(sCD4_200350 = allocVector(REALSXP,66));
	PROTECT(sCD4_350500 = allocVector(REALSXP,66));
	PROTECT(sCD4_500 = allocVector(REALSXP,66));
	PROTECT(sCD4_200_Art = allocVector(REALSXP,66));
	PROTECT(sCD4_200350_Art = allocVector(REALSXP,66));
	PROTECT(sCD4_350500_Art = allocVector(REALSXP,66));
	PROTECT(sCD4_500_Art = allocVector(REALSXP,66));
	PROTECT(sWHO_1 = allocVector(REALSXP,66));
	PROTECT(sWHO_2 = allocVector(REALSXP,66));
	PROTECT(sWHO_3 = allocVector(REALSXP,66));
	PROTECT(sWHO_4 = allocVector(REALSXP,66));
	PROTECT(sWHO_1_Art = allocVector(REALSXP,66));
	PROTECT(sWHO_2_Art = allocVector(REALSXP,66));
	PROTECT(sWHO_3_Art = allocVector(REALSXP,66));
	PROTECT(sWHO_4_Art = allocVector(REALSXP,66));
	PROTECT(sINCIDENCE = allocVector(REALSXP,66));
	PROTECT(sPreArtCOST = allocVector(REALSXP,20));
	PROTECT(sArtCOST = allocVector(REALSXP,20));
	PROTECT(sPreArtCOST_Hiv = allocVector(REALSXP,20));
	PROTECT(sArtCOST_Hiv = allocVector(REALSXP,20));
	PROTECT(sC1 = allocVector(REALSXP,9));
	PROTECT(sL21 = allocVector(REALSXP,36));
	PROTECT(sR3 = allocVector(REALSXP,9));
	PROTECT(sR8 = allocVector(REALSXP,9));
	PROTECT(sART1 = allocVector(REALSXP,48));
	PROTECT(sART4 = allocVector(REALSXP,3));
	PROTECT(sART5 = allocVector(REALSXP,9));
	PROTECT(sART6 = allocVector(REALSXP,3));
	PROTECT(sART9 = allocVector(REALSXP,9));
	PROTECT(sART10 = allocVector(REALSXP,3));
	PROTECT(sART11 = allocVector(REALSXP,9));
	PROTECT(sART12 = allocVector(REALSXP,3));
	PROTECT(sART13 = allocVector(REALSXP,9));
	PROTECT(sART14 = allocVector(REALSXP,9));
	PROTECT(sPre2010 = allocVector(REALSXP,3));
	PROTECT(sIn2014 = allocVector(INTSXP,2));
	PROTECT(sHivArray = allocVector(INTSXP,3));
	PROTECT(sDiagArray = allocVector(INTSXP,3));
	PROTECT(sArtArray = allocVector(INTSXP,3));
	PROTECT(sR3_Counter = allocVector(INTSXP,9));
	PROTECT(sR8_Counter = allocVector(INTSXP,9));
	PROTECT(sART6_Counter = allocVector(INTSXP,3));
	PROTECT(sART10_Counter = allocVector(INTSXP,3));
	PROTECT(sART12_Counter = allocVector(INTSXP,3));
	PROTECT(sCLINIC = allocVector(REALSXP,5));
	PROTECT(sDeath = allocVector(REALSXP,66));
	PROTECT(sAidsDeath = allocVector(REALSXP,66));
	PROTECT(sDeath_2010_Age = allocVector(REALSXP,20));
	PROTECT(sAidsDeath_2010_Age = allocVector(REALSXP,20));
	PROTECT(sGuidelines_PopDist_HivNegative = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_500_NeverDiag = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_500_DiagNotInCareNeverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_500_DiagNotInCareEverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_500_InCareNeverArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_500_ArtLessSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_500_ArtMoreSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_500_OffArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_350500_NeverDiag = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_350500_DiagNotInCareNeverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_350500_DiagNotInCareEverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_350500_InCareNeverArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_350500_ArtLessSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_350500_ArtMoreSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_350500_OffArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200350_NeverDiag = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200350_DiagNotInCareNeverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200350_DiagNotInCareEverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200350_InCareNeverArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200350_ArtLessSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200350_ArtMoreSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200350_OffArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200_NeverDiag = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200_DiagNotInCareNeverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200_DiagNotInCareEverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200_InCareNeverArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200_ArtLessSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200_ArtMoreSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PopDist_200_OffArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_HivNegative = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_500_NeverDiag = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_500_DiagNotInCareNeverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_500_DiagNotInCareEverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_500_InCareNeverArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_500_ArtLessSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_500_ArtMoreSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_500_OffArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_350500_NeverDiag = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_350500_DiagNotInCareNeverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_350500_DiagNotInCareEverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_350500_InCareNeverArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_350500_ArtLessSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_350500_ArtMoreSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_350500_OffArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200350_NeverDiag = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200350_DiagNotInCareNeverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200350_DiagNotInCareEverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200350_InCareNeverArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200350_ArtLessSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200350_ArtMoreSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200350_OffArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200_NeverDiag = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200_DiagNotInCareNeverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200_DiagNotInCareEverCare = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200_InCareNeverArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200_ArtLessSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200_ArtMoreSixMonths = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Death_200_OffArt = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Art_500 = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Art_350500 = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Art_200350 = allocVector(INTSXP,36));
	PROTECT(sGuidelines_Art_200 = allocVector(INTSXP,36));
	PROTECT(sGuidelines_NewInfectionsAdult = allocVector(INTSXP,36));
	PROTECT(sGuidelines_NewDiagnoses = allocVector(INTSXP,36));
	PROTECT(sGuidelines_PreArtDropout = allocVector(INTSXP,36));
	PROTECT(sGuidelines_ArtDropout = allocVector(INTSXP,36));
	PROTECT(sMid2010 = allocVector(INTSXP,2));
	PROTECT(sPie_1 = allocVector(INTSXP,3));
	PROTECT(sPie_2 = allocVector(INTSXP,3));
	PROTECT(sPie_3 = allocVector(INTSXP,6));
	PROTECT(sDALY_OffArt = allocVector(REALSXP,20));
	PROTECT(sDALY_OnArt = allocVector(REALSXP,20));
	PROTECT(sDALY_LYL = allocVector(REALSXP,20));
	PROTECT(sPOP = allocVector(REALSXP,66));
	PROTECT(sUNIT_HctVisitCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_RapidHivTestCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_LinkageCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_ImpCareCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_PreArtClinicVisitCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_LabCd4TestCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_PocCd4TestCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_AnnualArtCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_AnnualAdherenceCost = allocVector(REALSXP,20));
	PROTECT(sUNIT_OutreachCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_HctVisitCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_RapidHivTestCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_LinkageCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_ImpCareCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_PreArtClinicVisitCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_LabCd4TestCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_PocCd4TestCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_AnnualArtCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_AnnualAdherenceCost = allocVector(REALSXP,20));
	PROTECT(sUnitCost_OutreachCost = allocVector(REALSXP,20));

	double * pCARE = REAL(sCARE);
	double * pCARE_PT = REAL(sCARE_PT);
	double * pDALY = REAL(sDALY);
	double * pCOST = REAL(sCOST);
	double * pPOP_15to49 = REAL(sPOP_15to49);
	double * pHIV_15to49 = REAL(sHIV_15to49);
	double * pART_15to49 = REAL(sART_15to49);
	double * pPOP_15plus = REAL(sPOP_15plus);
	double * pAidsDeath_15plus = REAL(sAidsDeath_15plus);
	double * pPOP_AgeSex_2007 = REAL(sPOP_AgeSex_2007);
	double * pHIV_AgeSex_2007 = REAL(sHIV_AgeSex_2007);
	double * pPOP_NoArtCd4_2007 = REAL(sPOP_NoArtCd4_2007);
	double * pPOP_AgeSex_2012 = REAL(sPOP_AgeSex_2012);
	double * pHIV_AgeSex_2012 = REAL(sHIV_AgeSex_2012);
	double * pPOP_AgeSex_2014 = REAL(sPOP_AgeSex_2014);
	double * pHIV_AgeSex_2014 = REAL(sHIV_AgeSex_2014);
	double * pCd4_200 = REAL(sCD4_200);
	double * pCd4_200350 = REAL(sCD4_200350);
	double * pCd4_350500 = REAL(sCD4_350500);
	double * pCd4_500 = REAL(sCD4_500);
	double * pCd4_200_Art = REAL(sCD4_200_Art);
	double * pCd4_200350_Art = REAL(sCD4_200350_Art);
	double * pCd4_350500_Art = REAL(sCD4_350500_Art);
	double * pCd4_500_Art = REAL(sCD4_500_Art);
	double * pWHO_1 = REAL(sWHO_1);
	double * pWHO_2 = REAL(sWHO_2);
	double * pWHO_3 = REAL(sWHO_3);
	double * pWHO_4 = REAL(sWHO_4);
	double * pWHO_1_Art = REAL(sWHO_1_Art);
	double * pWHO_2_Art = REAL(sWHO_2_Art);
	double * pWHO_3_Art = REAL(sWHO_3_Art);
	double * pWHO_4_Art = REAL(sWHO_4_Art);
	double * pINCIDENCE = REAL(sINCIDENCE);
	double * pPreArtCOST = REAL(sPreArtCOST);
	double * pArtCOST = REAL(sArtCOST);
	double * pPreArtCOST_Hiv = REAL(sPreArtCOST_Hiv);
	double * pArtCOST_Hiv = REAL(sArtCOST_Hiv);
	double * pC1 = REAL(sC1);
	double * pL21 = REAL(sL21);
	double * pR3 = REAL(sR3);
	double * pR8 = REAL(sR8);
	double * pART1 = REAL(sART1);
	double * pART4 = REAL(sART4);
	double * pART5 = REAL(sART5);
	double * pART6 = REAL(sART6);
	double * pART9 = REAL(sART9);
	double * pART10 = REAL(sART10);
	double * pART11 = REAL(sART11);
	double * pART12 = REAL(sART12);
	double * pART13 = REAL(sART13);
	double * pART14 = REAL(sART14);
	double * pPre2010 = REAL(sPre2010);
	int * pIn2014 = INTEGER(sIn2014);
	int * pHivArray = INTEGER(sHivArray);
	int * pDiagArray = INTEGER(sDiagArray);
	int * pArtArray = INTEGER(sArtArray);
	int * pR3_Counter = INTEGER(sR3_Counter);
	int * pR8_Counter = INTEGER(sR8_Counter);
	int * pART6_Counter = INTEGER(sART6_Counter);
	int * pART10_Counter = INTEGER(sART10_Counter);
	int * pART12_Counter = INTEGER(sART12_Counter);
	double * pCLINIC = REAL(sCLINIC);
	double * pDeath = REAL(sDeath);
	double * pAidsDeath = REAL(sAidsDeath);
	double * pDeath_2010_Age = REAL(sDeath_2010_Age);
	double * pAidsDeath_2010_Age = REAL(sAidsDeath_2010_Age);
	double * pDALY_OffArt = REAL(sDALY_OffArt);
	double * pDALY_OnArt = REAL(sDALY_OnArt);
	double * pDALY_LYL = REAL(sDALY_LYL);
	double * pPOP = REAL(sPOP);

	/* Cost Units */
	double * pUNIT_HctVisitCost = REAL(sUNIT_HctVisitCost);
	double * pUNIT_RapidHivTestCost = REAL(sUNIT_RapidHivTestCost);
	double * pUNIT_LinkageCost = REAL(sUNIT_LinkageCost);
	double * pUNIT_ImpCareCost = REAL(sUNIT_ImpCareCost);
	double * pUNIT_PreArtClinicVisitCost = REAL(sUNIT_PreArtClinicVisitCost);
	double * pUNIT_LabCd4TestCost = REAL(sUNIT_LabCd4TestCost);
	double * pUNIT_PocCd4TestCost = REAL(sUNIT_PocCd4TestCost);
	double * pUNIT_AnnualArtCost = REAL(sUNIT_AnnualArtCost);
	double * pUNIT_AnnualAdherenceCost = REAL(sUNIT_AnnualAdherenceCost);
	double * pUNIT_OutreachCost = REAL(sUNIT_OutreachCost);

	/* Unit Costs */
	double * pUnitCost_HctVisitCost = REAL(sUnitCost_HctVisitCost);
	double * pUnitCost_RapidHivTestCost = REAL(sUnitCost_RapidHivTestCost);
	double * pUnitCost_LinkageCost = REAL(sUnitCost_LinkageCost);
	double * pUnitCost_ImpCareCost = REAL(sUnitCost_ImpCareCost);
	double * pUnitCost_PreArtClinicVisitCost = REAL(sUnitCost_PreArtClinicVisitCost);
	double * pUnitCost_LabCd4TestCost = REAL(sUnitCost_LabCd4TestCost);
	double * pUnitCost_PocCd4TestCost = REAL(sUnitCost_PocCd4TestCost);
	double * pUnitCost_AnnualArtCost = REAL(sUnitCost_AnnualArtCost);
	double * pUnitCost_AnnualAdherenceCost = REAL(sUnitCost_AnnualAdherenceCost);
	double * pUnitCost_OutreachCost = REAL(sUnitCost_OutreachCost);

	int * pGuidelines_PopDist_HivNegative = INTEGER(sGuidelines_PopDist_HivNegative);
	int * pGuidelines_PopDist_500_NeverDiag = INTEGER(sGuidelines_PopDist_500_NeverDiag);
	int * pGuidelines_PopDist_500_DiagNotInCareNeverCare = INTEGER(sGuidelines_PopDist_500_DiagNotInCareNeverCare);
	int * pGuidelines_PopDist_500_DiagNotInCareEverCare = INTEGER(sGuidelines_PopDist_500_DiagNotInCareEverCare);
	int * pGuidelines_PopDist_500_InCareNeverArt = INTEGER(sGuidelines_PopDist_500_InCareNeverArt);
	int * pGuidelines_PopDist_500_ArtLessSixMonths = INTEGER(sGuidelines_PopDist_500_ArtLessSixMonths);
	int * pGuidelines_PopDist_500_ArtMoreSixMonths = INTEGER(sGuidelines_PopDist_500_ArtMoreSixMonths);
	int * pGuidelines_PopDist_500_OffArt = INTEGER(sGuidelines_PopDist_500_OffArt);
	int * pGuidelines_PopDist_350500_NeverDiag = INTEGER(sGuidelines_PopDist_350500_NeverDiag);
	int * pGuidelines_PopDist_350500_DiagNotInCareNeverCare = INTEGER(sGuidelines_PopDist_350500_DiagNotInCareNeverCare);
	int * pGuidelines_PopDist_350500_DiagNotInCareEverCare = INTEGER(sGuidelines_PopDist_350500_DiagNotInCareEverCare);
	int * pGuidelines_PopDist_350500_InCareNeverArt = INTEGER(sGuidelines_PopDist_350500_InCareNeverArt);
	int * pGuidelines_PopDist_350500_ArtLessSixMonths = INTEGER(sGuidelines_PopDist_350500_ArtLessSixMonths);
	int * pGuidelines_PopDist_350500_ArtMoreSixMonths = INTEGER(sGuidelines_PopDist_350500_ArtMoreSixMonths);
	int * pGuidelines_PopDist_350500_OffArt = INTEGER(sGuidelines_PopDist_350500_OffArt);
	int * pGuidelines_PopDist_200350_NeverDiag = INTEGER(sGuidelines_PopDist_200350_NeverDiag);
	int * pGuidelines_PopDist_200350_DiagNotInCareNeverCare = INTEGER(sGuidelines_PopDist_200350_DiagNotInCareNeverCare);
	int * pGuidelines_PopDist_200350_DiagNotInCareEverCare = INTEGER(sGuidelines_PopDist_200350_DiagNotInCareEverCare);
	int * pGuidelines_PopDist_200350_InCareNeverArt = INTEGER(sGuidelines_PopDist_200350_InCareNeverArt);
	int * pGuidelines_PopDist_200350_ArtLessSixMonths = INTEGER(sGuidelines_PopDist_200350_ArtLessSixMonths);
	int * pGuidelines_PopDist_200350_ArtMoreSixMonths = INTEGER(sGuidelines_PopDist_200350_ArtMoreSixMonths);
	int * pGuidelines_PopDist_200350_OffArt = INTEGER(sGuidelines_PopDist_200350_OffArt);
	int * pGuidelines_PopDist_200_NeverDiag = INTEGER(sGuidelines_PopDist_200_NeverDiag);
	int * pGuidelines_PopDist_200_DiagNotInCareNeverCare = INTEGER(sGuidelines_PopDist_200_DiagNotInCareNeverCare);
	int * pGuidelines_PopDist_200_DiagNotInCareEverCare = INTEGER(sGuidelines_PopDist_200_DiagNotInCareEverCare);
	int * pGuidelines_PopDist_200_InCareNeverArt = INTEGER(sGuidelines_PopDist_200_InCareNeverArt);
	int * pGuidelines_PopDist_200_ArtLessSixMonths = INTEGER(sGuidelines_PopDist_200_ArtLessSixMonths);
	int * pGuidelines_PopDist_200_ArtMoreSixMonths = INTEGER(sGuidelines_PopDist_200_ArtMoreSixMonths);
	int * pGuidelines_PopDist_200_OffArt = INTEGER(sGuidelines_PopDist_200_OffArt);
	int * pGuidelines_Death_HivNegative = INTEGER(sGuidelines_Death_HivNegative);
	int * pGuidelines_Death_500_NeverDiag = INTEGER(sGuidelines_Death_500_NeverDiag);
	int * pGuidelines_Death_500_DiagNotInCareNeverCare = INTEGER(sGuidelines_Death_500_DiagNotInCareNeverCare);
	int * pGuidelines_Death_500_DiagNotInCareEverCare = INTEGER(sGuidelines_Death_500_DiagNotInCareEverCare);
	int * pGuidelines_Death_500_InCareNeverArt = INTEGER(sGuidelines_Death_500_InCareNeverArt);
	int * pGuidelines_Death_500_ArtLessSixMonths = INTEGER(sGuidelines_Death_500_ArtLessSixMonths);
	int * pGuidelines_Death_500_ArtMoreSixMonths = INTEGER(sGuidelines_Death_500_ArtMoreSixMonths);
	int * pGuidelines_Death_500_OffArt = INTEGER(sGuidelines_Death_500_OffArt);
	int * pGuidelines_Death_350500_NeverDiag = INTEGER(sGuidelines_Death_350500_NeverDiag);
	int * pGuidelines_Death_350500_DiagNotInCareNeverCare = INTEGER(sGuidelines_Death_350500_DiagNotInCareNeverCare);
	int * pGuidelines_Death_350500_DiagNotInCareEverCare = INTEGER(sGuidelines_Death_350500_DiagNotInCareEverCare);
	int * pGuidelines_Death_350500_InCareNeverArt = INTEGER(sGuidelines_Death_350500_InCareNeverArt);
	int * pGuidelines_Death_350500_ArtLessSixMonths = INTEGER(sGuidelines_Death_350500_ArtLessSixMonths);
	int * pGuidelines_Death_350500_ArtMoreSixMonths = INTEGER(sGuidelines_Death_350500_ArtMoreSixMonths);
	int * pGuidelines_Death_350500_OffArt = INTEGER(sGuidelines_Death_350500_OffArt);
	int * pGuidelines_Death_200350_NeverDiag = INTEGER(sGuidelines_Death_200350_NeverDiag);
	int * pGuidelines_Death_200350_DiagNotInCareNeverCare = INTEGER(sGuidelines_Death_200350_DiagNotInCareNeverCare);
	int * pGuidelines_Death_200350_DiagNotInCareEverCare = INTEGER(sGuidelines_Death_200350_DiagNotInCareEverCare);
	int * pGuidelines_Death_200350_InCareNeverArt = INTEGER(sGuidelines_Death_200350_InCareNeverArt);
	int * pGuidelines_Death_200350_ArtLessSixMonths = INTEGER(sGuidelines_Death_200350_ArtLessSixMonths);
	int * pGuidelines_Death_200350_ArtMoreSixMonths = INTEGER(sGuidelines_Death_200350_ArtMoreSixMonths);
	int * pGuidelines_Death_200350_OffArt = INTEGER(sGuidelines_Death_200350_OffArt);
	int * pGuidelines_Death_200_NeverDiag = INTEGER(sGuidelines_Death_200_NeverDiag);
	int * pGuidelines_Death_200_DiagNotInCareNeverCare = INTEGER(sGuidelines_Death_200_DiagNotInCareNeverCare);
	int * pGuidelines_Death_200_DiagNotInCareEverCare = INTEGER(sGuidelines_Death_200_DiagNotInCareEverCare);
	int * pGuidelines_Death_200_InCareNeverArt = INTEGER(sGuidelines_Death_200_InCareNeverArt);
	int * pGuidelines_Death_200_ArtLessSixMonths = INTEGER(sGuidelines_Death_200_ArtLessSixMonths);
	int * pGuidelines_Death_200_ArtMoreSixMonths = INTEGER(sGuidelines_Death_200_ArtMoreSixMonths);
	int * pGuidelines_Death_200_OffArt = INTEGER(sGuidelines_Death_200_OffArt);	
	int * pGuidelines_Art_500 = INTEGER(sGuidelines_Art_500);
	int * pGuidelines_Art_350500 = INTEGER(sGuidelines_Art_350500);
	int * pGuidelines_Art_200350 = INTEGER(sGuidelines_Art_200350);
	int * pGuidelines_Art_200 = INTEGER(sGuidelines_Art_200);
	int * pGuidelines_NewInfectionsAdult = INTEGER(sGuidelines_NewInfectionsAdult);
	int * pGuidelines_NewDiagnoses = INTEGER(sGuidelines_NewDiagnoses);
	int * pGuidelines_PreArtDropout = INTEGER(sGuidelines_PreArtDropout);
	int * pGuidelines_ArtDropout = INTEGER(sGuidelines_ArtDropout);
	int * pMid2010 = INTEGER(sMid2010);
	int * pPie_1 = INTEGER(sPie_1);
	int * pPie_2 = INTEGER(sPie_2);
	int * pPie_3 = INTEGER(sPie_3);

	for(size_t i=0;i<66;i++) {
		if(i<2)
			pMid2010[i] = mid2010[i];
		if(i<2)
			pIn2014[i] = In2014[i];
		if(i<3) {
			pART4[i] = ART4[i];
			pART6[i] = ART6[i];
			pART10[i] = ART10[i];
			pART12[i] = ART12[i];
			pPre2010[i] = Pre2010[i];
			pHivArray[i] = HivArray[i];
			pDiagArray[i] = DiagArray[i];
			pArtArray[i] = ArtArray[i];
			pART6_Counter[i] = ART6_Counter[i];
			pART10_Counter[i] = ART10_Counter[i];
			pART12_Counter[i] = ART12_Counter[i];
			pPie_1[i] = Pie_1[i];
			pPie_2[i] = Pie_2[i];
		}
		if(i<4)
			pPOP_NoArtCd4_2007[i] = thePOP_NoArtCd4_2007[i];
		if(i<5)
			pCLINIC[i] = theCLINIC[i];
		if(i<6) {
			pCARE[i] = theCARE[i];
			pCARE_PT[i] = theCARE_PT[i];
			pPie_3[i] = Pie_3[i];	
		}
		if(i<9) {
			pC1[i] = C1[i];
			pR3[i] = R3[i];
			pR8[i] = R8[i];
			pART5[i] = ART5[i];
			pART9[i] = ART9[i];
			pART11[i] = ART11[i];
			pART13[i] = ART13[i];
			pART14[i] = ART14[i];
			pR3_Counter[i] = R3_Counter[i];
			pR8_Counter[i] = R8_Counter[i];
		}
		if(i<10) {
			pPOP_AgeSex_2014[i] = thePOP_AgeSex_2014[i];
			pHIV_AgeSex_2014[i] = theHIV_AgeSex_2014[i];
		}
		if(i<16) {
			pPOP_AgeSex_2012[i] = thePOP_AgeSex_2012[i];
			pHIV_AgeSex_2012[i] = theHIV_AgeSex_2012[i];
		}
		if(i<20) {
			pPOP_AgeSex_2007[i] = thePOP_AgeSex_2007[i];
			pHIV_AgeSex_2007[i] = theHIV_AgeSex_2007[i];
			pDeath_2010_Age[i] = theDeath_2010_Age[i];
			pAidsDeath_2010_Age[i] = theAidsDeath_2010_Age[i];
			pDALY[i] = theDALY[i];
			pCOST[i] = theCOST[i];
			pPreArtCOST[i] = thePreArtCOST[i];
			pArtCOST[i] = theArtCOST[i];
			pPreArtCOST_Hiv[i] = thePreArtCOST_Hiv[i];
			pArtCOST_Hiv[i] = theArtCOST_Hiv[i];
			pDALY_OffArt[i] = theDALY_OffArt[i];
			pDALY_OnArt[i] = theDALY_OnArt[i];
			pDALY_LYL[i] = theDALY_LYL[i];
			pUNIT_HctVisitCost[i] = theUNIT_HctVisitCost[i];
			pUNIT_RapidHivTestCost[i] = theUNIT_RapidHivTestCost[i];
			pUNIT_LinkageCost[i] = theUNIT_LinkageCost[i];
			pUNIT_ImpCareCost[i] = theUNIT_ImpCareCost[i];
			pUNIT_PreArtClinicVisitCost[i] = theUNIT_PreArtClinicVisitCost[i];
			pUNIT_LabCd4TestCost[i] = theUNIT_LabCd4TestCost[i];
			pUNIT_PocCd4TestCost[i] = theUNIT_PocCd4TestCost[i];
			pUNIT_AnnualArtCost[i] = theUNIT_AnnualArtCost[i];
			pUNIT_AnnualAdherenceCost[i] = theUNIT_AnnualAdherenceCost[i];
			pUNIT_OutreachCost[i] = theUNIT_OutreachCost[i];
			pUnitCost_HctVisitCost[i] = theUnitCost_HctVisitCost[i];
			pUnitCost_RapidHivTestCost[i] = theUnitCost_RapidHivTestCost[i];
			pUnitCost_LinkageCost[i] = theUnitCost_LinkageCost[i];
			pUnitCost_ImpCareCost[i] = theUnitCost_ImpCareCost[i];
			pUnitCost_PreArtClinicVisitCost[i] = theUnitCost_PreArtClinicVisitCost[i];
			pUnitCost_LabCd4TestCost[i] = theUnitCost_LabCd4TestCost[i];
			pUnitCost_PocCd4TestCost[i] = theUnitCost_PocCd4TestCost[i];
			pUnitCost_AnnualArtCost[i] = theUnitCost_AnnualArtCost[i];
			pUnitCost_AnnualAdherenceCost[i] = theUnitCost_AnnualAdherenceCost[i];
			pUnitCost_OutreachCost[i] = theUnitCost_OutreachCost[i];
		}
		if(i<36)
			pL21[i] = L21[i];
		if(i<48)
			pART1[i] = ART1[i];
		pPOP_15to49[i] = thePOP_15to49[i];
		pHIV_15to49[i] = theHIV_15to49[i];
		pART_15to49[i] = theART_15to49[i];
		pPOP_15plus[i] = thePOP_15plus[i];
		pAidsDeath_15plus[i] = theAidsDeath_15plus[i];
		pCd4_200[i] = theCD4_200[i];
		pCd4_200350[i] = theCD4_200350[i];
		pCd4_350500[i] = theCD4_350500[i];
		pCd4_500[i] = theCD4_500[i];
		pCd4_200_Art[i] = theCD4_200_Art[i];
		pCd4_200350_Art[i] = theCD4_200350_Art[i];
		pCd4_350500_Art[i] = theCD4_350500_Art[i];
		pCd4_500_Art[i] = theCD4_500_Art[i];
		pWHO_1[i] = theWHO_1[i];
		pWHO_2[i] = theWHO_2[i];
		pWHO_3[i] = theWHO_3[i];
		pWHO_4[i] = theWHO_4[i];
		pWHO_1_Art[i] = theWHO_1_Art[i];
		pWHO_2_Art[i] = theWHO_2_Art[i];
		pWHO_3_Art[i] = theWHO_3_Art[i];
		pWHO_4_Art[i] = theWHO_4_Art[i];
		pINCIDENCE[i] = theINCIDENCE[i];
		pDeath[i] = theDeath[i];
		pAidsDeath[i] = theAidsDeath[i];
		pPOP[i] = thePOP[i];
	}

	for(size_t i=0;i<36;i++) {
		pGuidelines_PopDist_HivNegative[i] = theGuidelines_PopDist_HivNegative[i];
		pGuidelines_PopDist_500_NeverDiag[i] = theGuidelines_PopDist_500_NeverDiag[i];
		pGuidelines_PopDist_500_DiagNotInCareNeverCare[i] = theGuidelines_PopDist_500_DiagNotInCareNeverCare[i];
		pGuidelines_PopDist_500_DiagNotInCareEverCare[i] = theGuidelines_PopDist_500_DiagNotInCareEverCare[i];
		pGuidelines_PopDist_500_InCareNeverArt[i] = theGuidelines_PopDist_500_InCareNeverArt[i];
		pGuidelines_PopDist_500_ArtLessSixMonths[i] = theGuidelines_PopDist_500_ArtLessSixMonths[i];
		pGuidelines_PopDist_500_ArtMoreSixMonths[i] = theGuidelines_PopDist_500_ArtMoreSixMonths[i];
		pGuidelines_PopDist_500_OffArt[i] = theGuidelines_PopDist_500_OffArt[i];
		pGuidelines_PopDist_350500_NeverDiag[i] = theGuidelines_PopDist_350500_NeverDiag[i];
		pGuidelines_PopDist_350500_DiagNotInCareNeverCare[i] = theGuidelines_PopDist_350500_DiagNotInCareNeverCare[i];
		pGuidelines_PopDist_350500_DiagNotInCareEverCare[i] = theGuidelines_PopDist_350500_DiagNotInCareEverCare[i];
		pGuidelines_PopDist_350500_InCareNeverArt[i] = theGuidelines_PopDist_350500_InCareNeverArt[i];
		pGuidelines_PopDist_350500_ArtLessSixMonths[i] = theGuidelines_PopDist_350500_ArtLessSixMonths[i];
		pGuidelines_PopDist_350500_ArtMoreSixMonths[i] = theGuidelines_PopDist_350500_ArtMoreSixMonths[i];
		pGuidelines_PopDist_350500_OffArt[i] = theGuidelines_PopDist_350500_OffArt[i];
		pGuidelines_PopDist_200350_NeverDiag[i] = theGuidelines_PopDist_200350_NeverDiag[i];
		pGuidelines_PopDist_200350_DiagNotInCareNeverCare[i] = theGuidelines_PopDist_200350_DiagNotInCareNeverCare[i];
		pGuidelines_PopDist_200350_DiagNotInCareEverCare[i] = theGuidelines_PopDist_200350_DiagNotInCareEverCare[i];
		pGuidelines_PopDist_200350_InCareNeverArt[i] = theGuidelines_PopDist_200350_InCareNeverArt[i];
		pGuidelines_PopDist_200350_ArtLessSixMonths[i] = theGuidelines_PopDist_200350_ArtLessSixMonths[i];
		pGuidelines_PopDist_200350_ArtMoreSixMonths[i] = theGuidelines_PopDist_200350_ArtMoreSixMonths[i];
		pGuidelines_PopDist_200350_OffArt[i] = theGuidelines_PopDist_200350_OffArt[i];
		pGuidelines_PopDist_200_NeverDiag[i] = theGuidelines_PopDist_200_NeverDiag[i];
		pGuidelines_PopDist_200_DiagNotInCareNeverCare[i] = theGuidelines_PopDist_200_DiagNotInCareNeverCare[i];
		pGuidelines_PopDist_200_DiagNotInCareEverCare[i] = theGuidelines_PopDist_200_DiagNotInCareEverCare[i];
		pGuidelines_PopDist_200_InCareNeverArt[i] = theGuidelines_PopDist_200_InCareNeverArt[i];
		pGuidelines_PopDist_200_ArtLessSixMonths[i] = theGuidelines_PopDist_200_ArtLessSixMonths[i];
		pGuidelines_PopDist_200_ArtMoreSixMonths[i] = theGuidelines_PopDist_200_ArtMoreSixMonths[i];
		pGuidelines_PopDist_200_OffArt[i] = theGuidelines_PopDist_200_OffArt[i];
		pGuidelines_Death_HivNegative[i] = theGuidelines_Death_HivNegative[i];
		pGuidelines_Death_500_NeverDiag[i] = theGuidelines_Death_500_NeverDiag[i];
		pGuidelines_Death_500_DiagNotInCareNeverCare[i] = theGuidelines_Death_500_DiagNotInCareNeverCare[i];
		pGuidelines_Death_500_DiagNotInCareEverCare[i] = theGuidelines_Death_500_DiagNotInCareEverCare[i];
		pGuidelines_Death_500_InCareNeverArt[i] = theGuidelines_Death_500_InCareNeverArt[i];
		pGuidelines_Death_500_ArtLessSixMonths[i] = theGuidelines_Death_500_ArtLessSixMonths[i];
		pGuidelines_Death_500_ArtMoreSixMonths[i] = theGuidelines_Death_500_ArtMoreSixMonths[i];
		pGuidelines_Death_500_OffArt[i] = theGuidelines_Death_500_OffArt[i];
		pGuidelines_Death_350500_NeverDiag[i] = theGuidelines_Death_350500_NeverDiag[i];
		pGuidelines_Death_350500_DiagNotInCareNeverCare[i] = theGuidelines_Death_350500_DiagNotInCareNeverCare[i];
		pGuidelines_Death_350500_DiagNotInCareEverCare[i] = theGuidelines_Death_350500_DiagNotInCareEverCare[i];
		pGuidelines_Death_350500_InCareNeverArt[i] = theGuidelines_Death_350500_InCareNeverArt[i];
		pGuidelines_Death_350500_ArtLessSixMonths[i] = theGuidelines_Death_350500_ArtLessSixMonths[i];
		pGuidelines_Death_350500_ArtMoreSixMonths[i] = theGuidelines_Death_350500_ArtMoreSixMonths[i];
		pGuidelines_Death_350500_OffArt[i] = theGuidelines_Death_350500_OffArt[i];
		pGuidelines_Death_200350_NeverDiag[i] = theGuidelines_Death_200350_NeverDiag[i];
		pGuidelines_Death_200350_DiagNotInCareNeverCare[i] = theGuidelines_Death_200350_DiagNotInCareNeverCare[i];
		pGuidelines_Death_200350_DiagNotInCareEverCare[i] = theGuidelines_Death_200350_DiagNotInCareEverCare[i];
		pGuidelines_Death_200350_InCareNeverArt[i] = theGuidelines_Death_200350_InCareNeverArt[i];
		pGuidelines_Death_200350_ArtLessSixMonths[i] = theGuidelines_Death_200350_ArtLessSixMonths[i];
		pGuidelines_Death_200350_ArtMoreSixMonths[i] = theGuidelines_Death_200350_ArtMoreSixMonths[i];
		pGuidelines_Death_200350_OffArt[i] = theGuidelines_Death_200350_OffArt[i];
		pGuidelines_Death_200_NeverDiag[i] = theGuidelines_Death_200_NeverDiag[i];
		pGuidelines_Death_200_DiagNotInCareNeverCare[i] = theGuidelines_Death_200_DiagNotInCareNeverCare[i];
		pGuidelines_Death_200_DiagNotInCareEverCare[i] = theGuidelines_Death_200_DiagNotInCareEverCare[i];
		pGuidelines_Death_200_InCareNeverArt[i] = theGuidelines_Death_200_InCareNeverArt[i];
		pGuidelines_Death_200_ArtLessSixMonths[i] = theGuidelines_Death_200_ArtLessSixMonths[i];
		pGuidelines_Death_200_ArtMoreSixMonths[i] = theGuidelines_Death_200_ArtMoreSixMonths[i];
		pGuidelines_Death_200_OffArt[i] = theGuidelines_Death_200_OffArt[i];
		pGuidelines_Art_500[i] = theGuidelines_Art_500[i];
		pGuidelines_Art_350500[i] = theGuidelines_Art_350500[i];
		pGuidelines_Art_200350[i] = theGuidelines_Art_200350[i];
		pGuidelines_Art_200[i] = theGuidelines_Art_200[i];
		pGuidelines_NewInfectionsAdult[i] = theGuidelines_NewInfectionsAdult[i];
		pGuidelines_NewDiagnoses[i] = theGuidelines_NewDiagnoses[i];
		pGuidelines_PreArtDropout[i] = theGuidelines_PreArtDropout[i];
		pGuidelines_ArtDropout[i] = theGuidelines_ArtDropout[i];
	}

	PROTECT(sOUT = allocVector(VECSXP,160));
	SET_VECTOR_ELT(sOUT,0,sCARE);
	SET_VECTOR_ELT(sOUT,1,sDALY);
	SET_VECTOR_ELT(sOUT,2,sCOST);
	SET_VECTOR_ELT(sOUT,3,sPOP_15to49);
	SET_VECTOR_ELT(sOUT,4,sHIV_15to49);
	SET_VECTOR_ELT(sOUT,5,sART_15to49);
	SET_VECTOR_ELT(sOUT,6,sPOP_15plus);
	SET_VECTOR_ELT(sOUT,7,sAidsDeath_15plus);
	SET_VECTOR_ELT(sOUT,8,sPOP_AgeSex_2007);
	SET_VECTOR_ELT(sOUT,9,sHIV_AgeSex_2007);
	SET_VECTOR_ELT(sOUT,10,sPOP_NoArtCd4_2007);
	SET_VECTOR_ELT(sOUT,11,sPOP_AgeSex_2012);
	SET_VECTOR_ELT(sOUT,12,sHIV_AgeSex_2012);
	SET_VECTOR_ELT(sOUT,13,sPOP_AgeSex_2014);
	SET_VECTOR_ELT(sOUT,14,sHIV_AgeSex_2014);
	SET_VECTOR_ELT(sOUT,15,sCD4_200);
	SET_VECTOR_ELT(sOUT,16,sCD4_200350);
	SET_VECTOR_ELT(sOUT,17,sCD4_350500);
	SET_VECTOR_ELT(sOUT,18,sCD4_500);
	SET_VECTOR_ELT(sOUT,19,sCD4_200_Art);
	SET_VECTOR_ELT(sOUT,20,sCD4_200350_Art);
	SET_VECTOR_ELT(sOUT,21,sCD4_350500_Art);
	SET_VECTOR_ELT(sOUT,22,sCD4_500_Art);
	SET_VECTOR_ELT(sOUT,23,sWHO_1);
	SET_VECTOR_ELT(sOUT,24,sWHO_2);
	SET_VECTOR_ELT(sOUT,25,sWHO_3);
	SET_VECTOR_ELT(sOUT,26,sWHO_4);
	SET_VECTOR_ELT(sOUT,27,sWHO_1_Art);
	SET_VECTOR_ELT(sOUT,28,sWHO_2_Art);
	SET_VECTOR_ELT(sOUT,29,sWHO_3_Art);
	SET_VECTOR_ELT(sOUT,30,sWHO_4_Art);
	SET_VECTOR_ELT(sOUT,31,sINCIDENCE);
	SET_VECTOR_ELT(sOUT,32,sPreArtCOST);
	SET_VECTOR_ELT(sOUT,33,sArtCOST);
	SET_VECTOR_ELT(sOUT,34,sPreArtCOST_Hiv);
	SET_VECTOR_ELT(sOUT,35,sArtCOST_Hiv);
	SET_VECTOR_ELT(sOUT,36,sC1);
	SET_VECTOR_ELT(sOUT,37,sL21);
	SET_VECTOR_ELT(sOUT,38,sR3);
	SET_VECTOR_ELT(sOUT,39,sR8);
	SET_VECTOR_ELT(sOUT,40,sART1);
	SET_VECTOR_ELT(sOUT,41,sART4);
	SET_VECTOR_ELT(sOUT,42,sART5);
	SET_VECTOR_ELT(sOUT,43,sART6);
	SET_VECTOR_ELT(sOUT,44,sART9);
	SET_VECTOR_ELT(sOUT,45,sART10);
	SET_VECTOR_ELT(sOUT,46,sART11);
	SET_VECTOR_ELT(sOUT,47,sART12);
	SET_VECTOR_ELT(sOUT,48,sART13);
	SET_VECTOR_ELT(sOUT,49,sART14);
	SET_VECTOR_ELT(sOUT,50,sPre2010);
	SET_VECTOR_ELT(sOUT,51,sHivArray);
	SET_VECTOR_ELT(sOUT,52,sDiagArray);
	SET_VECTOR_ELT(sOUT,53,sArtArray);
	SET_VECTOR_ELT(sOUT,54,sR3_Counter);
	SET_VECTOR_ELT(sOUT,55,sR8_Counter);
	SET_VECTOR_ELT(sOUT,56,sART6_Counter);
	SET_VECTOR_ELT(sOUT,57,sART10_Counter);
	SET_VECTOR_ELT(sOUT,58,sART12_Counter);
	SET_VECTOR_ELT(sOUT,59,sCLINIC);
	SET_VECTOR_ELT(sOUT,60,sDeath);
	SET_VECTOR_ELT(sOUT,61,sAidsDeath);
	SET_VECTOR_ELT(sOUT,62,sDeath_2010_Age);
	SET_VECTOR_ELT(sOUT,63,sAidsDeath_2010_Age);
	SET_VECTOR_ELT(sOUT,64,sGuidelines_PopDist_HivNegative);
	SET_VECTOR_ELT(sOUT,65,sGuidelines_PopDist_500_NeverDiag);
	SET_VECTOR_ELT(sOUT,66,sGuidelines_PopDist_500_DiagNotInCareNeverCare);
	SET_VECTOR_ELT(sOUT,67,sGuidelines_PopDist_500_DiagNotInCareEverCare);
	SET_VECTOR_ELT(sOUT,68,sGuidelines_PopDist_500_InCareNeverArt);
	SET_VECTOR_ELT(sOUT,69,sGuidelines_PopDist_500_ArtLessSixMonths);
	SET_VECTOR_ELT(sOUT,70,sGuidelines_PopDist_500_ArtMoreSixMonths);
	SET_VECTOR_ELT(sOUT,71,sGuidelines_PopDist_500_OffArt);
	SET_VECTOR_ELT(sOUT,72,sGuidelines_PopDist_350500_NeverDiag);
	SET_VECTOR_ELT(sOUT,73,sGuidelines_PopDist_350500_DiagNotInCareNeverCare);
	SET_VECTOR_ELT(sOUT,74,sGuidelines_PopDist_350500_DiagNotInCareEverCare);
	SET_VECTOR_ELT(sOUT,75,sGuidelines_PopDist_350500_InCareNeverArt);
	SET_VECTOR_ELT(sOUT,76,sGuidelines_PopDist_350500_ArtLessSixMonths);
	SET_VECTOR_ELT(sOUT,77,sGuidelines_PopDist_350500_ArtMoreSixMonths);
	SET_VECTOR_ELT(sOUT,78,sGuidelines_PopDist_350500_OffArt);
	SET_VECTOR_ELT(sOUT,79,sGuidelines_PopDist_200350_NeverDiag);
	SET_VECTOR_ELT(sOUT,80,sGuidelines_PopDist_200350_DiagNotInCareNeverCare);
	SET_VECTOR_ELT(sOUT,81,sGuidelines_PopDist_200350_DiagNotInCareEverCare);
	SET_VECTOR_ELT(sOUT,82,sGuidelines_PopDist_200350_InCareNeverArt);
	SET_VECTOR_ELT(sOUT,83,sGuidelines_PopDist_200350_ArtLessSixMonths);
	SET_VECTOR_ELT(sOUT,84,sGuidelines_PopDist_200350_ArtMoreSixMonths);
	SET_VECTOR_ELT(sOUT,85,sGuidelines_PopDist_200350_OffArt);
	SET_VECTOR_ELT(sOUT,86,sGuidelines_PopDist_200_NeverDiag);
	SET_VECTOR_ELT(sOUT,87,sGuidelines_PopDist_200_DiagNotInCareNeverCare);
	SET_VECTOR_ELT(sOUT,88,sGuidelines_PopDist_200_DiagNotInCareEverCare);
	SET_VECTOR_ELT(sOUT,89,sGuidelines_PopDist_200_InCareNeverArt);
	SET_VECTOR_ELT(sOUT,90,sGuidelines_PopDist_200_ArtLessSixMonths);
	SET_VECTOR_ELT(sOUT,91,sGuidelines_PopDist_200_ArtMoreSixMonths);
	SET_VECTOR_ELT(sOUT,92,sGuidelines_PopDist_200_OffArt);
	SET_VECTOR_ELT(sOUT,93,sGuidelines_Death_HivNegative);
	SET_VECTOR_ELT(sOUT,94,sGuidelines_Death_500_NeverDiag);
	SET_VECTOR_ELT(sOUT,95,sGuidelines_Death_500_DiagNotInCareNeverCare);
	SET_VECTOR_ELT(sOUT,96,sGuidelines_Death_500_DiagNotInCareEverCare);
	SET_VECTOR_ELT(sOUT,97,sGuidelines_Death_500_InCareNeverArt);
	SET_VECTOR_ELT(sOUT,98,sGuidelines_Death_500_ArtLessSixMonths);
	SET_VECTOR_ELT(sOUT,99,sGuidelines_Death_500_ArtMoreSixMonths);
	SET_VECTOR_ELT(sOUT,100,sGuidelines_Death_500_OffArt);
	SET_VECTOR_ELT(sOUT,101,sGuidelines_Death_350500_NeverDiag);
	SET_VECTOR_ELT(sOUT,102,sGuidelines_Death_350500_DiagNotInCareNeverCare);
	SET_VECTOR_ELT(sOUT,103,sGuidelines_Death_350500_DiagNotInCareEverCare);
	SET_VECTOR_ELT(sOUT,104,sGuidelines_Death_350500_InCareNeverArt);
	SET_VECTOR_ELT(sOUT,105,sGuidelines_Death_350500_ArtLessSixMonths);
	SET_VECTOR_ELT(sOUT,106,sGuidelines_Death_350500_ArtMoreSixMonths);
	SET_VECTOR_ELT(sOUT,107,sGuidelines_Death_350500_OffArt);
	SET_VECTOR_ELT(sOUT,108,sGuidelines_Death_200350_NeverDiag);
	SET_VECTOR_ELT(sOUT,109,sGuidelines_Death_200350_DiagNotInCareNeverCare);
	SET_VECTOR_ELT(sOUT,110,sGuidelines_Death_200350_DiagNotInCareEverCare);
	SET_VECTOR_ELT(sOUT,111,sGuidelines_Death_200350_InCareNeverArt);
	SET_VECTOR_ELT(sOUT,112,sGuidelines_Death_200350_ArtLessSixMonths);
	SET_VECTOR_ELT(sOUT,113,sGuidelines_Death_200350_ArtMoreSixMonths);
	SET_VECTOR_ELT(sOUT,114,sGuidelines_Death_200350_OffArt);
	SET_VECTOR_ELT(sOUT,115,sGuidelines_Death_200_NeverDiag);
	SET_VECTOR_ELT(sOUT,116,sGuidelines_Death_200_DiagNotInCareNeverCare);
	SET_VECTOR_ELT(sOUT,117,sGuidelines_Death_200_DiagNotInCareEverCare);
	SET_VECTOR_ELT(sOUT,118,sGuidelines_Death_200_InCareNeverArt);
	SET_VECTOR_ELT(sOUT,119,sGuidelines_Death_200_ArtLessSixMonths);
	SET_VECTOR_ELT(sOUT,120,sGuidelines_Death_200_ArtMoreSixMonths);
	SET_VECTOR_ELT(sOUT,121,sGuidelines_Death_200_OffArt);
	SET_VECTOR_ELT(sOUT,122,sGuidelines_Art_500);
	SET_VECTOR_ELT(sOUT,123,sGuidelines_Art_350500);
	SET_VECTOR_ELT(sOUT,124,sGuidelines_Art_200350);
	SET_VECTOR_ELT(sOUT,125,sGuidelines_Art_200);
	SET_VECTOR_ELT(sOUT,126,sGuidelines_NewInfectionsAdult);
	SET_VECTOR_ELT(sOUT,127,sGuidelines_NewDiagnoses);
	SET_VECTOR_ELT(sOUT,128,sGuidelines_PreArtDropout);
	SET_VECTOR_ELT(sOUT,129,sGuidelines_ArtDropout);
	SET_VECTOR_ELT(sOUT,130,sIn2014);
	SET_VECTOR_ELT(sOUT,131,sMid2010);
	SET_VECTOR_ELT(sOUT,132,sPie_1);
	SET_VECTOR_ELT(sOUT,133,sPie_2);
	SET_VECTOR_ELT(sOUT,134,sPie_3);
	SET_VECTOR_ELT(sOUT,135,sDALY_OffArt);
	SET_VECTOR_ELT(sOUT,136,sDALY_OnArt);
	SET_VECTOR_ELT(sOUT,137,sDALY_LYL);
	SET_VECTOR_ELT(sOUT,138,sPOP);
	SET_VECTOR_ELT(sOUT,139,sCARE_PT);
	SET_VECTOR_ELT(sOUT,140,sUNIT_HctVisitCost);
	SET_VECTOR_ELT(sOUT,141,sUNIT_RapidHivTestCost);
	SET_VECTOR_ELT(sOUT,142,sUNIT_LinkageCost);
	SET_VECTOR_ELT(sOUT,143,sUNIT_ImpCareCost);
	SET_VECTOR_ELT(sOUT,144,sUNIT_PreArtClinicVisitCost);
	SET_VECTOR_ELT(sOUT,145,sUNIT_LabCd4TestCost);
	SET_VECTOR_ELT(sOUT,146,sUNIT_PocCd4TestCost);
	SET_VECTOR_ELT(sOUT,147,sUNIT_AnnualArtCost);
	SET_VECTOR_ELT(sOUT,148,sUNIT_AnnualAdherenceCost);
	SET_VECTOR_ELT(sOUT,149,sUNIT_OutreachCost);
	SET_VECTOR_ELT(sOUT,150,sUnitCost_HctVisitCost);
	SET_VECTOR_ELT(sOUT,151,sUnitCost_RapidHivTestCost);
	SET_VECTOR_ELT(sOUT,152,sUnitCost_LinkageCost);
	SET_VECTOR_ELT(sOUT,153,sUnitCost_ImpCareCost);
	SET_VECTOR_ELT(sOUT,154,sUnitCost_PreArtClinicVisitCost);
	SET_VECTOR_ELT(sOUT,155,sUnitCost_LabCd4TestCost);
	SET_VECTOR_ELT(sOUT,156,sUnitCost_PocCd4TestCost);
	SET_VECTOR_ELT(sOUT,157,sUnitCost_AnnualArtCost);
	SET_VECTOR_ELT(sOUT,158,sUnitCost_AnnualAdherenceCost);
	SET_VECTOR_ELT(sOUT,159,sUnitCost_OutreachCost);

	PROTECT(sOUTNAMES = allocVector(VECSXP,160));
	SET_VECTOR_ELT(sOUTNAMES,0,mkChar("sCARE"));
	SET_VECTOR_ELT(sOUTNAMES,1,mkChar("sDALY"));
	SET_VECTOR_ELT(sOUTNAMES,2,mkChar("sCOST"));
	SET_VECTOR_ELT(sOUTNAMES,3,mkChar("sPOP_15to49"));
	SET_VECTOR_ELT(sOUTNAMES,4,mkChar("sHIV_15to49"));
	SET_VECTOR_ELT(sOUTNAMES,5,mkChar("sART_15to49"));
	SET_VECTOR_ELT(sOUTNAMES,6,mkChar("sPOP_15plus"));
	SET_VECTOR_ELT(sOUTNAMES,7,mkChar("sAidsDeath_15plus"));
	SET_VECTOR_ELT(sOUTNAMES,8,mkChar("sPOP_AgeSex_2007"));
	SET_VECTOR_ELT(sOUTNAMES,9,mkChar("sHIV_AgeSex_2007"));
	SET_VECTOR_ELT(sOUTNAMES,10,mkChar("sPOP_NoArtCd4_2007"));
	SET_VECTOR_ELT(sOUTNAMES,11,mkChar("sPOP_AgeSex_2012"));
	SET_VECTOR_ELT(sOUTNAMES,12,mkChar("sHIV_AgeSex_2012"));
	SET_VECTOR_ELT(sOUTNAMES,13,mkChar("sPOP_AgeSex_2014"));
	SET_VECTOR_ELT(sOUTNAMES,14,mkChar("sHIV_AgeSex_2014"));
	SET_VECTOR_ELT(sOUTNAMES,15,mkChar("sCD4_200"));
	SET_VECTOR_ELT(sOUTNAMES,16,mkChar("sCD4_200350"));
	SET_VECTOR_ELT(sOUTNAMES,17,mkChar("sCD4_350500"));
	SET_VECTOR_ELT(sOUTNAMES,18,mkChar("sCD4_500"));
	SET_VECTOR_ELT(sOUTNAMES,19,mkChar("sCD4_200_Art"));
	SET_VECTOR_ELT(sOUTNAMES,20,mkChar("sCD4_200350_Art"));
	SET_VECTOR_ELT(sOUTNAMES,21,mkChar("sCD4_350500_Art"));
	SET_VECTOR_ELT(sOUTNAMES,22,mkChar("sCD4_500_Art"));
	SET_VECTOR_ELT(sOUTNAMES,23,mkChar("sWHO_1"));
	SET_VECTOR_ELT(sOUTNAMES,24,mkChar("sWHO_2"));
	SET_VECTOR_ELT(sOUTNAMES,25,mkChar("sWHO_3"));
	SET_VECTOR_ELT(sOUTNAMES,26,mkChar("sWHO_4"));
	SET_VECTOR_ELT(sOUTNAMES,27,mkChar("sWHO_1_Art"));
	SET_VECTOR_ELT(sOUTNAMES,28,mkChar("sWHO_2_Art"));
	SET_VECTOR_ELT(sOUTNAMES,29,mkChar("sWHO_3_Art"));
	SET_VECTOR_ELT(sOUTNAMES,30,mkChar("sWHO_4_Art"));
	SET_VECTOR_ELT(sOUTNAMES,31,mkChar("sINCIDENCE"));
	SET_VECTOR_ELT(sOUTNAMES,32,mkChar("sPreArtCOST"));
	SET_VECTOR_ELT(sOUTNAMES,33,mkChar("sArtCOST"));
	SET_VECTOR_ELT(sOUTNAMES,34,mkChar("sPreArtCOST_Hiv"));
	SET_VECTOR_ELT(sOUTNAMES,35,mkChar("sArtCOST_Hiv"));
	SET_VECTOR_ELT(sOUTNAMES,36,mkChar("sC1"));
	SET_VECTOR_ELT(sOUTNAMES,37,mkChar("sL21"));
	SET_VECTOR_ELT(sOUTNAMES,38,mkChar("sR3"));
	SET_VECTOR_ELT(sOUTNAMES,39,mkChar("sR8"));
	SET_VECTOR_ELT(sOUTNAMES,40,mkChar("sART1"));
	SET_VECTOR_ELT(sOUTNAMES,41,mkChar("sART4"));
	SET_VECTOR_ELT(sOUTNAMES,42,mkChar("sART5"));
	SET_VECTOR_ELT(sOUTNAMES,43,mkChar("sART6"));
	SET_VECTOR_ELT(sOUTNAMES,44,mkChar("sART9"));
	SET_VECTOR_ELT(sOUTNAMES,45,mkChar("sART10"));
	SET_VECTOR_ELT(sOUTNAMES,46,mkChar("sART11"));
	SET_VECTOR_ELT(sOUTNAMES,47,mkChar("sART12"));
	SET_VECTOR_ELT(sOUTNAMES,48,mkChar("sART13"));
	SET_VECTOR_ELT(sOUTNAMES,49,mkChar("sART14"));
	SET_VECTOR_ELT(sOUTNAMES,50,mkChar("sPre2010"));
	SET_VECTOR_ELT(sOUTNAMES,51,mkChar("sHivArray"));
	SET_VECTOR_ELT(sOUTNAMES,52,mkChar("sDiagArray"));
	SET_VECTOR_ELT(sOUTNAMES,53,mkChar("sArtArray"));
	SET_VECTOR_ELT(sOUTNAMES,54,mkChar("sR3_Counter"));
	SET_VECTOR_ELT(sOUTNAMES,55,mkChar("sR8_Counter"));
	SET_VECTOR_ELT(sOUTNAMES,56,mkChar("sART6_Counter"));
	SET_VECTOR_ELT(sOUTNAMES,57,mkChar("sART10_Counter"));
	SET_VECTOR_ELT(sOUTNAMES,58,mkChar("sART12_Counter"));
	SET_VECTOR_ELT(sOUTNAMES,59,mkChar("sCLINIC"));
	SET_VECTOR_ELT(sOUTNAMES,60,mkChar("sDeath"));
	SET_VECTOR_ELT(sOUTNAMES,61,mkChar("sAidsDeath"));
	SET_VECTOR_ELT(sOUTNAMES,62,mkChar("sDeath_2010_Age"));
	SET_VECTOR_ELT(sOUTNAMES,63,mkChar("sAidsDeath_2010_Age"));
	SET_VECTOR_ELT(sOUTNAMES,64,mkChar("sGuidelines_PopDist_HivNegative"));
	SET_VECTOR_ELT(sOUTNAMES,65,mkChar("sGuidelines_PopDist_500_NeverDiag"));
	SET_VECTOR_ELT(sOUTNAMES,66,mkChar("sGuidelines_PopDist_500_DiagNotInCareNeverCare"));
	SET_VECTOR_ELT(sOUTNAMES,67,mkChar("sGuidelines_PopDist_500_DiagNotInCareEverCare"));
	SET_VECTOR_ELT(sOUTNAMES,68,mkChar("sGuidelines_PopDist_500_InCareNeverArt"));
	SET_VECTOR_ELT(sOUTNAMES,69,mkChar("sGuidelines_PopDist_500_ArtLessSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,70,mkChar("sGuidelines_PopDist_500_ArtMoreSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,71,mkChar("sGuidelines_PopDist_500_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,72,mkChar("sGuidelines_PopDist_350500_NeverDiag"));
	SET_VECTOR_ELT(sOUTNAMES,73,mkChar("sGuidelines_PopDist_350500_DiagNotInCareNeverCare"));
	SET_VECTOR_ELT(sOUTNAMES,74,mkChar("sGuidelines_PopDist_350500_DiagNotInCareEverCare"));
	SET_VECTOR_ELT(sOUTNAMES,75,mkChar("sGuidelines_PopDist_350500_InCareNeverArt"));
	SET_VECTOR_ELT(sOUTNAMES,76,mkChar("sGuidelines_PopDist_350500_ArtLessSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,77,mkChar("sGuidelines_PopDist_350500_ArtMoreSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,78,mkChar("sGuidelines_PopDist_350500_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,79,mkChar("sGuidelines_PopDist_200350_NeverDiag"));
	SET_VECTOR_ELT(sOUTNAMES,80,mkChar("sGuidelines_PopDist_200350_DiagNotInCareNeverCare"));
	SET_VECTOR_ELT(sOUTNAMES,81,mkChar("sGuidelines_PopDist_200350_DiagNotInCareEverCare"));
	SET_VECTOR_ELT(sOUTNAMES,82,mkChar("sGuidelines_PopDist_200350_InCareNeverArt"));
	SET_VECTOR_ELT(sOUTNAMES,83,mkChar("sGuidelines_PopDist_200350_ArtLessSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,84,mkChar("sGuidelines_PopDist_200350_ArtMoreSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,85,mkChar("sGuidelines_PopDist_200350_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,86,mkChar("sGuidelines_PopDist_200_NeverDiag"));
	SET_VECTOR_ELT(sOUTNAMES,87,mkChar("sGuidelines_PopDist_200_DiagNotInCareNeverCare"));
	SET_VECTOR_ELT(sOUTNAMES,88,mkChar("sGuidelines_PopDist_200_DiagNotInCareEverCare"));
	SET_VECTOR_ELT(sOUTNAMES,89,mkChar("sGuidelines_PopDist_200_InCareNeverArt"));
	SET_VECTOR_ELT(sOUTNAMES,90,mkChar("sGuidelines_PopDist_200_ArtLessSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,91,mkChar("sGuidelines_PopDist_200_ArtMoreSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,92,mkChar("sGuidelines_PopDist_200_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,93,mkChar("sGuidelines_Death_HivNegative"));
	SET_VECTOR_ELT(sOUTNAMES,94,mkChar("sGuidelines_Death_500_NeverDiag"));
	SET_VECTOR_ELT(sOUTNAMES,95,mkChar("sGuidelines_Death_500_DiagNotInCareNeverCare"));
	SET_VECTOR_ELT(sOUTNAMES,96,mkChar("sGuidelines_Death_500_DiagNotInCareEverCare"));
	SET_VECTOR_ELT(sOUTNAMES,97,mkChar("sGuidelines_Death_500_InCareNeverArt"));
	SET_VECTOR_ELT(sOUTNAMES,98,mkChar("sGuidelines_Death_500_ArtLessSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,99,mkChar("sGuidelines_Death_500_ArtMoreSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,100,mkChar("sGuidelines_Death_500_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,101,mkChar("sGuidelines_Death_350500_NeverDiag"));
	SET_VECTOR_ELT(sOUTNAMES,102,mkChar("sGuidelines_Death_350500_DiagNotInCareNeverCare"));
	SET_VECTOR_ELT(sOUTNAMES,103,mkChar("sGuidelines_Death_350500_DiagNotInCareEverCare"));
	SET_VECTOR_ELT(sOUTNAMES,104,mkChar("sGuidelines_Death_350500_InCareNeverArt"));
	SET_VECTOR_ELT(sOUTNAMES,105,mkChar("sGuidelines_Death_350500_ArtLessSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,106,mkChar("sGuidelines_Death_350500_ArtMoreSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,107,mkChar("sGuidelines_Death_350500_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,108,mkChar("sGuidelines_Death_200350_NeverDiag"));
	SET_VECTOR_ELT(sOUTNAMES,109,mkChar("sGuidelines_Death_200350_DiagNotInCareNeverCare"));
	SET_VECTOR_ELT(sOUTNAMES,110,mkChar("sGuidelines_Death_200350_DiagNotInCareEverCare"));
	SET_VECTOR_ELT(sOUTNAMES,111,mkChar("sGuidelines_Death_200350_InCareNeverArt"));
	SET_VECTOR_ELT(sOUTNAMES,112,mkChar("sGuidelines_Death_200350_ArtLessSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,113,mkChar("sGuidelines_Death_200350_ArtMoreSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,114,mkChar("sGuidelines_Death_200350_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,115,mkChar("sGuidelines_Death_200_NeverDiag"));
	SET_VECTOR_ELT(sOUTNAMES,116,mkChar("sGuidelines_Death_200_DiagNotInCareNeverCare"));
	SET_VECTOR_ELT(sOUTNAMES,117,mkChar("sGuidelines_Death_200_DiagNotInCareEverCare"));
	SET_VECTOR_ELT(sOUTNAMES,118,mkChar("sGuidelines_Death_200_InCareNeverArt"));
	SET_VECTOR_ELT(sOUTNAMES,119,mkChar("sGuidelines_Death_200_ArtLessSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,120,mkChar("sGuidelines_Death_200_ArtMoreSixMonths"));
	SET_VECTOR_ELT(sOUTNAMES,121,mkChar("sGuidelines_Death_200_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,122,mkChar("sGuidelines_Art_500"));
	SET_VECTOR_ELT(sOUTNAMES,123,mkChar("sGuidelines_Art_350500"));
	SET_VECTOR_ELT(sOUTNAMES,124,mkChar("sGuidelines_Art_200350"));
	SET_VECTOR_ELT(sOUTNAMES,125,mkChar("sGuidelines_Art_200"));
	SET_VECTOR_ELT(sOUTNAMES,126,mkChar("sGuidelines_NewInfectionsAdult"));
	SET_VECTOR_ELT(sOUTNAMES,127,mkChar("sGuidelines_NewDiagnoses"));
	SET_VECTOR_ELT(sOUTNAMES,128,mkChar("sGuidelines_PreArtDropout"));
	SET_VECTOR_ELT(sOUTNAMES,129,mkChar("sGuidelines_ArtDropout"));
	SET_VECTOR_ELT(sOUTNAMES,130,mkChar("sIn2014"));
	SET_VECTOR_ELT(sOUTNAMES,131,mkChar("sMid2010"));
	SET_VECTOR_ELT(sOUTNAMES,132,mkChar("sPie_1"));
	SET_VECTOR_ELT(sOUTNAMES,133,mkChar("sPie_2"));
	SET_VECTOR_ELT(sOUTNAMES,134,mkChar("sPie_3"));
	SET_VECTOR_ELT(sOUTNAMES,135,mkChar("sDALY_OffArt"));
	SET_VECTOR_ELT(sOUTNAMES,136,mkChar("sDALY_OnArt"));
	SET_VECTOR_ELT(sOUTNAMES,137,mkChar("sDALY_LYL"));
	SET_VECTOR_ELT(sOUTNAMES,138,mkChar("sPOP"));
	SET_VECTOR_ELT(sOUTNAMES,139,mkChar("sCARE_PT"));
	SET_VECTOR_ELT(sOUTNAMES,140,mkChar("sUNIT_HctVisitCost"));
	SET_VECTOR_ELT(sOUTNAMES,141,mkChar("sUNIT_RapidHivTestCost"));
	SET_VECTOR_ELT(sOUTNAMES,142,mkChar("sUNIT_LinkageCost"));
	SET_VECTOR_ELT(sOUTNAMES,143,mkChar("sUNIT_ImpCareCost"));
	SET_VECTOR_ELT(sOUTNAMES,144,mkChar("sUNIT_PreArtClinicVisitCost"));
	SET_VECTOR_ELT(sOUTNAMES,145,mkChar("sUNIT_LabCd4TestCost"));
	SET_VECTOR_ELT(sOUTNAMES,146,mkChar("sUNIT_PocCd4TestCost"));
	SET_VECTOR_ELT(sOUTNAMES,147,mkChar("sUNIT_AnnualArtCost"));
	SET_VECTOR_ELT(sOUTNAMES,148,mkChar("sUNIT_AnnualAdherenceCost"));
	SET_VECTOR_ELT(sOUTNAMES,149,mkChar("sUNIT_OutreachCost"));
	SET_VECTOR_ELT(sOUTNAMES,150,mkChar("sUnitCost_HctVisitCost"));
	SET_VECTOR_ELT(sOUTNAMES,151,mkChar("sUnitCost_RapidHivTestCost"));
	SET_VECTOR_ELT(sOUTNAMES,152,mkChar("sUnitCost_LinkageCost"));
	SET_VECTOR_ELT(sOUTNAMES,153,mkChar("sUnitCost_ImpCareCost"));
	SET_VECTOR_ELT(sOUTNAMES,154,mkChar("sUnitCost_PreArtClinicVisitCost"));
	SET_VECTOR_ELT(sOUTNAMES,155,mkChar("sUnitCost_LabCd4TestCost"));
	SET_VECTOR_ELT(sOUTNAMES,156,mkChar("sUnitCost_PocCd4TestCost"));
	SET_VECTOR_ELT(sOUTNAMES,157,mkChar("sUnitCost_AnnualArtCost"));
	SET_VECTOR_ELT(sOUTNAMES,158,mkChar("sUnitCost_AnnualAdherenceCost"));
	SET_VECTOR_ELT(sOUTNAMES,159,mkChar("sUnitCost_OutreachCost"));
	namesgets(sOUT,sOUTNAMES);

	UNPROTECT(176);
	return(sOUT);
	}

/////////////////////

}
