# 🔑 KeyLogger (Windows ‑ Educational)

> **Disclaimer ▸** This project is **for educational and research purposes only**.  
> Running key‑logging software on a computer that you do not own **or** without explicit permission is **illegal** in most jurisdictions.  
> Use responsibly.

---

## Overview

A minimal, WinAPI‑based keylogger written in C that records every key‑press system‑wide and appends the virtual‑key codes to **`keylog.txt`**.  
A small Python helper script (**`read_keylog.py`**) is included to translate those virtual‑key (VK) codes back into human‑readable symbols.

<table>
<tr><td>🎯 **Goal**</td><td>Demonstrate the mechanics of <code>WH_KEYBOARD_LL</code> hooks in Windows.</td></tr>
<tr><td>🛠 **Language / API**</td><td>C 17 + WinAPI (<code>windows.h</code>)</td></tr>
<tr><td>📂 **Log file**</td><td><code>keylog.txt</code> (<em>created in append mode so previous data is preserved</em>)</td></tr>
</table>

---

## Repository layout

| File                    | Role                                                                |
| ----------------------- | ------------------------------------------------------------------- |
| `keyLogger.c`           | Core key‑logger source (WinAPI hook, message loop, thread handling) |
| `read_keylog.py`        | Small helper to map VK codes → characters (run it after logging)    |
| `cheatsheet_winapi.txt` | Quick reference of common WinAPI typedefs (32/64‑bit)               |
| `.gitignore`            | Ignore compiled binary + log file                                   |
| `keylog.txt`            | *Created at runtime* – where keystrokes are stored                  |

---

## Prerequisites

| Platform           | Compiler        | Notes                                     |
| ------------------ | --------------- | ----------------------------------------- |
| **Windows 7 → 11** | GCC **or** MSVC | 64‑bit recommended, but 32‑bit works too. |

### I don’t have `gcc` on Windows 🤔

1. Install **MinGW‑w64** (GCC for Windows) via the official installer:  
   <https://sourceforge.net/projects/mingw/>
2. During installation, select a **x86_64** toolchain if your OS is 64‑bit.
3. Add `C:\mingw\bin` (or the chosen install path) to your system **`PATH`**.

---

## Building

```powershell
# Build a GUI executable (no console window)
gcc keyLogger.c -o keylogger.exe -mwindows

# …or keep the console for debugging
gcc keyLogger.c -o keylogger.exe


---

## Usage

```
1. Run keylogger.exe           → a message‑box confirms it’s running.
2. Do some typing…             → data streams into keylog.txt (same folder).
3. Click “OK” in the message‑box → the logger stops and closes cleanly.
4. Decode the log (optional):     python read_keylog.py
```

read_keylog.py prints each key name and reconstructs the typed message where possible (letters, numbers, basic symbols).


---

## Sample output

```bash
VK: 0x41 (65)
VK: 0x42 (66)
VK: 0x43 (67)
...
```

Running python read_keylog.py :

```bash
`A` (65)
`B` (66)
`C` (67)
Message : `A``B``C`
```

## Author

**Corentin Mahieu** – [@Fir3n0x](https://github.com/Fir3n0x)


Happy (ethical) hacking! 🛡️