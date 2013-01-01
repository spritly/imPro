/****************************************************************************** 
** @Filename:		IpMedian.h
** @Project: 		"Bildbearbeitung"
** @author:    	B.Hentzschel 
** @letzte Ae: 	2012-10-25
** 
** Umsetzung des Median Filter (Tiefpassfilter) zur Glaettung. 
** Ist ein Rangordnungsfilter.
******************************************************************************/
#pragma once
#include "IpFilter.h"

namespace IMGProcessing{
	class IpMedianFilter:public IpRankingFilter{
	public:
		IpMedianFilter();
		~IpMedianFilter();

		IpImage* Run( IpImage* aImg );
	};
}
