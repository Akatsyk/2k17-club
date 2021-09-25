#include "horizon.hpp"
#include "i_menu.hpp"
#include "parser.hpp"
#include "source.hpp"
//#include "background_img.hpp"
//#include "imgui_extension.hpp"
#include "rendering.hpp"
#include "menu.hpp"
#include "misc.hpp"
#include "menu/setup/settings.h"
#include "rage_aimbot.hpp"

#pragma region "Key"
inline std::string get_kname(int key) {
	switch (key) {
	case VK_LBUTTON:
		return "mouse1";
	case VK_RBUTTON:
		return "mouse2";
	case VK_CANCEL:
		return "break";
	case VK_MBUTTON:
		return "mouse3";
	case VK_XBUTTON1:
		return "mouse4";
	case VK_XBUTTON2:
		return "mouse5";
	case VK_BACK:
		return "backspace";
	case VK_TAB:
		return "tab";
	case VK_CLEAR:
		return "clear";
	case VK_RETURN:
		return "enter";
	case VK_SHIFT:
		return "shift";
	case VK_CONTROL:
		return "ctrl";
	case VK_MENU:
		return "alt";
	case VK_PAUSE:
		return "[19]";
	case VK_CAPITAL:
		return "capslock";
	case VK_SPACE:
		return "space";
	case VK_PRIOR:
		return "pgup";
	case VK_NEXT:
		return "pgdown";
	case VK_END:
		return "end";
	case VK_HOME:
		return "home";
	case VK_LEFT:
		return "left";
	case VK_UP:
		return "up";
	case VK_RIGHT:
		return "right";
	case VK_DOWN:
		return "down";
	case VK_SELECT:
		return "select";
	case VK_INSERT:
		return "insert";
	case VK_DELETE:
		return "delete";
	case '0':
		return "0";
	case '1':
		return "1";
	case '2':
		return "2";
	case '3':
		return "3";
	case '4':
		return "4";
	case '5':
		return "5";
	case '6':
		return "6";
	case '7':
		return "7";
	case '8':
		return "8";
	case '9':
		return "9";
	case 'A':
		return "a";
	case 'B':
		return "b";
	case 'C':
		return "c";
	case 'D':
		return "d";
	case 'E':
		return "e";
	case 'F':
		return "f";
	case 'G':
		return "g";
	case 'H':
		return "h";
	case 'I':
		return "i";
	case 'J':
		return "j";
	case 'K':
		return "k";
	case 'L':
		return "l";
	case 'M':
		return "m";
	case 'N':
		return "n";
	case 'O':
		return "o";
	case 'P':
		return "p";
	case 'Q':
		return "q";
	case 'R':
		return "r";
	case 'S':
		return "s";
	case 'T':
		return "t";
	case 'U':
		return "u";
	case 'V':
		return "v";
	case 'W':
		return "w";
	case 'X':
		return "x";
	case 'Y':
		return "y";
	case 'Z':
		return "z";
	case VK_LWIN:
		return "left win";
	case VK_RWIN:
		return "right win";
	case VK_NUMPAD0:
		return "num 0";
	case VK_NUMPAD1:
		return "num 1";
	case VK_NUMPAD2:
		return "num 2";
	case VK_NUMPAD3:
		return "num 3";
	case VK_NUMPAD4:
		return "num 4";
	case VK_NUMPAD5:
		return "num 5";
	case VK_NUMPAD6:
		return "num 6";
	case VK_NUMPAD7:
		return "num 7";
	case VK_NUMPAD8:
		return "num 8";
	case VK_NUMPAD9:
		return "num 9";
	case VK_MULTIPLY:
		return "num mult";
	case VK_ADD:
		return "num add";
	case VK_SEPARATOR:
		return "|";
	case VK_SUBTRACT:
		return "num sub";
	case VK_DECIMAL:
		return "num decimal";
	case VK_DIVIDE:
		return "num divide";
	case VK_F1:
		return "f1";
	case VK_F2:
		return "f2";
	case VK_F3:
		return "f3";
	case VK_F4:
		return "f4";
	case VK_F5:
		return "f5";
	case VK_F6:
		return "f6";
	case VK_F7:
		return "f7";
	case VK_F8:
		return "f8";
	case VK_F9:
		return "f9";
	case VK_F10:
		return "f10";
	case VK_F11:
		return "f11";
	case VK_F12:
		return "f12";
	case VK_NUMLOCK:
		return "num lock";
	case VK_SCROLL:
		return "break";
	case VK_LSHIFT:
		return "shift";
	case VK_RSHIFT:
		return "shift";
	case VK_LCONTROL:
		return "ctrl";
	case VK_RCONTROL:
		return "ctrl";
	case VK_LMENU:
		return "alt";
	case VK_RMENU:
		return "alt";
	case VK_OEM_COMMA:
		return "),";
	case VK_OEM_PERIOD:
		return ".";
	case VK_OEM_1:
		return ";";
	case VK_OEM_MINUS:
		return "-";
	case VK_OEM_PLUS:
		return "=";
	case VK_OEM_2:
		return "/";
	case VK_OEM_3:
		return "grave";
	case VK_OEM_4:
		return "[";
	case VK_OEM_5:
		return "\\";
	case VK_OEM_6:
		return "]";
	case VK_OEM_7:
		return "[222]";
	default:
		return "";
	}
}
#pragma endregion

template <typename T>
static bool items_getter(void* data, int idx, const char** out_text)
{
	auto items = (T*)data;
	if (out_text) {
		*out_text = items[idx].item_name.data();//std::string(items[idx].name.begin(), items[idx].translated_name.end()).data();
	}
	return true;
};

int tabcount = 0;

struct s_tab
{
	const char* name = "";
	const char* icon = 0;
	ImVec2 size = ImVec2(0, 0);
	int num = 0;

	s_tab(const char* _name, const char* _icon = "", ImVec2 _size = ImVec2(0, 0))
	{
		name = _name;
		icon = _icon;
		size = _size;
		num = tabcount;
		tabcount++;
	}

	~s_tab()
	{
		/*tabcount--;
		name = "";
		icon = 0;
		size = ImVec2(0, 0);
		num = 0;*/
	}
};

namespace ImGui
{
	bool ColorButton(const char* desc_id, const float col[], ImGuiColorEditFlags flags, ImVec2 size)
	{
		return ImGui::ColorButton(desc_id, ImColor(col[0], col[1], col[2], col[3]), flags, size);
	}

	ImGuiID Colorpicker_Close = 0;
	__inline void CloseLeftoverPicker() { if (Colorpicker_Close) ImGui::ClosePopup(Colorpicker_Close); }
	bool ColorPickerBox(const char* picker_idname, float col_ct[], float col_t[], float col_ct_invis[], float col_t_invis[], bool alpha = true, bool use_buttons = false)
	{
		bool ret = false;

		ImGui::SameLine();
		static bool switch_entity_teams = false;
		static bool switch_color_vis = false;

		float* col = use_buttons ? (switch_entity_teams ? (switch_color_vis ? col_t : col_t_invis) : (switch_color_vis ? col_ct : col_ct_invis)) : col_ct;

		const auto cursor_pos_y = GetCursorPosY();

		SetCursorPosY(cursor_pos_y + 5);
		bool open_popup = ImGui::ColorButton(picker_idname, col, ImGuiColorEditFlags_NoSidePreview
			| ImGuiColorEditFlags_NoSmallPreview
			| ImGuiColorEditFlags_AlphaPreview
			| ImGuiColorEditFlags_NoTooltip
			| ImGuiColorEditFlags_ColorPicker
			| ImGuiColorEditFlags_ColorPickerSameline, ImVec2(18, 10));

		SetCursorPosY(GetCursorPosY() - 5);

		/*SetCursorPosY(cursor_pos_y);*/
		if (open_popup) {
			ImGui::OpenPopup(picker_idname);
			Colorpicker_Close = ImGui::GetID(picker_idname);
		}

		if (ImGui::BeginPopup(picker_idname))
		{
			if (use_buttons) {
				const char* button_name0 = switch_entity_teams ? "Terrorists" : "Counter-Terrorists";
				if (ImGui::Button(button_name0, ImVec2(-1, 0)))
					switch_entity_teams = !switch_entity_teams;

				const char* button_name1 = switch_color_vis ? "Visible" : "Invisible";
				if (ImGui::Button(button_name1, ImVec2(-1, 0)))
					switch_color_vis = !switch_color_vis;
			}

			std::string id_new = picker_idname;
			id_new += "##pickeritself_";

			ret = ImGui::ColorPicker(id_new.c_str(), col, (alpha ? ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar : 0));
			ImGui::EndPopup();
		}

		return ret;
	}

	bool mouse_in_pos(ImRect minmaxs)
	{
		ImGuiContext& g = *GImGui;
		return (g.IO.MousePos.x >= minmaxs.Min.x && g.IO.MousePos.y >= minmaxs.Min.y && g.IO.MousePos.x <= minmaxs.Max.x && g.IO.MousePos.y <= minmaxs.Max.y);
	}

