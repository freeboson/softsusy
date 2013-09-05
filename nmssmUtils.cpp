
#include "nmssmUtils.h"
#include "nmssmsoftsusy.h"
#include "def.h"
#include "utils.h"

#include <cassert>
#include <sstream>

char const * const NMSSM_input::parameter_names[NUMBER_OF_NMSSM_INPUT_PARAMETERS] = {
   "tanBeta", "mHd2", "mHu2", "mu", "BmuOverCosBetaSinBeta", "lambda",
   "kappa", "Alambda", "Akappa", "lambda*S", "xiF", "xiS", "muPrime",
   "mPrimeS2", "mS2"
};

NMSSM_input::NMSSM_input()
  : parameter()    // sets all parameters to zero
  , has_been_set() // sets all values to zero (false)
{}

void NMSSM_input::set(NMSSM_parameters par, double value) {
   assert(par < NUMBER_OF_NMSSM_INPUT_PARAMETERS);
   parameter[par] = value;
   has_been_set[par] = true;
}

double NMSSM_input::get(NMSSM_parameters par) const {
   assert(par < NUMBER_OF_NMSSM_INPUT_PARAMETERS);
   return parameter[par];
}

DoubleVector NMSSM_input::get_nmpars() const {
   DoubleVector nmpars(5);
   nmpars(1) = get(NMSSM_input::lambda);
   nmpars(2) = get(NMSSM_input::kappa);
   if (is_set(NMSSM_input::lambdaS)) {
      if (!close(get(NMSSM_input::lambda),0.,EPSTOL)) {
         nmpars(3) = get(NMSSM_input::lambdaS) / get(NMSSM_input::lambda);
      } else {
         std::string msg =
            "# Error: you set lambda * <S> to a non-zero value"
            ", but lambda is zero.  "
            "Please set lambda (EXTPAR entry 61) to a non-zero value.";
         throw msg;
      }
   }
   nmpars(4) = get(NMSSM_input::xiF);
   nmpars(5) = get(NMSSM_input::muPrime);
   return nmpars;
};

bool NMSSM_input::is_set(NMSSM_parameters par) const {
   assert(par < NUMBER_OF_NMSSM_INPUT_PARAMETERS);
   return has_been_set[par];
}

bool NMSSM_input::is_Z3_symmetric() const {
   return (!is_set(mu)      || close(parameter[mu]      , 0., EPSTOL))
      && (!is_set(BmuOverCosBetaSinBeta)
          || close(parameter[BmuOverCosBetaSinBeta], 0., EPSTOL))
      && (!is_set(muPrime)  || close(parameter[muPrime] , 0., EPSTOL))
      && (!is_set(mPrimeS2) || close(parameter[mPrimeS2], 0., EPSTOL))
      && (!is_set(xiF)      || close(parameter[xiF]     , 0., EPSTOL));
}

void NMSSM_input::check_setup() {
   check_ewsb_output_parameters();
}

void NMSSM_input::check_ewsb_output_parameters() const {
   bool supported = false;

   // check supported cases
   const bool Z3_symmetric = is_Z3_symmetric();
   if (Z3_symmetric) {
      if (!is_set(lambdaS) && !is_set(kappa) && !is_set(mS2))
         supported = true;
   } else {
      if (!is_set(mu) && !is_set(BmuOverCosBetaSinBeta) && !is_set(xiS))
         supported = true;
   }

   if (!supported) {
      std::ostringstream msg;
      msg << "# Error: no combination of the following unset parameters is"
         " currently supported as EWSB output for a Z3 "
          << (Z3_symmetric ? "symmetric" : "violating") << " NMSSM: ";
      for (unsigned i = 0; i < NUMBER_OF_NMSSM_INPUT_PARAMETERS; i++) {
         if (!is_set(static_cast<NMSSM_parameters>(i)))
            msg << parameter_names[i] << ", ";
      }
      msg << "\n" "# Note: supported are: "
          << (Z3_symmetric ? "{lambda*S, kappa, mS^2}" : "{mu, Bmu, xi_S}")
          << '\n';
      throw msg.str();
   }
}

std::ostream& operator<<(std::ostream& lhs, const NMSSM_input& rhs) {
   for (unsigned i = 0; i < NMSSM_input::NUMBER_OF_NMSSM_INPUT_PARAMETERS; i++) {
      if (rhs.is_set(static_cast<NMSSM_input::NMSSM_parameters>(i))) {
         lhs << rhs.parameter_names[i] << " = "
             << rhs.get(static_cast<NMSSM_input::NMSSM_parameters>(i)) << ", ";
      }
   }
   return lhs;
}

