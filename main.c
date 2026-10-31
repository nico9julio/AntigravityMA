#define UNICODE
#define _UNICODE
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <shellapi.h>
#include <shlobj.h>
#include <objbase.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdbool.h>
#include "resource.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_PROFILES 64
#define MAX_STR 512

#define ID_EDIT_EXE         101
#define ID_BTN_BROWSE_EXE   102
#define ID_LIST_PROFILES    103
#define ID_EDIT_NAME        104
#define ID_EDIT_EMAIL       105
#define ID_CHK_ISOLATED     106
#define ID_CHK_SKIP_WIZARD  107
#define ID_CHK_SHORTCUT     108
#define ID_BTN_SAVE         109
#define ID_BTN_NEW          110
#define ID_BTN_LAUNCH       111
#define ID_BTN_DELETE       112
#define ID_BTN_REFRESH      113

typedef struct {
    const wchar_t* windowTitle;
    const wchar_t* lblExe;
    const wchar_t* btnBrowse;
    const wchar_t* lblList;
    const wchar_t* colSessionName;
    const wchar_t* colAccountEmail;
    const wchar_t* colTokenMode;
    const wchar_t* colShortcut;
    const wchar_t* colFolder;
    const wchar_t* btnLaunch;
    const wchar_t* btnNew;
    const wchar_t* btnDelete;
    const wchar_t* btnRefresh;
    const wchar_t* grpConfig;
    const wchar_t* lblSessionName;
    const wchar_t* lblEmail;
    const wchar_t* chkIsolated;
    const wchar_t* chkSkipWizard;
    const wchar_t* chkShortcut;
    const wchar_t* btnSave;
    const wchar_t* notLoggedIn;
    const wchar_t* modeIsolated;
    const wchar_t* modePrincipal;
    const wchar_t* shortcutYes;
    const wchar_t* shortcutNo;
    const wchar_t* defaultProfileName;
    const wchar_t* newAccountDefault;
    const wchar_t* fallbackSlug;
    const wchar_t* statusReady;
    const wchar_t* statusDetectedFmt;
    const wchar_t* statusCreatingNew;
    const wchar_t* msgNameRequired;
    const wchar_t* titleNameRequired;
    const wchar_t* shortcutDescFmt;
    const wchar_t* shortcutDescFallback;
    const wchar_t* msgSavedFmt;
    const wchar_t* titleSaved;
    const wchar_t* msgSelectToLaunch;
    const wchar_t* titleLaunch;
    const wchar_t* msgExeNotFound;
    const wchar_t* titleError;
    const wchar_t* statusLaunchingFmt;
    const wchar_t* msgLaunchFailed;
    const wchar_t* msgCannotDeleteMain;
    const wchar_t* titleNotAllowed;
    const wchar_t* msgConfirmDeleteFmt;
    const wchar_t* titleConfirmDelete;
    const wchar_t* statusDeleted;
    const wchar_t* browseTitle;
    const wchar_t* browseFilter;
} UiStrings;

static const UiStrings STRINGS_ES = {
    L"AntigravityMA - Gestor Multi-Cuenta y Perfiles",
    L"Ejecutable de Antigravity:",
    L"Examinar...",
    L"Sesiones / Perfiles de Antigravity en este equipo:",
    L"Nombre de Sesión",
    L"Cuenta (Email)",
    L"Modo de Token",
    L"Acceso Directo",
    L"Carpeta (AppData)",
    L"▶ Iniciar Sesión Seleccionada",
    L"+ Nueva Sesión",
    L"Eliminar Sesión",
    L"Recargar Lista",
    L"Configurar Sesión Seleccionada / Nueva",
    L"Nombre de la Sesión:",
    L"Correo / Cuenta:",
    L"Aislar token fuera del Administrador de Credenciales de Windows (SSH_CONNECTION=1)",
    L"Omitir asistente de instalación del IDE al abrir (ide-install-wizard-shown)",
    L"Crear / actualizar acceso directo en el Escritorio (Antigravity - <Nombre>.lnk)",
    L"Guardar Configuración",
    L"(Sin iniciar sesión)",
    L"Token Aislado (Archivo)",
    L"Credencial Windows (Principal)",
    L"Sí (Escritorio)",
    L"No",
    L"Principal",
    L"NuevaCuenta",
    L"Perfil",
    L"Listo.",
    L"Listo. Se detectaron %d sesiones configuradas en este equipo.",
    L"Creando nueva sesión: escribe el nombre y correo opcional, y pulsa 'Guardar Configuración'.",
    L"Por favor ingresa un nombre para la sesión.",
    L"Nombre requerido",
    L"Antigravity - Sesión %s (%s)",
    L"Perfil independiente",
    L"Sesión '%s' guardada correctamente.",
    L"Configuración Guardada",
    L"Selecciona una sesión de la lista para iniciarla.",
    L"Iniciar Sesión",
    L"No se encontró Antigravity.exe en la ruta indicada.",
    L"Error",
    L"Iniciando Antigravity con la sesión '%s'...",
    L"No se pudo iniciar el proceso de Antigravity.",
    L"La carpeta principal de Antigravity no puede eliminarse por seguridad.",
    L"Acción no permitida",
    L"¿Estás seguro de eliminar la sesión '%s'?\n\nCarpeta: %s\n(Tus proyectos de .gemini no se borrarán).",
    L"Confirmar eliminación",
    L"Sesión eliminada correctamente.",
    L"Seleccionar Antigravity.exe",
    L"Ejecutable de Antigravity (Antigravity.exe)\0Antigravity.exe\0Todos los ejecutables (*.exe)\0*.exe\0"
};

