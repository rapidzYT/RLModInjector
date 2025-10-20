using System;

namespace RocketLeagueTAS.DLL
{
    public class GameState
    {
        private MemoryManager memoryManager;
        private GameStateSnapshot currentState;
        private bool isInitialized = false;

        public void Initialize(MemoryManager memoryManager)
        {
            this.memoryManager = memoryManager;
            isInitialized = true;
            Console.WriteLine("Game state manager initialized");
        }

        public void Update()
        {
            if (!isInitialized || memoryManager == null) return;

            try
            {
                currentState = new GameStateSnapshot
                {
                    Timestamp = DateTime.Now.Ticks,
                    CarPosition = memoryManager.GetCarPosition(),
                    CarRotation = memoryManager.GetCarRotation(),
                    CarVelocity = memoryManager.GetCarVelocity(),
                    CarAngularVelocity = memoryManager.GetCarAngularVelocity(),
                    BallPosition = memoryManager.GetBallPosition(),
                    BallVelocity = memoryManager.GetBallVelocity(),
                    BallAngularVelocity = memoryManager.GetBallAngularVelocity()
                };
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to update game state: {ex.Message}");
            }
        }

        public GameStateSnapshot GetCurrentState()
        {
            return currentState;
        }

        public void SetState(GameStateSnapshot state)
        {
            if (!isInitialized || memoryManager == null) return;

            try
            {
                memoryManager.SetCarPosition(state.CarPosition);
                memoryManager.SetCarRotation(state.CarRotation);
                memoryManager.SetCarVelocity(state.CarVelocity);
                memoryManager.SetCarAngularVelocity(state.CarAngularVelocity);
                memoryManager.SetBallPosition(state.BallPosition);
                memoryManager.SetBallVelocity(state.BallVelocity);
                memoryManager.SetBallAngularVelocity(state.BallAngularVelocity);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to set game state: {ex.Message}");
            }
        }

        public bool IsInGame()
        {
            // Check if we're in a match (not in menu)
            // This would need to be implemented based on specific memory patterns
            return currentState != null && 
                   currentState.CarPosition.X != 0 && 
                   currentState.CarPosition.Y != 0 && 
                   currentState.CarPosition.Z != 0;
        }

        public bool IsInitialized => isInitialized;
    }
}