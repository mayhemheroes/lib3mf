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

Abstract: This is the class declaration of CVector3DFieldComposed

*/


#ifndef __LIB3MF_VECTOR3DFIELDCOMPOSED
#define __LIB3MF_VECTOR3DFIELDCOMPOSED

#include "lib3mf_interfaces.hpp"

// Parent classes
#include "lib3mf_vector3dfield.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#endif

// Include custom headers here.
#include "Model/Classes/NMR_ModelVector3DFieldComposed.h"

namespace Lib3MF {
namespace Impl {


/*************************************************************************************************************************
 Class declaration of CVector3DFieldComposed 
**************************************************************************************************************************/

class CVector3DFieldComposed : public virtual IVector3DFieldComposed, public virtual CVector3DField {
private:

	/**
	* Put private members here.
	*/
	NMR::CModelVector3DFieldComposed* vector3DFieldComposed();
protected:

	/**
	* Put protected members here.
	*/

public:

	/**
	* Put additional public members here. They will not be visible in the external API.
	*/
	CVector3DFieldComposed() = delete;
	CVector3DFieldComposed(NMR::PModelVector3DFieldComposed pVector3DFieldComposed);

	/**
	* Public member functions to implement.
	*/

	void SetMethod(const Lib3MF::eCompositionMethod eTheMethod) override;

	Lib3MF::eCompositionMethod GetMethod() override;

	void SetSpace(const Lib3MF::eCompositionSpace eTheCompositionSpace) override;

	Lib3MF::eCompositionSpace GetSpace() override;

	Lib3MF_double GetFactor1() override;

	void SetFactor1(const Lib3MF_double dFactor1) override;

	Lib3MF_double GetFactor2() override;

	void SetFactor2(const Lib3MF_double dFactor2) override;

	IVector3DFieldReference * Vector3DFieldReference1() override;

	IVector3DFieldReference * Vector3DFieldReference2() override;

	IScalarFieldReference * ScalarFieldReferenceMask() override;

};

} // namespace Impl
} // namespace Lib3MF

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // __LIB3MF_VECTOR3DFIELDCOMPOSED
