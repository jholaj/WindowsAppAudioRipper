// AudioAppRipper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "AudioCapture.h"

void usage()
{
    std::wcout <<
        L"Usage: AudioAppRipper.exe <pid> <outputfilename>\n"
        L"\n"
        L"<pid> is the process ID to capture from capture\n"
        L"<outputfilename> is the WAV file to receive the captured audio (until Ctrl+C is pressed)\n"
        L"\n"
        L"Examples:\n"
        L"\n"
        L"AudioAppRipper.exe 123456 Output.wav\n"
        L"\n"
        L"Captures audio from process 123456 and its children to Output.wav file.\n";
}

CLoopbackCapture loopbackCapture;

int wmain(int argc, wchar_t* argv[])
{

    if (argc != 3)
    {
        usage();
        return 0;
    }

    DWORD processId = wcstoul(argv[1], nullptr, 0);
    if (processId == 0)
    {
        usage();
        return 0;
    }

    PCWSTR outputFile = argv[2];

    CLoopbackCapture loopbackCapture;
    HRESULT hr = loopbackCapture.StartCaptureAsync(processId, outputFile);
    if (FAILED(hr))
    {
        wil::unique_hlocal_string message;
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (PWSTR)&message, 0, nullptr);
        std::wcout << L"Failed to start capture\n0x" << std::hex << hr << L": " << message.get() << L"\n";
    }
    
    std::wcout << L"Capturing audio (Press Ctrl+C to stop)..." << std::endl;

    bool isRecording = true;

    while (isRecording) {
        // If Ctrl+C was pressed => End capturing audio
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState(0x43) & 0x8000) { // Ctrl+C
            std::wcout << L"Stopping capture..." << std::endl;
            loopbackCapture.StopCaptureAsync();
            isRecording = false;
        }

    }

    return 0;
}
