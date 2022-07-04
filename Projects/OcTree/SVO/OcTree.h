#pragma once
#include "Chunk.h"

namespace Chunk {
	template<class T>
	class OcTree : public Chunk<T>
	{
	public:
		OcTree(int depth)
			:
			root()
		{
			this->depth = depth;
			this->splitRec(this->root, this->depth);
		};

		inline int getDepth() { return this->depth; };
		inline int getWidth() override { return pow(2, this->depth); }

		inline bool isLeaf(Node<T>* node) const { return !(node->data == NULL); }

		virtual T& get(int posx, int posy, int posz) override {
			return this->getNode(posx, posy, posz, 0).data;
		};
		virtual void set(T value, int posx, int posy, int posz) override {
			this->setNode(value, posx, posy, posz, 0);
		};

		
	private:
		Node<T> root;
		int depth;

		void split(Node<T>& node, int depth) {
			if (depth > 0) {
				Node<T>* nodeChilds = new Node<T>[8];
				this->split(nodeChilds[0], depth - 1);
				this->split(nodeChilds[1], depth - 1);
				this->split(nodeChilds[2], depth - 1);
				this->split(nodeChilds[3], depth - 1);
				this->split(nodeChilds[4], depth - 1);
				this->split(nodeChilds[5], depth - 1);
				this->split(nodeChilds[6], depth - 1);
				this->split(nodeChilds[7], depth - 1);
			}
		}

		void setNode(T value, uint_fast16_t posx, uint_fast16_t posy, uint_fast16_t posz, int depthSeek)
		{
			uint_fast32_t mortonCode = morton3D_32_encode(this->getWidth() - posx, posy, posz);

			int depth = this->depth;
			Node<T>* node = &this->root;
			while (depth > depthSeek)
			{
				depth--;
				node = &(*node).childs[(mortonCode >> 3 * depth) & 7];
			}
			node->data = value;
		}

		Node<T>& getNode(uint_fast16_t posx, uint_fast16_t posy, uint_fast16_t posz, int depthSeek)
		{
			uint_fast32_t mortonCode = morton3D_32_encode(this->getWidth() - posx, posy, posz);

			int depth = this->depth;
			Node<T>* node = &this->root;
			while (depth > depthSeek)
			{
				depth--;
				node = &(*node).childs[(mortonCode >> 3 * depth) & 7];
			}
			return (*node);
		}
	};
} 