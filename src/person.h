//
//  person.h
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__person__
#define __priorityQ__person__

#include <stdio.h>
#include "population.h"

class person {
public:
	person(population * thePop,const double Time); //constuctor
	virtual ~person(); //destructor
	
	/* Initialiser functions */
	bool AssignGender();
	void AssignInitialAge(const double Time);
	double GenerateNatDeathAge();
	double AssignNatDeathDate(const double Time);
	
	/////////////
	/* Methods */
	/////////////
	void Kill(const double theTime, const bool theCause);
	void SetAge(const double theTime);
	
	/* Hiv Acquisition Functions */
	void Hiv(const double theTime);
	void SetSeroStatus(const bool theState) { seroStatus = theState; }
	void SetSeroconversionDay(const double Time) { seroconversionDay = Time; }
	void SetHivIndicators();
	void SetInitialCd4Count();
	void SetInitialWhoStage();
	
	/* Hiv Progression Functions */
	void ScheduleHivIndicatorUpdate(const double theTime);
	void SetCurrentCd4Count(unsigned int theCount) { currentCd4 = theCount; }
	void SetCurrentWhoStage(unsigned int theStage) { currentWho = theStage; }
	double GenerateHivDeathDate(const double theTime); //function returns the HivDeathDate Value;
	void AssignHivDeathDate(const double theTime); //function creates the Death event.
	
	/* Hiv Care Functions */
	void SetDiagnosedState(const bool theState, unsigned int theRoute, const double theTime);
	void SetEverCd4TestState(const bool theState) { everCd4Test = theState; cd4TestCount++; calCd4TestCount++; }
	void SetEverCd4TestResultState(const bool theState);
	void SetInCareState(const bool theState, const double theTime);
	void SetArtInitiationState(const bool theState, const double theTime);
	void SetArtAdherenceState(const double theProb);
	void SetArtAtEnrollment(const bool theState) { artAtEnrollment = theState; }
	
	/* Natural History Date Setting Functions */
	void SetHivDate(double theDate) { hivDate = theDate; }
	void SetHivDeathDate(double theDate) { hivDeathDate = theDate; }
	void SetCd4DeclineDate(double theDate) { cd4DeclineDate = theDate; }
	void SetCd4RecoverDate(double theDate) { cd4RecoverDate = theDate; }
	void SetWhoDeclineDate(double theDate) { whoDeclineDate = theDate; }
	void SetWhoRecoverDate(double theDate) { whoRecoverDate = theDate; }
	
	/* Hiv Care Date Setting Functions */
	void SetHctHivTestDate(double theDate) { hctHivTestDate = theDate; }
	void SetVctHivTestDate(double theDate) { vctHivTestDate = theDate; }
	void SetPictHivTestDate(double theDate) { pictHivTestDate = theDate; }
	
	/* Update Tx Guidelines */
	void UpdateTxGuidelines(unsigned int theCd4, unsigned int theWho) { cd4Tx = theCd4; whoTx = theWho; }
	
	/* Daly Functions */
	void SetDalys(const double theValue) { iDALY += theValue; }
	void SetDalys_OffArt(const double theValue) { iDALY_OffArt += theValue; }
	void SetDalys_OnArt(const double theValue) { iDALY_OnArt += theValue; }
	void SetDalys_LYL(const double theValue) { iDALY_LYL += theValue; }
	void ResetDalys() { iDALY = 0; iDALY_OffArt = 0; iDALY_OnArt = 0; iDALY_LYL = 0; }
	
	/* Cost Functions */
	void SetHctVisitCost(const double theCost) { iHctVisitCost += theCost; }
	void SetRapidHivTestCost(const double theCost) { iRapidHivTestCost += theCost; }
	void SetPreArtClinicVisitCost(const double theCost) { iPreArtClinicVisitCost += theCost; }
	void SetLabCd4TestCost(const double theCost) { iLabCd4TestCost += theCost; }
	void SetPocCd4TestCost(const double theCost) { iPocCd4TestCost += theCost; }
	void SetAnnualArtCost(const double theCost) { iAnnualArtCost += theCost; }
	void SetAnnualAdherenceCost(const double theCost) { iAdherenceCost += theCost; }
	void SetArtOutreachCost(const double theCost) { iArtOutreachCost += theCost; }
	void SetPreArtOutreachCost(const double theCost) { iPreArtOutreachCost += theCost; }
	void SetLinkageCost(const double theCost) { iLinkageCost += theCost; }
	void SetImpCareCost(const double theCost) { iImpCareCost += theCost; }
	void ResetCost() { iHctVisitCost = 0; iRapidHivTestCost = 0; iPreArtClinicVisitCost = 0; iLabCd4TestCost = 0; iPocCd4TestCost = 0; iAnnualArtCost = 0; iAdherenceCost = 0; iArtOutreachCost = 0; iPreArtOutreachCost = 0; artTime = 0; diagNotLinkedTime = 0; iLinkageCost = 0; iImpCareCost = 0; }
	
