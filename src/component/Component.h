#ifndef CGPROJECT_COMPONENT_H
#define CGPROJECT_COMPONENT_H

class Component {
public:
	virtual void render() = 0;

	virtual ~Component() = default;

};

#endif //CGPROJECT_COMPONENT_H
