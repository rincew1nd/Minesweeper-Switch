#include "../Engine/Input.hpp"
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
        void HandleClick(TouchInfo*);
        Board* GetBoard() { return _board; };

    private:
        Board* _board;
        Resources* _resources;
        TTF_Font* _font = nullptr;

        std::vector<Button*> _buttons;
        std::vector<Widget*> _widgets;
        std::vector<TextObject*> _textes;
};