#ifndef IMAGE_BLOCK_FILE_READER_H__
#define IMAGE_BLOCK_FILE_READER_H__

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <imageprocessing/io/ImageBlockFactory.h>
#include <imageprocessing/io/ImageBlockReader.h>
#include <imageprocessing/ImageCrop.h>
#include <pipeline/all.h>

#include "ImageFileReader.h"

class ImageBlockFileReader : public ImageBlockReader
{
public:
    ImageBlockFileReader(const std::string filename);

protected:
    void readImage();
    
private:
    boost::shared_ptr<ImageFileReader> _fileReader;
    boost::shared_ptr<ImageCrop> _imageCrop;
};

class ImageBlockFileFactory : public ImageBlockFactory
{
public:
	ImageBlockFileFactory(const std::string& directory);
	boost::shared_ptr<ImageBlockReader> getReader(int n);
	
private:
	std::vector<boost::filesystem::path> _sortedPaths;
};

#endif //IMAGE_BLOCK_FILE_READER_H__