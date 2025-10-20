# Quick Start Guide - Rocket League TAS Mod

## New Users - Start Here!

### What You Need
1. Windows 10/11
2. Rocket League
3. Administrator access

### Setup (5 minutes)

#### If Building from Source:
1. **Install Visual Studio**
   - Download: https://visualstudio.microsoft.com/
   - Install "Desktop development with C++"

2. **Download Dependencies**
   ```bash
   setup_dependencies.bat
   ```
   - Follow the prompts to download ImGui and MinHook

3. **Build**
   ```bash
   build_all.bat
   ```

4. **Copy Files**
   - Go to `build/bin/Release/`
   - Copy `RLTASMod.dll` and `RLTASInjector.exe` to a new folder

#### If Using Pre-built Release:
1. Download the release ZIP
2. Extract to a folder
3. You're ready!

### Using the Mod (First Time)

1. **Start Rocket League**
   - Launch the game
   - Go to freeplay

2. **Inject the Mod**
   - Right-click `RLTASInjector.exe`
   - Click "Run as administrator"
   - Wait for "SUCCESS!" message

3. **Open GUI**
   - In Rocket League, press **F9**
   - The TAS GUI should appear!

### Making Your First TAS

**Example: Recording a Simple Aerial**

1. **In freeplay, position yourself**
   - Drive to a spot you like
   - Hit the ball so it's airborne

2. **Press F9** to open the GUI

3. **Create new TAS**
   - Controls tab → Type "my_first_aerial"
   - Click "New TAS"

4. **Record**
   - Click "Start" (will start recording immediately)
   - Jump, boost, air roll - do your aerial!
   - Click "Stop"

5. **Save it**
   - Click "Update"
   - Loaded TAS tab → Click "Save TAS"

6. **Replay it**
   - Controls tab → Click "Start"
   - Watch your perfect replay!

### Making it Better (Iterative TAS)

Now let's improve that aerial:

1. **Set break inputs**
   - Settings tab → Check "Jump"
   - This means pressing Jump during replay will let you take over

2. **Replay and improve**
   - Controls tab → Click "Start"
   - Watch the replay
   - When you want to change something, press Jump
   - Recording starts immediately!
   - Do your improved inputs
   - Click "Stop"

3. **Save the improvement**
   - Click "Update"
   - This adds your new inputs to the TAS

4. **Repeat**
   - Keep replaying and improving
   - Each time you Update, it saves to the same TAS

5. **Final save**
   - Loaded TAS tab → Click "Save TAS"
   - Your improved TAS is saved!

### Common Use Cases

#### Practicing a Specific Shot
```
1. Set up the shot (ball + car position)
2. New TAS → Record → Stop → Update
3. Replay and watch
4. Break input to correct mistakes
5. Update to save corrections
6. Repeat until perfect
```

#### Freestyling
```
1. Set record speed to 0.5x (slow motion)
2. Record your freestyle in slow-mo
3. Set replay speed to 1.0x
4. Watch it at full speed!
```

#### Learning a Mechanic
```
1. Record yourself doing it right
2. Save as "perfect_flick"
3. Later, load and study frame-by-frame
4. Use slow replay speed (0.1x)
```

### Tips for Beginners

1. **Start Simple**
   - Don't try complex shots first
   - Try just driving in a circle
   - Get comfortable with the workflow

2. **Use Slow Motion**
   - Record at 0.5x speed for precise inputs
   - Replay at 1.0x to see normal speed

3. **Name Your TAS Files**
   - Use descriptive names
   - "ceiling_shot_1", "flip_reset_practice", etc.

4. **Save Often**
   - Click "Save TAS" frequently
   - Don't lose your work!

5. **Experiment with Break Inputs**
   - Try different combinations
   - Find what works for your workflow

### Controls Reference

**In-Game:**
- F9 = Toggle TAS GUI

**GUI Navigation:**
- Mouse to click buttons
- Type in text fields
- Sliders for speed control

**Recording/Replaying:**
- All normal RL controls work
- Break inputs (if enabled) stop replay
- GUI buttons control TAS state

### Troubleshooting Quick Fixes

| Problem | Quick Fix |
|---------|-----------|
| GUI won't open | Press F9 multiple times |
| Injection failed | Run as Administrator |
| Can't find RL | Make sure game is running |
| Antivirus blocking | Add exception for the folder |
| Build failed | Run setup_dependencies.bat first |

### Next Steps

Once comfortable with basics:
- Read INSTALLATION_GUIDE.md for details
- Read RL_TAS_MOD_README.md for advanced features
- Experiment with speed controls
- Try complex multi-part TAS sequences
- Share your TAS files!

### Example Workflow Diagram

```
Start RL → Inject → F9 to open GUI
           ↓
    Create New TAS (captures position)
           ↓
    Click Start → Records automatically
           ↓
    Click Stop → Recording saved
           ↓
    Click Update → Adds to TAS
           ↓
    Click Start → Replays your inputs
           ↓
    Press break input → Starts recording again
           ↓
    Click Stop → New segment recorded
           ↓
    Click Update → Appends to TAS
           ↓
    Repeat until satisfied
           ↓
    Save TAS → Saved to file!
```

### Getting Help

**Before asking:**
1. Read this guide
2. Check INSTALLATION_GUIDE.md
3. Check main README.md

**When asking for help, include:**
- What you were trying to do
- What happened instead
- Any error messages
- Your OS and RL version

### Safety Reminder

⚠️ **IMPORTANT:**
- Use ONLY in offline/freeplay mode
- DO NOT use in online/competitive
- Mod may violate ToS
- Use at your own risk

### Have Fun!

The TAS mod is a powerful tool for:
- Learning mechanics
- Practicing shots
- Creating content
- Analyzing gameplay
- Having fun with Rocket League!

Start simple, experiment, and enjoy!

---

**Ready to build something amazing? Let's go!** 🚀⚽