/// User supplied routine. Inputs m at the unification scale, and uses
/// inputParameters vector to output m with high energy soft boundary
/// conditions.
void NmssmMsugraBcs(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  double m0 = inputParameters.display(1);
  double m12 = inputParameters.display(2);
  double a0 = inputParameters.display(3);

  /// Sets scalar soft masses equal to m0, fermion ones to m12 and sets the
  /// trilinear scalar coupling to be a0
  m.standardSugra(m0, m12, a0);
}

//PA: msugra bcs in the mssm limit of the general nmssm
void MssmMsugraBcs(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  double m0 = inputParameters.display(1);
  double m12 = inputParameters.display(2);
  double a0 = inputParameters.display(3);

  /// Sets scalar soft masses equal to m0, fermion ones to m12 and sets the
  /// trilinear scalar coupling to be a0
  m.standardsemiSugra(m0, m12, a0, 0.0, 1e-15);
  m.setMspSquared(1e6);
}

//PA: semi-msugra bcs for the nmssm
void SemiMsugraBcs(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  double m0 = inputParameters.display(1);
  double m12 = inputParameters.display(2);
  double a0 = inputParameters.display(3);
  double Al = inputParameters.display(4);
  double Ak = inputParameters.display(5);

  /// Sets scalar soft masses equal to m0, fermion ones to m12 and sets the
  /// trilinear scalar coupling to be a0
  m.standardsemiSugra(m0, m12, a0, Al, Ak);
}

void generalNmssmBcs(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  NmssmSusy s; SoftParsNmssm r;
  s = m.displaySusy();
  r.set(inputParameters);

  if (Z3 == false) {
    double m3sq = m.displayM3Squared();
    double XiS = m.displayXiS();
    r.setM3Squared(m3sq);
    r.setXiS(XiS);
  } else {
    double mSsq = m.displayMsSquared();
    r.setMsSquared(mSsq);
  }

  m.setSoftPars(r);
  m.setSusy(s);
}


/// This one doesn't overwrite mh1sq or mh2sq at the high scale.  For cases where the soft scalar Higgs masses are set in EWSB.
void generalNmssmBcs2(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  NmssmSusy s; SoftParsNmssm r;
  double mh1sq = m.displayMh1Squared();
  double mh2sq = m.displayMh2Squared();
  double mSsq = m.displayMsSquared();
  double m3sq = m.displayM3Squared();
  s = m.displaySusy();
  r.set(inputParameters);
  r.setMh1Squared(mh1sq);
  r.setMh2Squared(mh2sq);
  r.setM3Squared(m3sq);
  r.setMsSquared(mSsq);
  m.setSoftPars(r);
  m.setSusy(s);
}

