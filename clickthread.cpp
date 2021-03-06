#include "clickthread.h"

ClickThread::ClickThread(QList<const Click*> clicks) {
    this->clicks = clicks;
}

void ClickThread::run() {
    POINT pt;
    HWND hWnd;
    LPARAM lParam;

    keybd_event(VkKeyScan('c'), 0, 0, 0);
    keybd_event(VkKeyScan('c'), 0, KEYEVENTF_KEYUP, 0);

    Sleep(50);
    for(int i = 0; i < clicks.length(); i++) {
        pt.x = const_cast<Click*>(clicks.at(i))->getX();
        pt.y = const_cast<Click*>(clicks.at(i))->getY();

        hWnd = WindowFromPoint(pt);
        lParam = MAKELPARAM(pt.x, pt.y);

        if(const_cast<Click*>(clicks.at(i))->getAlt()) {
            keybd_event(VK_MENU, 0, 0, 0);
            Sleep(50);
        }

        PostMessage(hWnd, WM_RBUTTONDOWN, MK_RBUTTON, lParam);
        PostMessage(hWnd, WM_RBUTTONUP, MK_RBUTTON, lParam);

        if(const_cast<Click*>(clicks.at(i))->getAlt()) {
            Sleep(50);
            keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
            Sleep(50);
        }
    }

    Sleep(50);
    keybd_event(VkKeyScan('c'), 0, 0, 0);
    keybd_event(VkKeyScan('c'), 0, KEYEVENTF_KEYUP, 0);
}

ClickThread::~ClickThread() {
}
