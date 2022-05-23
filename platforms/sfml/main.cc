#include "../../src/gameboy_prelude.h"
#include "../cli/cli.h"

#include <SFML/Graphics.hpp>

#include <fstream>
#include <iterator>

static uint pixel_size = 5;

static uint width = GAMEBOY_WIDTH * pixel_size;
static uint height = GAMEBOY_HEIGHT * pixel_size;

static std::unique_ptr<sf::RenderWindow> window;
static sf::Image image;
static sf::Texture texture;
static sf::Sprite sprite;

static std::unique_ptr<Gameboy> gameboy;

static CliOptions cliOptions;

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

static std::string get_save_filename() {
    return cliOptions.filename + ".sav";
}

static bool file_exists(const std::string& filename) {
    std::ifstream f(filename.c_str());
    return f.good();
}

static void save_state() {
    auto cartridge_ram = gameboy->get_cartridge_ram();

    // Don't save empty cartridge RAM
    if (cartridge_ram.size() == 0) { return; }

    auto filename = get_save_filename();
    std::ofstream output_file(filename);
    std::copy(cartridge_ram.begin(), cartridge_ram.end(), std::ostreambuf_iterator<char>(output_file));
    log_info("Wrote %d KB to %s", cartridge_ram.size() / 1024, filename.c_str());
}

static std::vector<u8> load_state() {
    auto filename = get_save_filename();
    if (!file_exists(filename)) {
        return {};
    } else {
        auto save_data = read_bytes(filename);
        log_info("Read %d KB from %s", save_data.size() / 1024, filename.c_str());
        return save_data;
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
            save_state();
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
    cliOptions = get_cli_options(argc, argv);

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "gbemu", sf::Style::Titlebar | sf::Style::Close);
    image.create(width, height);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);
    window->display();

    auto rom_data = read_bytes(cliOptions.filename);
    log_info("Read %d KB from %s", rom_data.size() / 1024, cliOptions.filename.c_str());

    auto save_data = load_state();
    log_info("");

    gameboy = std::make_unique<Gameboy>(rom_data, cliOptions.options, save_data);
    gameboy->run(&is_closed, &draw);
    return 0;
}
