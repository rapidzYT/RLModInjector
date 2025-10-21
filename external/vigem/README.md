# ViGEm Client Library

This folder should contain the ViGEmClient SDK.

## Download:

**For Users (Driver):**
- https://github.com/nefarius/ViGEmBus/releases/latest
- Install ViGEmBus driver (one-time setup)

**For Development (SDK):**
- https://github.com/nefarius/ViGEmClient/releases/latest
- Download the SDK and extract here

## Expected Structure:

```
vigem/
  ├── include/
  │   └── ViGEm/
  │       ├── Client.h
  │       └── Common.h
  └── lib/
      └── ViGEmClient.lib (or .a for MinGW)
```

## Alternative: Header-Only Implementation

We'll use a simplified header-only approach that directly interfaces with ViGEmBus driver.
