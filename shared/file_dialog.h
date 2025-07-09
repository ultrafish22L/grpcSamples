#pragma once

#include <string>

namespace SharedUtils {

/**
 * Cross-platform file dialog for opening 3D model files
 * Supports Windows, macOS, and Linux
 */
class FileDialog {
public:
    /**
     * Open a file dialog to select a 3D model file
     * @return Path to selected file, or empty string if cancelled
     */
    static std::string openFile();
    
    /**
     * Check if a file has a supported 3D model extension
     * @param filename The filename to check
     * @return true if the file extension is supported
     */
    static bool isSupportedModelFile(const std::string& filename);

private:
    static std::string openFileWindows();
    static std::string openFileMacOS();
    static std::string openFileLinux();
};

// Implementation
inline std::string FileDialog::openFile() {
#ifdef _WIN32
    return openFileWindows();
#elif __APPLE__
    return openFileMacOS();
#else
    return openFileLinux();
#endif
}

inline bool FileDialog::isSupportedModelFile(const std::string& filename) {
    if (filename.length() < 4) return false;
    
    std::string ext = filename.substr(filename.length() - 4);
    // Convert to lowercase
    for (char& c : ext) {
        c = std::tolower(c);
    }
    
    return ext == ".obj" || ext == ".ply" || ext == ".stl";
}

#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>

inline std::string FileDialog::openFileWindows() {
    OPENFILENAMEA ofn;
    char szFile[260] = {0};
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "3D Model Files\0*.obj;*.ply;*.stl\0OBJ Files\0*.obj\0PLY Files\0*.ply\0STL Files\0*.stl\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    ofn.lpstrTitle = "Select 3D Model File";
    
    if (GetOpenFileNameA(&ofn)) {
        return std::string(szFile);
    }
    return "";
}

#elif __APPLE__
#include <CoreFoundation/CoreFoundation.h>

inline std::string FileDialog::openFileMacOS() {
    // Use osascript to show file dialog
    FILE* pipe = popen("osascript -e 'tell application \"System Events\" to activate' -e 'set theFile to choose file with prompt \"Select 3D Model File\" of type {\"obj\", \"ply\", \"stl\"}' -e 'POSIX path of theFile'", "r");
    if (!pipe) return "";
    
    char buffer[1024];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);
    
    // Remove trailing newline
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}

#else
#include <cstdlib>
#include <cstdio>

inline std::string FileDialog::openFileLinux() {
    // Try zenity first (most common)
    FILE* pipe = popen("zenity --file-selection --title='Select 3D Model File' --file-filter='3D Models | *.obj *.ply *.stl' 2>/dev/null", "r");
    if (pipe) {
        char buffer[1024];
        std::string result = "";
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
        int status = pclose(pipe);
        
        if (status == 0 && !result.empty()) {
            // Remove trailing newline
            if (result.back() == '\n') {
                result.pop_back();
            }
            return result;
        }
    }
    
    // Try kdialog as fallback
    pipe = popen("kdialog --getopenfilename . '*.obj *.ply *.stl|3D Model Files' 2>/dev/null", "r");
    if (pipe) {
        char buffer[1024];
        std::string result = "";
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }
        int status = pclose(pipe);
        
        if (status == 0 && !result.empty()) {
            // Remove trailing newline
            if (result.back() == '\n') {
                result.pop_back();
            }
            return result;
        }
    }
    
    // Fallback: print message and return empty
    std::cout << "File dialog not available. Please install zenity or kdialog for file selection." << std::endl;
    return "";
}

#endif

} // namespace SharedUtils