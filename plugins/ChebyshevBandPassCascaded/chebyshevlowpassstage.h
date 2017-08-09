#ifndef CHEBYSHEVLOWPASSSTAGE_H
#define CHEBYSHEVLOWPASSSTAGE_H
#include <secondorderfilter.h>

class ChebyshevLowHighPassStage:
        public SecondOrderFilter
{
public:
    ChebyshevLowHighPassStage();
    void setFilterParameters(int stage, int maxstage, float cuttoff, float sr, float passbandattenuation,bool highpass);
};

#endif // CHEBYSHEVLOWPASSSTAGE_H
