#include "ComponentTrees.h"

ComponentTrees::ComponentTrees()
{

}

boost::shared_ptr<ComponentTree>&
ComponentTrees::getTree(unsigned int section)
{
	return _treeSet[section];
}

void
ComponentTrees::setTree(unsigned int section,
						 const boost::shared_ptr<ComponentTree>& tree)
{
	_treeSet[section] = tree;
}

void
ComponentTrees::clear()
{
	_treeSet.clear();
}

boost::shared_ptr<ComponentTree>
ComponentTrees::operator[](unsigned int section)
{
	if (_treeSet.count(section))
	{
		return getTree(section);
	}
	else
	{
		boost::shared_ptr<ComponentTree> tree = boost::make_shared<ComponentTree>();
		_treeSet[section] = tree;
		return tree;
	}
}

int ComponentTrees::size()
{
	return _treeSet.size();
}
