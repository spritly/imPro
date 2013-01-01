/****************************************************************************** 
** @Filename: 	IpLaplaceFilter.h
** @Project: 	"Bildbearbeitung"
** @author:    B.Hentzschel 
** @letzte Ae: 2012-10-25
** 
** Umsetzung des Laplace Filter (Hochpassfilter) zur Kantendetektion. 
******************************************************************************/
#pragma once
#include "IpFilter.h"

namespace IMGProcessing{

	class IpLaplaceFilter : public IpMaskFilter{
	private: 
		void initMask();
	public:
		IpLaplaceFilter();
		~IpLaplaceFilter();
	};

}
