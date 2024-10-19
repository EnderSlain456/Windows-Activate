#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;

string getWindowsEdition() {
    HKEY hKey;
    const string regPath = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
    string edition;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, regPath.c_str(), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        char value[256];
        DWORD value_length = sizeof(value);
        if (RegQueryValueExA(hKey, "EditionID", NULL, NULL, (LPBYTE)value, &value_length) == ERROR_SUCCESS) {
            edition = string(value, value_length - 1);
        }
        RegCloseKey(hKey);
    } else {
        cerr << "Failed to open registry key." << endl;
        return "";
    }

    return edition;
}

string getProductKey(const string& edition) {
    if (edition == "Professional") {
        return "W269N-WFGWX-YVC9B-4J6C9-T83GX";
    } else if (edition == "Core" || edition == "Home") {
        return "TX9XD-98N7V-6WMQ6-BX7FG-H8Q99";
    } else if (edition == "Enterprise") {
        return "NPPR9-FWDCX-D2C8J-H872K-2YT43";
    } else if (edition == "Education") {
        return "NW6C2-QMPVW-D7KKK-3GKT6-VCFB2";
    } else if (edition == "Home Single Language") {
        return "7HNRX-D7KGG-3K4RQ-4WPJ4-YTDFH";
    } else if (edition == "Core N" || edition == "Home N") {
        return "3KHY7-WNT83-DGQKR-F7HPR-844BM";
    } else if (edition == "Professional N") {
        return "MH37W-N47XK-V7XM9-C7227-GCQG9";
    } else if (edition == "Education N") {
        return "2WH4N-8QGBV-H22JP-CT43Q-MDWWJ";
    } else if (edition == "Enterprise N") {
        return "DPH2V-TTNVB-4X9Q3-TJR4H-KHJW4";
    } else if (edition == "Home Country Specific") {
        return "PVMJN-6DFY6-9CCP6-7BKTT-D3WVR";
    }

    return "";
}

void executeCommand(const string& command) {
    system(command.c_str());
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    string edition = getWindowsEdition();
    if (edition.empty()) {
        cerr << "Could not determine Windows edition." << endl;
        return 1;
    }

    OutputDebugStringA(("Detected Windows Edition: " + edition + "\n").c_str());

    string productKey = getProductKey(edition);
    if (productKey.empty()) {
        cerr << "No product key found for the detected edition: " << edition << endl;
        return 1;
    }

    OutputDebugStringA(("Using Product Key: " + productKey + "\n").c_str());

    executeCommand("slmgr /ipk \"" + productKey + "\"");
    executeCommand("slmgr /skms kms8.msguides.com");
    executeCommand("slmgr /ato");

    OutputDebugStringA("Activation commands executed.\n");
    return 0;
}
