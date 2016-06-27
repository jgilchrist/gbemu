#pragma once

#include "../screen.h"

class SFMLScreen : public Screen {
public:
    SFMLScreen();
    ~SFMLScreen() override;

    void draw(const FrameBuffer& buffer) override;
    bool is_open() override;

private:
    sf::RenderWindow window;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    void set_pixels(const FrameBuffer& buffer);
    sf::Color get_color(Color color);
};
