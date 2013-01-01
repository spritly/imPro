#include "StdAfx.h"
#include "IpImage.h"

namespace IMGProcessing{

	using System::Exception;

	IpImage::IpImage(){
		mWidth = mHeight = 0;
		mPixImg = nullptr;
	}

	IpImage::IpImage(int aWidth, int aHeight){
		mWidth = aWidth;
		mHeight = aHeight;
		mPixImg = new Pixel*[mHeight];
		for( int i = 0; i < mHeight; i++){
			mPixImg[i] = new Pixel[mWidth];			
		}
	}

	IpImage::IpImage( Bitmap^ aImg ){
		mWidth = mHeight = 0;
		mPixImg = nullptr;
		SetImage( aImg );
	}

	IpImage::~IpImage(){
		delPixImg();
	}

	void IpImage::delPixImg(){
		if(mPixImg){
			for( int i = 0; i < mHeight; i++){
				delete[] mPixImg[i];
			}
			delete[] mPixImg;
		}
	}

	Bitmap^ IpImage::PixImgToBitmap(){
		if( mWidth > 0 && mHeight > 0 ){
			Bitmap^ resImg = gcnew Bitmap( mWidth, mHeight );
			
			for( int z = 0; z < mHeight; z++){
				for( int s = 0; s < mWidth; s++){				
					resImg->SetPixel( s, z, Color::FromArgb(
											mPixImg[z][s].mA,
											mPixImg[z][s].mR, 
											mPixImg[z][s].mG, 
											mPixImg[z][s].mB) );
				}
			}
			return resImg;
		}
		return nullptr;
	}
	
	void IpImage::SetImage( Bitmap^ aImg){
		if( !aImg)
			return;

		try{
			mWidth = aImg->Width;
			mHeight = aImg->Height;
			if( mPixImg )
				delete mPixImg;

			mPixImg = new Pixel*[mHeight];
			for( int z = 0; z < mHeight; z++){
				mPixImg[z] = new Pixel[mWidth];	
				for( int s = 0; s < mWidth; s++){
					mPixImg[z][s].mA = aImg->GetPixel(s, z).A;
					mPixImg[z][s].mR = aImg->GetPixel(s, z).R;
					mPixImg[z][s].mG = aImg->GetPixel(s, z).G;
					mPixImg[z][s].mB = aImg->GetPixel(s, z).B;
				}
			}
		}catch( Exception^ ex ){
			System::Diagnostics::Debug::WriteLine( ex );
		}
	}

}
