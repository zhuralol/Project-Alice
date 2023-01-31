#pragma once

#include <stdint.h>
#include <optional>
#include <string_view>
#include <string>

#include "parsers.hpp"
#include "unordered_dense.h"
#include "gui_graphics.hpp"
#include "modifiers.hpp"

namespace parsers {

	//
	// structures and functions for parsing .gfx files
	//

	struct building_gfx_context {
		sys::state& full_state;
		ui::definitions& ui_defs;
		ankerl::unordered_dense::map<std::string, dcon::gfx_object_id> map_of_names;
		ankerl::unordered_dense::map<std::string, dcon::texture_id> map_of_texture_names;
		building_gfx_context(sys::state& full_state, ui::definitions& ui_defs) : full_state(full_state), ui_defs(ui_defs) {

		}
	};

	struct gfx_xy_pair {
		int32_t x = 0;
		int32_t y = 0;

		void finish(building_gfx_context& context) { }
	};

	struct gfx_object {
		std::optional<int32_t> size;
		std::optional<gfx_xy_pair> size_obj;
		std::optional<gfx_xy_pair> bordersize;
		std::string_view name;
		std::string_view primary_texture;
		std::string_view secondary_texture;

		int32_t noofframes = 1;

		bool horizontal = true;
		bool allwaystransparent = false;
		bool flipv = false;
		bool clicksound_set = false;
		bool transparencecheck = false;

		void clicksound(parsers::association_type, std::string_view, parsers::error_handler& err, int32_t line, building_gfx_context& context) {
			clicksound_set = true;
		}

		void finish(building_gfx_context& context) {
		}
	};

