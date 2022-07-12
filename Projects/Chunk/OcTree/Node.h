#pragma once

// Contains child pointers
namespace Chunk {

	template<class T>
	class Node
	{
	public:
		Node()
		{
			this->childs = nullptr;
			this->data = {};
		}
	public:
		T data;
		Node<T>* childs;
	};
}