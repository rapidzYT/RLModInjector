namespace RocketLeagueTAS.App
{
    partial class MainForm
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.Label lblTitle;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Button btnInject;
        private System.Windows.Forms.GroupBox grpTASControls;
        private System.Windows.Forms.GroupBox grpRecording;
        private System.Windows.Forms.Button btnStartRecording;
        private System.Windows.Forms.Button btnStopRecording;
        private System.Windows.Forms.Label lblRecordingStatus;
        private System.Windows.Forms.GroupBox grpReplay;
        private System.Windows.Forms.Button btnStartReplay;
        private System.Windows.Forms.Button btnStopReplay;
        private System.Windows.Forms.Label lblReplayStatus;
        private System.Windows.Forms.Button btnLoadRecording;
        private System.Windows.Forms.TextBox txtLoadedFile;
        private System.Windows.Forms.Label lblLoadedFile;
        private System.Windows.Forms.Button btnTeleport;
        private System.Windows.Forms.Panel panelHeader;

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
            this.lblTitle = new System.Windows.Forms.Label();
            this.lblStatus = new System.Windows.Forms.Label();
            this.btnInject = new System.Windows.Forms.Button();
            this.grpTASControls = new System.Windows.Forms.GroupBox();
            this.grpRecording = new System.Windows.Forms.GroupBox();
            this.btnStartRecording = new System.Windows.Forms.Button();
            this.btnStopRecording = new System.Windows.Forms.Button();
            this.lblRecordingStatus = new System.Windows.Forms.Label();
            this.grpReplay = new System.Windows.Forms.GroupBox();
            this.btnStartReplay = new System.Windows.Forms.Button();
            this.btnStopReplay = new System.Windows.Forms.Button();
            this.lblReplayStatus = new System.Windows.Forms.Label();
            this.btnLoadRecording = new System.Windows.Forms.Button();
            this.txtLoadedFile = new System.Windows.Forms.TextBox();
            this.lblLoadedFile = new System.Windows.Forms.Label();
            this.btnTeleport = new System.Windows.Forms.Button();
            this.panelHeader = new System.Windows.Forms.Panel();
            this.grpTASControls.SuspendLayout();
            this.grpRecording.SuspendLayout();
            this.grpReplay.SuspendLayout();
            this.panelHeader.SuspendLayout();
            this.SuspendLayout();
            
            // 
            // panelHeader
            // 
            this.panelHeader.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(30)))), ((int)(((byte)(30)))), ((int)(((byte)(30)))));
            this.panelHeader.Controls.Add(this.lblTitle);
            this.panelHeader.Dock = System.Windows.Forms.DockStyle.Top;
            this.panelHeader.Location = new System.Drawing.Point(0, 0);
            this.panelHeader.Name = "panelHeader";
            this.panelHeader.Size = new System.Drawing.Size(500, 80);
            this.panelHeader.TabIndex = 0;
            
            // 
            // lblTitle
            // 
            this.lblTitle.AutoSize = true;
            this.lblTitle.Font = new System.Drawing.Font("Segoe UI", 24F, System.Drawing.FontStyle.Bold);
            this.lblTitle.ForeColor = System.Drawing.Color.White;
            this.lblTitle.Location = new System.Drawing.Point(20, 20);
            this.lblTitle.Name = "lblTitle";
            this.lblTitle.Size = new System.Drawing.Size(300, 45);
            this.lblTitle.TabIndex = 0;
            this.lblTitle.Text = "🚗 Rocket League TAS";
            
            // 
            // lblStatus
            // 
            this.lblStatus.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Bold);
            this.lblStatus.Location = new System.Drawing.Point(20, 100);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(460, 30);
            this.lblStatus.TabIndex = 1;
            this.lblStatus.Text = "⚠️ Not Connected";
            this.lblStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            
            // 
            // btnInject
            // 
            this.btnInject.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(122)))), ((int)(((byte)(204)))));
            this.btnInject.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnInject.Font = new System.Drawing.Font("Segoe UI", 14F, System.Drawing.FontStyle.Bold);
            this.btnInject.ForeColor = System.Drawing.Color.White;
            this.btnInject.Location = new System.Drawing.Point(20, 140);
            this.btnInject.Name = "btnInject";
            this.btnInject.Size = new System.Drawing.Size(460, 50);
            this.btnInject.TabIndex = 2;
            this.btnInject.Text = "🔌 Connect to Rocket League";
            this.btnInject.UseVisualStyleBackColor = false;
            this.btnInject.Click += new System.EventHandler(this.btnInject_Click);
            
            // 
            // grpTASControls
            // 
            this.grpTASControls.Controls.Add(this.grpRecording);
            this.grpTASControls.Controls.Add(this.grpReplay);
            this.grpTASControls.Enabled = false;
            this.grpTASControls.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.grpTASControls.Location = new System.Drawing.Point(20, 210);
            this.grpTASControls.Name = "grpTASControls";
            this.grpTASControls.Size = new System.Drawing.Size(460, 380);
            this.grpTASControls.TabIndex = 3;
            this.grpTASControls.TabStop = false;
            this.grpTASControls.Text = "TAS Controls";
            
            // 
            // grpRecording
            // 
            this.grpRecording.Controls.Add(this.btnStartRecording);
            this.grpRecording.Controls.Add(this.btnStopRecording);
            this.grpRecording.Controls.Add(this.lblRecordingStatus);
            this.grpRecording.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.grpRecording.Location = new System.Drawing.Point(15, 30);
            this.grpRecording.Name = "grpRecording";
            this.grpRecording.Size = new System.Drawing.Size(430, 120);
            this.grpRecording.TabIndex = 0;
            this.grpRecording.TabStop = false;
            this.grpRecording.Text = "📹 Recording";
            
            // 
            // btnStartRecording
            // 
            this.btnStartRecording.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(150)))), ((int)(((byte)(0)))));
            this.btnStartRecording.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnStartRecording.Font = new System.Drawing.Font("Segoe UI", 11F, System.Drawing.FontStyle.Bold);
            this.btnStartRecording.ForeColor = System.Drawing.Color.White;
            this.btnStartRecording.Location = new System.Drawing.Point(15, 30);
            this.btnStartRecording.Name = "btnStartRecording";
            this.btnStartRecording.Size = new System.Drawing.Size(200, 40);
            this.btnStartRecording.TabIndex = 0;
            this.btnStartRecording.Text = "🔴 Start Recording";
            this.btnStartRecording.UseVisualStyleBackColor = false;
            this.btnStartRecording.Click += new System.EventHandler(this.btnStartRecording_Click);
            
            // 
            // btnStopRecording
            // 
            this.btnStopRecording.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(180)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.btnStopRecording.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnStopRecording.Font = new System.Drawing.Font("Segoe UI", 11F, System.Drawing.FontStyle.Bold);
            this.btnStopRecording.ForeColor = System.Drawing.Color.White;
            this.btnStopRecording.Location = new System.Drawing.Point(225, 30);
            this.btnStopRecording.Name = "btnStopRecording";
            this.btnStopRecording.Size = new System.Drawing.Size(190, 40);
            this.btnStopRecording.TabIndex = 1;
            this.btnStopRecording.Text = "⏹️ Stop & Save";
            this.btnStopRecording.UseVisualStyleBackColor = false;
            this.btnStopRecording.Click += new System.EventHandler(this.btnStopRecording_Click);
            
            // 
            // lblRecordingStatus
            // 
            this.lblRecordingStatus.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.lblRecordingStatus.Location = new System.Drawing.Point(15, 80);
            this.lblRecordingStatus.Name = "lblRecordingStatus";
            this.lblRecordingStatus.Size = new System.Drawing.Size(400, 25);
            this.lblRecordingStatus.TabIndex = 2;
            this.lblRecordingStatus.Text = "⚫ Not Recording";
            this.lblRecordingStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            
            // 
            // grpReplay
            // 
            this.grpReplay.Controls.Add(this.btnStartReplay);
            this.grpReplay.Controls.Add(this.btnStopReplay);
            this.grpReplay.Controls.Add(this.lblReplayStatus);
            this.grpReplay.Controls.Add(this.btnLoadRecording);
            this.grpReplay.Controls.Add(this.lblLoadedFile);
            this.grpReplay.Controls.Add(this.txtLoadedFile);
            this.grpReplay.Controls.Add(this.btnTeleport);
            this.grpReplay.Font = new System.Drawing.Font("Segoe UI", 10F);
            this.grpReplay.Location = new System.Drawing.Point(15, 160);
            this.grpReplay.Name = "grpReplay";
            this.grpReplay.Size = new System.Drawing.Size(430, 210);
            this.grpReplay.TabIndex = 1;
            this.grpReplay.TabStop = false;
            this.grpReplay.Text = "▶️ Replay";
            
            // 
            // btnStartReplay
            // 
            this.btnStartReplay.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(100)))), ((int)(((byte)(180)))));
            this.btnStartReplay.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnStartReplay.Font = new System.Drawing.Font("Segoe UI", 11F, System.Drawing.FontStyle.Bold);
            this.btnStartReplay.ForeColor = System.Drawing.Color.White;
            this.btnStartReplay.Location = new System.Drawing.Point(15, 30);
            this.btnStartReplay.Name = "btnStartReplay";
            this.btnStartReplay.Size = new System.Drawing.Size(200, 40);
            this.btnStartReplay.TabIndex = 0;
            this.btnStartReplay.Text = "▶️ Start Replay";
            this.btnStartReplay.UseVisualStyleBackColor = false;
            this.btnStartReplay.Click += new System.EventHandler(this.btnStartReplay_Click);
            
            // 
            // btnStopReplay
            // 
            this.btnStopReplay.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(180)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.btnStopReplay.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnStopReplay.Font = new System.Drawing.Font("Segoe UI", 11F, System.Drawing.FontStyle.Bold);
            this.btnStopReplay.ForeColor = System.Drawing.Color.White;
            this.btnStopReplay.Location = new System.Drawing.Point(225, 30);
            this.btnStopReplay.Name = "btnStopReplay";
            this.btnStopReplay.Size = new System.Drawing.Size(190, 40);
            this.btnStopReplay.TabIndex = 1;
            this.btnStopReplay.Text = "⏹️ Stop Replay";
            this.btnStopReplay.UseVisualStyleBackColor = false;
            this.btnStopReplay.Click += new System.EventHandler(this.btnStopReplay_Click);
            
            // 
            // lblReplayStatus
            // 
            this.lblReplayStatus.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.lblReplayStatus.Location = new System.Drawing.Point(15, 80);
            this.lblReplayStatus.Name = "lblReplayStatus";
            this.lblReplayStatus.Size = new System.Drawing.Size(400, 25);
            this.lblReplayStatus.TabIndex = 2;
            this.lblReplayStatus.Text = "⏹️ Not Replaying";
            this.lblReplayStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            
            // 
            // lblLoadedFile
            // 
            this.lblLoadedFile.AutoSize = true;
            this.lblLoadedFile.Location = new System.Drawing.Point(15, 115);
            this.lblLoadedFile.Name = "lblLoadedFile";
            this.lblLoadedFile.Size = new System.Drawing.Size(100, 19);
            this.lblLoadedFile.TabIndex = 3;
            this.lblLoadedFile.Text = "Loaded File:";
            
            // 
            // txtLoadedFile
            // 
            this.txtLoadedFile.Location = new System.Drawing.Point(15, 140);
            this.txtLoadedFile.Name = "txtLoadedFile";
            this.txtLoadedFile.ReadOnly = true;
            this.txtLoadedFile.Size = new System.Drawing.Size(260, 25);
            this.txtLoadedFile.TabIndex = 4;
            this.txtLoadedFile.Text = "No file loaded";
            
            // 
            // btnLoadRecording
            // 
            this.btnLoadRecording.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(80)))), ((int)(((byte)(80)))), ((int)(((byte)(80)))));
            this.btnLoadRecording.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnLoadRecording.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold);
            this.btnLoadRecording.ForeColor = System.Drawing.Color.White;
            this.btnLoadRecording.Location = new System.Drawing.Point(285, 138);
            this.btnLoadRecording.Name = "btnLoadRecording";
            this.btnLoadRecording.Size = new System.Drawing.Size(130, 30);
            this.btnLoadRecording.TabIndex = 5;
            this.btnLoadRecording.Text = "📁 Load File";
            this.btnLoadRecording.UseVisualStyleBackColor = false;
            this.btnLoadRecording.Click += new System.EventHandler(this.btnLoadRecording_Click);
            
            // 
            // btnTeleport
            // 
            this.btnTeleport.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(150)))), ((int)(((byte)(100)))), ((int)(((byte)(0)))));
            this.btnTeleport.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnTeleport.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.btnTeleport.ForeColor = System.Drawing.Color.White;
            this.btnTeleport.Location = new System.Drawing.Point(15, 175);
            this.btnTeleport.Name = "btnTeleport";
            this.btnTeleport.Size = new System.Drawing.Size(400, 30);
            this.btnTeleport.TabIndex = 6;
            this.btnTeleport.Text = "📍 Teleport to Start Position";
            this.btnTeleport.UseVisualStyleBackColor = false;
            this.btnTeleport.Click += new System.EventHandler(this.btnTeleport_Click);
            
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(500, 610);
            this.Controls.Add(this.grpTASControls);
            this.Controls.Add(this.btnInject);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.panelHeader);
            this.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Rocket League TAS";
            this.grpTASControls.ResumeLayout(false);
            this.grpRecording.ResumeLayout(false);
            this.grpReplay.ResumeLayout(false);
            this.grpReplay.PerformLayout();
            this.panelHeader.ResumeLayout(false);
            this.panelHeader.PerformLayout();
            this.ResumeLayout(false);
        }
    }
}
