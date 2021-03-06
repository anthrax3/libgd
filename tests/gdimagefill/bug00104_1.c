/* test case for outside of buffer reads/write bug in _gdImageFillTiled */
#include "gd.h"
#include <stdio.h>
#include "gdtest.h"

int main()
{
	gdImagePtr im, tile;
	int im_white, tile_red, tile_blue;
	int x, y, error = 0;
	char path[1024];
	
	im = gdImageCreate(200, 150);

	tile = gdImageCreateTrueColor(2, 2);
	
	tile_red = gdImageColorAllocate(tile, 255, 0, 0);
	tile_blue = gdImageColorAllocate(tile, 0, 0, 255);
	
	gdImageSetPixel(tile, 0, 0, tile_red);
	gdImageSetPixel(tile, 1, 1, tile_red);
	gdImageSetPixel(tile, 1, 0, tile_blue);
	gdImageSetPixel(tile, 0, 1, tile_blue);
	
	gdImageSetTile(im, tile);
	gdImageFill(im, 11, 12, gdTiled);

	sprintf(path, "%s/gdimagefill/bug00104_1_exp.png", GDTEST_TOP_DIR);
	if (!gdAssertImageEqualsToFile(path, im)) {
		error = 1;
	}
	
	gdImageDestroy(im);
	return error;
}