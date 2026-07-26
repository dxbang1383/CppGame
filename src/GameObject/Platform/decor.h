#ifndef DECOR_H
#define DECOR_H

#include "platform.h"

class decor : public platform {
private :

public :
	decor(double x, double y, double width, double height);
	decor(int m, int n, std::string t);
	decor(int m, int n, std::string t, int srcX, int srcY);
	decor(int m, int n, std::string t, int srcX, int srcY, std::string typeAni);
};

#endif // !DECOR_H
