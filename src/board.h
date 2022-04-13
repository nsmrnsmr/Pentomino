#ifndef BOARD_2021_12_21
#define BOARD_2021_12_21

#pragma once
#include <iostream>
#include <vector>
#include "Eigen/Core"
#include "pentomino.h"

#define H 3
#define W 20
using MatXi = Eigen::MatrixXi;
using Vec2i = Eigen::Vector2i;

struct Board{
  MatXi board; //盤面の行列int型（Eigen::MatrixXiを使用）
  const int hight, width; //盤面のサイズ（指定なし：3*20）
  const int def_col; //盤面の基本色（指定なし：白）

  int j; //hight : y 現在注目している盤面のy座標（添字）
  int i; //width : x 現在注目している盤面のx座標（添字）

  //コンストラクタ
  Board(int h=H, int w=W, int col=254, int jj=0, int ii=0):
    hight(h),
    width(w),
    def_col(col),
    j(jj),
    i(ii)
  {
    board =  Eigen::MatrixXi::Constant(h,w,col);
  }
  
  //指定した座標（start）から指定した形（coords）に指定した色（color）をセットする
  void setColor(const Vec2i &start, const int color, const std::vector<Vec2i> &coords){
    for(auto c : coords){
      int x = c.x() + start.x();
      int y = c.y() + start.y();
      board(y, x) = color;
    };
  }

  //指定した座標（start）から指定した形（coords）に盤面のデフォルト色をセットする
  void setColor(const int color, const std::vector<Vec2i> &coords){
    Vec2i s;
    s << i, j;
    for(auto c : coords){
      int x = c.x() + s.x();
      int y = c.y() + s.y();
      board(y, x) = color;
    };
  }

  //盤面にペントミノをはめる
  void setColor(const Pentomino &p){
    Vec2i s;
    s << i, j;
    int col = p.color;
    for(auto c : p.coords){
      int x = c.x() + s.x();
      int y = c.y() + s.y();
      board(y, x) = col;
    };
  }

  //指定した座標が盤面内か判定する
  bool checkInner(const Vec2i &coord){
    if( coord.x() < width && coord.x() >= 0 &&
      coord.y() < hight && coord.y() >= 0){
      return true;
    }
    return false;

  }

  //指定した座標が既に塗られているか判定
  bool checkFilled(const Vec2i &coord){
    return board(coord.y(), coord.x()) != def_col;
  }

  //指定した座標が既に塗られているか判定（x，y）
  bool checkFilled(const int ii, const int jj){
    return board(jj, ii) != def_col;
  }

  //指定した座標たちに対して，checkInner，checkFilledを実行
  bool check(const std::vector<Vec2i> &coord){
    Vec2i s;
    s << i, j;
    for(auto c : coord){
      if( !checkInner(c+s) ) return false;
      if( checkFilled(c+s) ) return false;
    }
    return true;
  }

  //i，jを１つ進める（次の塗られていないマスに進む）
  bool next(){
    int tmpi = i;
    int tmpj = j;
    while( true ){
      tmpj = (tmpj+1) % hight;
      if( tmpj == 0 ) tmpi++;
      if( tmpi == width ) return false;
      if( !checkFilled(tmpi, tmpj) ){
        i = tmpi;
        j = tmpj;
        return true;
      }
    }
    return false;
  }

  //盤面を表示
  void print(){
    for(int jj=hight-1; jj>=0; jj--){
      for(int ii=0; ii<width; ii++){
        std::cout << "\033[38;5;"<< board(jj, ii) <<"m";
        std::cout << "▉";
        std::cout <<"\033[0m";
      }
      std::cout << "\n";
    }
  }
};
#endif
