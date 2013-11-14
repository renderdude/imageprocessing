#ifndef IMAGE_BLOCK_FACTORY_H__
#define IMAGE_BLOCK_FACTORY_H__

#include <imageprocessing/io/ImageBlockReader.h>
#include <boost/shared_ptr.hpp>

class ImageBlockFactory
{
public:
	virtual boost::shared_ptr<ImageBlockReader> getReader(int n) = 0;
};

#endif //IMAGE_BLOCK_FACTORY_H__