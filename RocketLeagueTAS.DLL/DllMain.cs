using System;
using System.Runtime.InteropServices;
using System.Threading;

namespace RocketLeagueTAS.DLL
{
    public class DllMain
    {
        private static TASCore tasCore;
        private static Thread guiThread;

        [DllExport("DllMain", CallingConvention = CallingConvention.StdCall)]
        public static bool DllMain(IntPtr hinstDLL, uint fdwReason, IntPtr lpvReserved)
        {
            switch (fdwReason)
            {
                case 1: // DLL_PROCESS_ATTACH
                    InitializeTAS();
                    break;
                case 0: // DLL_PROCESS_DETACH
                    CleanupTAS();
                    break;
            }
            return true;
        }

        private static void InitializeTAS()
        {
            try
            {
                Console.WriteLine("Initializing Rocket League TAS...");
                
                tasCore = new TASCore();
                tasCore.Initialize();

                // Start GUI in a separate thread
                guiThread = new Thread(StartGUI);
                guiThread.IsBackground = true;
                guiThread.Start();

                Console.WriteLine("Rocket League TAS initialized successfully!");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to initialize TAS: {ex.Message}");
            }
        }

        private static void StartGUI()
        {
            try
            {
                // Create and show the TAS GUI
                var gui = new TASGUI(tasCore);
                gui.ShowDialog();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"GUI error: {ex.Message}");
            }
        }

        private static void CleanupTAS()
        {
            try
            {
                if (tasCore != null)
                {
                    tasCore.StopRecording();
                    tasCore.StopReplay();
                }
                Console.WriteLine("TAS cleanup completed");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Cleanup error: {ex.Message}");
            }
        }

        // Export functions for external access
        [DllExport("StartRecording", CallingConvention = CallingConvention.StdCall)]
        public static void StartRecording()
        {
            tasCore?.StartRecording();
        }

        [DllExport("StopRecording", CallingConvention = CallingConvention.StdCall)]
        public static void StopRecording()
        {
            tasCore?.StopRecording();
        }

        [DllExport("StartReplay", CallingConvention = CallingConvention.StdCall)]
        public static void StartReplay()
        {
            tasCore?.StartReplay();
        }

        [DllExport("StopReplay", CallingConvention = CallingConvention.StdCall)]
        public static void StopReplay()
        {
            tasCore?.StopReplay();
        }

        [DllExport("Pause", CallingConvention = CallingConvention.StdCall)]
        public static void Pause()
        {
            tasCore?.Pause();
        }

        [DllExport("Resume", CallingConvention = CallingConvention.StdCall)]
        public static void Resume()
        {
            tasCore?.Resume();
        }

        [DllExport("SaveRecording", CallingConvention = CallingConvention.StdCall)]
        public static void SaveRecording([MarshalAs(UnmanagedType.LPStr)] string filename)
        {
            tasCore?.SaveRecording(filename);
        }

        [DllExport("LoadRecording", CallingConvention = CallingConvention.StdCall)]
        public static void LoadRecording([MarshalAs(UnmanagedType.LPStr)] string filename)
        {
            tasCore?.LoadRecording(filename);
        }
    }
}