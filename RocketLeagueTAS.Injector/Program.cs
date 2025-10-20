using System;
using System.IO;

namespace RocketLeagueTAS.Injector
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Rocket League TAS Injector");
            Console.WriteLine("=========================");
            Console.WriteLine();

            DLLInjector injector = new DLLInjector();

            try
            {
                // Check if Rocket League is running
                if (!injector.IsProcessRunning("RocketLeague"))
                {
                    Console.WriteLine("Rocket League is not running!");
                    Console.WriteLine("Please start Rocket League first, then run this injector.");
                    Console.WriteLine();
                    Console.WriteLine("Press any key to exit...");
                    Console.ReadKey();
                    return;
                }

                // Get the path to the TAS DLL
                string dllPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "RocketLeagueTAS.DLL.dll");
                
                if (!File.Exists(dllPath))
                {
                    Console.WriteLine($"TAS DLL not found at: {dllPath}");
                    Console.WriteLine("Please make sure the DLL is in the same directory as this injector.");
                    Console.WriteLine();
                    Console.WriteLine("Press any key to exit...");
                    Console.ReadKey();
                    return;
                }

                Console.WriteLine($"Injecting TAS DLL: {dllPath}");
                Console.WriteLine();

                // Inject the DLL
                bool success = injector.InjectDLL("RocketLeague", dllPath);

                if (success)
                {
                    Console.WriteLine();
                    Console.WriteLine("TAS injection successful!");
                    Console.WriteLine("The TAS GUI should now be visible in Rocket League.");
                    Console.WriteLine();
                    Console.WriteLine("Press any key to exit...");
                }
                else
                {
                    Console.WriteLine();
                    Console.WriteLine("TAS injection failed!");
                    Console.WriteLine("Please check the error messages above.");
                    Console.WriteLine();
                    Console.WriteLine("Press any key to exit...");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
                Console.WriteLine();
                Console.WriteLine("Press any key to exit...");
            }

            Console.ReadKey();
        }
    }
}