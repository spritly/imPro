/****************************************************************************** 
** @Filename: 		IpManager.h
** @Project: 		"Bildbearbeitung"
** @author:    	B.Hentzschel 
** @letzte Ae: 	2012-10-25
** 
** Verwaltet die BV-Filter ueber eine Liste und erzeugt sie
** dynamisch ueber eine fabrikmethode
******************************************************************************/
#pragma once

#include "IpFilter.h"
#include "IpLaplaceFilter.h"
#include "IpMeanValFilter.h"
#include "IpGaussFilter.h"
#include	"IpMedian.h"
#include "IpImage.h"

#include <vector>

namespace IMGProcessing{

	using namespace std;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;

	public ref class IpManager{
	private:
		IpImage* mInIpImage;
		IpImage* mOutIpImage;
		IpFilter* mCurrFilter; 
		Bitmap^ mInImgBitmap; // ist das PixImg in Bitmap Format und 
									 // wird aus zeitgruenden verwendet um laufende
									 // Umwandlungen zw PixImg und Bitmap zu umgehen
	public:
		IpManager(void);
		~IpManager(void);

		// liste mit verfuegbareb BV-Filtern
		vector<IpFilter*>* pAvailableFilterList; // unmanaged Container!!!

	private:
		// traegt verfuegbare Filter in eine Liste ein
		void registerFilter(IpFilter* aNewFilter); 		
		void delFilterList();		

	public:
		// wendet den mCurrFilter auf das mInIpImage an und erzeugt mOutIpImage
		bool ProcessImage();

		property Bitmap^ InImg{
			Bitmap^ get();
			void set( Bitmap^ aImg);
		}
		property IpImage* InIpImage{
			IpImage* get();
		}

		property Bitmap^ OutImg{
			Bitmap^ get();
			void set( Bitmap^ aImg);
		}

		property IpFilter* CurrFilter{
			IpFilter* get();
			void set( IpFilter* aFilter);
		}

		//***********************************************************************
		// Fabrikmethode, die anhand des Filternamens ein Filterobj liefert
		IpFilter* GetFilterByName( FilterName aName );

		// bildbearbeitungsMethoden ohne Filter Anwendung:
		Bitmap^ BinarizeImg( const IpImage* aOrgImg, const int aThreshold );
		Bitmap^ BinarizeImg( Bitmap^ aOrgImg, const int aThreshold );
		IpImage* GetGreyScaleImg( const IpImage* aOrgImg );		
	};

} // namespace IMGProcessing
