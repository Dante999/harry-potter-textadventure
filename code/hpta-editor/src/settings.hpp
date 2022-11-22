#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <map>
#include <string>

#include "hpta-lib/util/hpta_config.hpp"

namespace Settings {
constexpr auto gamedata_dir          = "gamedata_dir";
constexpr auto scale_factor          = "scale_factor";
constexpr auto configfile            = "configfile";
constexpr auto loglevel              = "loglevel";
constexpr auto map_font              = "map_font";
constexpr auto map_font_scale        = "map_font_scale";
constexpr auto editor_width          = "editor_width_px";
constexpr auto editor_height         = "editor_height_px";
constexpr auto room_object_width     = "room_outline_width_px";
constexpr auto room_object_height    = "room_outline_height_px";
constexpr auto room_center_width     = "room_body_width_px";
constexpr auto room_center_height    = "room_body_height_px";
constexpr auto room_link_thickness   = "room_link_thickness_px";
constexpr auto room_link_margin      = "room_link_margin_px";
constexpr auto room_link_arrow_size  = "room_link_arrow_size_px";
constexpr auto room_spread_factor    = "room_spread_factor";
constexpr auto map_start_x           = "map_start_x";
constexpr auto map_start_y           = "map_start_y";
constexpr auto mouse_debounce_ms     = "mouse_debounce_ms";
constexpr auto editor_textwraplen    = "editor_textwraplen";
constexpr auto editor_fontsize_ratio = "editor_fontsize_ratio";

} // namespace Settings

#endif /* SETTINGS_HPP */
