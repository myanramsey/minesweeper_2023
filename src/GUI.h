#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <map>
#include "Board.h"
#pragma once

using namespace std;

struct Textures{
    sf::Texture debug;

    sf::Texture digits_text;
    sf::Sprite digits;
    map<int,sf::Sprite> digitsmap;

    sf::Texture face_happy;
    sf::Texture face_lose;

    sf::Texture flag;

    sf::Texture leaderboard;

    sf::Texture mine;

    sf::Texture number_1;
    sf::Texture number_2;
    sf::Texture number_3;
    sf::Texture number_4;
    sf::Texture number_5;
    sf::Texture number_6;
    sf::Texture number_7;
    sf::Texture number_8;

    sf::Texture pause;
    sf::Texture play;

    sf::Texture tile_hidden;
    sf::Texture tile_revealed;

    Textures() : digits(digits_text) {
        if(!debug.loadFromFile("files/images/debug.png")) {}
        if(!digits_text.loadFromFile("files/images/digits.png")) {}

        // digits.setTexture(digits_text); // Handled in initializer list

        sf::IntRect zero_rect({0,0},{21,32});
        digits.setTextureRect(zero_rect);
        sf::Sprite zero= digits;
        digitsmap.emplace(0,zero);

        sf::IntRect one_rect({21,0},{21,32});
        digits.setTextureRect(one_rect);
        sf::Sprite one= digits;
        digitsmap.emplace(1,one);

        sf::IntRect two_rect({42,0},{21,32});
        digits.setTextureRect(two_rect);
        sf::Sprite two= digits;
        digitsmap.emplace(2,two);

        sf::IntRect three_rect({63,0},{21,32});
        digits.setTextureRect(three_rect);
        sf::Sprite three= digits;
        digitsmap.emplace(3,three);

        sf::IntRect four_rect({84,0},{21,32});
        digits.setTextureRect(four_rect);
        sf::Sprite four= digits;
        digitsmap.emplace(4,four);

        sf::IntRect five_rect({105,0},{21,32});
        digits.setTextureRect(five_rect);
        sf::Sprite five= digits;
        digitsmap.emplace(5,five);

        sf::IntRect six_rect({126,0},{21,32});
        digits.setTextureRect(six_rect);
        sf::Sprite six= digits;
        digitsmap.emplace(6,six);

        sf::IntRect seven_rect({147,0},{21,32});
        digits.setTextureRect(seven_rect);
        sf::Sprite seven= digits;
        digitsmap.emplace(7,seven);

        sf::IntRect eight_rect({168,0},{21,32});
        digits.setTextureRect(eight_rect);
        sf::Sprite eight= digits;
        digitsmap.emplace(8,eight);

        sf::IntRect nine_rect({189,0},{21,32});
        digits.setTextureRect(nine_rect);
        sf::Sprite nine= digits;
        digitsmap.emplace(9,nine);

        sf::IntRect minus_rect({210,0},{21,32});
        digits.setTextureRect(minus_rect);
        sf::Sprite minus= digits;
        digitsmap.emplace(-1,minus);


        if(!face_happy.loadFromFile("files/images/face_happy.png")) {}
        if(!face_lose.loadFromFile("files/images/face_lose.png")) {}

        if(!flag.loadFromFile("files/images/flag.png")) {}
        if(!leaderboard.loadFromFile("files/images/leaderboard.png")) {}
        if(!mine.loadFromFile("files/images/mine.png")) {}

        if(!number_1.loadFromFile("files/images/number_1.png")) {}
        if(!number_2.loadFromFile("files/images/number_2.png")) {}
        if(!number_3.loadFromFile("files/images/number_3.png")) {}
        if(!number_4.loadFromFile("files/images/number_4.png")) {}
        if(!number_5.loadFromFile("files/images/number_5.png")) {}
        if(!number_6.loadFromFile("files/images/number_6.png")) {}
        if(!number_7.loadFromFile("files/images/number_7.png")) {}
        if(!number_8.loadFromFile("files/images/number_8.png")) {}

        if(!pause.loadFromFile("files/images/pause.png")) {}
        if(!play.loadFromFile("files/images/play.png")) {}

        if(!tile_hidden.loadFromFile("files/images/tile_hidden.png")) {}
        if(!tile_revealed.loadFromFile("files/images/tile_revealed.png")) {}
    }
};
struct Name{
    string name;
    int time;
    string time_string;
    bool new_entry = false;
};

