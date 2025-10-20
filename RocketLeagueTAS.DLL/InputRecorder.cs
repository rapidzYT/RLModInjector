using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace RocketLeagueTAS.DLL
{
    [Serializable]
    public class InputState
    {
        public long Timestamp { get; set; }
        public bool Throttle { get; set; }
        public bool Brake { get; set; }
        public bool SteerLeft { get; set; }
        public bool SteerRight { get; set; }
        public bool Jump { get; set; }
        public bool Boost { get; set; }
        public bool Powerslide { get; set; }
        public bool PitchUp { get; set; }
        public bool PitchDown { get; set; }
        public bool YawLeft { get; set; }
        public bool YawRight { get; set; }
        public int MouseX { get; set; }
        public int MouseY { get; set; }
    }

    [Serializable]
    public class GameStateSnapshot
    {
        public long Timestamp { get; set; }
        public Vector3 CarPosition { get; set; }
        public Vector3 CarRotation { get; set; }
        public Vector3 CarVelocity { get; set; }
        public Vector3 CarAngularVelocity { get; set; }
        public Vector3 BallPosition { get; set; }
        public Vector3 BallVelocity { get; set; }
        public Vector3 BallAngularVelocity { get; set; }
    }

    [Serializable]
    public class Vector3
    {
        public float X { get; set; }
        public float Y { get; set; }
        public float Z { get; set; }

        public Vector3() { }
        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }

    [Serializable]
    public class TASRecording
    {
        public List<InputState> Inputs { get; set; } = new List<InputState>();
        public List<GameStateSnapshot> GameStates { get; set; } = new List<GameStateSnapshot>();
        public DateTime CreatedAt { get; set; }
        public string Version { get; set; } = "1.0";
    }

    public class InputRecorder
    {
        private TASRecording currentRecording;
        private bool isRecording = false;
        private long startTime;

        public void StartRecording()
        {
            currentRecording = new TASRecording
            {
                CreatedAt = DateTime.Now
            };
            isRecording = true;
            startTime = DateTime.Now.Ticks;
        }

        public void StopRecording()
        {
            isRecording = false;
        }

        public void RecordInput(InputState inputState)
        {
            if (!isRecording) return;

            // Normalize timestamp relative to recording start
            inputState.Timestamp = inputState.Timestamp - startTime;
            currentRecording.Inputs.Add(inputState);
        }

        public void RecordGameState(GameStateSnapshot gameState)
        {
            if (!isRecording) return;

            gameState.Timestamp = gameState.Timestamp - startTime;
            currentRecording.GameStates.Add(gameState);
        }

        public void SaveToFile(string filename)
        {
            if (currentRecording == null) return;

            try
            {
                using (FileStream fs = new FileStream(filename, FileMode.Create))
                {
                    BinaryFormatter formatter = new BinaryFormatter();
                    formatter.Serialize(fs, currentRecording);
                }
                Console.WriteLine($"Recording saved to {filename}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to save recording: {ex.Message}");
                throw;
            }
        }

        public TASRecording GetCurrentRecording()
        {
            return currentRecording;
        }

        public int GetInputCount()
        {
            return currentRecording?.Inputs.Count ?? 0;
        }

        public int GetGameStateCount()
        {
            return currentRecording?.GameStates.Count ?? 0;
        }

        public bool IsRecording => isRecording;
    }
}