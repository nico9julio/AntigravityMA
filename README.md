# AntigravityMA (Antigravity Multi-Account Manager)

<p align="center">
  <img src="AntigravityMA.ico" width="96" height="96" alt="AntigravityMA Icon" />
</p>

**[English](#english) | [Español](#español)**

---

<a name="english"></a>
## 🇬🇧 English

**AntigravityMA** is an ultra-lightweight, native **C (Win32 API)** desktop utility for managing multiple authenticated **Google Antigravity** (Desktop App / Antigravity 2.0) profiles and accounts on Windows without having to sign out or re-authenticate in the browser.

### ✨ Key Features

* **Ultra-lightweight & Zero Dependencies (~180 KB):** Statically compiled (`/MT`) using only native Windows APIs (`user32`, `comctl32`, `shell32`, `ole32`, `shlwapi`). Runs out-of-the-box on any Windows PC without requiring `.NET`, Node.js, or Visual C++ Redistributables.
* **Automatic Language Detection (ES / EN):** Automatically detects the Windows display language (`GetUserDefaultUILanguage()`). Displays in **Spanish** when Windows is set to Spanish (Spain `es-ES` or Mexico `es-MX`), and defaults to **English** on any other system language (can also be forced via `--lang=en` or `--lang=es`).
* **Auto-Discovery of Existing Sessions:**
  * Scans `%APPDATA%\Antigravity` (main session) and all `%APPDATA%\Antigravity-*` profile directories.
  * Reads `app_storage.json` to extract the signed-in email (`jetski.onboarding.lastLoginUsername`), custom session display name, and startup settings.
  * Inspects existing Desktop shortcuts (`Antigravity - *.lnk`) via COM (`IShellLinkW`).
* **True OAuth Credential Isolation:**
  * By default on Windows, Antigravity's internal engine (`language_server.exe`) stores the active OAuth token in a single Windows Credential Manager entry (`gemini:antigravity`), causing new logins to overwrite the previous account.
  * **AntigravityMA** isolates secondary accounts by enabling per-process file token storage (`SSH_CONNECTION=1`) and linking each profile's private token (`oauth-token.bin`) via *NTFS Hardlinks* (`CreateHardLinkW`).
* **Simultaneous Execution:** Run multiple Antigravity windows side-by-side with different Google accounts while sharing your `.gemini` projects, skills, plugins, and conversation history.
* **Silent Desktop Launchers:** Automatically generates `.lnk` Desktop shortcuts and windowless `.vbs` launchers (zero `cmd.exe` console flash).

### 🚀 How to Use

1. Run **`AntigravityMA.exe`**.
2. All existing sessions on your PC will appear automatically in the top table.
3. **To create a new session/account:**
   * Click **`+ New Session`**.
   * Enter a **Session Name** (e.g., `Work` or `Secondary`) and optionally the associated email.
   * Keep **"Isolate token outside Windows Credential Manager (SSH_CONNECTION=1)"** checked.
   * Click **`Save Configuration`**.
4. **To launch a session:**
   * Select it in the list and click **`▶ Launch Selected Session`** (or double-click the row), or use the **`Antigravity - <Name>.lnk`** shortcut created on your Desktop.
   * Sign in with your Google account once; your session will remain permanently saved in that profile.

---

<a name="español"></a>
## 🇪🇸 Español

**AntigravityMA** es una herramienta nativa y ultraligera escrita en **C puro (Win32 API)** para gestionar múltiples perfiles y cuentas autenticadas de **Google Antigravity** (versión de escritorio / Antigravity 2.0) en Windows sin tener que cerrar sesión ni volver a autenticarte por navegador.

### ✨ Características principales

* **Ultraligero y sin dependencias (~180 KB):** Compilado estáticamente (`/MT`) usando únicamente las APIs nativas de Windows (`user32`, `comctl32`, `shell32`, `ole32`, `shlwapi`). Funciona en cualquier PC con Windows sin requerir `.NET`, Node.js ni redistribuibles de Visual C++.
* **Detección automática de idioma (ES / EN):** Detecta automáticamente el idioma de Windows (`GetUserDefaultUILanguage()`). Si el sistema está en **Español (España `es-ES` o México `es-MX`)** se muestra en español; en cualquier otro idioma se muestra automáticamente en **inglés** (también puede forzarse con `--lang=es` o `--lang=en`).
* **Autodetección de sesiones existentes:**
  * Escanea automáticamente `%APPDATA%\Antigravity` (sesión principal) y todas las carpetas `%APPDATA%\Antigravity-*`.
  * Lee `app_storage.json` para detectar el correo autenticado (`jetski.onboarding.lastLoginUsername`), el nombre personalizado de la sesión y las preferencias de inicio.
  * Inspecciona los accesos directos existentes en el Escritorio (`Antigravity - *.lnk`) mediante COM (`IShellLinkW`).
* **Aislamiento real de credenciales OAuth:**
  * Por defecto en Windows, el motor interno de Antigravity (`language_server.exe`) guarda el token OAuth en una única entrada del Administrador de Credenciales de Windows (`gemini:antigravity`), provocando que al cambiar de cuenta se sobrescriba la anterior.
  * **AntigravityMA** aísla las cuentas secundarias activando el almacenamiento de credenciales en archivo independiente (`SSH_CONNECTION=1`) y sincronizando el token privado de cada perfil (`oauth-token.bin`) mediante *Hardlinks NTFS* (`CreateHardLinkW`).
* **Ejecución simultánea:** Permite tener abiertas varias ventanas de Antigravity al mismo tiempo con distintas cuentas de Google, compartiendo tus proyectos, skills, plugins e historial de `.gemini`.
* **Creación automática de accesos directos y lanzadores silenciosos:** Genera accesos directos `.lnk` en el Escritorio y scripts `.vbs` invisibles (sin parpadeo de consola `cmd.exe`).

---

## 🛠️ Build from Source / Compilación

Requirements / Requisitos: **Visual Studio Build Tools** (`cl.exe` & `rc.exe`).

```bat
build.bat
```

Or manually from the *Developer Command Prompt for VS*:

```bat
rc.exe /nologo resource.rc
cl.exe /nologo /O2 /MT /W3 /utf-8 main.c resource.res /Fe:AntigravityMA.exe /link /SUBSYSTEM:WINDOWS /MANIFEST:EMBED
```

---

## 📄 License / Licencia

MIT License.
