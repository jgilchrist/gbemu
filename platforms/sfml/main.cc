#include "../../src/gameboy_prelude.h"

#include <SFML/Graphics.hpp>
#include <optional>

static uint pixel_size = 5;

static uint width = GAMEBOY_WIDTH * pixel_size;
static uint height = GAMEBOY_HEIGHT * pixel_size;

static std::unique_ptr<sf::RenderWindow> window;
static sf::Image image;
static sf::Texture texture;
static sf::Sprite sprite;

static std::unique_ptr<Gameboy> gameboy;

static std::optional<GbButton> get_gb_button(int keyCode) {
    switch (keyCode) {
        case sf::Keyboard::Up: return GbButton::Up;
        case sf::Keyboard::Down: return GbButton::Down;
        case sf::Keyboard::Left: return GbButton::Left;
        case sf::Keyboard::Right: return GbButton::Right;
        case sf::Keyboard::X: return GbButton::A;
        case sf::Keyboard::Z: return GbButton::B;
        case sf::Keyboard::BackSpace: return GbButton::Select;
        case sf::Keyboard::Return: return GbButton::Start;
        default: return {};
    }
}

static sf::Color get_real_color(Color color) {
    switch (color) {
        case Color::White: return sf::Color(255, 255, 255);
        case Color::LightGray: return sf::Color(170, 170, 170);
        case Color::DarkGray: return sf::Color( 85,  85,  85);
        case Color::Black: return sf::Color(  0,   0,   0);
    }
}

static void set_large_pixel(uint x, uint y, sf::Color color) {
    for (uint w = 0; w < pixel_size; w++) {
        for (uint h = 0; h < pixel_size; h++) {
            image.setPixel(x * pixel_size + w, y * pixel_size + h, color);
        }
    }
}

static void set_pixels(const FrameBuffer& buffer) {
    for (uint y = 0; y < GAMEBOY_HEIGHT; y++) {
        for (uint x = 0; x < GAMEBOY_WIDTH; x++) {
            Color color = buffer.get_pixel(x, y);
            sf::Color pixel_color = get_real_color(color);

            set_large_pixel(x, y, pixel_color);
        }
    }
}

static void process_events() {
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (auto button = get_gb_button(event.key.code)) {
                gameboy->button_pressed(*button);
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            if (auto button = get_gb_button(event.key.code)) {
                gameboy->button_released(*button);
            }
        }

        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

static void draw(const FrameBuffer& buffer) {
    process_events();

    window->clear(sf::Color::White);

    set_pixels(buffer);
    texture.loadFromImage(image);
    sprite.setTexture(texture, true);

    window->draw(sprite);

    window->display();
}

static bool is_closed() {
    return !window->isOpen();
}

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);
    log_set_level(get_log_level(options));

    Cartridge cartridge(options.filename);
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Emulator", sf::Style::Titlebar | sf::Style::Close);

    image.create(width, height);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);

    gameboy = std::make_unique<Gameboy>(cartridge, options);

    gameboy->run(&is_closed, &draw);
    return 0;
}
