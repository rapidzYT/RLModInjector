using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using RocketLeagueTAS.DLL;

namespace RocketLeagueTAS.App
{
    public partial class MainForm : Form
    {
        private TASCore tasCore;
        private bool isInjected = false;
        private Process rlProcess;
        
        // DLL Injection
        [DllImport("kernel32.dll")]
        static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);
        
        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern IntPtr GetModuleHandle(string lpModuleName);
        
        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);
        
        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);
        
        [DllImport("kernel32.dll")]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);
        
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool CloseHandle(IntPtr hObject);
        
        const int PROCESS_CREATE_THREAD = 0x0002;
        const int PROCESS_QUERY_INFORMATION = 0x0400;
        const int PROCESS_VM_OPERATION = 0x0008;
        const int PROCESS_VM_WRITE = 0x0020;
        const int PROCESS_VM_READ = 0x0010;
        const uint MEM_COMMIT = 0x00001000;
        const uint MEM_RESERVE = 0x00002000;
        const uint PAGE_READWRITE = 4;

        public MainForm()
        {
            InitializeComponent();
            UpdateUI();
        }

        private void UpdateUI()
        {
            // Update injection status
            if (isInjected)
            {
                lblStatus.Text = "✅ Connected to Rocket League";
                lblStatus.ForeColor = Color.Green;
                btnInject.Enabled = false;
                grpTASControls.Enabled = true;
            }
            else
            {
                lblStatus.Text = "⚠️ Not Connected - Click 'Connect to Rocket League'";
                lblStatus.ForeColor = Color.Orange;
                btnInject.Enabled = true;
                grpTASControls.Enabled = false;
            }
            
            // Update TAS status
            if (tasCore != null)
            {
                lblRecordingStatus.Text = tasCore.IsRecording ? "🔴 Recording..." : "⚫ Not Recording";
                lblRecordingStatus.ForeColor = tasCore.IsRecording ? Color.Red : Color.Gray;
                
                lblReplayStatus.Text = tasCore.IsReplaying ? "▶️ Replaying..." : "⏹️ Not Replaying";
                lblReplayStatus.ForeColor = tasCore.IsReplaying ? Color.Blue : Color.Gray;
                
                btnStartRecording.Enabled = !tasCore.IsRecording && !tasCore.IsReplaying;
                btnStopRecording.Enabled = tasCore.IsRecording;
                btnStartReplay.Enabled = !tasCore.IsRecording && !tasCore.IsReplaying;
                btnStopReplay.Enabled = tasCore.IsReplaying;
            }
        }

        private void btnInject_Click(object sender, EventArgs e)
        {
            try
            {
                // Find Rocket League process
                Process[] processes = Process.GetProcessesByName("RocketLeague");
                if (processes.Length == 0)
                {
                    MessageBox.Show("Rocket League not found!\n\nPlease:\n1. Start Rocket League\n2. Load into freeplay\n3. Click 'Connect' again", 
                        "Rocket League Not Running", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                
                rlProcess = processes[0];
                
                // Get DLL path
                string dllPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "RocketLeagueTAS.DLL.dll");
                if (!File.Exists(dllPath))
                {
                    MessageBox.Show($"DLL not found at:\n{dllPath}\n\nMake sure RocketLeagueTAS.DLL.dll is in the same folder as this application.", 
                        "DLL Not Found", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                
                // Inject DLL
                lblStatus.Text = "Injecting...";
                lblStatus.ForeColor = Color.Blue;
                Application.DoEvents();
                
                if (InjectDLL(rlProcess.Id, dllPath))
                {
                    isInjected = true;
                    
                    // Initialize TAS Core
                    tasCore = new TASCore();
                    tasCore.Initialize();
                    
                    UpdateUI();
                    MessageBox.Show("Successfully connected to Rocket League!\n\nYou can now use the TAS controls below.", 
                        "Success!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {
                    MessageBox.Show("Failed to inject DLL.\n\nMake sure you're running as Administrator!", 
                        "Injection Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    lblStatus.Text = "❌ Injection Failed";
                    lblStatus.ForeColor = Color.Red;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private bool InjectDLL(int processId, string dllPath)
        {
            IntPtr hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, processId);
            if (hProcess == IntPtr.Zero)
                return false;

            IntPtr loadLibraryAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
            if (loadLibraryAddr == IntPtr.Zero)
            {
                CloseHandle(hProcess);
                return false;
            }

            IntPtr allocMemAddress = VirtualAllocEx(hProcess, IntPtr.Zero, (uint)((dllPath.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if (allocMemAddress == IntPtr.Zero)
            {
                CloseHandle(hProcess);
                return false;
            }

            UIntPtr bytesWritten;
            if (!WriteProcessMemory(hProcess, allocMemAddress, System.Text.Encoding.Default.GetBytes(dllPath), (uint)((dllPath.Length + 1) * Marshal.SizeOf(typeof(char))), out bytesWritten))
            {
                CloseHandle(hProcess);
                return false;
            }

            IntPtr hThread = CreateRemoteThread(hProcess, IntPtr.Zero, 0, loadLibraryAddr, allocMemAddress, 0, IntPtr.Zero);
            if (hThread == IntPtr.Zero)
            {
                CloseHandle(hProcess);
                return false;
            }

            CloseHandle(hThread);
            CloseHandle(hProcess);
            return true;
        }

        private void btnStartRecording_Click(object sender, EventArgs e)
        {
            if (tasCore == null) return;
            
            tasCore.StartRecording();
            UpdateUI();
        }

        private void btnStopRecording_Click(object sender, EventArgs e)
        {
            if (tasCore == null) return;
            
            tasCore.StopRecording();
            
            // Ask to save
            using (SaveFileDialog sfd = new SaveFileDialog())
            {
                sfd.Filter = "TAS Recording (*.tas)|*.tas";
                sfd.DefaultExt = "tas";
                sfd.FileName = $"recording_{DateTime.Now:yyyyMMdd_HHmmss}.tas";
                
                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    tasCore.SaveRecording(sfd.FileName);
                    txtLoadedFile.Text = Path.GetFileName(sfd.FileName);
                    MessageBox.Show($"Recording saved!\n\n{sfd.FileName}", "Saved", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            
            UpdateUI();
        }

        private void btnStartReplay_Click(object sender, EventArgs e)
        {
            if (tasCore == null) return;
            
            if (string.IsNullOrEmpty(txtLoadedFile.Text))
            {
                MessageBox.Show("Please load a recording first!", "No Recording", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            
            tasCore.StartReplay();
            UpdateUI();
        }

        private void btnStopReplay_Click(object sender, EventArgs e)
        {
            if (tasCore == null) return;
            
            tasCore.StopReplay();
            UpdateUI();
        }

        private void btnLoadRecording_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog ofd = new OpenFileDialog())
            {
                ofd.Filter = "TAS Recording (*.tas)|*.tas|All Files (*.*)|*.*";
                ofd.DefaultExt = "tas";
                
                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    if (tasCore != null)
                    {
                        tasCore.LoadRecording(ofd.FileName);
                        txtLoadedFile.Text = Path.GetFileName(ofd.FileName);
                        MessageBox.Show($"Recording loaded!\n\n{Path.GetFileName(ofd.FileName)}", "Loaded", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
            }
        }

        private void btnTeleport_Click(object sender, EventArgs e)
        {
            if (tasCore == null) return;
            
            tasCore.TeleportToFirstPosition();
            MessageBox.Show("Teleported to starting position!", "Teleported", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            if (tasCore != null)
            {
                tasCore.StopRecording();
                tasCore.StopReplay();
            }
            base.OnFormClosing(e);
        }
    }
}
