#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace VisConstants {
    const int viewNone = 0;
    const int viewStack = 1;
    const int viewQueue = 2;

    const int animIdle = 0;
    const int animStackPopPush = 1;
    const int animQueueProcess = 2;
    const int animImageSteps = 3;

    const int maxStackItems = 8;
    const int maxQueueItems = 8;

    struct VisTextures {
        sf::Texture bg;
        sf::Texture banner;
        sf::Texture blocks;
        sf::Texture tools;
        sf::Texture rotations;
        sf::Texture arrow;
        sf::Texture adjustment;
    };

    struct SubWindow {
        bool visible;
        bool minimized;
        int type; // 1 = Stack, 2 = Queue
        float x;
        float y;
        float w;
        float h;
    };

    struct VisButtonRects {
        sf::FloatRect showStackBtn;
        sf::FloatRect showQueueBtn;
        sf::FloatRect animDataBtn;
        sf::FloatRect animImageBtn;
        sf::FloatRect backBtn;
    };

    struct VisAnimController {
        int animType; // 0=None, 1=StackPopPush, 2=QueueProcess, 3=ImagePipeline
        float timer;
        int currentStep;
        float stepDuration;
    };
}
