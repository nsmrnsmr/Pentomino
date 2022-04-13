//Eigenが必要
//ペントミノをはめ込むプログラム
//board.h：盤面のヘッダー
//pentomino.h：ペントミノの:ヘッダー
#include <iostream>
#include <vector>
#include "Eigen/Core"
#include "pentomino.h"
#include "board.h"
using Vec2i = Eigen::Vector2i;

int cnt = 0;
void fill(Pentominos p, Board b){
  for(int i=0; i<12; i++){
    if( !p.pieces[i].use ){
      //std::cout << i <<"\n";
      for(int j=0; j<p.pieces[i].pattern; j++){
        if( b.check(p.pieces[i].pop(j)) ){
          b.setColor(p.pieces[i].color, p.pieces[i].pop(j));
          p.pieces[i].use = true;
          Vec2i s;
          s << b.i, b.j;
          if( !b.next() ){
            cnt++;
            b.print();
            std::cout << "\n";
            return;
          }else{
            fill(p, b);
          }
          //std::cout << b.i << "  "<< b.j <<"\n";
          p.pieces[i].use = false;
          //b.print();
          //std::cout << "\n";
          b.i = s.x();
          b.j = s.y();
          b.setColor(b.def_col, p.pieces[i].pop(j));
        }
      }
    }
  }
}

int main(){
  Pentominos pentos;
  Board board(3,20);

  fill(pentos, board);
  std::cout << cnt << "個\n";
  return 0;
}