static const UiStrings STRINGS_EN = {
    L"AntigravityMA - Multi-Account & Profile Manager",
    L"Antigravity Executable:",
    L"Browse...",
    L"Antigravity Sessions / Profiles on this PC:",
    L"Session Name",
    L"Account (Email)",
    L"Token Mode",
    L"Shortcut",
    L"Folder (AppData)",
    L"▶ Launch Selected Session",
    L"+ New Session",
    L"Delete Session",
    L"Refresh List",
    L"Configure Selected / New Session",
    L"Session Name:",
    L"Email / Account:",
    L"Isolate token outside Windows Credential Manager (SSH_CONNECTION=1)",
    L"Skip IDE installation wizard on startup (ide-install-wizard-shown)",
    L"Create / update Desktop shortcut (Antigravity - <Name>.lnk)",
    L"Save Configuration",
    L"(Not signed in)",
    L"Isolated Token (File)",
    L"Windows Credential (Main)",
    L"Yes (Desktop)",
    L"No",
    L"Main",
    L"NewAccount",
    L"Profile",
    L"Ready.",
    L"Ready. Detected %d configured sessions on this PC.",
    L"Creating new session: enter a name and optional email, then click 'Save Configuration'.",
    L"Please enter a name for the session.",
    L"Name Required",
    L"Antigravity - Session %s (%s)",
    L"Independent profile",
    L"Session '%s' saved successfully.",
    L"Configuration Saved",
    L"Select a session from the list to launch it.",
    L"Launch Session",
    L"Antigravity.exe was not found at the specified path.",
    L"Error",
    L"Launching Antigravity with session '%s'...",
    L"Could not start the Antigravity process.",
    L"The main Antigravity folder cannot be deleted for safety.",
    L"Action Not Allowed",
    L"Are you sure you want to delete session '%s'?\n\nFolder: %s\n(Your .gemini projects will not be deleted).",
    L"Confirm Deletion",
    L"Session deleted successfully.",
    L"Select Antigravity.exe",
    L"Antigravity Executable (Antigravity.exe)\0Antigravity.exe\0All Executables (*.exe)\0*.exe\0"
};

static const UiStrings* S = &STRINGS_EN;

typedef struct {
    wchar_t displayName[128];
    wchar_t folderName[128];
    wchar_t folderPath[MAX_PATH];
    wchar_t email[128];
    bool isDefaultFolder;
    bool isIsolated;
    bool skipWizard;
    bool hasDesktopShortcut;
    wchar_t existingShortcutPath[MAX_PATH];
} ProfileEntry;

static ProfileEntry g_profiles[MAX_PROFILES];
static int g_profileCount = 0;
static int g_selectedIndex = -1;
static bool g_isCreatingNew = false;

static wchar_t g_appDataDir[MAX_PATH];
static wchar_t g_localAppDataDir[MAX_PATH];
static wchar_t g_userProfileDir[MAX_PATH];
static wchar_t g_desktopDir[MAX_PATH];
static wchar_t g_antigravityExe[MAX_PATH];

static HWND g_hWndMain;
static HWND g_hEditExe, g_hBtnBrowse;
static HWND g_hList;
static HWND g_hEditName, g_hEditEmail;
static HWND g_hChkIsolated, g_hChkSkipWizard, g_hChkShortcut;
static HWND g_hBtnSave, g_hBtnNew, g_hBtnLaunch, g_hBtnDelete, g_hBtnRefresh;
static HWND g_hStatus;
static HFONT g_hFontUI = NULL;
static HFONT g_hFontBold = NULL;

// Detects if Windows UI language is Spanish (Spain es-ES or Mexico es-MX).
// Any other language defaults to English.
static void DetectUiLanguage(LPWSTR lpCmdLine) {
    if (lpCmdLine) {
        if (wcsstr(lpCmdLine, L"--lang=es") != NULL) {
            S = &STRINGS_ES;
            return;
        }
        if (wcsstr(lpCmdLine, L"--lang=en") != NULL) {
            S = &STRINGS_EN;
            return;
        }
    }

    LANGID langId = GetUserDefaultUILanguage();
    WORD primary = PRIMARYLANGID(langId);
    WORD sub = SUBLANGID(langId);

    if (primary == LANG_SPANISH &&
        (sub == SUBLANG_SPANISH || sub == SUBLANG_SPANISH_MODERN || sub == SUBLANG_SPANISH_MEXICAN)) {
        S = &STRINGS_ES;
    } else {
        S = &STRINGS_EN;
    }
}

static void SetStatusText(const wchar_t* msg) {
    if (g_hStatus) SetWindowTextW(g_hStatus, msg);
}

static bool ReadFileToUtf8(const wchar_t* path, char** outBuf, DWORD* outLen) {
    HANDLE hFile = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;
    DWORD size = GetFileSize(hFile, NULL);
    if (size == INVALID_FILE_SIZE || size > 10 * 1024 * 1024) {
        CloseHandle(hFile);
        return false;
    }
    char* buf = (char*)malloc(size + 1);
    if (!buf) {
        CloseHandle(hFile);
        return false;
    }
    DWORD read = 0;
    ReadFile(hFile, buf, size, &read, NULL);
    buf[read] = '\0';
    CloseHandle(hFile);
    *outBuf = buf;
    if (outLen) *outLen = read;
    return true;
}

static bool WriteUtf8File(const wchar_t* path, const char* content) {
    HANDLE hFile = CreateFileW(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;
    DWORD len = (DWORD)strlen(content);
    DWORD written = 0;
    BOOL ok = WriteFile(hFile, content, len, &written, NULL);
    CloseHandle(hFile);
    return ok && (written == len);
}

// Lightweight JSON string value extractor for flat JSON keys like "key": "value"
static bool ExtractJsonString(const char* json, const char* key, wchar_t* outValue, size_t maxChars) {
    outValue[0] = L'\0';
    if (!json || !key) return false;
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "\"%s\"", key);
    const char* p = strstr(json, pattern);
    if (!p) return false;
    p += strlen(pattern);
    while (*p && (*p == ' ' || *p == '\t' || *p == ':')) p++;
    if (*p != '\"') return false;
    p++;
    char valUtf8[512];
    size_t i = 0;
    while (*p && *p != '\"' && i < sizeof(valUtf8) - 1) {
        if (*p == '\\' && *(p + 1)) {
            p++;
        }
        valUtf8[i++] = *p++;
    }
    valUtf8[i] = '\0';
    MultiByteToWideChar(CP_UTF8, 0, valUtf8, -1, outValue, (int)maxChars);
    return true;
}

