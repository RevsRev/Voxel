#pragma once

#include <vector>
#include <algorithm>
#include <util/pattern/pubsub/Subscriber.h>

template <typename V>
class Publisher {
private:
	std::vector<Subscriber<V>*> subscribers{};

protected:
	void publishCreate(V& val) {
		for (int i = 0; i < subscribers.size(); i++) {
			subscribers.at(i)->onCreate(val);
		}
	}
	void publishUpdate(V& val) {
		for (int i = 0; i < subscribers.size(); i++) {
			subscribers.at(i)->onUpdate(val);
		}

	}
	void publishDelete(V& val) {
		for (int i = 0; i < subscribers.size(); i++) {
			subscribers.at(i)->onDelete(val);
		}
	}

public:
	void addSubscriber(Subscriber<V>* sub) {
		subscribers.push_back(sub);
	}
	void removeSubscriber(Subscriber<V>* sub) {
		//TODO - Implement
		/*std::vector<Subscriber<V>>::iterator position = std::find(subscribers.begin(), subscribers.end(), sub);
		if (position != subscribers.end()) {
			subscribers.erase(position);
		}*/
	}
};