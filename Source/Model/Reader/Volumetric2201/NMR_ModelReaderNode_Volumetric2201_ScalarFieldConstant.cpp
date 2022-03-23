/*++

Copyright (C) 2019 3MF Consortium

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
NMR_ModelReaderNode_Volumetric2201_ScalarFieldConstant.cpp covers the official 3MF volumetric extension.

--*/

#include "Model/Reader/Volumetric2201/NMR_ModelReaderNode_Volumetric2201_ScalarFieldConstant.h"

#include "Model/Classes/NMR_ModelConstants.h"
#include "Model/Classes/NMR_Model.h"
#include "Model/Classes/NMR_ModelTexture2D.h"

#include "Common/NMR_StringUtils.h"
#include "Common/NMR_Exception.h"
#include "Common/NMR_Exception_Windows.h"

namespace NMR {


	CModelReaderNode_Volumetric2201_ScalarFieldConstant::CModelReaderNode_Volumetric2201_ScalarFieldConstant(_In_ CModel* pModel, _In_ CModelScalarFieldConstant* pScalarFieldConstant, _In_ PModelWarnings pWarnings)
		: CModelReaderNode(pWarnings),
		m_pModel(pModel),
		m_pScalarFieldConstant(pScalarFieldConstant)
	{
		if (pModel == nullptr)
			throw CNMRException(NMR_ERROR_INVALIDPARAM);
		if (m_pScalarFieldConstant == nullptr)
			throw CNMRException(NMR_ERROR_INVALIDPARAM);
	}

	void CModelReaderNode_Volumetric2201_ScalarFieldConstant::parseXML(_In_ CXmlReader* pXMLReader)
	{
		// Parse name
		parseName(pXMLReader);

		// Parse attribute
		parseAttributes(pXMLReader);

		// Parse Content
		parseContent(pXMLReader);

		if (!m_bHasValue)
			throw CNMRException(-1); // TODO: NMR_ERROR_NAMESPACE_MISSING_CONSTANT_FIELD_VALUE
	}


	void CModelReaderNode_Volumetric2201_ScalarFieldConstant::OnAttribute(_In_z_ const nfChar* pAttributeName, _In_z_ const nfChar* pAttributeValue)
	{
		if (strcmp(pAttributeName, XML_3MF_ATTRIBUTE_SCALARFIELDCONSTANT_VALUE) == 0) {
			if (m_bHasValue)
				throw CNMRException(-1); // TODO NMR_ERROR_DUPLICATE....
			m_pScalarFieldConstant->setValue(fnStringToDouble(pAttributeValue));
			m_bHasValue = true;
		}
		else
			m_pWarnings->addException(CNMRException(NMR_ERROR_NAMESPACE_INVALID_ATTRIBUTE), mrwInvalidOptionalValue);
	}

	void CModelReaderNode_Volumetric2201_ScalarFieldConstant::OnNSChildElement(_In_z_ const nfChar* pChildName, _In_z_ const nfChar* pNameSpace, _In_ CXmlReader* pXMLReader)
	{
		__NMRASSERT(pChildName);
		__NMRASSERT(pXMLReader);
		__NMRASSERT(pNameSpace);

		if (strcmp(pNameSpace, XML_3MF_NAMESPACE_VOLUMETRICSPEC) == 0) {
			m_pWarnings->addException(CNMRException(NMR_ERROR_NAMESPACE_INVALID_ELEMENT), mrwInvalidOptionalValue);
		}
	}


}