	/* Cost Unit Functions */
	void SetHctVisitUnit(const double theUnit) { iHctVisitUnit += theUnit; }
	void SetRapidHivTestUnit(const double theUnit) { iRapidHivTestUnit += theUnit; }
	void SetPreArtClinicVisitUnit(const double theUnit) { iPreArtClinicVisitUnit += theUnit; }
	void SetLabCd4TestUnit(const double theUnit) { iLabCd4TestUnit += theUnit; }
	void SetPocCd4TestUnit(const double theUnit) { iPocCd4TestUnit += theUnit; }
	void SetAnnualArtUnit(const double theUnit) { iAnnualArtUnit += theUnit; }
	void SetAnnualAdherenceUnit(const double theUnit) { iAdherenceUnit += theUnit; }
	void SetArtOutreachUnit(const double theUnit) { iArtOutreachUnit += theUnit; }
	void SetPreArtOutreachUnit(const double theUnit) { iPreArtOutreachUnit += theUnit; }
	void SetLinkageUnit(const double theUnit) { iLinkageUnit += theUnit; }
	void SetImpCareUnit(const double theUnit) { iImpCareUnit += theUnit; }
	void ResetUnit() { iHctVisitUnit = 0; iRapidHivTestUnit = 0; iPreArtClinicVisitUnit = 0; iLabCd4TestUnit = 0; iPocCd4TestUnit = 0; iAnnualArtUnit = 0; iAdherenceUnit = 0; iArtOutreachUnit = 0; iPreArtOutreachUnit = 0; iLinkageUnit = 0; iImpCareUnit = 0; }
	
	/* Vector functions */
	void SetPersonIndex(const size_t theIndex) { personIndex = theIndex; }
	void SetRowIndex(const size_t theIndex) { rowIndex = theIndex; }
	void SetVectorUpdateDate(const double theDate) { vectorUpdateDate = theDate; }
	void SetInfectiousnessIndex(const size_t theIndex) { infectiousnessIndex = theIndex; }
	
	/* Population function */
	void UpdatePopulation() { iPop->UpdateVector(this); }
	void UpdateInfectiousnessArray() { iPop->UpdateArray(this); }

	/* Person-time functions */
	void SetLastUpdateTime(const double theTime) { lastUpdateTime = theTime; }
	
	//////////////////////
	/* Accessor methods */
	//////////////////////
	bool GetGender() const;
	double GetNatDeathDate() const;
	bool Alive() const;
	double GetAge(const double theTime);
	const double GetBirthDay() const { return birthDay; }
	unsigned int GetCurrentCd4() const { return currentCd4; }
	unsigned int GetCurrentWho() const { return currentWho; }
	
	/* Hiv Care Flag Getting Functions */
	bool GetDiagnosedState() const { return diagnosed; }
	unsigned int GetDiagnosisCount() const { return diagnosisCount; }
	unsigned int GetDiagnosisRoute() const { return diagnosisRoute; }
	bool GetEverCd4TestState() const { return everCd4Test; }
	unsigned int GetCd4TestCount() const { return cd4TestCount; }
	bool GetEverCd4TestResultState() const { return everCd4TestResult; }
	bool GetEligible() const { if(currentCd4 <= cd4Tx || currentWho >= whoTx) return true; else return false; }
	bool GetWhoEligible() const { if(currentWho >= whoTx) return true; else return false; }
	bool GetInCareState() const { return inCare; }
	bool GetEverCareState() const { return everCare; }
	bool GetArtInitiationState() const { return art; }
	bool GetArtAdherenceState() const { return adherence; }
	bool GetEverArt() const { return everArt; }
	bool GetSeroStatus() const { return seroStatus; }
	double GetSeroconversionDay() const { return seroconversionDay; }
	double GetArtDay() const { return artDay; }
	double GetArtTime() const { return artTime; }
	double GetDiagNotLinkedTime() const { return diagNotLinkedTime; }
	bool GetEverReturnCare() const { return everReturnPreArtCare; }
	bool GetEligibleAtReturnCare() const { return eligibleAtReturnPreArtCare; }
	
