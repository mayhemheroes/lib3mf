/*++

Copyright (C) 2019 3MF Consortium (Original Author)

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

Abstract: This is a stub class definition of CToolpathLayerData

*/

#include "lib3mf_toolpathlayerdata.hpp"
#include "lib3mf_interfaceexception.hpp"

// Include custom headers here.
#include "Common/Platform/NMR_ExportStream_Memory.h"
#include "Common/Platform/NMR_ImportStream_Shared_Memory.h"
#include "Common/Platform/NMR_ImportStream_Unique_Memory.h"
#include "Common/Platform/NMR_XmlWriter_Native.h"
#include "Model/Classes/NMR_ModelConstants.h"

using namespace Lib3MF::Impl;

/*************************************************************************************************************************
 Class definition of CToolpathLayerData 
**************************************************************************************************************************/

Lib3MF_uint32 CToolpathLayerData::RegisterProfile(IToolpathProfile* pProfile)
{
	return 0;
}

Lib3MF_uint32 CToolpathLayerData::RegisterPart(IObject* pProfile)
{
	return 0;
}

void CToolpathLayerData::WriteHatchData(const Lib3MF_uint32 nProfileID, const Lib3MF_uint32 nPartID, const Lib3MF_uint64 nPointDataBufferSize, const Lib3MF::sPosition2D * pPointDataBuffer)
{
}

void CToolpathLayerData::WriteLoop(const Lib3MF_uint32 nProfileID, const Lib3MF_uint32 nPartID, const Lib3MF_uint64 nPointDataBufferSize, const Lib3MF::sPosition2D * pPointDataBuffer)
{
}

void CToolpathLayerData::WritePolyline(const Lib3MF_uint32 nProfileID, const Lib3MF_uint32 nPartID, const Lib3MF_uint64 nPointDataBufferSize, const Lib3MF::sPosition2D * pPointDataBuffer)
{
}

NMR::PImportStream CToolpathLayerData::createStream()
{
	NMR::PExportStreamMemory pExportStream;

	{
		NMR::PXmlWriter_Native pXmlWriter = std::make_shared<NMR::CXmlWriter_Native>(pExportStream);
		pXmlWriter->WriteStartDocument();
		pXmlWriter->WriteStartElement(nullptr, XML_3MF_TOOLPATHELEMENT_LAYER, XML_3MF_NAMESPACE_TOOLPATHLAYER);

		pXmlWriter->WriteEndDocument();
		pXmlWriter->Flush();
	}
	
	// TODO: Do not copy but use Pipe-based importexportstream!
	NMR::CImportStream_Shared_Memory pImportStream (pExportStream->getData(), pExportStream->getDataSize());	
	return pImportStream.copyToMemory();


}
