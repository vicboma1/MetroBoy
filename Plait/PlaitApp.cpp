#include "Plait/PlaitApp.h"
#include "AppLib/GLBase.h"

#include "AppLib/AppHost.h"
#include "AppLib/GLBase.h"

#include "Plait/CellDB.h"

#include "imgui/imgui.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <deque>
#include <algorithm>
#include <filesystem>
#include <sstream>

//#include <windows.h>

using namespace std;

static std::map<ToolMode, std::string> tool_to_string = {
  {ToolMode::NONE,            "NONE"},
  {ToolMode::IMGUI,           "IMGUI"},
  {ToolMode::DRAG_NODE,       "DRAG_NODE"},
  {ToolMode::SELECT_REGION,   "SELECT_REGION"},
  {ToolMode::LOCK_REGION,     "LOCK_REGION"},
  {ToolMode::UNLOCK_REGION,   "UNLOCK_REGION"},
  {ToolMode::GHOST_REGION,    "GHOST_REGION"},
  {ToolMode::PLACE_ANCHOR,    "PLACE_ANCHOR"},
  {ToolMode::PAN_VIEW,        "PAN_VIEW"},
  {ToolMode::MENU_OPTION,     "MENU_OPTION"},
  {ToolMode::SPLIT_CELL,      "SPLIT_CELL"},
  {ToolMode::MERGE_CELL,      "MERGE_CELL"},
};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  int ret = 0;

  const char* die_db_file = "gameboy.die_db.json";
  (void)die_db_file;

  PlaitApp* app = new PlaitApp();

#if 0
  printf("Parsing gateboy source\n");
  app->die_db.parse_dir("GateBoyLib");
  printf("Done\n\n");

  {
    printf("Saving cell db\n");
    //std::ostringstream stream_out;
    //app->die_db.save_json(stream_out);
    app->die_db.save_json(die_db_file);
    printf("Done\n\n");

    printf("Loading gameboy.die_db.json\n");
    app->die_db.clear();
    //std::istringstream stream_in(stream_out.str());
    //app->die_db.load_json(stream_in);
    app->die_db.load_json(die_db_file);
    printf("Done\n\n");
  }

  /*
  {
    printf("Loading gameboy.plait.json\n");
    app->plait.load_json("gameboy.plait.json", app->die_db);
    printf("Done\n\n");


    printf("Saving plait\n");
    //std::ostringstream stream_out;
    app->plait.save_json("gameboy.plait_hax.json");
    printf("Done\n\n");

    printf("Loading plait\n");
    //std::istringstream stream_in(stream_out.str());
    app->plait.clear();
    app->plait.load_json("gameboy.plait_hax.json", app->die_db);
    printf("Done\n\n");
  }
  */

#else
  printf("Loading gameboy.die_db.json\n");
  app->die_db.clear();
  app->die_db.load_json("gameboy.die_db.json");
  printf("Done\n\n");

  printf("Loading gameboy.plait.json\n");
  app->plait.load_json("gameboy.plait.json", app->die_db);
  printf("Done\n\n");


  size_t total_nodes = 0;
  for (auto& [tag, plait_cell] : app->plait.cell_map) {
    total_nodes += plait_cell->nodes.size();
  }
  printf("Total cells %zd\n", app->plait.cell_map.size());
  printf("Total nodes %zd\n", total_nodes);
  printf("Total edges %zd\n", app->plait.trace_map.size());

  AppHost* app_host = new AppHost(app);
  ret = app_host->app_main(argc, argv);
  delete app;
#endif

  return ret;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

