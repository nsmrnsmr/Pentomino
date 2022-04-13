//ピースを全て表示するサンプルコード
#include <iostream>
#include <vector>
#include "Eigen/Core"
#include "pentomino.h"
#include "board.h"
using Vec2i = Eigen::Vector2i;

int main(){
  Pentominos pentos;
  for(int i=0; i<12; i++){
    for(int j=0; j<pentos.pieces[i].pattern; j++){
      Board board(10, 10, 254, 4, 4);
      board.setColor(pentos.pieces[i].color, pentos.pieces[i].pop(j));
      board.print();
      std::cout << "\n";
    }
  }
  return 0;
}

