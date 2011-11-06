/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _FORMS_TIME_HXX_
#define _FORMS_TIME_HXX_

#include "EditBase.hxx"
#include "limitedformats.hxx"

//.........................................................................
namespace frm
{
//.........................................................................

//==================================================================
//= OTimeModel
//==================================================================
class OTimeModel
				:public OEditBaseModel
				,public OLimitedFormats
{
private:
	::com::sun::star::uno::Any		m_aSaveValue;
	sal_Bool			            m_bDateTimeField;

protected:
	virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();

public:
	DECLARE_DEFAULT_LEAF_XTOR( OTimeModel );

	// stario::XPersistObject
	virtual ::rtl::OUString SAL_CALL getServiceName() throw ( ::com::sun::star::uno::RuntimeException);

	// ::com::sun::star::beans::XPropertySet
	virtual void SAL_CALL getFastPropertyValue(::com::sun::star::uno::Any& rValue, sal_Int32 nHandle ) const;
	virtual sal_Bool SAL_CALL convertFastPropertyValue(::com::sun::star::uno::Any& rConvertedValue, ::com::sun::star::uno::Any& rOldValue,
										  sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue )
										throw(::com::sun::star::lang::IllegalArgumentException);
	virtual void SAL_CALL setFastPropertyValue_NoBroadcast(sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue) throw ( ::com::sun::star::uno::Exception);

	// ::com::sun::star::lang::XServiceInfo
	IMPLEMENTATION_NAME(OTimeModel);
	virtual StringSequence SAL_CALL getSupportedServiceNames() throw();

    // OControlModel's property handling
	virtual void describeFixedProperties(
		::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rProps
    ) const;

    // prevent method hiding
    using OBoundControlModel::getFastPropertyValue;

protected:
    // OBoundControlModel overridables
    virtual ::com::sun::star::uno::Any
                            translateDbColumnToControlValue( );
    virtual sal_Bool        commitControlValueToDbColumn( bool _bPostReset );

    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type >
                            getSupportedBindingTypes();
    virtual ::com::sun::star::uno::Any
                            translateControlValueToExternalValue( ) const;
    virtual ::com::sun::star::uno::Any
                            translateExternalValueToControlValue( const ::com::sun::star::uno::Any& _rExternalValue ) const;

    virtual ::com::sun::star::uno::Any
                            translateControlValueToValidatableValue( ) const;

    virtual ::com::sun::star::uno::Any
                            getDefaultForReset() const;
	virtual void            resetNoBroadcast();

	virtual void		    onConnectedDbColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxForm );

protected:
    DECLARE_XCLONEABLE();

private:
    /** translates the control value (the VCL-internal integer representation of a date) into
        a UNO-Date.
    */
    void                    impl_translateControlValueToUNOTime(
                                ::com::sun::star::uno::Any& _rUNOValue ) const;
};

//==================================================================
//= OTimeControl
//==================================================================
class OTimeControl: public OBoundControl
{
protected:
	virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();

public:
	OTimeControl(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory);
	DECLARE_UNO3_AGG_DEFAULTS(OTimeControl, OBoundControl);

	// ::com::sun::star::lang::XServiceInfo
	IMPLEMENTATION_NAME(OTimeControl);
	virtual StringSequence SAL_CALL getSupportedServiceNames() throw();
};

//.........................................................................
}	// namespace frm
//.........................................................................

#endif // _FORMS_TIME_HXX_

