//
// Created by Mya  on 7/23/23.
//
#ifndef HELLOSFML_BOARD_H
#define HELLOSFML_BOARD_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <stdlib.h>
#include <random>



#include "Cell.h"

#pragma once
using namespace std;

class Board{
    int cols;
    int rows;
    int mines;
    vector <vector<Cell>> cells;
public:
    Board(string filename) {
        ifstream board_config;
        board_config.open(filename);
        board_config >> cols;
        board_config >> rows;
        board_config >> mines;

        for (int i = 0; i < rows; i++) {
            vector <Cell> whole_row;
            for (int j = 0; j < cols; j++){
                whole_row.push_back(Cell());
            }
            cells.push_back(whole_row);
        }
        PlaceMines();
        PlaceNumbers();
    }

    int get_width(){
        return cols * 32;
    }
    int get_height(){
        return (rows * 32) + 100;
    }
    int leaderboard_width(){
        return cols * 16;
    }
    int leaderboard_height(){
        return rows * 16 + 50;
    }
    int get_rows(){
        return rows;
    }
    int get_cols(){
        return cols;
    }
    int get_mines(){
        return mines;
    }
    vector <vector<Cell>> get_cells(){
        return cells;
    }

    void PrintBoard(){
        cout << "      ";
        for (int i = 0; i < cols; i++) {
            cout << i << setw(4);
        }
        cout << endl;
        for (int i = 0; i < rows; i++) {
            if(i < 10) {
                cout << i << setw(2) << ":" << setw(1);
            } else
                cout << i << setw(1) << ":" << setw(2);
            for (int j = 0; j < cols; j++) {
                cells.at(i).at(j).PrintCell();
                cout << setw(4);
            }
            cout << endl;
        }
    }

    void PlaceMines(){
        vector <int> x_val;
        vector <int> y_val;

        for (int i = 0; i < mines; i++){
            random_device row_generator;
            uniform_int_distribution<int> row_distribution(0,rows - 1);

            random_device col_generator;
            uniform_int_distribution<int> col_distribution(0,cols - 1);

            int y = row_distribution(row_generator);
            int x = col_distribution(col_generator);

            if(!cells.at(y).at(x).MineStatus()){
                cells.at(y).at(x).ActiveMine();
            }
            else{
                i--;
            }
        }
    }
    void PlaceNumbers(){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(cells.at(i).at(j).MineStatus()) {
                    if(j== 0) {
                        if (i == 0) {
                            cells.at(i).at(j + 1).AdjecentTiles();
                            cells.at(i + 1).at(j + 1).AdjecentTiles();
                            cells.at(i + 1).at(j).AdjecentTiles();
                        } else if (i == rows - 1) {
                            cells.at(i - 1).at(j).AdjecentTiles();
                            cells.at(i - 1).at(j + 1).AdjecentTiles();
                            cells.at(i).at(j + 1).AdjecentTiles();
                        }
                        else{
                            cells.at(i - 1).at(j).AdjecentTiles();
                            cells.at(i - 1).at(j + 1).AdjecentTiles();
                            cells.at(i).at(j + 1).AdjecentTiles();
                            cells.at(i + 1).at(j + 1).AdjecentTiles();
                            cells.at(i + 1).at(j).AdjecentTiles();
                        }
                    }
                    else if(j == cols - 1){
                        if(i == 0){
                            cells.at(i).at(j-1).AdjecentTiles();
                            cells.at(i + 1).at(j- 1).AdjecentTiles();
                            cells.at(i + 1).at(j).AdjecentTiles();
                        }
                        else if( i == rows - 1){
                            cells.at(i - 1).at(j).AdjecentTiles();
                            cells.at(i - 1).at(j - 1).AdjecentTiles();
                            cells.at(i).at(j - 1).AdjecentTiles();
                        }
                        else{
                            cells.at(i-1).at(j).AdjecentTiles();
                            cells.at(i - 1).at(j - 1).AdjecentTiles();
                            cells.at(i).at(j - 1).AdjecentTiles();
                            cells.at(i + 1).at(j - 1).AdjecentTiles();
                            cells.at(i + 1).at(j).AdjecentTiles();

                        }
                    }
                    else{
                        if(i == 0){
                            cells.at(i).at(j -1).AdjecentTiles();
                            cells.at(i).at(j + 1).AdjecentTiles();

                            cells.at(i + 1).at(j -1).AdjecentTiles();
                            cells.at(i + 1).at(j).AdjecentTiles();
                            cells.at(i + 1).at(j + 1).AdjecentTiles();
                        }
                        else if( i == rows - 1){
                            cells.at(i - 1).at(j -1).AdjecentTiles();
                            cells.at(i - 1).at(j).AdjecentTiles();
                            cells.at(i - 1).at(j + 1).AdjecentTiles();

                            cells.at(i).at(j -1).AdjecentTiles();
                            cells.at(i).at(j + 1).AdjecentTiles();
                        }
                        else{
                            cells.at(i - 1).at(j -1).AdjecentTiles();
                            cells.at(i - 1).at(j).AdjecentTiles();
                            cells.at(i - 1).at(j + 1).AdjecentTiles();

                            cells.at(i).at(j -1).AdjecentTiles();
                            cells.at(i).at(j + 1).AdjecentTiles();

                            cells.at(i + 1).at(j -1).AdjecentTiles();
                            cells.at(i + 1).at(j).AdjecentTiles();
                            cells.at(i + 1).at(j + 1).AdjecentTiles();
                        }
                    }
                }
            }
        }

    }
    void ActivateCell(int x, int y){
        if(!cells.at(y).at(x).FlagStatus())
            cells.at(y).at(x).ToggleCell();
    }
    void FlaggedCell(int x, int y){
        if(!cells.at(y).at(x).CellActiveStatus())
            cells.at(y).at(x).ToggleFlag();
    }
    bool CheckMineClicked(int x, int y){
        if(cells.at(y).at(x).CellActiveStatus() && cells.at(y).at(x).MineStatus())
            return true;
        return false;

    }
    bool GameWon(){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if(!cells[i][j].MineStatus() & !cells[i][j].CellActiveStatus())
                    return false;
            }
        }
        return true;
    }

    void RevealAdjacentCells(const int x, int y){
        if(x < 0 || y < 0 || y > rows - 1  || x > cols - 1 || cells[y][x].CellActiveStatus() || cells[y][x].FlagStatus()){
            return;
        }
        else {
            if (cells.at(y).at(x).CellValue() == 0) {
                cells[y][x].ToggleCell(); // reveal tile
                RevealAdjacentCells(x - 1, y-1);
                RevealAdjacentCells(x - 1, y);
                RevealAdjacentCells(x - 1, y + 1);

                RevealAdjacentCells(x, y + 1);
                RevealAdjacentCells(x, y - 1);

                RevealAdjacentCells(x + 1, y - 1);
                RevealAdjacentCells(x + 1, y);
                RevealAdjacentCells(x + 1, y + 1);
                }
                //todo: make sure is working :)
            else {
             ActivateCell(x,y);
            }
        }
    }



};

#endif //HELLOSFML_BOARD_H