PlaitApp::PlaitApp() {
  auto& n2c = node_type_to_color;

  n2c["not1"]  = COL_MID_GREY;

  n2c["and2"]  = COL_MID_RED;
  n2c["and3"]  = COL_MID_RED;
  n2c["and4"]  = COL_MID_RED;

  n2c["nand2"] = COL_MID_RED - COL_HINT1;
  n2c["nand3"] = COL_MID_RED - COL_HINT1;
  n2c["nand4"] = COL_MID_RED - COL_HINT1;
  n2c["nand5"] = COL_MID_RED - COL_HINT1;
  n2c["nand6"] = COL_MID_RED - COL_HINT1;
  n2c["nand7"] = COL_MID_RED - COL_HINT1;

  n2c["or2"]   = COL_MID_BLUE;
  n2c["or3"]   = COL_MID_BLUE;
  n2c["or4"]   = COL_MID_BLUE;

  n2c["nor2"]  = COL_MID_BLUE - COL_HINT1;
  n2c["nor3"]  = COL_MID_BLUE - COL_HINT1;
  n2c["nor4"]  = COL_MID_BLUE - COL_HINT1;
  n2c["nor5"]  = COL_MID_BLUE - COL_HINT1;
  n2c["nor6"]  = COL_MID_BLUE - COL_HINT1;
  n2c["nor7"]  = COL_MID_BLUE - COL_HINT1;
  n2c["nor8"]  = COL_MID_BLUE - COL_HINT1;

  n2c["and_or3"]     = COL_MID_MAGENTA;
  n2c["or_and3"]     = COL_MID_MAGENTA;
  n2c["not_or_and3"] = COL_MID_MAGENTA - COL_HINT1;

  n2c["add_s"] = COL_AZURE;
  n2c["add_c"] = COL_AZURE;

  n2c["xor2"]  = COL_MINT;
  n2c["xnor2"] = COL_MINT;

  n2c["mux2n"] = COL_ROSE - COL_HINT1;
  n2c["mux2p"] = COL_ROSE + COL_HINT1;
  n2c["amux2"] = COL_ROSE;
  n2c["amux4"] = COL_ROSE;
}

PlaitApp::~PlaitApp() {
}

