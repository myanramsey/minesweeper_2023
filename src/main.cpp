#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "GUI.h"
#include "Board.h"

#pragma once
using namespace std;

int main(){
    // _________________Creating Board _________________//
    Board board("files/board_config.cfg");
    string player_name;
    // _________________Loading Textures & Font _________________//
    Textures textures;
    sf::Font font;
    font.loadFromFile("files/font.ttf");

    // _________________Welcome Window _________________//
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    // _________________Input Text Varibales _________________//
    sf::String input = "|";
    sf::Text input_text(input, font, 18);
    input_text.setFillColor(sf::Color::Yellow);
    input_text.setStyle(sf::Text::Bold);
    setText(input_text, 800.0f / 2.0f, 600.0 / 2.0f - 45);
    // _________________Welcome Varibles_________________//
    int name_check = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.type == sf::Event::TextEntered) {
                cout << "both work" << endl;
            }
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8 && input.getSize() != 1) {
                        input.erase(input.getSize() - 2, 2);
                        input += "|";
                    } else if (input.getSize() < 11 && ((65 <= event.text.unicode and event.text.unicode <= 90) or
                                                        (97 <= event.text.unicode and event.text.unicode <= 122))) {
                        input.erase(input.getSize() - 1, 1);
                        input += event.text.unicode;
                        input += "|";
                    }
                    input_text.setString(input);
                    setText(input_text, 800.0f / 2.0f, 600.0 / 2.0f - 45);
                }
                if (event.text.unicode == 10) {
                    if (CheckString(input) != "") {
                        player_name = CheckString(input);
                        name_check = 1;
                        window.close();
                    }
                }
        }
        window.clear();
        DrawStartScreen(window, event, board,font);
        window.draw(input_text);
        window.display();
    }

    if (name_check == 0)
        return 0;

    // _________________Game Window _________________//
    sf::RenderWindow gamewindow(sf::VideoMode(board.get_width(), board.get_height()), "Minesweeper");
    // _________________Sprites _________________//
    sf::Sprite debug;
    debug.setTexture(textures.debug);
    debug.setPosition((board.get_cols() * 32) - 304, 32 * ((board.get_rows()) + 0.5f));

    sf::Sprite face;
    face.setTexture(textures.face_happy);
    face.setPosition(((board.get_cols() / 2.0f) * 32) - 32, 32 * ((board.get_rows()) + 0.5f));

    sf::Sprite time_button;
    time_button.setTexture(textures.pause);
    time_button.setPosition((board.get_cols() * 32) - 240, 32 * ((board.get_rows()) + 0.5f));

    sf::Sprite leaderboard_button;
    leaderboard_button.setTexture(textures.leaderboard);
    leaderboard_button.setPosition(((board.get_cols()) * 32) - 176, 32 * ((board.get_rows()) + 0.5f));
    // _________________Game Window Varaibles_________________//
    bool game_continue = true;
    bool game_lose = false;
    bool debug_toggle = false;
    bool leaderboard_toggle = false;
    bool pause = false;

    auto start_time = chrono::high_resolution_clock::now();
    auto pause_time = chrono::high_resolution_clock::now();
    auto unpaused_time = chrono::high_resolution_clock::now();

    int total_pause_time = 0;
    int elapsed_time = 0;
    int total_time = 0;

    while (gamewindow.isOpen()) {
        sf::Event event;
        while (gamewindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gamewindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                // Gets Cordinates
                auto x = sf::Mouse::getPosition(gamewindow).x;
                auto y = sf::Mouse::getPosition(gamewindow).y;
                cout << x << " : " << y << endl;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (y < (board.get_rows() * 32) && game_continue) {
                        x = floor(x / 32);
                        y = floor(y / 32);
                        board.RevealAdjacentCells(x, y);
                        if (board.CheckMineClicked(x, y)) {
                            total_time = 0;

                            face.setTexture(textures.face_lose);

                            game_continue = false;
                            game_lose = true;
                        } else if (board.GameWon()) {
                            Leaderboard_reset();
                            ChangedLeaderBoard(player_name, total_time);
                            leaderboard_toggle = true;
                            game_continue = false;
                        }
                    } else if (debug.getGlobalBounds().contains(x, y) && game_continue) {
                        debug_toggle = !debug_toggle;
                    } else if (face.getGlobalBounds().contains(x,y)) {
                        Leaderboard_reset();
                        Board new_board("files/board_config.cfg");
                        board = new_board;

                        start_time = chrono::high_resolution_clock::now();
                        elapsed_time = 0;
                        face.setTexture(textures.face_happy);

                        game_continue = true;
                    } else if (time_button.getGlobalBounds().contains(x, y)) {
                        pause = !pause;
                        if (!pause) {
                            pause_time = chrono::high_resolution_clock::now();
                            time_button.setTexture(textures.pause);
                            elapsed_time += chrono::duration_cast<chrono::seconds>(pause_time - unpaused_time).count();
                        } else {
                            time_button.setTexture(textures.play);
                            unpaused_time = chrono::high_resolution_clock::now();

                        }
                    } else if (leaderboard_button.getGlobalBounds().contains(x, y)) {
                        leaderboard_toggle = true;
                        pause = !pause;
                        if (!pause) {
                            pause_time = chrono::high_resolution_clock::now();
                            time_button.setTexture(textures.pause);
                            elapsed_time += chrono::duration_cast<chrono::seconds>(pause_time - unpaused_time).count();
                        } else {
                            time_button.setTexture(textures.play);
                            unpaused_time = chrono::high_resolution_clock::now();

                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right && game_continue) {
                    if (y < (board.get_rows() * 32)) {
                        x = floor(x / 32);
                        y = floor(y / 32);
                        board.FlaggedCell(x, y);
                    }
                }
            }
        }

        gamewindow.clear(sf::Color::White);

        // _________________Time_________________//
        auto game_duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time);

        if (!pause && game_continue) {
            total_time = game_duration.count();
            total_time -= elapsed_time;
        }
