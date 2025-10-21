# 🔧 x64dbg - Filter To Only logical-loader.exe Strings!

## ❌ The Problem:

You're seeing **Windows system DLL strings** (explorer.exe, shell32.dll, etc.)

We need **ONLY logical-loader.exe strings!**

---

## ✅ HOW TO FILTER:

### **Method 1: Search In Specific Module**

1. **In x64dbg**, look at the **top-left corner**
2. You'll see a list of **modules** (DLLs loaded)
3. **Find and click:** `logical-loader.exe` in the module list
4. **Right-click in the CPU window**
5. **Search for → Current module → String references**
   (NOT "All modules"!)

**Now you'll ONLY see strings from logical-loader.exe!** ✅

---

### **Method 2: Use Symbols Window**

1. **Symbols tab** (bottom of x64dbg)
2. **Find `logical-loader.exe` in the list**
3. **Double-click it**
4. **Right-click → Search for → String references (current module)**

---

### **Method 3: Manual Filter**

In the string search results:

1. Look at the **Module** column
2. **Only look at rows** where Module = `logical-loader.exe`
3. **Ignore** everything else (kernel32, ntdll, explorer, etc.)

---

## 🔍 **What To Look For:**

Once you filter to ONLY logical-loader.exe strings, search for:

### **TAS Related:**
- "TAS"
- "Record"
- "Replay"
- "Input"
- "Playback"
- "Frame"

### **Item Related:**
- "Item"
- "Unlock"
- "Spawn"
- "Inventory"
- "Alpha"
- "Zomba"
- "Fennec"
- "Octane"
- "Boost"
- "Wheels"

### **Rocket League Related:**
- "RocketLeague"
- "RL"
- "Car"
- "Ball"
- "Freeplay"

---

## 📸 **What To Send Me:**

After filtering to logical-loader.exe ONLY:

**Screenshot:**
- Strings with "TAS", "Record", "Replay"
- Strings with "Item", "Unlock", "Spawn"
- Any memory addresses you see (like `0x1234567`)

---

## 🎯 **Quick Steps:**

```
1. In x64dbg, find "logical-loader.exe" in modules list
2. Click it
3. Right-click → Search for → Current module → String references
4. Look for TAS/Item strings
5. Screenshot and send!
```

---

## 💡 **TIP:**

If you don't see many strings, try:

1. **Symbols → logical-loader**
2. **Look at the Functions** instead
3. Look for function names like:
   - `RecordInput`
   - `ReplayTAS`
   - `UnlockItem`
   - `SpawnItem`
   - `InjectInput`

---

## ⚡ **DO THIS NOW:**

1. **Make sure you're in logical-loader.exe module** (not Windows DLLs!)
2. **Search strings in CURRENT MODULE ONLY**
3. **Look for TAS/Item related strings**
4. **Screenshot and send!**

**Then we'll see the REAL code!** 🔥
