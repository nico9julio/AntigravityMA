# AntigravityMA (Antigravity Multi-Account Manager)

<p align="center">
  <img src="AntigravityMA.ico" width="96" height="96" alt="AntigravityMA Icon" />
</p>

**AntigravityMA** es una herramienta nativa y ultraligera escrita en **C puro (Win32 API)** para gestionar múltiples perfiles y cuentas autenticadas de **Google Antigravity** (versión de escritorio / Antigravity 2.0) en Windows sin tener que cerrar sesión ni volver a autenticarte por navegador.

---

## ✨ Características principales

* **Ultraligero y sin dependencias (~175 KB):** Compilado estáticamente (`/MT`) usando únicamente las APIs nativas de Windows (`user32`, `comctl32`, `shell32`, `ole32`, `shlwapi`). Funciona en cualquier PC con Windows sin requerir `.NET`, Node.js ni redistribuibles de Visual C++.
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

## 🚀 Cómo usar AntigravityMA

1. Ejecuta **`AntigravityMA.exe`**.
2. La tabla superior mostrará automáticamente todas las sesiones detectadas en tu equipo.
3. **Para crear una nueva sesión/cuenta:**
   * Haz clic en **`+ Nueva Sesión`**.
   * Escribe el **Nombre de la Sesión** (por ejemplo, `Trabajo` o `Secundaria`) y opcionalmente el correo asociado.
   * Asegúrate de mantener marcada la opción **"Aislar token fuera del Administrador de Credenciales de Windows (SSH_CONNECTION=1)"**.
   * Haz clic en **`Guardar Configuración`**.
4. **Para iniciar una sesión:**
   * Selecciónala en la tabla y pulsa **`▶ Iniciar Sesión Seleccionada`** (o haz doble clic sobre ella), o bien utiliza el acceso directo **`Antigravity - <Nombre>.lnk`** creado en tu Escritorio.
   * Inicia sesión con tu cuenta de Google una única vez; la sesión quedará guardada permanentemente en ese perfil.

---

## 🛠️ Compilación desde el código fuente

Requisitos: **Visual Studio Build Tools** (compilador MSVC `cl.exe` y compilador de recursos `rc.exe`).

Ejecuta el script incluido:

```bat
build.bat
```

O manualmente desde la *Developer Command Prompt for VS*:

```bat
rc.exe /nologo resource.rc
cl.exe /nologo /O2 /MT /W3 /utf-8 main.c resource.res /Fe:AntigravityMA.exe /link /SUBSYSTEM:WINDOWS
```

---

## 📁 Estructura del proyecto

* `main.c` — Código fuente completo de la aplicación y su interfaz gráfica Win32.
* `resource.h` / `resource.rc` — Definición de recursos de Windows (ícono integrado y metadatos de versión).
* `AntigravityMA.ico` — Ícono oficial de la aplicación.
* `build.bat` — Script de compilación estática para MSVC.
* `AntigravityMA.exe` — Binario portable precompilado para Windows x64.

---

## 📄 Licencia

MIT License. Libre para usar, modificar y distribuir.
