#include "wintoastlib.h"
#include <string>
#include <Windows.h>

using namespace WinToastLib;
using namespace std;


const DWORD period = 3.6e+6; // period when notification will be sent
const DWORD nlong = 6000; // time that notification will dissapear after
wstring imgPath;

enum Results {
	ToastClicked,             // user clicked on the toast
	ToastDismissed,           // user dismissed the toast
	ToastTimeOut,             // toast timed out
	ToastHided,               // application hid the toast
	ToastNotActivated,        // toast was not activated
	ToastFailed,              // toast failed
	SystemNotSupported,       // system does not support toasts
	UnhandledOption,          // unhandled option
	MultipleTextNotSupported, // multiple texts were provided
	InitializationFailure,    // toast notification manager initialization failure
	ToastNotLaunched          // toast could not be launched
};


class CustomHandler : public IWinToastHandler {
	public:
		void toastActivated() const {

			exit(0);
		}

		void toastActivated(int actionIndx) const{

		}

		void toastDismissed(WinToastDismissalReason state) const{
			//exit(ToastFailed);
		}

		void toastFailed() const {

			exit(ToastFailed);
		}
};

void pushNotification() {
	static wstring appName = L"Blink Reminder";
	static wstring appUserModelID = L"Blink Reminder";
	static wstring title = L"Break Time!";
	static wstring subtitle = L"It's time to blink your eyes & to stand up and move!";
	static INT64 expiration = nlong;
	static wstring imagePath = imgPath;


	static WinToastTemplate::AudioOption audioOption = WinToastTemplate::AudioOption::Loop;
	static WinToastTemplate::Scenario scenarioOption = WinToastTemplate::Scenario::Alarm;
	static WinToastTemplate::Duration dur = WinToastTemplate::Duration::System;

	WinToast::instance()->setAppName(appName);
	WinToast::instance()->setAppUserModelId(appUserModelID);

	WinToast::instance()->initialize();




	WinToastTemplate templ(WinToastTemplate::ImageAndText02);
	templ.setFirstLine(title);
	templ.setSecondLine(subtitle);
	templ.setAudioOption(audioOption);
	templ.setScenario(scenarioOption);
	templ.setImagePath(imagePath);
	templ.setDuration(dur);
	templ.setExpiration(nlong);
	//std::vector<std::wstring> actions;

	/*for (auto const& action : actions) {
		templ.addAction(action);
	}*/

	WinToast::instance()->showToast(templ, new CustomHandler());
}


void generateNotification() {
	Sleep(period);
	pushNotification();
	Sleep(nlong);
}


int wmain(int argc, LPWSTR* argv) {
	
	for (int i = 0; i < argc; i++) {
		if (!wcscmp(L"--image", argv[i])) {
			imgPath = argv[++i];
		}
	}
	do {
		generateNotification();
	} while (true);

	//return wmain();
}