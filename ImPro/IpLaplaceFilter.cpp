#include "StdAfx.h"
#include "IpLaplaceFilter.h"

namespace IMGProcessing{

	IpLaplaceFilter::IpLaplaceFilter(void){
		mName = FilterName::Laplace;
		mCategory = FilterCategory::EdgeFilter;		
		initMask();
	}

	IpLaplaceFilter::~IpLaplaceFilter(void){
		for( int i = 0; i < mMaskSize; i++ )
			delete [] mMask[i];
		delete [] mMask;
	}

	void IpLaplaceFilter::initMask(){	
		mMaskSize = 3;
		mNormFactor = 1;
		mMask = new int*[mMaskSize];

		for( int i = 0; i < mMaskSize; i++ ){
			mMask[i] = new int[mMaskSize];
		}

		mMask[0][0] = -1;
		mMask[0][1] = -2;
		mMask[0][2] = -1;

		mMask[1][0] = -2;
		mMask[1][1] = 12;
		mMask[1][2] = -2;

		mMask[2][0] = -1;
		mMask[2][1] = -2;
		mMask[2][2] = -1;		
	}


}
