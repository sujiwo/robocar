/*
 * This class is a wrapper for Libjpeg to compress/decompress
 * in-memory image (no writing to file)
 */


#include <jpeglib.h>
#include <boost/shared_ptr.hpp>


class JpegCompress {

public:
	JpegCompress (int maximumSize);
	~JpegCompress ();

	void compress (const char *image, int width, int height, bool isColor=true);
	const uint8_t *data () { return store; }

private:
	uint8_t *store;
};


class JpegDecompress {
public:

	JpegDecompress ();
	~JpegDecompress ();

private:

};
