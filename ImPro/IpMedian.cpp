#include "StdAfx.h"
#include "IpMedian.h"


namespace IMGProcessing{

	using namespace std;
	using namespace System::Collections::Generic;

	IpMedianFilter::IpMedianFilter(){
		mName = FilterName::Median;
		mCategory = FilterCategory::SmoothFilter;
		mMaskSize = 5;
	}

	IpMedianFilter::~IpMedianFilter(){
		// es wurde keine Maske erzeugt deshalb keine Freigabe noetig
	}

	IpImage* IpMedianFilter::Run( IpImage* aImg ){
		IpImage* outImg = new IpImage(aImg->mWidth, aImg->mHeight);		
		int imgWidth	= aImg->mWidth;
		int imgHeight	= aImg->mHeight;
		
		unsigned char midGValR, midGValG, midGValB;
		midGValR = midGValG = midGValB =0;
		int midListIdx = mMaskSize*mMaskSize/2;

		List<unsigned char>^ listR = gcnew List<unsigned char>();
		List<unsigned char>^ listG = gcnew List<unsigned char>();
		List<unsigned char>^ listB = gcnew List<unsigned char>();

		try {
			for(int z = mMaskSize/2; z < imgHeight - mMaskSize/2 ; z++) {
				for(int s = mMaskSize/2; s < imgWidth - mMaskSize/2; s++) {

					for( int k = -(mMaskSize / 2); k <= mMaskSize/2; k++) {
						for( int p = -(mMaskSize / 2); p <= mMaskSize / 2; p++) {							
							listR->Add( aImg->mPixImg[z+k][s+p].mR );
							listG->Add( aImg->mPixImg[z+k][s+p].mG );
							listB->Add( aImg->mPixImg[z+k][s+p].mB );
						}
					}
					listR->Sort();
					listG->Sort();
					listB->Sort();
					midGValR =listR[midListIdx]; 
					midGValG =listG[midListIdx]; 
					midGValB =listB[midListIdx]; 

					outImg->mPixImg[z][s] = Pixel( midGValR, midGValG, midGValB );  
					listR->Clear();
					listG->Clear();
					listB->Clear();
				} // for s
			} // for z

		}catch( Exception^ ex){
			System::Diagnostics::Debug::WriteLine( ex);
			delete outImg;
			return nullptr;
		}
		return outImg;
	}

}