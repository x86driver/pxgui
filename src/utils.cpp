#include <SDL.h>

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;

   default:
        break;           /* shouldn't happen, but avoids warnings */
    } // switch
}

/*
 * Read sysfs from path to result
 * Max data: 64 bytes
 * return: 0 -> OK, otherwise -> fail
 */
#include <string.h>
int read_sysfs(const char *path, char result[64])
{
    FILE *fp = fopen(path, "r");
    if (!fp)
        return -1;

    fread(&result[0], 64, 1, fp);
    fclose(fp);

    return 0;
}

/*
 * Write sysfs
 * Max data: written until the end of data ('\0')
 * return: 0 -> OK, otherwise -> fail
 */
int write_sysfs(const char *path, const char *data)
{
    FILE *fp = fopen(path, "w");
    if (!fp)
        return -1;

    fwrite(data, strlen(data), 1, fp);
    fclose(fp);

    return 0;
}
