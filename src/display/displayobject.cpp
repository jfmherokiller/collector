

#include <SDL.h>

#include <collector.h>
#include <filestore/selection.h>
#include <display/displayobject.h>



DisplayObject::DisplayObject(Selection** _s)
{
	s = _s;
}


bool DisplayObject::on_key(SDL_KeyboardEvent &e)
{
	return false;
}

bool DisplayObject::on_text(SDL_TextInputEvent &e)
{
	return false;
}

bool DisplayObject::on_wheel(SDL_MouseWheelEvent &e)
{
	offset.y -= (e.y * config->scroll_speed);
	limit_scroll();
	return false;
}

bool DisplayObject::on_motion(SDL_MouseMotionEvent &e)
{
	return false;
}


/*
	Optional tools for scrolling and centering
*/

void DisplayObject::pageup()
{
	offset.y -= WINDOW_H;
	limit_scroll();
}

void DisplayObject::pagedown()
{
	offset.y += WINDOW_H;
	limit_scroll();
}

bool DisplayObject::is_dirty()
{
	bool state = dirty;
	dirty = false;
	return state;
}

void DisplayObject::set_centered_width(int w)
{
	offset.x = (WINDOW_W - w) / 2;
}

void DisplayObject::set_scroll_range(size_t s)
{
	//account for the two UI bars at the top and bottom
	scroll_range = s + (2 * CLI_H);
	limit_scroll();
}

void DisplayObject::limit_scroll()
{
	int max_scroll = scroll_range - WINDOW_H;

	if(max_scroll < 0) max_scroll = 0;

	if(offset.y < 0) offset.y = 0;
	else if(offset.y > max_scroll) offset.y = max_scroll;
}
