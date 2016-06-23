This is a test for the 10 sprites-per-scanline limit of the Gameboy. This ROM relies heavily on STAT interrupts (OAM interrupts) as an early warning for the program to abort writing to VRAM before it becomes inaccessible and continue on the next VBlank. Basically the 11th sprite just scrolls vertically over an over again, and every time the Game Boy has to render a line with more than 10 sprites, the 11th sprite's lines disappear.

Credits:
Shonumi aka D.S. Baxter (https://github.com/shonumi)
