/****************************************************************************** 
** @Filename: 	IpGaussFilter.h
** @Project: 	"Bildbearbeitung"
** @author:    B.Hentzschel 
** @letzte Ae: 2012-10-25
** 
** Umsetzung des Gauss Filter (Tiefpassfilter) zur Glaettung. 
******************************************************************************/
#pragma once

#include "IpFilter.h"

namespace IMGProcessing{

	class IpGaussFilter:public IpMaskFilter{
	private: 
		void initMask();
	public:
		IpGaussFilter();
		~IpGaussFilter();
	};
}
