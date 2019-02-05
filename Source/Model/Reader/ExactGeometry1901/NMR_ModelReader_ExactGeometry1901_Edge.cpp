/*++

Copyright (C) 2018 3MF Consortium

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Abstract:

NMR_ModelReaderNode_ExactGeometry1901_Edge.cpp covers the official 3MF Exact Geometry Extension.

--*/

#include "Model/Reader/ExactGeometry1901/NMR_ModelReader_ExactGeometry1901_Edge.h"
#include "Model/Reader/ExactGeometry1901/NMR_ModelReader_ExactGeometry1901_UVTCoord.h"

#include "Model/Classes/NMR_ModelConstants.h"
#include "Model/Classes/NMR_ModelMeshObject.h"

#include "Common/NMR_StringUtils.h"
#include "Common/NMR_Exception.h"
#include "Common/NMR_Exception_Windows.h"
#include <cmath>

namespace NMR {

	CModelReaderNode_ExactGeometry1901_Edge::CModelReaderNode_ExactGeometry1901_Edge(_In_ CModel * pModel, _In_ CModelNurbsSurface * pNurbsSurface, _In_ PModelReaderWarnings pWarnings)
		: CModelReaderNode(pWarnings)
	{
		if (pNurbsSurface == nullptr)
			throw CNMRException(NMR_ERROR_INVALIDPARAM);

		m_pModel = pModel;
		m_pNurbsSurface = pNurbsSurface;
		m_pWarnings = pWarnings;

		m_nCurveID = 0;
		m_dT1 = 0.0;
		m_dT2 = 0.0;
		m_bHasCurveID = false;
		m_bHasT1 = false;
		m_bHasT2 = false;
		m_bNurbsEdgeID = 0;


	}

	void CModelReaderNode_ExactGeometry1901_Edge::parseXML(_In_ CXmlReader * pXMLReader)
	{
		// Parse name
		parseName(pXMLReader);

		// Parse attribute
		parseAttributes(pXMLReader);

		if ((!m_bHasCurveID) || (!m_bHasT1) || (!m_bHasT2)) 
			throw CNMRException(NMR_ERROR_MISSINGNURBSEDGEATTRIBUTE);

		m_bNurbsEdgeID = m_pNurbsSurface->addEdgeMapping(m_nCurveID, m_dT1, m_dT2);

		// Parse Content
		parseContent(pXMLReader);


	}

	
	void CModelReaderNode_ExactGeometry1901_Edge::OnAttribute(_In_z_ const nfChar * pAttributeName, _In_z_ const nfChar * pAttributeValue)
	{
		__NMRASSERT(pAttributeName);
		__NMRASSERT(pAttributeValue);
		if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_NURBS_CURVEID) == 0) {
			if (m_bHasCurveID)
				throw CNMRException(NMR_ERROR_NURBSDUPLICATEATTRIBUTE);

			nfUint32 nValue = fnStringToUint32(pAttributeValue);
			if ((nValue == 0) || (nValue >= XML_3MF_MAXRESOURCEID))
				throw CNMRException(NMR_ERROR_INVALIDCURVEID);

			m_nCurveID = nValue;
			m_bHasCurveID = true;
		}
		else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_NURBS_T1) == 0) {
			if (m_bHasT1)
				throw CNMRException(NMR_ERROR_NURBSDUPLICATEATTRIBUTE);

			nfDouble dValue = fnStringToDouble(pAttributeValue);
			if (std::isnan(dValue) || (dValue < -XML_3MF_MAXIMUMCOORDINATEVALUE) || (dValue > XML_3MF_MAXIMUMCOORDINATEVALUE))
				throw CNMRException(NMR_ERROR_NURBSINVALIDATTRIBUTE);

			m_dT1 = dValue;
			m_bHasT1 = true;
		}
		else if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_NURBS_T2) == 0) {
			if (m_bHasT2)
				throw CNMRException(NMR_ERROR_NURBSDUPLICATEATTRIBUTE);

			nfDouble dValue = fnStringToDouble(pAttributeValue);
			if (std::isnan(dValue) || (dValue < -XML_3MF_MAXIMUMCOORDINATEVALUE) || (dValue > XML_3MF_MAXIMUMCOORDINATEVALUE))
				throw CNMRException(NMR_ERROR_NURBSINVALIDATTRIBUTE);

			m_dT2 = dValue;
			m_bHasT2 = true;
		}
		else
			m_pWarnings->addException(CNMRException(NMR_ERROR_NURBSINVALIDATTRIBUTE), mrwInvalidOptionalValue);
	}

	void CModelReaderNode_ExactGeometry1901_Edge::OnNSAttribute(_In_z_ const nfChar * pAttributeName, _In_z_ const nfChar * pAttributeValue, _In_z_ const nfChar * pNameSpace)
	{
		

	}
	
	void CModelReaderNode_ExactGeometry1901_Edge::OnNSChildElement(_In_z_ const nfChar * pChildName, _In_z_ const nfChar * pNameSpace, _In_ CXmlReader * pXMLReader)
	{
		__NMRASSERT(pChildName);
		__NMRASSERT(pXMLReader);
		__NMRASSERT(pNameSpace);

		if (strcmp(pNameSpace, XML_3MF_NAMESPACE_NURBSSPEC) == 0) {
			if (strcmp(pChildName, XML_3MF_ELEMENT_NURBS_UVTCOORD) == 0)
			{
				PModelReaderNode_ExactGeometry1901_UVTCoord pXMLNode = std::make_shared<CModelReaderNode_ExactGeometry1901_UVTCoord>(m_pModel, m_pWarnings);
				pXMLNode->parseXML(pXMLReader);

				nfDouble dU;
				nfDouble dV;
				nfDouble dT;
				pXMLNode->retrieveCoord(dU, dV, dT);

				m_pNurbsSurface->addEdgeMappingUVCoordinate(m_bNurbsEdgeID, dU, dV, dT);

			}
			else
				m_pWarnings->addException(CNMRException(NMR_ERROR_NAMESPACE_INVALID_ELEMENT), mrwInvalidOptionalValue);
		}
	}


}
