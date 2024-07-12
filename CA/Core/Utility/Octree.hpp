#pragma once
#include <glm/vec3.hpp>
#include <array>

class ONode
{
public:
	ONode();
	std::array<ONode*, 8> childern;
};

template <typename T>
class OLeaf : public ONode
{
public:
	OLeaf(T data) : data(data) {};
	T data;
};

template<typename T>
class OTree
{
public:
	OTree(glm::ivec3 origin, int depth);
	ONode* find(glm::ivec3 locPos);
	T* getData(glm::ivec3 locPos);
private:
	ONode* root;
	glm::ivec3 origin;
	int depth;
};

ONode::ONode()
{
	childern = std::array<ONode*, 8>{nullptr};
}

// Size of a voxel is 1/(2^depth)
// Each side consists of a maximum of 2*depth divisions
template<typename T>
inline OTree<T>::OTree(glm::ivec3 origin, int depth)
{
	this->origin = origin;
	this->depth = depth;

	if (depth == 0)
		throw "Depth cannot be 0";

	root = new ONode();
}

template<typename T>
inline ONode* OTree<T>::find(glm::ivec3 locPos)
{
	return nullptr;
}

template<typename T>
inline T* OTree<T>::getData(glm::ivec3 locPos)
{
	ONode* currentNode = this->root;
	int depth = 0;
}
