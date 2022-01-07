#ifndef PANEL_ITEM_LIST_HPP
#define PANEL_ITEM_LIST_HPP

#include <string>

#include "hpta-editor/ipanel.hpp"
#include "hpta-editor/object_cache.hpp"

class Panel_item_list : public IPanel {
  private:
	Item_cache &m_item_cache;
	float       m_scale_factor;

  public:
	Panel_item_list(Item_cache &item_cache) : m_item_cache{item_cache}
	{
		m_scale_factor = Hpta_config::get_float(Settings::scale_factor);
	}

	void refresh() override;
};

#endif // PANEL_ITEM_LIST_HPP
