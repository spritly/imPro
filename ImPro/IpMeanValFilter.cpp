#include "StdAfx.h"
#include "IpMeanValFilter.h"

namespace IMGProcessing{

	IpMeanValFilter::IpMeanValFilter(void){
		mName = FilterName::Meanval;
		mCategory = FilterCategory::SmoothFilter;
		initMask();
	}

	IpMeanValFilter::~IpMeanValFilter(void){
		for( int i = 0; i < mMaskSize; i++ )
			delete [] mMask[i];
		delete [] mMask;
	}

	void IpMeanValFilter::initMask(){
		mMaskSize = 7;
		mNormFactor = mMaskSize * mMaskSize;
		mMask = new int*[mMaskSize];
		for( int i = 0; i < mMaskSize; i++ ){
			mMask[i] = new int[mMaskSize];
			for( int j = 0; j < mMaskSize; j++){
				mMask[i][j] = 1;
			}
		}
	}

}
