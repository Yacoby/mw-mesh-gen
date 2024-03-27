﻿#ifndef __GUI__
#define __GUI__

#define WORKER_UPDATE 50003
#define WORKER_SUCCESS 50004
#define WORKER_FAILURE 50005

/**
@file
Subclass of GrassGen, which is generated by wxFormBuilder.
*/

#include "GrassGen.h"
#include "includes.h"
#include "Funcs.h"
#include "Ini.h"


class GenThreadEvent : public wxEvent{
	wxString mStatusBar;
	int mProgBar;
	int mOptions;
public:

	GenThreadEvent(int winid = 0, wxEventType commandType = wxEVT_NULL):wxEvent(winid,commandType){}

	enum{ GN_PROG_BAR = 1, GN_STAT_BAR = 2, GN_ALL_DONE = 4};

	void setOptions(int m){ mOptions = m;}
	int getOptions(){return mOptions;}

	void setStatusString(wxString s){mStatusBar = s;}
	wxString getStatusString(){return mStatusBar;}

	void setProgBar(int m){mProgBar = m;}
	int getProgBar(){return mProgBar;}
protected:
	wxEvent *Clone() const { return new GenThreadEvent(*this); }
};




/** Implementing GrassGen */
class GUI : public GrassGen{
private:

	struct FileTime{
		boost::filesystem::path file;
		time_t time;
	};
	static bool timeSort(FileTime i,FileTime j) { return (i.time<j.time); }

	void clearModList();
	std::list<std::string> getActiveFiles();

	int getCell(float xy);

	void setStatusText(std::string text){
		mStatus->SetStatusText(text);
		wxWindow::Update();
	}

	std::string getRegKey(wchar_t* pos, wchar_t* name);

protected:

	void OnThreadEvent(wxCommandEvent& event){
		if ( event.GetInt() < 0 )
			mGenerate->Enable(true);
		else
			mProgBar->SetValue(  event.GetInt() );
		mStatus->SetStatusText( event.GetString() );
	}

    void OnThreadStatusUpdate(wxCommandEvent& event){
        mProgBar->SetValue(event.GetInt());
        mStatus->SetStatusText( event.GetString() );
    }

    void OnThreadSuccess(wxCommandEvent& event){
        mProgBar->SetValue(100);
        mStatus->SetStatusText("Success" );
        mGenerate->Enable(true);
    }

    void OnThreadFailure(wxCommandEvent& event){
        mGenerate->Enable(true);
        mProgBar->SetValue(0);
        mStatus->SetStatusText("Failed" );
        wxMessageBox(event.GetString(), wxT("Something went wrong"), wxICON_ERROR);
    }

	// Handlers for GrassGen events.
	void OnImportPress( wxCommandEvent& event );
	void OnAddPress( wxCommandEvent& event );
	void OnRemovePress( wxCommandEvent& event );
	void OnGenPress( wxCommandEvent& event );	

	DECLARE_EVENT_TABLE();

public:
	/** Constructor */
	GUI( wxWindow* parent );
};

#endif // __GUI__
