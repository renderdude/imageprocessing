#ifndef COMPONENT_TREES_H__
#define COMPONENT_TREES_H__

#include <boost/shared_ptr.hpp>
#include <map>
#include <pipeline/Data.h>
#include <imageprocessing/ComponentTree.h>

class ComponentTrees : public pipeline::Data
{
	typedef std::map<unsigned int, boost::shared_ptr<ComponentTree> > trees_type;
	
public:
	typedef trees_type::const_iterator const_iterator;
	typedef trees_type::iterator iterator;
	
	ComponentTrees();
	
	void setTree(unsigned int section,
				 const boost::shared_ptr<ComponentTree>& tree);
	
	void clear();
	
	/**
	 * Get a tree for a given section, if it exists.
	 */
	boost::shared_ptr<ComponentTree>& getTree(unsigned int section);
	
	/**
	 * Unlike getTree, the [] operator will create an empty ComponentTree
	 * for the given section if it does not already exist.
	 */
	boost::shared_ptr<ComponentTree> operator[] (unsigned int section);
	
	const const_iterator begin() const {return _treeSet.begin(); }
	const const_iterator end() const { return _treeSet.end(); }
	
	const iterator begin() { return _treeSet.begin(); }
	const iterator end() { return _treeSet.end(); }
	
	int size();
	
private:
	trees_type _treeSet;
	
};

#endif //COMPONENT_TREES_H__