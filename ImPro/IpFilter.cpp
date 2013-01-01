#include "StdAfx.h"
#include "IpFilter.h"

namespace IMGProcessing{	

	//**************************************************************************
	// IpFilter
	IpFilter::IpFilter(){
		mName = FilterName::NoName;
		mCategory = FilterCategory::NotDefined;
	}

	//**************************************************************************
	// IpRankingFilter
	IpRankingFilter::IpRankingFilter():mMaskSize(cStdFilterSize){}

	IpRankingFilter::IpRankingFilter( int aFilterSize){
		mMaskSize = aFilterSize;		
	}

	//**************************************************************************
	// IpMaskFilter
	IpMaskFilter::IpMaskFilter():mNormFactor(1){
		initMask();
	}

	void IpMaskFilter::initMask(){
		mMask = NULL;
		mMaskSize = 0;		
		mNormFactor = 1;
	}

   int IpMaskFilter::checkRange(int val) {
      return val > 255 ? 255 : (val < 0 ? 0 : val);
   }
	
	// da die Faltung mit der Maske bei allen maskenfiltern gleich ist
	// wird Run hier definiert und muss im Bedarfsfall in abgeleiteten
	// Klassen überschrieben werden
	IpImage* IpMaskFilter::Run( IpImage* aImg){
		IpImage* outImg = new IpImage(aImg->mWidth, aImg->mHeight);		
		int imgWidth	= aImg->mWidth;
		int imgHeight	= aImg->mHeight;

		try {
			Pixel currPixVal;
			int mz = 0, ms = 0; 
			int sumR = 0, sumG = 0, sumB = 0;
			
			for(int z = mMaskSize/2; z < imgHeight - mMaskSize/2 ; z++) {
				for(int s = mMaskSize/2; s < imgWidth - mMaskSize/2; s++) {										
					// Maske ueber das akt. Pixel legen und durch Faltung
					// den Wert des Pixels im neuen Bild ermitteln
					mz = 0;
					for( int k = -(mMaskSize / 2); k <= mMaskSize/2; k++) {
						ms = 0;
						for( int p = -(mMaskSize / 2); p <= mMaskSize / 2; p++) {
							currPixVal = aImg->mPixImg[z+k][s+p];
							sumR += currPixVal.mR* mMask[mz][ms];
							sumG += currPixVal.mG* mMask[mz][ms];
							sumB += currPixVal.mB* mMask[mz][ms];
							ms++;
						}
						mz++;
					}
					sumR = checkRange( sumR/ mNormFactor  );
					sumG = checkRange( sumG/ mNormFactor  );
					sumB = checkRange( sumB/ mNormFactor  );
					outImg->mPixImg[z][s] = Pixel( sumR, sumG, sumB); // Pixelwert im neuen Bild  
					sumR = sumG = sumB = 0;
				}
			} // for zeilen

		}catch( Exception^ ex){
			System::Diagnostics::Debug::WriteLine( ex);
			delete outImg;
			return nullptr;
		}
		return outImg;
	}


} 
