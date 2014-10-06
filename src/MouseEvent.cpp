#include "MouseEvent.h"
// const std::string MouseEvent::MOUSE_MOVE = "MOUSE_MOVE";
// const std::string MouseEvent::MOUSE_CLICK = "MOUSE_CLICK";
const std::string MouseEvent::MOUSE_MOVE("MOUSE_MOVE");
const std::string MouseEvent::MOUSE_DOWN("MOUSE_DOWN");
const std::string MouseEvent::MOUSE_UP("MOUSE_UP");
const std::string MouseEvent::MOUSE_HOVER("MOUSE_HOVER");
const std::string MouseEvent::MOUSE_LOSE_HOVER("MOUSE_LOSE_HOVER");

MouseEvent::MouseEvent(const std::string& type, const int mouseX, const int mouseY)
	: Event(type)
	, mouseX_(mouseX)
	, mouseY_(mouseY)
{
	
}
