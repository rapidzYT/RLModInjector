using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace RocketLeagueTAS.DLL
{
    public class TASCore
    {
        private InputRecorder recorder;
        private InputReplayer replayer;
        private MemoryManager memoryManager;
        private GameState gameState;
        private bool isRecording = false;
        private bool isReplaying = false;
        private bool isPaused = false;
        private Thread tasThread;

        // Windows API functions for input simulation
        [DllImport("user32.dll")]
        private static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);

        [DllImport("user32.dll")]
        private static extern short GetAsyncKeyState(int vKey);

        [DllImport("user32.dll")]
        private static extern bool SetCursorPos(int x, int y);

        [DllImport("user32.dll")]
        private static extern bool GetCursorPos(out POINT lpPoint);

        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public int X;
            public int Y;
        }

        // Virtual key codes for Rocket League controls
        public const int VK_W = 0x57; // Throttle
        public const int VK_S = 0x53; // Brake/Reverse
        public const int VK_A = 0x41; // Steer Left
        public const int VK_D = 0x44; // Steer Right
        public const int VK_SPACE = 0x20; // Jump
        public const int VK_SHIFT = 0x10; // Boost
        public const int VK_CONTROL = 0x11; // Powerslide
        public const int VK_UP = 0x26; // Pitch Up
        public const int VK_DOWN = 0x28; // Pitch Down
        public const int VK_LEFT = 0x25; // Yaw Left
        public const int VK_RIGHT = 0x27; // Yaw Right

        public TASCore()
        {
            recorder = new InputRecorder();
            replayer = new InputReplayer();
            memoryManager = new MemoryManager();
            gameState = new GameState();
        }

        public void Initialize()
        {
            try
            {
                // Find Rocket League process
                Process[] processes = Process.GetProcessesByName("RocketLeague");
                if (processes.Length == 0)
                {
                    throw new Exception("Rocket League process not found!");
                }

                memoryManager.Initialize(processes[0]);
                gameState.Initialize(memoryManager);

                // Start the TAS thread
                tasThread = new Thread(TASLoop);
                tasThread.IsBackground = true;
                tasThread.Start();

                Console.WriteLine("TAS Core initialized successfully!");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to initialize TAS Core: {ex.Message}");
                throw;
            }
        }

        private void TASLoop()
        {
            while (true)
            {
                try
                {
                    if (isRecording && !isPaused)
                    {
                        RecordInputs();
                    }
                    else if (isReplaying && !isPaused)
                    {
                        ReplayInputs();
                    }

                    // Update game state
                    gameState.Update();

                    Thread.Sleep(1); // 1000 FPS for precise input recording
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"TAS Loop error: {ex.Message}");
                }
            }
        }

        private void RecordInputs()
        {
            var inputState = new InputState
            {
                Timestamp = DateTime.Now.Ticks,
                Throttle = IsKeyPressed(VK_W),
                Brake = IsKeyPressed(VK_S),
                SteerLeft = IsKeyPressed(VK_A),
                SteerRight = IsKeyPressed(VK_D),
                Jump = IsKeyPressed(VK_SPACE),
                Boost = IsKeyPressed(VK_SHIFT),
                Powerslide = IsKeyPressed(VK_CONTROL),
                PitchUp = IsKeyPressed(VK_UP),
                PitchDown = IsKeyPressed(VK_DOWN),
                YawLeft = IsKeyPressed(VK_LEFT),
                YawRight = IsKeyPressed(VK_RIGHT),
                MouseX = GetMouseX(),
                MouseY = GetMouseY()
            };

            recorder.RecordInput(inputState);
        }

        private void ReplayInputs()
        {
            var inputState = replayer.GetNextInput();
            if (inputState != null)
            {
                SimulateInput(inputState);
            }
        }

        private void SimulateInput(InputState inputState)
        {
            // Simulate keyboard inputs
            SimulateKey(inputState.Throttle, VK_W);
            SimulateKey(inputState.Brake, VK_S);
            SimulateKey(inputState.SteerLeft, VK_A);
            SimulateKey(inputState.SteerRight, VK_D);
            SimulateKey(inputState.Jump, VK_SPACE);
            SimulateKey(inputState.Boost, VK_SHIFT);
            SimulateKey(inputState.Powerslide, VK_CONTROL);
            SimulateKey(inputState.PitchUp, VK_UP);
            SimulateKey(inputState.PitchDown, VK_DOWN);
            SimulateKey(inputState.YawLeft, VK_LEFT);
            SimulateKey(inputState.YawRight, VK_RIGHT);

            // Simulate mouse movement
            SetCursorPos(inputState.MouseX, inputState.MouseY);
        }

        private void SimulateKey(bool isPressed, int vk)
        {
            if (isPressed)
            {
                keybd_event((byte)vk, 0, 0, UIntPtr.Zero);
            }
            else
            {
                keybd_event((byte)vk, 0, 2, UIntPtr.Zero); // KEYEVENTF_KEYUP
            }
        }

        private bool IsKeyPressed(int vk)
        {
            return (GetAsyncKeyState(vk) & 0x8000) != 0;
        }

        private int GetMouseX()
        {
            GetCursorPos(out POINT point);
            return point.X;
        }

        private int GetMouseY()
        {
            GetCursorPos(out POINT point);
            return point.Y;
        }

        // Public methods for GUI control
        public void StartRecording()
        {
            isRecording = true;
            isReplaying = false;
            recorder.StartRecording();
            Console.WriteLine("Started recording inputs");
        }

        public void StopRecording()
        {
            isRecording = false;
            recorder.StopRecording();
            Console.WriteLine("Stopped recording inputs");
        }

        public void StartReplay()
        {
            isReplaying = true;
            isRecording = false;
            replayer.StartReplay();
            
            // Teleport to first position
            TeleportToFirstPosition();
            Console.WriteLine("Started replaying inputs");
        }

        public void StopReplay()
        {
            isReplaying = false;
            replayer.StopReplay();
            Console.WriteLine("Stopped replaying inputs");
        }

        public void Pause()
        {
            isPaused = true;
            Console.WriteLine("Paused TAS");
        }

        public void Resume()
        {
            isPaused = false;
            Console.WriteLine("Resumed TAS");
        }

        public void TeleportToFirstPosition()
        {
            try
            {
                var firstState = replayer.GetFirstState();
                if (firstState != null)
                {
                    memoryManager.SetCarPosition(firstState.CarPosition);
                    memoryManager.SetCarRotation(firstState.CarRotation);
                    memoryManager.SetCarVelocity(firstState.CarVelocity);
                    memoryManager.SetCarAngularVelocity(firstState.CarAngularVelocity);
                    
                    memoryManager.SetBallPosition(firstState.BallPosition);
                    memoryManager.SetBallVelocity(firstState.BallVelocity);
                    memoryManager.SetBallAngularVelocity(firstState.BallAngularVelocity);
                    
                    Console.WriteLine("Teleported to first position");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to teleport to first position: {ex.Message}");
            }
        }

        public void SaveRecording(string filename)
        {
            recorder.SaveToFile(filename);
            Console.WriteLine($"Saved recording to {filename}");
        }

        public void LoadRecording(string filename)
        {
            replayer.LoadFromFile(filename);
            Console.WriteLine($"Loaded recording from {filename}");
        }

        public bool IsRecording => isRecording;
        public bool IsReplaying => isReplaying;
        public bool IsPaused => isPaused;
    }
}