void setText(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f));
    text.setPosition(sf::Vector2f(x, y));
}

// NOTE: Changed Board to be passed by value or reference? Keep value to match original, but added Font reference.
// The original code passed 'event' by reference but didn't use it, so I removed it from arguments in main but kept here if needed.
// Actually, main calls it: DrawStartScreen(window, board, font);
// I need to update this signature to match main.
void DrawStartScreen(sf::RenderWindow &window, Board board, sf::Font& font) { 
    // removed 'sf::Event &event' as it was unused and caused issues if not updated
    sf::RectangleShape rectangle(sf::Vector2f(board.get_width(), board.get_height()));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(sf::Vector2f(0, 0));
    window.draw(rectangle);

    sf::Text start_text(font, "WELCOME TO MINESWEEPER!", 24);
    start_text.setFillColor(sf::Color::White);
    start_text.setStyle(sf::Text::Bold |sf::Text::Underlined);
    setText(start_text,board.get_width()/2.0f,board.get_height()/2.0f- 150);
    window.draw(start_text);

    sf::Text name_text(font, "Enter your name:" , 20);
    name_text.setFillColor(sf::Color::White);
    name_text.setStyle(sf::Text::Bold);
    setText(name_text,board.get_width()/2.0f,board.get_height()/2.0f - 75);
    window.draw(name_text);
}

string CheckString(sf::String input){
    input.erase(input.getSize() - 1 ,1 );
    if(input[0] >= 97){
        input[0] -= 32;
    }
    for(int i = 1; i < input.getSize(); i++){
        if(input[i] < 90)
            input[i] += 32;
    }
    // toAnsiString still exists in SFML 3
    string str;
    str = input.toAnsiString(); 
    return str;
}

