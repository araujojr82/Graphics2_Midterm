#include "cAnimationState.h"

// Returns true if time had to be reset
// (for checking to see if the animation has finished or not)
bool cAnimationState::sStateDetails::IncrementTime(bool bResetToZero /*=true*/)
{
	bool bDidWeReset = false;

	this->currentTime += this->frameStepTime;
	if ( this->currentTime >= this->totalTime )
	{
		if( this->runInLoop )
		{
			this->currentTime = 0.0f;
			bDidWeReset = true;
		}
		else
		{
			bDidWeReset = false;
			this->isFinished = true;
		}
	}
	return bDidWeReset;
}
