/****************************************************************************** 
** @Filename: 	IpFilter.h
** @Project: 	"Bildbearbeitung"
** @author:    B.Hentzschel 
** @letzte Ae: 2012-10-25
** 
** Abstracte Klassen für die Ableitung von Filtern.
** Verwendung von unmanaged C++ Code aus Zeitgruenden
******************************************************************************/
#pragma once
#include <string>
#include "IpImage.h"

namespace IMGProcessing{
	using namespace std;
	using namespace System;
	using namespace System::Drawing;

	// neuen Filter hier mit namen erfassen und einer Kategorie zuordnen
	enum class FilterCategory{ NotDefined = 0, EdgeFilter, SmoothFilter };
	enum class FilterName{ NoName = 0, Laplace, Meanval, Gauss, Median };

	//**************************************************************************
	// Wrapperklasse,um auf unmanaged 'IpFilter' klasse managed zuzugreifen
	//**************************************************************************
	ref class IpFilterManaged{
		// todo
	};


	//**************************************************************************
	// Filter-Oberklasse 
	//**************************************************************************
	class IpFilter abstract{
	protected:
		static const int cStdFilterSize = 3;
	public:
		FilterName mName;			  // diesen beiden Vars muessen in
		FilterCategory mCategory; // abgeleiteten klassen werte zugeordnet werden
	public:
		IpFilter();
		virtual ~IpFilter(){};
		// wendet Filter auf uebergebenes Bild an:
		virtual IpImage* Run( IpImage* aImg ) abstract;
	};
	
	//**************************************************************************
	// alle vom IpRankingFilter abgeleitete Klassen muessen die 'Run' Methode
	// einzeln definieren und die Arbeitsweise des Filters somit beschreiben
	class IpRankingFilter abstract: public IpFilter{
	protected:
		int mMaskSize;		
	public:
		IpRankingFilter();
		IpRankingFilter( int aFilterSize );
		virtual ~IpRankingFilter(){};
	};

	//**************************************************************************
	// verwendung einer parametrisierten Maske als Filter.
	// Alle abgeleiteten klassen muessen die entspr. Filtermaske mit der Methode
	// 'initMask' definieren. Die Run-Methode fuehrt eine Faltung des Bildes mit
	// der Maske pixelweise durch. Diese Faltung ist bereits in 'IpMaskFilter'
	// definiert, kann aber im Bedarfsfall ueberschrieben werden.
	class IpMaskFilter abstract: public IpFilter{
	private:
		int checkRange(int val);
	protected:
		int** mMask;
		int mMaskSize;
		int mNormFactor; // zum Normalisieren der Pixelwerte falls noetig

		virtual void initMask()abstract;		
		IpImage* Run( IpImage* aImg); 
	public:
		IpMaskFilter();
		virtual ~IpMaskFilter(){};
	};
}
