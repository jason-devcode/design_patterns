#include <iostream>
#include <memory>
#include <stdexcept>


class NodeBehavior {
	public:
		NodeBehavior()=default;
		~NodeBehavior()=default;
		virtual void execute();
};

class Node : public NodeBehavior {};


int main() {

	return 0;
}