void extendedNMSugraBcs(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  for (int i=1; i<=3; i++)
     m.setGauginoMass(i, inputParameters.display(i));
  if (inputParameters.display(25) > 1. && m.displaySetTbAtMX())
    m.setTanb(inputParameters.display(25));
  m.setTrilinearElement(UA, 1, 1, m.displayYukawaElement(YU, 1, 1) *
			inputParameters.display(11));
  m.setTrilinearElement(UA, 2, 2, m.displayYukawaElement(YU, 2, 2) *
			inputParameters.display(11));
  m.setTrilinearElement(UA, 3, 3, m.displayYukawaElement(YU, 3, 3) *
			inputParameters.display(11));
  m.setTrilinearElement(DA, 1, 1, m.displayYukawaElement(YD, 1, 1) *
			inputParameters.display(12));
  m.setTrilinearElement(DA, 2, 2, m.displayYukawaElement(YD, 2, 2) *
			inputParameters.display(12));
  m.setTrilinearElement(DA, 3, 3, m.displayYukawaElement(YD, 3, 3) *
			inputParameters.display(12));
  m.setTrilinearElement(EA, 1, 1, m.displayYukawaElement(YE, 1, 1) *
			inputParameters.display(13));
  m.setTrilinearElement(EA, 2, 2, m.displayYukawaElement(YE, 2, 2) *
			inputParameters.display(13));
  m.setTrilinearElement(EA, 3, 3, m.displayYukawaElement(YE, 3, 3) *
			inputParameters.display(13));
  m.setSoftMassElement(mLl, 1, 1, signedSqr(inputParameters.display(31)));
  m.setSoftMassElement(mLl, 2, 2, signedSqr(inputParameters.display(32)));
  m.setSoftMassElement(mLl, 3, 3, signedSqr(inputParameters.display(33)));
  m.setSoftMassElement(mEr, 1, 1, signedSqr(inputParameters.display(34)));
  m.setSoftMassElement(mEr, 2, 2, signedSqr(inputParameters.display(35)));
  m.setSoftMassElement(mEr, 3, 3, signedSqr(inputParameters.display(36)));
  m.setSoftMassElement(mQl, 1, 1, signedSqr(inputParameters.display(41)));
  m.setSoftMassElement(mQl, 2, 2, signedSqr(inputParameters.display(42)));
  m.setSoftMassElement(mQl, 3, 3, signedSqr(inputParameters.display(43)));
  m.setSoftMassElement(mUr, 1, 1, signedSqr(inputParameters.display(44)));
  m.setSoftMassElement(mUr, 2, 2, signedSqr(inputParameters.display(45)));
  m.setSoftMassElement(mUr, 3, 3, signedSqr(inputParameters.display(46)));
  m.setSoftMassElement(mDr, 1, 1, signedSqr(inputParameters.display(47)));
  m.setSoftMassElement(mDr, 2, 2, signedSqr(inputParameters.display(48)));
  m.setSoftMassElement(mDr, 3, 3, signedSqr(inputParameters.display(49)));
  m.setMh1Squared(inputParameters.display(21));
  m.setMh2Squared(inputParameters.display(22));

  m.setTrialambda(m.displayLambda() * inputParameters.display(50));
  m.setTriakappa(m.displayKappa() * inputParameters.display(51));

  if (Z3 == false) {
    m.setMspSquared(inputParameters.display(52) * m.displayMupr());
    m.setMsSquared(signedSqr(inputParameters.display(53)));
  }
}

//This won't work for Z3 == true until we allow mS not to be set EWSB consitions
void nuhmINM(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  double m0 = inputParameters.display(1);
  double m12 = inputParameters.display(2);
  double mH  = inputParameters.display(3);
  double A0 = inputParameters.display(4);

  double Al = inputParameters.display(5);
  double Ak = inputParameters.display(6);
  /// Sets scalar soft masses equal to m0, fermion ones to m12 and sets the
  /// trilinear scalar coupling to be A0
  ///  if (m0 < 0.0) m.flagTachyon(true); Deleted on request from A Pukhov
  m.standardsemiSugra(m0, m12, A0, Al, Ak);

  m.setMh1Squared(mH * mH); m.setMh2Squared(mH * mH);
  m.setMsSquared(mH * mH);
  m.setTrialambda(m.displayLambda() * Al);
  m.setTriakappa(m.displayKappa() * Ak);
  if(Z3 == false) {
 m.setMspSquared(inputParameters.display(inputParameters.display(52) * m.displayMupr()  ));
  }
}

void nuhmIINM(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  double m0 = inputParameters.display(1);
  double m12 = inputParameters.display(2);
  double mH1  = inputParameters.display(3);
  double mH2  = inputParameters.display(4);
  double A0 = inputParameters.display(5);
  double mS = 0.0;
  if (Z3 == false)
     mS = inputParameters.display(6);
  double Al = inputParameters.display(5);
  double Ak = inputParameters.display(6);
  m.standardsemiSugra(m0, m12, A0, Al, Ak);

  m.setMh1Squared(mH1 * mH1); m.setMh2Squared(mH2 * mH2);
  if (Z3 == false)
     m.setMsSquared(mS * mS);
  m.setTrialambda(m.displayLambda() * Al);
  m.setTriakappa(m.displayKappa() * Ak);
  if (Z3 == false) {
    m.setMspSquared(inputParameters.display(inputParameters.display(52) * m.displayMupr()  ));
  }
}

//PA: anomally mediation Bcs with an extra universal m0 contribution.
void amsbBcs(NmssmSoftsusy & m, const DoubleVector & inputParameters) {
  double m32 = inputParameters.display(1);
  double m0 = inputParameters.display(2);

  m.standardSugra(m0, 0., 0.);
  m.addAmsb(m32);
}
