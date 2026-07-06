#include <windows.h>
#include <shlobj.h>

namespace gwin_progress_dialog {
    struct ProgressDialog {
        IProgressDialog* pd;

        ProgressDialog() {
            CoInitialize(nullptr);
            
            CoCreateInstance(
                CLSID_ProgressDialog, nullptr, CLSCTX_ALL,
                IID_IProgressDialog, (void**)&pd
            );
        }

        void setTitle(const wchar_t* title) { pd->SetTitle(title); }
        void setLine(int line, const wchar_t* text) { pd->SetLine(1, text, FALSE, nullptr); }
        void setCancelMsg(const wchar_t* msg) { pd->SetCancelMsg(msg, nullptr); }
        void setProgress(int current, int total) { pd->SetProgress(current, total); }

        void start() {
            pd->StartProgressDialog(
                nullptr, nullptr,
                PROGDLG_NORMAL | PROGDLG_AUTOTIME | PROGDLG_NOCANCEL,
                nullptr
            );
        }

        void close() {
            if (!pd) return;
            pd->StopProgressDialog();
            pd->Release();
            CoUninitialize();
            pd = nullptr;
        }

        ~ProgressDialog() {
            close();
        }
    };
}
