#ifndef IMAGE_BLOCK_STACK_READER_H__
#define IMAGE_BLOCK_STACK_READER_H__

#include <string>

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

#include <pipeline/all.h>
#include <imageprocessing/Image.h>
#include <imageprocessing/ImageStack.h>
#include <catmaidsopnet/Block.h>
#include <imageprocessing/io/ImageBlockFactory.h>

class ImageBlockStackReader : public pipeline::ProcessNode
{
public:
	ImageBlockStackReader(ImageBlockFactory *blockFactory);
	
private:
	//Like in ImageStackDirectoryReader
	class StackAssembler : public pipeline::SimpleProcessNode<>
	{

	public:

		StackAssembler();

	private:

		void updateOutputs();

		pipeline::Inputs<Image> _images;

		pipeline::Output<ImageStack> _stack;
	};

	//void updateOutputs();
	
	void onBlockModified(const pipeline::Modified&);

	std::vector<boost::shared_ptr<ImageBlockReader> > _blockReaders;
	
	boost::shared_ptr<StackAssembler> _stackAssembler;
	
	pipeline::Input<Block> _block;
	
	ImageBlockFactory *_blockFactory;
};

#endif //IMAGE_BLOCK_STACK_READER_H__