	struct gfx_object_outer {
		void spritetype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);
		void corneredtilespritetype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);
		void maskedshieldtype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);
		void textspritetype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);
		void tilespritetype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);
		void progressbartype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);
		void barcharttype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);
		void piecharttype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);
		void linecharttype(gfx_object const& obj, parsers::error_handler& err, int32_t line, building_gfx_context& context);

		void finish(building_gfx_context const& context) {
		}
	};

	void gfx_add_obj(parsers::token_generator& gen, parsers::error_handler& err, building_gfx_context& context);

	struct gfx_files {
		void finish(building_gfx_context& context) {
		}
	};

	//
	// structures and functions for parsing .gui files
	//

	struct gui_element_common {
		ui::element_data target;

		gui_element_common() { }
		void size(gfx_xy_pair const& pr, error_handler& err, int32_t line, building_gfx_context& context);
		void position(gfx_xy_pair const& pr, error_handler& err, int32_t line, building_gfx_context& context);
		void orientation(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void name(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void rotation(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void finish(building_gfx_context& context) {
		}
	};

	struct button : public gui_element_common {
		button();
		void spritetype(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void shortcut(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void buttontext(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void buttonfont(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void format(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void clicksound(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
	};

	struct image : public gui_element_common {
		image();
		void frame(association_type, uint32_t v, error_handler& err, int32_t line, building_gfx_context& context);
		void spritetype(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void scale(association_type, float v, error_handler& err, int32_t line, building_gfx_context& context);
	};

	struct textbox : public gui_element_common {
		textbox();
		void bordersize(gfx_xy_pair const& pr, error_handler& err, int32_t line, building_gfx_context& context);
		void fixedsize(association_type, bool v, error_handler& err, int32_t line, building_gfx_context& context);
		void maxwidth(association_type, int32_t v, error_handler& err, int32_t line, building_gfx_context& context);
		void maxheight(association_type, int32_t v, error_handler& err, int32_t line, building_gfx_context& context);
		void font(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void format(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void text(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void texturefile(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
	};

	struct listbox : public gui_element_common {
		listbox();
		void background(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void bordersize(gfx_xy_pair const& pr, error_handler& err, int32_t line, building_gfx_context& context);
		void offset(gfx_xy_pair const& pr, error_handler& err, int32_t line, building_gfx_context& context);
		void spacing(association_type, uint32_t v, error_handler& err, int32_t line, building_gfx_context& context);
	};

	struct overlapping : public gui_element_common {
		overlapping();
		void format(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void spacing(association_type, float v, error_handler& err, int32_t line, building_gfx_context& context);
	};

	struct scrollbar : public gui_element_common {
		std::vector<ui::element_data> children;
		std::string_view leftbutton_;
		std::string_view rightbutton_;
		std::string_view rangelimitmaxicon_;
		std::string_view rangelimitminicon_;
		std::string_view track_;
		std::string_view slider_;

		scrollbar();
		void horizontal(association_type, bool v, error_handler& err, int32_t line, building_gfx_context& context);
		void leftbutton(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void rightbutton(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void lockable(association_type, bool v, error_handler& err, int32_t line, building_gfx_context& context);
		void maxvalue(association_type, uint32_t v, error_handler& err, int32_t line, building_gfx_context& context);
		void rangelimitmaxicon(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void rangelimitminicon(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void slider(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void track(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void stepsize(association_type, std::string_view txt, error_handler& err, int32_t line, building_gfx_context& context);
		void userangelimit(association_type, bool v, error_handler& err, int32_t line, building_gfx_context& context);
		void bordersize(gfx_xy_pair const& pr, error_handler& err, int32_t line, building_gfx_context& context);
		void guibuttontype(button const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void icontype(image const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void finish(building_gfx_context& context);
	};

	struct window : public gui_element_common {
		std::vector<ui::element_data> children;
		window();
		void fullscreen(association_type, bool v, error_handler& err, int32_t line, building_gfx_context& context);
		void moveable(association_type, bool v, error_handler& err, int32_t line, building_gfx_context& context);
		void guibuttontype(button const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void icontype(image const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void eu3dialogtype(window const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void instanttextboxtype(textbox const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void listboxtype(listbox const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void positiontype(gui_element_common const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void scrollbartype(scrollbar const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void windowtype(window const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void checkboxtype(button const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void shieldtype(image const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void overlappingelementsboxtype(overlapping const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void editboxtype(textbox const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void textboxtype(textbox const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void finish(building_gfx_context& context);
	};

	struct guitypes {
		void finish(building_gfx_context& context) {
		}
		void guibuttontype(button const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void icontype(image const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void eu3dialogtype(window const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void instanttextboxtype(textbox const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void listboxtype(listbox const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void positiontype(gui_element_common const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void scrollbartype(scrollbar const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void windowtype(window const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void checkboxtype(button const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void shieldtype(image const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void overlappingelementsboxtype(overlapping const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void editboxtype(textbox const& v, error_handler& err, int32_t line, building_gfx_context& context);
		void textboxtype(textbox const& v, error_handler& err, int32_t line, building_gfx_context& context);
	};
	struct gui_files {
		void finish(building_gfx_context& context) {
		}
	};

	struct scenario_building_context {
		sys::state& state;

		ankerl::unordered_dense::map<uint32_t, dcon::national_identity_id> map_of_ident_names;
		tagged_vector<std::string, dcon::national_identity_id> file_names_for_idents;

		ankerl::unordered_dense::map<std::string, dcon::religion_id> map_of_religion_names;
		ankerl::unordered_dense::map<std::string, dcon::culture_id> map_of_culture_names;
		ankerl::unordered_dense::map<std::string, dcon::culture_group_id> map_of_culture_group_names;
		ankerl::unordered_dense::map<std::string, dcon::commodity_id> map_of_commodity_names;
		ankerl::unordered_dense::map<std::string, dcon::factory_type_id> map_of_production_types;

		scenario_building_context(sys::state& state) : state(state) { }
	};

	struct national_identity_file {
		void any_value(std::string_view tag, association_type, std::string_view txt, error_handler& err, int32_t line, scenario_building_context& context);
		void finish(scenario_building_context& context) { }
	};

	struct color_from_3f {
		uint32_t value = 0;
		template<typename T>
		void free_value(float v, error_handler& err, int32_t line, T& context) {
			value = (value >> 8) | (uint32_t(v * 255.0f) << 16);
		}
		template<typename T>
		void finish(T& context) { }
	};

	struct religion_context {
		dcon::religion_id id;
		scenario_building_context& outer_context;
	};
	struct religion_def {
		void icon(association_type, int32_t v, error_handler& err, int32_t line, religion_context& context) {
			context.outer_context.state.world.religion_set_icon(context.id, uint8_t(v));
		}
		void color(color_from_3f v, error_handler& err, int32_t line, religion_context& context) {
			context.outer_context.state.world.religion_set_color(context.id, v.value);
		}
		void pagan(association_type, bool v, error_handler& err, int32_t line, religion_context& context) {
			context.outer_context.state.world.religion_set_is_pagan(context.id, v);
		}
		void finish(religion_context& context) { }
	};

	void make_religion(std::string_view name, token_generator& gen, error_handler& err, scenario_building_context& context);

	struct religion_group {
		void finish(scenario_building_context& context) { }
	};

	struct religion_file {
		void any_group(std::string_view name, religion_group, error_handler& err, int32_t line, scenario_building_context& context) {

		}
		void finish(scenario_building_context& context) { }
	};

	struct color_from_3i {
		uint32_t value = 0;
		template<typename T>
		void free_value(int32_t v, error_handler& err, int32_t line, T& context) {
			value = (value >> 8) | (uint32_t(v & 0xFF) << 16);
		}
		template<typename T>
		void finish(T& context) { }
	};

	struct culture_group_context {
		dcon::culture_group_id id;
		scenario_building_context& outer_context;
	};
	struct culture_context {
		dcon::culture_id id;
		scenario_building_context& outer_context;
	};
	struct names_context {
		dcon::culture_id id;
		bool first_names = false;
		scenario_building_context& outer_context;
	};



	void make_culture_group(std::string_view name, token_generator& gen, error_handler& err, scenario_building_context& context);
	void make_culture(std::string_view name, token_generator& gen, error_handler& err, culture_group_context& context);
	void make_fn_list(token_generator& gen, error_handler& err, culture_context& context);
	void make_ln_list(token_generator& gen, error_handler& err, culture_context& context);

	struct names_list {
		void free_value(std::string_view text, error_handler& err, int32_t line, names_context& context) {
			auto new_id = context.outer_context.state.add_to_pool(text);
			if(context.first_names) {
				context.outer_context.state.world.culture_get_first_names(context.id).push_back(new_id);
			} else {
				context.outer_context.state.world.culture_get_last_names(context.id).push_back(new_id);
			}
		}
		void finish(names_context& context) { }
	};

	struct culture {
		void color(color_from_3i v, error_handler& err, int32_t line, culture_context& context) {
			context.outer_context.state.world.culture_set_color(context.id, v.value);
		}
		void radicalism(association_type, int32_t v, error_handler& err, int32_t line, culture_context& context) {
			context.outer_context.state.world.culture_set_radicalism(context.id, int8_t(v));
		}
		void finish(culture_context& context) { }
	};

	struct culture_group {
		void leader(association_type, std::string_view name, error_handler& err, int32_t line, culture_group_context& context) {
			if(name == "european")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::european));
			else if(name == "southamerican")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::southamerican));
			else if(name == "russian")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::russian));
			else if(name == "arab")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::arab));
			else if(name == "asian")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::asian));
			else if(name == "indian")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::indian));
			else if(name == "nativeamerican")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::nativeamerican));
			else if(name == "african")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::african));
			else if(name == "polar_bear")
				context.outer_context.state.world.culture_group_set_leader(context.id, uint8_t(sys::leader_type::polar_bear));
			else {
				err.accumulated_errors += "Unknown leader type " + std::string(name) + " in file " + err.file_name + " line " + std::to_string(line) + "\n";
			}
		}
		void is_overseas(association_type, bool v, error_handler& err, int32_t line, culture_group_context& context) {

			context.outer_context.state.world.culture_group_set_is_overseas(context.id, v);
		}
		void union_tag(association_type, uint32_t v, error_handler& err, int32_t line, culture_group_context& context) {
			auto nat_tag = context.outer_context.map_of_ident_names.find(v);
			if(nat_tag != context.outer_context.map_of_ident_names.end())
				context.outer_context.state.world.force_create_cultural_union_of(nat_tag->second, context.id);
			else
				err.accumulated_errors += "Unknown national tag in file " + err.file_name + " line " + std::to_string(line) + "\n";
		}
		void finish(culture_group_context& context) { }
	};

	struct culture_file {
		void finish(scenario_building_context& context) { }
	};


	struct good_group_context {
		sys::commodity_group group = sys::commodity_group::consumer_goods;
		scenario_building_context& outer_context;
	};
	struct good_context {
		dcon::commodity_id id;
		scenario_building_context& outer_context;
	};

	struct good {
		void money(association_type, bool v, error_handler& err, int32_t line, good_context& context) {
			if(v) {
				auto money_id = dcon::commodity_id(0);
				context.outer_context.state.world.commodity_set_color(money_id, context.outer_context.state.world.commodity_get_color(context.id));
				context.outer_context.state.world.commodity_set_cost(money_id, context.outer_context.state.world.commodity_get_cost(context.id));

				for(auto& pr : context.outer_context.map_of_commodity_names) {
					if(pr.second == context.id) {
						pr.second = money_id;
						break;
					}
				}
				context.id = money_id;
				context.outer_context.state.world.pop_back_commodity();
			}
		}
		void color(color_from_3i v, error_handler& err, int32_t line, good_context& context) {
			context.outer_context.state.world.commodity_set_color(context.id, v.value);
		}
		void cost(association_type, float v, error_handler& err, int32_t line, good_context& context) {
			context.outer_context.state.world.commodity_set_cost(context.id, v);
		}
		void available_from_start(association_type, bool b, error_handler& err, int32_t line, good_context& context) {
			context.outer_context.state.world.commodity_set_is_available_from_start(context.id, b);
		}

		void finish(good_context& context) { }
	};

	void make_good(std::string_view name, token_generator& gen, error_handler& err, good_group_context& context);
	void make_goods_group(std::string_view name, token_generator& gen, error_handler& err, scenario_building_context& context);

	struct goods_group {
		void finish(good_group_context& context) { }
	};

	struct goods_file {
		void finish(scenario_building_context& context) { }
	};

#define MOD_PROV_FUNCTION(X) template<typename T> \
	void X (association_type, float v, error_handler& err, int32_t line, T& context) { \
		if(next_to_add >= sys::modifier_definition_size) { \
			err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n"; \
		} else { \
			constructed_definition.offsets[next_to_add] = uint8_t(sys::provincial_mod_offsets:: X ); \
			constructed_definition.values[next_to_add] = v; \
			++next_to_add; \
		} \
	}
#define MOD_NAT_FUNCTION(X) template<typename T> \
	void X (association_type, float v, error_handler& err, int32_t line, T& context) { \
		if(next_to_add >= sys::modifier_definition_size) { \
			err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n"; \
		} else { \
			constructed_definition.offsets[next_to_add] = uint8_t(sys::national_mod_offsets:: X ); \
			constructed_definition.values[next_to_add] = v; \
			++next_to_add; \
		} \
	}

	struct modifier_base {
		uint8_t icon_index = 0;
		sys::modifier_definition constructed_definition;
		uint32_t next_to_add = 0;
		template<typename T>
		void icon(association_type, uint32_t v, error_handler& err, int32_t line, T& context) {
			icon_index = uint8_t(v);
		}

		MOD_PROV_FUNCTION(supply_limit)
		MOD_PROV_FUNCTION(attrition)
		MOD_PROV_FUNCTION(max_attrition)
		MOD_NAT_FUNCTION(war_exhaustion)
		MOD_NAT_FUNCTION(max_war_exhaustion)
		MOD_NAT_FUNCTION(leadership)
		MOD_NAT_FUNCTION(leadership_modifier)
		MOD_NAT_FUNCTION(supply_consumption)
		MOD_NAT_FUNCTION(org_regain)
		MOD_NAT_FUNCTION(reinforce_speed)
		MOD_NAT_FUNCTION(land_organisation)
		MOD_NAT_FUNCTION(naval_organisation)
		MOD_NAT_FUNCTION(research_points)
		MOD_NAT_FUNCTION(research_points_modifier)
		MOD_NAT_FUNCTION(research_points_on_conquer)
		MOD_NAT_FUNCTION(import_cost)
		MOD_NAT_FUNCTION(loan_interest)
		MOD_NAT_FUNCTION(tax_efficiency)
		MOD_NAT_FUNCTION(min_tax)
		MOD_NAT_FUNCTION(max_tax)
		MOD_NAT_FUNCTION(min_military_spending)
		MOD_NAT_FUNCTION(max_military_spending)
		MOD_NAT_FUNCTION(min_social_spending)
		MOD_NAT_FUNCTION(max_social_spending)
		MOD_NAT_FUNCTION(factory_owner_cost)
		MOD_NAT_FUNCTION(min_tariff)
		MOD_NAT_FUNCTION(max_tariff)
		MOD_NAT_FUNCTION(ruling_party_support)
		MOD_PROV_FUNCTION(local_ruling_party_support)
		MOD_NAT_FUNCTION(rich_vote)
		MOD_NAT_FUNCTION(middle_vote)
		MOD_NAT_FUNCTION(poor_vote)
		MOD_NAT_FUNCTION(minimum_wage)
		MOD_NAT_FUNCTION(factory_maintenance)
		MOD_PROV_FUNCTION(poor_life_needs)
		MOD_PROV_FUNCTION(rich_life_needs)
		MOD_PROV_FUNCTION(middle_life_needs)
		MOD_PROV_FUNCTION(poor_everyday_needs)
		MOD_PROV_FUNCTION(middle_everyday_needs)
		MOD_PROV_FUNCTION(rich_everyday_needs)
		MOD_PROV_FUNCTION(poor_luxury_needs)
		MOD_PROV_FUNCTION(middle_luxury_needs)
		MOD_PROV_FUNCTION(rich_luxury_needs)
		MOD_NAT_FUNCTION(unemployment_benefit)
		MOD_NAT_FUNCTION(pension_level)
		MOD_PROV_FUNCTION(population_growth)
		MOD_NAT_FUNCTION(global_population_growth)
		MOD_NAT_FUNCTION(factory_input)
		MOD_NAT_FUNCTION(factory_output)
		MOD_NAT_FUNCTION(factory_throughput)
		MOD_NAT_FUNCTION(rgo_input)
		MOD_NAT_FUNCTION(rgo_output)
		MOD_NAT_FUNCTION(rgo_throughput)
		MOD_NAT_FUNCTION(artisan_input)
		MOD_NAT_FUNCTION(artisan_output)
		MOD_NAT_FUNCTION(artisan_throughput)
		MOD_PROV_FUNCTION(local_factory_input)
		MOD_PROV_FUNCTION(local_factory_output)
		MOD_PROV_FUNCTION(local_factory_throughput)
		MOD_PROV_FUNCTION(local_rgo_input)
		MOD_PROV_FUNCTION(local_rgo_output)
		MOD_PROV_FUNCTION(local_rgo_throughput)
		MOD_PROV_FUNCTION(local_artisan_input)
		MOD_PROV_FUNCTION(local_artisan_output)
		MOD_PROV_FUNCTION(local_artisan_throughput)
		MOD_PROV_FUNCTION(number_of_voters)
		MOD_PROV_FUNCTION(goods_demand)
		MOD_NAT_FUNCTION(badboy)
		MOD_PROV_FUNCTION(assimilation_rate)
		MOD_NAT_FUNCTION(global_assimilation_rate)
		MOD_NAT_FUNCTION(prestige)
		MOD_NAT_FUNCTION(factory_cost)
		MOD_PROV_FUNCTION(life_rating)
		MOD_PROV_FUNCTION(farm_rgo_eff)
		MOD_PROV_FUNCTION(mine_rgo_eff)
		MOD_PROV_FUNCTION(farm_rgo_size)
		MOD_PROV_FUNCTION(mine_rgo_size)
		MOD_NAT_FUNCTION(issue_change_speed)
		MOD_NAT_FUNCTION(social_reform_desire)
		MOD_NAT_FUNCTION(political_reform_desire)
		MOD_NAT_FUNCTION(literacy_con_impact)
		MOD_PROV_FUNCTION(pop_militancy_modifier)
		MOD_PROV_FUNCTION(pop_consciousness_modifier)
		MOD_PROV_FUNCTION(rich_income_modifier)
		MOD_PROV_FUNCTION(middle_income_modifier)
		MOD_PROV_FUNCTION(poor_income_modifier)
		MOD_PROV_FUNCTION(boost_strongest_party)
		MOD_NAT_FUNCTION(global_immigrant_attract)
		template<typename T>
		void immigration(association_type, float v, error_handler& err, int32_t line, T& context) {
			if(next_to_add >= sys::modifier_definition_size) {
				err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n";
			} else {
				constructed_definition.offsets[next_to_add] = uint8_t(sys::provincial_mod_offsets::immigrant_attract);
				constructed_definition.values[next_to_add] = v;
				++next_to_add;
			}
		}
		MOD_PROV_FUNCTION(immigrant_attract)
		MOD_PROV_FUNCTION(immigrant_push)
		MOD_PROV_FUNCTION(local_repair)
		MOD_PROV_FUNCTION(local_ship_build)
		MOD_NAT_FUNCTION(poor_savings_modifier)
		MOD_NAT_FUNCTION(influence_modifier)
		MOD_NAT_FUNCTION(diplomatic_points_modifier)
		MOD_NAT_FUNCTION(mobilisation_size)
		MOD_NAT_FUNCTION(mobilisation_economy_impact)
		template<typename T> \
		void mobilization_size(association_type, float v, error_handler& err, int32_t line, T& context) {
			if(next_to_add >= sys::modifier_definition_size) {
					err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n";
			} else {
				constructed_definition.offsets[next_to_add] = uint8_t(sys::national_mod_offsets::mobilisation_size);
				constructed_definition.values[next_to_add] = v;
				++next_to_add;
			}
		}
		template<typename T>
		void mobilization_economy_impact(association_type, float v, error_handler& err, int32_t line, T& context) {
			if(next_to_add >= sys::modifier_definition_size) {
				err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n";
			} else {
				constructed_definition.offsets[next_to_add] = uint8_t(sys::national_mod_offsets::mobilisation_economy_impact);
				constructed_definition.values[next_to_add] = v;
				++next_to_add;
			}
		}
		MOD_NAT_FUNCTION(global_pop_militancy_modifier)
		MOD_NAT_FUNCTION(global_pop_consciousness_modifier)
		MOD_PROV_FUNCTION(movement_cost)
		MOD_PROV_FUNCTION(combat_width)
		MOD_PROV_FUNCTION(min_build_naval_base)
		MOD_PROV_FUNCTION(min_build_railroad)
		MOD_PROV_FUNCTION(min_build_fort)
		MOD_PROV_FUNCTION(attack)
		template<typename T>
		void defender(association_type, float v, error_handler& err, int32_t line, T& context) {
			if(next_to_add >= sys::modifier_definition_size) {
				err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n";
			} else {
				constructed_definition.offsets[next_to_add] = uint8_t(sys::provincial_mod_offsets::defense);
				constructed_definition.values[next_to_add] = v;
				++next_to_add;
			}
		}
		template<typename T>
		void attacker(association_type, float v, error_handler& err, int32_t line, T& context) {
			if(next_to_add >= sys::modifier_definition_size) {
				err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n";
			} else {
				constructed_definition.offsets[next_to_add] = uint8_t(sys::provincial_mod_offsets::attack);
				constructed_definition.values[next_to_add] = v;
				++next_to_add;
			}
		}
		template<typename T>
		void defence(association_type, float v, error_handler& err, int32_t line, T& context) {
			if(next_to_add >= sys::modifier_definition_size) {
				err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n";
			} else {
				constructed_definition.offsets[next_to_add] = uint8_t(sys::provincial_mod_offsets::defense);
				constructed_definition.values[next_to_add] = v;
				++next_to_add;
			}
		}
		MOD_NAT_FUNCTION(core_pop_militancy_modifier)
		MOD_NAT_FUNCTION(core_pop_consciousness_modifier)
		MOD_NAT_FUNCTION(non_accepted_pop_militancy_modifier)
		MOD_NAT_FUNCTION(non_accepted_pop_consciousness_modifier)
		MOD_NAT_FUNCTION(cb_generation_speed_modifier)
		MOD_NAT_FUNCTION(mobilization_impact)
		template<typename T>
		void mobilisation_impact(association_type, float v, error_handler& err, int32_t line, T& context) {
			if(next_to_add >= sys::modifier_definition_size) {
				err.accumulated_errors += "Too many modifier values; " + err.file_name + " line " + std::to_string(line) + "\n";
			} else {
				constructed_definition.offsets[next_to_add] = uint8_t(sys::national_mod_offsets::mobilization_impact);
				constructed_definition.values[next_to_add] = v;
				++next_to_add;
			}
		}
		MOD_NAT_FUNCTION(suppression_points_modifier)
		MOD_NAT_FUNCTION(education_efficiency_modifier)
		MOD_NAT_FUNCTION(civilization_progress_modifier)
		MOD_NAT_FUNCTION(administrative_efficiency_modifier)
		MOD_NAT_FUNCTION(land_unit_start_experience)
		MOD_NAT_FUNCTION(naval_unit_start_experience)
		MOD_NAT_FUNCTION(naval_attack_modifier)
		MOD_NAT_FUNCTION(naval_defense_modifier)
		MOD_NAT_FUNCTION(land_attack_modifier)
		MOD_NAT_FUNCTION(land_defense_modifier)
		MOD_NAT_FUNCTION(tariff_efficiency_modifier)
		MOD_NAT_FUNCTION(max_loan_modifier)
		MOD_NAT_FUNCTION(unciv_economic_modifier)
		MOD_NAT_FUNCTION(unciv_military_modifier)
		MOD_NAT_FUNCTION(self_unciv_economic_modifier)
		MOD_NAT_FUNCTION(self_unciv_military_modifier)
		MOD_NAT_FUNCTION(commerce_tech_research_bonus)
		MOD_NAT_FUNCTION(army_tech_research_bonus)
		MOD_NAT_FUNCTION(industry_tech_research_bonus)
		MOD_NAT_FUNCTION(navy_tech_research_bonus)
		MOD_NAT_FUNCTION(culture_tech_research_bonus)
		template<typename T>
		void finish(T& context) { }

		void convert_to_national_mod() {
			for(uint32_t i = 0; i < this->next_to_add; ++i) {
				if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::poor_life_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::poor_life_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::rich_life_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::rich_life_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::middle_life_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::middle_life_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::poor_everyday_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::poor_everyday_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::rich_everyday_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::rich_everyday_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::middle_everyday_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::middle_everyday_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::poor_luxury_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::poor_luxury_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::middle_luxury_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::middle_luxury_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::rich_luxury_needs) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::rich_luxury_needs);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::goods_demand) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::goods_demand);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::assimilation_rate) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::global_assimilation_rate);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::farm_rgo_eff) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::farm_rgo_eff);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::mine_rgo_eff) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::mine_rgo_eff);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::farm_rgo_size) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::farm_rgo_size);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::mine_rgo_size) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::mine_rgo_size);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::pop_militancy_modifier) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::global_pop_militancy_modifier);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::pop_consciousness_modifier) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::global_pop_consciousness_modifier);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::rich_income_modifier) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::rich_income_modifier);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::middle_income_modifier) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::middle_income_modifier);
				} else if(constructed_definition.offsets[i] == sys::provincial_mod_offsets::poor_income_modifier) {
					constructed_definition.offsets[i] = uint8_t(sys::national_mod_offsets::poor_income_modifier);
				}
				constructed_definition.offsets[i] += 1;
			}
		}
		void convert_to_province_mod() {
			for(uint32_t i = 0; i < this->next_to_add; ++i) {
				constructed_definition.offsets[i] += 1;
			}
		}
		void convert_to_neutral_mod() {
			for(uint32_t i = 0; i < this->next_to_add; ++i) {
				constructed_definition.offsets[i] -= 1;
			}
		}
	};

#undef MOD_PROV_FUNCTION
#undef MOD_NAT_FUNCTION


	struct int_vector {
		std::vector<int32_t> data;
		template<typename T>
		void free_value(int32_t v, error_handler& err, int32_t line, T& context) {
			data.push_back(v);
		}
		template<typename T>
		void finish(T& context) { }
	};
	struct commodity_array {
		tagged_vector<float, dcon::commodity_id> data;

		void any_value(std::string_view name, association_type, float value, error_handler& err, int32_t line, scenario_building_context& context) {
			auto found_commodity = context.map_of_commodity_names.find(std::string(name));
			if(found_commodity != context.map_of_commodity_names.end()) {
				data.safe_get(found_commodity->second) = value;
			} else {
				err.accumulated_errors += "Unknown commodity " + std::string(name) + " in file " + err.file_name + " line " + std::to_string(line) + "\n";
			}
		}

		void finish(scenario_building_context& context) {
			data.resize(context.state.world.commodity_size());
		}
	};

	enum class building_type {
		factory, naval_base, fort, railroad
	};
	struct building_definition : public modifier_base {
		int_vector colonial_points;
		commodity_array goods_cost;
		bool default_enabled = false;
		std::string_view production_type;
		float infrastructure = 0.0f;
		int32_t colonial_range = 0;
		int32_t max_level = 0;
		int32_t naval_capacity = 0;
		int32_t time = 0;
		int32_t cost = 0;
		building_type stored_type = building_type::factory;

		void type(association_type, std::string_view value, error_handler& err, int32_t line, scenario_building_context& context) {
			if(is_fixed_token_ci(value.data(), value.data() + value.length(), "factory")) {
				stored_type = building_type::factory;
			} else if(is_fixed_token_ci(value.data(), value.data() + value.length(), "fort")) {
				stored_type = building_type::fort;
			} else if(is_fixed_token_ci(value.data(), value.data() + value.length(), "naval_base")) {
				stored_type = building_type::naval_base;
			} else if(is_fixed_token_ci(value.data(), value.data() + value.length(), "infrastructure")) {
				stored_type = building_type::railroad;
			} else {
				err.accumulated_errors += "Unknown building type " + std::string(value) + " in file " + err.file_name + " line " + std::to_string(line) + "\n";
			}
		}
		

		void finish(scenario_building_context& context) { }
	};

	struct building_file {
		void result(std::string_view name, building_definition&& res, error_handler& err, int32_t line, scenario_building_context& context);
		void finish(scenario_building_context& context) { }
	};
}

#include "parser_defs_generated.hpp"

