/****************************************************************************** 
** @Filename: 		IpImage.h
** @Project: 		"Bildbearbeitung"
** @author:			B.Hentzschel 
** @letzte Ae: 	2012-10-25
** 
** Die Klasse 'IpImage' 
******************************************************************************/
#pragma once

namespace IMGProcessing{
	using namespace System::Drawing;

	//**************************************************************************
	// Pixel -> Stellt ein RGB farbpixel dar
	//**************************************************************************
	struct Pixel{		 
		unsigned char mR, mG, mB, mA;
    
		Pixel(int aRed, int aGreen, int aBlue, int aTransp = 255){
			mR = (unsigned char)aRed;
			mG = (unsigned char)aGreen;
			mB = (unsigned char)aBlue;
			mA = (unsigned char)aTransp;
		}

		Pixel(){
			mR = mG = mB = 0;
			mA = 255;
		}
	};

	//**************************************************************************
	// IpImage -> BildKlasse mit schnellem Zugriff auf Bilddaten ueber
	// unmanaged c++ code
	//**************************************************************************
	class IpImage{
	public:
		int mWidth, mHeight;
		Pixel** mPixImg;
	public:
		IpImage();
		IpImage(int aWidth, int aHeight);
		IpImage( Bitmap^ aImg );
		~IpImage();
		
	private:
		void delPixImg();

	public:
		// wandelt die pixelMatrix 'mPixImg' in ein Bitmap um
		Bitmap^ PixImgToBitmap();

		// wandelt ein Bitmap in PixelMatrix und definiert 'mPixImg'
		void SetImage( Bitmap^ aImg);

		// []operator?????? ->ToDo
	};
}
