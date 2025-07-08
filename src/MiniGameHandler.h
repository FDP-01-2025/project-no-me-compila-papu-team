#ifndef MINIGAMEHANDLER_H
#define MINIGAMEHANDLER_H

class MiniGameHandler {
public:
    MiniGameHandler();
    bool playRandomMiniGame();
    // Nuevos minijuegos
    bool playGuessNumber();
    bool playMemorySequence();
    bool playQuickReaction();
};

#endif // MINIGAMEHANDLER_H