	bool Tab(const char* label, const ImVec2& size_arg, bool selected)
	{
		return ButtonEx(label, size_arg, (selected ? ImGuiItemFlags_TabButton : 0));
	}

	// NB: This is an internal helper. The user-facing IsItemHovered() is using data emitted from ItemAdd(), with a slightly different logic.
	bool IsHovered(const ImRect& bb, ImGuiID id, bool flatten_childs)
	{
		ImGuiContext& g = *GImGui;
		if (g.HoveredId == 0 || g.HoveredId == id || g.HoveredIdAllowOverlap)
		{
			ImGuiWindow* window = GetCurrentWindowRead();
			if (g.HoveredWindow == window || (flatten_childs && g.HoveredRootWindow == window->RootWindow))
				if ((g.ActiveId == 0 || g.ActiveId == id || g.ActiveIdAllowOverlap) && IsMouseHoveringRect(bb.Min, bb.Max))
					return true;
		}
		return false;
	}


	bool Bind(const char* label, int* key, const ImVec2& size_arg)
	{
		ImGuiWindow* window = GetCurrentWindow();

		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		const ImGuiIO& io = g.IO;
		const ImGuiStyle& style = g.Style;

		const ImGuiID id = window->GetID(label);

		ImVec2 label_size = CalcTextSize(label, NULL, true);
		ImVec2 size = CalcItemSize(size_arg, CalcItemWidth() / 2, label_size.y + style.FramePadding.y);// *2.0f);

		const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
		const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? (style.ItemInnerSpacing.x + label_size.x) : 0.0f, 0.0f));

		ItemSize(total_bb, style.FramePadding.y);

		if (!ItemAdd(total_bb, id))
			return false;

		bool value_changed = false;

		std::string text = "None";

		bool hovered = false, held = false;

		if (g.ActiveId == id)
		{
			text = "Press a Key";

			if (!g.ActiveIdIsJustActivated)
			{
				for (int i = 0; i < 255; i++)
				{
					if (ctx.pressed_keys[i])//g.IO.KeysReleased[i])
					{
						SetActiveID(0, window);
						*key = (i == 0x1B/*VK_ESCAPE*/) ? 0 : i;
						value_changed = true;
						break;
					}
				}

				/*for (int i = 0; i < 6; i++)
				{
					if (g.IO.MouseReleased[i])
					{
						SetActiveID(0);
						*key = i + 1;
						value_changed = true;
						break;
					}
				}*/
			}
		}
		else
		{
			hovered = IsHovered(frame_bb, id, false);

			if (hovered)
			{
				SetHoveredID(id);

				if (g.IO.MouseDown[0])
				{
					held = true;
					FocusWindow(window);
				}
				else if (g.IO.MouseReleased[0])
				{
					SetActiveID(id, window);
				}
			}

			text = get_kname(*key);
		}

		const ImU32 col = GetColorU32((hovered && held) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
		RenderFrame(frame_bb.Min, frame_bb.Max, col, true, style.FrameRounding); // main frame
		label_size = CalcTextSize(text.c_str(), NULL, true);
		ImVec2 pos_min = frame_bb.Min;
		ImVec2 pos_max = frame_bb.Max;
		ImVec2 label_pos = pos_min;
		label_pos.x = ImMax(label_pos.x, (label_pos.x + pos_max.x - label_size.x) * 0.5f);
		label_pos.y = ImMax(label_pos.y, (label_pos.y + pos_max.y - label_size.y) * 0.5f);
		RenderText(label_pos, text.c_str(), NULL);
		RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y - 3), label); // render item lable

		return value_changed;
	}
}

namespace menu
{
	LPDIRECT3DTEXTURE9 flag_ewropi = NULL;
	LPDIRECT3DTEXTURE9 m_tplayer_with_glow = NULL;
	LPDIRECT3DTEXTURE9 m_tplayer_no_glow = NULL;
	IDirect3DDevice9* m_device = nullptr;

	int category = -1;
	int new_category = -1;

	void init(const float& alpha)
	{
		auto style = &ImGui::GetStyle();

		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];//ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_CloseButton] = ImVec4(0.41f, 0.41f, 0.41f, 0.50f);
		colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

