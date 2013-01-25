#include <ncurses.h>
#include <string>
#include <unistd.h>
#include "CSMenu.h"
#include "CTMenu.h"
#include "CSPScene.h"
#include "CMPScene.h"
#include "CServerScene.h"
#include "CClientScene.h"

#define COLS_NUMBER 110 /**< define screen width*/
#define LINES_NUMBER 28 /**< define screen height*/
/** Define statement constants. */
enum EWindow { CONFAIL = -2, /**< Connection fail */ 
    CREATEFAIL = -1, /**< Create server fail */
    FAIL, /**< Common fail / undefined error */
    MAINMENU, /**< Main menu */
    GAME, /**< Singleplayer game */
    MULTIPLAYER, /**< Multiplayer menu */
    EXIT, /**< Exit successfully */
    CONTROLS, /**< Control menu */
    LOCALGAME, /**< Multiplayer game on this computer */
    SERVER, /**< Create server / Multiplayer game */
    CLIENT /**< Connect to server / Multiplayer game */
};
/** 
* Setting up player name (by user name). Create ncurses. Set up ncurses (start color, keys, echo, etc.).
* According to status value start menu or start game scene. If any error appears main() print error 
* message to console and end program with return value 1.
*/
int main(){
    int status = MAINMENU;
    string playerName;
    playerName = getlogin(); // setting up player name by his login name
    if(playerName.length() > 8 ) playerName = playerName.substr(0,7); //if it's too long cut it

    WINDOW * win;
    win = initscr (); //create a window
    /* When the console is smaller that we require. */  
    if(COLS < COLS_NUMBER || LINES < LINES_NUMBER){
      endwin (); //close ncurses 
      printf("This program is running in %dx%d resolution. Change your console resolution.\n", COLS_NUMBER, LINES_NUMBER);
        return 1;
    }
    /* Set up some needed ncurses things. */
    noecho (); //no echo
    start_color (); //start color mode
    keypad (stdscr, TRUE); // enable keys F1 - F12, enter etc.
    curs_set(0); //turn off cursor
    resize_term(LINES_NUMBER, COLS_NUMBER); //resize terminal to our size

    CSMenu *menu;
    CTMenu *textMenu;
    CScene *gameScene;

    while(true){
        if(status==MAINMENU){
            menu = new CSMenu(COLS_NUMBER, LINES_NUMBER);
            menu->buttonAdd("Singleplayer", GAME);
            menu->buttonAdd("Multiplayer", MULTIPLAYER);
            menu->buttonAdd("Controls", CONTROLS);
            menu->buttonAdd("Exit", EXIT);
            status = menu->show();
            delete menu;
        }else if(status == MULTIPLAYER){
            menu = new CSMenu(COLS, LINES);
            menu->buttonAdd("On This Computer", LOCALGAME);
            menu->buttonAdd("Create Game", SERVER);
            menu->buttonAdd("Join Game", CLIENT);
            menu->buttonAdd("Back", MAINMENU);
            menu->setTexts("MULTIPLAYER", "You think that you can beat someone?");
            status = menu->show();
            delete menu;
        }else if(status==CONTROLS){
            textMenu = new CTMenu(COLS_NUMBER, LINES_NUMBER, MAINMENU, "Back");
            textMenu->setTexts("CONTROLS", "This is how to control it!");
            textMenu->addTextLine("WORM 1:");
            textMenu->addTextLine("LEFT leftArrow RIGHT rightArrow");
            textMenu->addTextLine("Worm 2:");
            textMenu->addTextLine("LEFT a RIGHT s");
            textMenu->addTextLine("Worm 3:");
            textMenu->addTextLine("LEFT j RIGHT k");
            textMenu->addTextLine("Worm 4:");
            textMenu->addTextLine("LEFT NUM4 RIGHT NUM5");
            textMenu->addTextLine("Menu:");
            textMenu->addTextLine("OK enter UP upArrow DOWN downArrow");
            status = textMenu->show();
            delete textMenu;
        }else if(status==LOCALGAME){
            int players;
            menu = new CSMenu(COLS, LINES);
            menu->buttonAdd("2 Players", 2);
            menu->buttonAdd("3 Players", 3);
            menu->buttonAdd("4 Players", 4);
            menu->buttonAdd("Back",0);
            menu->setTexts("MULTIPLAYER - LOCAL", "Do not forget to look at controls.");
            players = menu->show();
            delete menu;
            if(!players) {status=MAINMENU; continue;}
            gameScene = new CMPScene(players);
            status = gameScene->show();
            delete gameScene;
        }else if(status==GAME){
            int players;
            menu = new CSMenu(COLS, LINES);
            menu->buttonAdd("1 Worm", 2);
            menu->buttonAdd("2 Worms", 3);
            menu->buttonAdd("3 Worms", 4);
            menu->buttonAdd("Back",0);
            menu->setTexts("SINGLEPLAYER", "Choose against how many opponents you want to play.");
            players = menu->show();
            delete menu;
            if(!players) {status=MAINMENU; continue;}
            gameScene = new CSPScene(players, playerName);
            status = gameScene->show();
            delete gameScene;
        }else if(status==SERVER){
            gameScene = new CServerScene(playerName);
            status = gameScene->show();
            delete gameScene;
        }else if(status==CLIENT){
            gameScene = new CClientScene(playerName);
            status = gameScene->show();
            delete gameScene;
        }else{
            break;
        }
    }

    erase (); //erase screen               
    refresh (); //refresh screen     
    endwin (); //end ncurses
    /* Control fails. Print which error just appear.*/
    if(status < 1){
        if(status==FAIL){
            printf("This program has been terminated because of console resolution changes.\n");
        }else   if( status == CREATEFAIL){
            printf("Can not create server. Try it again later.\n");
        }else if ( status == CONFAIL){
            printf("Connection error.\n");
        }
        return 1;
    }   

    return 0;
}