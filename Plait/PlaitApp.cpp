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

  {ToolMode::CREATE_LEAF,     "CREATE_LEAF"},
  {ToolMode::DELETE_LEAF,     "DELETE_LEAF"},
  {ToolMode::LINK_LEAF,       "LINK_LEAF"},
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
    printf("Saving gameboy.die_db.json\n");
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
    total_nodes++;
    total_nodes += plait_cell->leaf_nodes.size();
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
    paint_node(cell->root_node);
    for (auto& [name, leaf] : cell->leaf_nodes) {
      paint_node(leaf);
    }
  }

  printf("Init done %f\n", timestamp());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::app_close() {
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

bool PlaitApp::hit_node(dvec2 _mouse_pos, PlaitNode* node) {
   dvec2 node_pos = node->get_pos_new();
  int width = 128;
  int height = 64;

  if (_mouse_pos.x >= node_pos.x &&
      _mouse_pos.y >= node_pos.y &&
      _mouse_pos.x <= node_pos.x + width &&
      _mouse_pos.y <= node_pos.y + height) {
    return true;
  }
  else {
    return false;
  }
}

PlaitNode* PlaitApp::pick_node(dvec2 _mouse_pos) {
  for (auto& [tag, plait_cell] : plait.cell_map) {

    if (hit_node(_mouse_pos, plait_cell->root_node)) return plait_cell->root_node;

    for (auto& [name, leaf] : plait_cell->leaf_nodes) {
      if (hit_node(_mouse_pos, leaf)) return leaf;
    }
  }

  return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

bool PlaitApp::contains_node(dvec2 corner_a, dvec2 corner_b, PlaitNode* node) {
  const dvec2 node_size = {128,64};

  dvec2 rmin = min(corner_a, corner_b);
  dvec2 rmax = max(corner_a, corner_b);

  dvec2 nmin = node->get_pos_new();
  dvec2 nmax = node->get_pos_new() + node_size;

  if (nmin.x < rmin.x) return false;
  if (nmin.y < rmin.y) return false;
  if (nmax.x > rmax.x) return false;
  if (nmax.y > rmax.y) return false;
  return true;
}

void PlaitApp::apply_region_node(dvec2 corner_a, dvec2 corner_b, NodeCallback callback) {
  for (auto& [tag, plait_cell] : plait.cell_map) {
    if (contains_node(corner_a, corner_b, plait_cell->root_node)) {
      callback(plait_cell->root_node);
    }
    for (auto& [name, leaf] : plait_cell->leaf_nodes) {
      if (contains_node(corner_a, corner_b, leaf)) {
        callback(leaf);
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::select_region(dvec2 corner_a, dvec2 corner_b) {
  printf("Selection region ");
  auto callback = [this](PlaitNode* node) {
    printf("%s ", node->plait_cell->name());
    node->select();
    node_selection.insert(node);
  };

  apply_region_node(corner_a, corner_b, callback);
  printf("\n");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::select_node(PlaitNode* node) {
  printf("Selecting %s\n", node->plait_cell->name());
  node->select();
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
    node->deselect();
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
      const char* filename = "gameboy.plait.json";
      printf("Saving plait %s\n", filename);
      commit_selection();
      clear_selection();
      plait.save_json(filename);
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
        node->toggle_ghosted();
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

//--------------------------------------------------------------------------------

void PlaitApp::event_create_leaf(SDL_Event event) {
  switch(event.type) {
  case SDL_MOUSEBUTTONDOWN: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      commit_selection();
      clear_selection();
      if (clicked_node) {
        plait.spawn_leaf_node(clicked_node);
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

void PlaitApp::event_delete_leaf(SDL_Event event) {
  switch(event.type) {
  case SDL_MOUSEBUTTONDOWN: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      commit_selection();
      clear_selection();
      if (clicked_node) {
        if (clicked_node->name == "root") {
          plait.delete_leaves(clicked_node);
        }
        else {
          plait.delete_leaf_node(clicked_node);
        }
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

void PlaitApp::event_link_leaf(SDL_Event event) {
  switch(event.type) {
  case SDL_MOUSEBUTTONDOWN: {
    if (event.button.button & SDL_BUTTON_LMASK) {
      if (clicked_node) {
        for (auto leaf_node : node_selection) {
          plait.link_leaf(leaf_node, clicked_node);
        }
      }
      clicked_node = nullptr;
    }
    break;
  }
  case SDL_KEYUP: {
    int key = event.key.keysym.scancode;
    if (key == SDL_SCANCODE_C) {
      current_tool = ToolMode::NONE;
    }
    break;
  }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::event_select_tool(SDL_Event event) {
  if (event.type == SDL_KEYDOWN) {
    int key = event.key.keysym.scancode;
    ToolMode new_tool = ToolMode::NONE;

    if (key == SDL_SCANCODE_E) show_edges = !show_edges;

    if (key == SDL_SCANCODE_A)     new_tool = ToolMode::PLACE_ANCHOR;
    if (key == SDL_SCANCODE_D)     new_tool = ToolMode::LOCK_REGION;
    if (key == SDL_SCANCODE_F)     new_tool = ToolMode::UNLOCK_REGION;
    if (key == SDL_SCANCODE_Q)     new_tool = ToolMode::GHOST_REGION;
    if (key == SDL_SCANCODE_Z)     new_tool = ToolMode::CREATE_LEAF;
    if (key == SDL_SCANCODE_X)     new_tool = ToolMode::DELETE_LEAF;
    if (key == SDL_SCANCODE_C)     new_tool = ToolMode::LINK_LEAF;
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

      if (!clicked_node->selected()) {
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
      clicked_node = pick_node(mouse_pos_world);
      click_pos_screen = mouse_pos_screen;
      click_pos_world = mouse_pos_world;
    }


    switch(current_tool) {
    case ToolMode::NONE:           event_select_tool(event); break;
    case ToolMode::IMGUI:          event_imgui(event); break;
    case ToolMode::DRAG_NODE:      event_drag_nodes(event); break;
    case ToolMode::SELECT_REGION:  event_select_region(event); break;
    case ToolMode::GHOST_REGION:   event_ghost_region(event); break;
    case ToolMode::CREATE_LEAF:     event_create_leaf(event); break;
    case ToolMode::DELETE_LEAF:     event_delete_leaf(event); break;
    case ToolMode::PAN_VIEW:       event_pan_view(event); break;
    case ToolMode::MENU_OPTION:    event_menu_option(event); break;
    case ToolMode::LINK_LEAF:      event_link_leaf(event); break;
    default: {
      printf("Bad tool!\n");
      __debugbreak();
      break;
    }
    }

    if(event.type == SDL_MOUSEWHEEL) {
      view_control.on_mouse_wheel((int)mouse_pos_screen.x, (int)mouse_pos_screen.y, double(event.wheel.y) * 0.25);
    }

    if (event.type == SDL_MOUSEBUTTONUP && (event.button.button & SDL_BUTTON_LMASK)) {
      clicked_node = nullptr;
    }
  }

  if (current_tool != ToolMode::IMGUI) {
    hovered_node = pick_node(mouse_pos_world);
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

void PlaitApp::draw_node_outline(PlaitNode* node) {
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

  if (node_visible) {
    uint32_t color = COL_DARK_GREY;
    if (node->name != "root") color = COL_DARK_GREEN;
    if (node->name == "root" && node->plait_cell->leaf_nodes.size()) color = COL_DARK_YELLOW;

    if (node->selected() || node->plait_cell->selected_node_count) {
      color = node->selected() ? COL_PALE_GREY : COL_PALE_YELLOW;
      outline_painter.push_box(node_pos_new - dvec2( 0, 0), node_pos_new + node_size + dvec2( 0, 0), color);
      outline_painter.push_box(node_pos_new - dvec2( 8, 8), node_pos_new + node_size + dvec2( 8, 8), color);
      outline_painter.push_box(node_pos_new - dvec2(16,16), node_pos_new + node_size + dvec2(16,16), color);
    }
    else {
      outline_painter.push_box(node_pos_new, node_pos_new + node_size, color);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

void PlaitApp::draw_node_fill(PlaitNode* node) {
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
  // Node fill

  if (node_visible && !node->ghosted) {
    uint32_t color = node == hovered_node ? node->color + COL_HINT3 : node->color;
    if (node->pos_new.x < node->plait_cell->root_node->pos_new.x) {
      if (node->plait_cell->die_cell->cell_type == DieCellType::DFF) {
      }
      else if (node->plait_cell->die_cell->cell_type == DieCellType::BUS) {
      }
      else if (node->plait_cell->die_cell->cell_type == DieCellType::PIN_IO) {
      }
      else {
        color = 0xFF0000FF;
      }
    }
    box_painter.push_corner_size(node_pos_new + dvec2(4,4), node_size - dvec2(8,8), color);
  }

  //----------------------------------------
  // Node text

  if (node_visible) {
    text_painter.add_text_at(node->plait_cell->name(), float(node_pos_new.x + 8), float(node_pos_new.y + 8));
    text_painter.add_text_at(node->plait_cell->gate(), float(node_pos_new.x + 8), float(node_pos_new.y + 24));
  }


  //----------------------------------------
  // Node input port(s)

  if (node_visible) {
    size_t prev_port_count = node->plait_cell->die_cell->input_ports.size();
    double prev_stride = (node_size.y) / (prev_port_count + 1);

    for (size_t i = 0; i < prev_port_count; i++) {
      dvec2 port_pos = node_pos_new + dvec2(0, prev_stride * (i + 1));
      port_painter.push_center_size(port_pos, port_size, 0xCC008000);
    }
  }

  //----------------------------------------
  // Node output port(s)

  if (node_visible) {
    size_t next_port_count = node->plait_cell->die_cell->output_ports.size();
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

  auto output_node = edge->output_node;
  auto input_node  = edge->input_node;
  if (output_node->ghosted || input_node->ghosted) return;

  auto output_pos_new = output_node->get_pos_new();
  auto input_pos_new  = input_node->get_pos_new();

  // Highlight "backwards" edges in red.
  bool edge_backwards = output_pos_new.x > input_pos_new.x;
  uint32_t output_color = edge_backwards ? 0xFF0000FF : 0x40FFFFFF;
  uint32_t input_color = edge_backwards ? 0xFF0000FF : 0x4044FF44;

  // Make edges connected to selected nodes opaque.
  if (output_node->plait_cell->selected() || input_node->plait_cell->selected()) {
    if (edge_backwards) {
      output_color = 0xFF8080FF;
      input_color = 0xFF8080FF;
    }
    else {
      output_color |= 0xFF000000;
      input_color |= 0xFF000000;
    }
  }

  size_t output_port_count = output_node->plait_cell->die_cell->output_ports.size();
  size_t input_port_count  = input_node->plait_cell->die_cell->input_ports.size();

  double output_stride = (node_size.y) / (output_port_count + 1);
  double input_stride  = (node_size.y) / (input_port_count + 1);

  dvec2 output_port_pos = output_pos_new + dvec2(node_size.x, output_stride * (edge->output_port_index + 1));
  dvec2 input_port_pos  = input_pos_new  + dvec2(0,           input_stride * (edge->input_port_index + 1));

  edge_painter.push(output_port_pos, output_color, input_port_pos, input_color);
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

  for (auto node : node_selection) {
    dvec2 node_pos_old = node->get_pos_old();
    outline_painter.push_box(node_pos_old, node_pos_old + node_size, 0xFF404040);
  }
  outline_painter.render(view_control.view_snap, 0, 0, 1);

  // Node outlines

  for (auto& [tag, plait_cell] : plait.cell_map) {
    draw_node_outline(plait_cell->root_node);

    for (auto& [name, leaf] : plait_cell->leaf_nodes) {
      draw_node_outline(leaf);
    }
  }

  outline_painter.render(view_control.view_snap, 0, 0, 1);

  // Unselected node fills

  for (auto& [tag, plait_cell] : plait.cell_map) {
    if (!plait_cell->root_node->selected()) draw_node_fill(plait_cell->root_node);

    for (auto& [name, leaf] : plait_cell->leaf_nodes) {
      if (!leaf->selected()) draw_node_fill(leaf);
    }
  }
  box_painter.render(view_control.view_snap, 0, 0, 1);
  port_painter.render(view_control.view_snap, 0, 0, 1);
  text_painter.render(view_control.view_snap, 0, 0, 1);

  // All traces

  if (show_edges) {
    for (auto& [trace_key, trace] : plait.trace_map) {
      draw_edge(trace);
    }
  }

  edge_painter.render(view_control.view_snap, 0, 0, 1);

  // Selected node fills

  for (auto node: node_selection) {
    draw_node_fill(node);
  }
  box_painter.render(view_control.view_snap, 0, 0, 1);
  port_painter.render(view_control.view_snap, 0, 0, 1);
  text_painter.render(view_control.view_snap, 0, 0, 1);

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
