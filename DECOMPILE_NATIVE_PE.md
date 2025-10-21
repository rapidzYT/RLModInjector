# 🔓 Decompile Native PE (C++) Executable

## ✅ So It's Native C++!

**PE = Portable Executable** (compiled C/C++)

We need **different tools** for this!

---

## 📥 **Best Tools for Native PE:**

### **Option 1: Ghidra** (RECOMMENDED - FREE!)

**Download:** https://github.com/NationalSecurityAgency/ghidra/releases/latest

**Why Ghidra:**
- ✅ FREE (from NSA!)
- ✅ Best decompiler
- ✅ Easy to use
- ✅ Shows C-like code

**Steps:**
1. Download **ghidra_11.2.1_PUBLIC_20241105.zip** (latest)
2. Extract it
3. Need **Java JDK** installed first!
   - Download Java: https://adoptium.net/temurin/releases/
   - Get JDK 21 (Latest LTS)
4. Run **ghidraRun.bat**
5. **File → New Project**
6. **File → Import File** → Select `logical-loader.exe`
7. **Analysis → Auto Analyze** (wait a few minutes)
8. **Browse the decompiled code!**

---

### **Option 2: x64dbg** (EASIER SETUP!)

**Download:** https://x64dbg.com/

**Why x64dbg:**
- ✅ No Java needed!
- ✅ Simpler to use
- ✅ Good for finding strings/functions
- ⚠️ Shows assembly (harder to read than C)

**Steps:**
1. Download **snapshot** version
2. Extract and run **x96dbg.exe** (for 64-bit) or **x32dbg.exe** (for 32-bit)
3. **File → Open** → Select `logical-loader.exe`
4. **Right-click → Search for → All modules → String references**
5. Look for strings like:
   - "TAS"
   - "Item"
   - "Unlock"
   - "Input"
   - "Record"
   - "Replay"

---

### **Option 3: IDA Free** (PROFESSIONAL)

**Download:** https://hex-rays.com/ida-free/

**Why IDA:**
- ✅ Industry standard
- ✅ Best analysis
- ⚠️ Registration required

---

## 🔍 **What To Look For:**

### **In Ghidra/IDA (Decompiled Code):**

Look for functions containing:
- `WriteProcessMemory` - They're writing to RL's memory!
- `ReadProcessMemory` - They're reading RL's memory!
- `CreateRemoteThread` - DLL injection
- Memory addresses like `0x1A2B3C4D`
- Strings with "TAS", "Item", "Unlock", "Input"

### **In x64dbg (Strings):**

Search for strings:
- "TAS"
- "Record"
- "Replay"
- "Item"
- "Unlock"
- "Alpha Boost"
- "White Zomba"
- "Fennec"

**Then find what code USES those strings!**

---

## 🎯 **Easiest Approach: x64dbg**

**DO THIS NOW:**

1. **Download x64dbg**: https://github.com/x64dbg/x64dbg/releases/latest
2. **Download**: `snapshot_2024-XX-XX_XX-XX.zip`
3. **Extract** it
4. **Run** `release\x64\x64dbg.exe` (or x32 if it's 32-bit)
5. **File → Open** → `logical-loader.exe`
6. **Right-click in CPU window → Search for → All modules → String references**
7. **Look for strings** with "TAS", "Item", etc.
8. **Double-click a string** to see what code uses it!

---

## 📸 **What To Send Me:**

Once you open it in x64dbg:

1. **Screenshot of string references** (the list)
2. **Look for:**
   - Memory addresses (like `RocketLeague.exe+0x1234567`)
   - Function names
   - TAS-related strings
   - Item-related strings

**Then I can help you understand the code!**

---

## 💡 **What We Can Learn:**

From a native PE we can find:

✅ **Memory addresses** they use (GOLD!)
✅ **What functions** they call
✅ **How they hook** into RL
✅ **Item IDs** and offsets
✅ **Input injection** method

---

## ⚡ **QUICK START (x64dbg):**

```
1. Download x64dbg (no Java needed!)
2. Extract
3. Run x64dbg.exe
4. Open logical-loader.exe
5. Search for strings
6. Screenshot results
7. Send to me!
```

**This is faster than Ghidra!** ⚡

---

## 🆘 **Need Help?**

Tell me:
- Did you download x64dbg?
- Can you open the exe?
- Do you see the CPU window?
- Can you find string search?

**I'll walk you through it!** 💪

---

## 🔥 **LET'S DO THIS:**

**Download x64dbg NOW:** https://github.com/x64dbg/x64dbg/releases/latest

**Then:**
1. Open logical-loader.exe in it
2. Search for strings
3. Screenshot what you find!

**This will show us THE REAL WORKING CODE!** 🎯
