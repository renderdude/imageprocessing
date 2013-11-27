#include <imageprocessing/Image.h>
#include <imageprocessing/ImageStack.h>
#include <imageprocessing/io/ImageBlockFileReader.h>
#include "ImageBlockStackReader.h"

logger::LogChannel imageblockstackreaderlog("imageblockstackreaderlog", "[ImageBlockStackReader] ");

ImageBlockStackReader::ImageBlockStackReader()
{
	registerInput(_block, "block");
	registerInput(_blockFactory, "factory");
	
	registerInputs(_images, "images");
	registerOutput(_stack, "stack");

	
	_block.registerBackwardCallback(&ImageBlockStackReader::onBlockModified, this);
	_blockFactory.registerBackwardCallback(&ImageBlockStackReader::onFactoryModified, this);

	// expose the result of the stack assembler
	registerOutput(_stack, "stack");
	LOG_DEBUG(imageblockstackreaderlog) << "Created an ImageBlockStackReader" << std::endl;
}

/*void
ImageBlockStackReader::updateOutputs()
{
	LOG_DEBUG(imageblockstackreaderlog) << "Updating outputs" << std::endl; 
	
}*/


void
ImageBlockStackReader::onFactoryModified(const pipeline::Modified& )
{
	setup();
}

void
ImageBlockStackReader::onBlockModified(const pipeline::Modified&)
{
	setup();
}

void
ImageBlockStackReader::updateOutputs()
{
	LOG_DEBUG(imageblockstackreaderlog) << "Updating outputs" << std::endl;
	_stack->clear();

	foreach (boost::shared_ptr<Image> image, _images)
	{
		_stack->add(image);
	}
}


void
ImageBlockStackReader::setup()
{

	if (_block && _blockFactory)
	{
		LOG_DEBUG(imageblockstackreaderlog) << "Got input modified" << std::endl;
		
		int minZ = _block->location()->z;
		int maxZ = minZ + _block->size()->z;
		LOG_DEBUG(imageblockstackreaderlog) << "Clear readers" << std::endl;
		_blockReaders.clear();
		LOG_DEBUG(imageblockstackreaderlog) << "Clear stack assembler inputs" << std::endl; 
		//_stackAssembler->clearInputs(0);
		for (unsigned int z = minZ; z < maxZ; ++z)
		{
			LOG_DEBUG(imageblockstackreaderlog) << "Adding input for z " << z << std::endl; 
			boost::shared_ptr<pipeline::Wrap<unsigned int> > wrapZ = 
				boost::make_shared<pipeline::Wrap<unsigned int> >(z);
			boost::shared_ptr<ImageBlockReader> reader = _blockFactory->getReader(z);
			_blockReaders.push_back(reader);
			reader->setInput("block", _block);
			
			reader->setInput("section", wrapZ);
			addInput("images", reader->getOutput("image"));
		}
		
		//updateOutputs();
		
	}
	else
	{
		LOG_DEBUG(imageblockstackreaderlog) << "Got input modified, but inputs aren't ready." << std::endl;
	}
}