// Updates or inserts a string key in app_storage.json while preserving all other keys
static bool SaveAppStorageJson(const wchar_t* folderPath, const wchar_t* email, const wchar_t* displayName, bool skipWizard) {
    wchar_t jsonPath[MAX_PATH];
    swprintf(jsonPath, MAX_PATH, L"%s\\app_storage.json", folderPath);

    char* existing = NULL;
    DWORD len = 0;
    bool hasExisting = ReadFileToUtf8(jsonPath, &existing, &len);

    char emailUtf8[256] = {0};
    char nameUtf8[256] = {0};
    WideCharToMultiByte(CP_UTF8, 0, email, -1, emailUtf8, sizeof(emailUtf8), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, displayName, -1, nameUtf8, sizeof(nameUtf8), NULL, NULL);

    if (!hasExisting || !existing || len < 5) {
        if (existing) free(existing);
        char newJson[1024];
        snprintf(newJson, sizeof(newJson),
            "{\n"
            "  \"ide-install-wizard-shown\": \"%s\",\n"
            "  \"jetski.onboarding.lastLoginUsername\": \"%s\",\n"
            "  \"agy.profile.displayName\": \"%s\",\n"
            "  \"didAskForNotificationPermission\": \"true\"\n"
            "}\n",
            skipWizard ? "true" : "false",
            emailUtf8,
            nameUtf8);
        return WriteUtf8File(jsonPath, newJson);
    }

    // Parse existing lines except the keys we are updating, then append ours cleanly
    size_t outCap = len + 2048;
    char* outJson = (char*)malloc(outCap);
    if (!outJson) {
        free(existing);
        return false;
    }
    strcpy(outJson, "{\n");

    char* line = strtok(existing, "\r\n");
    bool firstEntry = true;
    while (line) {
        const char* t = line;
        while (*t == ' ' || *t == '\t') t++;
        if (*t != '{' && *t != '}' && *t != '\0') {
            if (!strstr(t, "\"ide-install-wizard-shown\"") &&
                !strstr(t, "\"jetski.onboarding.lastLoginUsername\"") &&
                !strstr(t, "\"agy.profile.displayName\"")) {
                char cleanLine[2048];
                strncpy(cleanLine, t, sizeof(cleanLine) - 1);
                cleanLine[sizeof(cleanLine) - 1] = '\0';
                size_t clen = strlen(cleanLine);
                while (clen > 0 && (cleanLine[clen - 1] == ',' || cleanLine[clen - 1] == ' ' || cleanLine[clen - 1] == '\t')) {
                    cleanLine[--clen] = '\0';
                }
                if (clen > 0) {
                    if (!firstEntry) strcat(outJson, ",\n");
                    strcat(outJson, "  ");
                    strcat(outJson, cleanLine);
                    firstEntry = false;
                }
            }
        }
        line = strtok(NULL, "\r\n");
    }

    char tail[1024];
    snprintf(tail, sizeof(tail),
        "%s  \"ide-install-wizard-shown\": \"%s\",\n"
        "  \"jetski.onboarding.lastLoginUsername\": \"%s\",\n"
        "  \"agy.profile.displayName\": \"%s\"\n"
        "}\n",
        firstEntry ? "" : ",\n",
        skipWizard ? "true" : "false",
        emailUtf8,
        nameUtf8);
    strcat(outJson, tail);

    bool ok = WriteUtf8File(jsonPath, outJson);
    free(outJson);
    free(existing);
    return ok;
}

static bool CreateShellShortcut(const wchar_t* shortcutPath, const wchar_t* targetPath, const wchar_t* arguments, const wchar_t* workingDir, const wchar_t* iconPath, const wchar_t* description) {
    IShellLinkW* psl = NULL;
    HRESULT hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLinkW, (LPVOID*)&psl);
    if (FAILED(hr)) return false;

    psl->lpVtbl->SetPath(psl, targetPath);
    if (arguments) psl->lpVtbl->SetArguments(psl, arguments);
    if (workingDir) psl->lpVtbl->SetWorkingDirectory(psl, workingDir);
    if (iconPath) psl->lpVtbl->SetIconLocation(psl, iconPath, 0);
    if (description) psl->lpVtbl->SetDescription(psl, description);

    IPersistFile* ppf = NULL;
    hr = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile, (LPVOID*)&ppf);
    bool success = false;
    if (SUCCEEDED(hr)) {
        hr = ppf->lpVtbl->Save(ppf, shortcutPath, TRUE);
        success = SUCCEEDED(hr);
        ppf->lpVtbl->Release(ppf);
    }
    psl->lpVtbl->Release(psl);
    return success;
}

static bool ReadShortcutInfo(const wchar_t* shortcutPath, wchar_t* outTarget, wchar_t* outArgs) {
    outTarget[0] = L'\0';
    outArgs[0] = L'\0';
    IShellLinkW* psl = NULL;
    HRESULT hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLinkW, (LPVOID*)&psl);
    if (FAILED(hr)) return false;

    IPersistFile* ppf = NULL;
    hr = psl->lpVtbl->QueryInterface(psl, &IID_IPersistFile, (LPVOID*)&ppf);
    bool ok = false;
    if (SUCCEEDED(hr)) {
        if (SUCCEEDED(ppf->lpVtbl->Load(ppf, shortcutPath, STGM_READ))) {
            psl->lpVtbl->GetPath(psl, outTarget, MAX_PATH, NULL, 0);
            psl->lpVtbl->GetArguments(psl, outArgs, MAX_STR);
            ok = true;
        }
        ppf->lpVtbl->Release(ppf);
    }
    psl->lpVtbl->Release(psl);
    return ok;
}

