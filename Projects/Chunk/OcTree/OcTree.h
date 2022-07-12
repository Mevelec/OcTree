#pragma once
#include "Chunk.h"
#include "Node.h"
#include <libmorton/morton.h>
#include <assert.h>     /* assert */

namespace Chunk {
	template<class T>
	class OcTree : public Chunk<T>
	{
	public:
		OcTree(int depth, const T& default_v)
			:
			root()
		{
			this->depth = depth;
			this->root.data = default_v;
		};
		OcTree(int depth)
			:
			root()
		{
			this->depth = depth;
		};

		inline int getDepth() { return this->depth; };
		inline int getDimention() override { return pow(2, this->depth); }


		virtual T& get(int x, int y, int z) override {
			assert( x >= 0 && x < this->getDimention() );
			assert( y >= 0 && y < this->getDimention() );
			assert( z >= 0 && z < this->getDimention() );

			return this->getNode(x, y, z, 0).data;
		};
		virtual void set(T value, int x, int y, int z) override {
			assert( x >= 0 && x < this->getDimention() );
			assert( y >= 0 && y < this->getDimention() );
			assert( z >= 0 && z < this->getDimention() );

			this->setNode(value, x, y, z, 0);
		};

		
	private:
		Node<T> root;
		int depth;

		void split(Node<T>& node) {
			node.split();
		}

		void setNode(T value, uint_fast16_t x, uint_fast16_t y, uint_fast16_t z, int depthSeek)
		{
			uint_fast32_t mortonCode = libmorton::morton3D_32_encode(this->getDimention() - x, y, z);

			int depth = this->depth;
			Node<T>* node = &this->root;
			while (depth > depthSeek && !(node->childs == nullptr && node->data == value) )
			{
				if(node->childs == nullptr){
					split(*node);
				}
				depth--;
				node = &(*node).childs[(mortonCode >> 3 * depth) & 7];
			}
			node->data = value;
		}

		Node<T>& getNode(uint_fast16_t x, uint_fast16_t y, uint_fast16_t z, int depthSeek)
		{
			uint_fast32_t mortonCode = libmorton::morton3D_32_encode(this->getDimention() - x, y, z);

			int depth = this->depth;
			Node<T>* node = &this->root;
			while (depth > depthSeek && node->childs != nullptr)
			{
				depth--;
				node = &(*node).childs[(mortonCode >> 3 * depth) & 7];

			}
			return (*node);
		}
	};
} 