#ifndef IMAGE_BLOCK_READER_H__
#define IMAGE_BLOCK_READER_H__

#include "ImageReader.h"
#include <catmaidsopnet/Block.h>
#include <pipeline/all.h>

class ImageBlockReader : public ImageReader {

protected:
    ImageBlockReader();

    pipeline::Input<Block> _block;

	pipeline::Input<unsigned int> _sectionId;
    //unsigned int _sectionId;

};

#endif //IMAGE_BLOCK_READER_H__
