#pragma once

// Contains child pointers
namespace Chunk {

	template<class T>
	class Node
	{
		template<typename U>
		friend class OcTree;
	public:
		Node(const T& value)
		{
			this->childs = nullptr;
			this->data = value;
		}
		Node()
		{
			this->childs = nullptr;
			this->data = {};
		}

		~Node() {
			if(this->childs != nullptr) {
				delete[] this->childs;
			}
		}

		void reduce(){
			if(needReduce()){
				this->data = this->childs[0].data;
				delete[] this->childs;
				this->childs = nullptr;
			}
		}

		bool needReduce(){
			if(this->childs == nullptr) {
				return false;
			}
			else {
				return  this->childs[0].data == this->childs[1].data &&
						this->childs[0].data == this->childs[2].data &&
						this->childs[0].data == this->childs[3].data &&
						this->childs[0].data == this->childs[4].data &&
						this->childs[0].data == this->childs[5].data &&
						this->childs[0].data == this->childs[6].data &&
						this->childs[0].data == this->childs[7].data;
			}
		}

		void split(){
			childs = new Node<T>[8];
			this->childs[0].data = this->data;
			this->childs[1].data = this->data;
			this->childs[2].data = this->data;
			this->childs[3].data = this->data; 
			this->childs[4].data = this->data; 
			this->childs[5].data = this->data; 
			this->childs[6].data = this->data; 
			this->childs[7].data = this->data; 
		}
		
		const T& get(){
			return data;
		}

		void set(){
			return data;
		}

		Node<T>* childs(){
			return childs;
		}
	
	private:
		T data;
		Node<T>* childs;
	};
}