static bool GenerateVbsLauncher(const ProfileEntry* prof) {
    wchar_t vbsPath[MAX_PATH];
    swprintf(vbsPath, MAX_PATH, L"%s\\launch-profile.vbs", prof->folderPath);

    wchar_t exeDir[MAX_PATH];
    wcscpy_s(exeDir, MAX_PATH, g_antigravityExe);
    PathRemoveFileSpecW(exeDir);

    wchar_t sharedTokenPath[MAX_PATH];
    swprintf(sharedTokenPath, MAX_PATH, L"%s\\.gemini\\antigravity\\jetski-standalone-oauth-token", g_userProfileDir);

    wchar_t profileTokenPath[MAX_PATH];
    swprintf(profileTokenPath, MAX_PATH, L"%s\\oauth-token.bin", prof->folderPath);

    char exeUtf8[MAX_PATH], exeDirUtf8[MAX_PATH], folderUtf8[MAX_PATH], sharedTokUtf8[MAX_PATH], profTokUtf8[MAX_PATH];
    WideCharToMultiByte(CP_UTF8, 0, g_antigravityExe, -1, exeUtf8, sizeof(exeUtf8), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, exeDir, -1, exeDirUtf8, sizeof(exeDirUtf8), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, prof->folderPath, -1, folderUtf8, sizeof(folderUtf8), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, sharedTokenPath, -1, sharedTokUtf8, sizeof(sharedTokUtf8), NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, profileTokenPath, -1, profTokUtf8, sizeof(profTokUtf8), NULL, NULL);

    char vbsContent[4096];
    if (prof->isIsolated) {
        snprintf(vbsContent, sizeof(vbsContent),
            "Set WshShell = CreateObject(\"WScript.Shell\")\r\n"
            "Set FSO = CreateObject(\"Scripting.FileSystemObject\")\r\n"
            "Set WshEnv = WshShell.Environment(\"PROCESS\")\r\n"
            "WshEnv(\"SSH_CONNECTION\") = \"1\"\r\n"
            "If FSO.FileExists(\"%s\") Then\r\n"
            "    On Error Resume Next\r\n"
            "    FSO.CopyFile \"%s\", \"%s\", True\r\n"
            "    On Error GoTo 0\r\n"
            "End If\r\n"
            "WshShell.CurrentDirectory = \"%s\"\r\n"
            "WshShell.Run \"\"\"%s\"\" --user-data-dir=\"\"%s\"\"\", 1, False\r\n",
            profTokUtf8, profTokUtf8, sharedTokUtf8,
            exeDirUtf8, exeUtf8, folderUtf8);
    } else {
        snprintf(vbsContent, sizeof(vbsContent),
            "Set WshShell = CreateObject(\"WScript.Shell\")\r\n"
            "WshShell.CurrentDirectory = \"%s\"\r\n"
            "WshShell.Run \"\"\"%s\"\" --user-data-dir=\"\"%s\"\"\", 1, False\r\n",
            exeDirUtf8, exeUtf8, folderUtf8);
    }
    return WriteUtf8File(vbsPath, vbsContent);
}

// Links the isolated token file via NTFS Hardlink so any login/refresh in language_server.exe
// automatically updates this profile's private oauth-token.bin
static void SyncIsolatedTokenHardlink(const ProfileEntry* prof) {
    if (!prof->isIsolated) return;

    wchar_t geminiAntigravityDir[MAX_PATH];
    swprintf(geminiAntigravityDir, MAX_PATH, L"%s\\.gemini\\antigravity", g_userProfileDir);
    SHCreateDirectoryExW(NULL, geminiAntigravityDir, NULL);

    wchar_t sharedTokenPath[MAX_PATH];
    swprintf(sharedTokenPath, MAX_PATH, L"%s\\jetski-standalone-oauth-token", geminiAntigravityDir);

    wchar_t profileTokenPath[MAX_PATH];
    swprintf(profileTokenPath, MAX_PATH, L"%s\\oauth-token.bin", prof->folderPath);

    // If profile already has its own token file, point sharedTokenPath to it via hardlink
    if (PathFileExistsW(profileTokenPath)) {
        DeleteFileW(sharedTokenPath);
        if (!CreateHardLinkW(sharedTokenPath, profileTokenPath, NULL)) {
            CopyFileW(profileTokenPath, sharedTokenPath, FALSE);
        }
    } else if (PathFileExistsW(sharedTokenPath) && g_profileCount <= 2) {
        // First time migrating existing shared token to this isolated profile
        if (!CreateHardLinkW(profileTokenPath, sharedTokenPath, NULL)) {
            CopyFileW(sharedTokenPath, profileTokenPath, FALSE);
        }
    }
}

static void InspectDesktopShortcutsForProfile(ProfileEntry* prof) {
    prof->hasDesktopShortcut = false;
    prof->existingShortcutPath[0] = L'\0';

    wchar_t searchPattern[MAX_PATH];
    swprintf(searchPattern, MAX_PATH, L"%s\\Antigravity - *.lnk", g_desktopDir);

    WIN32_FIND_DATAW fd;
    HANDLE hFind = FindFirstFileW(searchPattern, &fd);
    if (hFind == INVALID_HANDLE_VALUE) return;

    do {
        wchar_t lnkPath[MAX_PATH];
        swprintf(lnkPath, MAX_PATH, L"%s\\%s", g_desktopDir, fd.cFileName);
        wchar_t target[MAX_PATH], args[MAX_STR];
        if (ReadShortcutInfo(lnkPath, target, args)) {
            bool matches = false;
            if (prof->isDefaultFolder) {
                wchar_t exactArg[MAX_PATH];
                swprintf(exactArg, MAX_PATH, L"--user-data-dir=\"%s\"", prof->folderPath);
                if (wcsstr(args, exactArg) != NULL) matches = true;
            } else {
                if (wcsstr(args, prof->folderName) != NULL) matches = true;
            }
            if (matches) {
                prof->hasDesktopShortcut = true;
                wcscpy_s(prof->existingShortcutPath, MAX_PATH, lnkPath);
                if (prof->displayName[0] == L'\0') {
                    const wchar_t* prefix = L"Antigravity - ";
                    if (wcsncmp(fd.cFileName, prefix, wcslen(prefix)) == 0) {
                        wcscpy_s(prof->displayName, 128, fd.cFileName + wcslen(prefix));
                        wchar_t* dot = wcsrchr(prof->displayName, L'.');
                        if (dot) *dot = L'\0';
                    }
                }
                break;
            }
        }
    } while (FindNextFileW(hFind, &fd));
    FindClose(hFind);
}

