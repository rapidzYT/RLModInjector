using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using RocketLeagueTAS.DLL;

namespace RocketLeagueTAS.GUI
{
    public partial class TASGUI : Form
    {
        private TASCore tasCore;
        private Timer updateTimer;
        private string currentRecordingFile = "";

        public TASGUI(TASCore tasCore)
        {
            this.tasCore = tasCore;
            InitializeComponent();
            InitializeTimer();
            UpdateUI();
        }

        private void InitializeTimer()
        {
            updateTimer = new Timer();
            updateTimer.Interval = 100; // Update every 100ms
            updateTimer.Tick += UpdateTimer_Tick;
            updateTimer.Start();
        }

        private void UpdateTimer_Tick(object sender, EventArgs e)
        {
            UpdateUI();
        }

        private void UpdateUI()
        {
            // Update status labels
            lblRecordingStatus.Text = tasCore.IsRecording ? "Recording" : "Not Recording";
            lblRecordingStatus.ForeColor = tasCore.IsRecording ? Color.Red : Color.Green;

            lblReplayStatus.Text = tasCore.IsReplaying ? "Replaying" : "Not Replaying";
            lblReplayStatus.ForeColor = tasCore.IsReplaying ? Color.Blue : Color.Gray;

            lblPauseStatus.Text = tasCore.IsPaused ? "Paused" : "Running";
            lblPauseStatus.ForeColor = tasCore.IsPaused ? Color.Orange : Color.Green;

            // Update button states
            btnStartRecording.Enabled = !tasCore.IsRecording && !tasCore.IsReplaying;
            btnStopRecording.Enabled = tasCore.IsRecording;
            btnStartReplay.Enabled = !tasCore.IsRecording && !tasCore.IsReplaying && !string.IsNullOrEmpty(currentRecordingFile);
            btnStopReplay.Enabled = tasCore.IsReplaying;
            btnPause.Enabled = tasCore.IsRecording || tasCore.IsReplaying;
            btnResume.Enabled = tasCore.IsPaused;
        }

        private void btnStartRecording_Click(object sender, EventArgs e)
        {
            try
            {
                tasCore.StartRecording();
                MessageBox.Show("Recording started!", "TAS", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to start recording: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnStopRecording_Click(object sender, EventArgs e)
        {
            try
            {
                tasCore.StopRecording();
                
                // Ask user to save recording
                using (var saveDialog = new SaveFileDialog())
                {
                    saveDialog.Filter = "TAS Recording (*.tas)|*.tas|All Files (*.*)|*.*";
                    saveDialog.DefaultExt = "tas";
                    saveDialog.FileName = $"recording_{DateTime.Now:yyyyMMdd_HHmmss}.tas";
                    
                    if (saveDialog.ShowDialog() == DialogResult.OK)
                    {
                        tasCore.SaveRecording(saveDialog.FileName);
                        currentRecordingFile = saveDialog.FileName;
                        MessageBox.Show($"Recording saved to {saveDialog.FileName}", "TAS", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to stop recording: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnStartReplay_Click(object sender, EventArgs e)
        {
            try
            {
                if (string.IsNullOrEmpty(currentRecordingFile))
                {
                    MessageBox.Show("Please load a recording first!", "TAS", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                tasCore.LoadRecording(currentRecordingFile);
                tasCore.StartReplay();
                MessageBox.Show("Replay started!", "TAS", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to start replay: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnStopReplay_Click(object sender, EventArgs e)
        {
            try
            {
                tasCore.StopReplay();
                MessageBox.Show("Replay stopped!", "TAS", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to stop replay: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnPause_Click(object sender, EventArgs e)
        {
            try
            {
                tasCore.Pause();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to pause: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnResume_Click(object sender, EventArgs e)
        {
            try
            {
                tasCore.Resume();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to resume: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnLoadRecording_Click(object sender, EventArgs e)
        {
            try
            {
                using (var openDialog = new OpenFileDialog())
                {
                    openDialog.Filter = "TAS Recording (*.tas)|*.tas|All Files (*.*)|*.*";
                    openDialog.DefaultExt = "tas";
                    
                    if (openDialog.ShowDialog() == DialogResult.OK)
                    {
                        currentRecordingFile = openDialog.FileName;
                        tasCore.LoadRecording(currentRecordingFile);
                        lblLoadedFile.Text = Path.GetFileName(currentRecordingFile);
                        MessageBox.Show($"Recording loaded: {openDialog.FileName}", "TAS", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to load recording: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnTeleportToStart_Click(object sender, EventArgs e)
        {
            try
            {
                tasCore.TeleportToFirstPosition();
                MessageBox.Show("Teleported to first position!", "TAS", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to teleport: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            try
            {
                tasCore.StopRecording();
                tasCore.StopReplay();
                updateTimer?.Stop();
                updateTimer?.Dispose();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error during cleanup: {ex.Message}");
            }
            
            base.OnFormClosing(e);
        }
    }
}