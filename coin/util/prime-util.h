/*######     Copyright (c) 1997-2013 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com #######################################
#                                                                                                                                                                          #
# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;  #
# either version 3, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      #
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU #
# General Public License along with this program; If not, see <http://www.gnu.org/licenses/>                                                                               #
##########################################################################################################################################################################*/

#pragma once

#include <el/bignum.h>

#include <el/num/mod.h>
#include <el/num/prime.h>
using namespace Ext::Num;

#include "util.h"

namespace Coin {

const size_t DEFAULT_SIEVE_SIZE = 1024000;
const size_t MAX_SIEVE_SIZE = min(PRIME_LIMIT, size_t(20*1000*1000));

const int FRACTIONAL_BITS = 24;

extern const BigInteger PRIME_MIN;

const BigInteger& GetPrimeMax();


ENUM_CLASS(PrimeChainType) {
    Cunningham1 = 0,					// values used in XPT protocol
	Cunningham2 = 1,
	Twin = 2,
	Unknown = 255
} END_ENUM_CLASS(PrimeChainType);

BigInteger HashValueToBigInteger(const HashValue& hash);

struct CunninghamLengths {
	double Cunningham1Length,
		Cunningham2Length,
		TwinLength;

	CunninghamLengths()
		:	Cunningham1Length(0)
		,	Cunningham2Length(0)
		,	TwinLength(0)
	{}

	bool TargetAchieved(double target) const {
		return Cunningham1Length >= target || Cunningham2Length >= target || TwinLength >= target;
	}

	pair<PrimeChainType, double> BestTypeLength() const {
		return TwinLength > max(Cunningham1Length, Cunningham2Length) ? make_pair(PrimeChainType::Twin, TwinLength)
			: Cunningham2Length > Cunningham1Length ? make_pair(PrimeChainType::Cunningham2, Cunningham2Length)
			: make_pair(PrimeChainType::Cunningham1, Cunningham1Length);
	}
};

class PrimeTester {
public:
	bool FermatTest;
	
	PrimeTester();
	double FermatProbablePrimalityTest(const Bn& n, bool bFastFail = false);
	double EulerLagrangeLifchitzTest(const Bn& primePrev, bool bSophieGermain);
	double ProbableCunninghamChainTest(const Bn& n, int step);
	CunninghamLengths ProbablePrimeChainTest(const Bn& origin, PrimeChainType chainType = PrimeChainType::Unknown);
private:
	Bn m_tmp_R, m_tmp_N_Minus1, m_tmp_T, m_tmpNext;
};




} // Coin::

