#include "../../src/gameboy_prelude.h"

#include <SFML/Graphics.hpp>

static uint pixel_size = 5;

static uint width = GAMEBOY_WIDTH * pixel_size;
static uint height = GAMEBOY_HEIGHT * pixel_size;

static std::unique_ptr<sf::RenderWindow> window;
static sf::Image image;
static sf::Texture texture;
static sf::Sprite sprite;

static std::unique_ptr<Gameboy> gameboy;

static bool should_exit = false;

static bool get_gb_button(int keyCode, GbButton& button) {
    switch (keyCode) {
        case sf::Keyboard::Up: button = GbButton::Up; break;
        case sf::Keyboard::Down: button = GbButton::Down; break;
        case sf::Keyboard::Left: button = GbButton::Left; break;
        case sf::Keyboard::Right: button = GbButton::Right; break;
        case sf::Keyboard::X: button = GbButton::A; break;
        case sf::Keyboard::Z: button = GbButton::B; break;
        case sf::Keyboard::BackSpace: button = GbButton::Select; break;
        case sf::Keyboard::Return: button = GbButton::Start; break;
        case sf::Keyboard::Escape: should_exit = true; return false;
        case sf::Keyboard::B: gameboy->debug_toggle_background(); return false;
        case sf::Keyboard::S: gameboy->debug_toggle_sprites(); return false;
        case sf::Keyboard::W: gameboy->debug_toggle_window(); return false;
        default: return false;
    }

    return true;
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
            GbButton button;

            auto relevant_button = get_gb_button(event.key.code, button);
            if (relevant_button) {
                gameboy->button_pressed(button);
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            GbButton button;

            auto relevant_button = get_gb_button(event.key.code, button);
            if (relevant_button) {
                gameboy->button_released(button);
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
    return !window->isOpen() || should_exit;
}

int main(int argc, char* argv[]) {
    Options options = get_options(argc, argv);

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Emulator", sf::Style::Titlebar | sf::Style::Close);
    image.create(width, height);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);
    window->display();

    auto rom_data = read_bytes(options.filename);
    gameboy = std::make_unique<Gameboy>(rom_data, options);
    gameboy->run(&is_closed, &draw);
    return 0;
}
