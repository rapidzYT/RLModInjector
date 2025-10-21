# 🔍 Finding The Module List in x64dbg

## 📋 Where To Look:

### **Option 1: Symbols Tab**

1. Look at the **BOTTOM of x64dbg**
2. Find tabs: **Log | Notes | Breakpoints | Memory Map | Call Stack | SEH | Handles | Threads | Graph | Symbols**
3. **Click "Symbols" tab**
4. You'll see a list like:
   - logical-loader.exe
   - ntdll.dll
   - kernel32.dll
   - etc.
5. **Double-click "logical-loader.exe"**

---

### **Option 2: Memory Map Tab**

1. **Bottom tabs → "Memory Map"**
2. Find `logical-loader.exe` in the list
3. Note the address range

---

### **Option 3: Manual Address Filter**

In your string search results:

1. Look at the **Address column**
2. Logical-loader.exe addresses will usually start with something like:
   - `00000000004xxxxx` (for 32-bit)
   - `00007FF6xxxxxxxx` (for 64-bit, but different from Windows DLLs)
3. Windows DLL addresses are usually:
   - `00007FFCDxxxxxxx` (like your results above)

**Your results all start with `00007FFCD` = Windows DLLs!** ❌

---

## 🎯 **EASIER METHOD - Just Search Differently:**

### **In x64dbg Main Menu:**

1. **Right-click ANYWHERE in the main CPU window**
2. **Search for → String references**
3. A dialog appears
4. **In the dialog:**
   - There should be a dropdown for **"Module"**
   - Select **"logical-loader.exe"** from dropdown
   - OR type the exe name

---

## 💡 **Alternative: Use Command Bar**

At the bottom of x64dbg, there's a **command bar**:

Type this command:
```
strref logical-loader.exe
```

This will show ONLY strings from logical-loader.exe!

---

## 🔧 **If Nothing Works - Try This:**

### **Method 1: Restart x64dbg**

1. **File → Open**
2. Select `logical-loader.exe` again
3. When it stops at entry point
4. **Press F9** to run it (it might need to be running)
5. **Then** search for strings

### **Method 2: Look for Function Names**

Instead of strings, try:

1. **Right-click → Search for → Current Module → Intermodular calls**
2. Look for calls to:
   - `WriteProcessMemory`
   - `ReadProcessMemory`
   - `CreateRemoteThread`
   - `keybd_event`
   - `SendInput`

---

## 📸 **Send Me This:**

Take a screenshot of:

1. **The whole x64dbg window** (so I can see what you see)
2. **The bottom tabs** (so I can guide you)
3. **Any menus you see**

**Then I can tell you EXACTLY where to click!**

---

## ⚡ **QUICK TRY:**

**In the command bar at bottom, type:**
```
strref
```

**Then in the References window, look for a filter/module option!**

---

**OR just screenshot your x64dbg window and I'll guide you!** 📸