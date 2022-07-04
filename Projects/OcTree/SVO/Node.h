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
		}
	public:
		T data;
		Node<T>* childs;
	};
}