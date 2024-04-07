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
#include "Funcs.h"
#include "LoadOrder.h"

#include <filesystem>
#include <optional>


/** Implementing GrassGen */
class GUI : public GrassGen {
private:
    std::filesystem::path morrowindDirectory;
    std::unique_ptr<LoadOrder> loadOrder;
    std::optional<std::string> getRegKey(const char* pos, const char* name);

protected:
    void sendStatusUpdate(int progressPercent, const std::string &message) {
        wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, WORKER_UPDATE);
        evt.SetInt(progressPercent);
        evt.SetString(message);
        wxPostEvent(this, evt);
    }

    void sendSuccess(int duration) {
        wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, WORKER_SUCCESS);
        evt.SetInt(duration);
        wxPostEvent(this, evt);
    }

    void sendFailure(const std::string &message) {
        wxCommandEvent evt(wxEVT_COMMAND_MENU_SELECTED, WORKER_FAILURE);
        evt.SetString(message);
        wxPostEvent(this, evt);
    }

    void OnThreadStatusUpdate(wxCommandEvent &event) {
        mProgBar->SetValue(event.GetInt());
        mStatus->SetStatusText(event.GetString());
    }

    void OnThreadSuccess(wxCommandEvent &event) {
        mProgBar->SetValue(100);
        auto duration = event.GetInt();
        mStatus->SetStatusText("Success in " + std::to_string(duration) + " seconds");
        mGenerate->Enable(true);
    }

    void OnThreadFailure(wxCommandEvent &event) {
        mGenerate->Enable(true);
        mProgBar->SetValue(0);
        mStatus->SetStatusText("Failed");
        wxMessageBox(event.GetString(), wxT("Something went wrong"), wxICON_ERROR);
    }

    // Handlers for GrassGen events.
    void OnImportPress(wxCommandEvent &event);
    void OnImportOpenMwPress(wxCommandEvent &event);

    void OnAddPress(wxCommandEvent &event);

    void OnRemovePress(wxCommandEvent &event);
    void OnResetPress(wxCommandEvent &event);

    void OnGenPress(wxCommandEvent &event);

DECLARE_EVENT_TABLE()

public:
    /** Constructor */
    GUI(wxWindow *parent);
};

#endif // __GUI__
