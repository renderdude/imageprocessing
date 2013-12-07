#include "ImageBlockFileReader.h"
#include <pipeline/Value.h>

logger::LogChannel imageblockfilereaderlog("imageblockfilereaderlog",
										    "[ImageBlockFileReader] ");

ImageBlockFileReader::ImageBlockFileReader(std::string filename)
{
    _fileReader = boost::make_shared<ImageFileReader>(filename);
    //_imageCrop = boost::make_shared<ImageCrop>();
    //_imageCrop->setInput("image", _fileReader->getInput("image"));
}

void
ImageBlockFileReader::readImage()
{
	LOG_DEBUG(imageblockfilereaderlog) << "reading cropped image" << std::endl;
	
    pipeline::Value<Image> cropped;
    boost::shared_ptr<pipeline::Wrap<int> > x =
        boost::make_shared<pipeline::Wrap<int> >(_block->location().x);
    boost::shared_ptr<pipeline::Wrap<int> > y =
        boost::make_shared<pipeline::Wrap<int> >(_block->location().y);
    boost::shared_ptr<pipeline::Wrap<int> > w =
        boost::make_shared<pipeline::Wrap<int> >(_block->size().x);
    boost::shared_ptr<pipeline::Wrap<int> > h =
        boost::make_shared<pipeline::Wrap<int> >(_block->size().y);

	_imageCrop = boost::make_shared<ImageCrop>();
	LOG_DEBUG(imageblockfilereaderlog) << "Created ImageCrop, setting things up" << std::endl;
    _imageCrop->setInput("image", _fileReader->getOutput("image"));
    _imageCrop->setInput("x", x);
    _imageCrop->setInput("y", y);
    _imageCrop->setInput("width", w);
    _imageCrop->setInput("height", h);

	LOG_DEBUG(imageblockfilereaderlog) << "Getting cropped output" << std::endl;
    cropped = _imageCrop->getOutput("cropped image");
   
	LOG_DEBUG(imageblockfilereaderlog) << "Pointer magic" << std::endl;
    *_image = *cropped;
	LOG_DEBUG(imageblockfilereaderlog) << "done reading" << std::endl;
}

ImageBlockFileFactory::ImageBlockFileFactory(const std::string& directory)
{
	LOG_DEBUG(imageblockfilereaderlog) << "reading from directory " << directory << std::endl;
	
	boost::filesystem::path dir(directory);
	
	if (!boost::filesystem::exists(dir))
	{
		BOOST_THROW_EXCEPTION(IOError() << error_message(directory + " does not exist"));
	}
	
	if (!boost::filesystem::is_directory(dir))
	{
		BOOST_THROW_EXCEPTION(IOError() << error_message(directory + " is not a directory"));
	}
	
	std::copy(
			boost::filesystem::directory_iterator(dir),
			boost::filesystem::directory_iterator(),
			back_inserter(_sortedPaths));
	std::sort(_sortedPaths.begin(), _sortedPaths.end());
	
	LOG_DEBUG(imageblockfilereaderlog) << " directory contains " << _sortedPaths.size() << " files" << std::endl;
}

boost::shared_ptr<ImageBlockReader>
ImageBlockFileFactory::getReader(int n)
{
	LOG_DEBUG(imageblockfilereaderlog) << "For file " << n << " returning path " << _sortedPaths[n].string() << std::endl;
	return boost::make_shared<ImageBlockFileReader>(_sortedPaths[n].string());
}
