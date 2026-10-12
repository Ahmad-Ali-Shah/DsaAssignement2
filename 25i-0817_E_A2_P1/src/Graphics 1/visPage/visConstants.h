#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace VisConstants {
    const int VIEW_NONE = 0;
    const int VIEW_STACK = 1;
    const int VIEW_QUEUE = 2;

    const int ANIM_IDLE = 0;
    const int ANIM_STACK_POP_PUSH = 1;
    const int ANIM_QUEUE_PROCESS = 2;
    const int ANIM_IMAGE_STEPS = 3;

    const int MAX_STACK_ITEMS = 8;
    const int MAX_QUEUE_ITEMS = 8;

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
    };

    struct VisAnimController {
        int animType; // 0=None, 1=StackPopPush, 2=QueueProcess, 3=ImagePipeline
        float timer;
        int currentStep;
        float stepDuration;
    };
}
