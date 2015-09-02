/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/combobox.h
// Purpose:     wxComboBox class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_COMBOBOX_H_
#define _WX_COMBOBOX_H_

#include "wx/containr.h"
#include "wx/choice.h"
#include "wx/textctrl.h"

WX_DEFINE_ARRAY( char * , wxComboBoxDataArray ) ;

// forward declaration of private implementation classes

class wxComboBoxText;
class wxComboBoxChoice;
class wxComboWidgetImpl;

// Combobox item
class WXDLLIMPEXP_CORE wxComboBox :
    public wxWindowWithItems<
#if wxOSX_USE_CARBON
                wxNavigationEnabled<wxControl>,
#else
                wxControl,
#endif
                wxComboBoxBase>
{
    wxDECLARE_DYNAMIC_CLASS(wxComboBox);

 public:
    virtual ~wxComboBox();

#if wxOSX_USE_CARBON
    // forward these functions to all subcontrols
    virtual bool Enable(bool enable = true);
    virtual bool Show(bool show = true);
#endif

    // callback functions
    virtual void DelegateTextChanged( const wxString& value );
    virtual void DelegateChoice( const wxString& value );

    wxComboBox() { }

    wxComboBox(wxWindow *parent, wxWindowID id,
           const wxString& value = wxEmptyString,
           const wxPoint& pos = wxDefaultPosition,
           const wxSize& size = wxDefaultSize,
           int n = 0, const wxString choices[] = NULL,
           long style = 0,
           const wxValidator& validator = wxDefaultValidator,
           const wxString& name = wxComboBoxNameStr)
    {
        Create(parent, id, value, pos, size, n, choices, style, validator, name);
    }

    wxComboBox(wxWindow *parent, wxWindowID id,
           const wxString& value,
           const wxPoint& pos,
           const wxSize& size,
           const wxArrayString& choices,
           long style = 0,
           const wxValidator& validator = wxDefaultValidator,
           const wxString& name = wxComboBoxNameStr)
    {
        Create(parent, id, value, pos, size, choices, style, validator, name);
    }

    bool Create(wxWindow *parent, wxWindowID id,
           const wxString& value = wxEmptyString,
           const wxPoint& pos = wxDefaultPosition,
           const wxSize& size = wxDefaultSize,
           int n = 0, const wxString choices[] = NULL,
           long style = 0,
           const wxValidator& validator = wxDefaultValidator,
           const wxString& name = wxComboBoxNameStr);

    bool Create(wxWindow *parent, wxWindowID id,
           const wxString& value,
           const wxPoint& pos,
           const wxSize& size,
           const wxArrayString& choices,
           long style = 0,
           const wxValidator& validator = wxDefaultValidator,
           const wxString& name = wxComboBoxNameStr);

    virtual int GetSelection() const wxOVERRIDE;
    virtual void GetSelection(long *from, long *to) const wxOVERRIDE;
    virtual void SetSelection(int n) wxOVERRIDE;
    virtual void SetSelection(long from, long to) wxOVERRIDE;
    virtual int FindString(const wxString& s, bool bCase = false) const wxOVERRIDE;
    virtual wxString GetString(unsigned int n) const wxOVERRIDE;
    virtual wxString GetStringSelection() const wxOVERRIDE;
    virtual void SetString(unsigned int n, const wxString& s) wxOVERRIDE;

    virtual unsigned int GetCount() const wxOVERRIDE;

    virtual void SetValue(const wxString& value) wxOVERRIDE;
// these methods are provided by wxTextEntry for the native impl.
#if wxOSX_USE_CARBON
    // Text field functions
    virtual wxString GetValue() const;
    virtual void WriteText(const wxString& text);

    // Clipboard operations
    virtual void Copy();
    virtual void Cut();
    virtual void Paste();
    virtual void SetInsertionPoint(long pos);
    virtual void SetInsertionPointEnd();
    virtual long GetInsertionPoint() const;
    virtual wxTextPos GetLastPosition() const;
    virtual void Replace(long from, long to, const wxString& value);
    virtual void Remove(long from, long to);
    virtual void SetEditable(bool editable);
    virtual bool IsEditable() const;

    virtual void Undo();
    virtual void Redo();
    virtual void SelectAll();

    virtual bool CanCopy() const;
    virtual bool CanCut() const;
    virtual bool CanPaste() const;
    virtual bool CanUndo() const;
    virtual bool CanRedo() const;

    virtual wxClientDataType GetClientDataType() const;

    virtual wxTextWidgetImpl* GetTextPeer() const;
#endif // wxOSX_USE_CARBON

#if wxOSX_USE_COCOA
    virtual void Popup() wxOVERRIDE;
    virtual void Dismiss() wxOVERRIDE;
#endif // wxOSX_USE_COCOA


    // osx specific event handling common for all osx-ports

    virtual bool        OSXHandleClicked( double timestampsec ) wxOVERRIDE;

#if wxOSX_USE_COCOA
    wxComboWidgetImpl* GetComboPeer() const;
#endif
protected:
    // List functions
    virtual void DoDeleteOneItem(unsigned int n) wxOVERRIDE;
    virtual void DoClear() wxOVERRIDE;

    // wxTextEntry functions
#if wxOSX_USE_CARBON
    virtual wxString DoGetValue() const;
#endif
    virtual wxWindow *GetEditableWindow() wxOVERRIDE { return this; }

    // override the base class virtuals involved in geometry calculations
    virtual wxSize DoGetBestSize() const wxOVERRIDE;
#if wxOSX_USE_CARBON
    virtual void DoMoveWindow(int x, int y, int width, int height);
#endif

    virtual int DoInsertItems(const wxArrayStringsAdapter& items,
                              unsigned int pos,
                              void **clientData, wxClientDataType type) wxOVERRIDE;

    virtual void DoSetItemClientData(unsigned int n, void* clientData) wxOVERRIDE;
    virtual void * DoGetItemClientData(unsigned int n) const wxOVERRIDE;

#if wxOSX_USE_CARBON
    virtual void SetClientDataType(wxClientDataType clientDataItemsType);
#endif

    virtual void EnableTextChangedEvents(bool enable) wxOVERRIDE;

    // the subcontrols
    wxComboBoxText*     m_text;
    wxComboBoxChoice*   m_choice;

    wxComboBoxDataArray m_datas;
};

#endif // _WX_COMBOBOX_H_
