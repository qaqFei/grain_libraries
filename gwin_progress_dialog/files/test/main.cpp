void entrypoint() {
    gwin_progress_dialog::ProgressDialog pd {};
    pd.setTitle(L"Title!!");
    pd.start();
    pd.setLine(1, L"Line 1");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    pd.setLine(2, L"Line 2");
    pd.setProgress(20, 100);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pd.setLine(3, L"Line 3");
    pd.setProgress(80, 100);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
