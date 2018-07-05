#include "../GameObjects/Board.hpp"

#include "../Engine/Button.hpp"
#include "../Widgets/SettingsWidget.hpp"
#include "../Widgets/GameOverWidget.hpp"

class GameScene
{
    public:
        GameScene(Resources*);
        void InitButtons();
        void Draw(SDL_Renderer*);
        void HandleClick(touchPosition*);
        Board* GetBoard() { return _board; };

    private:
        Board* _board;
        Resources* _resources;
        std::vector<Button*> _buttons;
        std::vector<Widget*> _widgets;
};