const char* PlaitApp::app_get_title() {
  return "PlaitApp";
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::paint_node(PlaitNode* node) {
  node->color = 0xFFFF00FF;

  auto cell_type = node->plait_cell->die_cell->cell_type;
  if (cell_type == DieCellType::PIN_IN)  node->color = COL_PALE_RED;
  if (cell_type == DieCellType::PIN_OUT) node->color = COL_PALE_GREEN;
  if (cell_type == DieCellType::PIN_IO)  node->color = COL_PALE_YELLOW;

  if (cell_type == DieCellType::SIG_IN)  node->color = COL_MID_RED;
  if (cell_type == DieCellType::SIG_OUT) node->color = COL_MID_GREEN;

  if (cell_type == DieCellType::BUS)     node->color = COL_DARK_GREY;
  if (cell_type == DieCellType::DFF)     node->color = COL_DARK_YELLOW;
  if (cell_type == DieCellType::LATCH)   node->color = COL_ORANGE;
  if (cell_type == DieCellType::TRIBUF)  node->color = COL_MID_YELLOW;
  if (cell_type == DieCellType::ADDER)   node->color = COL_MID_TEAL;

  if (cell_type == DieCellType::LOGIC) {
    auto it = node_type_to_color.find(node->plait_cell->gate());
    if (it != node_type_to_color.end()) {
      node->color = (*it).second;
    }
    else {
      printf("Could not pick a color for %s\n", node->plait_cell->gate());
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::app_init(int screen_w, int screen_h) {
  view_control.init(screen_w, screen_h);

  check_gl_error();
  box_painter.init();
  check_gl_error();
  port_painter.init();
  check_gl_error();
  grid_painter.init();
  check_gl_error();
  edge_painter.init();
  check_gl_error();
  outline_painter.init();
  check_gl_error();
  text_painter.init();
  check_gl_error();
  blitter.init();
  check_gl_error();

  uint32_t pix[] = {
    0xFF00FFFF, 0xFF00FFFF, 0xFF00FFFF, 0xFF00FFFF,
    0xFF00FFFF, 0xFFFF00FF, 0xFFFF00FF, 0xFF00FFFF,
    0xFF00FFFF, 0xFFFF00FF, 0xFFFF00FF, 0xFF00FFFF,
    0xFF00FFFF, 0xFF00FFFF, 0xFF00FFFF, 0xFF00FFFF,
  };

  tex = create_texture_u32(4, 4, pix);

  for (auto& [tag, cell] : plait.cell_map) {
    for (auto& [name, node] : cell->nodes) {
      paint_node(node);
    }
  }

  printf("Init done %f\n", timestamp());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::app_close() {
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

PlaitNode* PlaitApp::pick_node(dvec2 _mouse_pos, bool ignore_selected, bool ignore_clicked, bool ignore_hovered) {
  (void)ignore_selected;
  (void)ignore_clicked;
  (void)ignore_hovered;

  for (auto& [tag, plait_cell] : plait.cell_map) {
    for (auto& [name, node] : plait_cell->nodes) {
      if ((node == clicked_node) && ignore_clicked) continue;
      dvec2 node_pos = node->get_pos_new();

      int width = 128;
      int height = 64;

      if (_mouse_pos.x >= node_pos.x &&
          _mouse_pos.y >= node_pos.y &&
          _mouse_pos.x <= node_pos.x + width &&
          _mouse_pos.y <= node_pos.y + height) {
        return node;
      }
    }
  }

  return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::apply_region_node(dvec2 corner_a, dvec2 corner_b, NodeCallback callback) {

  dvec2 rmin = min(corner_a, corner_b);
  dvec2 rmax = max(corner_a, corner_b);

  const dvec2 node_size = {128,64};

  for (auto& [tag, plait_cell] : plait.cell_map) {
    for (auto& [name, node] : plait_cell->nodes) {
      dvec2 nmin = node->get_pos_new();
      dvec2 nmax = node->get_pos_new() + node_size;

      if (nmin.x < rmin.x) continue;
      if (nmin.y < rmin.y) continue;
      if (nmax.x > rmax.x) continue;
      if (nmax.y > rmax.y) continue;

      callback(node);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::select_region(dvec2 corner_a, dvec2 corner_b) {
  printf("Selection region ");
  auto callback = [this](PlaitNode* node) {
    printf("%s ", node->plait_cell->name());
    node->selected = true;
    node_selection.insert(node);
  };

  apply_region_node(corner_a, corner_b, callback);
  printf("\n");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::select_node(PlaitNode* node) {
  printf("Selecting %s\n", node->plait_cell->name());
  node->selected = true;
  node_selection.insert(node);
}

void PlaitApp::commit_selection() {
  if (node_selection.empty()) return;

  printf("Committing ");
  for (auto node : node_selection) {
    printf("%s ", node->plait_cell->name());
    node->commit_pos();
  }
  printf("\n");
}

void PlaitApp::revert_selection() {
  if (node_selection.empty()) return;

  printf("Reverting ");
  for (auto node : node_selection) {
    printf("%s ", node->plait_cell->name());
    node->revert_pos();
  }
  printf("\n");
}

void PlaitApp::clear_selection() {
  if (node_selection.empty()) return;

  printf("Unselecting ");
  for (auto node : node_selection) {
    printf("%s ", node->plait_cell->name());
    node->selected = false;
  }
  node_selection.clear();
  printf("\n");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

double remap(double x, double a1, double a2, double b1, double b2) {
  x = (x - a1) / (a2 - a1);
  x = x * (b2 - b1) + b1;
  return x;
}

double remap_clamp(double x, double a1, double a2, double b1, double b2) {
  if (x < a1) x = a1;
  if (x > a2) x = a2;

  x = (x - a1) / (a2 - a1);
  x = x * (b2 - b1) + b1;
  return x;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::begin_frame(int screen_w, int screen_h) {
    view_control.begin_frame(screen_w, screen_h);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::event_menu_option(SDL_Event event) {
  switch(event.type) {
  case SDL_KEYDOWN: {
    int key = event.key.keysym.scancode;
    if (key == SDL_SCANCODE_S) {
      printf("Saving plait\n");
      plait.save_json("gameboy.plait.json");
    }
    break;
  }
  case SDL_KEYUP: {
    int key = event.key.keysym.scancode;
    if (key == SDL_SCANCODE_LALT) {
      current_tool = ToolMode::NONE;
    }
    break;
  }
  }
}

//--------------------------------------------------------------------------------

void PlaitApp::event_select_region(SDL_Event event) {
  bool was_drag = length(click_pos_screen - mouse_pos_screen) > 3;

  switch(event.type) {
  case SDL_MOUSEBUTTONDOWN:
    if (clicked_node) {
      select_node(clicked_node);
    }
    break;
  case SDL_MOUSEBUTTONUP: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      if (was_drag) {
        commit_selection();
        clear_selection();
        select_region(click_pos_world, mouse_pos_world);
      }
      else {
        if (clicked_node) {
          select_node(clicked_node);
        }
      }
    }
    break;
  }
  case SDL_KEYUP: {
    int key = event.key.keysym.scancode;
    if (key == SDL_SCANCODE_LCTRL) {
      current_tool = ToolMode::NONE;
    }
    break;
  }
  }
}

//--------------------------------------------------------------------------------

void PlaitApp::event_ghost_region(SDL_Event event) {
  switch(event.type) {
  case SDL_MOUSEBUTTONUP: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      auto callback = [this](PlaitNode* node) {
        node->toggle_ghost();
      };
      apply_region_node(click_pos_world, mouse_pos_world, callback);
    }
    break;
  }
  case SDL_KEYUP: {
    int key = event.key.keysym.scancode;
    if (key == SDL_SCANCODE_Q) {
      current_tool = ToolMode::NONE;
    }
    break;
  }
  }
}

//--------------------------------------------------------------------------------

void PlaitApp::event_split_cell(SDL_Event event) {
  switch(event.type) {
  case SDL_MOUSEBUTTONDOWN: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      commit_selection();
      clear_selection();
      if (clicked_node) {
        plait.split_node(clicked_node);
        clicked_node = nullptr;
      }
    }
    break;
  }
  case SDL_KEYUP: {
    int key = event.key.keysym.scancode;
    if (key == SDL_SCANCODE_Z) {
      current_tool = ToolMode::NONE;
    }
    break;
  }
  }
}

//--------------------------------------------------------------------------------

void PlaitApp::event_merge_cell(SDL_Event event) {
  switch(event.type) {
  case SDL_MOUSEBUTTONDOWN: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      commit_selection();
      clear_selection();
      if (clicked_node) {
        plait.merge_node(clicked_node);
        clicked_node = nullptr;
      }
    }
    break;
  }
  case SDL_KEYUP: {
    int key = event.key.keysym.scancode;
    if (key == SDL_SCANCODE_X) {
      current_tool = ToolMode::NONE;
    }
    break;
  }
  }
}

//--------------------------------------------------------------------------------

void PlaitApp::event_pan_view(SDL_Event event) {
  bool was_drag = length(click_pos_screen - mouse_pos_screen) > 3;

  switch(event.type) {
  case SDL_MOUSEMOTION: {
    if (event.motion.state & SDL_BUTTON_LMASK) {
      view_control.pan(event.motion.xrel, event.motion.yrel);
    }
    break;
  }
  case SDL_MOUSEBUTTONUP: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      if (!was_drag) {
        commit_selection();
        clear_selection();
      }
      current_tool = ToolMode::NONE;
    }
    break;
  }
  }
}

//--------------------------------------------------------------------------------

void PlaitApp::event_drag_nodes(SDL_Event event) {
  switch(event.type) {
  case SDL_MOUSEMOTION: {
    if (event.motion.state & SDL_BUTTON_LMASK) {
      dvec2 pos_abs_new = mouse_pos_world + clicked_offset;
      pos_abs_new.x = round(pos_abs_new.x / 16) * 16.0;
      pos_abs_new.y = round(pos_abs_new.y / 16) * 16.0;
      dvec2 delta = pos_abs_new - clicked_node->get_pos_new();
      for (auto node : node_selection) node->move(delta);
    }
    break;
  }
  case SDL_MOUSEBUTTONUP: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      current_tool = ToolMode::NONE;
    }
    break;
  }
  }
}

//--------------------------------------------------------------------------------

void PlaitApp::event_imgui(SDL_Event event) {
  ImGuiIO& io = ImGui::GetIO();

  switch (event.type) {
  case SDL_TEXTINPUT: {
    io.AddInputCharactersUTF8(event.text.text);
    break;
  }
  case SDL_KEYDOWN:
  case SDL_KEYUP: {
    int key = event.key.keysym.scancode;
    IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
    io.KeysDown[key] = (event.type == SDL_KEYDOWN);
    io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
    io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
    io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
    io.KeySuper = false;
    break;
  }
  case SDL_MOUSEWHEEL: {
    io.MouseWheelH += event.wheel.x;
    io.MouseWheel += event.wheel.y;
    break;
  }
  }

  if (!io.WantCaptureKeyboard && !io.WantCaptureMouse) {
    current_tool = ToolMode::NONE;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::event_select_tool(SDL_Event event) {
  if (event.type == SDL_KEYDOWN) {
    int key = event.key.keysym.scancode;
    ToolMode new_tool = ToolMode::NONE;

    if (key == SDL_SCANCODE_A)     new_tool = ToolMode::PLACE_ANCHOR;
    if (key == SDL_SCANCODE_D)     new_tool = ToolMode::LOCK_REGION;
    if (key == SDL_SCANCODE_F)     new_tool = ToolMode::UNLOCK_REGION;
    if (key == SDL_SCANCODE_Q)     new_tool = ToolMode::GHOST_REGION;
    if (key == SDL_SCANCODE_Z)     new_tool = ToolMode::SPLIT_CELL;
    if (key == SDL_SCANCODE_X)     new_tool = ToolMode::MERGE_CELL;
    if (key == SDL_SCANCODE_LALT)  new_tool = ToolMode::MENU_OPTION;
    if (key == SDL_SCANCODE_LCTRL) new_tool = ToolMode::SELECT_REGION;

    if (new_tool != ToolMode::NONE) {
      current_tool = new_tool;
    }

    if (key == SDL_SCANCODE_ESCAPE && node_selection.size()) {
      printf("Reverting selection\n");
      revert_selection();
      clear_selection();
    }

    if (key == SDL_SCANCODE_RETURN && node_selection.size()) {
      printf("Commiting selection\n");
      commit_selection();
      clear_selection();
    }
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button & SDL_BUTTON_LMASK) {
    if (clicked_node) {
      clicked_offset  = clicked_node->get_pos_new() - mouse_pos_world;

      if (!clicked_node->selected) {
        commit_selection();
        clear_selection();
        select_node(clicked_node);
      }
      current_tool = ToolMode::DRAG_NODE;
    }
    else {
      //commit_selection();
      //clear_selection();
      current_tool = ToolMode::PAN_VIEW;
    }
  }
  else {
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureKeyboard || io.WantCaptureMouse) {
      current_tool = ToolMode::IMGUI;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::app_update(double delta_time) {
  (void)delta_time;

  {
    int mouse_x = 0, mouse_y = 0;
    mouse_buttons    = SDL_GetMouseState(&mouse_x, &mouse_y);
    mouse_pos_screen = {mouse_x, mouse_y};
    mouse_pos_world  = view_control.view_snap.screenToWorld(mouse_pos_screen);
  }

  {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[0] = (mouse_buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0;
    io.MouseDown[1] = (mouse_buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0;
    io.MouseDown[2] = (mouse_buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0;
    io.MousePos = { (float)mouse_pos_screen.x, (float)mouse_pos_screen.y };
  }

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_MOUSEBUTTONDOWN && (event.button.button & SDL_BUTTON_LMASK)) {
      clicked_node = pick_node(mouse_pos_world, /*ignore_selected*/ false, /*ignore_clicked*/ true, /*ignore_hovered*/ false);
      click_pos_screen = mouse_pos_screen;
      click_pos_world = mouse_pos_world;
    }


    switch(current_tool) {
    case ToolMode::NONE:           event_select_tool(event); break;
    case ToolMode::IMGUI:          event_imgui(event); break;
    case ToolMode::DRAG_NODE:      event_drag_nodes(event); break;
    case ToolMode::SELECT_REGION:  event_select_region(event); break;
    case ToolMode::GHOST_REGION:   event_ghost_region(event); break;
    case ToolMode::SPLIT_CELL:     event_split_cell(event); break;
    case ToolMode::MERGE_CELL:     event_merge_cell(event); break;
    case ToolMode::PAN_VIEW:       event_pan_view(event); break;
    case ToolMode::MENU_OPTION:    event_menu_option(event); break;
    }

    if(event.type == SDL_MOUSEWHEEL) {
      view_control.on_mouse_wheel((int)mouse_pos_screen.x, (int)mouse_pos_screen.y, double(event.wheel.y) * 0.25);
    }

    if (event.type == SDL_MOUSEBUTTONUP && (event.button.button & SDL_BUTTON_LMASK)) {
      clicked_node = nullptr;
    }
  }

  if (current_tool != ToolMode::IMGUI) {
    hovered_node = pick_node(mouse_pos_world, /*ignore_selected*/ false, /*ignore_clicked*/ true, /*ignore_hovered*/ false);
  }
  else {
    hovered_node = nullptr;
  }

  view_control.update(delta_time);

  //----------------------------------------
  // Pull nodes towards their parents/children

#if 0
  for (auto& [tag, node] : plait.node_map) {
    for (auto next : node->next) {
      spring_nodes(node, next);
    }

    if (node->get_cell() && node->get_cell()->cell_type == CellType::BUS) {
      if (node->prev.size() >= 2) {
        for (size_t i = 0; i < node->prev.size() - 1; i++) {
          spring_nodes2(node->prev[i + 0], node->prev[i + 1]);
        }
      }
    }
    else {
      if (node->next.size() >= 2) {
        for (size_t i = 0; i < node->next.size() - 1; i++) {
          spring_nodes2(node->next[i + 0], node->next[i + 1]);
        }
      }
    }
  }
#endif

#if 0
  // Push nodes away from their siblings
  for (auto node : plait.nodes) {
    if (node->prev.size() >= 2) {
      for (size_t i = 0; i < node->prev.size() - 1; i++) {
        Node* a = node->prev[i + 0];
        Node* b = node->prev[i + 1];

        if (a->selected) continue;
        if (a->locked) continue;
        if (a->anchored()) continue;

        dvec2 offset = a->get_pos_new() - b->get_pos_new();
        if (length(offset) < 256) {
          a->set_pos_new(a->get_pos_old() + offset * 0.01);
          a->commit_pos();
        }
      }
    }

    if (node->next.size() >= 2) {
      for (size_t i = 0; i < node->next.size() - 1; i++) {
        Node* a = node->next[i + 0];
        Node* b = node->next[i + 1];

        if (a->selected) continue;
        if (a->locked) continue;
        if (a->anchored()) continue;

        dvec2 offset = a->get_pos_new() - b->get_pos_new();
        if (length(offset) < 256) {
          a->set_pos_new(a->get_pos_old() + offset * 0.01);
          a->commit_pos();
        }
      }
    }
  }
#endif

  //----------------------------------------
  // Apply accumulated spring forces

#if 0
  for (auto& [tag, node] : plait.node_map) {
    if (node->selected || node->locked || node->anchored()) {
    }
    else {
      node->move(node->spring_force * 0.01);
      node->commit_pos();
    }
    node->spring_force = {0,0};
  }
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::draw_node(PlaitNode* node) {
  const auto& view = view_control.view_snap;

  dvec2 node_pos_old = node->get_pos_old();
  dvec2 node_pos_new = node->get_pos_new();

  const dvec2 node_size = {128,64};
  const dvec2 port_size = {4,4};

  bool node_visible = true;
  if (node_pos_new.x > view.max.x) node_visible = false;
  if (node_pos_new.y > view.max.y) node_visible = false;
  if (node_pos_new.x + node_size.x < view.min.x) node_visible = false;
  if (node_pos_new.y + node_size.y < view.min.y) node_visible = false;

  //----------------------------------------

  // Node outline
  if (node_visible) {
    uint32_t color = 0xFF808080;
    if (node->selected) color = 0xFFCCCCCC;
    if (node->name != "root") color = 0xFFFF00FF;

    outline_painter.push_box(node_pos_new, node_pos_new + node_size, color);
  }

  // Node fill
  if (node_visible && !node->ghost) {
    box_painter.push_corner_size(
      node_pos_new + dvec2(4,4),
      node_size - dvec2(8,8),
      node == hovered_node ? node->color + COL_HINT3 : node->color);
  }

  // Node text
  if (node_visible) {
    text_painter.add_text_at(node->plait_cell->name(), float(node_pos_new.x + 8), float(node_pos_new.y + 8));
    text_painter.add_text_at(node->plait_cell->gate(), float(node_pos_new.x + 8), float(node_pos_new.y + 24));
  }


  // Node input port(s)
  if (node_visible) {
    size_t prev_port_count = node->plait_cell->die_cell->prev_ports.size();
    double prev_stride = (node_size.y) / (prev_port_count + 1);

    for (size_t i = 0; i < prev_port_count; i++) {
      dvec2 port_pos = node_pos_new + dvec2(0, prev_stride * (i + 1));
      port_painter.push_center_size(port_pos, port_size, 0xCC008000);
    }
  }

  // Node output port(s)
  if (node_visible) {
    size_t next_port_count = node->plait_cell->die_cell->next_ports.size();
    double next_stride = (node_size.y) / (next_port_count + 1);

    for (size_t i = 0; i < next_port_count; i++) {
      dvec2 port_pos = node_pos_new + dvec2(node_size.x, next_stride * (i + 1));
      port_painter.push_center_size(port_pos, port_size, 0xCC000080);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::draw_edge(PlaitTrace* edge) {
  const dvec2 node_size = {128,64};

  auto input_node = edge->input_node;
  auto output_node = edge->output_node;
  if (input_node->ghost || output_node->ghost) return;

  auto prev_pos_new = input_node->get_pos_new();
  auto next_pos_new = output_node->get_pos_new();

  // Highlight "backwards" edges in red.
  bool edge_backwards = prev_pos_new.x > next_pos_new.x;
  uint32_t color_a = edge_backwards ? 0xFF0000FF : 0x40FFFFFF;
  uint32_t color_b = edge_backwards ? 0xFF0000FF : 0x4044FF44;

  // Make edges connected to selected nodes opaque.
  if (input_node->selected || output_node->selected) {
    if (edge_backwards) {
      color_a = 0xFF8080FF;
      color_b = 0xFF8080FF;
    }
    else {
      color_a |= 0xFF000000;
      color_b |= 0xFF000000;
    }
  }

  size_t prev_port_count = input_node->plait_cell->die_cell->next_ports.size();
  size_t next_port_count = output_node->plait_cell->die_cell->prev_ports.size();

  double stride_a = (node_size.y) / (prev_port_count + 1);
  double stride_b = (node_size.y) / (next_port_count + 1);

  dvec2 port_prev = prev_pos_new + dvec2(node_size.x, stride_a * (edge->input_port_index + 1));
  dvec2 port_next = next_pos_new + dvec2(0,           stride_b * (edge->output_port_index + 1));

  edge_painter.push(port_prev, color_a, port_next, color_b);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::app_render_frame() {

  text_painter.bg_col = {0.0,0.0,0.0,0.3};
  const dvec2 node_size = {128,64};

  //----------------------------------------
  // Grid layer

  grid_painter.render(view_control.view_snap);

  //----------------------------------------
  // Node layer

  // Node shadows
  {
    for (auto node : node_selection) {
      dvec2 node_pos_old = node->get_pos_old();
      outline_painter.push_box(node_pos_old, node_pos_old + node_size, 0xFF404040);
    }
    outline_painter.render(view_control.view_snap, 0, 0, 1);
  }

  // Unselected nodes
  {
    for (auto& [tag, plait_cell] : plait.cell_map) {
      for (auto& [name, node] : plait_cell->nodes) {
        if (!node->selected) draw_node(node);
      }
    }
    outline_painter.render(view_control.view_snap, 0, 0, 1);
    box_painter.render(view_control.view_snap, 0, 0, 1);
    port_painter.render(view_control.view_snap, 0, 0, 1);
    edge_painter.render(view_control.view_snap, 0, 0, 1);
    text_painter.render(view_control.view_snap, 0, 0, 1);
  }

  // All traces

  for (auto& [trace_key, trace] : plait.trace_map) {
    draw_edge(trace);
  }

  // Selected nodes
  {
    for (auto node: node_selection) {
      draw_node(node);
    }
    outline_painter.render(view_control.view_snap, 0, 0, 1);
    box_painter.render(view_control.view_snap, 0, 0, 1);
    port_painter.render(view_control.view_snap, 0, 0, 1);
    edge_painter.render(view_control.view_snap, 0, 0, 1);
    text_painter.render(view_control.view_snap, 0, 0, 1);
  }

  //----------------------------------------
  // UI layer

  // Draw in-progress anchor edges

  if (current_tool == ToolMode::PLACE_ANCHOR) {
    for (auto selected_node : node_selection) {
      edge_painter.push(mouse_pos_world, 0xFFFFFFFF, selected_node->get_pos_new() + node_size * 0.5, 0xFFFF8080);
    }
    edge_painter.render(view_control.view_snap, 0, 0, 1);
  }

  // Draw selection rect

  if (mouse_buttons & SDL_BUTTON_LMASK) {
    uint32_t sel_color = 0x00000000;
    if (current_tool == ToolMode::SELECT_REGION) sel_color = 0xFFFFFFFF;
    if (current_tool == ToolMode::LOCK_REGION)   sel_color = 0xFF00FFFF;
    if (current_tool == ToolMode::UNLOCK_REGION) sel_color = 0xFFFFFF00;
    if (current_tool == ToolMode::GHOST_REGION)  sel_color = 0xFFFF0040;

    if (sel_color) {
      outline_painter.push_box(click_pos_world, mouse_pos_world, sel_color);
      outline_painter.render(view_control.view_snap, 0, 0, 1);
    }
  }

  frame_count++;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::app_render_ui() {

  // Draw selection info
  {
    StringDumper d;
    d("Tool mode %s\n", tool_to_string[current_tool].c_str());
    d("Selected nodes : ");
    for (auto selected_node : node_selection) d("%s ", selected_node->plait_cell->name());
    d("\n");
    d("Clicked node : %s\n", clicked_node ? clicked_node->plait_cell->name() : "<none>");
    d("Hovered node : %s\n", hovered_node ? hovered_node->plait_cell->name() : "<none>");

    if (hovered_node) {
      hovered_node->plait_cell->dump(d);
      hovered_node->dump(d);
    }

    text_painter.add_text_at(d.c_str(), 0, 0);
  }

  text_painter.render(view_control.view_screen, 0, 0, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------
