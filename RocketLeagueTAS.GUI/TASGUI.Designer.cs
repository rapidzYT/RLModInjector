namespace RocketLeagueTAS.GUI
{
    partial class TASGUI
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.GroupBox grpRecording;
        private System.Windows.Forms.Button btnStartRecording;
        private System.Windows.Forms.Button btnStopRecording;
        private System.Windows.Forms.Label lblRecordingStatus;
        private System.Windows.Forms.GroupBox grpReplay;
        private System.Windows.Forms.Button btnStartReplay;
        private System.Windows.Forms.Button btnStopReplay;
        private System.Windows.Forms.Label lblReplayStatus;
        private System.Windows.Forms.Button btnLoadRecording;
        private System.Windows.Forms.Label lblLoadedFile;
        private System.Windows.Forms.GroupBox grpControl;
        private System.Windows.Forms.Button btnPause;
        private System.Windows.Forms.Button btnResume;
        private System.Windows.Forms.Label lblPauseStatus;
        private System.Windows.Forms.Button btnTeleportToStart;
        private System.Windows.Forms.GroupBox grpStatus;
        private System.Windows.Forms.Label lblTitle;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.grpRecording = new System.Windows.Forms.GroupBox();
            this.btnStartRecording = new System.Windows.Forms.Button();
            this.btnStopRecording = new System.Windows.Forms.Button();
            this.lblRecordingStatus = new System.Windows.Forms.Label();
            this.grpReplay = new System.Windows.Forms.GroupBox();
            this.btnStartReplay = new System.Windows.Forms.Button();
            this.btnStopReplay = new System.Windows.Forms.Button();
            this.lblReplayStatus = new System.Windows.Forms.Label();
            this.btnLoadRecording = new System.Windows.Forms.Button();
            this.lblLoadedFile = new System.Windows.Forms.Label();
            this.grpControl = new System.Windows.Forms.GroupBox();
            this.btnPause = new System.Windows.Forms.Button();
            this.btnResume = new System.Windows.Forms.Button();
            this.lblPauseStatus = new System.Windows.Forms.Label();
            this.btnTeleportToStart = new System.Windows.Forms.Button();
            this.grpStatus = new System.Windows.Forms.GroupBox();
            this.lblTitle = new System.Windows.Forms.Label();
            this.grpRecording.SuspendLayout();
            this.grpReplay.SuspendLayout();
            this.grpControl.SuspendLayout();
            this.grpStatus.SuspendLayout();
            this.SuspendLayout();
            
            // 
            // lblTitle
            // 
            this.lblTitle.AutoSize = true;
            this.lblTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Bold);
            this.lblTitle.Location = new System.Drawing.Point(12, 9);
            this.lblTitle.Name = "lblTitle";
            this.lblTitle.Size = new System.Drawing.Size(200, 26);
            this.lblTitle.TabIndex = 0;
            this.lblTitle.Text = "Rocket League TAS";
            
            // 
            // grpRecording
            // 
            this.grpRecording.Controls.Add(this.btnStartRecording);
            this.grpRecording.Controls.Add(this.btnStopRecording);
            this.grpRecording.Controls.Add(this.lblRecordingStatus);
            this.grpRecording.Location = new System.Drawing.Point(12, 50);
            this.grpRecording.Name = "grpRecording";
            this.grpRecording.Size = new System.Drawing.Size(200, 100);
            this.grpRecording.TabIndex = 1;
            this.grpRecording.TabStop = false;
            this.grpRecording.Text = "Recording";
            
            // 
            // btnStartRecording
            // 
            this.btnStartRecording.Location = new System.Drawing.Point(15, 25);
            this.btnStartRecording.Name = "btnStartRecording";
            this.btnStartRecording.Size = new System.Drawing.Size(80, 30);
            this.btnStartRecording.TabIndex = 0;
            this.btnStartRecording.Text = "Start";
            this.btnStartRecording.UseVisualStyleBackColor = true;
            this.btnStartRecording.Click += new System.EventHandler(this.btnStartRecording_Click);
            
            // 
            // btnStopRecording
            // 
            this.btnStopRecording.Location = new System.Drawing.Point(105, 25);
            this.btnStopRecording.Name = "btnStopRecording";
            this.btnStopRecording.Size = new System.Drawing.Size(80, 30);
            this.btnStopRecording.TabIndex = 1;
            this.btnStopRecording.Text = "Stop";
            this.btnStopRecording.UseVisualStyleBackColor = true;
            this.btnStopRecording.Click += new System.EventHandler(this.btnStopRecording_Click);
            
            // 
            // lblRecordingStatus
            // 
            this.lblRecordingStatus.AutoSize = true;
            this.lblRecordingStatus.Location = new System.Drawing.Point(15, 65);
            this.lblRecordingStatus.Name = "lblRecordingStatus";
            this.lblRecordingStatus.Size = new System.Drawing.Size(85, 13);
            this.lblRecordingStatus.TabIndex = 2;
            this.lblRecordingStatus.Text = "Not Recording";
            
            // 
            // grpReplay
            // 
            this.grpReplay.Controls.Add(this.btnStartReplay);
            this.grpReplay.Controls.Add(this.btnStopReplay);
            this.grpReplay.Controls.Add(this.lblReplayStatus);
            this.grpReplay.Controls.Add(this.btnLoadRecording);
            this.grpReplay.Controls.Add(this.lblLoadedFile);
            this.grpReplay.Location = new System.Drawing.Point(12, 160);
            this.grpReplay.Name = "grpReplay";
            this.grpReplay.Size = new System.Drawing.Size(200, 130);
            this.grpReplay.TabIndex = 2;
            this.grpReplay.TabStop = false;
            this.grpReplay.Text = "Replay";
            
            // 
            // btnStartReplay
            // 
            this.btnStartReplay.Location = new System.Drawing.Point(15, 25);
            this.btnStartReplay.Name = "btnStartReplay";
            this.btnStartReplay.Size = new System.Drawing.Size(80, 30);
            this.btnStartReplay.TabIndex = 0;
            this.btnStartReplay.Text = "Start";
            this.btnStartReplay.UseVisualStyleBackColor = true;
            this.btnStartReplay.Click += new System.EventHandler(this.btnStartReplay_Click);
            
            // 
            // btnStopReplay
            // 
            this.btnStopReplay.Location = new System.Drawing.Point(105, 25);
            this.btnStopReplay.Name = "btnStopReplay";
            this.btnStopReplay.Size = new System.Drawing.Size(80, 30);
            this.btnStopReplay.TabIndex = 1;
            this.btnStopReplay.Text = "Stop";
            this.btnStopReplay.UseVisualStyleBackColor = true;
            this.btnStopReplay.Click += new System.EventHandler(this.btnStopReplay_Click);
            
            // 
            // lblReplayStatus
            // 
            this.lblReplayStatus.AutoSize = true;
            this.lblReplayStatus.Location = new System.Drawing.Point(15, 65);
            this.lblReplayStatus.Name = "lblReplayStatus";
            this.lblReplayStatus.Size = new System.Drawing.Size(75, 13);
            this.lblReplayStatus.TabIndex = 2;
            this.lblReplayStatus.Text = "Not Replaying";
            
            // 
            // btnLoadRecording
            // 
            this.btnLoadRecording.Location = new System.Drawing.Point(15, 85);
            this.btnLoadRecording.Name = "btnLoadRecording";
            this.btnLoadRecording.Size = new System.Drawing.Size(80, 30);
            this.btnLoadRecording.TabIndex = 3;
            this.btnLoadRecording.Text = "Load";
            this.btnLoadRecording.UseVisualStyleBackColor = true;
            this.btnLoadRecording.Click += new System.EventHandler(this.btnLoadRecording_Click);
            
            // 
            // lblLoadedFile
            // 
            this.lblLoadedFile.AutoSize = true;
            this.lblLoadedFile.Location = new System.Drawing.Point(105, 95);
            this.lblLoadedFile.Name = "lblLoadedFile";
            this.lblLoadedFile.Size = new System.Drawing.Size(0, 13);
            this.lblLoadedFile.TabIndex = 4;
            
            // 
            // grpControl
            // 
            this.grpControl.Controls.Add(this.btnPause);
            this.grpControl.Controls.Add(this.btnResume);
            this.grpControl.Controls.Add(this.lblPauseStatus);
            this.grpControl.Controls.Add(this.btnTeleportToStart);
            this.grpControl.Location = new System.Drawing.Point(12, 300);
            this.grpControl.Name = "grpControl";
            this.grpControl.Size = new System.Drawing.Size(200, 120);
            this.grpControl.TabIndex = 3;
            this.grpControl.TabStop = false;
            this.grpControl.Text = "Control";
            
            // 
            // btnPause
            // 
            this.btnPause.Location = new System.Drawing.Point(15, 25);
            this.btnPause.Name = "btnPause";
            this.btnPause.Size = new System.Drawing.Size(80, 30);
            this.btnPause.TabIndex = 0;
            this.btnPause.Text = "Pause";
            this.btnPause.UseVisualStyleBackColor = true;
            this.btnPause.Click += new System.EventHandler(this.btnPause_Click);
            
            // 
            // btnResume
            // 
            this.btnResume.Location = new System.Drawing.Point(105, 25);
            this.btnResume.Name = "btnResume";
            this.btnResume.Size = new System.Drawing.Size(80, 30);
            this.btnResume.TabIndex = 1;
            this.btnResume.Text = "Resume";
            this.btnResume.UseVisualStyleBackColor = true;
            this.btnResume.Click += new System.EventHandler(this.btnResume_Click);
            
            // 
            // lblPauseStatus
            // 
            this.lblPauseStatus.AutoSize = true;
            this.lblPauseStatus.Location = new System.Drawing.Point(15, 65);
            this.lblPauseStatus.Name = "lblPauseStatus";
            this.lblPauseStatus.Size = new System.Drawing.Size(50, 13);
            this.lblPauseStatus.TabIndex = 2;
            this.lblPauseStatus.Text = "Running";
            
            // 
            // btnTeleportToStart
            // 
            this.btnTeleportToStart.Location = new System.Drawing.Point(15, 85);
            this.btnTeleportToStart.Name = "btnTeleportToStart";
            this.btnTeleportToStart.Size = new System.Drawing.Size(170, 30);
            this.btnTeleportToStart.TabIndex = 3;
            this.btnTeleportToStart.Text = "Teleport to Start";
            this.btnTeleportToStart.UseVisualStyleBackColor = true;
            this.btnTeleportToStart.Click += new System.EventHandler(this.btnTeleportToStart_Click);
            
            // 
            // TASGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(230, 440);
            this.Controls.Add(this.grpControl);
            this.Controls.Add(this.grpReplay);
            this.Controls.Add(this.grpRecording);
            this.Controls.Add(this.lblTitle);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "TASGUI";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Rocket League TAS";
            this.grpRecording.ResumeLayout(false);
            this.grpRecording.PerformLayout();
            this.grpReplay.ResumeLayout(false);
            this.grpReplay.PerformLayout();
            this.grpControl.ResumeLayout(false);
            this.grpControl.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();
        }
    }
}