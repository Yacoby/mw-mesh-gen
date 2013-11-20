﻿#ifndef __GUI__
#define __GUI__

#define WORKER_EVENT 50002

/**
@file
Subclass of GrassGen, which is generated by wxFormBuilder.
*/

#include "GrassGen.h"
#include "SettingsEditor.h"
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
		std::string file;
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

	std::string getRegKey(std::string pos, std::string name);

	void genGrass(const std::string& out,
                  const std::string& base,
                  const std::string& ini,
                  const std::vector<std::string> files,
                  int zoffset);
protected:

	void OnThreadEvent(wxCommandEvent& event){
		if ( event.GetInt() < 0 )
			mGenerate->Enable(true);
		else
			mProgBar->SetValue(  event.GetInt() );
		mStatus->SetStatusText( event.GetString() );
		
	}




	// Handlers for GrassGen events.
	void OnImportPress( wxCommandEvent& event );
	void OnAddPress( wxCommandEvent& event );
	void OnRemovePress( wxCommandEvent& event );
	void OnGenPress( wxCommandEvent& event );
	void OnEditorPress( wxCommandEvent& event );
	

	DECLARE_EVENT_TABLE();

public:
	/** Constructor */
	GUI( wxWindow* parent );
};

#endif // __GUI__