		ImGui::GetIO().Fonts->AddFontDefault();
	}

	void skins_listbox(const char* label, std::string filter, int selected_rarity, int* current_item, skin_list_t& skins, int height_in_items, const float& alpha)
	{
		if (!ImGui::ListBoxHeader(label, skins.list.size(), height_in_items))
			return;

		for (int i = 0; i < skins.list.size(); i++)
		{
			const auto item_selected = (i == *current_item);
			const auto item_text = skins.list[i].translated_name;
			auto rarity = parser::rarities.get_by_id(skins.list[i].rarity);
			auto color = rarity.Color.alpha(alpha * 255);

			if (selected_rarity != 0 &&
				selected_rarity != rarity.id)
				continue;

			std::string pstr = std::string(item_text.begin(), item_text.end());

			if (!filter.empty() &&
				parser::to_lower(pstr).find(parser::to_lower(filter)) == std::string::npos)
				continue;

			ImGui::PushID(i);
			ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)color);
			if (ImGui::Selectable(pstr.data(), item_selected))
			{
				*current_item = i;
			}
			ImGui::PopStyleColor();
			ImGui::PopID();
		}

		ImGui::ListBoxFooter();
	}

	void draw_skinchanger(const float& alpha)
	{
		static auto selected_item = 0;
		static auto fake_wear = 1.f;
		static auto fake_seed = 0;
		static char fake_name[256] = "";
		static auto fake_stattrak = false;
		static auto fake_stattrak_value = 0;

		//if (ImGui::Begin("Skin changer")
		//{
		ImGui::Page::Begin(3);
		ImGui::PushItemWidth(ImGui::GetCurrentWindow()->Size.x);

		ImGui::ListBox(sxor("##weapons"), &selected_item, items_getter<weapon_t>, (void*)parser::weapons.list.data(), parser::weapons.list.size(), 22);

		ImGui::PopItemWidth();
		ImGui::Page::Next();
		ImGui::PushItemWidth(ImGui::GetCurrentWindow()->Size.x);

		static bool show_all_skins = false;
		//ImGui::Checkbox("All skins", &show_all_skins);

		static char filter_buffer[64] = "";
		ImGui::InputText(sxor("##filter"), filter_buffer, 64);

		// draw rarities
		static auto selected_rarity = 0;
		{
			static auto draw_rarity = [](rarity_t& rarity, int& selected_rarity, const float& alpha) {

				bool selected = false;
				auto size = ImVec2(12, 8);

				auto rarity_col = rarity.Color.alpha(alpha * 255);

				ImGui::PushStyleColor(ImGuiCol_Button, selected_rarity == rarity.id ? (ImVec4)rarity_col : (ImVec4)rarity_col.malpha(0.3f)); //40 ����� ����
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)rarity_col.malpha(0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)rarity_col.malpha(0.7f));

				if (ImGui::Button(("##" + rarity.name).data(), size))
					selected_rarity = rarity.id;

				ImGui::PopStyleColor(3);
				ImGui::SameLine(/*0.f, 10.4f*/);

			};

			for (auto& rarity : parser::rarities.list) {
				draw_rarity(rarity, selected_rarity, alpha);
			}

			ImGui::NewLine();
		}

		auto selected_weapon = parser::weapons.list[selected_item].id;
		auto selected_skin = 0;
		/*for (auto i = 0u; i < parser::weapons.list[selected_item].skins.list.size(); i++)
		{
			auto skin = parser::weapons.list[selected_item].skins.list[i];
			if (skin.id == cheat::settings.paint[selected_weapon])
				selected_skin = i;
		}*/
		auto old_skin = selected_skin;

		if (!parser::weapons.list.empty())
			skins_listbox(sxor("##skins"), std::string(filter_buffer), selected_rarity, &selected_skin, parser::weapons.list[selected_item].skins, 20, alpha);

		//if (selected_skin != old_skin) {
		//	ctx.m_settings.paint[selected_weapon] = parser::weapons.list[selected_item].skins.list[selected_skin].id;
		//	//game::full_update();
		//}

		ImGui::PopItemWidth();
		ImGui::Page::Next();
		ImGui::PushItemWidth(ImGui::GetCurrentWindow()->Size.x);

		ImGui::SliderFloat(sxor("wear"), &fake_wear, 0.f, 1.f);
		ImGui::Spacing();

		ImGui::Text(sxor("seed"));
		ImGui::InputInt(sxor("##_seed"), &fake_seed);
		ImGui::Spacing();

		ImGui::Checkbox(sxor("stat trak"), &fake_stattrak);
		if (fake_stattrak) {
			ImGui::InputInt(sxor("##_stattrak_value"), &fake_stattrak_value);
		}
		ImGui::Spacing();

		ImGui::Text(sxor("name"));
		ImGui::InputText(sxor("##_name"), fake_name, 256);
		ImGui::Spacing();

		static auto selected_knife = 0;
		static std::vector<knife_t> knife_list;
		if (knife_list.empty())
		{
			knife_list = parser::knifes.list;

			knife_t default_knife;
			default_knife.id = 0;
			default_knife.translated_name = L"Default";
			knife_list.insert(knife_list.begin(), default_knife);
		}

		if (ImGui::ListBox("##knife_changer", &selected_knife, items_getter<knife_t>, (void*)knife_list.data(), knife_list.size(), 6))
		{
			auto new_id = knife_list[selected_knife].id;
			ctx.m_settings.skinchanger_knife = new_id;
			//game::full_update();
		}

		ImGui::PopItemWidth();
		ImGui::Page::End();

		//}
		//ImGui::End();
	}

	bool add_tab(s_tab tab, int* var/*, bool is_clickable = true*/, ImVec2 override_size = ImVec2(-1, -1), bool hovered = true)
	{
		bool ret = false;
		const auto allowed_to_use_icon = strlen(tab.icon) > 0;

		if (allowed_to_use_icon && !hovered)
			ImGui::PushFont(d::fonts::menu_icons.imgui);
		else
			ImGui::PushFont(d::fonts::menu_tab.imgui);

		if (ImGui::Tab((allowed_to_use_icon && !hovered ? tab.icon : tab.name), override_size == ImVec2(-1, -1) ? tab.size : override_size, *var == tab.num))
		{
			ret = true;

			if (/*is_clickable && */var != nullptr)
				*var = tab.num;
		}

		ImGui::PopFont();

		//ImGui::SameLine(0);
		return ret;
	}

	std::list<int> get_spec(int playerId)
	{
		std::list<int> list;

		if (!csgo.m_engine()->IsInGame())
			return list;

		auto player = csgo.m_entity_list()->GetClientEntity(playerId);
		if (!player)
			return list;

		if (player->IsDead())
		{
			auto observerTarget = player->m_hObserverTarget() ? csgo.m_entity_list()->GetClientEntityFromHandle(*player->m_hObserverTarget()) : nullptr;
			if (!observerTarget)
				return list;

			player = observerTarget;
		}

		for (int i = 1; i < csgo.m_globals()->maxClients; i++)
		{
			auto pPlayer = csgo.m_entity_list()->GetClientEntity(i);

			if (!pPlayer)
				continue;

			if (pPlayer->IsDormant() || !pPlayer->IsDead())
				continue;

			auto target = pPlayer->m_hObserverTarget() ? csgo.m_entity_list()->GetClientEntityFromHandle(*pPlayer->m_hObserverTarget()) : nullptr;
			if (player != target)
				continue;

			list.push_back(i);
		}

		return list;
	}

	void speclist()
	{
		if (!ctx.m_settings.misc_spectators_list)
			return;

		ImGuiStyle& style = ImGui::GetStyle();
		//float oldAlpha = style.Colors[ImGuiCol_WindowBg].w;
		//style.Colors[ImGuiCol_WindowBg].w = Vars.Visuals.SpectatorListAlpha / 255.0f;

		if (ImGui::Begin(sxor("spectator list"), &ctx.m_settings.misc_spectators_list, ImVec2(300, 300), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_ShowBorders))// |  ImGuiWindowFlags_ShowBorders))
		{
			ImGui::TextColored(ImVec4(style.Colors[ImGuiCol_Text].x - 0.3f, style.Colors[ImGuiCol_Text].y - 0.3f, style.Colors[ImGuiCol_Text].z - 0.3f, style.Colors[ImGuiCol_Text].w), sxor("spectators:"));
			ImGui::Separator();
			if (csgo.m_engine()->IsInGame()) {
				for (int playerId : get_spec(csgo.m_engine()->GetLocalPlayer()))
				{
					auto player = csgo.m_entity_list()->GetClientEntity(playerId);

					player_info entityInformation;
					csgo.m_engine()->GetPlayerInfo(playerId, &entityInformation);

					std::string name(entityInformation.name);

					if (name.size() > 31)
						name.resize(31);

					ImGui::Text(name.c_str());
				}
			}
			//ImGui::Separator();

			ImGui::End();
		}
		//style.WindowPadding = oldPadding;
		//style.Colors[ImGuiCol_WindowBg].w = oldAlpha;
	}

	void draw(IDirect3DDevice9* device)
	{
		//	ImGui::is_input_allowed = true;
		//	m_device = device;


		//	ImGuiIO& io = ImGui::GetIO();
		//	io.MousePos.x = feature::menu->_cursor_position.x;
		//	io.MousePos.y = feature::menu->_cursor_position.y;
		//	//ImGui::GetIO().MouseDrawCursor = m_opened; // makes cursor dissapear when menu is closed ///������ ������, ���� �� ������

		//	if (ctx.m_settings.misc_status_list)
		//	{
		//		static bool tr = true;
		//		float cursor_pos_y;
		//		ImGui::Begin("status list", &ctx.m_settings.misc_status_list, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders);
		//		{
		//			if (csgo.m_engine()->IsInGame() && !ctx.m_local()->IsDead())
		//			{
		//				ImGui::is_input_allowed = false;
		//				int desync_range = fabs(Math::angle_diff(ctx.angles[ANGLE_REAL], ctx.angles[ANGLE_FAKE]));
		//				int fakelag_choke = csgo.m_client_state()->m_iChockedCommands;

		//				ImGui::Text("desync delta:");
		//				ImGui::SameLine();

		//				cursor_pos_y = ImGui::GetCursorPosY();

		//				ImGui::SetCursorPosY(cursor_pos_y + 8);
		//				ImGui::SliderInt("##lmao", &desync_range, 0, 60); 
		//				ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
		//				
		//				//ImGui::TextColored(lby_broken ? ImVec4(0.f, 1.f, 0.f, 1.f) : ImVec4(1.f, 0.f, 0.f, 1.f), "[is broken]");

		//				//ImGui::Text("lagcomp:");
		//				//ImGui::SameLine();
		//				//ImGui::TextColored(Vars.LC ? ImVec4(0.f, 1.f, 0.f, 1.f) : ImVec4(1.f, 0.f, 0.f, 1.f), "[is broken]");

		//				ImGui::Text("speed: %.0f", ctx.m_local()->m_vecVelocity().Length2D());
		//		
		//				ImGui::Text("fakelag:");
		//				ImGui::SameLine();
		//				cursor_pos_y = ImGui::GetCursorPosY();

		//				ImGui::SetCursorPosY(cursor_pos_y + 8);
		//				ImGui::SliderInt("##flmao", &fakelag_choke, 0, 15);
		//				ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);

		//				if (ctx.has_exploit_toggled)
		//				{
		//					ImGui::Text("exploit:");
		//					
		//					if (ctx.exploit_allowed && ctx.ticks_allowed > 13 && ctx.main_exploit != 0) {
		//						ImGui::SameLine();

		//						if (ctx.main_exploit == 1)
		//							ImGui::Text("hide shots");
		//						else if (ctx.main_exploit > 1)
		//							ImGui::Text("doubletap");
		//					}
		//					else
		//					{
		//						ImGui::SameLine();
		//						ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "none");
		//					}
		//				}

		//				if (ctx.m_settings.aimbot_key != 0)
		//				{
		//					ImGui::Text("rage aimbot: ");
		//					ImGui::SameLine();
		//				
		//					if (ctx.allows_aimbot)
		//						ImGui::Text("enabled");
		//					else
		//						ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "disabled");
		//				
		//				}

		//				if (ctx.allows_aimbot)
		//				{
		//					ImGui::Text("min damage override: ");
		//					ImGui::SameLine();

		//					if (feature::ragebot->m_damage_key)
		//						ImGui::Text("enabled");
		//					else
		//						ImGui::Text("disabled");

		//				}

		//				/*ImGui::Text("lagcomp:");
		//				ImGui::SameLine();
		//				ImGui::TextColored(ctx.breaks_lc ? ImVec4(0.f, 1.f, 0.f, 1.f) : ImVec4(1.f, 0.f, 0.f, 1.f), "%.f", ctx.last_origin_delta);*/
		//			}
		//		}
		//		ImGui::End();
		//	}

		//	speclist();

		//	if (!feature::menu->_menu_opened)
		//		return;

		//	ImGui::is_input_allowed = true;

		//	static auto alpha = 1.f;
		//	static auto pos = 0.4f;
		//	static auto switch_p = false;
		//	static auto switch_category = false;
		//	static auto was_hovered = false;
		//	static auto tab_size = 150.f;

		//	/*
		//	main.RegisterTab(&legitbot, "legit bot", "a", 480, 660, { "global", "A", "P", "e", "W", "Z" }, F::Weapons);
		//	main.RegisterTab(&ragebot, "rage bot", "c", 0, 623, {"aimbot", "anti-aim"});
		//	main.RegisterTab(&visuals, "visuals", "d", 530, 0, { "players","other" });
		//	main.RegisterTab(&misc, "miscellaneous", "f", 0, 623, {"misc", "config"});
		//	main.RegisterTab(&skins, "skins", "e", 0, 623);
		//	main.RegisterTab(&Lists, "players", "k", 530, 660);
		//	*/

		//	static auto t_ragebot = s_tab(("Ragebot"), "c");
		//	static auto t_legitbot = s_tab(("Legitbot"), "a");
		//	static auto t_visuals = s_tab(("Visuals"), "d");
		//	static auto t_skins = s_tab(("Skins"), "e");
		//	static auto t_misc = s_tab(("Misc"), "f");
		//	static auto	curtab = 0;

		//	//bool pressed_return = false;

		//	if (alpha < 1.f)
		//		init(1.f); //����� ��� ���� �� ������� �������� ���������

		//	ImGui::SetNextWindowSize(ImVec2(700, 550));

		//	if (ImGui::Begin(sxor("birdie v4"), (bool*)0, ImGuiWindowFlags_NoCollapse | ImGuiColumnsFlags_NoResize | ImGuiWindowFlags_NoTitleBar/*| ImGuiWindowFlags_CoolStyle*/ | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse, 0))
		//	{
		//		auto window = ImGui::GetCurrentWindow();
		//		const auto cursorpos = ImGui::GetCursorPos();

		//		/*pos = Math::clamp(pos, -1.f, 0.f);
		//		ImGui::PushClipRect(window->Pos + ImVec2(window->WindowPadding.x, 40 + window->WindowPadding.y), window->Pos + ImVec2(0, 40 + window->WindowPadding.y) + ImVec2(window->Size.x - window->WindowPadding.x, window->Size.y - 40 - window->WindowPadding.y * 2.f), false);
		//		ImGui::SetCursorPosY(cursorpos.y + window->Size.y * pos);
		//		ImGui::SetCursorPosX(cursorpos.x - 500);
		//		ImGui::Image((void*)flag_ewropi, ImVec2(1600, 900), ImVec2(0.f, 0.f), ImVec2(1.f, 1.f), ImVec4(1.f, 1.f, 1.f, 0.15f));
		//		ImGui::PopClipRect();

		//		if (fabs(pos) >= 1.f || pos == 0.f)
		//			switch_p = !switch_p;

		//		if (switch_p)
		//			pos -= 0.0005f;
		//		else
		//			pos += 0.0005f;

		//		ImGui::SetCursorPos(cursorpos);*/

		//		if (alpha < 1.f) //����� �� ��� ������ �� ��� ����� � �������� ��� ����� ��� ���� LINE#308, �����.
		//			init(alpha); //����� ��� ���� �� ������� �������� ���������

		//		auto is_hovered = ImGui::mouse_in_pos(ImRect(window->Pos, window->Pos + ImVec2(static_cast<float>(tab_size * 0.45f) + window->WindowPadding.x * 2.f, window->Size.y)));

		//		if (is_hovered || was_hovered && ImGui::mouse_in_pos(ImRect(window->Pos, window->Pos + ImVec2(tab_size + window->WindowPadding.x * 2.f, window->Size.y)))) {
		//			if (pos < 1.f)
		//				pos += 0.08f;

		//			is_hovered = true;
		//		}
		//		else {
		//			if (pos > 0.5f)
		//				pos -= 0.08f;
		//		}

		//		pos = Math::clamp(pos, 0.5f, 1.f);

		//		const auto show_names = (pos > 0.65f);

		//		/*if (pos > 0.8f)
		//		{
		//			ImGui::SameLine();
		//			ImGui::SetCursorPosY(cursorpos.y + window->Size.y - window->WindowPadding.y*2.f - 22.5f);
		//			ImGui::Text("getze.us v4");
		//		}*/
		//		ImGui::SetCursorPos(cursorpos);

		//		ImGui::PushClipRect(window->Pos, window->Pos + ImVec2(tab_size * pos + window->WindowPadding.x * 2.f, window->Size.y), false);
		//		add_tab(t_ragebot, &curtab, ImVec2(tab_size * pos, static_cast<float>(tab_size * 0.45f)), show_names);
		//		add_tab(t_legitbot, &curtab, ImVec2(tab_size * pos, static_cast<float>(tab_size * 0.45f)), show_names);
		//		add_tab(t_visuals, &curtab, ImVec2(tab_size * pos, static_cast<float>(tab_size * 0.45f)), show_names);
		//		add_tab(t_skins, &curtab, ImVec2(tab_size * pos, static_cast<float>(tab_size * 0.45f)), show_names);
		//		add_tab(t_misc, &curtab, ImVec2(tab_size * pos, static_cast<float>(tab_size * 0.45f)), show_names);
		//		ImGui::PopClipRect();

		//		ImGui::SetCursorPos(ImVec2(tab_size * pos + window->WindowPadding.x * 2.f, cursorpos.y));

		//		//if (switch_category) {
		//		//	if (alpha > 0.01f) {
		//		//		init(alpha); //��������� �������
		//		//		alpha -= 0.025f;
		//		//	}
		//		//	else {
		//		//		switch_category = false;
		//		//		category = new_category; //�������� ����� ���������, ����-� ����������� ��������
		//		//	}
		//		//}
		//		//else
		//		//{
		//		//	if (alpha < 1.f) {
		//		//		init(alpha); //��������� �������
		//		//		alpha += 0.025f;
		//		//	}
		//		//}

		//		alpha = Math::clamp(alpha, 0.f, 1.f);

		//		static int currentCategory{ 0 };
		//		static int currentWeapon{ 0 };

		//		ImGui::BeginChild(sxor("##mainshit"), ImVec2(0, window->Size.y - window->WindowPadding.y * 2.f), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		//		{
		//			float cursor_pos_y;

		//			switch (curtab)
		//			{
		//			case 0:
		//				ImGui::Columns(2, NULL, true);
		//				{
		//					ImGui::BeginChild("##ragebotmain");
		//					{
		//						ImGui::Checkbox(sxor("Ragebot enabled"), &ctx.m_settings.aimbot_enabled);
		//						ImGui::SameLine();
		//						ImGui::Bind(sxor("##ROnkey"), &ctx.m_settings.aimbot_key, ImVec2(100, 20));

		//						ImGui::Checkbox(sxor("Automatic revolver"), &ctx.m_settings.aimbot_auto_revolver);
		//						ImGui::Checkbox(sxor("Silent aim"), &ctx.m_settings.aimbot_silent_aim);
		//						ImGui::Checkbox(sxor("No Recoil/Spread"), &ctx.m_settings.aimbot_no_spread);
		//						ImGui::Checkbox(sxor("Automatic scope"), &ctx.m_settings.aimbot_autoscope);
		//						ImGui::SliderInt(sxor("Field of view"), &ctx.m_settings.aimbot_fov_limit, 0, 180);
		//						ImGui::Checkbox(sxor("Hitchance"), &ctx.m_settings.aimbot_hitchance);

		//						ImGui::SliderInt(sxor("##hcv"), &ctx.m_settings.aimbot_hitchance_val, 0, 100);
		//						ImGui::Spacing();

		//						ImGui::SliderInt(sxor("Min damage"), &ctx.m_settings.aimbot_min_damage_viable, 0, 101);
		//						ImGui::Spacing();
		//						ImGui::Checkbox(sxor("Autowall"), &ctx.m_settings.aimbot_autowall);
		//						ImGui::Text(sxor("Wall min damage"));
		//						ImGui::SliderInt(sxor("##Wallmindamage"), &ctx.m_settings.aimbot_min_damage, 0, 101);
		//						ImGui::Spacing();
		//						ImGui::Checkbox("Position Adjustment", &ctx.m_settings.aimbot_position_adjustment);
		//						ImGui::Checkbox("Extended Silent Shot", &ctx.m_settings.extended_silent_shot);
		//						ImGui::Checkbox("Fake-Correction", &ctx.m_settings.aimbot_position_adjustment_old);
		//						ImGui::Checkbox("Aimbot With Knife", &ctx.m_settings.aimbot_allow_knife);
		//						ImGui::Checkbox("Aimbot With Zeus", &ctx.m_settings.aimbot_allow_taser);
		//						ImGui::Checkbox("OnShot Capsule", &ctx.m_settings.misc_visuals_hitboxes);
		//						ImGui::ColorPickerBox("#nigaimbox", ctx.m_settings.misc_visuals_hitboxes_color, nullptr, nullptr, nullptr);
		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();

		//						ImGui::Columns(2, NULL, true);
		//						ImGui::BeginChild("##ragebothitbox");
		//						{

		//							ImGui::Checkbox(sxor("Scan head"), &ctx.m_settings.aimbot_hitboxes[0]);
		//							ImGui::Checkbox(sxor("Scan chest"), &ctx.m_settings.aimbot_hitboxes[1]);
		//							ImGui::Checkbox(sxor("Scan body"), &ctx.m_settings.aimbot_hitboxes[2]);
		//							ImGui::Checkbox(sxor("Scan arms"), &ctx.m_settings.aimbot_hitboxes[3]);
		//							ImGui::Checkbox(sxor("Scan legs"), &ctx.m_settings.aimbot_hitboxes[4]);
		//							ImGui::Checkbox(sxor("Scan feet"), &ctx.m_settings.aimbot_hitboxes[5]);
		//							ImGui::Separator();
		//							ImGui::Spacing();
		//							ImGui::Checkbox(sxor("Prefer body aim"), &ctx.m_settings.aimbot_prefer_body);							}
		//						ImGui::EndChild();
		//						ImGui::NextColumn();
		//						ImGui::BeginChild("##ragebotedges");
		//						{
		//							constexpr auto sliders_size = 135.f;
		//							ImGui::Text("MultiPoint");
		//							ImGui::Checkbox(sxor("Head"), &ctx.m_settings.aimbot_multipoint[0]);
		//							if (ctx.m_settings.aimbot_multipoint[0])
		//							{
		//								cursor_pos_y = ImGui::GetCursorPosY();

		//								ImGui::SetCursorPosY(cursor_pos_y + 8);
		//								ImGui::PushItemWidth(sliders_size);
		//								ImGui::SliderInt(sxor("##Headscale"), &ctx.m_settings.aimbot_pointscale[0], 1, 100);
		//								ImGui::PopItemWidth();
		//								ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
		//								ImGui::Spacing();								
		//								ImGui::Spacing();
		//								ImGui::Spacing();

		//							}
		//							ImGui::Checkbox(sxor("Chest"), &ctx.m_settings.aimbot_multipoint[1]);
		//							if (ctx.m_settings.aimbot_multipoint[1])
		//							{
		//								cursor_pos_y = ImGui::GetCursorPosY();

		//								ImGui::SetCursorPosY(cursor_pos_y + 8);
		//								ImGui::PushItemWidth(sliders_size);
		//								ImGui::SliderInt(sxor("##chestscale"), &ctx.m_settings.aimbot_pointscale[1], 1, 100);
		//								ImGui::PopItemWidth();
		//								ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);	

		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//							}
		//							ImGui::Checkbox(sxor("Body"), &ctx.m_settings.aimbot_multipoint[2]);
		//							if (ctx.m_settings.aimbot_multipoint[2])
		//							{
		//								cursor_pos_y = ImGui::GetCursorPosY();

		//								ImGui::SetCursorPosY(cursor_pos_y + 8);
		//								ImGui::PushItemWidth(sliders_size);
		//								ImGui::SliderInt(sxor("##bodyscale"), &ctx.m_settings.aimbot_pointscale[2], 1, 100);
		//								ImGui::PopItemWidth();
		//								ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
		//							

		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//							}
		//							ImGui::Checkbox(sxor("Arms"), &ctx.m_settings.aimbot_multipoint[3]);
		//							if (ctx.m_settings.aimbot_multipoint[3])
		//							{
		//								cursor_pos_y = ImGui::GetCursorPosY();

		//								ImGui::SetCursorPosY(cursor_pos_y + 8);
		//								ImGui::PushItemWidth(sliders_size);
		//								ImGui::SliderInt(sxor("##armsscale"), &ctx.m_settings.aimbot_pointscale[3], 1, 100);
		//								ImGui::PopItemWidth();

		//								ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//							}
		//							ImGui::Checkbox(sxor("Legs"), &ctx.m_settings.aimbot_multipoint[4]);
		//							if (ctx.m_settings.aimbot_multipoint[4])
		//							{
		//								cursor_pos_y = ImGui::GetCursorPosY();

		//								ImGui::SetCursorPosY(cursor_pos_y + 8);
		//								ImGui::PushItemWidth(sliders_size);
		//								ImGui::SliderInt(sxor("##legsscale"), &ctx.m_settings.aimbot_pointscale[4], 1, 100);
		//								ImGui::PopItemWidth();

		//								ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//							}
		//							ImGui::Checkbox(sxor("Feet"), &ctx.m_settings.aimbot_multipoint[5]);
		//							if (ctx.m_settings.aimbot_multipoint[5])
		//							{
		//								cursor_pos_y = ImGui::GetCursorPosY();

		//								ImGui::SetCursorPosY(cursor_pos_y + 8);
		//								ImGui::PushItemWidth(sliders_size);
		//								ImGui::SliderInt(sxor("##feetscale"), &ctx.m_settings.aimbot_pointscale[5], 1, 100);
		//								ImGui::PopItemWidth();

		//								ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//								ImGui::Spacing();
		//							}
		//						}
		//						ImGui::EndChild();
		//					}
		//					ImGui::EndChild();
		//				}
		//				ImGui::NextColumn();
		//				{
		//					ImGui::BeginChild("##ragebotaa");
		//					{
		//						ImGui::Checkbox(sxor("Anti-Aim"), &ctx.m_settings.anti_aim_enabled);
		//						ImGui::Text("Pitch");
		//						ImGui::Combo("##typexAA", &ctx.m_settings.anti_aim_typex, "Off\0Down\0Up\0Zero");
		//						ImGui::Text("Yaw");
		//						ImGui::Combo("##typeyAA", &ctx.m_settings.anti_aim_typey, "Off\0Backwards\0Zero\0Lby Twist\0Spin\0");
		//						ImGui::Text("Yaw Jitter");
		//						ImGui::Combo("##YawdJitter", &ctx.m_settings.anti_aim_jittering_type, "Off\0Random\0Static\0");
		//						if (ctx.m_settings.anti_aim_jittering_type != 0)
		//							ImGui::SliderInt("##jittering", &ctx.m_settings.anti_aim_jittering, -90, 90);
		//						ImGui::Text("Desync Type");
		//						ImGui::Combo("##typeyFAA", &ctx.m_settings.anti_aim_typeyfake, "Off\0Static\0Jitter\0Tank\0Onetap\0");
		//						if (ctx.m_settings.anti_aim_typeyfake != 0)
		//							ImGui::SliderInt("", &ctx.m_settings.anti_aim_fake_limit, 0, 60);
		//						ImGui::Text("Invert Anti-Aim");
		//						ImGui::Bind("##fakesidekey", &ctx.m_settings.anti_aim_fake_switch.key, ImVec2(100, 20));
		//						//ImGui::SameLine();
		//						ImGui::Text("body yaw");
		//						ImGui::Combo("##body yaw", &ctx.m_settings.anti_aim_typelby, "opposite\0eye yaw\0");
		//						ImGui::Text("on-shot fake yaw");
		//						ImGui::Combo("##onshotyaw", &ctx.m_settings.anti_aim_typeyfake_shot, "Default\0Opposite\0Cycle\0Alternative\0");
		//						ImGui::Text("At Targets");
		//						ImGui::Checkbox(sxor("Follow by crosshair"), &ctx.m_settings.anti_aim_at_target[0]);
		//						ImGui::Combo("##freestanding body yaw", &ctx.m_settings.anti_aim_freestanding_fake_type,"none\0peeking\0hiding\0");
		//						ImGui::Checkbox(sxor("Swap Desync on Overlap"), &ctx.m_settings.anti_aim_automatic_side[4]);


		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();
		//						ImGui::Checkbox(sxor("Fakelag"), &ctx.m_settings.fake_lag_enabled);
		//						ImGui::Combo("##typeFakelag", &ctx.m_settings.fake_lag_type, "Maximum\0Break\0");
		//						ImGui::SliderInt("value", &ctx.m_settings.fake_lag_value, 0, 16);
		//						ImGui::SliderInt("variance", &ctx.m_settings.fake_lag_variance, 0,100);
		//						ImGui::Spacing();
		//						ImGui::Checkbox(sxor("Fake Lag While Shooting"), &ctx.m_settings.fake_lag_shooting);
		//						ImGui::Checkbox(sxor("Fake Lag On Peek"), &ctx.m_settings.fake_lag_peek);
		//						ImGui::Checkbox(sxor("Lag Compensation Breaker"), &ctx.m_settings.fake_lag_lag_compensation);
		//						ImGui::Checkbox(sxor("Desync Client Side"), &ctx.m_settings.fake_lag_special);

		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();
		//						
		//						ImGui::Text("Doubletap");
		//						ImGui::SameLine();
		//						ImGui::Bind("##DTkey", &ctx.m_settings.aimbot_doubletap_exploit_toggle.key, ImVec2(100, 20));
		//						ImGui::Combo("##dt mode", &ctx.m_settings.aimbot_doubletap_method, "Defensive\0Instant\0");
		//						ImGui::SliderInt("DT Hitchance", &ctx.m_settings.aimbot_doubletap_hitchance_val, 0, 80);
		//						ImGui::Checkbox(sxor("Extend Teleport"), &ctx.m_settings.aimbot_extra_doubletap_options[0]);
		//						ImGui::Checkbox(sxor("Stop Before 2nd Shot"), &ctx.m_settings.aimbot_extra_doubletap_options[1]);

		//						ImGui::Text("HideShots");
		//						ImGui::SameLine();
		//						ImGui::Bind("##Hideshotskey", &ctx.m_settings.aimbot_hideshots_exploit_toggle.key, ImVec2(100, 20));
		//						ImGui::Spacing();

		//						ImGui::Text("Damage Override");
		//						ImGui::SameLine();
		//						ImGui::Bind("##DMGkey", &ctx.m_settings.aimbot_min_damage_override.key, ImVec2(100, 20));
		//						ImGui::SliderInt(sxor("##Keymindamage"), &ctx.m_settings.aimbot_min_damage_override_val, 0, 101);

		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();

		//						ImGui::Checkbox(sxor("Quick stop"), &ctx.m_settings.aimbot_autostop);
		//						ImGui::Checkbox(sxor("Between shoots"), &ctx.m_settings.autostop_only_when_shooting);
		//						ImGui::Checkbox(sxor("Force Accuracy"), &ctx.m_settings.autostop_force_accuracy);
		//						ImGui::Combo("##autostop", &ctx.m_settings.autostop_type, "Slow motion\0Full Stop\0");

		//					}
		//					ImGui::EndChild();
		//				}
		//				ImGui::Columns(1);

		//				break;
		//			case 1:
		//				
		//				ImGui::PushItemWidth(110.0f);
		//				ImGui::PushID(0);
		//				ImGui::Combo("", &currentCategory, "Global\0Pistols\0Heavy\0SMG\0Rifles\0");
		//				ImGui::PopID();
		//				ImGui::SameLine();
		//				ImGui::PushID(1);

		//				switch (currentCategory) {
		//				case 0:
		//					currentWeapon = 0;
		//					ImGui::NewLine();
		//					break;
		//				case 1: {
		//					static int currentPistol{ 0 };
		//					static constexpr const char* pistols[]{ "Global", "Glock-18", "P2000", "USP-S", "Dual Berettas", "P250", "Tec-9", "Five-Seven", "CZ-75", "Desert Eagle", "Revolver" };

		//					ImGui::Combo("", &currentPistol, [](void* data, int idx, const char** out_text) {
		//						if (ctx.m_settings.aimbot[idx ? idx : 35].enabled) {
		//							static std::string name;
		//							name = pistols[idx];
		//							*out_text = name.append(" *").c_str();
		//						}
		//						else {
		//							*out_text = pistols[idx];
		//						}
		//						return true;
		//						}, nullptr, IM_ARRAYSIZE(pistols));

		//					currentWeapon = currentPistol ? currentPistol : 35;
		//					break;
		//				}
		//				case 2: {
		//					static int currentHeavy{ 0 };
		//					static constexpr const char* heavies[]{ "Global", "Nova", "XM1014", "Sawed-off", "MAG-7", "M249", "Negev" };

		//					ImGui::Combo("", &currentHeavy, [](void* data, int idx, const char** out_text) {
		//						if (ctx.m_settings.aimbot[idx ? idx + 10 : 36].enabled) {
		//							static std::string name;
		//							name = heavies[idx];
		//							*out_text = name.append(" *").c_str();
		//						}
		//						else {
		//							*out_text = heavies[idx];
		//						}
		//						return true;
		//						}, nullptr, IM_ARRAYSIZE(heavies));

		//					currentWeapon = currentHeavy ? currentHeavy + 10 : 36;
		//					break;
		//				}
		//				case 3: {
		//					static int currentSmg{ 0 };
		//					static constexpr const char* smgs[]{ "Global", "Mac-10", "MP9", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon" };

		//					ImGui::Combo("", &currentSmg, [](void* data, int idx, const char** out_text) {
		//						if (ctx.m_settings.aimbot[idx ? idx + 16 : 37].enabled) {
		//							static std::string name;
		//							name = smgs[idx];
		//							*out_text = name.append(" *").c_str();
		//						}
		//						else {
		//							*out_text = smgs[idx];
		//						}
		//						return true;
		//						}, nullptr, IM_ARRAYSIZE(smgs));

		//					currentWeapon = currentSmg ? currentSmg + 16 : 37;
		//					break;
		//				}
		//				case 4: {
		//					static int currentRifle{ 0 };
		//					static constexpr const char* rifles[]{ "Global", "Galil AR", "Famas", "AK-47", "M4A4", "M4A1-S", "SSG-08", "SG-553", "AUG", "AWP", "G3SG1", "SCAR-20" };

		//					ImGui::Combo("", &currentRifle, [](void* data, int idx, const char** out_text) {
		//						if (ctx.m_settings.aimbot[idx ? idx + 23 : 38].enabled) {
		//							static std::string name;
		//							name = rifles[idx];
		//							*out_text = name.append(" *").c_str();
		//						}
		//						else {
		//							*out_text = rifles[idx];
		//						}
		//						return true;
		//						}, nullptr, IM_ARRAYSIZE(rifles));

		//					currentWeapon = currentRifle ? currentRifle + 23 : 38;
		//					break;
		//				}
		//				}
		//				ImGui::PopID();
		//				ImGui::SameLine();
		//				ImGui::Checkbox("Enabled", &ctx.m_settings.aimbot[currentWeapon].enabled);
		//				ImGui::Separator();
		//				ImGui::Columns(2, nullptr, false);
		//				ImGui::SetColumnOffset(1, 220.0f);

		//				ImGui::Checkbox("Silent", &ctx.m_settings.aimbot[currentWeapon].silent);
		//				ImGui::Checkbox("Auto Delay", &ctx.m_settings.aimbot[currentWeapon].autodelay);
		//				ImGui::Checkbox("Friendly fire", &ctx.m_settings.aimbot[currentWeapon].friendlyFire);
		//				ImGui::Checkbox("Visible only", &ctx.m_settings.aimbot[currentWeapon].visibleOnly);
		//				ImGui::Checkbox("Scoped only", &ctx.m_settings.aimbot[currentWeapon].scopedOnly);
		//				ImGui::Checkbox("Ignore flash", &ctx.m_settings.aimbot[currentWeapon].ignoreFlash);
		//				ImGui::Checkbox("Ignore smoke", &ctx.m_settings.aimbot[currentWeapon].ignoreSmoke);
		//				ImGui::Combo("Bone", &ctx.m_settings.aimbot[currentWeapon].bone, "Nearest\0Best damage\0Head\0Neck\0Sternum\0Chest\0Stomach\0Pelvis\0");
		//				ImGui::NextColumn();
		//				ImGui::PushItemWidth(240.0f);
		//				ImGui::SliderFloat("Fov", &ctx.m_settings.aimbot[currentWeapon].fov, 0.0f, 20.0f, "%.2f");
		//				ImGui::SliderFloat("Smooth", &ctx.m_settings.aimbot[currentWeapon].smooth, 1.0f, 100.0f, "%.2f");
		//				ImGui::SliderFloat("Rcs Fov", &ctx.m_settings.aimbot[currentWeapon].rcsfov, 1.0f, 100.0f, "%.2f");
		//				ImGui::SliderFloat("Silent Fov", &ctx.m_settings.aimbot[currentWeapon].silentfov, 1.0f, 100.0f, "%.2f");
		//				ImGui::SliderFloat("Kill Delay", &ctx.m_settings.aimbot[currentWeapon].killdelay, 0.0f, 5.0f, "%.2f");
		//				ImGui::Columns(1);

		//				break;
		//			case 2:
		//				ImGui::Columns(2, NULL, true);
		//				{
		//					ImGui::BeginChild("##visualsplayers");
		//					ImGui::Checkbox("Visuals enabled", &ctx.m_settings.visuals_enabled);
		//					ImGui::Checkbox("Dormant", &ctx.m_settings.esp_dormant);
		//					ImGui::Checkbox("Offscreen arrows", &ctx.m_settings.esp_offscreen);
		//					ImGui::ColorPickerBox("#nigarrows", ctx.m_settings.colors_esp_offscreen, nullptr, nullptr, nullptr);
		//					ImGui::Checkbox("Name", &ctx.m_settings.esp_name);
		//					ImGui::ColorPickerBox("#nigname", ctx.m_settings.colors_esp_name, nullptr, nullptr, nullptr);
		//					ImGui::Checkbox("Health", &ctx.m_settings.esp_health);
		//					ImGui::ColorPickerBox("#nighealth", ctx.m_settings.colors_esp_health, nullptr, nullptr, nullptr);
		//					ImGui::Checkbox("Weapon", &ctx.m_settings.esp_weapon);
		//					ImGui::Checkbox("Weapon ammo", &ctx.m_settings.esp_weapon);
		//					ImGui::ColorPickerBox("#nigammo", ctx.m_settings.colors_esp_ammo, nullptr, nullptr, nullptr);
		//					ImGui::Checkbox("Skeleton", &ctx.m_settings.esp_skeleton);
		//					ImGui::ColorPickerBox("#nigton", ctx.m_settings.colors_skeletons_enemy, nullptr, nullptr, nullptr);

		//					ImGui::Checkbox("Glow ESP", &ctx.m_settings.esp_glow);
		//					ImGui::SameLine();
		//					ImGui::Checkbox("Color based on hp", &ctx.m_settings.colors_glow_hp);
		//					ImGui::ColorPickerBox("#nigglow", ctx.m_settings.colors_glow_enemy, nullptr, nullptr, nullptr);
		//					ImGui::Spacing();
		//					ImGui::Separator();
		//					ImGui::Spacing();
		//					ImGui::Checkbox("Penetration crosshair", &ctx.m_settings.visuals_autowall_crosshair);
		//					ImGui::Checkbox("Bullet impacts", &ctx.m_settings.visuals_draw_local_impacts);
		//					ImGui::Checkbox("Grenade Prediction", &ctx.m_settings.misc_grenade_preview);
		//		
		//					ImGui::Checkbox("Hitmarker", &ctx.m_settings.misc_visuals_indicators_2[0]);
		//					ImGui::SameLine();
		//					ImGui::Checkbox("Hitsound", &ctx.m_settings.misc_hitsound_type);
		//					ImGui::Spacing();
		//					ImGui::Separator();
		//					ImGui::Spacing();
		//					ImGui::Checkbox("Remove visual recoil", &ctx.m_settings.visuals_no_recoil);
		//					ImGui::Checkbox("Remove ingame post processing", &ctx.m_settings.visuals_no_postprocess);
		//					ImGui::Checkbox("Remove scope", &ctx.m_settings.visuals_no_scope);
		//					ImGui::Checkbox("Remove 1st zoom level", &ctx.m_settings.visuals_no_first_scope);
		//					ImGui::Checkbox("Remove smoke", &ctx.m_settings.visuals_no_smoke);
		//					ImGui::Checkbox("Remove flash", &ctx.m_settings.visuals_no_flash);
		//					ImGui::Checkbox("Override fov", &ctx.m_settings.misc_override_fov);
		//					ImGui::SameLine();
		//					cursor_pos_y = ImGui::GetCursorPosY();

		//					ImGui::SetCursorPosY(cursor_pos_y + 8);
		//					ImGui::SliderInt("##oFov", &ctx.m_settings.misc_override_fov_val, -20, 60);
		//					ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
		//					ImGui::EndChild();
		//				}
		//				ImGui::NextColumn();
		//				{
		//					ImGui::BeginChild("##visualsworld");
		//					{
		//					//	ImGui::Spacing();
		//						ImGui::Checkbox("Show Weapons", &ctx.m_settings.esp_world_weapons);
		//						ImGui::Checkbox("Show grenades", &ctx.m_settings.esp_world_nades);
		//						ImGui::Checkbox("Show c4/hostage", &ctx.m_settings.esp_world_bomb);
		//						ImGui::Checkbox("Nightmode", &ctx.m_settings.misc_visuals_world_modulation[1]);
		//						ImGui::ColorPickerBox("#nigmode", ctx.m_settings.colors_world_color, nullptr, nullptr, nullptr);
		//						ImGui::Checkbox("Fullbright", &ctx.m_settings.misc_visuals_world_modulation[0]);
		//						ImGui::SliderInt("Prop alpha", &ctx.m_settings.visuals_props_alpha, 0, 100);

		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();

		//						ImGui::Checkbox("Local bullets tracer", &ctx.m_settings.visuals_draw_local_beams);//local_beams_color
		//						ImGui::ColorPickerBox("#nigtrace", ctx.m_settings.local_beams_color, nullptr, nullptr, nullptr);
		//						ImGui::Checkbox(sxor("Force crosshair"), &ctx.m_settings.visuals_force_crosshair);
		//						ImGui::Checkbox(sxor("Force Enemy On Radar"), &ctx.m_settings.misc_engine_radar);

		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();

		//						ImGui::Checkbox("Visible Chams", &ctx.m_settings.chams_enemy);
		//						ImGui::ColorPickerBox("#nigchamviable", ctx.m_settings.colors_chams_enemy_viable, nullptr, nullptr, nullptr);
		//						ImGui::Checkbox("Behind Wall", &ctx.m_settings.chams_walls);
		//						ImGui::ColorPickerBox("#nigchamshidden", ctx.m_settings.colors_chams_enemy_hidden, nullptr, nullptr, nullptr);
		//						ImGui::Checkbox("Local Model", &ctx.m_settings.chams_local_player);
		//						ImGui::ColorPickerBox("#nigchamslocal", ctx.m_settings.colors_chams_local, nullptr, nullptr, nullptr);
		//						ImGui::Text(sxor("Override player material"));
		//						ImGui::Combo("##playamaterial", &ctx.m_settings.menu_chams_type, "Flat\0Filled\0Glowing\0Model Glowing\0");
		//						ImGui::Spacing();

		//						ImGui::SliderInt("Local scope alpha", &ctx.m_settings.scope_transparency, 0, 100);

		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();
		//						ImGui::Checkbox(sxor("Spectator list"), &ctx.m_settings.visuals_extra_windows[0]);
		//						ImGui::Checkbox(sxor("Keybinds"), &ctx.m_settings.visuals_extra_windows[1]);
		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();

		//					}
		//					ImGui::EndChild();
		//				}
		//				ImGui::Columns(1);


		//				break;

		//			case 3:
		//			{
		//				static auto selected_item = 0;
		//				static auto fake_wear = 1.f;
		//				static auto fake_seed = 0;
		//				static char fake_name[256] = "";
		//				static auto fake_stattrak = false;
		//				static auto fake_stattrak_value = 0;

		//				//if (ImGui::Begin("Skin changer")
		//				//{
		//				ImGui::Page::Begin(3);
		//				ImGui::PushItemWidth(ImGui::GetCurrentWindow()->Size.x);

		//				ImGui::ListBox(sxor("##weapons"), &selected_item, items_getter<weapon_t>, (void*)parser::weapons.list.data(), parser::weapons.list.size(), 22);

		//				ImGui::PopItemWidth();
		//				ImGui::Page::Next();
		//				ImGui::PushItemWidth(ImGui::GetCurrentWindow()->Size.x);

		//				static bool show_all_skins = false;
		//				//ImGui::Checkbox("All skins", &show_all_skins);

		//				static char filter_buffer[64] = "";
		//				ImGui::InputText(sxor("##filter"), filter_buffer, 64);

		//				// draw rarities
		//				static auto selected_rarity = 0;
		//				{
		//					static auto draw_rarity = [](rarity_t& rarity, int& selected_rarity, const float& alpha) {

		//						bool selected = false;
		//						auto size = ImVec2(12, 8);

		//						auto rarity_col = rarity.Color.alpha(alpha * 255);

		//						ImGui::PushStyleColor(ImGuiCol_Button, selected_rarity == rarity.id ? (ImVec4)rarity_col : (ImVec4)rarity_col.malpha(0.3f)); //40 ����� ����
		//						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)rarity_col.malpha(0.7f));
		//						ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)rarity_col.malpha(0.7f));

		//						if (ImGui::Button(("##" + rarity.name).data(), size))
		//							selected_rarity = rarity.id;

		//						ImGui::PopStyleColor(3);
		//						ImGui::SameLine(/*0.f, 10.4f*/);

		//					};

		//					for (auto& rarity : parser::rarities.list) {
		//						draw_rarity(rarity, selected_rarity, alpha);
		//					}

		//					ImGui::NewLine();
		//				}

		//				auto selected_weapon = parser::weapons.list[selected_item].id;
		//				auto selected_skin = 0;
		//				/*for (auto i = 0u; i < parser::weapons.list[selected_item].skins.list.size(); i++)
		//				{
		//					auto skin = parser::weapons.list[selected_item].skins.list[i];
		//					if (skin.id == cheat::settings.paint[selected_weapon])
		//						selected_skin = i;
		//				}*/
		//				auto old_skin = selected_skin;

		//				if (!parser::weapons.list.empty())
		//					skins_listbox(sxor("##skins"), std::string(filter_buffer), selected_rarity, &selected_skin, parser::weapons.list[selected_item].skins, 20, alpha);

		//				//if (selected_skin != old_skin) {
		//				//	ctx.m_settings.paint[selected_weapon] = parser::weapons.list[selected_item].skins.list[selected_skin].id;
		//				//	//game::full_update();
		//				//}

		//				ImGui::PopItemWidth();
		//				ImGui::Page::Next();
		//				ImGui::PushItemWidth(ImGui::GetCurrentWindow()->Size.x);

		//				ImGui::SliderFloat(sxor("wear"), &fake_wear, 0.f, 1.f);
		//				ImGui::Spacing();

		//				ImGui::Text(sxor("seed"));
		//				ImGui::InputInt(sxor("##_seed"), &fake_seed);
		//				ImGui::Spacing();

		//				ImGui::Checkbox(sxor("stat trak"), &fake_stattrak);
		//				if (fake_stattrak) {
		//					ImGui::InputInt(sxor("##_stattrak_value"), &fake_stattrak_value);
		//				}
		//				ImGui::Spacing();

		//				ImGui::Text(sxor("name"));
		//				ImGui::InputText(sxor("##_name"), fake_name, 256);
		//				ImGui::Spacing();

		//				static auto selected_knife = 0;
		//				static std::vector<knife_t> knife_list;
		//				if (knife_list.empty())
		//				{
		//					knife_list = parser::knifes.list;

		//					knife_t default_knife;
		//					default_knife.id = 0;
		//					default_knife.translated_name = L"Default";
		//					knife_list.insert(knife_list.begin(), default_knife);
		//				}

		//				if (ImGui::ListBox("##knife_changer", &selected_knife, items_getter<knife_t>, (void*)knife_list.data(), knife_list.size(), 6))
		//				{
		//					auto new_id = knife_list[selected_knife].id;
		//					ctx.m_settings.skinchanger_knife = new_id;
		//					//game::full_update();
		//				}

		//				ImGui::PopItemWidth();
		//				ImGui::Page::End();

		//				//}
		//				//ImGui::End();
		//			}break;
		//			case 4:
		//			{
		//				ImGui::Columns(2, NULL, true);
		//				{
		//					ImGui::BeginChild("##misclocal");
		//					{
		//						ImGui::Checkbox(sxor("Auto bhop"), &ctx.m_settings.misc_bhop); 

		//						ImGui::Checkbox(sxor("skinchanger"), &ctx.m_settings.skinchanger_enabled);
		//						ImGui::Combo("##slowwalkd", &ctx.m_settings.skinchanger_knife, "Favor Desyncsd\0Favor Random\0");
		//						ImGui::Combo("##slowwalak", &ctx.m_settings.skinchanger_knife_skin, "Favor Desync\0Favor Random\0");

		//						ImGui::Checkbox(sxor("Auto strafe"), &ctx.m_settings.misc_autostrafer);
		//						ImGui::SameLine();
		//						ImGui::Checkbox(sxor("WASD"), &ctx.m_settings.misc_autostrafer_wasd);
		//						ImGui::Spacing();
		//						ImGui::Checkbox(sxor("In-game Inventory"), &ctx.m_settings.misc_unlock_inventory);
		//						ImGui::Checkbox(sxor("Left Hand Knife"), &ctx.m_settings.misc_knife_hand_switch);
		//						ImGui::Checkbox(sxor("Preserve killfeed"), &ctx.m_settings.misc_preserve_killfeed);
		//						ImGui::SliderInt(sxor("Aspect Ratio"), &ctx.m_settings.misc_aspect_ratio, 0, 100);
		//						ImGui::Spacing();
		//						ImGui::Checkbox(sxor("Thirdperson"), &ctx.m_settings.visuals_tp_force);
		//						ImGui::SameLine();
		//						ImGui::Bind("##tpkey", &ctx.m_settings.visuals_tp_key.key, ImVec2(100, 20));

		//						if (ctx.m_settings.visuals_tp_force)
		//						ImGui::SliderInt(sxor("##tpdistance"), &ctx.m_settings.visuals_tp_dist, 30, 300);
		//						ImGui::Spacing();
		//						ImGui::Text(sxor("Auto peek"));
		//						ImGui::Bind("##apkey", &ctx.m_settings.anti_aim_autopeek_key.key, ImVec2(100, 20));
		//						ImGui::Spacing();
		//						ImGui::Text(sxor("Fakeduck"));
		//						ImGui::Bind("##fdkey", &ctx.m_settings.anti_aim_fakeduck_key.key, ImVec2(100, 20));
		//						//ImGui::Text(sxor("Slowwalk Key"));
		//						//ImGui::Bind("##slowwalk", &ctx.m_settings._anti_aim_slowwalk_key, ImVec2(100, 20));
		//						//ImGui::Text(sxor("Slowwalk"));
		//						//ImGui::Combo("##slowwalk", &ctx.m_settings.anti_aim_slow_walk_types, "Favor Desync\0Favor Random\0");
		//						//ImGui::SliderInt("slow walk limit", &ctx.m_settings.anti_aim_slow_walk_speed, 0, 100);
		//						//ImGui::SliderInt("speed desync amount", &ctx.m_settings.anti_aim_slow_walk_desync, 0, 100);
		//						ImGui::Combo(sxor("Leg movement"), &ctx.m_settings.anti_aim_leg_movement, "Default\0Always Slide\0Never Slide\0LedSync");

		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();

		//						ImGui::Checkbox(sxor("Log misses"), &ctx.m_settings.misc_notifications[2]);
		//						ImGui::SameLine();
		//						ImGui::Checkbox(sxor("Log shots"), &ctx.m_settings.misc_notifications[3]);
		//						
		//						ImGui::Checkbox(sxor("Log damage"), &ctx.m_settings.misc_notifications[1]);
		//						ImGui::SameLine();
		//						ImGui::Checkbox(sxor("Log purchases"), &ctx.m_settings.misc_notifications[4]);
		//						//ImGui::MultiCombo(sxor("notifications"), &ctx.m_settings.misc_autobuy_secondary, "bomb info\0 damage given\0miss\0shot debug\0purchases\0damage received");
		//						ImGui::Spacing();
		//						ImGui::Separator();
		//						ImGui::Spacing();

		//						ImGui::Checkbox(sxor("Autobuy"), &ctx.m_settings.misc_autobuy_enabled);
		//						if (ctx.m_settings.misc_autobuy_enabled) {
		//							ImGui::Text(sxor("Autobuy primary"));
		//							ImGui::Combo(sxor("##Autoprimary"), &ctx.m_settings.misc_autobuy_primary, "none\0AK47/M4A1\0AWP\0SCAR20/G3\0SSG-08\0\0");
		//							ImGui::Text(sxor("Autobuy secondary"));
		//							ImGui::Combo(sxor("##Autoecondary"), &ctx.m_settings.misc_autobuy_secondary, "none\0Deagle/R8\0Tec9/FiveSeven\0Dual berettas\0P250/CZ-74\0");
		//							ImGui::Separator();
		//						
		//							ImGui::Text(sxor("minimum money"));
		//							ImGui::SliderInt(sxor("##musor"), &ctx.m_settings.misc_autobuy_money_limit, 0, 10000);
		//							ImGui::Spacing();
		//							ImGui::Separator();
		//							ImGui::Checkbox(sxor("HE"), &ctx.m_settings.misc_autobuy_etc[4]);
		//							ImGui::SameLine();
		//							ImGui::Checkbox(sxor("Smoke"), &ctx.m_settings.misc_autobuy_etc[3]);
		//							ImGui::SameLine();
		//							ImGui::Checkbox(sxor("Flash"), &ctx.m_settings.misc_autobuy_etc[5]);
		//							ImGui::SameLine();
		//							ImGui::Checkbox(sxor("Molotov"), &ctx.m_settings.misc_autobuy_etc[7]);
		//							ImGui::Separator();
		//							ImGui::Checkbox(sxor("Armor"), &ctx.m_settings.misc_autobuy_etc[1]);
		//							ImGui::SameLine();
		//							ImGui::Checkbox(sxor("Taser"), &ctx.m_settings.misc_autobuy_etc[0]);
		//							ImGui::SameLine();
		//							ImGui::Checkbox(sxor("Kit"), &ctx.m_settings.misc_autobuy_etc[2]);
		//						}
		//					}
		//					ImGui::EndChild();
		//				}
		//				ImGui::NextColumn();
		//				{
		//					ImGui::BeginChild("##cfgmisc");
		//					{

		//						ImGui::Text(sxor("CFGS"));
		//						ImGui::Combo("##cfgselct", &g_settings.cur_cfg, "Legit\0Rage\0Hvh\0MM hvh\0Semi-rage\0");

		//						if (ImGui::Button(sxor("Save")))
		//							feature::misc->save_cfg();

		//						if (ImGui::Button(sxor("Load"))) {
		//							feature::misc->load_cfg();
		//							if (ctx.m_settings.skinchanger_enabled) ctx.updated_skin = true;
		//						}

		//						ImGui::Spacing();
		//						ImGui::Spacing();
		//						ImGui::Spacing();

		//						if (ImGui::Button(sxor("Reset")))
		//						{
		//							const size_t settings_size = sizeof(c_variables);
		//							for (int i = 0; i < settings_size; i++)
		//							{
		//								byte &current_byte = *reinterpret_cast<byte*>(uintptr_t(&ctx.m_settings) + i);
		//								current_byte = 0;
		//							}

		//							//#TODO def settings
		//						}
		//					}
		//					ImGui::EndChild();
		//				}
		//				ImGui::Columns(1);
		//				break;
		//			}
		//			default:
		//				break;
		//			}

		//			ImGui::EndChild();
		//		}

		//		was_hovered = is_hovered;
		//	}

		//	if (alpha != 1.f)
		//		init(1.f); //����� ��� ���� �� ������� �������� ���������

		//	ImGui::End();
		//}
	}
}