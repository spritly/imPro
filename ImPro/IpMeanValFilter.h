/****************************************************************************** 
** @Filename: 		IpMeanValFilter.h
** @Project: 		"Bildbearbeitung"
** @author:    	B.Hentzschel 
** @letzte Ae: 	2012-10-25
** 
** Umsetzung des Mittelwert Filter (Tiefpassfilter) zur Glaettung. 
******************************************************************************/
#pragma once

#include "IpFilter.h"

namespace IMGProcessing{
	class IpMeanValFilter:public IpMaskFilter{
	private: 
		void initMask();
	public:
		IpMeanValFilter();
		~IpMeanValFilter();
	};
}