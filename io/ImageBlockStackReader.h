#ifndef IMAGE_BLOCK_STACK_READER_H__
#define IMAGE_BLOCK_STACK_READER_H__

#include <string>

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

#include <pipeline/all.h>
#include <imageprocessing/Image.h>
#include <imageprocessing/ImageStack.h>
#include <sopnet/sopnet/block/Block.h>
#include <imageprocessing/io/ImageBlockFactory.h>

class ImageBlockStackReader : public pipeline::SimpleProcessNode<>
{
public:
	ImageBlockStackReader();
	
private:
	
	void onBlockModified(const pipeline::Modified&);
	
	void onFactoryModified(const pipeline::Modified&);

	void setup();
	
	void updateOutputs();
	
	std::vector<boost::shared_ptr<ImageBlockReader> > _blockReaders;
	
	pipeline::Inputs<Image> _images;
	pipeline::Input<Block> _block;
	pipeline::Input<ImageBlockFactory> _blockFactory;
	
	pipeline::Output<ImageStack> _stack;
};

#endif //IMAGE_BLOCK_STACK_READER_H__