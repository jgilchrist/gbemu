#include "sfml_screen.h"

#include "../../util/log.h"

SFMLScreen::SFMLScreen(uint _magnification) :
    magnification(_magnification),
    width(GAMEBOY_WIDTH*magnification),
    height(GAMEBOY_HEIGHT*magnification),
    pixel_size(magnification),
    window(sf::VideoMode(width, height), "Emulator", sf::Style::Titlebar | sf::Style::Close)
{
    image.create(width, height);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

void SFMLScreen::draw(const FrameBuffer& buffer) {
    window.clear(sf::Color::White);

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    set_pixels(buffer);
    texture.loadFromImage(image);
    sprite.setTexture(texture, true);

    window.draw(sprite);

    window.display();
}

void SFMLScreen::set_pixels(const FrameBuffer& buffer) {
    for (unsigned x = 0; x < GAMEBOY_WIDTH; x++) {
        for (unsigned y = 0; y < GAMEBOY_HEIGHT; y++) {
            sf::Color pixel_color = get_color(buffer.get_pixel(x, y));

            set_large_pixel(x, y, pixel_color);
        }
    }
}

void SFMLScreen::set_large_pixel(uint x, uint y, sf::Color color) {
    for (unsigned w = 0; w < pixel_size; w++) {
        for (unsigned h = 0; h < pixel_size; h++) {
            image.setPixel(x * pixel_size + w, y * pixel_size + h, color);
        }
    }
}

sf::Color SFMLScreen::get_color(Color color) {
    switch (color) {
        case Color::Color0: return sf::Color(255, 255, 255);
        case Color::Color1: return sf::Color(170, 170, 170);
        case Color::Color2: return sf::Color( 85,  85,  85);
        case Color::Color3: return sf::Color(  0,   0,   0);
    }
}

bool SFMLScreen::is_open() {
    return window.isOpen();
}
