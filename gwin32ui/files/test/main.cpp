void entrypoint() {
    using namespace gwin32ui;

    auto win = Win32Window::Make({});

    win->registerWidget(Widgets::Button({
        .text = L"BUTTON 1!",
        .onClick = [&]() {
            std::cout << "1 CLICKED!" << std::endl;
            selectSaveFile(win.get(), L"All Files (*.*)\0*.*\0", L"Hey!");
            showErrorMsg(win.get(), L"Hey!");
            showWarnMsg(win.get(), L"Hey!");
            showInfoMsg(win.get(), L"Hey!");
            showYesNoMsg(win.get(), L"Hey!");
        }
    }));

    int button2 = win->registerWidget(Widgets::Button({
        .text = L"BUTTON 2!",
        .onClick = [&]() {
            std::cout << "2 CLICKED!" << std::endl;
            selectFolder(win.get(), L"Hey!");
        }
    }));

    win->nextRow();

    win->registerWidget(Widgets::Button({
        .text = L"BUTTON 3!",
        .onClick = [&]() {
            std::cout << "3 CLICKED!, i will click button 2" << std::endl;
            WidgetStatics::Button::click(win->refWidget(button2));
        }
    }));

    win->registerWidget(Widgets::Label({
        .text = L"LABEL 1!"
    }));

    int checkbox1 = win->registerWidget(Widgets::CheckBox({
        .text = L"CHECKBOX 1!",
        .checked = true,
        .onChange = [](bool checked) {
            std::cout << "CHECKBOX 1: " << (checked ? "checked" : "unchecked") << std::endl;
        }
    }));

    win->nextRow();

    win->registerWidget(Widgets::Button({
        .text = L"BUTTON 4!",
        .onClick = [&](){
            std::cout << "4 CLICKED!, i will click checkbox 1" << std::endl;
            WidgetStatics::CheckBox::click(win->refWidget(checkbox1));
        }
    }));

    win->registerWidget(Widgets::TextInput({
        .text = L"TEXT INPUT 1!",
        .onChange = [&](const std::wstring& text) {
            std::wcout << "TEXT INPUT (W): " << text << std::endl;
            std::cout << "TEXT INPUT: " << Win32Utils::wstringToString(text) << std::endl;
        }
    }));

    win->createWidgets();
    win->doGrid();
    win->resizeToGridBounds();
    win->mainloop();
}