static void LoadProfileFromDir(const wchar_t* folderName, bool isDefault) {
    if (g_profileCount >= MAX_PROFILES) return;
    ProfileEntry* p = &g_profiles[g_profileCount];
    ZeroMemory(p, sizeof(ProfileEntry));

    wcscpy_s(p->folderName, 128, folderName);
    swprintf(p->folderPath, MAX_PATH, L"%s\\%s", g_appDataDir, folderName);
    p->isDefaultFolder = isDefault;
    p->isIsolated = !isDefault;
    p->skipWizard = true;

    wchar_t jsonPath[MAX_PATH];
    swprintf(jsonPath, MAX_PATH, L"%s\\app_storage.json", p->folderPath);
    char* json = NULL;
    if (ReadFileToUtf8(jsonPath, &json, NULL)) {
        ExtractJsonString(json, "jetski.onboarding.lastLoginUsername", p->email, 128);
        ExtractJsonString(json, "agy.profile.displayName", p->displayName, 128);
        wchar_t wiz[32];
        if (ExtractJsonString(json, "ide-install-wizard-shown", wiz, 32)) {
            p->skipWizard = (_wcsicmp(wiz, L"true") == 0);
        }
        free(json);
    }

    // Check if launch-profile.vbs or launch-*.vbs exists to detect isolation mode
    wchar_t vbsSearch[MAX_PATH];
    swprintf(vbsSearch, MAX_PATH, L"%s\\launch*.vbs", p->folderPath);
    WIN32_FIND_DATAW fd;
    HANDLE hFind = FindFirstFileW(vbsSearch, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        wchar_t vbsPath[MAX_PATH];
        swprintf(vbsPath, MAX_PATH, L"%s\\%s", p->folderPath, fd.cFileName);
        char* vbsContent = NULL;
        if (ReadFileToUtf8(vbsPath, &vbsContent, NULL)) {
            if (strstr(vbsContent, "SSH_CONNECTION")) {
                p->isIsolated = true;
            }
            free(vbsContent);
        }
        FindClose(hFind);
    }

    InspectDesktopShortcutsForProfile(p);

    if (p->displayName[0] == L'\0') {
        if (isDefault) {
            if (p->email[0] != L'\0') {
                wcscpy_s(p->displayName, 128, p->email);
                wchar_t* at = wcschr(p->displayName, L'@');
                if (at) *at = L'\0';
            } else {
                wcscpy_s(p->displayName, 128, S->defaultProfileName);
            }
        } else {
            if (_wcsnicmp(folderName, L"Antigravity-", 12) == 0) {
                wcscpy_s(p->displayName, 128, folderName + 12);
            } else {
                wcscpy_s(p->displayName, 128, folderName);
            }
        }
    }

    g_profileCount++;
}

static void RefreshProfileList(void) {
    g_profileCount = 0;

    // 1. Default profile (%APPDATA%\Antigravity)
    wchar_t defaultDir[MAX_PATH];
    swprintf(defaultDir, MAX_PATH, L"%s\\Antigravity", g_appDataDir);
    if (PathFileExistsW(defaultDir)) {
        LoadProfileFromDir(L"Antigravity", true);
    }

    // 2. All %APPDATA%\Antigravity-* folders
    wchar_t searchPattern[MAX_PATH];
    swprintf(searchPattern, MAX_PATH, L"%s\\Antigravity-*", g_appDataDir);
    WIN32_FIND_DATAW fd;
    HANDLE hFind = FindFirstFileW(searchPattern, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                LoadProfileFromDir(fd.cFileName, false);
            }
        } while (FindNextFileW(hFind, &fd));
        FindClose(hFind);
    }

    // Populate ListView
    ListView_DeleteAllItems(g_hList);
    for (int i = 0; i < g_profileCount; i++) {
        LVITEMW lvi = {0};
        lvi.mask = LVIF_TEXT;
        lvi.iItem = i;
        lvi.pszText = g_profiles[i].displayName;
        ListView_InsertItem(g_hList, &lvi);

        ListView_SetItemText(g_hList, i, 1, (LPWSTR)(g_profiles[i].email[0] ? g_profiles[i].email : S->notLoggedIn));
        ListView_SetItemText(g_hList, i, 2, (LPWSTR)(g_profiles[i].isIsolated ? S->modeIsolated : S->modePrincipal));
        ListView_SetItemText(g_hList, i, 3, (LPWSTR)(g_profiles[i].hasDesktopShortcut ? S->shortcutYes : S->shortcutNo));
        ListView_SetItemText(g_hList, i, 4, g_profiles[i].folderName);
    }

    if (g_profileCount > 0) {
        ListView_SetItemState(g_hList, 0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
    }
    wchar_t msg[256];
    swprintf(msg, 256, S->statusDetectedFmt, g_profileCount);
    SetStatusText(msg);
}

