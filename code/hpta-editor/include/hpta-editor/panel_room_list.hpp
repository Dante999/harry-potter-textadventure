#ifndef PANEL_ROOM_SELECTOR_HPP
#define PANEL_ROOM_SELECTOR_HPP

#include <string>

#include "hpta-editor/ipanel.hpp"
#include "hpta-editor/object_cache.hpp"

class Panel_room_list : public IPanel {

  private:
	Room_cache &m_room_cache;
	float       m_scale_factor;

  public:
	Panel_room_list(Room_cache &room_cache) : m_room_cache{room_cache}
	{
		m_scale_factor = Hpta_config::get_float(Settings::scale_factor);
	}

	void refresh() override;
};
#endif // PANEL_ROOM_SELECTOR_HPP
