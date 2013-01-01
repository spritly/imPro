#include "StdAfx.h"
#include "IpManager.h"

namespace IMGProcessing{

	IpManager::IpManager(void)	{
		mInIpImage = new IpImage(); 
		mInImgBitmap = nullptr; // um Bitmap nicht laufend beim Abfragen von
							// inImg zu erzeugen

		mOutIpImage = new IpImage();
		mCurrFilter = NULL;
		pAvailableFilterList = new vector<IpFilter*>;

		// alle zu verwendenden Filter muessen hier anmeldet werden
		registerFilter( new IpLaplaceFilter() );
		registerFilter( new IpMeanValFilter() );
		registerFilter( new IpGaussFilter() );
		registerFilter( new IpMedianFilter() );
	}

	//**************************************************************************
	IpManager::~IpManager(void){
		delete mCurrFilter;
		delFilterList();
		if( mInIpImage )
			delete mInIpImage;
		if( mOutIpImage )
			delete mOutIpImage;
 	}

	//**************************************************************************
	void IpManager::delFilterList(){
		while( pAvailableFilterList->size() > 0 ){
			pAvailableFilterList->erase( pAvailableFilterList->end()-1 );
		}
	}

	//**************************************************************************
	void IpManager::registerFilter(IpFilter* aNewFilter){
		pAvailableFilterList->push_back( aNewFilter );
	}
	
	//**************************************************************************
	bool IpManager::ProcessImage(){
		try{
			if( !mCurrFilter ){
				// kein Filter ausgewaehlt
				return false;
			}			
			mOutIpImage = mCurrFilter->Run( mInIpImage );
		}catch( Exception^ ex){
			System::Diagnostics::Debug::WriteLine( ex->ToString());
			return false;
		}
		return true;
	}

	//************** properties: ********************************************	
	Bitmap^ IpManager::InImg::get(){
		if( mInImgBitmap )
			// falls schon mal aus dem inImg ein Bitmap gemacht wurde...
			return mInImgBitmap;

		if( mInIpImage ){
			mInImgBitmap = mInIpImage->PixImgToBitmap();
			return mInImgBitmap;
		}
		else
			return nullptr;
	}

	IpImage* IpManager::InIpImage::get(){
		return mInIpImage;
	}	

	void IpManager::InImg::set( Bitmap^ aImg ){
		if( mInIpImage )
			delete mInIpImage;
		
		mInIpImage = new IpImage();

		try{
			mInIpImage->SetImage( aImg );
		}catch( Exception^ ex ){
			delete mInImgBitmap;
			return;
		}
		mInImgBitmap = aImg;
	}

	
	Bitmap^ IpManager::OutImg::get(){
		if( mOutIpImage )
			return mOutIpImage->PixImgToBitmap();
		else
			return nullptr;
	}


	void IpManager::OutImg::set( Bitmap^ aImg){
		if( !aImg  )
			return;
		mOutIpImage->SetImage( aImg );
	}

	IpFilter* IpManager::CurrFilter::get(){
		if( mCurrFilter )
			return mCurrFilter;
		else
			return NULL;
	}

	void IpManager::CurrFilter::set( IpFilter* aFilter){
		if( aFilter )
			mCurrFilter = aFilter;
	}

	//**************************************************************************
	// Filter dynamisch erzeugen
	IpFilter* IpManager::GetFilterByName( FilterName aName ){
		IpFilter* newFilter = NULL;
		switch( aName ){
			case FilterName::Laplace:
				newFilter = new IpLaplaceFilter();
				break;	
			case FilterName::Meanval:
				newFilter = new IpMeanValFilter();
				break;
			case FilterName::Gauss:
				newFilter = new IpGaussFilter();
				break;
			case FilterName::Median:
				newFilter = new IpMedianFilter();
				break;
		}
		return newFilter;
	}


	IpImage* IpManager::GetGreyScaleImg( const IpImage* aOrgImg ){
		if( aOrgImg ){
			IpImage* greyImg = new IpImage( aOrgImg->mWidth, aOrgImg->mHeight );
			int greyVal = 0;
			for( int z = 0; z < greyImg->mHeight; z++){
				for( int s = 0; s < greyImg->mWidth; s++){
					// Formel:GW = 0.3*R + 0.59*G + 0.11*B
					greyVal = (int)System::Math::Round(	
										0.3  * aOrgImg->mPixImg[z][s].mR + 
										0.59 * aOrgImg->mPixImg[z][s].mG +
										0.11 * aOrgImg->mPixImg[z][s].mB );
					greyVal = greyVal > 255 ? 255 : greyVal < 0 ? 0 : greyVal;
					greyImg->mPixImg[z][s] = Pixel( greyVal, greyVal, greyVal ); 
				}
			}
			return greyImg;
		}else
			return nullptr;
	}

	Bitmap^ IpManager::BinarizeImg( Bitmap^ aOrgImg, const int aThreshold ){
		IpImage* binImg = new IpImage( aOrgImg );
		Bitmap^ resImg;
		if( binImg )
			resImg = BinarizeImg( binImg, aThreshold );
		else
			resImg = nullptr;		
		return resImg;
	}

	Bitmap^ IpManager::BinarizeImg( const IpImage* aOrgImg, const int aThreshold ){
		IpImage* binImg;
		try{
			if( aThreshold >= 0 && aThreshold < 256 ){
				// erst GW bild bilden, dann binarisieren
				binImg = GetGreyScaleImg( aOrgImg );
				Pixel whitePix = Pixel(255,255,255);
				Pixel blackPix = Pixel( 0, 0, 0 );
				unsigned char currGval = 0;
				if( binImg ){
					for( int z = 0; z < binImg->mHeight; z++){
						for( int s = 0; s < binImg->mWidth; s++){
							currGval = binImg->mPixImg[z][s].mR; 
							binImg->mPixImg[z][s] = currGval > aThreshold ? whitePix : blackPix;
						}
					}
					return binImg->PixImgToBitmap();
				}				
			}
		}catch( Exception^ ex){
			if( binImg )
				delete binImg;
			System::Diagnostics::Debug::WriteLine( ex->ToString() );			
		}
		return nullptr;
	}
} // namespace
