#include "display.hpp"
#include "main.h"
#include <string>
#include <cstring>

using namespace pros;

#define TUNE_SELECT_BUTTON_NUM 0
#define AUTON_SELECT_BUTTON_NUM 1
#define BACK_BUTTON_NUM 2

// All LVGL Objects initialized here
lv_obj_t * autonButton;
lv_obj_t * valueButton;
lv_obj_t * autonLabel;
lv_obj_t * valueLabel;
static lv_obj_t * myLabel;
lv_obj_t * test;

lv_obj_t * backButton;
lv_obj_t * backButtonLabel;

lv_obj_t * titlePage;
lv_obj_t * autonSelectPage;
lv_obj_t * valueTuningPage;

lv_obj_t * autonButtonMatrix;
lv_obj_t * selectedAutonLabel;

lv_style_t releaseStyle; //relesed style
lv_style_t clickStyle; //pressed style

static lv_style_t blackStyle; //relesed style

int auton_sel = 0;

// Enumeration to represent the page the GUI is currently on
enum Page {
  title_page,
  tune_values_page,
  select_auton_page,
} currentPage;


// Map for button labels
static const char * button_labels[] {
    "#ff0000 RF 1#", "#ff0000 RF 2#", "#0000ff BF 1#", "#0000ff BF 2#", "\n",
    "#ff0000 RB 1#", "#ff0000 RB 2#", "#0000ff BB 1#", "#0000ff BB 2#","\n",
    "#00ff00 SKILLS#",""};


// FUNCTIONS
static lv_res_t auton_button_actions(lv_obj_t * btnm, const char * button_text) {

    if(button_text == "#ff0000 RF 1#"){
      auton_sel = 1;
      lv_label_set_text(myLabel, "Red Front 1");
    }
    else if(button_text == "#ff0000 RF 2#"){
      lv_label_set_text(myLabel, "Red Front 2");
      auton_sel = 2;
    }
    else if(button_text == "#0000ff BF 1#"){
      lv_label_set_text(myLabel, "Blue Front 1");
      auton_sel = 3;
    }
    else if(button_text == "#0000ff BF 2#"){
      lv_label_set_text(myLabel, "Blue Front 2");
      auton_sel = 4;
    }
    else if(button_text == "#ff0000 RB 1#"){
      lv_label_set_text(myLabel, "Red Back 1");
      auton_sel = 5;
    }
    else if(button_text == "#ff0000 RB 2#"){
      lv_label_set_text(myLabel, "Red Back 2");
      auton_sel = 6;
    }
    else if(button_text == "#0000ff BB 1#"){
      lv_label_set_text(myLabel, "Blue Back 1");
      auton_sel = 7;
    }
    else if(button_text == "#0000ff BB 2#"){
      lv_label_set_text(myLabel, "Blue Back 2");
      auton_sel = 8;
    }
    else if(button_text == "#00ff00 SKILLS#"){
      lv_label_set_text(myLabel, "Skills Auton");
      auton_sel = 9;
    }

     lv_obj_set_pos(myLabel,140,130);

     return LV_RES_OK;
}


static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn); //id useful when there are multiple buttons

    if(id == AUTON_SELECT_BUTTON_NUM && currentPage == title_page){
        lv_obj_set_hidden(titlePage,true);
        lv_obj_set_hidden(autonSelectPage,false);
        currentPage = select_auton_page;
    }

    if(id==TUNE_SELECT_BUTTON_NUM && currentPage == title_page) {
      lv_obj_set_hidden(titlePage,true);
      lv_obj_set_hidden(valueTuningPage,false);
      currentPage = tune_values_page;
    }

    if(id==BACK_BUTTON_NUM){
      switch(currentPage) {
        case title_page:
        break;

        case select_auton_page:
          lv_obj_set_hidden(autonSelectPage,true);
          lv_obj_set_hidden(titlePage,false);
          currentPage = title_page;
          break;

        case tune_values_page:
          lv_obj_set_hidden(valueTuningPage,true);
          lv_obj_set_hidden(titlePage,false);
          currentPage = title_page;
          break;
      }
    }

    return LV_RES_OK;
}


void createTuneValues(void) {

  valueTuningPage = lv_page_create(lv_scr_act(),NULL);
  lv_obj_align(valueTuningPage, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, LV_VER_RES * 0.2);
  lv_obj_set_width(valueTuningPage, LV_HOR_RES);
  lv_obj_set_height(valueTuningPage, LV_VER_RES* 0.8);
  lv_obj_set_hidden(valueTuningPage,true);

}

