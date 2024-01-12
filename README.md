# Capturing Sound of an App with specified PID
- Only audio from the specified process, and its children, will be captured. Audio rendered by other processes will not be captured.
- If the processes whose audio will be captured does not have any audio rendering streams, then the capturing process receives silence.
- To use this sample, obtain PID for the process tree you wish to capture. Run the sample with the PID and the output WAV file.
- Example:
    - AppRipper.exe 123456 Output.wav
-  Requires Windows 10 build 20348 or later!
- Edited sample app from this [repo](https://github.com/microsoft/Windows-classic-samples)
