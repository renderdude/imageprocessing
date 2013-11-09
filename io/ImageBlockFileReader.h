#ifndef IMAGE_BLOCK_FILE_READER_H__
#define IMAGE_BLOCK_FILE_READER_H__

#include "ImageFileReader.h"
#include "ImageBlockReader.h"
#include <boost/shared_ptr.hpp>
#include <imageprocessing/ImageCrop.h>

class ImageBlockFileReader : public ImageBlockReader
{
public:
    ImageBlockFileReader(std::string filename, unsigned int n);

protected:
    void readImage();
    
private:
    boost::shared_ptr<ImageFileReader> _fileReader;
    boost::shared_ptr<ImageCrop> _imageCrop;
};


#endif //IMAGE_BLOCK_FILE_READER_H__