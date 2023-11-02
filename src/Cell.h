//
// Created by Mya  on 7/25/23.
//
#include <iostream>
using namespace std;


#ifndef HELLOSFML_CELL_H
#define HELLOSFML_CELL_H

class Cell{
    int value;
    bool mine;
    bool cell_active;
    bool cell_flagged;

public:
    Cell(){
        this->value = 0;
        this->mine = false;
        this->cell_active = false;
        this->cell_flagged = false;
    }

    void ActiveMine(){
        this->mine = true;
        this->value = 5;
    }
    void AdjecentTiles(){
        this->value += 1;
    }

    void PrintCell(){
        if (mine){
            cout << "x";
        }
        else{
            cout << value;
        }
    }

    bool MineStatus(){
        return mine;
    }
    bool CellActiveStatus(){
        return cell_active;
    }
    void ToggleCell(){
        this->cell_active = true;
    }

    void ToggleFlag(){
        this->cell_flagged = !cell_flagged;

    }
    bool FlagStatus(){
        return cell_flagged;
    }


    int CellValue(){
        return value;
    }

};

#endif //HELLOSFML_CELL_H
