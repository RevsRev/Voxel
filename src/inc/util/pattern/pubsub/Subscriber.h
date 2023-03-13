#pragma once

template <typename V>
class Subscriber {
public:
	//TODO - arguments should be constant
	virtual void onCreate(V& val) = 0;
	virtual void onUpdate(V& val) = 0;
	virtual void onDelete(V& val) = 0;
};