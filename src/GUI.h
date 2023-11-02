

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
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


    Textures(){
        debug.loadFromFile("files/images/debug.png");

        digits_text.loadFromFile("files/images/digits.png");
        digits.setTexture(digits_text);

        sf::IntRect zero_rect(0,0,21,32);
        digits.setTextureRect(zero_rect);
        sf::Sprite zero= digits;
        digitsmap.emplace(0,zero);

        sf::IntRect one_rect(21,0,21,32);
        digits.setTextureRect(one_rect);
        sf::Sprite one= digits;
        digitsmap.emplace(1,one);

        sf::IntRect two_rect(42,0,21,32);
        digits.setTextureRect(two_rect);
        sf::Sprite two= digits;
        digitsmap.emplace(2,two);

        sf::IntRect three_rect(63,0,21,32);
        digits.setTextureRect(three_rect);
        sf::Sprite three= digits;
        digitsmap.emplace(3,three);

        sf::IntRect four_rect(84,0,21,32);
        digits.setTextureRect(four_rect);
        sf::Sprite four= digits;
        digitsmap.emplace(4,four);

        sf::IntRect five_rect(105,0,21,32);
        digits.setTextureRect(five_rect);
        sf::Sprite five= digits;
        digitsmap.emplace(5,five);

        sf::IntRect six_rect(126,0,21,32);
        digits.setTextureRect(six_rect);
        sf::Sprite six= digits;
        digitsmap.emplace(6,six);

        sf::IntRect seven_rect(147,0,21,32);
        digits.setTextureRect(seven_rect);
        sf::Sprite seven= digits;
        digitsmap.emplace(7,seven);

        sf::IntRect eight_rect(168,0,21,32);
        digits.setTextureRect(eight_rect);
        sf::Sprite eight= digits;
        digitsmap.emplace(8,eight);

        sf::IntRect nine_rect(189,0,21,32);
        digits.setTextureRect(nine_rect);
        sf::Sprite nine= digits;
        digitsmap.emplace(9,nine);

        sf::IntRect minus_rect(210,0,21,32);
        digits.setTextureRect(minus_rect);
        sf::Sprite minus= digits;
        digitsmap.emplace(-1,minus);


        face_happy.loadFromFile("files/images/face_happy.png");
        face_lose.loadFromFile("files/images/face_lose.png");

        flag.loadFromFile("files/images/flag.png");
        leaderboard.loadFromFile("files/images/leaderboard.png");
        mine.loadFromFile("files/images/mine.png");

        number_1.loadFromFile("files/images/number_1.png");
        number_2.loadFromFile("files/images/number_2.png");
        number_3.loadFromFile("files/images/number_3.png");
        number_4.loadFromFile("files/images/number_4.png");
        number_5.loadFromFile("files/images/number_5.png");
        number_6.loadFromFile("files/images/number_6.png");
        number_7.loadFromFile("files/images/number_7.png");
        number_8.loadFromFile("files/images/number_8.png");

        pause.loadFromFile("files/images/pause.png");
        play.loadFromFile("files/images/play.png");

        tile_hidden.loadFromFile("files/images/tile_hidden.png");
        tile_revealed.loadFromFile("files/images/tile_revealed.png");

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
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}
void DrawStartScreen(sf::RenderWindow &window, sf::Event &event, Board board,sf::Font font) {

    sf::RectangleShape rectangle(sf::Vector2f(board.get_width(), board.get_height()));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(0, 0);
    window.draw(rectangle);

    sf::Text start_text("WELCOME TO MINESWEEPER!", font, 24);
    start_text.setFillColor(sf::Color::White);
    start_text.setStyle(sf::Text::Bold |sf::Text::Underlined);
    setText(start_text,board.get_width()/2.0f,board.get_height()/2.0f- 150);
    window.draw(start_text);

    sf::Text name_text("Enter your name:" , font , 20);
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

    string str;
    str = input.toAnsiString();
    return str;
}
void DrawReavealedTiles(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i ++) {
        for (int j = 0; j < board.get_cols(); j++) {
            sf::Sprite temp;
            temp.setTexture(textures.tile_revealed);
            temp.setPosition(j * 32, i * 32);
            window.draw(temp);
        }
    }
}
void DrawNumbers(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i++) {
        sf::Sprite temp;
        for (int j = 0; j < board.get_cols(); j++) {
            if(!board.get_cells().at(i).at(j).MineStatus()){
                if(board.get_cells().at(i).at(j).CellValue() == 1){
                    temp.setTexture(textures.number_1);
                }
                else if(board.get_cells().at(i).at(j).CellValue() == 2){
                    temp.setTexture(textures.number_2);
                }
                else if(board.get_cells().at(i).at(j).CellValue() == 3) {
                    temp.setTexture(textures.number_3);
                }
                else if(board.get_cells().at(i).at(j).CellValue() == 4) {
                    temp.setTexture(textures.number_4);
                }
                else if(board.get_cells().at(i).at(j).CellValue() == 5) {
                    temp.setTexture(textures.number_5);
                }
                else if(board.get_cells().at(i).at(j).CellValue() == 6) {
                    temp.setTexture(textures.number_6);
                }
                else if(board.get_cells().at(i).at(j).CellValue() == 7) {
                    temp.setTexture(textures.number_7);
                }
                else if(board.get_cells().at(i).at(j).CellValue() == 8) {
                    temp.setTexture(textures.number_8);
                }
                else{
                    temp.setTexture(textures.tile_revealed);
                }
            }
            else{
                temp.setTexture(textures.mine);
            }
            temp.setPosition(j * 32,i * 32);
            window.draw(temp);
        }

    }
}
void DrawHidden(sf::RenderWindow &window,Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i ++) {
        for (int j = 0; j < board.get_cols(); j++) {
            sf::Sprite temp;
            if (!board.get_cells().at(i).at(j).CellActiveStatus()) {
                temp.setTexture(textures.tile_hidden);
                temp.setPosition(j * 32, i * 32);
            }
            temp.setPosition(j * 32,i * 32);
            window.draw(temp);
            window.draw(temp);
        }
    }
}
void DrawFlagged(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i ++) {
        auto vector = board.get_cells();
        for (int j = 0; j < board.get_cols(); j++) {
            sf::Sprite temp;
            if(vector.at(i).at(j).FlagStatus()){
                temp.setTexture(textures.flag);
                temp.setPosition(j * 32, i * 32);
                window.draw(temp);
            }
        }
    }
}
void DrawMines(sf::RenderWindow &window, Board board, Textures textures){
    //todo: make mine appear
    for (int i = 0; i < board.get_rows(); i ++) {
        for (int j = 0; j < board.get_cols(); j++) {
            if(board.get_cells().at(i).at(j).MineStatus()){
                sf::Sprite temp;
                temp.setTexture(textures.mine);
                temp.setPosition(j * 32, i * 32);
                window.draw(temp);
            }
        }
    }
}
void DrawDebug(sf::RenderWindow &window, Board board, Textures textures){
    for (int i = 0; i < board.get_rows(); i++) {
        for (int j = 0; j < board.get_cols(); j++) {
            if (board.get_cells().at(i).at(j).MineStatus()) {
                sf::Sprite temp_revealed;
                sf::Sprite temp_mine;

                temp_revealed.setTexture(textures.tile_revealed);
                temp_mine.setTexture(textures.mine);

                temp_revealed.setPosition(j * 32, i * 32);
                temp_mine.setPosition(j * 32, i * 32);

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

    minutes0_map[minutes0].setPosition((board.get_cols()*32)-97, 32*(board.get_rows()+0.5f)+16);
    minutes1_map[minutes1].setPosition((board.get_cols()*32)-76, 32*(board.get_rows()+0.5f)+16);

    window.draw(minutes0_map[minutes0]);
    window.draw(minutes1_map[minutes1]);

    auto seconds0_map = textures.digitsmap;
    auto seconds1_map = textures.digitsmap;

    seconds0_map[seconds0].setPosition((board.get_cols()*32)-54, 32*(board.get_rows()+0.5f)+16);
    seconds1_map[seconds1].setPosition((board.get_cols()*32)-33, 32*(board.get_rows()+0.5f)+16);

    window.draw(seconds0_map[seconds0]);
    window.draw(seconds1_map[seconds1]);

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


    if(count > 0){

        count0_map[count0].setPosition(33, 32 * ((board.get_rows())+0.5f) + 16);
        count1_map[count1].setPosition(54, 32 * ((board.get_rows())+0.5f) + 16);
        count2_map[count2].setPosition(75, 32 * ((board.get_rows())+0.5f) + 16);
    }
    else{
        count0 = count / 100 * -1;
        count1 = count / 10 * -1;
        count2 = count % 10 * -1;

        minus_map[-1].setPosition(12, 32 * ((board.get_rows())+0.5f) + 16);
        count0_map[count0].setPosition(33, 32 * ((board.get_rows())+0.5f) + 16);
        count1_map[count1].setPosition(54, 32 * ((board.get_rows())+0.5f) + 16);
        count2_map[count2].setPosition(75, 32 * ((board.get_rows())+0.5f) + 16);
        window.draw(minus_map[-1]);

    }

    window.draw(count0_map[count0]);
    window.draw(count1_map[count1]);
    window.draw(count2_map[count2]);


}
void Leaderboard_reset(){
    vector<string> data_vector;
    ifstream board_config;
    board_config.open("files/leaderboard.txt");
    int index = 0;

    if (board_config.is_open()) {
        string data;
        while(getline(board_config, data)) {
            data_vector.push_back(data);
            index += 1;
        }
    }

    ofstream leaderboard("files/leaderboard.txt");
    for(int i = 0; i < 5; i ++){
        string temp_time = "";
        string temp_name = "";
        for(int j = 0; j < sizeof(data_vector[i]); j++){
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
void DrawLeaderBoard(sf::RenderWindow &window, Board board, Textures textures, sf::Font font) {
    ifstream board_config;
    board_config.open("files/leaderboard.txt");

    vector<string> data_vector;
    int index = 0;

    if (board_config.is_open()) {
        string data;
        while(getline(board_config, data)) {
            data_vector.push_back(data);
            index += 1;
        }
    }

    string temp = "";

    for(int i = 0; i < 5; i ++){
        string temp_time = "";
        string temp_name = "";
        for(int j = 0; j < sizeof(data_vector[i]); j++){
            if(isdigit(data_vector[i][j]) || data_vector[i][j] == ':'){
                temp_time += data_vector[i][j];
            }
            else if(isalpha(data_vector[i][j]) || data_vector[i][j] == '*'){
                temp_name += data_vector[i][j];
            }
        }
        temp += "\n\n" + to_string(i+1) + "\t" + temp_time + "\t" + temp_name;
    }

    sf::Text leaderboard_sf_text(temp,font,18);
    leaderboard_sf_text.setFillColor(sf::Color::White);
    leaderboard_sf_text.setStyle(sf::Text::Bold);

    setText(leaderboard_sf_text,board.leaderboard_width()/2.0f,board.leaderboard_height()/2.0f - 20);

    sf::Text leaderboard_title("LEADERBOARD", font, 20);
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
        int index = 0;
        string data;
        while(getline(leaderboard, data)) {
            data_vector.push_back(data);
            index += 1;
        }
    }

    //get values in int and strings//
    for(int i = 0; i < 5; i ++){
        Name temp;
        string temp_time = "";
        string temp_name = "";
        for(int j = 0; j < sizeof(data_vector[i]); j++){
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

    users_name.time_string = to_string(minutes0) + to_string(minutes) + ":" + to_string(seconds0) + to_string(seconds1);
    trying.push_back(users_name);


    //sort vector and remove last time
    int index = 0;
    int max_value = trying.at(0).time;
    sort(trying.begin(), trying.end());

    //remove the longest time
    trying.pop_back();

    //write in file
    ofstream rewrite("files/leaderboard.txt");
    for(int i = 0; i < trying.size(); i++){
        rewrite << trying[i].time_string + "," + trying[i].name + "\n";
    }
}
