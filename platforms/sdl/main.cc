#include "../../src/gameboy_prelude.h"
#include "../cli/cli.h"

#include <SDL.h>

#include <fstream>
#include <iterator>

static uint pixel_size = 2;

static uint width = GAMEBOY_WIDTH * pixel_size;
static uint height = GAMEBOY_HEIGHT * pixel_size;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* gb_screen_texture;

static std::unique_ptr<Gameboy> gameboy;

static CliOptions cliOptions;

static bool should_exit = false;

static std::unique_ptr<GbButton> get_gb_button(int keyCode) {
    switch (keyCode) {
        case SDLK_UP: return std::make_unique<GbButton>(GbButton::Up);
        case SDLK_DOWN: return std::make_unique<GbButton>(GbButton::Down);
        case SDLK_LEFT: return std::make_unique<GbButton>(GbButton::Left);
        case SDLK_RIGHT: return std::make_unique<GbButton>(GbButton::Right);
        case SDLK_x: return std::make_unique<GbButton>(GbButton::A);
        case SDLK_z: return std::make_unique<GbButton>(GbButton::B);
        case SDLK_BACKSPACE: return std::make_unique<GbButton>(GbButton::Select);
        case SDLK_RETURN: return std::make_unique<GbButton>(GbButton::Start);
        case SDLK_b: gameboy->debug_toggle_background(); return nullptr;
        case SDLK_s: gameboy->debug_toggle_sprites(); return nullptr;
        case SDLK_w: gameboy->debug_toggle_window(); return nullptr;
        default: return nullptr;
    }
}

static uint32_t get_real_color(Color color) {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    switch (color) {
        case Color::White: r = g = b = 255; break;
        case Color::LightGray: r = g = b = 170; break;
        case Color::DarkGray: r = g = b = 85; break;
        case Color::Black: r = g = b = 0; break;
    }

    return (r << 16) | (g << 8) | (b << 0);
}

static void set_pixel(uint32_t* pixels, uint x, uint y, uint32_t pixel_argb) {
    pixels[width * y + x] = pixel_argb;
}

static void set_large_pixel(uint32_t* pixels, uint x, uint y, uint32_t pixel_argb) {
    for (uint w = 0; w < pixel_size; w++) {
        for (uint h = 0; h < pixel_size; h++) {
            set_pixel(pixels, x * pixel_size + w, y * pixel_size + h, pixel_argb);
        }
    }
}

static void set_pixels(uint32_t* pixels, const FrameBuffer& buffer) {
    for (uint y = 0; y < GAMEBOY_HEIGHT; y++) {
        for (uint x = 0; x < GAMEBOY_WIDTH; x++) {
            Color color = buffer.get_pixel(x, y);
            uint32_t pixel_argb = get_real_color(color);
            set_large_pixel(pixels, x, y, pixel_argb);
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
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.repeat == true) { break; }
                if (auto button_pressed = get_gb_button(event.key.keysym.sym); button_pressed != nullptr) {
                    gameboy->button_pressed(*button_pressed);
                }
                break;
            case SDL_KEYUP:
                if (event.key.repeat == true) { break; }
                if (auto button_released = get_gb_button(event.key.keysym.sym); button_released != nullptr) {
                    gameboy->button_released(*button_released);
                }
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    should_exit = true;
                }
                break;
            case SDL_QUIT:
                should_exit = true;
                break;
        }
    }
}

template <typename TPixels, typename Proc>
static void draw_with_pixels(Proc set_pixels_proc, TPixels buffer) {
    process_events();

    SDL_RenderClear(renderer);

    void* pixels_ptr;
    int pitch;
    SDL_LockTexture(gb_screen_texture, nullptr, &pixels_ptr, &pitch);

    uint32_t* pixels = static_cast<uint32_t*>(pixels_ptr);
    set_pixels_proc(pixels, buffer);
    SDL_UnlockTexture(gb_screen_texture);

    SDL_RenderCopy(renderer, gb_screen_texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

static void draw_dmg(const FrameBuffer& buffer) {
    draw_with_pixels(set_pixels, buffer);
}

static void draw_gbc(const FrameBuffer& buffer) {
    draw_with_pixels(set_pixels, buffer);
}

static bool is_closed() {
    return should_exit;
}

int main(int argc, char* argv[]) {
    cliOptions = get_cli_options(argc, argv);

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "gbemu",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    if (window == nullptr) {
        fatal_error("Failed to initialise SDL");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    gb_screen_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        width, height
    );

    auto rom_data = read_bytes(cliOptions.filename);
    log_info("Read %d KB from %s", rom_data.size() / 1024, cliOptions.filename.c_str());

    auto save_data = load_state();
    log_info("");

    gameboy = std::make_unique<Gameboy>(rom_data, cliOptions.options, save_data);
    gameboy->run(&is_closed, &draw_dmg, &draw_gbc);

    save_state();
    SDL_DestroyTexture(gb_screen_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
