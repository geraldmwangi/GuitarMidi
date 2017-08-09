#include "chebyshevlowpassstage.h"
#include <math.h>
#include <assert.h>
ChebyshevLowHighPassStage::ChebyshevLowHighPassStage()
{

}

void ChebyshevLowHighPassStage::setFilterParameters(int stage, int maxstage, float cuttoff, float sr, float passbandattenuation, bool highpass)
{
    assert(stage<=maxstage);
    float n=2*maxstage;
    float sign=highpass?-1.0:1.0;
    float eps=pow(10.0,0.1*passbandattenuation)-1.0;
    float eta=sinh(1.0/n*asinh(1.0/eps));

    float omega=pow(tan(M_PI*cuttoff/sr),sign);
    float theta=((float)(2*stage-1))/(2*n)*M_PI;

    float ar=2.0*eta*sin(theta);
    float br=pow(cos(theta),2.0)+eta*eta;

    float Kr=sqrt(eta*eta+pow(sin(stage/n*M_PI),2.0));
    float Kr2=sqrt(eta*eta+pow(sin((n-stage+1)/n*M_PI),2.0));

    float d0=1.0 + omega*ar + br*omega*omega;
    float d1=-2.0 + 2.0*br*omega*omega;
    float d2=1.0- omega*ar + br*omega*omega;

    float K=omega*omega*Kr*Kr2;
    setFilterCoefficients(K/d0,K*2.0/d0*sign,K/d0,d1/d0*sign,d2/d0);

}