	/* Hiv Care Date Getting Functions */
	double GetHivDate() const { return hivDate; }
	double GetHivDeathDate() const { return hivDeathDate; }
	double GetCd4DeclineDate() const { return cd4DeclineDate; }
	double GetCd4RecoverDate() const { return cd4RecoverDate; }
	double GetWhoDeclineDate() const { return whoDeclineDate; }
	double GetWhoRecoverDate() const { return whoRecoverDate; }
	
	/* Hiv Care Date Getting Functions */
	double GetHctHivTestDate() const { return hctHivTestDate; }
	double GetVctHivTestDate() const { return vctHivTestDate; }
	double GetPictHivTestDate() const { return pictHivTestDate; }
	
	/* Tx Guideline Getting Functions */
	unsigned int GetCd4TxGuideline() const { return cd4Tx; }
	unsigned int GetWhoTxGuideline() const { return whoTx; }
	
	/* Daly Functions */
	double GetDalys() const { return iDALY; }
	double GetDalys_OffArt() const { return iDALY_OffArt; }
	double GetDalys_OnArt() const { return iDALY_OnArt; }
	double GetDalys_LYL() const { return iDALY_LYL; }
	
	/* Cost Functions */
	double GetHctVisitCost() const { return iHctVisitCost; }
	double GetRapidHivTestCost() const { return iRapidHivTestCost; }
	double GetPreArtClinicVisitCost() const { return iPreArtClinicVisitCost; }
	double GetLabCd4TestCost() const { return iLabCd4TestCost; }
	double GetPocCd4TestCost() const { return iPocCd4TestCost; }
	double GetAnnualArtCost() const { return iAnnualArtCost; }
	double GetAnnualAdherenceCost() const { return iAdherenceCost; }
	double GetArtOutreachCost() const { return iArtOutreachCost; }
	double GetPreArtOutreachCost() const { return iPreArtOutreachCost; }
	double GetLinkageCost() const { return iLinkageCost; }
	double GetImpCareCost() const { return iImpCareCost; }

	/* Cost Unit Functions */
	double GetHctVisitUnit() const { return iHctVisitUnit; }
	double GetRapidHivTestUnit() const { return iRapidHivTestUnit; }
	double GetPreArtClinicVisitUnit() const { return iPreArtClinicVisitUnit; }
	double GetLabCd4TestUnit() const { return iLabCd4TestUnit; }
	double GetPocCd4TestUnit() const { return iPocCd4TestUnit; }
	double GetAnnualArtUnit() const { return iAnnualArtUnit; }
	double GetAnnualAdherenceUnit() const { return iAdherenceUnit; }
	double GetArtOutreachUnit() const { return iArtOutreachUnit; }
	double GetPreArtOutreachUnit() const { return iPreArtOutreachUnit; }
	double GetLinkageUnit() const { return iLinkageUnit; }
	double GetImpCareUnit() const { return iImpCareUnit; }
	
	/* Output functions */
	bool GetHivDeath() const { return hivDeath; }
	bool GetArtDeath() const { return artDeath; }
	unsigned int GetCd4AtArt() const { return cd4AtArt; }
	unsigned int GetArtCount() const { return artCount; }
	
	/* Vector function */
	size_t GetPersonIndex() const { return personIndex; }
	size_t GetRowIndex() const { return rowIndex; }
	size_t GetInfectiousnessIndex() const { return infectiousnessIndex; }
	double GetVectorUpdateDate() const { return vectorUpdateDate; }
	
	/* Calibration functions */
	void ResetCalibration();
	bool GetCalEverDiag() const { return calEverDiag; }
	double GetCalDiagDay() const { return calDiagDay; }
	unsigned int GetCalDiagRoute() const { return calDiagRoute; }
	unsigned int GetLastDiagnosisRoute() const { return lastDiagnosisRoute; }
	bool GetCalEverCare() const { return calEverCare; }
	double GetCalCareDay() const { return calCareDay; }
	unsigned int GetCalCareRoute() const { return calCareRoute; }
	unsigned int GetCalCd4EntryCare() const { return calCd4EntryCare; }
	unsigned int GetCalCd4TestCount() const { return calCd4TestCount; }
	unsigned int GetSecondaryCd4() const { return secondaryCd4; }
	bool GetCalEverArt() const { return calEverArt; }
	double GetCalArtDay() const { return calArtDay; }
	unsigned int GetCalCd4AtArt() const { return calCd4AtArt; }
	unsigned int GetCalAtArtCareRoute() const { return calAtArtCareRoute; }
	unsigned int GetCalAtArtPreArtVisitCount() const { return calAtArtPreArtVisitCount; }
	bool GetCalAtArtEverReturnCare() const { return calAtArtEverReturnPreArtCare; }
	bool GetCalAtArtEligibleAtReturnCare() const { return calAtArtEligibleAtReturnPreArtCare; }
	bool GetArtAtEnrollment() const { return artAtEnrollment; }
	bool GetCalEverReturnArt() const { return calEverReturnArt; }
	bool GetCalEligibleAtEnrollment() const { return calEligibleAtEnrollment; }

