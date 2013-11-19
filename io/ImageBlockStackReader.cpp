#include <imageprocessing/Image.h>
#include <imageprocessing/ImageStack.h>
#include <imageprocessing/io/ImageBlockFileReader.h>
#include "ImageBlockStackReader.h"

logger::LogChannel imageblockstackreaderlog("imageblockstackreaderlog", "[ImageBlockStackReader] ");

ImageBlockStackReader::ImageBlockStackReader()
{	
	_stackAssembler = boost::make_shared<StackAssembler>();
	registerInput(_block, "block");
	registerInput(_blockFactory, "factory");
	
	_block.registerBackwardCallback(&ImageBlockStackReader::onBlockModified, this);

	// expose the result of the stack assembler
	registerOutput(_stackAssembler->getOutput(), "stack");
}

/*void
ImageBlockStackReader::updateOutputs()
{
	LOG_DEBUG(imageblockstackreaderlog) << "Updating outputs" << std::endl; 
	
}*/


ImageBlockStackReader::StackAssembler::StackAssembler() {

	registerInputs(_images, "images");
	registerOutput(_stack, "stack");
}

void
ImageBlockStackReader::StackAssembler::updateOutputs() {

	LOG_DEBUG(imageblockstackreaderlog) << "Stack Assembler updating outputs" << std::endl;
	_stack->clear();

	foreach (boost::shared_ptr<Image> image, _images)
		_stack->add(image);
}

void
ImageBlockStackReader::onBlockModified(const pipeline::Modified&)
{
	LOG_DEBUG(imageblockstackreaderlog) << "Got block modified" << std::endl;
	int minZ = _block->location()->z;
	int maxZ = minZ + _block->size()->z;
	LOG_DEBUG(imageblockstackreaderlog) << "Clear readers" << std::endl;
	_blockReaders.clear();
	LOG_DEBUG(imageblockstackreaderlog) << "Clear stack assembler inputs" << std::endl; 
	_stackAssembler->clearInputs(0);
	for (unsigned int z = minZ; z < maxZ; ++z)
	{
		LOG_DEBUG(imageblockstackreaderlog) << "Adding input for z " << z << std::endl; 
		boost::shared_ptr<pipeline::Wrap<unsigned int> > wrapZ = 
			boost::make_shared<pipeline::Wrap<unsigned int> >(z);
		boost::shared_ptr<ImageBlockReader> reader = _blockFactory->getReader(z);
		_blockReaders.push_back(reader);
		reader->setInput("block", _block);
		
		reader->setInput("section", wrapZ);
		_stackAssembler->addInput(reader->getOutput("image"));
	}	
}
