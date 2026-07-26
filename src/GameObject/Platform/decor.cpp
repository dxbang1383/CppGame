#include "decor.h"

decor::decor(double x, double y, double width, double height) :
	platform(x, y, width, height)
{

}

decor::decor(int m, int n, std::string t) :
	platform(m, n, t)
{

}

decor::decor(int m, int n, std::string t, int srcX, int srcY) :
	platform(m, n, t, srcX, srcY)
{

}

decor::decor(int m, int n, std::string t, int srcX, int srcY, std::string typeAni) :
	platform(m, n, t, srcX, srcY, typeAni)
{

}