	/* Person-time functions */
	double GetLastUpdateTime() const { return lastUpdateTime; }
	
private:
	/* Basic characteristics */
	bool gender;
	double currentAge;
	double initialAge;
	double natDeathDate;
	
	/* Hiv status */
	bool seroStatus;
	double seroconversionDay;
	unsigned int currentCd4;
	unsigned int initialCd4;
	unsigned int currentWho;
	unsigned int initialWho;
	
	/* Day = time an event occured */
	double deathDay;
	const double birthDay;
	double artDay;
	double artTime;
	double diagDay;
	double careDay;
	double initArtDay;
	double lostArtDay;
	double lastUpdateTime;
	double diagNotLinkedTime;
	
	/* Date = time an event will occur */
	double hivDate;
	double hivDeathDate;
	double cd4DeclineDate;
	double cd4RecoverDate;
	double whoDeclineDate;
	double whoRecoverDate;
	double vectorUpdateDate;
	
	/* Hiv test dates */
	double hctHivTestDate;
	double vctHivTestDate;
	double pictHivTestDate;
	
	/* Hiv care flags */
	bool diagnosed;
	unsigned int diagnosisCount;
	unsigned int diagnosisRoute; //1 = Hct, 2 = Vct, 3 = Pict.
	unsigned int lastDiagnosisRoute;
	double lastDiagnosisDay;
	bool inCare;
	bool everCare;
	bool everCd4Test;
	unsigned int cd4TestCount;
	bool everCd4TestResult;
	unsigned int cd4TestResultCount;
	unsigned int secondaryCd4;
	bool everLostPreArtCare;
	bool everReturnPreArtCare;
	bool eligibleAtReturnPreArtCare;
	bool art;
	bool everArt;
	bool artAtEnrollment;
	unsigned int artCount;
	bool everLostArt;
	bool everReturnArt;
	bool adherence;
	
	/* Ouput info */
	unsigned int cd4AtArt;
	bool hivDeath;
	bool artDeath;
	
	/* Tx Guidelines */
	unsigned int cd4Tx;
	unsigned int whoTx;
	
	/* DALY */
	double iDALY;
	double iDALY_OffArt;
	double iDALY_OnArt;
	double iDALY_LYL;
	
	/* COST */
	double iHctVisitCost;
	double iRapidHivTestCost;
	double iPreArtClinicVisitCost;
	double iLabCd4TestCost;
	double iPocCd4TestCost;
	double iAnnualArtCost;
	double iAdherenceCost;
	double iArtOutreachCost;
	double iPreArtOutreachCost;
	double iLinkageCost;
	double iImpCareCost;

	/* COST UNIT */
	double iHctVisitUnit;
	double iRapidHivTestUnit;
	double iPreArtClinicVisitUnit;
	double iLabCd4TestUnit;
	double iPocCd4TestUnit;
	double iAnnualArtUnit;
	double iAdherenceUnit;
	double iArtOutreachUnit;
	double iPreArtOutreachUnit;
	double iLinkageUnit;
	double iImpCareUnit;
	
	/* Data */
	population * const iPop;
	size_t personIndex;
	size_t rowIndex;
	size_t infectiousnessIndex;
	
	/* Calibration */
	bool calEverDiag;
	double calDiagDay;
	unsigned int calDiagRoute;
	bool calEverCare;
	double calCareDay;
	unsigned int calCareRoute;
	unsigned int calCd4EntryCare;
	unsigned int calCd4TestCount;
	bool calEverArt;
	double calArtDay;
	unsigned int calCd4AtArt;
	unsigned int calAtArtCareRoute;
	unsigned int calAtArtPreArtVisitCount;
	bool calAtArtEverReturnPreArtCare;
	bool calAtArtEligibleAtReturnPreArtCare;
	bool calEverReturnArt;
	bool calEligibleAtEnrollment;
};

#endif /* defined(__priorityQ__person__) */