void createSelectAuton(void) {

  autonSelectPage = lv_page_create(lv_scr_act(),NULL);
  lv_obj_align(autonSelectPage, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, LV_VER_RES * 0.2);
  lv_obj_set_width(autonSelectPage, LV_HOR_RES);
  lv_obj_set_height(autonSelectPage, LV_VER_RES* 0.8);
  lv_obj_set_hidden(autonSelectPage,true);

  autonButtonMatrix = lv_btnm_create(autonSelectPage, NULL);
  lv_btnm_set_recolor(autonButtonMatrix,true);
  lv_btnm_set_map(autonButtonMatrix, button_labels);
  lv_obj_set_size(autonButtonMatrix, LV_HOR_RES * 0.93, 120);
  lv_obj_align(autonButtonMatrix, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
  lv_obj_set_pos(autonButtonMatrix, 3, 300);
  lv_btnm_set_action(autonButtonMatrix, auton_button_actions);
  lv_btnm_set_style(autonButtonMatrix,LV_BTNM_STYLE_BG,&blackStyle);

  myLabel = lv_label_create(autonSelectPage, NULL); //create label and puts it on the screen
  //lv_obj_align(myLabel, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0); //set the position to center
  lv_obj_set_pos(myLabel, 140,130);
  lv_label_set_style(myLabel, &lv_style_plain);
  //lv_label_set_text(myLabel, std::to_string(auton_sel).c_str()); //sets label text
  lv_label_set_text(myLabel, "No Auton Selected");
}

void createTitlePage(void) {
  titlePage = lv_page_create(lv_scr_act(),NULL);
  lv_obj_align(titlePage, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, LV_VER_RES * 0.2);
  lv_obj_set_width(titlePage, LV_HOR_RES);
  lv_obj_set_height(titlePage, LV_VER_RES* 0.8);

  autonButton = lv_btn_create(titlePage, NULL); //create button, lv_scr_act() is deafult screen object
  lv_obj_set_free_num(autonButton, AUTON_SELECT_BUTTON_NUM); //set button is to 0
  lv_btn_set_action(autonButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
  lv_btn_set_style(autonButton, LV_BTN_STYLE_REL, &releaseStyle); //set the relesed style
  lv_btn_set_style(autonButton, LV_BTN_STYLE_PR, &clickStyle); //set the pressed style
  lv_obj_set_size(autonButton, 200, 50); //set the button size
  lv_obj_align(autonButton, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0); //set the position to top mid

  valueButton = lv_btn_create(titlePage, NULL); //create button, lv_scr_act() is deafult screen object
  lv_obj_set_free_num(valueButton, TUNE_SELECT_BUTTON_NUM); //set button is to 0
  lv_btn_set_action(valueButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
  lv_btn_set_style(valueButton, LV_BTN_STYLE_REL, &releaseStyle); //set the relesed style
  lv_btn_set_style(valueButton, LV_BTN_STYLE_PR, &clickStyle); //set the pressed style
  lv_obj_set_size(valueButton, 200, 50); //set the button size
  lv_obj_align(valueButton, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0); //set the position to top mid

  autonLabel = lv_label_create(autonButton, NULL); //create label and puts it inside of the button
  lv_label_set_text(autonLabel, "Auton Selection"); //sets label text

  valueLabel = lv_label_create(valueButton, NULL); //create label and puts it inside of the button
  lv_label_set_text(valueLabel, "Value Tuning"); //sets label text



}

void createStyles(void) {
  lv_style_copy(&releaseStyle, &lv_style_plain);
  releaseStyle.body.main_color = LV_COLOR_MAKE(150, 0, 0);
  releaseStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
  releaseStyle.body.radius = 0;
  releaseStyle.text.color = LV_COLOR_MAKE(255, 255, 255);

  lv_style_copy(&clickStyle, &lv_style_plain);
  clickStyle.body.main_color = LV_COLOR_MAKE(255, 0, 0);
  clickStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
  clickStyle.body.radius = 0;
  clickStyle.text.color = LV_COLOR_MAKE(255, 255, 255);

  lv_style_copy(&blackStyle, &lv_style_plain);
  blackStyle.body.main_color = LV_COLOR_BLACK;
  blackStyle.body.grad_color = LV_COLOR_BLACK;
  blackStyle.body.border.color = LV_COLOR_WHITE;
  blackStyle.body.border.width = 4;


}





// Allow the GUI to consistently work
void gui(void *param) {

  // Prevent any unwanted bugs by displaying too quickly
  delay(200);

  // Crete the LVGL objects
  createStyles();
  createTitlePage();
  createSelectAuton();
  createTuneValues();


  backButton = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_align(backButton, NULL, LV_ALIGN_IN_TOP_LEFT,5,0);
  lv_obj_set_free_num(backButton, BACK_BUTTON_NUM);
  lv_btn_set_action(backButton, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_btn_set_style(backButton, LV_BTN_STYLE_REL, &releaseStyle);
  lv_btn_set_style(backButton, LV_BTN_STYLE_PR, &clickStyle);
  lv_obj_set_size(backButton, 150, 35);

  backButtonLabel = lv_label_create(backButton, NULL);
  lv_label_set_text(backButtonLabel, "Back");


  // Loop infinitely to allow the user to use the GUI with the buttons
  while(true) {
    delay(20);
  }

}






























/////
