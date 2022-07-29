#pragma once

// Contains child pointers
namespace DataStructs {

	template<class T>
	class Node
	{
		template<typename U>
		friend class OcTree;
	public:
		Node(const T& value)
		{
			this->_childs = nullptr;
			this->_data = value;
		}
		Node()
		{
			this->_childs = nullptr;
			this->_data = {};
		}

		~Node() {
			if(this->_childs != nullptr) {
				delete[] this->_childs;
			}
		}

		void reduce(){
			if(needReduce()){
				this->_data = this->_childs[0]._data;
				delete[] this->_childs;
				this->_childs = nullptr;
			}
		}

		bool needReduce(){
			if(this->_childs == nullptr) {
				return false;
			}
			else {
				return  this->_childs[0]._data == this->_childs[1]._data &&
						this->_childs[0]._data == this->_childs[2]._data &&
						this->_childs[0]._data == this->_childs[3]._data &&
						this->_childs[0]._data == this->_childs[4]._data &&
						this->_childs[0]._data == this->_childs[5]._data &&
						this->_childs[0]._data == this->_childs[6]._data &&
						this->_childs[0]._data == this->_childs[7]._data;
			}
		}

		void split(){
			_childs = new Node<T>[8];
			this->_childs[0]._data = this->_data;
			this->_childs[1]._data = this->_data;
			this->_childs[2]._data = this->_data;
			this->_childs[3]._data = this->_data; 
			this->_childs[4]._data = this->_data; 
			this->_childs[5]._data = this->_data; 
			this->_childs[6]._data = this->_data; 
			this->_childs[7]._data = this->_data; 
		}
		
		const T& data(){
			return _data;
		}

		void set(const T& v){
			_data = v;
		}

		Node<T>* childs(){
			return _childs;
		}
	
	private:
		T _data;
		Node<T>* _childs;
	};
}