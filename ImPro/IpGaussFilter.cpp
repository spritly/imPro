#include "StdAfx.h"
#include "IpGaussFilter.h"

namespace IMGProcessing{

	IpGaussFilter::IpGaussFilter(){
		mName = FilterName::Gauss;
		mCategory = FilterCategory::SmoothFilter;
		
		initMask();
	}

	IpGaussFilter::~IpGaussFilter(){
		for( int i = 0; i < mMaskSize; i++ )
			delete [] mMask[i];
		delete [] mMask;
	}

	void IpGaussFilter::initMask(){	
		mMaskSize = 3;
		mNormFactor = 16;
		mMask = new int*[mMaskSize];
		for( int i = 0; i < mMaskSize; i++ ){
			mMask[i] = new int[mMaskSize];
		}

		mMask[0][0] = 1;
		mMask[0][1] = 2;
		mMask[0][2] = 1;

		mMask[1][0] = 2;
		mMask[1][1] = 4;
		mMask[1][2] = 2;

		mMask[2][0] = 1;
		mMask[2][1] = 2;
		mMask[2][2] = 1;
	}
}