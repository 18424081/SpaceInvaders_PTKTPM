#pragma once

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

#define CONNECT_TIMEOUT 5000 // Milliseconds. --client
#define CLIENT_TIMEOUT 5000
#define HEARTBEAT_INTERVAL 1000 // Milliseconds. --server
#define HEARTBEAT_RETRIES 5
#define SERVER_PORT 560001
#define HIGHEST_TIMESTAMP 2147483648
#define PACKET_HEARTBEAT PacketType::Heartbeat

#define SPLASH_STATE_SHOW_TIME 2

#define WING_SOUND_FILEPATH "Resources/res/Wing.wav"

//Splash State.
#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/texture/SplashBackground.png"

// Main Menu State.
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/texture/Logo.png"
#define MAIN_MENU_PLAY_BUTTON "Resources/texture/PlayButton.png"
#define MAIN_MENU_EXIT_BUTTON "Resources/texture/ExitButton.png"
#define MAIN_MENU_TITLE "Resources/texture/GameTitle.png"

#define GAME_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"
#define PAUSE_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"

#define MAIN_MENU_TITLE_PATH "Resources/res/Game Title.png"


#define RESUME_BUTTON "Resources/res/Resume Button.png"
#define HOME_BUTTON "Resources/res/Home Button.png"
#define RETRY_BUTTON "Resources/res/Retry Button.png"

#define MAIN_MENU_PLAY_BUTTON_OUTER "Resources/res/Play Button Outer.png"

#define PAUSE_BUTTON "Resources/res/Pause Button.png"

#define X_PIECE_FILEPATH "Resources/res/X.png"
#define X_WINNING_PIECE_FILEPATH "Resources/res/X Win.png"
#define O_PIECE_FILEPATH "Resources/res/O.png"
#define O_WINNING_PIECE_FILEPATH "Resources/res/O Win.png"

#define GRID_SPRITE_FILEPATH "Resources/res/Grid.png"

#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1
#define PLAYER_PIECE X_PIECE
#define AI_PIECE O_PIECE

#define STATE_PLAYING 98
#define STATE_PAUSED 97
#define STATE_WON 96
#define STATE_LOSE 95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING 93
#define STATE_DRAW 92

#define TIME_BEFORE_SHOWING_GAME_OVER 3