//        cout << "OG total time: " << game_duration.count();
//        cout << " | elapsed time: " << elapsed_time << " | New total time: " << total_time << endl;

        DrawTime(gamewindow, board, textures, total_time);

        // _________________Drawing Revealed_________________//
        DrawReavealedTiles(gamewindow, board, textures);

        // _________________If paused DO NOT DRAW_________________//
        if (!pause) {
            DrawNumbers(gamewindow, board, textures);
            DrawHidden(gamewindow, board, textures);
            DrawFlagged(gamewindow, board, textures);
            if (debug_toggle)
                DrawDebug(gamewindow, board, textures);
        }

        // _________________Always Draw_________________//
        FlagCount(gamewindow, board, textures);
        gamewindow.draw(leaderboard_button);
        gamewindow.draw(time_button);


        // _________________Draw Toggled_________________//
        if (!game_continue && game_lose) {
            DrawMines(gamewindow, board, textures);
        }


        gamewindow.draw(debug);
        gamewindow.draw(face);

        gamewindow.display();

        if (leaderboard_toggle) {
            sf::RenderWindow leaderboard_window(sf::VideoMode(board.leaderboard_width(), board.leaderboard_height()),"Leaderboard");
            while (leaderboard_window.isOpen()) {
                while (leaderboard_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        leaderboard_window.close();
                        leaderboard_toggle = false;
                        pause = false;
                        if (!pause) {
                            pause_time = chrono::high_resolution_clock::now();
                            time_button.setTexture(textures.pause);
                            elapsed_time += chrono::duration_cast<chrono::seconds>(pause_time - unpaused_time).count();
                        } else {
                            time_button.setTexture(textures.play);
                            unpaused_time = chrono::high_resolution_clock::now();

                        }
                    }
                }
                leaderboard_window.clear(sf::Color::Blue);
                DrawLeaderBoard(leaderboard_window,board,textures,font);
                leaderboard_window.display();
            }
        }
    }
}

