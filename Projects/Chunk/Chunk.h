#pragma once
#include <cmath>

namespace Chunk {
	template <class T>
	class Chunk
	{
	public:
		// get value at given position
		virtual const T& get(int posx, int posy, int posz) = 0;
		// set value at given position
		virtual void set(T value, int posx, int posy, int posz) = 0;

		//get Dimention of chunck (is square shapped)
 		virtual int getDimention() = 0;
	};
}