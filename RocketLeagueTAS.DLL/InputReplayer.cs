using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace RocketLeagueTAS.DLL
{
    public class InputReplayer
    {
        private TASRecording loadedRecording;
        private int currentInputIndex = 0;
        private int currentGameStateIndex = 0;
        private bool isReplaying = false;
        private long replayStartTime;

        public void LoadFromFile(string filename)
        {
            try
            {
                using (FileStream fs = new FileStream(filename, FileMode.Open))
                {
                    BinaryFormatter formatter = new BinaryFormatter();
                    loadedRecording = (TASRecording)formatter.Deserialize(fs);
                }
                Console.WriteLine($"Loaded recording with {loadedRecording.Inputs.Count} inputs and {loadedRecording.GameStates.Count} game states");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to load recording: {ex.Message}");
                throw;
            }
        }

        public void StartReplay()
        {
            if (loadedRecording == null)
            {
                throw new InvalidOperationException("No recording loaded");
            }

            currentInputIndex = 0;
            currentGameStateIndex = 0;
            isReplaying = true;
            replayStartTime = DateTime.Now.Ticks;
        }

        public void StopReplay()
        {
            isReplaying = false;
        }

        public InputState GetNextInput()
        {
            if (!isReplaying || loadedRecording == null || currentInputIndex >= loadedRecording.Inputs.Count)
            {
                return null;
            }

            var currentTime = DateTime.Now.Ticks - replayStartTime;
            var input = loadedRecording.Inputs[currentInputIndex];

            // Check if it's time to play this input
            if (currentTime >= input.Timestamp)
            {
                currentInputIndex++;
                return input;
            }

            return null;
        }

        public GameStateSnapshot GetNextGameState()
        {
            if (!isReplaying || loadedRecording == null || currentGameStateIndex >= loadedRecording.GameStates.Count)
            {
                return null;
            }

            var currentTime = DateTime.Now.Ticks - replayStartTime;
            var gameState = loadedRecording.GameStates[currentGameStateIndex];

            // Check if it's time to play this game state
            if (currentTime >= gameState.Timestamp)
            {
                currentGameStateIndex++;
                return gameState;
            }

            return null;
        }

        public GameStateSnapshot GetFirstState()
        {
            if (loadedRecording?.GameStates.Count > 0)
            {
                return loadedRecording.GameStates[0];
            }
            return null;
        }

        public void ResetReplay()
        {
            currentInputIndex = 0;
            currentGameStateIndex = 0;
        }

        public void SeekToTime(long timestamp)
        {
            if (loadedRecording == null) return;

            // Find the closest input and game state for the given timestamp
            currentInputIndex = 0;
            for (int i = 0; i < loadedRecording.Inputs.Count; i++)
            {
                if (loadedRecording.Inputs[i].Timestamp <= timestamp)
                {
                    currentInputIndex = i;
                }
                else
                {
                    break;
                }
            }

            currentGameStateIndex = 0;
            for (int i = 0; i < loadedRecording.GameStates.Count; i++)
            {
                if (loadedRecording.GameStates[i].Timestamp <= timestamp)
                {
                    currentGameStateIndex = i;
                }
                else
                {
                    break;
                }
            }
        }

        public float GetReplayProgress()
        {
            if (loadedRecording == null || loadedRecording.Inputs.Count == 0)
            {
                return 0f;
            }

            var lastInputTime = loadedRecording.Inputs[loadedRecording.Inputs.Count - 1].Timestamp;
            var currentTime = DateTime.Now.Ticks - replayStartTime;
            
            return Math.Min(1.0f, (float)currentTime / lastInputTime);
        }

        public long GetReplayDuration()
        {
            if (loadedRecording?.Inputs.Count > 0)
            {
                return loadedRecording.Inputs[loadedRecording.Inputs.Count - 1].Timestamp;
            }
            return 0;
        }

        public bool IsReplaying => isReplaying;
        public bool HasRecording => loadedRecording != null;
        public int InputCount => loadedRecording?.Inputs.Count ?? 0;
        public int GameStateCount => loadedRecording?.GameStates.Count ?? 0;
    }
}