void DrawReavealedTiles(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i ++) {
        for (int j = 0; j < board.get_cols(); j++) {
            sf::Sprite temp(textures.tile_revealed);
            temp.setPosition(sf::Vector2f(j * 32, i * 32));
            window.draw(temp);
        }
    }
}
void DrawNumbers(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i++) {
        for (int j = 0; j < board.get_cols(); j++) {
            sf::Sprite temp(textures.tile_revealed);
            
            if(!board.get_cells().at(i).at(j).MineStatus()){
                int val = board.get_cells().at(i).at(j).CellValue();
                if(val == 1) temp.setTexture(textures.number_1);
                else if(val == 2) temp.setTexture(textures.number_2);
                else if(val == 3) temp.setTexture(textures.number_3);
                else if(val == 4) temp.setTexture(textures.number_4);
                else if(val == 5) temp.setTexture(textures.number_5);
                else if(val == 6) temp.setTexture(textures.number_6);
                else if(val == 7) temp.setTexture(textures.number_7);
                else if(val == 8) temp.setTexture(textures.number_8);
                else temp.setTexture(textures.tile_revealed);
            }
            else{
                temp.setTexture(textures.mine);
            }
            temp.setPosition(sf::Vector2f(j * 32,i * 32));
            window.draw(temp);
        }

    }
}
void DrawHidden(sf::RenderWindow &window,Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i ++) {
        for (int j = 0; j < board.get_cols(); j++) {
            if (!board.get_cells().at(i).at(j).CellActiveStatus()) {
                sf::Sprite temp(textures.tile_hidden);
                temp.setPosition(sf::Vector2f(j * 32, i * 32));
                window.draw(temp);
            }
        }
    }
}
void DrawFlagged(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i ++) {
        auto vector = board.get_cells();
        for (int j = 0; j < board.get_cols(); j++) {
            if(vector.at(i).at(j).FlagStatus()){
                sf::Sprite temp(textures.flag);
                temp.setPosition(sf::Vector2f(j * 32, i * 32));
                window.draw(temp);
            }
        }
    }
}
void DrawMines(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i ++) {
        for (int j = 0; j < board.get_cols(); j++) {
            if(board.get_cells().at(i).at(j).MineStatus()){
                sf::Sprite temp(textures.mine);
                temp.setPosition(sf::Vector2f(j * 32, i * 32));
                window.draw(temp);
            }
        }
    }
}
void DrawDebug(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i++) {
        for (int j = 0; j < board.get_cols(); j++) {
            if (board.get_cells().at(i).at(j).MineStatus()) {
                sf::Sprite temp_revealed(textures.tile_revealed);
                sf::Sprite temp_mine(textures.mine);

                temp_revealed.setPosition(sf::Vector2f(j * 32, i * 32));
                temp_mine.setPosition(sf::Vector2f(j * 32, i * 32));

                window.draw(temp_revealed);
                window.draw(temp_mine);
            }
        }
    }
}
void DrawTime(sf::RenderWindow &window, Board board, Textures textures, int total_time){


    int minutes = total_time / 60;
    int seconds = total_time % 60;

    int minutes0 = minutes / 10 % 10;
    int minutes1 = minutes % 10 ;

    int seconds0 = seconds / 10 % 10;
    int seconds1 = seconds % 10;

    auto minutes0_map = textures.digitsmap;
    auto minutes1_map = textures.digitsmap;

    minutes0_map.at(minutes0).setPosition(sf::Vector2f((board.get_cols()*32)-97, 32*(board.get_rows()+0.5f)+16));
    minutes1_map.at(minutes1).setPosition(sf::Vector2f((board.get_cols()*32)-76, 32*(board.get_rows()+0.5f)+16));

    window.draw(minutes0_map.at(minutes0));
    window.draw(minutes1_map.at(minutes1));

    auto seconds0_map = textures.digitsmap;
    auto seconds1_map = textures.digitsmap;

    seconds0_map.at(seconds0).setPosition(sf::Vector2f((board.get_cols()*32)-54, 32*(board.get_rows()+0.5f)+16));
    seconds1_map.at(seconds1).setPosition(sf::Vector2f((board.get_cols()*32)-33, 32*(board.get_rows()+0.5f)+16));

    window.draw(seconds0_map.at(seconds0));
    window.draw(seconds1_map.at(seconds1));

}
void FlagCount(sf::RenderWindow &window, Board board, Textures textures){
    int count = board.get_mines();
    for (int i = 0; i < board.get_rows(); i++) {
        for (int j = 0; j < board.get_cols(); j++) {
            if(board.get_cells().at(i).at(j).FlagStatus()){
                count -= 1;
            }
        }
    }


    auto count0_map = textures.digitsmap;
    auto count1_map = textures.digitsmap;
    auto count2_map = textures.digitsmap;
    auto minus_map = textures.digitsmap;

    int count0 = count / 100;
    int count1 = count / 10;
    int count2 = count % 10;


    if(count >= 0){
        count0_map.at(count0).setPosition(sf::Vector2f(33, 32 * ((board.get_rows())+0.5f) + 16));
        count1_map.at(count1).setPosition(sf::Vector2f(54, 32 * ((board.get_rows())+0.5f) + 16));
        count2_map.at(count2).setPosition(sf::Vector2f(75, 32 * ((board.get_rows())+0.5f) + 16));
    }
    else{
        count0 = (count / 100) * -1;
        count1 = (count / 10) * -1;
        count2 = (count % 10) * -1;

        minus_map.at(-1).setPosition(sf::Vector2f(12, 32 * ((board.get_rows())+0.5f) + 16));
        count0_map.at(count0).setPosition(sf::Vector2f(33, 32 * ((board.get_rows())+0.5f) + 16));
        count1_map.at(count1).setPosition(sf::Vector2f(54, 32 * ((board.get_rows())+0.5f) + 16));
        count2_map.at(count2).setPosition(sf::Vector2f(75, 32 * ((board.get_rows())+0.5f) + 16));
        window.draw(minus_map.at(-1));

    }

    window.draw(count0_map.at(count0));
    window.draw(count1_map.at(count1));
    window.draw(count2_map.at(count2));


}
void Leaderboard_reset(){
    vector<string> data_vector;
    ifstream board_config;
    board_config.open("files/leaderboard.txt");

    if (board_config.is_open()) {
        string data;
        while(getline(board_config, data)) {
            data_vector.push_back(data);
        }
    }

    ofstream leaderboard("files/leaderboard.txt");
    for(int i = 0; i < 5 && i < data_vector.size(); i ++){
        string temp_time = "";
        string temp_name = "";
        for(int j = 0; j < data_vector[i].length(); j++){
            if(isdigit(data_vector[i][j]) || data_vector[i][j] == ':'){
                temp_time += data_vector[i][j];
            }
            else if(isalpha(data_vector[i][j])){
                temp_name += data_vector[i][j];
            }
        }
        leaderboard << temp_time + "," + temp_name + "\n";
    }
}
void DrawLeaderBoard(sf::RenderWindow &window, Board board, Textures textures, sf::Font& font) {
    ifstream board_config;
    board_config.open("files/leaderboard.txt");

    vector<string> data_vector;

    if (board_config.is_open()) {
        string data;
        while(getline(board_config, data)) {
            data_vector.push_back(data);
        }
    }

    string temp = "";

    for(int i = 0; i < 5 && i < data_vector.size(); i ++){
        string temp_time = "";
        string temp_name = "";
        for(int j = 0; j < data_vector[i].length(); j++){
            if(isdigit(data_vector[i][j]) || data_vector[i][j] == ':'){
                temp_time += data_vector[i][j];
            }
            else if(isalpha(data_vector[i][j]) || data_vector[i][j] == '*'){
                temp_name += data_vector[i][j];
            }
        }
        temp += "\n\n" + to_string(i+1) + "\t" + temp_time + "\t" + temp_name;
    }

    sf::Text leaderboard_sf_text(font, temp, 18);
    leaderboard_sf_text.setFillColor(sf::Color::White);
    leaderboard_sf_text.setStyle(sf::Text::Bold);

    setText(leaderboard_sf_text,board.leaderboard_width()/2.0f,board.leaderboard_height()/2.0f - 20);

    sf::Text leaderboard_title(font, "LEADERBOARD", 20);
    leaderboard_title.setFillColor(sf::Color::White);
    leaderboard_title.setStyle(sf::Text::Bold |sf::Text::Underlined);
    setText(leaderboard_title,board.leaderboard_width()/2.0f,board.leaderboard_height()/2.0f - 120);

    window.draw(leaderboard_title);
    window.draw(leaderboard_sf_text);

}

