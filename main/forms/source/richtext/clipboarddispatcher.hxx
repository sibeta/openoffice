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



#ifndef FORMS_SOURCE_RICHTEXT_CLIPBOARDDISPATCHER_HXX
#define FORMS_SOURCE_RICHTEXT_CLIPBOARDDISPATCHER_HXX

#include "featuredispatcher.hxx"
#include <tools/link.hxx>

class TransferableClipboardListener;
class TransferableDataHelper;
//........................................................................
namespace frm
{
//........................................................................

	//====================================================================
	//= OClipboardDispatcher
	//====================================================================
    class OClipboardDispatcher : public ORichTextFeatureDispatcher
	{
    public:
        enum ClipboardFunc
        {
            eCut,
            eCopy,
            ePaste
        };

    private:
        ClipboardFunc   m_eFunc;
        sal_Bool        m_bLastKnownEnabled;

    public:
        OClipboardDispatcher( EditView& _rView, ClipboardFunc _eFunc );

    protected:
        // XDispatch
        virtual void SAL_CALL dispatch( const ::com::sun::star::util::URL& URL, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& Arguments ) throw (::com::sun::star::uno::RuntimeException);

        // ORichTextFeatureDispatcher
        virtual void    invalidateFeatureState_Broadcast();
        virtual ::com::sun::star::frame::FeatureStateEvent
                        buildStatusEvent() const;

    protected:
        /** determines whether our functionality is currently available
            to be overridden for ePaste
        */
        virtual sal_Bool implIsEnabled( ) const;
	};

	//====================================================================
	//= OPasteClipboardDispatcher
	//====================================================================
    class OPasteClipboardDispatcher : public OClipboardDispatcher
    {
    private:
        TransferableClipboardListener*  m_pClipListener;
        sal_Bool                        m_bPastePossible;

    public:
        OPasteClipboardDispatcher( EditView& _rView );

    protected:
        ~OPasteClipboardDispatcher();

        // OClipboardDispatcher
        virtual sal_Bool    implIsEnabled( ) const;

        // ORichTextFeatureDispatcher
        virtual void    disposing( ::osl::ClearableMutexGuard& _rClearBeforeNotify );

    private:
        DECL_LINK( OnClipboardChanged, TransferableDataHelper* );
    };

//........................................................................
} // namespace frm
//........................................................................

#endif // FORMS_SOURCE_RICHTEXT_CLIPBOARDDISPATCHER_HXX