static void PopulateFormFromSelection(int idx) {
    g_selectedIndex = idx;
    g_isCreatingNew = false;
    if (idx < 0 || idx >= g_profileCount) {
        SetWindowTextW(g_hEditName, L"");
        SetWindowTextW(g_hEditEmail, L"");
        SendMessageW(g_hChkIsolated, BM_SETCHECK, BST_CHECKED, 0);
        SendMessageW(g_hChkSkipWizard, BM_SETCHECK, BST_CHECKED, 0);
        SendMessageW(g_hChkShortcut, BM_SETCHECK, BST_CHECKED, 0);
        EnableWindow(g_hChkIsolated, TRUE);
        EnableWindow(g_hBtnDelete, FALSE);
        return;
    }

    ProfileEntry* p = &g_profiles[idx];
    SetWindowTextW(g_hEditName, p->displayName);
    SetWindowTextW(g_hEditEmail, p->email);
    SendMessageW(g_hChkIsolated, BM_SETCHECK, p->isIsolated ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessageW(g_hChkSkipWizard, BM_SETCHECK, p->skipWizard ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessageW(g_hChkShortcut, BM_SETCHECK, p->hasDesktopShortcut ? BST_CHECKED : BST_UNCHECKED, 0);

    // Default profile always uses Windows Credential Manager to keep principal session intact
    EnableWindow(g_hChkIsolated, !p->isDefaultFolder);
    EnableWindow(g_hBtnDelete, !p->isDefaultFolder);
}

static void PrepareNewProfileForm(void) {
    g_isCreatingNew = true;
    g_selectedIndex = -1;
    ListView_SetItemState(g_hList, -1, 0, LVIS_SELECTED | LVIS_FOCUSED);
    SetWindowTextW(g_hEditName, S->newAccountDefault);
    SetWindowTextW(g_hEditEmail, L"");
    SendMessageW(g_hChkIsolated, BM_SETCHECK, BST_CHECKED, 0);
    SendMessageW(g_hChkSkipWizard, BM_SETCHECK, BST_CHECKED, 0);
    SendMessageW(g_hChkShortcut, BM_SETCHECK, BST_CHECKED, 0);
    EnableWindow(g_hChkIsolated, TRUE);
    EnableWindow(g_hBtnDelete, FALSE);
    SetFocus(g_hEditName);
    SendMessageW(g_hEditName, EM_SETSEL, 0, -1);
    SetStatusText(S->statusCreatingNew);
}

static void SanitizeFolderName(const wchar_t* input, wchar_t* output, size_t maxLen) {
    size_t j = 0;
    for (size_t i = 0; input[i] != L'\0' && j < maxLen - 1; i++) {
        wchar_t c = input[i];
        if ((c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z') ||
            (c >= L'0' && c <= L'9') || c == L'-' || c == L'_') {
            output[j++] = c;
        } else if (c == L' ') {
            output[j++] = L'_';
        }
    }
    output[j] = L'\0';
    if (j == 0) wcscpy_s(output, maxLen, S->fallbackSlug);
}

static void SaveCurrentProfile(void) {
    GetWindowTextW(g_hEditExe, g_antigravityExe, MAX_PATH);
    wchar_t name[128] = {0};
    wchar_t email[128] = {0};
    GetWindowTextW(g_hEditName, name, 128);
    GetWindowTextW(g_hEditEmail, email, 128);

    if (wcslen(name) == 0) {
        MessageBoxW(g_hWndMain, S->msgNameRequired, S->titleNameRequired, MB_ICONWARNING);
        return;
    }

    bool isIsolated = (SendMessageW(g_hChkIsolated, BM_GETCHECK, 0, 0) == BST_CHECKED);
    bool skipWizard = (SendMessageW(g_hChkSkipWizard, BM_GETCHECK, 0, 0) == BST_CHECKED);
    bool wantShortcut = (SendMessageW(g_hChkShortcut, BM_GETCHECK, 0, 0) == BST_CHECKED);

    ProfileEntry prof = {0};
    if (!g_isCreatingNew && g_selectedIndex >= 0 && g_selectedIndex < g_profileCount) {
        prof = g_profiles[g_selectedIndex];
        wcscpy_s(prof.displayName, 128, name);
        wcscpy_s(prof.email, 128, email);
        prof.isIsolated = prof.isDefaultFolder ? false : isIsolated;
        prof.skipWizard = skipWizard;
    } else {
        wcscpy_s(prof.displayName, 128, name);
        wcscpy_s(prof.email, 128, email);
        prof.isDefaultFolder = false;
        prof.isIsolated = isIsolated;
        prof.skipWizard = skipWizard;

        wchar_t slug[96];
        SanitizeFolderName(name, slug, 96);
        swprintf(prof.folderName, 128, L"Antigravity-%s", slug);
        swprintf(prof.folderPath, MAX_PATH, L"%s\\%s", g_appDataDir, prof.folderName);
    }

    SHCreateDirectoryExW(NULL, prof.folderPath, NULL);
    SaveAppStorageJson(prof.folderPath, prof.email, prof.displayName, prof.skipWizard);
    GenerateVbsLauncher(&prof);
    SyncIsolatedTokenHardlink(&prof);

    // Remove old shortcut if renamed or unchecked
    if (prof.existingShortcutPath[0] != L'\0' && PathFileExistsW(prof.existingShortcutPath)) {
        DeleteFileW(prof.existingShortcutPath);
    }

    if (wantShortcut) {
        wchar_t lnkPath[MAX_PATH];
        swprintf(lnkPath, MAX_PATH, L"%s\\Antigravity - %s.lnk", g_desktopDir, prof.displayName);

        wchar_t exeDir[MAX_PATH];
        wcscpy_s(exeDir, MAX_PATH, g_antigravityExe);
        PathRemoveFileSpecW(exeDir);

        wchar_t desc[256];
        swprintf(desc, 256, S->shortcutDescFmt, prof.displayName, prof.email[0] ? prof.email : S->shortcutDescFallback);

        if (prof.isIsolated) {
            wchar_t vbsArg[MAX_PATH];
            swprintf(vbsArg, MAX_PATH, L"\"%s\\launch-profile.vbs\"", prof.folderPath);
            CreateShellShortcut(lnkPath, L"C:\\Windows\\System32\\wscript.exe", vbsArg, exeDir, g_antigravityExe, desc);
        } else {
            wchar_t directArg[MAX_PATH];
            swprintf(directArg, MAX_PATH, L"--user-data-dir=\"%s\"", prof.folderPath);
            CreateShellShortcut(lnkPath, g_antigravityExe, directArg, exeDir, g_antigravityExe, desc);
        }
    }

    RefreshProfileList();
    // Reselect saved profile
    for (int i = 0; i < g_profileCount; i++) {
        if (_wcsicmp(g_profiles[i].folderName, prof.folderName) == 0) {
            ListView_SetItemState(g_hList, i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
            PopulateFormFromSelection(i);
            break;
        }
    }

    wchar_t msg[256];
    swprintf(msg, 256, S->msgSavedFmt, prof.displayName);
    SetStatusText(msg);
    MessageBoxW(g_hWndMain, msg, S->titleSaved, MB_ICONINFORMATION);
}

static void LaunchSelectedProfile(void) {
    if (g_selectedIndex < 0 || g_selectedIndex >= g_profileCount) {
        MessageBoxW(g_hWndMain, S->msgSelectToLaunch, S->titleLaunch, MB_ICONWARNING);
        return;
    }

    GetWindowTextW(g_hEditExe, g_antigravityExe, MAX_PATH);
    if (!PathFileExistsW(g_antigravityExe)) {
        MessageBoxW(g_hWndMain, S->msgExeNotFound, S->titleError, MB_ICONERROR);
        return;
    }

    ProfileEntry* p = &g_profiles[g_selectedIndex];
    SyncIsolatedTokenHardlink(p);

    if (p->isIsolated) {
        SetEnvironmentVariableW(L"SSH_CONNECTION", L"1");
    } else {
        SetEnvironmentVariableW(L"SSH_CONNECTION", NULL);
    }

    wchar_t cmdLine[MAX_PATH * 2];
    swprintf(cmdLine, MAX_PATH * 2, L"\"%s\" --user-data-dir=\"%s\"", g_antigravityExe, p->folderPath);

    wchar_t exeDir[MAX_PATH];
    wcscpy_s(exeDir, MAX_PATH, g_antigravityExe);
    PathRemoveFileSpecW(exeDir);

    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi = {0};
    if (CreateProcessW(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, exeDir, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        wchar_t msg[256];
        swprintf(msg, 256, S->statusLaunchingFmt, p->displayName);
        SetStatusText(msg);
    } else {
        MessageBoxW(g_hWndMain, S->msgLaunchFailed, S->titleError, MB_ICONERROR);
    }
}

static void DeleteSelectedProfile(void) {
    if (g_selectedIndex < 0 || g_selectedIndex >= g_profileCount) return;
    ProfileEntry* p = &g_profiles[g_selectedIndex];
    if (p->isDefaultFolder) {
        MessageBoxW(g_hWndMain, S->msgCannotDeleteMain, S->titleNotAllowed, MB_ICONWARNING);
        return;
    }

    wchar_t confirmMsg[512];
    swprintf(confirmMsg, 512, S->msgConfirmDeleteFmt, p->displayName, p->folderPath);

    if (MessageBoxW(g_hWndMain, confirmMsg, S->titleConfirmDelete, MB_YESNO | MB_ICONQUESTION) != IDYES) {
        return;
    }

    if (p->existingShortcutPath[0] != L'\0' && PathFileExistsW(p->existingShortcutPath)) {
        DeleteFileW(p->existingShortcutPath);
    }

    // SHFileOperationW requires double-null-terminated string
    wchar_t doubleNullPath[MAX_PATH + 2] = {0};
    wcscpy_s(doubleNullPath, MAX_PATH, p->folderPath);

    SHFILEOPSTRUCTW fileOp = {0};
    fileOp.hwnd = g_hWndMain;
    fileOp.wFunc = FO_DELETE;
    fileOp.pFrom = doubleNullPath;
    fileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
    SHFileOperationW(&fileOp);

    RefreshProfileList();
    SetStatusText(S->statusDeleted);
}

static void BrowseForAntigravityExe(void) {
    wchar_t file[MAX_PATH] = {0};
    GetWindowTextW(g_hEditExe, file, MAX_PATH);

    OPENFILENAMEW ofn = { sizeof(ofn) };
    ofn.hwndOwner = g_hWndMain;
    ofn.lpstrFilter = S->browseFilter;
    ofn.lpstrFile = file;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrTitle = S->browseTitle;

    if (GetOpenFileNameW(&ofn)) {
        wcscpy_s(g_antigravityExe, MAX_PATH, file);
        SetWindowTextW(g_hEditExe, g_antigravityExe);
    }
}

static void ApplyFontRecursive(HWND hWnd) {
    SendMessageW(hWnd, WM_SETFONT, (WPARAM)g_hFontUI, TRUE);
    for (HWND child = GetWindow(hWnd, GW_CHILD); child != NULL; child = GetWindow(child, GW_HWNDNEXT)) {
        ApplyFontRecursive(child);
    }
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        g_hFontUI = CreateFontW(-14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
        g_hFontBold = CreateFontW(-14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

        // Top section: Antigravity.exe path
        CreateWindowW(L"STATIC", S->lblExe, WS_CHILD | WS_VISIBLE,
            16, 16, 170, 22, hWnd, NULL, NULL, NULL);
        g_hEditExe = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", g_antigravityExe,
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            185, 13, 470, 25, hWnd, (HMENU)ID_EDIT_EXE, NULL, NULL);
        g_hBtnBrowse = CreateWindowW(L"BUTTON", S->btnBrowse, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            665, 12, 95, 27, hWnd, (HMENU)ID_BTN_BROWSE_EXE, NULL, NULL);

        // Profiles ListView
        HWND hLblList = CreateWindowW(L"STATIC", S->lblList, WS_CHILD | WS_VISIBLE,
            16, 50, 450, 20, hWnd, NULL, NULL, NULL);

        g_hList = CreateWindowExW(WS_EX_CLIENTEDGE, WC_LISTVIEWW, L"",
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS,
            16, 74, 744, 175, hWnd, (HMENU)ID_LIST_PROFILES, NULL, NULL);
        ListView_SetExtendedListViewStyle(g_hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);

        LVCOLUMNW col = {0};
        col.mask = LVCF_TEXT | LVCF_WIDTH;
        col.pszText = (LPWSTR)S->colSessionName; col.cx = 145; ListView_InsertColumn(g_hList, 0, &col);
        col.pszText = (LPWSTR)S->colAccountEmail; col.cx = 195; ListView_InsertColumn(g_hList, 1, &col);
        col.pszText = (LPWSTR)S->colTokenMode; col.cx = 175; ListView_InsertColumn(g_hList, 2, &col);
        col.pszText = (LPWSTR)S->colShortcut; col.cx = 100; ListView_InsertColumn(g_hList, 3, &col);
        col.pszText = (LPWSTR)S->colFolder; col.cx = 120; ListView_InsertColumn(g_hList, 4, &col);

        // Quick action bar below list
        g_hBtnLaunch = CreateWindowW(L"BUTTON", S->btnLaunch, WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            16, 258, 215, 32, hWnd, (HMENU)ID_BTN_LAUNCH, NULL, NULL);
        g_hBtnNew = CreateWindowW(L"BUTTON", S->btnNew, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            242, 258, 140, 32, hWnd, (HMENU)ID_BTN_NEW, NULL, NULL);
        g_hBtnDelete = CreateWindowW(L"BUTTON", S->btnDelete, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            392, 258, 140, 32, hWnd, (HMENU)ID_BTN_DELETE, NULL, NULL);
        g_hBtnRefresh = CreateWindowW(L"BUTTON", S->btnRefresh, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            630, 258, 130, 32, hWnd, (HMENU)ID_BTN_REFRESH, NULL, NULL);

        // GroupBox for editing / configuring profile
        CreateWindowW(L"BUTTON", S->grpConfig, WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            16, 302, 744, 175, hWnd, NULL, NULL, NULL);

        CreateWindowW(L"STATIC", S->lblSessionName, WS_CHILD | WS_VISIBLE,
            34, 332, 145, 22, hWnd, NULL, NULL, NULL);
        g_hEditName = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            185, 329, 230, 25, hWnd, (HMENU)ID_EDIT_NAME, NULL, NULL);

        CreateWindowW(L"STATIC", S->lblEmail, WS_CHILD | WS_VISIBLE,
            435, 332, 110, 22, hWnd, NULL, NULL, NULL);
        g_hEditEmail = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            545, 329, 195, 25, hWnd, (HMENU)ID_EDIT_EMAIL, NULL, NULL);

        g_hChkIsolated = CreateWindowW(L"BUTTON",
            S->chkIsolated,
            WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
            34, 368, 530, 24, hWnd, (HMENU)ID_CHK_ISOLATED, NULL, NULL);

        g_hChkSkipWizard = CreateWindowW(L"BUTTON",
            S->chkSkipWizard,
            WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
            34, 396, 530, 24, hWnd, (HMENU)ID_CHK_SKIP_WIZARD, NULL, NULL);

        g_hChkShortcut = CreateWindowW(L"BUTTON",
            S->chkShortcut,
            WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
            34, 424, 530, 24, hWnd, (HMENU)ID_CHK_SHORTCUT, NULL, NULL);

        g_hBtnSave = CreateWindowW(L"BUTTON", S->btnSave, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            565, 412, 175, 42, hWnd, (HMENU)ID_BTN_SAVE, NULL, NULL);

        g_hStatus = CreateWindowExW(0, STATUSCLASSNAMEW, S->statusReady,
            WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
            0, 0, 0, 0, hWnd, NULL, NULL, NULL);

        ApplyFontRecursive(hWnd);
        SendMessageW(hLblList, WM_SETFONT, (WPARAM)g_hFontBold, TRUE);
        SendMessageW(g_hBtnLaunch, WM_SETFONT, (WPARAM)g_hFontBold, TRUE);
        SendMessageW(g_hBtnSave, WM_SETFONT, (WPARAM)g_hFontBold, TRUE);

        RefreshProfileList();
        return 0;
    }

    case WM_SIZE: {
        SendMessageW(g_hStatus, WM_SIZE, 0, 0);
        return 0;
    }

    case WM_NOTIFY: {
        LPNMHDR nm = (LPNMHDR)lParam;
        if (nm->idFrom == ID_LIST_PROFILES) {
            if (nm->code == LVN_ITEMCHANGED) {
                LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
                if ((pnmv->uChanged & LVIF_STATE) && (pnmv->uNewState & LVIS_SELECTED)) {
                    PopulateFormFromSelection(pnmv->iItem);
                }
            } else if (nm->code == NM_DBLCLK) {
                LaunchSelectedProfile();
            }
        }
        return 0;
    }

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case ID_BTN_BROWSE_EXE:
            BrowseForAntigravityExe();
            break;
        case ID_BTN_NEW:
            PrepareNewProfileForm();
            break;
        case ID_BTN_SAVE:
            SaveCurrentProfile();
            break;
        case ID_BTN_LAUNCH:
            LaunchSelectedProfile();
            break;
        case ID_BTN_DELETE:
            DeleteSelectedProfile();
            break;
        case ID_BTN_REFRESH:
            RefreshProfileList();
            break;
        }
        return 0;
    }

    case WM_DESTROY:
        if (g_hFontUI) DeleteObject(g_hFontUI);
        if (g_hFontBold) DeleteObject(g_hFontBold);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

static void InitSystemPaths(void) {
    GetEnvironmentVariableW(L"APPDATA", g_appDataDir, MAX_PATH);
    GetEnvironmentVariableW(L"LOCALAPPDATA", g_localAppDataDir, MAX_PATH);
    GetEnvironmentVariableW(L"USERPROFILE", g_userProfileDir, MAX_PATH);
    SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, g_desktopDir);

    swprintf(g_antigravityExe, MAX_PATH, L"%s\\Programs\\Antigravity\\Antigravity.exe", g_localAppDataDir);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    InitCommonControls();
    DetectUiLanguage(lpCmdLine);
    InitSystemPaths();

    WNDCLASSEXW wc = { sizeof(wc) };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = L"AntigravityMAClass";
    wc.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_APP_ICON));
    if (!wc.hIcon) wc.hIcon = ExtractIconW(hInstance, g_antigravityExe, 0);
    if (!wc.hIcon) wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = (HICON)LoadImageW(hInstance, MAKEINTRESOURCEW(IDI_APP_ICON), IMAGE_ICON,
        GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
    if (!wc.hIconSm) wc.hIconSm = wc.hIcon;

    RegisterClassExW(&wc);

    int width = 790;
    int height = 545;
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    g_hWndMain = CreateWindowExW(
        0,
        wc.lpszClassName,
        S->windowTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        (screenW - width) / 2,
        (screenH - height) / 2,
        width,
        height,
        NULL, NULL, hInstance, NULL);

    ShowWindow(g_hWndMain, nCmdShow);
    UpdateWindow(g_hWndMain);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        if (!IsDialogMessageW(g_hWndMain, &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    CoUninitialize();
    return (int)msg.wParam;
}
