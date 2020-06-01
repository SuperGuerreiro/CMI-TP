#pragma once

#include "ScreenElement.hpp"

class Group : public ScreenElement
{
public:
	Group();
	~Group();

	void update() override;
	void draw() override;
	void draw(int xOffset, int yOffset, int width, int height) override;

	void setOffset(int xOffset, int yOffset) override;
	void setSize(int width, int height) override;
	void setFillMode(bool fill) override;

	bool onClick(int x, int y, int button) override;

	const inline ElementType getType() const override { return ElementType::Group; };
	const inline std::string getName() const override { return ""; };

	inline void add(ScreenElement* e) { elements.push_back(e); };
	inline void clear()
	{
		for each (ScreenElement* e in elements)
		{
			delete e;
		}
		elements.clear();
	};
	inline ScreenElement* operator[](int i) const { return elements[i]; };
	inline int getNumElements() { return elements.size(); };

private:
	std::vector<ScreenElement*> elements;
};