bool operator<(const Name& a, const Name& b)
{
    return a.time < b.time;
}

void ChangedLeaderBoard(string name, int time){
    ifstream leaderboard;
    leaderboard.open("files/leaderboard.txt");

    vector<string> data_vector;
    vector<Name> trying;

    //________read file and get data_______//
    if (leaderboard.is_open()) {
        string data;
        while(getline(leaderboard, data)) {
            data_vector.push_back(data);
        }
    }

    //get values in int and strings//
    for(int i = 0; i < 5 && i < data_vector.size(); i ++){
        Name temp;
        string temp_time = "";
        string temp_name = "";
        for(int j = 0; j < data_vector[i].length(); j++){
            if(isdigit(data_vector[i][j]) || data_vector[i][j] == ':'){
                temp_time += data_vector[i][j];
            }
            else if(isalpha(data_vector[i][j])){
                temp_name += data_vector[i][j];
            }
        }
        temp.name = temp_name;
        temp.time_string = temp_time;
        //________convert to measurable seconds_______//
        if(temp_time.length() >= 5) {
            int minutes0 = (int(temp_time[0]) - int('0')) * 10;
            int minutes1 = int(temp_time[1]) - int('0');
            int total_min = minutes1 + minutes0;

            int seconds0 = (int(temp_time[3]) - int('0')) * 10;
            int seconds1 = int(temp_time[4]) - int('0');
            int total_sec = seconds1 + seconds0;

            int temp_total_time = 0;
            temp_total_time = total_sec + (total_min * 60);

            temp.time = temp_total_time;
            trying.push_back(temp);
        }
    }

    //Add users total time
    Name users_name;
    users_name.name = name + " *";
    users_name.time = time;

    int minutes = time / 60;
    int seconds = time % 60;

    int minutes0 = minutes / 10 % 10;
    int minutes1 = minutes % 10 ;

    int seconds0 = seconds / 10 % 10;
    int seconds1 = seconds % 10;

    users_name.time_string = to_string(minutes0) + to_string(minutes1) + ":" + to_string(seconds0) + to_string(seconds1);
    trying.push_back(users_name);


    //sort vector and remove last time
    sort(trying.begin(), trying.end());

    //remove the longest time
    if(trying.size() > 5) trying.pop_back();

    //write in file
    ofstream rewrite("files/leaderboard.txt");
    for(int i = 0; i < trying.size(); i++){
        rewrite << trying[i].time_string + "," + trying[i].name + "\n";
    }
}