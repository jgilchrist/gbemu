#include "sfml_screen.h"

SFMLScreen::SFMLScreen() :
    window(sf::VideoMode(GAMEBOY_WIDTH, GAMEBOY_HEIGHT), "Emulator")
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

SFMLScreen::~SFMLScreen() {
}

void SFMLScreen::draw(const FrameBuffer& buffer) {
    window.clear(sf::Color::Black);

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    window.display();
}

bool SFMLScreen::is_open() {
    return window.isOpen();
}
